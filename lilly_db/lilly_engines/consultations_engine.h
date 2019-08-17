#ifndef CONSULTATIONS_ENGINE_H
#define CONSULTATIONS_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


#pragma pack(push,1)

typedef struct {
				 t_lilly_db_record_id code_consultation;
				 uint32 patient_id;
				 uint32 medecin_id;
				 uint32 audiogram_id;
				 uint32 tympanogram_id;
				 uint32 gainp_id;
				 uint32 audiovoc_id;
			   } t_consultation_record,*p_consultation_record; // 32 bytes

#pragma pack(pop)


#define CONSULTATION_RECORD_SIZE sizeof(t_consultation_record)


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_consultations_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_consultations_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif