#ifndef LILLY_DB_MANAGER_H
#define LILLY_DB_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_io.h>
#include <lilly_os.h>

#include <lilly_mem.h>

#pragma pack(push,1)


typedef struct {
				 uint32 unique_index;
				 uint32 crc32;
			   } t_lilly_db_record_id,*p_lilly_db_record_id;

typedef struct {
				 uint64 operator_id;
				 t_date_time time_stamp;
			   } t_lilly_db_time_stamp,*p_lilly_db_time_stamp;

typedef struct {
				 t_lilly_db_time_stamp creation_stamp;
				 t_lilly_db_time_stamp modification_stamp;
			   } t_lilly_db_time_stamp_informations,*p_lilly_db_time_stamp_informations;


typedef struct {
				 uint64 signature;
				 uint64 header_size;
				 uint64 database_size;
				 uint64 record_size;
				 uint64 flags;
				 t_lilly_db_time_stamp creation_stamp;
				 t_lilly_db_time_stamp modification_stamp;
				 uint64 record_count;
				 uint64 deleted_record_count;
				 uint32 session_id; // les bases de données qui n'ont pas les mêmes session id, ne communiquent pas
				 uint32 header_crc;
			   } t_lilly_db_header,*p_lilly_db_header; // 96 bytes


#define LILLY_DB_HDR_ENCRYPTION_FLAG       (1 << 1)
#define LILLY_DB_HDR_COMPRESSION_FLAG      (1 << 2)
#define LILLY_DB_HDR_CHECK_CRC_FLAG        (1 << 3)
#define LILLY_DB_HDR_MAC_ADDRESS_LOCK_FLAG (1 << 4)
#define LILLY_DB_HDR_POWER_USER_ONLY_FLAG  (1 << 5)
#define LILLY_DB_SESSION_ID_LOCK_FLAG      (1 << 6)


#define LILLY_DB_CRASH_STATE_FLAG          (1 << 24) // if present ça veut dire , la base n'a pas été quitté correctement (crash app, coupure courant etc...)

#define LILLY_DB_DATABASE_HEADER_SIZE (uint64)(sizeof(t_lilly_db_header))

#define LILLY_DB_SUPER_USER_ID  IO_ERROR


typedef struct {
				 uint64 record_flags;  //4
				 t_lilly_db_time_stamp creation_time;    //8
				 t_lilly_db_time_stamp last_modification_time;  //8
				 uint64 offset;       //8
				 uint64 reserved;
				 uint32 reserved2;
				 uint32 record_crc;    //4
			   } t_lilly_db_record_header,*p_lilly_db_record_header; // taille 64 bytes


#define LILLY_DB_RECORD_HEADER_SIZE (sizeof(t_lilly_db_record_header))

#define LILLY_DB_RECORD_DELETION_FLAG 1


typedef struct {
				 uint64 flags;
				 puchar current_record_data;
				 uint64 current_record_offset;
				 uint64 first_record_offset;
				 uint64 last_record_offset;
                 uint64 last_processed_offset;
			   } t_lilly_db_cursor,*p_lilly_db_cursor;


#pragma pack(pop)


typedef struct {
				 unsigned_int error_code;
				 unsigned_int io_handle;
				 uint64 io_size;
				 uint64 operator_id;
				 t_lilly_db_header db_header;
				 t_lilly_db_cursor db_cursor;
				 uint64 header_extra_data_offset;
				 unsigned_int header_extra_data_size;
				 unsigned_int db_path_len;
				 uchar db_path[424]; // (MAX_PATH * 2 ) + alignement
			   } t_lilly_db_handle,*p_lilly_db_handle;

typedef struct {
				 uint32 operator_id;
				 uint32 session_id;
				 uint64 session_flags;
				 p_lilly_db_handle operators_database_handle;
				 p_lilly_db_handle patients_database_handle;
				 p_lilly_db_handle doctors_database_handle;
				 p_lilly_db_handle audiograms_database_handle;
				 p_lilly_db_handle tympanograms_database_handle;
				 p_lilly_db_handle gainp_database_handle;
				 p_lilly_db_handle audiovoc_database_handle;
			   } t_lilly_db_session,*p_lilly_db_session;



#define LILLY_DB_EMPTY_DATABASE_ERROR     1990
#define LILLY_DB_DUPLICATE_RECORD_ERROR   1991
#define LILLY_DB_IO_FILE_EXISTS_ERROR     1992
#define LILLY_DB_SIGNATURE_ERROR          1993
#define LILLY_DB_IO_STATE_ERROR           1994
#define LILLY_DB_CORRUPTED_DATABASE_ERROR 1995
#define LILLY_DB_TAMPERED_DATABASE_ERROR  1996
#define LILLY_DB_UNSPECIFIED_FATAL_ERROR  1997
#define LILLY_DB_SERIALIZE_DATA_ERROR     1998
#define LILLY_DB_USER_PRIVILEGE_ERROR     1999
#define LILLY_DB_SESSION_MISMATCH_ERROR   2000


#define LILLY_CALL_CONVENTION __fastcall

struct t_lilly_database_manager;

typedef opaque_ptr LILLY_CALL_CONVENTION t_lilly_db_create_db_handle(const struct t_lilly_database_manager *self,const puchar db_path,const unsigned_int db_path_len,const uint64 record_size,const uint64 header_size,const uint32 operator_id,const uint32 session_id,const uint64 db_signature,const uint64 db_flags,const punsigned_int error_code);
typedef t_lilly_db_create_db_handle *p_lilly_db_create_db_handle;

typedef opaque_ptr LILLY_CALL_CONVENTION t_lilly_db_open_db_handle(const struct t_lilly_database_manager *self,const puchar db_path,const unsigned_int db_path_len,const uint64 db_signature,const uint64 operator_id,const punsigned_int error_code);
typedef t_lilly_db_open_db_handle *p_lilly_db_open_db_handle;

typedef void LILLY_CALL_CONVENTION t_lilly_db_close_db_handle(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_close_db_handle *p_lilly_db_close_db_handle;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_purge_database(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_purge_database *p_lilly_db_purge_database;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_export_database(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const puchar target_path);
typedef t_lilly_db_export_database *p_lilly_db_export_database;

typedef puchar LILLY_CALL_CONVENTION t_lilly_db_read_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const unsigned_int record_data_size,const uint64 record_offset);
typedef t_lilly_db_read_record *p_lilly_db_read_record;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_write_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const puchar record_data,const unsigned_int record_data_size,const uint64 record_offset);
typedef t_lilly_db_write_record *p_lilly_db_write_record;

typedef puchar LILLY_CALL_CONVENTION t_lilly_db_get_first_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_get_first_record *p_lilly_db_get_first_record;

typedef puchar LILLY_CALL_CONVENTION t_lilly_db_get_next_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_get_next_record *p_lilly_db_get_next_record;

typedef puchar LILLY_CALL_CONVENTION t_lilly_db_get_previous_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_get_previous_record *p_lilly_db_get_previous_record;

typedef puchar LILLY_CALL_CONVENTION t_lilly_db_get_last_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_get_last_record *p_lilly_db_get_last_record;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_append_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const puchar record,const unsigned_int record_size);
typedef t_lilly_db_append_record *p_lilly_db_append_record;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_edit_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const puchar record,const unsigned_int record_size,const uint64 record_offset);
typedef t_lilly_db_edit_record *p_lilly_db_edit_record;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_delete_record(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const uint64 record_offset);
typedef t_lilly_db_delete_record *p_lilly_db_delete_record;

typedef uint64 LILLY_CALL_CONVENTION t_lilly_db_get_current_record_offset(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_get_current_record_offset *p_lilly_db_get_current_record_offset;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_set_current_record_offset(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const uint64 offset);
typedef t_lilly_db_set_current_record_offset *p_lilly_db_set_current_record_offset;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_get_record_time_stamp_infos(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const uint64 record_offset,const p_lilly_db_time_stamp_informations time_stamp_infos);
typedef t_lilly_db_get_record_time_stamp_infos *p_lilly_db_get_record_time_stamp_infos;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_set_record_creation_time(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const uint64 record_offset,const p_date_time new_date); // utilisée par l'application d'import
typedef t_lilly_db_set_record_creation_time *p_lilly_db_set_record_creation_time;

typedef uint32 LILLY_CALL_CONVENTION t_lilly_db_get_record_crc32(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const uint64 record_offset);
typedef t_lilly_db_get_record_crc32 *p_lilly_db_get_record_crc32;

typedef unsigned_int LILLY_CALL_CONVENTION t_lilly_db_get_last_error(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle);
typedef t_lilly_db_get_last_error *p_lilly_db_get_last_error;

typedef void LILLY_CALL_CONVENTION t_lilly_db_set_last_error(const struct t_lilly_database_manager *self,const p_lilly_db_handle db_handle,const unsigned_int error_code);
typedef t_lilly_db_set_last_error *p_lilly_db_set_last_error;


	/*typedef struct t_lilly_database_manager {
											  unsigned_int error_code;
											  p_lilly_db_create_db_handle
											  p_lilly_db_open_db_handle
											  p_lilly_db_close_db_handle
											  p_lilly_db_purge_database
											  p_lilly_db_export_database
											  p_lilly_db_read_record
											  p_lilly_db_write_record
											  p_lilly_db_get_first_record
											  p_lilly_db_get_next_record
											  p_lilly_db_get_previous_record
											  p_lilly_db_get_last_record
											  p_lilly_db_append_record
											  p_lilly_db_edit_record
                                              p_lilly_db_delete_record
											};    */
#ifdef __cplusplus
}
#endif

#endif