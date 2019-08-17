#ifndef DOCTORS_ENGINE_H
#define DOCTORS_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


#pragma pack(push,1)


typedef struct {
				 t_lilly_db_record_id code_medecin;
				 uchar nom_prenom[48];
				 uint8 gouvernorat;
				 uint8 pays;
                 uint8 type;
				 uint8 reserved[5];
				 uchar ville[32];
				 uchar phone_principal[32];
				 uchar phone_secondaire[32];
				 uchar fax[32];
				 uchar email[64];
			   } t_medecin_record,*p_medecin_record; // taille 256 bytes


#pragma pack(pop)


#define MEDECIN_RECORD_SIZE sizeof(t_medecin_record)

#define MEDECIN_PRIVE_TYPE 0
#define HOPITAL_TYPE       1
#define CLINIQUE_TYPE      2


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_doctors_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_doctors_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif