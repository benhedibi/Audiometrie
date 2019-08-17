#ifndef PATIENT_IMPORT_H
#define PATIENT_IMPORT_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_db_import.h>


extern struct t_lilly_db_handle* __fastcall patients_import_execute(const p_lilly_db_session_manager session_manager,const puchar source_path,const puchar destination_path,const unsigned_int destination_path_len,const uint64 db_flags,const uint32 operator_id,const uint32 session_id,const p_serializer_callback serializer_callback,const punsigned_int error_code,const puint32 bad_dates);



#ifdef __cplusplus
}
#endif

#endif