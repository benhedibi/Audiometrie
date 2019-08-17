#ifndef AUDIO_VOC_H
#define AUDIO_VOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db.h>

#pragma pack(push,1)

typedef struct {
				 uint8 valeurs[12];
				 uint32 reserved;
			   } t_audiovoc,*p_audiovoc;

typedef struct {
				 t_lilly_db_record_id code_audiovoc;
				 uint32 code_patient;
				 uint32 code_medecin;
				 t_audiovoc appareil_off;
                 t_audiovoc appareil_on;
				 uint8 oreille;
				 uint8 nature;
				 uint8 controle;
				 uint8 reserved;
				 uint32 observation_blob_id;
               } t_audiovoc_record,*p_audiovoc_record;  // 56 bytes


#pragma pack(pop)

#define AUDIOVOC_RECORD_SIZE sizeof(t_audiovoc_record)

#define AUDIOVOC_NATURE_AVEC_LL (1 << 1)
#define AUDIOVOC_NATURE_SANS_LL (1 << 2)

#define AUDIOVOC_OREILLE_DROITE 1
#define AUDIOVOC_OREILLE_GAUCHE 2

#define AUDIOVOC_CONTROLE_MONOSYLLABIQUE (1 << 1)
#define AUDIOVOC_CONTROLE_DYSSYLLABIQUE  (1 << 2)



extern p_lilly_db_handle audiovoc_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code);
extern p_lilly_db_handle audiovoc_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code);
extern void audiovoc_db_close_database(const p_lilly_db_handle db_handle);
extern boolean audiovoc_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path);

extern boolean audiovoc_db_append_record(const p_lilly_db_handle db_handle,const p_audiovoc_record record);
extern boolean audiovoc_db_edit_record(const p_lilly_db_handle db_handle,const p_audiovoc_record record,const uint64 record_offset);
extern boolean audiovoc_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset);

extern p_audiovoc_record audiovoc_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);
extern p_audiovoc_record audiovoc_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);

extern p_audiovoc_record audiovoc_db_codeaudiov_to_record(const p_lilly_db_handle db_handle,const uint32 codeaudiov);

extern uint32 audiovoc_db_get_record_crc(const p_lilly_db_handle db_handle,const p_audiovoc_record record);

#ifdef __cplusplus
}
#endif

#endif