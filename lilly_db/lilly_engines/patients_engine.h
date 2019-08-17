#ifndef PATIENTS_ENGINE_H
#define PATIENTS_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


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
                 uint32 last_consultation_id; // pour aligner en 64 bits
				 //uint32 consultations[40];
				 uchar nom_prenom[64];
				 uchar ville[32];
				 uchar phone_principal[32];
				 uchar phone_secondaire[32];
				 uchar email[64];
				 uchar travail[64];
			   } t_patient_record,*p_patient_record; // taille 512 bytes !

#pragma pack(pop)

#define PATIENT_RECORD_SIZE sizeof(t_patient_record)

#define MALE_GENDER   0
#define FEMALE_GENDER 1


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_patients_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_patients_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif