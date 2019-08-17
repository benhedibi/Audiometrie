#include <patients_import.h>
#include <patients_engine.h>
#include <lilly_io.h>
#include <lilly_mem.h>
#include <lilly_utils.h>
#include <lilly_os.h>
#include <cmnfnc.h>
#include <db_signatures.h>

#define PATIENT_CODEP       0
#define PATIENT_NOM         1
#define PATIENT_AGE         2
#define PATIENT_PROFESSION  3
#define PATIENT_VILLE       4
#define PATIENT_GOUVERNORA  5
#define PATIENT_PAYS        6
#define PATIENT_CODEM       7
#define PATIENT_OBS         8
#define PATIENT_NELE        9
#define PATIENT_TEL         10
#define PATIENT_DELEGATION  11
#define PATIENT_OP          12
#define PATIENT_MAIL        13
#define PATIENT_TEL2        14


static boolean add_record(const p_lilly_db_session_manager session_manager,const p_lilly_db_engine db_engine,const struct t_lilly_db_handle *db_handle,const puchar buffer,const unsigned_int buffer_size,const t_serializer_callback serializer_callback)
{
  uint64 offset;
  puchar observations;
  unsigned_int observations_len;
  int i;
  t_lilly_db_time_stamp date_stamp;
  t_patient_record record;
  t_db_field_buffer field_buffer;


	 avcore_memset(&record,0,sizeof(record));

     record.gouvernorat = 21;

	 record.pays = 184;

	 record.sexe = 0xFF;

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_CODEP,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!field_buffer.field_len)
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_DATA_CONVERSION_ERROR;
	   return FALSE;
	 }

	 for (i = 0; i < field_buffer.field_len; i += 2)
	 {
	   switch (field_buffer.data[i])
	   {
		 case '0' :
		 case '1' :
		 case '2' :
		 case '3' :
		 case '4' :
		 case '5' :
		 case '6' :
		 case '7' :
		 case '8' :
		 case '9' : break;

		  default : db_engine->error_code = LILLY_DB_IMPORT_DATA_CONVERSION_ERROR;
					return FALSE;
	   }
	 }

	 if (serializer_callback)
	 {
	   serializer_callback(&field_buffer,t_lilly_db_import_codep_serializer);
	   if (!field_buffer.field_len) return TRUE;
	 }

	 record.code_patient.unique_index = avcore_watoi((puchar)&field_buffer.data);

     //if (record.code_patient.unique_index == 6491) asm int 03;
	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_NOM,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
	   if (serializer_callback)
	   {
		 field_buffer.data[sizeof(field_buffer.data) - 1] = 0xFF;
		 serializer_callback(&field_buffer,t_lilly_db_import_patient_name_serializer);
		 record.sexe = field_buffer.data[sizeof(field_buffer.data) - 1];
	   }

	   avcore_memcpy(&record.nom_prenom,&field_buffer.data,MACRO_MIN_VALUE(sizeof(record.nom_prenom) - 2,field_buffer.field_len));
	 }
	 else return TRUE; // we skip empty names



	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_AGE,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
	   for (i = 0; i < field_buffer.field_len; i += 2)
	   {
		 switch (field_buffer.data[i])
		 {
		   case '0' :
		   case '1' :
		   case '2' :
		   case '3' :
		   case '4' :
		   case '5' :
		   case '6' :
		   case '7' :
		   case '8' :
		   case '9' : break;

			default : db_engine->error_code = LILLY_DB_IMPORT_DATA_CONVERSION_ERROR;
					  return FALSE;
		 }
	   }

	   record.age_consultation = avcore_watoi((puchar)&field_buffer.data);
	 }

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_PROFESSION,buffer,buffer_size))
	 {
       db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!field_buffer.field_len)
	 {
	   avcore_memcpy(&record.travail,DEFAULT_NAME,MACRO_MIN_VALUE(sizeof(record.travail) - 2,DEFAULT_NAME_LEN));
	 }
	 else
	 {
	   if (serializer_callback)
	   {
		 serializer_callback(&field_buffer,t_lilly_db_import_job_serializer);
	   }

	   avcore_memcpy(&record.travail,&field_buffer.data,MACRO_MIN_VALUE(sizeof(record.travail) - 2,field_buffer.field_len));
	 }

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_VILLE,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
	   if (serializer_callback)
	   {
		 serializer_callback(&field_buffer,t_lilly_db_import_ville_serializer);
	   }

	   avcore_memcpy(&record.ville,&field_buffer.data,MACRO_MIN_VALUE(sizeof(record.ville) - 2,field_buffer.field_len));
	 }

     if (!lilly_import_read_db_field(&field_buffer,PATIENT_PAYS,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
	   if (field_buffer.data[0] == '.')
	   {
		 record.pays = 184;
		 record.gouvernorat = 22;
		 goto leave_me_alone;
	   }

	   if (serializer_callback)
	   {
		 serializer_callback(&field_buffer,t_lilly_db_import_pays_serializer);
	   }

	   record.pays = field_buffer.data[0];
	 }

	 if (record.pays == 184)
	 {
	   if (!lilly_import_read_db_field(&field_buffer,PATIENT_GOUVERNORA,buffer,buffer_size))
	   {
		 db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
		 return FALSE;
	   }

	   if (field_buffer.field_len)
	   {
		 if (serializer_callback)
		 {
		   serializer_callback(&field_buffer,t_lilly_db_import_gouvernorat_serializer);
		 }

		 record.gouvernorat = field_buffer.data[0];
	   }
	 }
     else record.gouvernorat = 0xFF;

	 leave_me_alone :

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_CODEM,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if ((!field_buffer.field_len) || ((field_buffer.field_len == 2) && (field_buffer.data[0] == '.')))
	 {
	   field_buffer.field_len = DEFAULT_NAME_LEN;
	   avcore_memcpy(&field_buffer.data,DEFAULT_NAME,DEFAULT_NAME_LEN);
	 }

     if (serializer_callback)
	 {
	   serializer_callback(&field_buffer,t_lilly_db_import_doctor_name_serializer);
	 }

	 record.code_medecin = session_manager->doctor_name_to_id(session_manager,(puchar)&field_buffer.data,field_buffer.field_len);

	 if (record.code_medecin == IO_ERROR)
	 {
	   db_engine->error_code = session_manager->error_code;
	   return FALSE;
     }

     if (!lilly_import_read_db_field(&field_buffer,PATIENT_OP,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (!field_buffer.field_len)
	 {
	   field_buffer.field_len = DEFAULT_OPERATOR_NAME_LEN;
	   avcore_memcpy(&field_buffer.data,DEFAULT_OPERATOR_NAME,DEFAULT_OPERATOR_NAME_LEN);
	 }
	 else if (serializer_callback)
	 {
	   serializer_callback(&field_buffer,t_lilly_db_import_operator_name_serializer);
	 }

	 date_stamp.operator_id = (uint64)session_manager->operator_name_to_id(session_manager,(puchar)&field_buffer.data,field_buffer.field_len);

	 if (date_stamp.operator_id == IO_ERROR)
	 {
	   db_engine->error_code = API_ERROR;
	   return FALSE;
	 }

     if (!lilly_import_read_db_field(&field_buffer,PATIENT_OBS,buffer,buffer_size))
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

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_NELE,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
	   if ((field_buffer.data[0] != '.') && (field_buffer.field_len != 1) && (!lilly_import_str_to_date((puchar)&field_buffer.data,field_buffer.field_len,&record.date_naissance)))
	   {
		 db_engine->error_code = LILLY_DB_IMPORT_DATA_CONVERSION_ERROR;
		 db_engine->rtm_params_size = record.code_patient.unique_index;
		 return FALSE;
	   }
	 }

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_TEL,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
       avcore_memcpy(&record.phone_principal,&field_buffer.data,MACRO_MIN_VALUE(sizeof(record.phone_principal) - 2,field_buffer.field_len));
	 }

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_MAIL,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
	   if (serializer_callback)
	   {
		 serializer_callback(&field_buffer,t_lilly_db_import_generic_string_serializer);
	   }

	   avcore_memcpy(&record.email,&field_buffer.data,MACRO_MIN_VALUE(sizeof(record.email) - 2,field_buffer.field_len));
	 }

	 if (!lilly_import_read_db_field(&field_buffer,PATIENT_TEL2,buffer,buffer_size))
	 {
	   db_engine->error_code = LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR;
	   return FALSE;
	 }

	 if (field_buffer.field_len)
	 {
	   avcore_memcpy(&record.phone_secondaire,&field_buffer.data,MACRO_MIN_VALUE(sizeof(record.phone_secondaire) - 2,field_buffer.field_len));
	 }
	 
	 if (!db_engine->append_record(db_engine,db_handle,&record))
	 {
	   if (db_engine->error_code == LILLY_DB_DUPLICATE_RECORD_ERROR)
	   {
		 return TRUE;
	   }
	   return FALSE;
	 }

	 offset = lilly_db_get_current_record_offset(db_handle);

	 lilly_os_get_current_time_stamp(&date_stamp.time_stamp);

	 if (!lilly_db_set_record_creation_time(db_handle,offset,&date_stamp,TRUE))
	 {
	   db_engine->error_code = lilly_db_get_last_error(db_handle);
	   return FALSE;
	 }

     return TRUE;

}

struct t_lilly_db_handle* __fastcall patients_import_execute(const p_lilly_db_session_manager session_manager,const puchar source_path,const puchar destination_path,const unsigned_int destination_path_len,const uint64 db_flags,const uint32 operator_id,const uint32 session_id,const p_serializer_callback serializer_callback,const punsigned_int error_code,const puint32 bad_dates)
{
  unsigned_int fhandle,fsize,size_left,index;
  puchar fbuffer,data;
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

	 db_engine = session_manager->register_lilly_engine(session_manager,PATIENT_DB_SIGNATURE);

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

	 index = 0;


	 while (TRUE)
	 {
	   if (!add_record(session_manager,db_engine,db_handle,data,size_left,serializer_callback))
	   {
		 if (db_engine->error_code == LILLY_DB_IMPORT_DATA_CONVERSION_ERROR)
		 {
		   bad_dates[index++] = db_engine->rtm_params_size;
		 }
		 else
		 {
		   *error_code = lilly_db_get_last_error(db_handle);
		   break;
		 }
	   }

	   if (db_engine->error_code == LILLY_DB_DUPLICATE_RECORD_ERROR)
	   {
		 bad_dates[index++] = db_engine->rtm_params_size;
	   }

	   data = lilly_import_get_next_field(data,&size_left);

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
