#include <tympano_import.h>
#include <tympano_engine.h>
#include <patients_engine.h>
#include <lilly_io.h>
#include <lilly_mem.h>
#include <lilly_utils.h>
#include <lilly_os.h>
#include <cmnfnc.h>
#include <db_signatures.h>


#define TYMPANO_CODEP 0
#define TYMPANO_DATE  1
#define TYMPANO_OD    2
#define TYMPANO_RSOD  3
#define TYMPANO_OG    4
#define TYMPANO_RSOG  5
#define TYMPANO_OBS   6
#define TYMPANO_OP    7


static boolean read_valeurs(const p_tympano_oreille oreille,const p_db_field_buffer field_buffer,const p_str_to_float_callback callback)
{
  puchar p = (puchar)&field_buffer->data;
  puchar src,dest;
  int i,ix;
  uchar tmp[8],tmp2[16];


	  for (i = 1; i <= 13; i++)
	  {
		src = &tmp;

		*(puint64)src = *(puint64)(p + ((i - 1) * 8));

		avcore_memset(&tmp2,0,sizeof(tmp2));

		dest = &tmp2;

		for (ix = 0; ix < 4; ix++)
		{
		  if (*src != ' ')
		  {
			if (*src == '.')
			{
			  if (ix == 0)
			  {
				*dest++ = '0';
				*dest++ = 0;
			  }

			  *dest++ = ',';
			  *dest++ = 0;
			}
			else
			{
			  *(puint16)dest = *(puint16)src;
			  dest += 2;
			}
		  }
		  src += 2;
		}

		if (tmp2[0] == 0)
		{
		  tmp2[0] = '0';
		}

		oreille->valeurs[i - 1] = callback((puchar)&tmp2);
	  }

	  return TRUE;


}

static boolean read_reflexes(const p_tympano_oreille oreille,const p_db_field_buffer field_buffer)
{
  puchar p = (puchar)&field_buffer->data;
  unsigned_int index,val_len;
  uchar conv_buffer[8];


	 index = 0;

	 conv_buffer[7] = 0;

	 while (TRUE)
	 {
	   val_len = 0;

	   while (TRUE)
	   {
		 if ((*p == ' ') || (*p == 0) || (val_len >= 6)) break;
		 *(puint16)&conv_buffer[val_len] = *(puint16)p;
		 p += 2;
		 val_len += 2;
		 field_buffer->field_len -= 2;
	   }

	   *(puint16)&conv_buffer[val_len] = 0;

	   oreille->reflexes[index++] = avcore_watoi((puchar)&conv_buffer);

	   if ((signed_int)field_buffer->field_len <= 0) break;

	   if (index >= sizeof(oreille->reflexes) / sizeof(oreille->reflexes[0]))
	   {
		 return FALSE;
	   }

	   while (TRUE)
	   {
		 if (*p != ' ') break;

		 field_buffer->field_len -= 2;

		 if ((signed_int)field_buffer->field_len <= 0) return FALSE;

		 p += 2;
	   }

	 }

	 return TRUE;
}

static boolean lilly_import_read_db_field_ex(const p_db_field_buffer field_buffer,unsigned_int field_index,puchar data,unsigned_int data_size)
{
  const puchar null_field = (puchar)L"** NULL **";
  const null_field_len = 20;

  puint16 pw;
  boolean guillemet_found = FALSE;


	 if ((signed_int)field_index < 0) return FALSE;

	 while (field_index)
	 {
	   field_index -= (*data == ',');
	   data += 2;
	   data_size -= 2;
	   if ((signed_int)data_size <=0) return FALSE;
	 }

	 if (*data == '"')
	 {
	   guillemet_found = TRUE;
	   data += 2;
	   data_size -= 2;
	 }

	 if ((*data == '*') && (data_size >= null_field_len)) // is it an empty field ?
	 {
	   if (avcore_memcmp(data,null_field,null_field_len))
	   {
		 field_buffer->field_len = 0;
		 field_buffer->data[0] = 0;
		 return TRUE;
       }
	 }

	 if ((signed_int)data_size <= 0) return FALSE;

	 while (*data == ' ') // clean space at the beginning
	 {
	   data += 2;
	   data_size -= 2;
	   if ((signed_int)data_size <= 0) return FALSE;
	 }

	 field_buffer->field_len = 0;

	 pw = (puint16)&field_buffer->data[0];

	 while (TRUE)
	 {
	   if (((signed_int)data_size <= 0) || (*data == '"') || (*data == ',') || (field_buffer->field_len >= sizeof(field_buffer->data) - 2)) break;

	   *pw = *(puint16)data;

	   data_size -= 2;

	   data += 2;

	   pw++;

	   field_buffer->field_len += 2;
	 }

	 if (!field_buffer->field_len) return TRUE; // something went wrong

	 pw -= (int)guillemet_found;

	 *pw = 0;

	 field_buffer->field_len -= ((int)guillemet_found * 2);

	 return TRUE;

}

static boolean add_record(const p_lilly_db_session_manager session_manager,const p_lilly_db_engine db_engine,const struct t_lilly_db_handle *db_handle,const puchar buffer,const unsigned_int buffer_size,const p_str_to_float_callback callback)
{
  uint64 offset;
  puchar observations;
  unsigned_int observations_len;
  p_patient_record pat_rec;
  t_lilly_db_time_stamp date_stamp;
  t_tympanogram_record record;
  t_db_field_buffer field_buffer;


	 avcore_memset(&record,0,sizeof(record));

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_CODEP,buffer,buffer_size))
	 {
	   db_engine->rtm_params_size = 123456;
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 record.code_patient = avcore_watoi((puchar)&field_buffer.data);

	// if (record.code_patient == 9003) asm int 03;

	 {
	   p_lilly_db_engine patients_db_engine;
	   struct t_lilly_db_handle * patients_db_handle;

	   patients_db_engine = session_manager->request_lilly_engine(session_manager,PATIENT_DB_SIGNATURE);

	   if (!patients_db_engine)
	   {
		 db_engine->error_code = session_manager->error_code;
		 return FALSE;
	   }

	   patients_db_handle = session_manager->request_db_handle(session_manager,PATIENT_DB_SIGNATURE);

	   if (!patients_db_handle)
	   {
		 db_engine->error_code = session_manager->error_code;
		 return FALSE;
       }

	   pat_rec = (p_patient_record)patients_db_engine->code_to_record(patients_db_engine,patients_db_handle,record.code_patient);

	   if (!pat_rec)
	   {
		 return TRUE; // entrée orpheline
	   }

	   record.code_medecin = pat_rec->code_medecin;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_DATE,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_str_to_date((puchar)&field_buffer.data,field_buffer.field_len,&date_stamp.time_stamp))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_DATA_CONVERSION_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_OD,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_valeurs(&record.oreille_droite,&field_buffer,callback)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_RSOD,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_reflexes(&record.oreille_droite,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_OG,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_valeurs(&record.oreille_gauche,&field_buffer,callback)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_RSOG,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_reflexes(&record.oreille_gauche,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_OP,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!field_buffer.field_len)
	 {
	   field_buffer.field_len = DEFAULT_OPERATOR_NAME_LEN;

	   *(puint16)&field_buffer.data[DEFAULT_OPERATOR_NAME_LEN] = 0;

	   avcore_memcpy((puchar)&field_buffer.data[0],DEFAULT_OPERATOR_NAME,DEFAULT_OPERATOR_NAME_LEN);
	 }

	 date_stamp.operator_id = session_manager->operator_name_to_id(session_manager,(puchar)&field_buffer.data,field_buffer.field_len);

	 if (date_stamp.operator_id == (uint32)IO_ERROR)
	 {
	   db_engine->error_code = session_manager->error_code;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,TYMPANO_OBS,buffer,buffer_size))
	 {
       if (!lilly_import_read_db_field_ex(&field_buffer,TYMPANO_OP,buffer,buffer_size))
	   {
		 db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	   }
	 }

	 if (field_buffer.field_len)
	 {
	   t_lilly_db_blob_name blob_name;

	   if (!lilly_db_record_id_to_blob_name_id(db_handle,&blob_name,lilly_db_get_unique_autoinc_key(db_handle),t_lilly_db_observations_confidentielles_blob_type))
	   {
		 db_engine->error_code = lilly_db_get_last_error(db_handle);
		 return FALSE;
	   }

	   if (!lilly_db_create_blob(db_handle,&blob_name,(puchar)&field_buffer.data,field_buffer.field_len,date_stamp.operator_id))
	   {
		 db_engine->error_code = lilly_db_get_last_error(db_handle);
		 return FALSE;
       }
	 }

	 if (!db_engine->append_record(db_engine,db_handle,&record)) return FALSE;

	 offset = lilly_db_get_current_record_offset(db_handle);

	 if (!lilly_db_set_record_creation_time(db_handle,offset,&date_stamp,TRUE))
	 {
	   db_engine->error_code = lilly_db_get_last_error(db_handle);
	   return FALSE;
	 }

	 return TRUE;

}

struct t_lilly_db_handle* tympano_import_execute(const p_lilly_db_session_manager session_manager,const puchar source_path,const puchar destination_path,const unsigned_int destination_path_len,const uint64 db_flags,const uint32 operator_id,const uint32 session_id,const t_str_to_float_callback callback,const punsigned_int error_code)
{
  unsigned_int fhandle,fsize,size_left;
  puchar fbuffer,data;
  int index;
  struct t_lilly_db_handle* db_handle;
  p_lilly_db_engine db_engine;


	 *error_code = ERROR_SUCCESS;

	 fhandle = lilly_io_open_file(source_path,lilly_io_fmOpen,lilly_io_faRead);

	 if ((signed_int)fhandle <= 0)
	 {
	   *error_code = IO_ERROR;
	   return NULL;
	 }

	 db_handle = NULL;

	 fsize = lilly_io_get_file_size_ex(fhandle);

	 if ((signed_int)fsize <= 0) goto fermer_handle;

	 fbuffer = lilly_malloc(fsize);

	 if (!fbuffer)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   goto fermer_handle;
	 }

	 if (!lilly_io_file_read(fhandle,fbuffer,fsize))
	 {
	   *error_code = IO_ERROR;
	   goto liberer_memoire;
	 }

	 db_engine = session_manager->register_lilly_engine(session_manager,TYMPANOGRAM_DB_SIGNATURE);

	 if (!db_engine)
	 {
	   *error_code = session_manager->error_code;
	   goto liberer_memoire;
	 }

	 db_handle = db_engine->new_database(db_engine,destination_path,destination_path_len,db_flags,operator_id,session_id);

	 if (!db_handle)
	 {
	   *error_code = db_engine->error_code;
	   goto liberer_memoire;
	 }

	 lilly_db_set_blob_db_path(db_handle,L"C:\\patient2k19\\databases\\blobs\\tympanograms\\",avcore_wstrlen(L"C:\\patient2k19\\databases\\blobs\\tympanograms\\") * 2);

	 size_left = fsize;
	 data = lilly_import_get_first_field(fbuffer,&size_left);

	 if ((!data) || ((signed_int)size_left <= 0))
	 {
	   *error_code = DATA_SIGNATURE_ERROR;
	   goto liberer_memoire;
	 }

	 index = 0;

	 while (TRUE)
	 {
	   if (!add_record(session_manager,db_engine,db_handle,data,size_left,callback))
	   {
		 if (db_engine->rtm_params_size != 123456)
		 {
		 *error_code = lilly_db_get_last_error(db_handle);
		 break;
         }
	   }

	   data = lilly_import_get_next_field(data,&size_left);

	   index++;

      //if (index == 10993) asm int 03;

	   if ((!data) || ((signed_int)size_left <= 0)) break;
	 }

	 liberer_memoire :

	 if (fbuffer)
	 {
	   lilly_free(fbuffer,fsize);
	 }

	 fermer_handle :

	 lilly_io_close_file(fhandle);

	 return db_handle;

}
