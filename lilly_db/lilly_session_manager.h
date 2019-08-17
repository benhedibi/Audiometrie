#ifndef LILLY_DB_SESSION_MANAGER_H
#define LILLY_DB_SESSION_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db2.h>
#include <lilly_engine.h>


#pragma pack(push,1)

typedef struct {
				 t_date_time start_time;
				 t_date_time end_time;
			   } t_lilly_db_time_range,*p_lilly_db_range_time;

typedef struct {
				 uint32 patient_id;
				 uint32 audiogram_id;
				 uint32 tympanogram_id;
				 uint32 audiovoc_id;
				 uint32 gainp_id;
				 t_lilly_db_time_range time_range;
				 uint32 reserved; // juste pour aligner en 8 bytes
			   } t_consultation_filter_params,*p_consultation_filter_params;


#pragma pack(pop)

struct t_lilly_db_session_manager;

typedef p_lilly_db_engine LILLY_CALL_CONVENTION t_register_lilly_engine(const struct t_lilly_db_session_manager *self,const uint32 engine_id);
typedef t_register_lilly_engine *p_register_lilly_engine;

typedef p_lilly_db_engine LILLY_CALL_CONVENTION t_request_lilly_engine(const struct t_lilly_db_session_manager *self,const uint32 engine_id);
typedef t_request_lilly_engine *p_request_lilly_engine;

typedef struct t_lilly_db_handle* LILLY_CALL_CONVENTION t_request_db_handle(const struct t_lilly_db_session_manager *self,const uint32 engine_id);
typedef t_request_db_handle *p_request_db_handle;

typedef opaque_ptr LILLY_CALL_CONVENTION t_code_to_record(const struct t_lilly_db_session_manager *self,const uint32 engine_id,const uint32 code);
typedef t_code_to_record *p_code_to_record;

typedef puchar LILLY_CALL_CONVENTION t_record_id_to_name(const struct t_lilly_db_session_manager *self,const uint32 engine_id,const uint32 record_id,const punsigned_int name_len);
typedef t_record_id_to_name *p_record_id_to_name;

typedef opaque_ptr LILLY_CALL_CONVENTION t_record_id_to_consultation_record(const struct t_lilly_db_session_manager *self,const uint32 engine_id,const uint32 record_id);
typedef t_record_id_to_consultation_record *p_record_id_to_consultation_record;

typedef boolean LILLY_CALL_CONVENTION t_delete_consultation(const struct t_lilly_db_session_manager *self,const uint32 consultation_id);
typedef t_delete_consultation *p_delete_consultation;

typedef boolean LILLY_CALL_CONVENTION t_delete_consultation_ex(const struct t_lilly_db_session_manager *self,const struct t_lilly_db_handle* db_handle,const opaque_ptr consultation_record,const uint64 offset);
typedef t_delete_consultation_ex *p_delete_consultation_ex;

typedef unsigned_int LILLY_CALL_CONVENTION t_delete_patient(const struct t_lilly_db_session_manager *self,const uint32 patient_id);
typedef t_delete_patient *p_delete_patient;

typedef boolean LILLY_CALL_CONVENTION t_delete_patient_ex(const struct t_lilly_db_session_manager *self,const struct t_lilly_db_handle* db_handle,const opaque_ptr patient_record,const uint64 offset);
typedef t_delete_consultation_ex *p_delete_patient_ex;

/* helpers pour le programme d'importation des bases DBASE */

typedef uint32 LILLY_CALL_CONVENTION t_operator_name_to_id(const struct t_lilly_db_session_manager *self,const puchar name,const unsigned_int name_len);
typedef t_operator_name_to_id *p_operator_name_to_id;

typedef uint32 LILLY_CALL_CONVENTION t_doctor_name_to_id(const struct t_lilly_db_session_manager *self,const puchar name,const unsigned_int name_len);
typedef t_doctor_name_to_id *p_doctor_name_to_id;

typedef uint32 LILLY_CALL_CONVENTION t_code_patient_to_operator_id(const struct t_lilly_db_session_manager *self,const uint32 codep);
typedef t_code_patient_to_operator_id *p_code_patient_to_operator_id;

/* fin helpers */

typedef void LILLY_CALL_CONVENTION t_set_current_operator_id(const struct t_lilly_db_session_manager *self,const uint32 operator_id);
typedef t_set_current_operator_id *p_set_current_operator_id;

typedef uint32 LILLY_CALL_CONVENTION t_get_current_operator_id(const struct t_lilly_db_session_manager *self);
typedef t_get_current_operator_id *p_get_current_operator_id;

typedef uint32 LILLY_CALL_CONVENTION t_get_current_session_id(const struct t_lilly_db_session_manager *self);
typedef t_get_current_session_id *p_get_current_session_id;

typedef boolean LILLY_CALL_CONVENTION t_load_lilly_engine(const struct t_lilly_db_session_manager *self,const puchar engine_database_path);
typedef t_load_lilly_engine *p_load_lilly_engine;

typedef void LILLY_CALL_CONVENTION t_release_lilly_engine(const struct t_lilly_db_session_manager *self,const uint32 database_id);
typedef t_release_lilly_engine *p_release_lilly_engine;

// penser à passer les new db, purge db par cet engin

#pragma pack(push,1)

typedef struct t_lilly_db_session_manager {
											unsigned_int error_code;
											opaque_ptr rtm_params;
											unsigned_int rtm_params_size;
											p_register_lilly_engine register_lilly_engine;
											p_load_lilly_engine load_lilly_engine;
											p_release_lilly_engine release_lilly_engine;
											p_request_lilly_engine request_lilly_engine;
											p_request_db_handle request_db_handle;
											p_code_to_record code_to_record;
											p_record_id_to_consultation_record record_id_to_consultation_record;
											p_delete_consultation delete_consultation;
											p_delete_consultation_ex delete_consultation_ex;
											p_delete_patient delete_patient;
											p_delete_patient_ex delete_patient_ex;
											/* helpers */
											p_record_id_to_name record_id_to_name;
											p_operator_name_to_id operator_name_to_id;
											p_doctor_name_to_id doctor_name_to_id;
											p_code_patient_to_operator_id code_patient_to_operator_id;
											/* fin helpers */
											p_set_current_operator_id set_current_operator_id;
											p_get_current_operator_id get_current_operator_id;
											p_get_current_session_id get_current_session_id;
										  } *p_lilly_db_session_manager;

#pragma pack(pop)

#define LILLY_SESSION_MANAGER_INIT_ERROR         3000
#define LILLY_SESSION_MANAGER_ENGINE_UNLOADED    3001
#define LILLY_SESSION_MANAGER_DB_UNLOADED        3002
#define LILLY_SESSION_MANAGER_BAD_ID_ERROR       3003
#define LILLY_SESSION_MANAGER_UNSUPPORTED_ID     3004

extern p_lilly_db_session_manager LILLY_CALL_CONVENTION get_new_session_manager(const uint32 session_id,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_session_manager(const p_lilly_db_session_manager session_manager);


#ifdef __cplusplus
}
#endif

#endif