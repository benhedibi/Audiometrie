#include <tympano.h>
#include <db_signatures.h>
#include <cmnfnc.h>
#include <lilly_utils.h>
#include <lilly_os.h>


p_lilly_db_handle tympanogram_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code)
{

	if (!error_code) return NULL;

	 *error_code = ERROR_SUCCESS;

	 return lilly_db_create_db_handle(database_path,db_path_len,TYMPANOGRAM_RECORD_SIZE,LILLY_DB_DATABASE_HEADER_SIZE,operator_id,session_id,TYMPANOGRAM_DB_SIGNATURE,databse_flags,error_code);
}

p_lilly_db_handle tympanogram_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code)
{

	 if (!error_code) return NULL;

	 *error_code = ERROR_SUCCESS;

	 return lilly_db_open_db_handle(database_path,db_path_len,TYMPANOGRAM_DB_SIGNATURE,operator_id,error_code);
}

void tympanogram_db_close_database(const p_lilly_db_handle db_handle)
{

	 lilly_db_close_db_handle(db_handle);

	 return;
}

boolean tympanogram_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path)
{

	 return lilly_db_export_database(db_handle,database_path);

}

static uint32 generate_record_unique_index()
{
  t_date_time date_time;


	 lilly_os_get_current_time_stamp(&date_time);

     return *(puint32)&date_time;  // très dangereux car j'assume que la structure ne changera pas hours,minutes,seconds,day
}

boolean tympanogram_db_append_record(const p_lilly_db_handle db_handle,const p_tympanogram_record record)
{

	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 record->code_tympanogram.crc32 = tympanogram_db_get_record_crc(db_handle,record);

	 if (!record->code_tympanogram.crc32) return FALSE;

	 record->code_tympanogram.unique_index = generate_record_unique_index();

	 return lilly_db_append_record(db_handle,(puchar)record,TYMPANOGRAM_RECORD_SIZE);

}

boolean tympanogram_db_edit_record(const p_lilly_db_handle db_handle,const p_tympanogram_record record,const uint64 record_offset)
{

	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 if ((int64)record_offset <= 0)
	 {
	   lilly_db_set_last_error(db_handle,API_ERROR);
	   return FALSE;
     }

	 return lilly_db_edit_record(db_handle,(puchar)record,TYMPANOGRAM_RECORD_SIZE,record_offset);
}

boolean tympanogram_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset)
{

	 return lilly_db_delete_record(db_handle,record_offset);

}

p_tympanogram_record tympanogram_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params)
{

	 return NULL;

}

p_tympanogram_record tympanogram_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params)
{

	 return NULL;

}

p_tympanogram_record tympanogram_db_codetymp_to_record(const p_lilly_db_handle db_handle,const uint32 codetymp)
{
  p_tympanogram_record iterator;


	 if (!db_handle) return NULL;

	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 iterator = (p_tympanogram_record)lilly_db_get_first_record(db_handle);

	 if (!iterator) return NULL;

	 while (TRUE)
	 {
	   if (iterator->code_tympanogram.unique_index == codetymp) break;

	   iterator = (p_tympanogram_record)lilly_db_get_next_record(db_handle);

	   if (!iterator) break;
	 }

	 return iterator;
}

uint32 tympanogram_db_get_record_crc(const p_lilly_db_handle db_handle,const p_tympanogram_record record)
{
  puchar p;
  uint32 crc = 0;


	 if (!db_handle) return 0;

	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 if (!record)
	 {
	   lilly_db_set_last_error(db_handle,API_ERROR);
	   return 0;
	 }

	 return lilly_crc32_buffer((puchar)record,sizeof(*record),0);
}