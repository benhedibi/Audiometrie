#include <tympano_engine.h>

#include <lilly_session_manager.h>
#include <lilly_mem.h>
#include <lilly_utils.h>
#include <lilly_os.h>

#include <db_signatures.h>

#include <cmnfnc.h>

static boolean LILLY_CALL_CONVENTION build_indexes(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle)
{
  p_tympanogram_record iterator;
  uint64 offset;


	 if (!self) return FALSE;

	 self->error_code = ERROR_SUCCESS;

	 iterator = (p_tympanogram_record)lilly_db_get_first_record(db_handle);

	 if (!iterator)
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return NULL;
	 }

	 while (TRUE)
	 {
	   if (!lilly_db_add_index(db_handle,iterator->code_tympanogram.unique_index,lilly_db_get_current_record_offset(db_handle))) break;

	   iterator = (p_tympanogram_record)lilly_db_get_next_record(db_handle);

	   if (!iterator) break;
	 }

	 self->error_code = lilly_db_get_last_error(db_handle);

	 return (self->error_code == ERROR_SUCCESS);
}

static struct t_lilly_db_handle* LILLY_CALL_CONVENTION new_database(const p_lilly_db_engine self,const puchar database_path,const unsigned_int db_path_len,const uint64 databse_flags,const uint32 operator_id,const uint32 session_id)
{
  struct t_lilly_db_handle* db_handle;


	 self->error_code = ERROR_SUCCESS;

	 db_handle = lilly_db_create_db_handle(database_path,db_path_len,TYMPANOGRAM_RECORD_SIZE,LILLY_DB_DATABASE_HEADER_SIZE,operator_id,session_id,TYMPANOGRAM_DB_SIGNATURE,
	 databse_flags,&self->error_code);

	 if (!db_handle) return NULL;

	 if (self->error_code == LILLY_DB_VIRGIN_INDEX_FILE)
	 {
	   if (!build_indexes(self,db_handle))
	   {
		 lilly_db_close_db_handle(db_handle);
		 db_handle = NULL;
	   }
	 }

	 return db_handle;
}

static struct t_lilly_db_handle* LILLY_CALL_CONVENTION load_database(const p_lilly_db_engine self,const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id)
{
  struct t_lilly_db_handle* db_handle;


	 self->error_code = ERROR_SUCCESS;

	 db_handle = lilly_db_open_db_handle(database_path,db_path_len,TYMPANOGRAM_DB_SIGNATURE,operator_id,session_id,&self->error_code);

     if (!db_handle) return NULL;

	 if (self->error_code == LILLY_DB_VIRGIN_INDEX_FILE)
	 {
	   if (!build_indexes(self,db_handle))
	   {
		 lilly_db_close_db_handle(db_handle);
		 db_handle = NULL;
	   }
	 }

	 return db_handle;
}

static void LILLY_CALL_CONVENTION close_database(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle)
{

	 self->error_code = ERROR_SUCCESS;

	 lilly_db_close_db_handle(db_handle);

	 return;
}

static boolean LILLY_CALL_CONVENTION save_database(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const puchar database_path)
{

	 self->error_code = ERROR_SUCCESS;

	 if (!lilly_db_export_database(db_handle,database_path))
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	 }

	 return (self->error_code == ERROR_SUCCESS);
}

static boolean LILLY_CALL_CONVENTION append_record(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const opaque_ptr record_ptr)
{
  p_tympanogram_record record = (p_tympanogram_record)record_ptr;


	 self->error_code = ERROR_SUCCESS;

	 record->code_tympanogram.unique_index = lilly_db_get_unique_autoinc_key(db_handle);

	 if (record->code_tympanogram.unique_index == IO_ERROR)
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return FALSE;
	 }

	 record->code_tympanogram.crc32 = self->get_record_crc(self,db_handle,record);

	 if (!record->code_tympanogram.crc32) return FALSE;

	 if (!lilly_db_append_record(db_handle,(puchar)record,TYMPANOGRAM_RECORD_SIZE))
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return FALSE;
	 }

     if (!lilly_db_add_index(db_handle,record->code_tympanogram.unique_index,lilly_db_get_current_record_offset(db_handle)))
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);

	   if (self->error_code != LILLY_DB_FEATURE_UNAVAILABLE) return FALSE;

	   self->error_code = ERROR_SUCCESS;

	   lilly_db_set_last_error(db_handle,ERROR_SUCCESS);
	 }

	 return TRUE;
}

static boolean LILLY_CALL_CONVENTION edit_record(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const opaque_ptr record_ptr,const uint64 record_offset)
{
  p_tympanogram_record record = (p_tympanogram_record)record_ptr;


	 self->error_code = ERROR_SUCCESS;

	 if (((int64)record_offset <= 0) || (!record->code_tympanogram.crc32))
	 {
	   self->error_code = API_ERROR;
	   return FALSE;
	 }

	 record->code_tympanogram.crc32 = self->get_record_crc(self,db_handle,record);

	 if (!record->code_tympanogram.crc32) return FALSE;

	 if (lilly_db_edit_record(db_handle,(puchar)record,TYMPANOGRAM_RECORD_SIZE,record_offset)) return TRUE;

     self->error_code = lilly_db_get_last_error(db_handle);

	 return FALSE;
}

static boolean LILLY_CALL_CONVENTION delete_record(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const uint64 record_offset)
{
  p_tympanogram_record record;
  uint32 rec_id;


     self->error_code = ERROR_SUCCESS;

	 if ((int64)record_offset <= 0)
	 {
	   self->error_code = API_ERROR;
	   return FALSE;
	 }

	 record = (p_tympanogram_record)lilly_db_read_record(db_handle,TYMPANOGRAM_RECORD_SIZE,record_offset);

	 if (!record)
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return FALSE;
	 }

	 rec_id = record->code_tympanogram.unique_index;

	 if (!lilly_db_delete_record(db_handle,record_offset))
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return FALSE;
	 }

	 if (!lilly_db_del_index(db_handle,rec_id))
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);

	   if (self->error_code != LILLY_DB_FEATURE_UNAVAILABLE) return FALSE;

	   self->error_code = ERROR_SUCCESS;

	   lilly_db_set_last_error(db_handle,ERROR_SUCCESS);
	 }

	 return TRUE;
}

static opaque_ptr LILLY_CALL_CONVENTION get_first_filtered_record(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const opaque_ptr filter_params)
{
     self->error_code = ERROR_NOT_IMPLEMENTED;

	 return NULL;
}

static opaque_ptr LILLY_CALL_CONVENTION get_next_filtered_record(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const opaque_ptr filter_params)
{
     self->error_code = ERROR_NOT_IMPLEMENTED;

	 return NULL;
}

static opaque_ptr LILLY_CALL_CONVENTION code_to_record(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const uint32 rec_code)
{
  p_tympanogram_record iterator;


	 self->error_code = ERROR_SUCCESS;

	 iterator = lilly_db_index_to_record(db_handle,TYMPANOGRAM_RECORD_SIZE,rec_code);

	 if (iterator)
	 {
	   return iterator;
	 }

	 self->error_code = lilly_db_get_last_error(db_handle);

	 if (self->error_code != LILLY_DB_FEATURE_UNAVAILABLE)
	 {
	   return iterator;
	 }

	 self->error_code = ERROR_SUCCESS;

	 lilly_db_set_last_error(db_handle,ERROR_SUCCESS);

	 iterator = (p_tympanogram_record)lilly_db_get_first_record(db_handle);

	 if (!iterator)
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return NULL;
     }

	 while (TRUE)
	 {
	   if (iterator->code_tympanogram.unique_index == rec_code) break;

	   iterator = (p_tympanogram_record)lilly_db_get_next_record(db_handle);

	   if (!iterator) break;
	 }

	 self->error_code = lilly_db_get_last_error(db_handle);

	 return iterator;
}

static uint32 LILLY_CALL_CONVENTION get_record_crc(const p_lilly_db_engine self,const struct t_lilly_db_handle *db_handle,const opaque_ptr record)
{
  uint32 crc;


	 self->error_code = ERROR_SUCCESS;

	 crc = lilly_crc32_buffer((puchar)record,TYMPANOGRAM_RECORD_SIZE,0);

	 if (!crc)
	 {
	   self->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
     }

	 return crc;
}

p_lilly_db_engine LILLY_CALL_CONVENTION get_tympano_db_engine(const opaque_ptr session_manager,const punsigned_int error_code)
{
  p_lilly_db_engine db_engine;


	 if (!error_code) return NULL;

	 *error_code = ERROR_SUCCESS;

	 if (!session_manager)
	 {
	   *error_code = API_ERROR;
	   return NULL;
	 }

	 db_engine = lilly_malloc(sizeof(*db_engine));

	 if (!db_engine)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   return NULL;
	 }

	 db_engine->error_code = ERROR_SUCCESS;

	 db_engine->session_manager = session_manager;

	 db_engine->new_database = (p_lilly_db_new_database)new_database;
	 db_engine->load_database = (p_lilly_db_load_database)load_database;
	 db_engine->close_database = (p_lilly_db_close_database)close_database;
	 db_engine->save_database = (p_lilly_db_save_database)save_database;
	 db_engine->append_record = (p_lilly_db_append_record)append_record;
	 db_engine->edit_record = (p_lilly_db_edit_record)edit_record;
	 db_engine->delete_record = (p_lilly_db_delete_record)delete_record;
	 db_engine->get_first_filtered_record = (p_lilly_db_get_first_filtered_record)get_first_filtered_record;
	 db_engine->get_next_filtered_record = (p_lilly_db_get_next_filtered_record)get_next_filtered_record;
	 db_engine->code_to_record = (p_lilly_db_code_to_record)code_to_record;
	 db_engine->get_record_crc = (p_lilly_db_get_record_crc)get_record_crc;

     return db_engine;
}

void LILLY_CALL_CONVENTION release_tympano_db_engine(const p_lilly_db_engine db_engine)
{

	 if (db_engine)
	 {
	   avcore_memset(db_engine,0,sizeof(*db_engine));
	   lilly_free(db_engine,sizeof(*db_engine));
	 }

	 return;
}