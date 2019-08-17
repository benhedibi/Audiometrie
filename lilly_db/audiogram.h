#ifndef AUDIOGRAM_H
#define AUDIOGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db.h>

#pragma pack(push,1)


typedef struct {
				 uint8 va[16];
				 uint8 vo[16];
				 uint8 ucl[16];
			   } t_audiogram_oreille,*p_audiogram_oreille;

typedef struct {
				 t_lilly_db_record_id code_audiogram;
				 uint32 code_patient;
				 uint32 code_medecin;
				 uint64 parametres_confidentiels;
				 t_audiogram_oreille oreille_droite;
				 t_audiogram_oreille oreille_gauche;
                 uint8 weber[8];
                 uint32 observation_blob_id;
				 uint8 reserved[16];
			   } t_audiogram_record,*p_audiogram_record;


#pragma pack(pop)


#define AUDIOGRAM_RECORD_SIZE sizeof(t_audiogram_record)

#define AUDIOGRAM_STE_INNEE      (1 << 1)
#define AUDIOGRAM_STE_ACQUISE    (1 << 2)
#define AUDIOGRAM_STE_MIXTE_P    (1 << 3)
#define AUDIOGRAM_STE_MIXTE_T    (1 << 4)
#define AUDIOGRAM_PRESBYCOUSIE   (1 << 5)
#define AUDIOGRAM_HEREDITAIRE_P  (1 << 6)
#define AUDIOGRAM_MENIERE        (1 << 7)
#define AUDIOGRAM_BRUTALE        (1 << 8)
#define AUDIOGRAM_OTOTOXI        (1 << 9)
#define AUDIOGRAM_NEURINOME      (1 << 10)
#define AUDIOGRAM_APP            (1 << 11)
#define AUDIOGRAM_ACOUPHENES     (1 << 12)
#define AUDIOGRAM_PERCEPTION     (1 << 13)
#define AUDIOGRAM_OSM            (1 << 14)  // 14
#define AUDIOGRAM_OTITES         (1 << 15)
#define AUDIOGRAM_OTOSPONGIOSE   (1 << 16)
#define AUDIOGRAM_SONORE         (1 << 17)
#define AUDIOGRAM_BLAST          (1 << 18)
#define AUDIOGRAM_CRANIEN        (1 << 19)
#define AUDIOGRAM_MENINGITE      (1 << 20) // 20
#define AUDIOGRAM_FUMEUR         (1 << 21) //21
#define AUDIOGRAM_TYMPANOPLASTIE (1 << 22)




extern p_lilly_db_handle audiogram_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code);
extern p_lilly_db_handle audiogram_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code);
extern void audiogram_db_close_database(const p_lilly_db_handle db_handle);
extern boolean audiogram_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path);

extern boolean audiogram_db_append_record(const p_lilly_db_handle db_handle,const p_audiogram_record record);
extern boolean audiogram_db_edit_record(const p_lilly_db_handle db_handle,const p_audiogram_record record,const uint64 record_offset);
extern boolean audiogram_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset);

extern p_audiogram_record audiogram_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);
extern p_audiogram_record audiogram_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);

extern p_audiogram_record audiogram_db_codeaudiog_to_record(const p_lilly_db_handle db_handle,const uint32 codeaudiog);

extern uint32 audiogram_db_get_record_crc(const p_lilly_db_handle db_handle,const p_audiogram_record record);


#ifdef __cplusplus
}
#endif

#endif