#include <operateurs_.h>
#include <db_signatures.h>
#include <cmnfnc.h>
#include <lilly_utils.h>


p_lilly_db_handle operator_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code)
{

	 if (!error_code) return NULL;

	 *error_code = ERROR_SUCCESS;

	 return lilly_db_create_db_handle(database_path,db_path_len,OPERATEUR_RECORD_SIZE,LILLY_DB_DATABASE_HEADER_SIZE,operator_id,session_id,OPERATOR_DB_SIGNATURE,databse_flags,error_code);
}

p_lilly_db_handle operator_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code)
{

	 if (!error_code) return NULL;

	 *error_code = ERROR_SUCCESS;

	 return lilly_db_open_db_handle(database_path,db_path_len,OPERATOR_DB_SIGNATURE,operator_id,error_code);

}

void operator_db_close_database(const p_lilly_db_handle db_handle)
{

	 lilly_db_close_db_handle(db_handle);

	 return;
}

boolean operator_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path)
{
	 return lilly_db_export_database(db_handle,database_path);
}

boolean operator_db_append_record(const p_lilly_db_handle db_handle,const p_operateur_record record)
{
  p_operateur_record iterator;


	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 record->code_operateur.unique_index = operator_db_get_record_crc(db_handle,record);

	 if (!record->code_operateur.unique_index) return FALSE;

	 record->code_operateur.crc32 = record->code_operateur.unique_index;

	 iterator = (p_operateur_record)lilly_db_get_first_record(db_handle);

	 if (!iterator)
	 {
	   if (lilly_db_get_last_error(db_handle) != LILLY_DB_EMPTY_DATABASE_ERROR) return FALSE;

	   lilly_db_set_last_error(db_handle,ERROR_SUCCESS);
	 }
	 else
	 {
	   while (TRUE)
	   {
		 if (iterator->code_operateur.crc32 == record->code_operateur.crc32)
		 {
		   lilly_db_set_last_error(db_handle,LILLY_DB_DUPLICATE_RECORD_ERROR);
		   return FALSE;
		 }

		 iterator = (p_operateur_record)lilly_db_get_next_record(db_handle);

		 if (!iterator) break;
	   }
	 }

	 return ((lilly_db_get_last_error(db_handle) == ERROR_SUCCESS) && (lilly_db_append_record(db_handle,(puchar)record,OPERATEUR_RECORD_SIZE)));
}

boolean operator_db_edit_record(const p_lilly_db_handle db_handle,const p_operateur_record record,const uint64 record_offset)
{
  p_operateur_record iterator;


	 if ((int64)record_offset <= 0)
	 {
	   lilly_db_set_last_error(db_handle,API_ERROR);
	   return FALSE;
	 }

	 iterator = (p_operateur_record)lilly_db_get_first_record(db_handle);

	 if (!iterator) return FALSE;

	 while (TRUE)
	 {
	   if (iterator->code_operateur.crc32 == record->code_operateur.crc32)
	   {
		 lilly_db_set_last_error(db_handle,LILLY_DB_DUPLICATE_RECORD_ERROR);
		 return FALSE;
	   }

	   iterator = (p_operateur_record)lilly_db_get_next_record(db_handle);

	   if (!iterator) break;
	 }

	 return ((lilly_db_get_last_error(db_handle) == ERROR_SUCCESS) && (lilly_db_edit_record(db_handle,(puchar)record,OPERATEUR_RECORD_SIZE,record_offset)));
}

boolean operator_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset)
{

	 return lilly_db_delete_record(db_handle,record_offset);
}

p_operateur_record operator_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params)
{
	 return NULL;
}

p_operateur_record operator_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params)
{
	 return NULL;
}

p_operateur_record operator_db_codeop_to_record(const p_lilly_db_handle db_handle,const uint32 codeop)
{
  p_operateur_record iterator;


	 if (!db_handle) return NULL;

	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 iterator = (p_operateur_record)lilly_db_get_first_record(db_handle);

	 if (!iterator) return NULL;

	 while (TRUE)
	 {
	   if (iterator->code_operateur.unique_index == codeop) break;

	   iterator = (p_operateur_record)lilly_db_get_next_record(db_handle);

	   if (!iterator) break;
	 }

     return iterator;
}

uint32 operator_db_get_record_crc(const p_lilly_db_handle db_handle,const p_operateur_record record)
{
  puchar p;
  uint32 crc = 0;
  t_lilly_serialized_string serialized_result;


	 if (!db_handle) return 0;

	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 if ((!record) || (record->nom_prenom[0] == 0))
	 {
	   lilly_db_set_last_error(db_handle,API_ERROR);
	   return 0;
	 }

	 p = (puchar)&record->nom_prenom[0];

	 if (!lilly_serialize_string_field(p,avcore_wstrlen(p) * 2,&serialized_result))
	 {
	   lilly_db_set_last_error(db_handle,LILLY_DB_SERIALIZE_DATA_ERROR);
	   return 0;
	 }

	 crc = lilly_crc32_serialized_result(&serialized_result,crc);

	 if (!crc)
	 {
	   lilly_db_set_last_error(db_handle,LILLY_DB_UNSPECIFIED_FATAL_ERROR);
	   return 0;
	 }

	 p = (puchar)&record->phone_principal[0];

	 if (*p != 0)
	 {
	   if (!lilly_serialize_phone_field(p,avcore_wstrlen(p) * 2,&serialized_result))
	   {
		 lilly_db_set_last_error(db_handle,LILLY_DB_SERIALIZE_DATA_ERROR);
		 return 0;
	   }

	   crc = lilly_crc32_serialized_result(&serialized_result,crc);

	   if (!crc)
	   {
		 lilly_db_set_last_error(db_handle,LILLY_DB_UNSPECIFIED_FATAL_ERROR);
		 return 0;
	   }
	 }

	 p = (puchar)&record->phone_secondaire[0];

	 if (*p != 0)
	 {
	   if (!lilly_serialize_phone_field(p,avcore_wstrlen(p) * 2,&serialized_result))
	   {
		 lilly_db_set_last_error(db_handle,LILLY_DB_SERIALIZE_DATA_ERROR);
		 return 0;
	   }

	   crc = lilly_crc32_serialized_result(&serialized_result,crc);

	   if (!crc)
	   {
		 lilly_db_set_last_error(db_handle,LILLY_DB_UNSPECIFIED_FATAL_ERROR);
		 return 0;
	   }
	 }

	 p = (puchar)&record->email;

	 if (*p != 0)
	 {
	   unsigned_int len = avcore_wstrlen(p) * 2;

	   if (!lilly_is_valid_email_field(p,len))
	   {
		 lilly_db_set_last_error(db_handle,LILLY_DB_SERIALIZE_DATA_ERROR);
		 return 0;
       }

	   crc = lilly_crc32_buffer(p,len,crc);

	   if (!crc)
	   {
		 lilly_db_set_last_error(db_handle,LILLY_DB_UNSPECIFIED_FATAL_ERROR);
		 return 0;
	   }
	 }

	 return crc;
}