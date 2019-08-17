#ifndef OPERATORS_ENGINE_H
#define OPERATORS_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


#pragma pack(push,1)

typedef struct {
				 t_lilly_db_record_id code_operateur;
				 uchar nom_prenom[48];
				 uchar phone_principal[32];
				 uchar phone_secondaire[32];
				 uchar email[64];
			   } t_operateur_record,*p_operateur_record;

#pragma pack(pop)


#define OPERATEUR_RECORD_SIZE sizeof(t_operateur_record)


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_operators_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_operators_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif