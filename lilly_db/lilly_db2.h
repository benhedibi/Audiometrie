#ifndef LILLY_DB2_H
#define LILLY_DB2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>

#pragma pack(push,1)


typedef struct {
				 uint32 unique_index;
				 uint32 crc32;
			   } t_lilly_db_record_id,*p_lilly_db_record_id; // 8 bytes

typedef struct {
				 uint32 operator_id;
				 t_date_time time_stamp;
			   } t_lilly_db_time_stamp,*p_lilly_db_time_stamp; // 12 bytes

typedef struct {
				 t_lilly_db_time_stamp creation_stamp;
				 t_lilly_db_time_stamp modification_stamp;
			   } t_lilly_db_time_stamp_informations,*p_lilly_db_time_stamp_informations; // 24 bytes


#define LILLY_DB_DATABASE_HEADER_SIZE 64


typedef enum {
			   t_by_name_lilly_db_filter_type,
			   t_by_age_lilly_db_filter_type,
			   t_by_date_lilly_db_filter_type,
			   t_by_id_lilly_db_filter_type,
			   t_by_country_lilly_db_filter_type,
			   t_by_gouvernorat_lilly_db_filter_type,
			   t_by_city_lilly_db_filter_type,
			   t_by_gender_lilly_db_filter_type,
			   t_by_taille_lilly_db_filter_type,
			   t_by_poids_lilly_db_filter_type,
			   t_by_telephone_lilly_db_filter_type,
			   t_by_mail_lilly_db_filter_type,
			   t_by_valeurs_types_lilly_db_filter_type
			 } t_lilly_db_filter_type;

typedef enum {
			   t_string_match_lilly_db_filter_mode,
			   t_numerical_match_lilly_db_filter_mode,
			   t_full_match_lilly_db_filter_mode
			 } t_lilly_db_filter_match_mode;

typedef enum {
			   t_less_lilly_db_filter_operation,
			   t_less_or_equal_lilly_db_filter_operation,
			   t_great_lilly_db_filter_operation,
			   t_great_or_equal_lilly_db_filter_operation,
			   t_equal_lilly_db_filter_operation
			 } t_lilly_db_filter_operation;

typedef enum {
			   t_or_lilly_db_filter_join_mode,
			   t_and_lilly_db_filter_join_mode,
			   t_not_lilly_db_filter_join_mode
			 } t_lilly_db_join_mode;

typedef struct {
				 puchar op1;
				 puchar op2;
				 t_lilly_db_filter_type filter_type;
				 t_lilly_db_filter_match_mode match_mode;
				 t_lilly_db_filter_operation operation;
			   } t_lilly_db_filter_argument,*p_lilly_db_filter_argument;

typedef struct {
				 t_lilly_db_filter_argument arg1;
				 t_lilly_db_filter_argument arg2;
				 t_lilly_db_join_mode join_mode;
			   } t_lilly_db_filter_instruction,*p_lilly_db_filter_instruction;
typedef struct {
				 unsigned_int filters_count;
				 t_lilly_db_filter_instruction instructions[8];
			   } t_lilly_db_filters_stack,*p_lilly_db_filters_stack;

typedef struct {
				 unsigned_int db_signature;  // 4
				 unsigned_int record_size;  // 2
				 uint64 database_size; // 8
				 unsigned_int record_count; // 4
				 unsigned_int deleted_record_count; // 4
				 unsigned_int session_id; // les bases de données qui n'ont pas les mêmes session id, ne communiquent pas  // 4
				 unsigned_int header_crc;  // 4
				 t_lilly_db_time_stamp_informations time_stamp_infos;  // 24
				 boolean encryption;
				 boolean compression;
				 boolean integrity_check;
				 boolean mac_address_lock;
				 boolean power_user_only;
				 boolean session_id_lock;
				 boolean read_only;
				 boolean indexing;
                 boolean crash_flag;
			   } t_lilly_db_database_infos,*p_lilly_db_database_infos;


#pragma pack(pop)


#define LILLY_DB_HDR_ENCRYPTION_FLAG       (1 << 1)
#define LILLY_DB_HDR_COMPRESSION_FLAG      (1 << 2)
#define LILLY_DB_HDR_CHECK_CRC_FLAG        (1 << 3)
#define LILLY_DB_HDR_MAC_ADDRESS_LOCK_FLAG (1 << 4)
#define LILLY_DB_HDR_POWER_USER_ONLY_FLAG  (1 << 5)
#define LILLY_DB_SESSION_ID_LOCK_FLAG      (1 << 6)
#define LILLY_DB_READ_ONLY_FLAG            (1 << 7)
#define LILLY_DB_INDEXING_FLAG             (1 << 8)


#define LILLY_DB_SUPER_USER_ID  0

#define LILLY_DB_MAX_PATH 256


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
#define LILLY_DB_MALFORMED_BLOB_ERROR     2001
#define LILLY_DB_BLOB_ID_COLLISION_ERROR  2002
#define LILLY_DB_BLOB_OBJECT_NOT_FOUND    2003
#define LILLY_DB_RECORD_LOOKUP_ERROR      2004
#define LILLY_DB_FEATURE_UNAVAILABLE      2005
#define LILLY_DB_VIRGIN_INDEX_FILE        2006


#define LILLY_DB_ENGINE_IMPORT_FUNCTIONS_HELPERS

struct t_lilly_db_handle;

struct t_lilly_db_blob_handle;

extern struct t_lilly_db_handle *lilly_db_create_db_handle(const puchar db_path,const unsigned_int db_path_len,const uint64 record_size,const uint64 header_size,const uint32 operator_id,const uint32 session_id,const uint64 db_signature,const uint64 db_flags,const punsigned_int error_code);
extern struct t_lilly_db_handle *lilly_db_open_db_handle(const puchar db_path,const unsigned_int db_path_len,const uint64 db_signature,const uint32 operator_id,const uint32 session_id,const punsigned_int error_code);
extern void lilly_db_close_db_handle(struct t_lilly_db_handle *db_handle);

extern boolean lilly_db_purge_database(struct t_lilly_db_handle *db_handle);

extern boolean lilly_db_export_database(struct t_lilly_db_handle *db_handle,const puchar target_path);

extern boolean lilly_db_set_lazy_write_mode(struct t_lilly_db_handle *db_handle,const boolean active);

extern puchar lilly_db_read_record(struct t_lilly_db_handle *db_handle,const unsigned_int record_data_size,const uint64 record_offset);
extern boolean lilly_db_write_record(struct t_lilly_db_handle *db_handle,const puchar record_data,const unsigned_int record_data_size,const uint64 record_offset);

extern puchar lilly_db_get_first_record(struct t_lilly_db_handle *db_handle);
extern puchar lilly_db_get_next_record(struct t_lilly_db_handle *db_handle);
extern puchar lilly_db_get_previous_record(struct t_lilly_db_handle *db_handle);
extern puchar lilly_db_get_last_record(struct t_lilly_db_handle *db_handle);

extern boolean lilly_db_append_record(struct t_lilly_db_handle *db_handle,const puchar record,const unsigned_int record_size);
extern boolean lilly_db_edit_record(struct t_lilly_db_handle *db_handle,const puchar record,const unsigned_int record_size,const uint64 record_offset);
extern boolean lilly_db_delete_record(struct t_lilly_db_handle *db_handle,const uint64 record_offset);

extern uint64 lilly_db_get_current_record_offset(struct t_lilly_db_handle *db_handle);
extern boolean lilly_db_set_current_record_offset(struct t_lilly_db_handle *db_handle,const uint64 offset);

extern boolean lilly_db_get_record_time_stamp_infos(struct t_lilly_db_handle *db_handle,const uint64 record_offset,const p_lilly_db_time_stamp_informations time_stamp_infos);

extern boolean lilly_db_set_record_creation_time(struct t_lilly_db_handle *db_handle,const uint64 record_offset,const p_lilly_db_time_stamp new_date,const boolean update_operator_id); // utilisée par l'application d'import

extern uint32 lilly_db_get_record_crc32(struct t_lilly_db_handle *db_handle,const uint64 record_offset);

extern unsigned_int lilly_db_get_last_error(struct t_lilly_db_handle *db_handle);
extern void lilly_db_set_last_error(struct t_lilly_db_handle *db_handle,const unsigned_int error_code);

extern uint32 lilly_db_get_unique_autoinc_key(struct t_lilly_db_handle *db_handle);
extern uint32 lilly_db_set_unique_autoinc_key(struct t_lilly_db_handle *db_handle,const uint32 key); // temporaire pour la base patients

extern boolean lilly_db_get_database_informations(struct t_lilly_db_handle *db_handle,const p_lilly_db_database_infos db_infos);
extern boolean lilly_db_set_database_informations(struct t_lilly_db_handle *db_handle,const p_lilly_db_database_infos db_infos); // disponible en mode administration

/*

	Gestionnaire des BLOB

*/

#pragma pack(push,1)

typedef enum {
			   t_lilly_db_bin_blob_type,
			   t_lilly_db_notes_medecin_blob_type,
			   t_lilly_db_observations_confidentielles_blob_type,
			   t_lilly_db_photo_blob_type,
			   MAX_LILLY_DB_BLOB_TYPE = t_lilly_db_photo_blob_type
			 } t_lilly_db_blob_type;

typedef struct {
				 unsigned_int len;
				 uchar name[32 - sizeof(unsigned_int)]; // prefix  4 + 16 bytes hex + 2 null afin de permettre un affichage unicodestring
			   } t_lilly_db_blob_name,*p_lilly_db_blob_name;

#pragma pack(pop)

extern boolean lilly_db_record_id_to_blob_name_id(struct t_lilly_db_handle *db_handle,const p_lilly_db_blob_name blob_id,const uint32 record_id,const t_lilly_db_blob_type blob_type);

extern puchar lilly_db_get_blob_db_path(struct t_lilly_db_handle *db_handle,const punsigned_int blob_path_len);
extern boolean lilly_db_set_blob_db_path(struct t_lilly_db_handle *db_handle,const puchar blob_db_path,const unsigned_int blob_db_path_len);

extern boolean lilly_db_create_blob(struct t_lilly_db_handle *db_handle,const p_lilly_db_blob_name blob_id,const puchar data,const unsigned_int data_size,const uint32 operator_id);
extern struct t_lilly_db_blob_handle* lilly_db_open_blob(struct t_lilly_db_handle *db_handle,const p_lilly_db_blob_name blob_id);

extern uint64 lilly_db_get_blob_data_size(struct t_lilly_db_blob_handle *blob_handle);
extern unsigned_int lilly_db_get_blob_last_error(struct t_lilly_db_blob_handle *blob_handle);

extern boolean lilly_db_delete_blob(struct t_lilly_db_handle *db_handle,const p_lilly_db_blob_name blob_id);

extern boolean lilly_db_read_blob(struct t_lilly_db_blob_handle *blob_handle,const puchar data,const unsigned_int data_size);
extern boolean lilly_db_write_blob(struct t_lilly_db_blob_handle* blob_handle,const puchar data,const unsigned_int data_size,const uint32 operator_id);

extern void lilly_db_close_blob(struct t_lilly_db_blob_handle *blob_handle);

/*

   INDEXING

*/

extern boolean lilly_db_add_index(struct t_lilly_db_handle *db_handle,const uint32 index,const uint64 offset);
extern boolean lilly_db_del_index(struct t_lilly_db_handle *db_handle,const uint32 index);
extern opaque_ptr lilly_db_index_to_record(struct t_lilly_db_handle *db_handle,const unsigned_int record_size,const uint32 index);
extern uint64 lilly_db_index_to_record_offset(struct t_lilly_db_handle *db_handle,const uint32 index);
extern boolean lilly_db_index_file_available(struct t_lilly_db_handle *db_handle);

/*
	SUPPORT FILTRES
*/


extern boolean execute_filters(const p_lilly_db_filters_stack filters,const punsigned_int error_code);

#ifdef __cplusplus
}
#endif

#endif