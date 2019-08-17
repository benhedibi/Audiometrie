#ifndef TYMPANO_H
#define TYMPANO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db.h>

#pragma pack(push,1)


typedef struct {
				 float valeurs[13];
				 uint8 reflexes[4];
				 uint8 reserved[8];
			   } t_tympano_oreille,*p_tympano_oreille; // 64 bytes

typedef struct {
				 t_lilly_db_record_id code_tympanogram;
				 uint32 code_patient;
				 uint32 code_medecin;
				 t_tympano_oreille oreille_droite;
				 t_tympano_oreille oreille_gauche;
				 uint32 observation_blob_id;
				 uint32 reserved; // alignement
			   } t_tympanogram_record,*p_tympanogram_record; // total 152 bytes


#pragma pack(pop)


#define TYMPANOGRAM_RECORD_SIZE sizeof(t_tympanogram_record)


extern p_lilly_db_handle tympanogram_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code);
extern p_lilly_db_handle tympanogram_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code);
extern void tympanogram_db_close_database(const p_lilly_db_handle db_handle);
extern boolean tympanogram_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path);

extern boolean tympanogram_db_append_record(const p_lilly_db_handle db_handle,const p_tympanogram_record record);
extern boolean tympanogram_db_edit_record(const p_lilly_db_handle db_handle,const p_tympanogram_record record,const uint64 record_offset);
extern boolean tympanogram_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset);

extern p_tympanogram_record tympanogram_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);
extern p_tympanogram_record tympanogram_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);

extern p_tympanogram_record tympanogram_db_codetymp_to_record(const p_lilly_db_handle db_handle,const uint32 codetymp);

extern uint32 tympanogram_db_get_record_crc(const p_lilly_db_handle db_handle,const p_tympanogram_record record);



#ifdef __cplusplus
}
#endif

#endif