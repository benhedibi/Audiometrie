#include <audiog_import.h>
#include <audiograms_engine.h>
#include <patients_engine.h>
#include <lilly_io.h>
#include <lilly_mem.h>
#include <lilly_utils.h>
#include <lilly_os.h>
#include <cmnfnc.h>
#include <db_signatures.h>

#define AUDIOG_CODEP 0
#define AUDIOG_DATE   1
#define AUDIOG_VAOD   2
#define AUDIOG_VOOD   3
#define AUDIOG_VAOG   4
#define AUDIOG_VOOG   5
#define AUDIOG_WEBER  6
#define AUDIOG_OBS    7
#define AUDIOG_MASQ   8
#define AUDIOG_UCLD   9
#define AUDIOG_UCLG   10
#define AUDIOG_CONF   11
#define AUDIOG_OP     12


static boolean read_va(const p_audiogram_oreille oreille,const p_db_field_buffer field_buffer)
{
  puchar p = (puchar)&field_buffer->data;
  unsigned_int index,val_len;
  uchar conv_buffer[8];
  //boolean is_intermediaire[7] = {FALSE,TRUE,TRUE,
  uint8 valeur,intermediaire;

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

	   valeur = avcore_watoi((puchar)&conv_buffer);

	   if ((index >= 1) && (index < 9))
	   {
		 //intermediaire = (valeur - oreille->va[index - 1]) / 2;
		 oreille->va[index++] = valeur;
		 oreille->va[index++] = valeur; // + intermediaire;
	   }
	   else oreille->va[index++] = valeur;

	   if ((signed_int)field_buffer->field_len <= 0) break;

	   if (index >= sizeof(oreille->va) / sizeof(oreille->va[0]))
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

static boolean read_vo(const p_audiogram_oreille oreille,const p_db_field_buffer field_buffer)
{
  puchar p = (puchar)&field_buffer->data;
  unsigned_int index,val_len;
  uchar conv_buffer[8];
  uint8 valeur,intermediaire;

	 index = 0;

	 conv_buffer[7] = 0;

	 while (TRUE)
	 {
	   val_len = 0;

	   while (TRUE)
	   {
		 if ((*p == ' ') || (*p == 0) || (val_len >= 4)) break;
		 *(puint16)&conv_buffer[val_len] = *(puint16)p;
		 p += 2;
		 val_len += 2;
		 field_buffer->field_len -= 2;
	   }

	   *(puint16)&conv_buffer[val_len] = 0;

	   valeur = avcore_watoi((puchar)&conv_buffer);

	   if ((index >= 1) && (index < 9))
	   {
		 //intermediaire = (valeur - oreille->va[index - 1]) / 2;
		 oreille->vo[index++] = valeur;
		 oreille->vo[index++] = valeur; // + intermediaire;
	   }
	   else oreille->vo[index++] = valeur;

	   if ((signed_int)field_buffer->field_len <= 0) break;

	   if (index >= sizeof(oreille->vo) / sizeof(oreille->vo[0]))
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

static boolean read_ucl(const p_audiogram_oreille oreille,const p_db_field_buffer field_buffer)
{
  puchar p = (puchar)&field_buffer->data;
  unsigned_int index,val_len;
  uchar conv_buffer[8];
  uint8 valeur;

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

	   valeur = avcore_watoi((puchar)&conv_buffer);

	   if ((index >= 1) && (index < 9))
	   {
		 oreille->ucl[index++] = valeur;
		 oreille->ucl[index++] = valeur;
	   }
	   else oreille->ucl[index++] = valeur;

	   if ((signed_int)field_buffer->field_len <= 0) break;

	   if (index >= sizeof(oreille->va) / sizeof(oreille->va[0]))
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

static boolean read_weber(const p_audiogram_record record,const p_db_field_buffer field_buffer)
{
  puchar p = (puchar)&field_buffer->data;
  uchar conv_buffer[4];
  int i;

	 if (field_buffer->field_len != 10) return FALSE;

	 conv_buffer[3] = 0;

	 for (i = 0; i < 5; i++)
	 {
	   *(puint16)&conv_buffer[0] = *((puint16)p);
	   record->weber[i] = avcore_watoi((puchar)&conv_buffer);
	   p += 2;
	 }

	 return TRUE;
}


static boolean read_conf(const p_audiogram_record record,const p_db_field_buffer field_buffer)
{
  puchar p = (puchar)&field_buffer->data;
  int i;

	for (i = 1; i < field_buffer->field_len / 2; i++)
	{
	  if (*p == '1')
	  {
		SET_ATTRIBUTE(record->parametres_confidentiels,(1 << i));
	  }

	  p += 2;
	}

    return TRUE;
}

static boolean add_record(const p_lilly_db_session_manager session_manager,const p_lilly_db_engine db_engine,const struct t_lilly_db_handle *db_handle,const puchar buffer,const unsigned_int buffer_size)
{
  uint64 offset;
  puchar observations;
  p_patient_record pat_rec;
  unsigned_int observations_len;
  t_lilly_db_time_stamp date_stamp;
  t_audiogram_record record;
  t_db_field_buffer field_buffer;



	 avcore_memset(&record,0,sizeof(record));

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_CODEP,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 record.code_patient = avcore_watoi((puchar)&field_buffer.data);

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

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_DATE,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_str_to_date((puchar)&field_buffer.data,field_buffer.field_len,&date_stamp.time_stamp))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_DATA_CONVERSION_ERROR;
	   return FALSE;
	 }

	 if (date_stamp.time_stamp.year == 2099) // corriger une foutaise de saisie
	 {
	   date_stamp.time_stamp.year = 2000;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_VAOD,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_va(&record.oreille_droite,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_VOOD,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_vo(&record.oreille_droite,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_VAOG,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_va(&record.oreille_gauche,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_VOOG,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_vo(&record.oreille_gauche,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_UCLD,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_ucl(&record.oreille_droite,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_UCLG,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_ucl(&record.oreille_gauche,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_WEBER,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_weber(&record,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

     if (!lilly_import_read_db_field(&field_buffer,AUDIOG_OP,buffer,buffer_size))
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

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_OBS,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
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

	 if (!lilly_import_read_db_field(&field_buffer,AUDIOG_CONF,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((field_buffer.field_len) && (!read_conf(&record,&field_buffer)))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
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

struct t_lilly_db_handle* audiog_import_execute(const p_lilly_db_session_manager session_manager,const puchar source_path,const puchar destination_path,const unsigned_int destination_path_len,const uint64 db_flags,const uint32 operator_id,const uint32 session_id,const t_serializer_callback serializer_callback,const punsigned_int error_code)
{
  unsigned_int fhandle,fsize;
  puchar fbuffer,data;
  unsigned_int size_left;
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

	 db_engine = session_manager->register_lilly_engine(session_manager,AUDIOGRAM_DB_SIGNATURE);

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

	 size_left = fsize;
	 data = lilly_import_get_first_field(fbuffer,&size_left);

	 if ((!data) || ((signed_int)size_left <= 0))
	 {
	   *error_code = DATA_SIGNATURE_ERROR;
	   goto liberer_memoire;
	 }
	 //int index = 0;
	 while (TRUE)
	 {
	   if (!add_record(session_manager,db_engine,db_handle,data,size_left))
	   {
		 *error_code = lilly_db_get_last_error(db_handle);
		 break;
	   }

	   data = lilly_import_get_next_field(data,&size_left);

	  // index++;

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

