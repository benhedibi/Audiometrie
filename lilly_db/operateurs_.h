#ifndef OPERATEUR_H
#define OPERATEUR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db.h>

#pragma pack(push,1)

typedef struct {
				 t_lilly_db_record_id code_operateur;
				 uchar nom_prenom[48];
				 uchar phone_principal[32];
				 uchar phone_secondaire[32];
				 uchar email[64];
                 uint32 picture_blob_id;
			   } t_operateur_record,*p_operateur_record;


#pragma pack(pop)

#define OPERATEUR_RECORD_SIZE (unsigned_int)(sizeof(t_operateur_record))

extern p_lilly_db_handle operator_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code);
extern p_lilly_db_handle operator_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code);
extern void operator_db_close_database(const p_lilly_db_handle db_handle);
extern boolean operator_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path);

extern boolean operator_db_append_record(const p_lilly_db_handle db_handle,const p_operateur_record record);
extern boolean operator_db_edit_record(const p_lilly_db_handle db_handle,const p_operateur_record record,const uint64 record_offset);
extern boolean operator_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset);

extern p_operateur_record operator_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);
extern p_operateur_record operator_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);

extern p_operateur_record operator_db_codeop_to_record(const p_lilly_db_handle db_handle,const uint32 codeop);

extern uint32 operator_db_get_record_crc(const p_lilly_db_handle db_handle,const p_operateur_record record);


#ifdef __cplusplus
}
#endif

#endif