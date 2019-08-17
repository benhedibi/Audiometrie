#ifndef TYMPANO_IMPORT_H
#define TYMPANO_IMPORT_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_db_import.h>


typedef float __fastcall t_str_to_float_callback(const puchar str);
typedef t_str_to_float_callback *p_str_to_float_callback;

extern struct t_lilly_db_handle* tympano_import_execute(const p_lilly_db_session_manager session_manager,const puchar source_path,const puchar destination_path,const unsigned_int destination_path_len,const uint64 db_flags,const uint32 operator_id,const uint32 session_id,const t_str_to_float_callback serializer_callback,const punsigned_int error_code);



#ifdef __cplusplus
}
#endif

#endif