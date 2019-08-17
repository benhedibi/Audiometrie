#include <lilly_db.h>
#include <cmnfnc.h>
#include <lilly_utils.h>

/*
	INTERNAL ROUTINES

*/


static void lilly_db_update_time_stamp(const p_lilly_db_time_stamp time_stamp,const uint64 operator_id)
{

	 time_stamp->operator_id = operator_id;

	 lilly_os_get_current_time_stamp(&time_stamp->time_stamp);

	 return;
}

static boolean lilly_db_read_header(const p_lilly_db_handle db_handle)
{
  uint32 crc;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((signed_int)db_handle->io_handle <= 0)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (db_handle->io_size < LILLY_DB_DATABASE_HEADER_SIZE)
	 {
	   db_handle->error_code = LILLY_DB_CORRUPTED_DATABASE_ERROR;
	   return FALSE;
	 }

	 if ((int64)(lilly_io_file_seek(db_handle->io_handle,0,lilly_soFromBeginning)) < 0)
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_file_read(db_handle->io_handle,(puchar)&db_handle->db_header,LILLY_DB_DATABASE_HEADER_SIZE))
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 if (((int64)db_handle->db_header.header_size <= 0) || ((int64)db_handle->db_header.database_size < 0) || ((int64)db_handle->db_header.record_size <= 0) ||
	 ((int64)db_handle->db_header.record_count < 0) || ((int64)db_handle->db_header.deleted_record_count < 0) ||
	 (db_handle->db_header.record_size * db_handle->db_header.record_count != db_handle->db_header.database_size) ||
	 ((db_handle->db_header.record_count) && (db_handle->io_size < db_handle->db_header.header_size + db_handle->db_header.database_size)))
	 {
	   db_handle->error_code = LILLY_DB_TAMPERED_DATABASE_ERROR;
	   return FALSE;
	 }

	 if (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG))
	 {
	   crc = lilly_crc32_buffer((puchar)&db_handle->db_header,FIELD_OFFSET(t_lilly_db_header,header_crc),0);

	   if (!crc)
	   {
		 db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
		 return FALSE;
	   }

	   if (crc != db_handle->db_header.header_crc)
	   {
		 db_handle->error_code = LILLY_DB_TAMPERED_DATABASE_ERROR;
         return FALSE;
	   }
	 }

	 return TRUE;
}

static boolean lilly_db_write_header(const p_lilly_db_handle db_handle,const puchar header_extra_data,const unsigned_int header_extra_data_size)
{
  p_lilly_db_time_stamp time_stamp;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (header_extra_data)
	 {
	   if (((signed_int)header_extra_data_size <= 0) || ((uint64)header_extra_data_size + LILLY_DB_DATABASE_HEADER_SIZE != db_handle->db_header.header_size) ||
	   ((uint64)header_extra_data_size + LILLY_DB_DATABASE_HEADER_SIZE != db_handle->db_cursor.first_record_offset))
	   {
		 db_handle->error_code = API_ERROR;
		 return FALSE;
	   }
	 }

	 if ((int64)(lilly_io_file_seek(db_handle->io_handle,0,lilly_soFromBeginning)) < 0)
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 if (!db_handle->db_header.creation_stamp.time_stamp.year)
	 {
	   time_stamp = &db_handle->db_header.creation_stamp;
	 }
	 else time_stamp = &db_handle->db_header.modification_stamp;

	 lilly_db_update_time_stamp(time_stamp,db_handle->operator_id);

	 if (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG))
	 {
	   db_handle->db_header.header_crc = lilly_crc32_buffer((puchar)&db_handle->db_header,FIELD_OFFSET(t_lilly_db_header,header_crc),0);

	   if (!db_handle->db_header.header_crc)
	   {
		 db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
		 return FALSE;
	   }
	 }

	 if (!lilly_io_file_write(db_handle->io_handle,(puchar)&db_handle->db_header,LILLY_DB_DATABASE_HEADER_SIZE))
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 if (header_extra_data)
	 {
	   if (!lilly_io_file_write(db_handle->io_handle,header_extra_data,header_extra_data_size))
	   {
		 db_handle->error_code = IO_ERROR;
		 return FALSE;
	   }
	 }

	 return TRUE;
}

static boolean set_record_offset(const p_lilly_db_handle db_handle,const uint64 record_offset)
{

	 if (((int64)record_offset < db_handle->db_cursor.first_record_offset) || (record_offset > db_handle->db_cursor.last_record_offset + db_handle->db_header.record_size))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (lilly_io_file_seek(db_handle->io_handle,record_offset,lilly_soFromBeginning) != record_offset)
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 return TRUE;
}

static uint32 lilly_db_get_record_crc(const p_lilly_db_handle db_handle,const puchar record_buffer)
{
  unsigned_int crc_size;
  uint32 crc;


	 crc = lilly_crc32_buffer(record_buffer,FIELD_OFFSET(t_lilly_db_record_header,record_crc),0);

	 if (!crc)
	 {
	   db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
	   return 0;
	 }

	 crc = lilly_crc32_buffer(record_buffer + FIELD_OFFSET(t_lilly_db_record_header,record_crc) + sizeof(((p_lilly_db_record_header)record_buffer)->record_crc),
	 db_handle->db_header.record_size - FIELD_OFFSET(t_lilly_db_record_header,record_crc) + sizeof(((p_lilly_db_record_header)record_buffer)->record_crc),crc);

	 if (!crc)
	 {
	   db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
     }

	 return crc;
}

static boolean lilly_db_read_record_ex(const p_lilly_db_handle db_handle,const p_lilly_db_record_header record,const uint64 record_offset)
{

	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (!set_record_offset(db_handle,record_offset)) return FALSE;

	 if (!lilly_io_file_read(db_handle->io_handle,(puchar)record,db_handle->db_header.record_size))
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 db_handle->db_cursor.last_processed_offset = record_offset;

     if (record->offset != record_offset)
	 {
	   db_handle->error_code = LILLY_DB_CORRUPTED_DATABASE_ERROR;
	   return FALSE;
	 }

	 if (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG))
	 {
	   uint32 crc = lilly_db_get_record_crc(db_handle,(puchar)record);

	   if (!crc) return FALSE;

	   if (crc != record->record_crc)
	   {
		 db_handle->error_code = LILLY_DB_TAMPERED_DATABASE_ERROR;
		 return FALSE;
       }
	 }

	 return TRUE;
}

static boolean lilly_db_write_record_ex(const p_lilly_db_handle db_handle,const p_lilly_db_record_header record,const uint64 record_offset)
{
  p_lilly_db_time_stamp time_stamp;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (!set_record_offset(db_handle,record_offset)) return FALSE;

	 if (!record->creation_time.time_stamp.year)
	 {
	   time_stamp = &record->creation_time;
	 }
	 else time_stamp = &record->last_modification_time;

	 lilly_db_update_time_stamp(time_stamp,db_handle->operator_id);

	 record->offset = record_offset;

	 if (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG))
	 {
	   record->record_crc = lilly_db_get_record_crc(db_handle,(puchar)record);

       if (!record->record_crc) return FALSE;
	 }

	 if (!lilly_io_file_write(db_handle->io_handle,(puchar)record,db_handle->db_header.record_size))
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 db_handle->db_cursor.last_processed_offset = record_offset;

	 return TRUE;
}

static puchar lilly_db_get_first_record_ex(const p_lilly_db_handle db_handle)
{

	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((signed_int)db_handle->io_handle <= 0)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 if (lilly_db_read_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,db_handle->db_cursor.first_record_offset))
	 {
	   db_handle->db_cursor.current_record_offset = db_handle->db_cursor.first_record_offset + db_handle->db_header.record_size;
	   if (set_record_offset(db_handle,db_handle->db_cursor.current_record_offset)) return db_handle->db_cursor.current_record_data;
	 }

	 return NULL;
}

static puchar lilly_db_get_next_record_ex(const p_lilly_db_handle db_handle)
{

	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((signed_int)db_handle->io_handle <= 0)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 if (db_handle->db_cursor.current_record_offset > db_handle->db_cursor.last_record_offset) return NULL;

	 if (!lilly_db_read_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,db_handle->db_cursor.current_record_offset)) return NULL;

	 db_handle->db_cursor.current_record_offset += db_handle->db_header.record_size;

	 if (!set_record_offset(db_handle,db_handle->db_cursor.current_record_offset)) return NULL;

	 return db_handle->db_cursor.current_record_data;
}

static puchar lilly_db_get_previous_record_ex(const p_lilly_db_handle db_handle)
{
  puchar record;


	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((signed_int)db_handle->io_handle <= 0)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 if ((int64)db_handle->db_cursor.current_record_offset < db_handle->db_cursor.first_record_offset) return NULL;

	 if (!lilly_db_read_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,db_handle->db_cursor.current_record_offset)) return NULL;

	 db_handle->db_cursor.current_record_offset -= db_handle->db_header.record_size;

	 if (!set_record_offset(db_handle,db_handle->db_cursor.current_record_offset)) return NULL;

	 return db_handle->db_cursor.current_record_data;
}

static puchar lilly_db_get_last_record_ex(const p_lilly_db_handle db_handle)
{

	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((signed_int)db_handle->io_handle <= 0)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 if (lilly_db_read_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,db_handle->db_cursor.last_record_offset))
	 {
	   db_handle->db_cursor.current_record_offset = db_handle->db_cursor.last_record_offset + db_handle->db_header.record_size;
	   if (set_record_offset(db_handle,db_handle->db_cursor.current_record_offset)) return db_handle->db_cursor.current_record_data;
	 }

	 return NULL;
}


/*

	END OF INTERNAL ROUTINES

*/

p_lilly_db_handle lilly_db_create_db_handle(const puchar db_path,const unsigned_int db_path_len,const uint64 record_size,const uint64 header_size,const uint32 operator_id,const uint32 session_id,const uint64 db_signature,const uint64 db_flags,const punsigned_int error_code)
{
  p_lilly_db_handle handle = NULL;


	 if (!error_code) return handle;

	 *error_code = ERROR_SUCCESS;

	 if ((!db_path) || ((signed_int)db_path_len <= 0) || (db_path_len > sizeof(handle->db_path) - 2) || ((int64)record_size <= 0))
	 {
	   *error_code = API_ERROR;
	   return handle;
	 }
	 else if (lilly_io_file_exists(db_path))
	 {
	   *error_code = LILLY_DB_IO_FILE_EXISTS_ERROR;
       return handle;
	 }

	 handle = (p_lilly_db_handle)lilly_malloc(sizeof(*handle));

	 if (!handle)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   return handle;
	 }

	 avcore_memset(handle,0,sizeof(t_lilly_db_handle));

	 handle->io_handle = lilly_io_create_file(db_path);

	 if ((signed_int)handle->io_handle <= 0)
	 {
	   *error_code = IO_ERROR;
	   goto failure;
	 }

	 handle->operator_id = operator_id;

	 handle->io_size = header_size;

	 handle->db_cursor.current_record_data = (puchar)lilly_malloc(record_size + LILLY_DB_RECORD_HEADER_SIZE);

	 if (!handle->db_cursor.current_record_data)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   goto failure;
	 }

	 handle->db_header.signature = db_signature;
	 handle->db_header.header_size = header_size;
	 handle->db_header.record_size = record_size + LILLY_DB_RECORD_HEADER_SIZE;
	 handle->db_header.flags = db_flags;
	 handle->db_header.session_id = session_id;

	 SET_ATTRIBUTE(handle->db_header.flags,LILLY_DB_CRASH_STATE_FLAG);

	 if (!lilly_db_write_header(handle,NULL,0)) goto failure;

	 handle->db_cursor.current_record_offset = header_size;
	 handle->db_cursor.first_record_offset = header_size;
	 handle->db_cursor.last_record_offset = header_size;

	 handle->db_path_len = db_path_len;

	 avcore_memcpy(&handle->db_path,db_path,db_path_len);

	 goto fin;

	 failure :

	 lilly_db_close_db_handle(handle);

	 handle = NULL;

	 fin :

	 return handle;
}

p_lilly_db_handle lilly_db_open_db_handle(const puchar db_path,const unsigned_int db_path_len,const uint64 db_signature,const uint64 operator_id,const punsigned_int error_code)
{
  p_lilly_db_handle handle = NULL;


	 if (!error_code) return handle;

	 *error_code = ERROR_SUCCESS;

	 if ((!db_path) || ((signed_int)db_path_len <= 0) || (db_path_len > sizeof(handle->db_path) - 2))
	 {
	   *error_code = API_ERROR;
	   return NULL;
	 }
	 else if (!lilly_io_file_exists(db_path))
	 {
	   *error_code = LILLY_DB_IO_FILE_EXISTS_ERROR;
	   return NULL;
	 }

	 handle = (p_lilly_db_handle)lilly_malloc(sizeof(*handle));

	 if (!handle)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   return NULL;
	 }

	 avcore_memset(handle,0,sizeof(*handle));

	 handle->io_handle = lilly_io_open_file(db_path,lilly_io_fmOpen,lilly_io_faReadWrite);

	 if ((signed_int)handle->io_handle <= 0)
	 {
	   *error_code = IO_ERROR;
	   return NULL;
	 }

	 handle->io_size = lilly_io_get_file_size_ex(handle->io_handle);

	 if ((int64)handle->io_size <= 0)
	 {
	   *error_code = IO_ERROR;
	   goto failure;
	 }

	 handle->operator_id = operator_id;

	 if (!lilly_db_read_header(handle))
	 {
	   *error_code = handle->error_code;
	   goto failure;
	 }

	 if (handle->db_header.signature != db_signature)
	 {
	   *error_code = LILLY_DB_SIGNATURE_ERROR;
	   goto failure;
	 }

	 if ((CHECK_ATTRIBUTE(handle->db_header.flags,LILLY_DB_HDR_POWER_USER_ONLY_FLAG)) && (operator_id != LILLY_DB_SUPER_USER_ID))
	 {
	   *error_code = LILLY_DB_USER_PRIVILEGE_ERROR;
	   goto failure;
	 }

	 handle->db_cursor.current_record_data = (puchar)lilly_malloc((unsigned_int)handle->db_header.record_size);

	 if (!handle->db_cursor.current_record_data)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   goto failure;
	 }

	 avcore_memset(handle->db_cursor.current_record_data,0,(unsigned_int)handle->db_header.record_size);

	 if (handle->db_header.header_size > LILLY_DB_DATABASE_HEADER_SIZE)
	 {
	   handle->header_extra_data_offset = LILLY_DB_DATABASE_HEADER_SIZE;
	   handle->header_extra_data_size = handle->db_header.header_size - LILLY_DB_DATABASE_HEADER_SIZE;
	 }

	 handle->db_path_len = db_path_len;

	 avcore_memcpy((puchar)&handle->db_path[0],db_path,db_path_len);

	 handle->db_cursor.first_record_offset = handle->db_header.header_size;
	 handle->db_cursor.current_record_offset = handle->db_cursor.first_record_offset;

	 if (handle->db_header.record_count)
	 {
	   handle->db_cursor.last_record_offset = (handle->db_header.header_size + handle->db_header.database_size) - handle->db_header.record_size;
	 }
	 else handle->db_cursor.last_record_offset = handle->db_cursor.current_record_offset;

	 return handle;

	 failure :

	 lilly_db_close_db_handle(handle);

	 return NULL;
}

void lilly_db_close_db_handle(const p_lilly_db_handle db_handle)
{

	 if (!db_handle) return;

	 if ((signed_int)db_handle->io_handle > 0)
	 {
	   lilly_io_close_file(db_handle->io_handle);
	 }

	 if (db_handle->db_cursor.current_record_data)
	 {
	   lilly_free(db_handle->db_cursor.current_record_data,db_handle->db_header.record_size);
	 }

	 avcore_memset(db_handle,0,sizeof(*db_handle));

	 lilly_free(db_handle,sizeof(*db_handle));

     return;
}

boolean lilly_db_purge_database(const p_lilly_db_handle db_handle)
{
  puchar extra_data;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((signed_int)db_handle->io_handle < 0)
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 extra_data = NULL;

	 if (db_handle->header_extra_data_offset)
	 {
	   if ((int64)lilly_io_file_seek(db_handle->io_handle,db_handle->header_extra_data_offset,lilly_soFromBeginning) <= 0)
	   {
		 db_handle->error_code = IO_ERROR;
		 return FALSE;
	   }

	   extra_data = (puchar)lilly_malloc(db_handle->header_extra_data_size);

	   if (!extra_data)
	   {
		 db_handle->error_code = MEM_ALLOC_ERROR;
		 return FALSE;
	   }

	   if (!lilly_io_file_read(db_handle->io_handle,extra_data,db_handle->header_extra_data_size))
	   {
		 db_handle->error_code = IO_ERROR;
		 lilly_free(extra_data,db_handle->header_extra_data_size);
		 return FALSE;
       }
	 }

	 lilly_io_close_file(db_handle->io_handle);

	 db_handle->io_handle = 0;

	 if (!lilly_io_delete_file(db_handle->db_path))
	 {
	   db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;

	   if (extra_data)
	   {
		 lilly_free(extra_data,db_handle->header_extra_data_size);
	   }

	   return FALSE;
	 }

	 db_handle->io_handle = lilly_io_create_file(db_handle->db_path);

	 if ((int64)db_handle->io_handle <= 0)
	 {
	   db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;

       if (extra_data)
	   {
		 lilly_free(extra_data,db_handle->header_extra_data_size);
	   }

	   return FALSE;
	 }

	 db_handle->io_size = db_handle->db_header.header_size;

	 db_handle->db_header.database_size = 0;

	 lilly_db_update_time_stamp(&db_handle->db_header.modification_stamp,db_handle->operator_id);

	 db_handle->db_header.record_count = 0;
	 db_handle->db_header.deleted_record_count = 0;

	 if (!lilly_db_write_header(db_handle,extra_data,db_handle->header_extra_data_size))
	 {
       db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;

       if (extra_data)
	   {
		 lilly_free(extra_data,db_handle->header_extra_data_size);
	   }

	   return FALSE;
     }

	 db_handle->db_cursor.current_record_offset = db_handle->db_header.header_size;
	 db_handle->db_cursor.first_record_offset = db_handle->db_header.header_size;
	 db_handle->db_cursor.last_record_offset = db_handle->db_header.header_size;

	 return TRUE;
}

boolean lilly_db_export_database(const p_lilly_db_handle db_handle,const puchar target_path)
{
	return FALSE;
}

// ajouter 2 fonctions pour lire et ecrire dans l'extra header space


puchar lilly_db_read_record(const p_lilly_db_handle db_handle,const unsigned_int record_data_size,const uint64 record_offset)
{

	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

     if (((uint64)record_data_size + LILLY_DB_RECORD_HEADER_SIZE != db_handle->db_header.record_size) || ((int64)record_offset <= 0))
	 {
	   db_handle->error_code = API_ERROR;
	   return NULL;
	 }

	 if (!lilly_db_read_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,record_offset)) return NULL;

	 return (db_handle->db_cursor.current_record_data + LILLY_DB_RECORD_HEADER_SIZE);

}

boolean lilly_db_write_record(const p_lilly_db_handle db_handle,const puchar data,const unsigned_int data_size,const uint64 record_offset)
{

	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if ((!data) || ((signed_int)data_size <= 0) || ((uint64)data_size + LILLY_DB_RECORD_HEADER_SIZE != db_handle->db_header.record_size) || ((int64)record_offset < 0))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 avcore_memcpy(db_handle->db_cursor.current_record_data + LILLY_DB_RECORD_HEADER_SIZE,data,data_size);

	 return ((lilly_db_write_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,record_offset)) &&
	 (lilly_db_write_header(db_handle,NULL,0)));

}

puchar lilly_db_get_first_record(const p_lilly_db_handle db_handle)
{
  puchar record;


	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 record = lilly_db_get_first_record_ex(db_handle);

	 if (!record) return NULL;

	 while (TRUE)
	 {
	   if (!CHECK_ATTRIBUTE(((p_lilly_db_record_header)record)->record_flags,LILLY_DB_RECORD_DELETION_FLAG)) break;

	   record = lilly_db_get_next_record(db_handle);

	   if (!record) break;
	 }

	 if (record)
	 {
	   record += LILLY_DB_RECORD_HEADER_SIZE;
	 }

	 return record;
}

puchar lilly_db_get_next_record(const p_lilly_db_handle db_handle)
{
  puchar record;


	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 while (TRUE)
	 {
	   record = lilly_db_get_next_record_ex(db_handle);

	   if (!record) break;

	   if (!CHECK_ATTRIBUTE(((p_lilly_db_record_header)record)->record_flags,LILLY_DB_RECORD_DELETION_FLAG)) break;
	 }

	 if (record)
	 {
	   record += LILLY_DB_RECORD_HEADER_SIZE;
	 }

	 return record;
}

puchar lilly_db_get_previous_record(const p_lilly_db_handle db_handle)
{
  puchar record;


     if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 while (TRUE)
	 {
	   record = lilly_db_get_previous_record_ex(db_handle);

	   if (!record) break;

	   if (!CHECK_ATTRIBUTE(((p_lilly_db_record_header)record)->record_flags,LILLY_DB_RECORD_DELETION_FLAG)) break;
	 }

	 if (record)
	 {
	   record += LILLY_DB_RECORD_HEADER_SIZE;
	 }

	 return record;
}

puchar lilly_db_get_last_record(const p_lilly_db_handle db_handle)
{
  puchar record;


	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return NULL;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return NULL;
	 }

	 record = lilly_db_get_last_record_ex(db_handle);

	 if (!record) return NULL;

	 if (!CHECK_ATTRIBUTE(((p_lilly_db_record_header)record)->record_flags,LILLY_DB_RECORD_DELETION_FLAG))
	 {
	   record += LILLY_DB_RECORD_HEADER_SIZE;
	 }
	 else record = lilly_db_get_previous_record(db_handle);

	 return record;
	 
}

boolean lilly_db_append_record(const p_lilly_db_handle db_handle,const puchar record,const unsigned_int record_size)
{

	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((!record) || ((signed_int)record_size <= 0))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (db_handle->db_header.record_count)
	 {
	   db_handle->db_cursor.last_record_offset += db_handle->db_header.record_size;
	 }

	 db_handle->db_cursor.current_record_offset = db_handle->db_cursor.last_record_offset;

	 if (!lilly_db_write_record(db_handle,record,record_size,db_handle->db_cursor.last_record_offset)) return FALSE;

	 db_handle->io_size += db_handle->db_header.record_size;

	 db_handle->db_header.database_size += db_handle->db_header.record_size;

	 db_handle->db_header.record_count++;

	 return lilly_db_write_header(db_handle,NULL,0);

}

boolean lilly_db_edit_record(const p_lilly_db_handle db_handle,const puchar record,const unsigned_int record_size,const uint64 record_offset)
{

	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((!record) || ((signed_int)record_size <= 0))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

     if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return FALSE;
	 }

	 return ((lilly_db_write_record(db_handle,record,record_size,record_offset)) && (lilly_db_write_header(db_handle,NULL,0)));
}

boolean lilly_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset)
{
  p_lilly_db_record_header record;


	 if (!db_handle) return FALSE;

	 if ((int64)record_offset <= 0)
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

     if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return FALSE;
	 }

	 record = (p_lilly_db_record_header)db_handle->db_cursor.current_record_data;

	 if (!lilly_db_read_record_ex(db_handle,record,record_offset)) return FALSE;

     SET_ATTRIBUTE(record->record_flags,LILLY_DB_RECORD_DELETION_FLAG);

	 if (!lilly_db_write_record_ex(db_handle,record,record_offset)) return FALSE;

	 db_handle->db_header.database_size -= db_handle->db_header.record_size;

	 db_handle->db_header.record_count--;

	 db_handle->db_header.deleted_record_count++;

	 return lilly_db_write_header(db_handle,NULL,0);

}

uint64 lilly_db_get_current_record_offset(const p_lilly_db_handle db_handle)
{

	 if (!db_handle) return IO_ERROR;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data) || (!db_handle->db_cursor.current_record_offset))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return IO_ERROR;
	 }

	 return db_handle->db_cursor.last_processed_offset;
}

boolean lilly_db_set_current_record_offset(const p_lilly_db_handle db_handle,const uint64 offset)
{

	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((int64)offset <= 0) || (offset < db_handle->db_cursor.first_record_offset) || (offset > db_handle->db_cursor.last_record_offset))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 if (((signed_int)db_handle->io_handle <= 0) || (!db_handle->db_cursor.current_record_data) || (!db_handle->db_cursor.current_record_offset))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 db_handle->db_cursor.current_record_offset = lilly_io_file_seek(db_handle->io_handle,offset,lilly_soFromBeginning);

	 if ((int64)db_handle->db_cursor.current_record_offset < 0)
	 {
	   db_handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 db_handle->db_cursor.last_processed_offset = offset;

	 return TRUE;

}

boolean lilly_db_get_record_time_stamp_infos(const p_lilly_db_handle db_handle,const uint64 record_offset,const p_lilly_db_time_stamp_informations time_stamp_infos)
{


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((int64)record_offset <= 0) || (!time_stamp_infos))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 if (!lilly_db_read_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,record_offset)) return FALSE;

	 // aussi dangereux que la mort, mais je laisse le compilateur générer le meilleur code possible

	 *time_stamp_infos = *(p_lilly_db_time_stamp_informations)(&((p_lilly_db_record_header)db_handle->db_cursor.current_record_data)->creation_time);

	 return TRUE;
}

boolean lilly_db_set_record_creation_time(const p_lilly_db_handle db_handle,const uint64 record_offset,const p_date_time new_date)
{
  p_lilly_db_record_header record;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((int64)record_offset <= 0) || (!new_date))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 record = (p_lilly_db_record_header)db_handle->db_cursor.current_record_data;

	 if (!lilly_db_read_record_ex(db_handle,record,record_offset)) return FALSE;

	 *(p_date_time)&record->creation_time.time_stamp = *new_date;

	 return lilly_db_write_record_ex(db_handle,record,record_offset);

}

uint32 lilly_db_get_record_crc32(const p_lilly_db_handle db_handle,const uint64 record_offset)
{
  p_lilly_db_record_header record;


	 if (!db_handle) return 0;

	 db_handle->error_code = ERROR_SUCCESS;

	 if ((int64)record_offset <= 0)
	 {
	   db_handle->error_code = API_ERROR;
	   return 0;
	 }

	 if (!lilly_db_read_record_ex(db_handle,(p_lilly_db_record_header)db_handle->db_cursor.current_record_data,record_offset)) return FALSE;

	 return ((p_lilly_db_record_header)db_handle->db_cursor.current_record_data)->record_crc;
}

unsigned_int lilly_db_get_last_error(const p_lilly_db_handle db_handle)
{
	if (db_handle) return db_handle->error_code;
	else return IO_ERROR;
}

void lilly_db_set_last_error(const p_lilly_db_handle db_handle,const unsigned_int error_code)
{
	if (db_handle)
	{
	  db_handle->error_code = error_code;
	}

	return;
}

typedef struct {
				 uint64 signature;
				 uint64 data_size;
				 t_lilly_db_time_stamp_informations time_stamp_infos;
				 uint32 session_id;
				 uint32 crc32;
			   } t_blob_header,*p_blob_header;


puchar lilly_db_get_blob_db_path(const p_lilly_db_handle db_handle,const punsigned_int blob_path_len)
{

	if (!db_handle) return NULL;

	db_handle->error_code = ERROR_SUCCESS;

	if (!blob_path_len)
	{
	  db_handle->error_code = API_ERROR;
	  return NULL;
	}

	*blob_path_len = db_handle->blob_path_len;

	return (puchar)&db_handle->blob_folder_path[0];

}

boolean lilly_db_set_blob_db_path(const p_lilly_db_handle db_handle,const puchar blob_db_path,const unsigned_int blob_db_path_len)
{

	if (!db_handle) return FALSE;

	db_handle->error_code = ERROR_SUCCESS;

	if ((!blob_db_path) || ((signed_int)blob_db_path_len <= 0) || (blob_db_path_len > sizeof(db_handle->blob_folder_path) - 2))
	{
	  db_handle->error_code = API_ERROR;
	  return FALSE;
	}

	db_handle->blob_path_len = blob_db_path_len;

	*(puint16)&db_handle->blob_folder_path[blob_db_path_len] = 0;

	avcore_memcpy((puchar)&db_handle->blob_folder_path[0],blob_db_path,blob_db_path_len);

    return TRUE;
}

#define LILLY_DB_BLOB_SIGNATURE 0x00626F6C625F6170

static boolean build_blob_file_path(const puchar blob_db_folder_path,const unsigned_int blob_db_folder_path_len,const puchar blob_result_file_path,const unsigned_int max_path_len,const uint32 blob_id)
{
  t_int_to_hexbuffer hexbuff;


	avcore_memcpy(blob_result_file_path,blob_db_folder_path,blob_db_folder_path_len);

	blob_result_file_path[blob_db_folder_path_len] = IO_FOLDER_SEPARATOR;
	blob_result_file_path[blob_db_folder_path_len + 1] = 0;

	avcore_witoh((unsigned_int)blob_id,&hexbuff);

	unsigned_int len = avcore_wstrlen((puchar)&hexbuff) * 2;

	if (!len) return FALSE;

	if (blob_db_folder_path_len + 2 + len > max_path_len - 2) return FALSE;

	*(puint16)&blob_result_file_path[blob_db_folder_path_len + 2 + len] = 0;

	avcore_memcpy(&blob_result_file_path[blob_db_folder_path_len + 2],&hexbuff,len);

    return TRUE;
}

uint32 lilly_db_create_blob(const p_lilly_db_handle db_handle,const puchar data,const unsigned_int data_size,const uint32 operator_id)
{
  unsigned_int fhandle;
  t_blob_header blob_hdr;
  uchar blob_path[260 * 2];


	if (!db_handle) return 0;

	db_handle->error_code = ERROR_SUCCESS;

	if ((!data) || ((signed_int)data_size <= 0))
	{
	  db_handle->error_code = API_ERROR;
	  return 0;
	}

	avcore_memset(&blob_hdr,0,sizeof(blob_hdr));

	blob_hdr.signature = LILLY_DB_BLOB_SIGNATURE;
	blob_hdr.data_size = data_size;

	lilly_db_update_time_stamp(&blob_hdr.time_stamp_infos.creation_stamp,(uint64)operator_id);

	blob_hdr.session_id = db_handle->db_header.session_id;

	blob_hdr.crc32 = lilly_crc32_buffer((puchar)&blob_hdr,FIELD_OFFSET(t_blob_header,crc32),0);

	if (!blob_hdr.crc32)
	{
	  db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
	  return 0;
	}

	if (!build_blob_file_path((puchar)&db_handle->blob_folder_path,db_handle->blob_path_len,(puchar)&blob_path,sizeof(blob_path),blob_hdr.crc32))
	{
	  db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
	  return 0;
	}

	fhandle = lilly_io_create_file((puchar)&blob_path);

	if ((signed_int)fhandle <= 0)
	{
	  db_handle->error_code = IO_ERROR;
	  return 0;
	}

	if (!lilly_io_file_write(fhandle,(puchar)&blob_hdr,sizeof(blob_hdr)))
	{
	  lilly_io_close_file(fhandle);
	  db_handle->error_code = IO_ERROR;
	  lilly_io_delete_file((puchar)&blob_path);
	  return 0;
	}

	if (!lilly_io_file_write(fhandle,data,data_size))
	{
	  lilly_io_close_file(fhandle);
	  db_handle->error_code = IO_ERROR;
	  lilly_io_delete_file((puchar)&blob_path);
	  return 0;
	}

	lilly_io_close_file(fhandle);

	return blob_hdr.crc32;

}

typedef struct t_lilly_db_blob_handle {
										unsigned_int error_code;
										unsigned_int io_handle;
										uint64 io_size;
										t_blob_header header;
										uchar blob_file_path[260];
									  } *p_lilly_db_blob_handle;


p_lilly_db_blob_handle lilly_db_open_blob(const p_lilly_db_handle db_handle,const uint32 blob_id)
{
  p_lilly_db_blob_handle blob_handle;


	if (!db_handle) return NULL;

	db_handle->error_code = ERROR_SUCCESS;

	if ((!blob_id) || (!db_handle->blob_path_len))
	{
	  db_handle->error_code = API_ERROR;
	  return NULL;
	}

    blob_handle = (p_lilly_db_blob_handle)lilly_malloc(sizeof(*blob_handle));

	if (!blob_handle)
	{
	  db_handle->error_code = MEM_ALLOC_ERROR;
	  return NULL;
	}

	avcore_memset(blob_handle,0,sizeof(*blob_handle));

	if (!build_blob_file_path((puchar)&db_handle->blob_folder_path,db_handle->blob_path_len,(puchar)&blob_handle->blob_file_path,sizeof(blob_handle->blob_file_path),blob_id))
	{
	  db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
	  lilly_free(blob_handle,sizeof(*blob_handle));
	  return NULL;
	}

	if (!lilly_io_file_exists((puchar)&blob_handle->blob_file_path))
	{
	  db_handle->error_code = IO_ERROR;
      lilly_free(blob_handle,sizeof(*blob_handle));
	  return NULL;
	}

	blob_handle->io_handle = lilly_io_open_file((puchar)&blob_handle->blob_file_path,lilly_io_fmOpen,lilly_io_faReadWrite);

	if ((signed_int)blob_handle->io_handle <= 0)
	{
	  db_handle->error_code = IO_ERROR;
	  lilly_free(blob_handle,sizeof(*blob_handle));
	  return NULL;
	}

	blob_handle->io_size = lilly_io_get_file_size_ex(blob_handle->io_handle);

	if ((int64)blob_handle->io_size <= sizeof(blob_handle->header))
	{
	  db_handle->error_code = LILLY_DB_MALFORMED_BLOB_ERROR;
	  lilly_io_close_file(blob_handle->io_handle);
	  lilly_free(blob_handle,sizeof(*blob_handle));
	  return NULL;
	}

	if (!lilly_io_file_read(blob_handle->io_handle,(puchar)&blob_handle->header,sizeof(blob_handle->header)))
	{
	  db_handle->error_code = IO_ERROR;
	  lilly_io_close_file(blob_handle->io_handle);
	  lilly_free(blob_handle,sizeof(*blob_handle));
	  return NULL;
	}

	if ((blob_handle->header.signature != LILLY_DB_BLOB_SIGNATURE) || (blob_handle->header.data_size != blob_handle->io_size - sizeof(blob_handle->header)))
	{
	  db_handle->error_code = LILLY_DB_MALFORMED_BLOB_ERROR;
	  lilly_io_close_file(blob_handle->io_handle);
	  lilly_free(blob_handle,sizeof(*blob_handle));
	  return NULL;
	}

	if ((CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_SESSION_ID_LOCK_FLAG)) && (db_handle->db_header.session_id != blob_handle->header.session_id))
	{
	  db_handle->error_code = LILLY_DB_SESSION_MISMATCH_ERROR;
	  lilly_io_close_file(blob_handle->io_handle);
	  lilly_free(blob_handle,sizeof(*blob_handle));
	  return NULL;
	}

	return blob_handle;
}

uint64 lilly_db_get_blob_data_size(p_lilly_db_blob_handle blob_handle)
{

	if (!blob_handle) return IO_ERROR;

	return blob_handle->header.data_size;
}

unsigned_int lilly_db_get_blob_last_error(p_lilly_db_blob_handle blob_handle)
{

	if (!blob_handle) return API_ERROR;
    else return blob_handle->error_code;
}

boolean lilly_db_delete_blob(const p_lilly_db_handle db_handle,const uint32 blob_id)
{
  uchar blob_path[260 * 2];


	if (!db_handle) return FALSE;

	if (!blob_id)
	{
	  db_handle->error_code = API_ERROR;
	  return FALSE;
	}

	db_handle->error_code = ERROR_SUCCESS;

	if (!build_blob_file_path((puchar)&db_handle->blob_folder_path,db_handle->blob_path_len,(puchar)&blob_path,sizeof(blob_path),blob_id))
	{
	  db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
	  return FALSE;
	}

	if (!lilly_io_file_exists((puchar)&blob_path)) return TRUE;

	if (!lilly_io_delete_file((puchar)&blob_path))
	{
	  db_handle->error_code = IO_ERROR;
	  return FALSE;
	}

	return TRUE;

}

boolean lilly_db_read_blob(const p_lilly_db_blob_handle blob_handle,const puchar data,const unsigned_int data_size)
{

	if (!blob_handle) return FALSE;

	blob_handle->error_code = ERROR_SUCCESS;

	if ((!data) || ((signed_int)data_size <= 0))
	{
	  blob_handle->error_code = API_ERROR;
	  return FALSE;
	}

	if (!blob_handle->header.data_size) return false;
	else if (blob_handle->header.data_size != (uint64)data_size)
	{
	  blob_handle->error_code = API_ERROR;
	  return FALSE;
	}

	if ((lilly_io_file_seek(blob_handle->io_handle,sizeof(blob_handle->header),lilly_soFromBeginning) != 0) && (!lilly_io_file_read(blob_handle->io_handle,data,data_size)))
	{
	  blob_handle->error_code = IO_ERROR;
	  return FALSE;
	}

	return TRUE;
}

boolean lilly_db_write_blob(const p_lilly_db_blob_handle blob_handle,const puchar data,const unsigned_int data_size,const uint32 operator_id)
{


	if (!blob_handle) return FALSE;

	blob_handle->error_code = ERROR_SUCCESS;

	if ((!data) || ((signed_int)data_size <= 0))
	{
	  blob_handle->error_code = API_ERROR;
	  return FALSE;
	}

	lilly_db_update_time_stamp(&blob_handle->header.time_stamp_infos.modification_stamp,operator_id);

	if ((uint64)data_size < blob_handle->header.data_size)
	{
	  lilly_io_close_file(blob_handle->io_handle);

	  if (!lilly_io_delete_file((puchar)&blob_handle->blob_file_path))
	  {
		blob_handle->error_code = IO_ERROR;
		return FALSE;
	  }

	  blob_handle->io_handle = lilly_io_create_file((puchar)&blob_handle->blob_file_path);

	  if ((signed_int)blob_handle->io_handle <= 0)
	  {
		blob_handle->error_code = IO_ERROR;
		return FALSE;
	  }

	  blob_handle->header.data_size = (uint64)data_size;

	  if ((!lilly_io_file_write(blob_handle->io_handle,(puchar)&blob_handle->header,sizeof(blob_handle->header))) || (!lilly_io_file_write(blob_handle->io_handle,data,data_size)))
	  {
		blob_handle->error_code = IO_ERROR;
		return FALSE;
	  }

	  return TRUE;
	}

	blob_handle->header.data_size = (uint64)data_size;

	if ((lilly_io_file_seek(blob_handle->io_handle,0,lilly_soFromBeginning) != 0) && (!lilly_io_file_write(blob_handle->io_handle,(puchar)&blob_handle->header,sizeof(blob_handle->header))))
	{
	  blob_handle->error_code = IO_ERROR;
	  return FALSE;
	}

	if (!lilly_io_file_write(blob_handle->io_handle,data,data_size))
	{
	  blob_handle->error_code = IO_ERROR;
	  return FALSE;
	}

	return TRUE;
}

void lilly_db_close_blob(const p_lilly_db_blob_handle blob_handle)
{

	if (blob_handle)
	{
	  if (blob_handle->io_handle)
	  {
		lilly_io_close_file(blob_handle->io_handle);
		blob_handle->io_handle = 0;
	  }
	  lilly_free(blob_handle,sizeof(*blob_handle));
	}

	return;
}

