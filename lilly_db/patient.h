#ifndef PATIENT_H
#define PATIENT_H


#ifdef __cplusplus
extern "C" {
#endif

#include <lilly_db.h>

#pragma pack(push,1)

typedef struct {
				 t_lilly_db_record_id code_patient;
				 t_date_time date_naissance;
				 uint8 sexe;
				 uint8 age_consultation;
				 uint8 taille;
				 uint8 poids;
				 uint8 gouvernorat;
				 uint8 pays;
				 uint16 reserved; // alignment purpose
				 uint32 code_medecin;
                 uint32 picture_blob_id;
				 uint32 observation_blob_id;
                 uint32 alignment_reserved; // pour aligner en 64 bits
                 uchar nom_prenom[64];
				 uchar ville[32];
				 uchar phone_principal[32];
				 uchar phone_secondaire[32];
				 uchar email[64];
				 uchar travail[64];
			   } t_patient_record,*p_patient_record;

#pragma pack(pop)

#define PATIENT_RECORD_SIZE (unsigned_int)(sizeof(t_patient_record))

extern p_lilly_db_handle patient_db_new_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const uint32 session_id,const uint64 databse_flags,const punsigned_int error_code);
extern p_lilly_db_handle patient_db_load_database(const puchar database_path,const unsigned_int db_path_len,const uint32 operator_id,const punsigned_int error_code);
extern void patient_db_close_database(const p_lilly_db_handle db_handle);
extern boolean patient_db_save_database(const p_lilly_db_handle db_handle,const puchar database_path);

extern boolean patient_db_append_record(const p_lilly_db_handle db_handle,const p_patient_record record);
extern boolean patient_db_edit_record(const p_lilly_db_handle db_handle,const p_patient_record record,const uint64 record_offset);
extern boolean patient_db_delete_record(const p_lilly_db_handle db_handle,const uint64 record_offset);

extern p_patient_record patient_db_get_filtered_first_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);
extern p_patient_record patient_db_get_filtered_next_record(const p_lilly_db_handle db_handle,const opaque_ptr filter_params);

extern p_patient_record patient_db_codepat_to_record(const p_lilly_db_handle db_handle,const uint32 codepat);

extern uint32 patient_db_get_record_crc(const p_lilly_db_handle db_handle,const p_patient_record record);


#ifdef __cplusplus
}

#endif

#endif