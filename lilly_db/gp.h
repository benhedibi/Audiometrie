#ifndef GAINP_H
#define GAINP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db.h>

#pragma pack(push,1)

typedef struct {
				 uint8 sa[16];
				 uint8 sp[16];
				 uint8 mcl[16];
			   } t_gainp_mesures,*p_gainp_mesures;

typedef struct {
				 t_lilly_db_record_id code_gainp;
				 uint32 code_patient;
				 uint32 code_medecin;
				 t_gainp_mesures mesures;
                 uint8 oreille;
				 uint8 nature;
				 uint8 prothese;
				 uint8 appareil_id;
				 uint32 observation_blob_id;
			   } t_gainp_record,*p_gainp_record;


#pragma pack(pop)



#define GAINP_RECORD_SIZE sizeof(t_gainp_record)


#define GAINP_OREILLE_DROITE       (1 << 1)
#define GAINP_OREILLE_GAUCHE       (1 << 2)
#define GAINP_OREILLE_CHAMPS_LIBRE (1 << 3)

#define GAINP_NATURE_SON_PULSE 0
#define GAINP_NATURE_SON_PURE  1
#define GAINP_NATURE_SON_BLANC 2

#define GAINP_PROTHESE_TYPE_CONTOUR 0
#define GAINP_PROTHESE_TYPE_INTRA   1
#define GAINP_PROTHESE_TYPE_RIC     2


extern p_lilly_db_handle gainp_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code);
extern p_lilly_db_handle gainp_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code);
extern void gainp_db_close_database(const p_lilly_db_handle db_handle);
extern boolean gainp_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path);

extern boolean gainp_db_append_record(const p_lilly_db_handle db_handle,const p_gainp_record record);
extern boolean gainp_db_edit_record(const p_lilly_db_handle db_handle,const p_gainp_record record,const uint64 record_offset);
extern boolean gainp_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset);

extern p_gainp_record gainp_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);
extern p_gainp_record gainp_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);

extern p_gainp_record gainp_db_codegain_to_record(const p_lilly_db_handle db_handle,const uint32 codegain);

extern uint32 gainp_db_get_record_crc(const p_lilly_db_handle db_handle,const p_gainp_record record);


#ifdef __cplusplus
}
#endif

#endif
