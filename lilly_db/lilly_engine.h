#ifndef LILLY_DB_ENGINE_H
#define LILLY_DB_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db2.h>

struct t_lilly_db_engine;

typedef struct t_lilly_db_handle* LILLY_CALL_CONVENTION t_lilly_db_new_database(const struct t_lilly_db_engine *self,const puchar database_path,const unsigned_int db_path_len,const uint64 databse_flags,const uint32 operator_id,const uint32 session_id);
typedef t_lilly_db_new_database *p_lilly_db_new_database;

typedef struct t_lilly_db_handle* LILLY_CALL_CONVENTION t_lilly_db_load_database(const struct t_lilly_db_engine *self,const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id);
typedef t_lilly_db_load_database *p_lilly_db_load_database;

typedef void LILLY_CALL_CONVENTION t_lilly_db_close_database(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle);
typedef t_lilly_db_close_database *p_lilly_db_close_database;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_save_database(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const puchar database_path);
typedef t_lilly_db_save_database *p_lilly_db_save_database;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_append_record(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const opaque_ptr record);
typedef t_lilly_db_append_record *p_lilly_db_append_record;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_edit_record(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const opaque_ptr record,const uint64 record_offset);
typedef t_lilly_db_edit_record *p_lilly_db_edit_record;

typedef boolean LILLY_CALL_CONVENTION t_lilly_db_delete_record(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const uint64 record_offset);
typedef t_lilly_db_delete_record *p_lilly_db_delete_record;

typedef opaque_ptr LILLY_CALL_CONVENTION t_lilly_db_get_first_filtered_record(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const opaque_ptr filter_params);
typedef t_lilly_db_get_first_filtered_record *p_lilly_db_get_first_filtered_record;

typedef opaque_ptr LILLY_CALL_CONVENTION t_lilly_db_get_next_filtered_record(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const opaque_ptr filter_params);
typedef t_lilly_db_get_next_filtered_record *p_lilly_db_get_next_filtered_record;

typedef opaque_ptr LILLY_CALL_CONVENTION t_lilly_db_code_to_record(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const uint32 rec_code);
typedef t_lilly_db_code_to_record *p_lilly_db_code_to_record;

typedef uint32 LILLY_CALL_CONVENTION t_lilly_db_get_record_crc(const struct t_lilly_db_engine *self,const struct t_lilly_db_handle *db_handle,const opaque_ptr record);
typedef t_lilly_db_get_record_crc *p_lilly_db_get_record_crc;


#pragma pack(push,1)


typedef struct t_lilly_db_engine {
								   unsigned_int error_code;
								   opaque_ptr session_manager;
								   opaque_ptr rtm_params;
                                   unsigned_int rtm_params_size;
								   p_lilly_db_new_database new_database;
								   p_lilly_db_load_database load_database;
								   p_lilly_db_close_database close_database;
								   p_lilly_db_save_database save_database;
								   p_lilly_db_append_record append_record;
								   p_lilly_db_edit_record edit_record;
								   p_lilly_db_delete_record delete_record;
								   p_lilly_db_get_first_filtered_record get_first_filtered_record;
								   p_lilly_db_get_next_filtered_record get_next_filtered_record;
								   p_lilly_db_code_to_record code_to_record;
								   p_lilly_db_get_record_crc get_record_crc;
								 } *p_lilly_db_engine;

#pragma pack(pop)

typedef p_lilly_db_engine LILLY_CALL_CONVENTION t_get_lilly_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
typedef t_get_lilly_db_engine *p_get_lilly_db_engine;

typedef void LILLY_CALL_CONVENTION t_release_lilly_db_engine(const p_lilly_db_engine db_engine);
typedef t_release_lilly_db_engine *p_release_lilly_db_engine;


#ifdef __cplusplus
}
#endif

#endif