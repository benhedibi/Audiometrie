#ifndef GAINP_ENGINE_H
#define GAINP_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


#pragma pack(push,1)


typedef struct {
				 uint8 sa[16];
				 uint8 sp[16];
				 uint8 mcl[16];
			   } t_gainp_mesures,*p_gainp_mesures;

typedef struct {
				 t_lilly_db_record_id code_gainp; // 8
				 uint32 code_patient; // 4
				 uint32 code_medecin; // 4
				 t_gainp_mesures mesures; // 48
				 uint8 oreille;
				 uint8 nature;
				 uint8 prothese;
				 uint8 reserved; // 4
				 uint16 appareil_id;  // 2
				 uint16 reserved2;
			   } t_gainp_record,*p_gainp_record; // 72 bytes


#pragma pack(pop)


#define GAINP_RECORD_SIZE sizeof(t_gainp_record)


#define GAINP_OREILLE_DROITE       (1 << 1)
#define GAINP_OREILLE_GAUCHE       (1 << 2)
#define GAINP_OREILLE_CHAMPS_LIBRE 1

#define GAINP_NATURE_SON_PULSE 0
#define GAINP_NATURE_SON_PURE  1
#define GAINP_NATURE_SON_BLANC 2

#define GAINP_PROTHESE_TYPE_CONTOUR 0
#define GAINP_PROTHESE_TYPE_INTRA   1
#define GAINP_PROTHESE_TYPE_RIC     2


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_gainp_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_gainp_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif