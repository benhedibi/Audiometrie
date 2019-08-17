#ifndef TYMPANO_ENGINE_H
#define TYMPANO_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


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
			   } t_tympanogram_record,*p_tympanogram_record; // total 144 bytes


#pragma pack(pop)


#define TYMPANOGRAM_RECORD_SIZE sizeof(t_tympanogram_record)


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_tympano_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_tympano_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif