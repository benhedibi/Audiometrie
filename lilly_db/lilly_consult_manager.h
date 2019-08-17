#ifndef CONSULTATION_H
#define CONSULTATION_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_db.h>

#pragma pack(push,1)


typedef struct {
				 t_lilly_db_record_id code_consultation;
				 uint32 code_patient;
				 uint32 code_medecin;
				 uint32 code_audiogramme;
				 uint32 code_tympanogramme;
				 uint32 code_audiogramme_vocal;
				 uint32 code_gain_prothetique;
				 uint32 observation_blob_id;
			   } t_consultation_record,*p_consultation_record;


#pragma pack(pop)


#define CONSULTATION_RECORD_SIZE (unsigned_int)(sizeof(t_consultation_record))





#ifdef __cplusplus
}
#endif

#endif