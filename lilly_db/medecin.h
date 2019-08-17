#ifndef MEDECIN_H
#define MEDECIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db.h>

#pragma pack(push,1)


typedef struct {
				 t_lilly_db_record_id code_medecin;
				 uchar nom_prenom[48];
				 uint8 gouvernorat;
				 uint8 pays;
                 uint8 reserved[6];
				 uchar ville[32];
				 uchar phone_principal[32];
				 uchar phone_secondaire[32];
				 uchar fax[32];
				 uchar email[64];
			   } t_medecin_record,*p_medecin_record; // taille 256 bytes


#pragma pack(pop)


#define MEDECIN_RECORD_SIZE (unsigned_int)(sizeof(t_medecin_record))


extern p_lilly_db_handle doctor_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code);
extern p_lilly_db_handle doctor_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code);
extern void doctor_db_close_database(const p_lilly_db_handle db_handle);
extern boolean doctor_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path);

extern boolean doctor_db_append_record(const p_lilly_db_handle db_handle,const p_medecin_record record);
extern boolean doctor_db_edit_record(const p_lilly_db_handle db_handle,const p_medecin_record record,const uint64 record_offset);
extern boolean doctor_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset);

extern p_medecin_record doctor_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);
extern p_medecin_record doctor_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);

extern p_medecin_record doctor_db_codemed_to_record(const p_lilly_db_handle db_handle,const uint32 codemed);

extern uint32 doctor_db_get_record_crc(const p_lilly_db_handle db_handle,const p_medecin_record record);


#ifdef __cplusplus
}
#endif

#endif