#include <lilly_db2.h>
#include <lilly_utils.h>
#include <lilly_io.h>
#include <lilly_io_stream.h>
#include <lilly_os.h>
#include <lilly_mem.h>
#include <cmnfnc.h>


#pragma pack(push,1)


typedef struct {
				 uint32 record_flags;  //4
				 t_lilly_db_time_stamp_informations time_stamp_infos;  // 24
				 uint32 record_crc;    //4
			   } t_lilly_db_record_header,*p_lilly_db_record_header; // taille 32 bytes

typedef struct {
				 uint32 signature;  // 4
				 uint16 header_size; // 2
				 uint16 record_size;  // 2
				 uint64 database_size; // 8
				 uint32 flags;  // 4
				 t_lilly_db_time_stamp_informations time_stamp_infos;  // 24
				 uint32 record_count; // 4
				 uint32 deleted_record_count; // 4
				 uint32 session_id; // les bases de données qui n'ont pas les mêmes session id, ne communiquent pas  // 4
				 uint32 last_key_index; // 4
				 uint32 header_crc;  // 4
			   } t_lilly_db_header,*p_lilly_db_header; // 64 bytes


#define LILLY_DB_RECORD_HEADER_SIZE (sizeof(t_lilly_db_record_header))


typedef struct {
				 uint64 current_record_offset;
				 uint64 first_record_offset;
				 uint64 last_record_offset;
				 uint64 last_processed_offset;
			   } t_lilly_db_cursor,*p_lilly_db_cursor;

typedef struct {
				 puchar data;
				 unsigned_int data_size;
			   } t_lilly_db_blob_buffer,*p_lilly_db_blob_buffer;


typedef struct t_lilly_db_handle {
								   unsigned_int error_code;
								   opaque_ptr io_stream_handle;
                                   uint32 operator_id;
								   uint64 io_size;
								   t_lilly_db_header db_header;
								   t_lilly_db_cursor db_cursor;
								   unsigned_int header_extra_data_offset;
								   unsigned_int header_extra_data_size;
								   unsigned_int lazy_write_mode;
								   unsigned_int db_path_len;
								   unsigned_int blob_path_len;
								   uchar db_path[LILLY_DB_MAX_PATH * 2];
								   uchar blob_folder_path[256 * 2];
								 } *p_lilly_db_handle;


#pragma pack(pop)

#define LILLY_DB_CRASH_STATE_FLAG     (1 << 24) // if present ça veut dire , la base n'a pas été quitté correctement (crash app, coupure courant etc...)

#define LILLY_DB_RECORD_DELETION_FLAG 1



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

	 if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (db_handle->io_size < LILLY_DB_DATABASE_HEADER_SIZE)
	 {
	   db_handle->error_code = LILLY_DB_CORRUPTED_DATABASE_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_strm_read_stream_ex(db_handle->io_stream_handle,(puchar)&db_handle->db_header,LILLY_DB_DATABASE_HEADER_SIZE,0))
	 {
	   db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
	   return FALSE;
	 }

	 if ((!db_handle->db_header.header_size) || ((int64)db_handle->db_header.database_size < 0) || (!db_handle->db_header.record_size) ||
	 ((int32)db_handle->db_header.record_count < 0) || ((int32)db_handle->db_header.deleted_record_count < 0) ||
	 ((uint64)(db_handle->db_header.record_count *db_handle->db_header.record_size) != db_handle->db_header.database_size) ||
	 ((db_handle->db_header.record_count) && (db_handle->io_size < db_handle->db_header.database_size + db_handle->db_header.header_size)))
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

	 if (!db_handle->io_stream_handle)
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

	 if (!db_handle->db_header.time_stamp_infos.creation_stamp.time_stamp.year)
	 {
	   time_stamp = &db_handle->db_header.time_stamp_infos.creation_stamp;
	 }
	 else time_stamp = &db_handle->db_header.time_stamp_infos.modification_stamp;

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

	 if (!db_handle->lazy_write_mode)
	 {
	   if (!lilly_io_strm_write_stream_ex(db_handle->io_stream_handle,(puchar)&db_handle->db_header,LILLY_DB_DATABASE_HEADER_SIZE,0))
	   {
		 db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
		 return FALSE;
	   }

	   if (header_extra_data)
	   {
		 if (!lilly_io_strm_write_stream_ex(db_handle->io_stream_handle,header_extra_data,header_extra_data_size,(unsigned_int)(db_handle->db_header.header_size - LILLY_DB_DATABASE_HEADER_SIZE)))
		 {
		   db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
		   return FALSE;
		 }
	   }
     }

	 return TRUE;
}

static boolean set_record_offset(const p_lilly_db_handle db_handle,const uint64 record_offset)
{

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((int64)record_offset < db_handle->db_cursor.first_record_offset) || (record_offset > db_handle->db_cursor.last_record_offset + db_handle->db_header.record_size))
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_strm_set_current_stream_offset(db_handle->io_stream_handle,record_offset))
	 {
       db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
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

static puchar lilly_db_read_record_ex(const p_lilly_db_handle db_handle,const uint64 record_offset)
{
  puchar record;


	 record = lilly_io_strm_read_stream(db_handle->io_stream_handle,record_offset);

	 if (!record)
	 {
	   db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
	   return NULL;
     }

	 db_handle->db_cursor.last_processed_offset = record_offset;

	 if (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG))
	 {
	   uint32 crc = lilly_db_get_record_crc(db_handle,record);

	   if (!crc) return FALSE;

	   if (crc != ((p_lilly_db_record_header)record)->record_crc)
	   {
		 db_handle->error_code = LILLY_DB_TAMPERED_DATABASE_ERROR;
		 return FALSE;
       }
	 }

	 return record;
}

static boolean lilly_db_write_record_ex(const p_lilly_db_handle db_handle,const p_lilly_db_record_header record,const uint64 record_offset)
{
  p_lilly_db_time_stamp time_stamp;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (!record->time_stamp_infos.creation_stamp.time_stamp.year)
	 {
	   time_stamp = &record->time_stamp_infos.creation_stamp;
	 }
	 else time_stamp = &record->time_stamp_infos.modification_stamp;

	 lilly_db_update_time_stamp(time_stamp,db_handle->operator_id);

	 if (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG))
	 {
	   record->record_crc = lilly_db_get_record_crc(db_handle,(puchar)record);

       if (!record->record_crc) return FALSE;
	 }

	 if (!lilly_io_strm_write_stream(db_handle->io_stream_handle,(puchar)record,record_offset))
	 {
	   db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
       return FALSE;
     }

	 db_handle->db_cursor.last_processed_offset = record_offset;

	 return TRUE;
}

static puchar lilly_db_get_first_record_ex(const p_lilly_db_handle db_handle)
{
  puchar record;


	 record = lilly_db_read_record_ex(db_handle,db_handle->db_cursor.first_record_offset);

	 if (record)
	 {
	   db_handle->db_cursor.current_record_offset = db_handle->db_cursor.first_record_offset + db_handle->db_header.record_size; //lilly_io_strm_get_current_stream_offset(db_handle->io_stream_handle);
	 }

	 return record;
}

static puchar lilly_db_get_next_record_ex(const p_lilly_db_handle db_handle)
{
  puchar record;


	 if (db_handle->db_cursor.current_record_offset > db_handle->db_cursor.last_record_offset) return NULL;

	 record = lilly_db_read_record_ex(db_handle,db_handle->db_cursor.current_record_offset);

	 if (record)
	 {
	   db_handle->db_cursor.current_record_offset += db_handle->db_header.record_size; //lilly_io_strm_get_current_stream_offset(db_handle->io_stream_handle);
	 }

	 return record;
}

static puchar lilly_db_get_previous_record_ex(const p_lilly_db_handle db_handle)
{
  puchar record;


	 if ((int64)db_handle->db_cursor.current_record_offset < db_handle->db_cursor.first_record_offset) return NULL;

	 record = lilly_db_read_record_ex(db_handle,db_handle->db_cursor.current_record_offset);

	 if (!record) return NULL;

	 db_handle->db_cursor.current_record_offset -= db_handle->db_header.record_size;

	 if (!lilly_io_strm_set_current_stream_offset(db_handle->io_stream_handle,db_handle->db_cursor.current_record_offset))
	 {
	   db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
	   return NULL;
     }

	 return record;

}

static puchar lilly_db_get_last_record_ex(const p_lilly_db_handle db_handle)
{
  puchar record;


	 record = lilly_db_read_record_ex(db_handle,db_handle->db_cursor.last_record_offset);

	 if (record)
	 {
	   db_handle->db_cursor.current_record_offset = lilly_io_strm_get_current_stream_offset(db_handle->io_stream_handle);
	 }

	 return record;

}


/*

	END OF INTERNAL ROUTINES

*/

p_lilly_db_handle lilly_db_create_db_handle(const puchar db_path,const unsigned_int db_path_len,const uint64 record_size,const uint64 header_size,const uint32 operator_id,const uint32 session_id,const uint64 db_signature,const uint64 db_flags,const punsigned_int error_code)
{
  p_lilly_db_handle handle = NULL;
  uint32 encryption_key;


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

	 avcore_memset(handle,0,sizeof(*handle));

	 encryption_key = 0;

	 if (CHECK_ATTRIBUTE(db_flags,LILLY_DB_HDR_ENCRYPTION_FLAG))
	 {
	   encryption_key = session_id;
	 }

	 handle->io_stream_handle = lilly_io_strm_create_stream(db_path,record_size + LILLY_DB_RECORD_HEADER_SIZE,error_code,encryption_key,CHECK_ATTRIBUTE(db_flags,LILLY_DB_HDR_COMPRESSION_FLAG));

	 if (!handle->io_stream_handle)
	 {
	   lilly_free(handle,sizeof(*handle));
	   return NULL;
	 }

	 handle->db_header.signature = db_signature;
	 handle->db_header.header_size = header_size;
	 handle->db_header.record_size = record_size + LILLY_DB_RECORD_HEADER_SIZE;
	 handle->db_header.flags = db_flags;
	 handle->db_header.session_id = session_id;

	 SET_ATTRIBUTE(handle->db_header.flags,LILLY_DB_CRASH_STATE_FLAG);

	 if (!lilly_db_write_header(handle,NULL,0))
	 {
	   lilly_io_strm_close_stream(handle->io_stream_handle);
	   lilly_free(handle,sizeof(*handle));
	   return NULL;
     }

     handle->operator_id = operator_id;

	 handle->io_size = header_size;

	 handle->db_cursor.current_record_offset = header_size;
	 handle->db_cursor.first_record_offset = header_size;
	 handle->db_cursor.last_record_offset = header_size;

	 handle->db_path_len = db_path_len;

	 avcore_memcpy(&handle->db_path,db_path,db_path_len);

	 return handle;

}

p_lilly_db_handle lilly_db_open_db_handle(const puchar db_path,const unsigned_int db_path_len,const uint64 db_signature,const uint32 operator_id,const uint32 session_id,const punsigned_int error_code)
{
  p_lilly_db_handle handle = NULL;
  unsigned_int fhandle;
  uint32 encryption_key;

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

	 fhandle = lilly_io_open_file(db_path,lilly_io_fmOpen,lilly_io_faRead);

	 if ((signed_int)fhandle <= 0)
	 {
	   *error_code = IO_ERROR;
	   lilly_free(handle,sizeof(*handle));
	 }

	 handle->io_size = lilly_io_get_file_size_ex(fhandle);

	 if ((int64)handle->io_size <= 0)
	 {
	   *error_code = IO_ERROR;
	   goto failure;
	 }
	 else if (handle->io_size < LILLY_DB_DATABASE_HEADER_SIZE)
	 {
	   *error_code = LILLY_DB_CORRUPTED_DATABASE_ERROR;
	   goto failure;
	 }

	 if (!lilly_io_file_read(fhandle,(puchar)&handle->db_header,LILLY_DB_DATABASE_HEADER_SIZE))
	 {
	   *error_code = IO_ERROR;
	   goto failure;
     }

	 lilly_io_close_file(fhandle);

	 fhandle = 0;

     if (handle->db_header.signature != db_signature)
	 {
	   *error_code = LILLY_DB_SIGNATURE_ERROR;
	   goto failure;
	 }

	 if ((!handle->db_header.header_size) || ((int64)handle->db_header.database_size < 0) || (!handle->db_header.record_size) ||
	 ((int32)handle->db_header.record_count < 0) || ((int32)handle->db_header.deleted_record_count < 0) ||
	 ((uint64)(handle->db_header.record_count * handle->db_header.record_size) != handle->db_header.database_size) ||
	 ((handle->db_header.record_count) && (handle->io_size < handle->db_header.database_size + handle->db_header.header_size)))
	 {
	   *error_code = LILLY_DB_TAMPERED_DATABASE_ERROR;
	   goto failure;
	 }

	 if (CHECK_ATTRIBUTE(handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG))
	 {
	   uint32 crc = lilly_crc32_buffer((puchar)&handle->db_header,FIELD_OFFSET(t_lilly_db_header,header_crc),0);

	   if (!crc)
	   {
		 *error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
		 goto failure;
	   }

	   if (crc != handle->db_header.header_crc)
	   {
		 *error_code = LILLY_DB_TAMPERED_DATABASE_ERROR;
		 goto failure;
	   }
	 }

	 if ((CHECK_ATTRIBUTE(handle->db_header.flags,LILLY_DB_HDR_POWER_USER_ONLY_FLAG)) && (operator_id != LILLY_DB_SUPER_USER_ID))
	 {
	   *error_code = LILLY_DB_USER_PRIVILEGE_ERROR;
	   goto failure;
	 }

	 encryption_key = 0;

	 if (CHECK_ATTRIBUTE(handle->db_header.flags,LILLY_DB_HDR_ENCRYPTION_FLAG))
	 {
	   encryption_key = session_id;

	   if (!encryption_key)
	   {
		 *error_code = LILLY_DB_SESSION_MISMATCH_ERROR;
		 goto failure;
	   }
	 }

	 handle->io_stream_handle = lilly_io_strm_open_stream(db_path,(unsigned_int)handle->db_header.record_size,error_code,encryption_key,(unsigned_int)handle->db_header.header_size,
	 CHECK_ATTRIBUTE(handle->db_header.flags,LILLY_DB_HDR_COMPRESSION_FLAG),CHECK_ATTRIBUTE(handle->db_header.flags,LILLY_DB_READ_ONLY_FLAG));

	 if (!handle->io_stream_handle) goto failure;

	 handle->operator_id = operator_id;

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

	 goto ok;

	 failure :

	 if (fhandle)
	 {
	   lilly_io_close_file(fhandle);
	 }

	 if (handle->io_stream_handle)
	 {
	   lilly_io_strm_close_stream(handle->io_stream_handle);
	 }

	 lilly_free(handle,sizeof(*handle));

	 handle = NULL;

	 ok :

	 return handle;
}

void lilly_db_close_db_handle(const p_lilly_db_handle db_handle)
{

	 if (!db_handle) return;

	 if (db_handle->io_stream_handle)
	 {
	   if (db_handle->lazy_write_mode)
	   {
		 lilly_db_write_header(db_handle,NULL,0);
	   }

	   lilly_io_strm_close_stream(db_handle->io_stream_handle);
	 }

	 avcore_memset(db_handle,0,sizeof(*db_handle));

	 lilly_free(db_handle,sizeof(*db_handle));

     return;
}

boolean lilly_db_purge_database(const p_lilly_db_handle db_handle)
{
  unsigned_int lazy_mode_state;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_strm_truncate_stream(db_handle->io_stream_handle,(puchar)db_handle->db_path,0))
	 {
	   db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
	   return FALSE;
     }

	 db_handle->io_size = db_handle->db_header.header_size;

	 db_handle->db_header.database_size = 0;

	 db_handle->db_header.record_count = 0;
	 db_handle->db_header.deleted_record_count = 0;

	 lazy_mode_state = db_handle->lazy_write_mode;

	 db_handle->lazy_write_mode = 0;

	 if (!lilly_db_write_header(db_handle,NULL,0)) return FALSE;
     else db_handle->lazy_write_mode = lazy_mode_state;

	 db_handle->db_cursor.current_record_offset = db_handle->db_header.header_size;
	 db_handle->db_cursor.first_record_offset = db_handle->db_header.header_size;
	 db_handle->db_cursor.last_record_offset = db_handle->db_header.header_size;

	 return TRUE;
}

boolean lilly_db_export_database(const p_lilly_db_handle db_handle,const puchar target_path)
{

	 if (db_handle)
	 {
	   db_handle->error_code = ERROR_NOT_IMPLEMENTED;
	 }

	 return FALSE;

}

extern boolean lilly_db_set_lazy_write_mode(const p_lilly_db_handle db_handle,const boolean active)
{

	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if ((unsigned_int)active == db_handle->lazy_write_mode) return TRUE;

	 if ((db_handle->lazy_write_mode) && (!lilly_db_write_header(db_handle,NULL,0))) return FALSE;

	 db_handle->lazy_write_mode = (unsigned_int)active;

	 return TRUE;

}


// ajouter 2 fonctions pour lire et ecrire dans l'extra header space


puchar lilly_db_read_record(const p_lilly_db_handle db_handle,const unsigned_int record_data_size,const uint64 record_offset)
{
  puchar record;


	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (record_data_size + LILLY_DB_RECORD_HEADER_SIZE != (unsigned_int)db_handle->db_header.record_size)
	 {
	   db_handle->error_code = API_ERROR;
	   return NULL;
	 }

	 record = lilly_db_read_record_ex(db_handle,record_offset);

	 if (!record) return NULL;
     else return (record + LILLY_DB_RECORD_HEADER_SIZE);

}

boolean lilly_db_write_record(const p_lilly_db_handle db_handle,const puchar data,const unsigned_int data_size,const uint64 record_offset)
{
  puchar record;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if ((!data) || ((signed_int)data_size <= 0) || ((uint64)data_size + LILLY_DB_RECORD_HEADER_SIZE != db_handle->db_header.record_size) || ((int64)record_offset < 0))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 record = lilly_io_strm_get_stream_buffer(db_handle->io_stream_handle,record_offset);

	 if (!record)
	 {
	   db_handle->error_code = lilly_io_strm_get_last_error(db_handle->io_stream_handle);
	   return FALSE;
	 }

	 avcore_memcpy(record + LILLY_DB_RECORD_HEADER_SIZE,data,data_size);

	 return ((lilly_db_write_record_ex(db_handle,(p_lilly_db_record_header)record,record_offset)) &&
	 (lilly_db_write_header(db_handle,NULL,0)));

}

puchar lilly_db_get_first_record(const p_lilly_db_handle db_handle)
{
  puchar record;


	 if (!db_handle) return NULL;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (!db_handle->io_stream_handle)
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

	 if (!db_handle->io_stream_handle)
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

	 if (!db_handle->io_stream_handle)
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

	 if (!db_handle->io_stream_handle)
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

	 if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (db_handle->db_header.record_count)
	 {
	   db_handle->db_cursor.last_record_offset += db_handle->db_header.record_size;
	 }

	 db_handle->db_cursor.current_record_offset = db_handle->db_cursor.last_record_offset;

	 lilly_io_strm_clear_io_buffer(db_handle->io_stream_handle);

	 if (!lilly_db_write_record(db_handle,record,record_size,db_handle->db_cursor.last_record_offset)) return FALSE;

	 db_handle->io_size += db_handle->db_header.record_size;

	 db_handle->db_header.database_size += db_handle->db_header.record_size;

	 db_handle->db_header.record_count++;

	 db_handle->db_header.last_key_index++;

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

	 if (!db_handle->io_stream_handle)
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

     if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return FALSE;
	 }

	 if (!db_handle->db_header.record_count)
	 {
	   db_handle->error_code = LILLY_DB_EMPTY_DATABASE_ERROR;
	   return FALSE;
	 }

	 record = (p_lilly_db_record_header)lilly_db_read_record_ex(db_handle,record_offset);

	 if (!record) return FALSE;

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

	 if (!db_handle->io_stream_handle)
	 {
	   db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	   return IO_ERROR;
	 }

	 return db_handle->db_cursor.last_processed_offset;
}

boolean lilly_db_set_current_record_offset(const p_lilly_db_handle db_handle,const uint64 offset)
{

	 if (!db_handle) return FALSE;

	 if (!set_record_offset(db_handle,offset)) return FALSE;

	 db_handle->db_cursor.last_processed_offset = offset;

	 return TRUE;

}

boolean lilly_db_get_record_time_stamp_infos(const p_lilly_db_handle db_handle,const uint64 record_offset,const p_lilly_db_time_stamp_informations time_stamp_infos)
{
  puchar record;


	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (!time_stamp_infos)
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 record = lilly_db_read_record_ex(db_handle,record_offset);

	 if (!record) return FALSE;

	 // aussi dangereux que la mort, mais je laisse le compilateur générer le meilleur code possible

	 *time_stamp_infos = *(p_lilly_db_time_stamp_informations)(&((p_lilly_db_record_header)record)->time_stamp_infos.creation_stamp);

	 return TRUE;
}

boolean lilly_db_set_record_creation_time(const p_lilly_db_handle db_handle,const uint64 record_offset,const p_lilly_db_time_stamp new_date,const boolean update_operator_id)
{
  p_lilly_db_record_header record;



	 if (!db_handle) return FALSE;

	 db_handle->error_code = ERROR_SUCCESS;

	 if (((int64)record_offset <= 0) || (!new_date))
	 {
	   db_handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 record = (p_lilly_db_record_header)lilly_db_read_record_ex(db_handle,record_offset);

	 if (!lilly_db_read_record_ex(db_handle,record_offset)) return FALSE;

	 if (update_operator_id)
	 {
	   *(p_lilly_db_time_stamp)&record->time_stamp_infos.creation_stamp = *new_date;
	 }
	 else record->time_stamp_infos.creation_stamp.time_stamp = new_date->time_stamp;

	 return lilly_db_write_record_ex(db_handle,record,record_offset);

}

uint32 lilly_db_get_record_crc32(const p_lilly_db_handle db_handle,const uint64 record_offset)
{
  p_lilly_db_record_header record;


	 if (!db_handle) return 0;

	 record = (p_lilly_db_record_header)lilly_db_read_record_ex(db_handle,record_offset);

	 if (!record) return 0;
     else return record->record_crc;
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

uint32 lilly_db_get_unique_autoinc_key(const p_lilly_db_handle db_handle)
{

	if (!db_handle) return IO_ERROR;

	if (!db_handle->io_stream_handle)
	{
	  db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	  return IO_ERROR;
	}
    else return db_handle->db_header.last_key_index;
}

uint32 lilly_db_set_unique_autoinc_key(struct t_lilly_db_handle *db_handle,const uint32 key)
{
   db_handle->db_header.last_key_index = MACRO_MAX_VALUE(db_handle->db_header.last_key_index,key + 1);

   return key;
}

boolean lilly_db_get_database_informations(const p_lilly_db_handle db_handle,const p_lilly_db_database_infos db_infos)
{

	if (!db_handle) return FALSE;

	db_handle->error_code = ERROR_SUCCESS;

	avcore_memset(db_infos,0,sizeof(*db_infos));

	db_infos->db_signature = db_handle->db_header.signature;
	db_infos->record_size = db_handle->db_header.record_size;
	db_infos->database_size = db_handle->db_header.database_size;
	db_infos->record_count = db_handle->db_header.record_count;
	db_infos->deleted_record_count = db_handle->db_header.deleted_record_count;
	db_infos->session_id = db_handle->db_header.session_id;
	db_infos->header_crc = db_handle->db_header.header_crc;

	db_infos->time_stamp_infos = *(p_lilly_db_time_stamp_informations)&db_handle->db_header.time_stamp_infos;

	db_infos->encryption = (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_ENCRYPTION_FLAG));
	db_infos->compression = (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_COMPRESSION_FLAG));
	db_infos->integrity_check = (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_CHECK_CRC_FLAG));
	db_infos->mac_address_lock = (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_MAC_ADDRESS_LOCK_FLAG));
	db_infos->power_user_only = (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_HDR_POWER_USER_ONLY_FLAG));
	db_infos->session_id_lock = (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_SESSION_ID_LOCK_FLAG));
	db_infos->read_only = (CHECK_ATTRIBUTE(db_handle->db_header.flags,LILLY_DB_READ_ONLY_FLAG));

    return TRUE;

}


#pragma pack(push,1)


typedef struct {
				 uint32 signature; // 4
				 uint32 data_size; // 4
				 t_lilly_db_time_stamp_informations time_stamp_infos; // 12
				 t_lilly_db_blob_type blob_type;
				 uint8 reserved[4 - sizeof(t_lilly_db_blob_type)]; // 4
				 uint32 session_id; // 4
				 uint32 crc32;  // 4
			   } t_blob_header,*p_blob_header; // 32

#pragma pack(pop)


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

#define LILLY_DB_BLOB_SIGNATURE 0x626F6C62

#define BB_PREFIX 0x00420042UI32
#define BM_PREFIX 0x004D0042UI32
#define BC_PREFIX 0x00430042UI32
#define BP_PREFIX 0x00500042UI32

boolean lilly_db_record_id_to_blob_name_id(const p_lilly_db_handle db_handle,const p_lilly_db_blob_name blob_id,const uint32 record_id,const t_lilly_db_blob_type blob_type)
{
  static const uint32 prefixes[(unsigned_int)MAX_LILLY_DB_BLOB_TYPE + 1] = {BB_PREFIX,BM_PREFIX,BC_PREFIX,BP_PREFIX};


	if (!db_handle) return FALSE;

	db_handle->error_code = ERROR_SUCCESS;

	if ((!blob_id) || (blob_type > MAX_LILLY_DB_BLOB_TYPE))
	{
	  db_handle->error_code = API_ERROR;
	  return FALSE;
	}

	avcore_memset(blob_id,0,sizeof(*blob_id));

	blob_id->len = 20;

	*(puint32)&blob_id->name = prefixes[blob_type];

	avcore_witoh(record_id,(p_int_to_hexbuffer)&blob_id->name[4]);

	return TRUE;
}

boolean lilly_db_create_blob(const p_lilly_db_handle db_handle,const p_lilly_db_blob_name blob_id,const puchar data,const unsigned_int data_size,const uint32 operator_id)
{
  unsigned_int fhandle;
  t_blob_header blob_hdr;
  uchar blob_path[260 * 2];


	if (!db_handle) return FALSE;

	db_handle->error_code = ERROR_SUCCESS;

	if ((db_handle->blob_folder_path[0] == 0) || ((signed_int)db_handle->blob_path_len <= 0))
	{
	  db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	  return FALSE;
	}

	if ((!blob_id) || (!blob_id->len) || (!data) || ((signed_int)data_size <= 0))
	{
	  db_handle->error_code = API_ERROR;
	  return FALSE;
	}

	if (db_handle->blob_path_len + blob_id->len > sizeof(blob_path) - 4)
	{
	  db_handle->error_code = IO_ERROR;
	  return FALSE;
	}

	// touch memory

	*(puint16)&blob_path[db_handle->blob_path_len + 2 + blob_id->len] = 0;

	avcore_memcpy(&blob_path,&db_handle->blob_folder_path,db_handle->blob_path_len);

	blob_path[db_handle->blob_path_len] = IO_FOLDER_SEPARATOR;
	blob_path[db_handle->blob_path_len + 1] = 0;

	avcore_memcpy(&blob_path[db_handle->blob_path_len + 2],&blob_id->name,blob_id->len);

	if (lilly_io_file_exists((puchar)&blob_path))
	{
	   if (!lilly_io_delete_file((puchar)&blob_path))
	   {
		 db_handle->error_code = IO_ERROR;
		 return FALSE;
       }
	}

	fhandle = lilly_io_create_file((puchar)&blob_path);

	if ((signed_int)fhandle <= 0)
	{
	  db_handle->error_code = IO_ERROR;
	  return FALSE;
	}

    avcore_memset(&blob_hdr,0,sizeof(blob_hdr));

	blob_hdr.signature = LILLY_DB_BLOB_SIGNATURE;
	blob_hdr.data_size = data_size;

	lilly_db_update_time_stamp(&blob_hdr.time_stamp_infos.creation_stamp,(uint64)operator_id);

	switch (*(puint32)&blob_id->name)
	{
	  case BB_PREFIX : blob_hdr.blob_type = t_lilly_db_bin_blob_type;
					   break;

	  case BM_PREFIX : blob_hdr.blob_type = t_lilly_db_notes_medecin_blob_type;
					   break;

	  case BC_PREFIX : blob_hdr.blob_type = t_lilly_db_observations_confidentielles_blob_type;
					   break;

	  case BP_PREFIX : blob_hdr.blob_type = t_lilly_db_photo_blob_type;
					   break;

			 default : db_handle->error_code = API_ERROR;
					   lilly_io_close_file(fhandle);
                       lilly_io_delete_file((puchar)&blob_path);
					   return FALSE;
	}

	blob_hdr.session_id = db_handle->db_header.session_id;

	blob_hdr.crc32 = lilly_crc32_buffer((puchar)&blob_hdr,FIELD_OFFSET(t_blob_header,crc32),0);

	if (!blob_hdr.crc32)
	{
	  db_handle->error_code = LILLY_DB_UNSPECIFIED_FATAL_ERROR;
	  lilly_io_close_file(fhandle);
	  lilly_io_delete_file((puchar)&blob_path);
	  return FALSE;
	}

	if ((!lilly_io_file_write(fhandle,(puchar)&blob_hdr,sizeof(blob_hdr))) || (!lilly_io_file_write(fhandle,data,data_size)))
	{
      db_handle->error_code = IO_ERROR;
	  lilly_io_close_file(fhandle);
	  lilly_io_delete_file((puchar)&blob_path);
	  return FALSE;
	}

	lilly_io_close_file(fhandle);

	return TRUE;

}

typedef struct t_lilly_db_blob_handle {
										unsigned_int error_code;
										unsigned_int io_handle;
										uint64 io_size;
										t_blob_header header;
										uchar blob_file_path[260 * 2];
									  } *p_lilly_db_blob_handle;


p_lilly_db_blob_handle lilly_db_open_blob(const p_lilly_db_handle db_handle,const p_lilly_db_blob_name blob_id)
{
  p_lilly_db_blob_handle blob_handle;


	if (!db_handle) return NULL;

	db_handle->error_code = ERROR_SUCCESS;

	if ((db_handle->blob_folder_path[0] == 0) || ((signed_int)db_handle->blob_path_len <= 0))
	{
	  db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	  return NULL;
	}

	if ((!blob_id) || ((signed_int)blob_id->len <= 0))
	{
	  db_handle->error_code = API_ERROR;
	  return NULL;
	}

	if (db_handle->blob_path_len + blob_id->len > sizeof(blob_handle->blob_file_path) - 4)
	{
	  db_handle->error_code = IO_ERROR;
	  return NULL;
	}

    blob_handle = (p_lilly_db_blob_handle)lilly_malloc(sizeof(*blob_handle));

	if (!blob_handle)
	{
	  db_handle->error_code = MEM_ALLOC_ERROR;
	  return NULL;
	}

	avcore_memset(blob_handle,0,sizeof(*blob_handle));

	avcore_memcpy(&blob_handle->blob_file_path,&db_handle->blob_folder_path,db_handle->blob_path_len);

	blob_handle->blob_file_path[db_handle->blob_path_len] = IO_FOLDER_SEPARATOR;
	blob_handle->blob_file_path[db_handle->blob_path_len + 1] = 0;

	avcore_memcpy(&blob_handle->blob_file_path[db_handle->blob_path_len + 2],&blob_id->name,blob_id->len);

	if (!lilly_io_file_exists((puchar)&blob_handle->blob_file_path))
	{
	  db_handle->error_code = LILLY_DB_BLOB_OBJECT_NOT_FOUND;
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

	if (lilly_crc32_buffer((puchar)&blob_handle->header,FIELD_OFFSET(t_blob_header,crc32),0) != blob_handle->header.crc32)
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

#undef LILLY_DB_BLOB_SIGNATURE

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

boolean lilly_db_delete_blob(const p_lilly_db_handle db_handle,const p_lilly_db_blob_name blob_id)
{
  uchar blob_path[260 * 2];



	if (!db_handle) return FALSE;

	db_handle->error_code = ERROR_SUCCESS;

	if ((db_handle->blob_folder_path[0] == 0) || ((signed_int)db_handle->blob_path_len <= 0))
	{
	  db_handle->error_code = LILLY_DB_IO_STATE_ERROR;
	  return FALSE;
	}

	if ((!blob_id) || ((signed_int)blob_id->len <= 0))
	{
	  db_handle->error_code = API_ERROR;
	  return FALSE;
	}

	if (db_handle->blob_path_len + blob_id->len > sizeof(blob_path) - 4)
	{
	  db_handle->error_code = IO_ERROR;
	  return FALSE;
	}

	// touch memory

	*(puint16)&blob_path[db_handle->blob_path_len + 2 + blob_id->len] = 0;

	avcore_memcpy(&blob_path,&db_handle->blob_folder_path,db_handle->blob_path_len);

	blob_path[db_handle->blob_path_len] = IO_FOLDER_SEPARATOR;
	blob_path[db_handle->blob_path_len + 1] = 0;

	avcore_memcpy(&blob_path[db_handle->blob_path_len + 2],&blob_id->name,blob_id->len);

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

	if (!blob_handle->header.data_size) return FALSE;
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

/*

	SUPPORT FILTERS

*/

boolean execute_filters(const p_lilly_db_filters_stack filters,const punsigned_int error_code)
{
  int i;

	if (!error_code) return FALSE;

	*error_code = ERROR_SUCCESS;

	for (i = 0; i < filters->filters_count; i++)
	{

	}

	return FALSE;
}

