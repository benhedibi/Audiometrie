#ifndef DBIMPORT_H
#define DBIMPORT_H


#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_session_manager.h>


typedef struct {
				 unsigned_int field_len;
				 uchar data[256 - sizeof(unsigned_int)];
			   } t_db_field_buffer,*p_db_field_buffer;


#define LILLY_DB_IMPORT_MALFORMED_FIELD_ERROR 2000
#define LILLY_DB_IMPORT_DATA_CONVERSION_ERROR 2001

typedef enum {
			   t_lilly_db_import_generic_string_serializer,
			   t_lilly_db_import_job_serializer,
			   t_lilly_db_import_operator_name_serializer,
			   t_lilly_db_import_doctor_name_serializer,
			   t_lilly_db_import_pays_serializer,
			   t_lilly_db_import_ville_serializer,
			   t_lilly_db_import_gouvernorat_serializer,
			   t_lilly_db_import_gainp_prothese_ref_serializer,
			   t_lilly_db_import_codep_serializer,
			   t_lilly_db_import_patient_name_serializer
			 } t_lilly_db_import_serializer_mode;

typedef void __fastcall t_serializer_callback(const p_db_field_buffer field_buffer,const t_lilly_db_import_serializer_mode serializer_mode);
typedef t_serializer_callback *p_serializer_callback;

typedef struct t_lilly_db_handle* t_lilly_db_import_execute(const p_lilly_db_session_manager session_manager,const puchar source_path,const puchar destination_path,const unsigned_int destination_path_len,const uint64 db_flags,const uint32 operator_id,const uint32 session_id,const t_serializer_callback serializer_callback,const punsigned_int error_code);
typedef t_lilly_db_import_execute *p_lilly_db_import_execute;

extern boolean lilly_import_read_db_field(const p_db_field_buffer field_buffer,unsigned_int field_index,puchar data,unsigned_int data_size);

extern puchar lilly_import_get_first_field(const puchar buffer,const punsigned_int size_left);
extern puchar lilly_import_get_next_field(const puchar buffer,const punsigned_int size_left);


#define DEFAULT_OPERATOR_NAME ((puchar)L"LOTFI ZEKRI")
#define DEFAULT_OPERATOR_NAME_LEN 22

#define DEFAULT_NAME ((puchar)L"Non spécifié")
#define DEFAULT_NAME_LEN 24


#ifdef __cplusplus
}
#endif

#endif