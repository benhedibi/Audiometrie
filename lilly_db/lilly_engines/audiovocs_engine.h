#ifndef AUDIOVOCS_ENGINE_H
#define AUDIOVOCS_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


#pragma pack(push,1)

typedef struct {
				 uint8 valeurs[12];
				 uint32 reserved;
			   } t_audiovoc,*p_audiovoc;

typedef struct {
				 t_lilly_db_record_id code_audiovoc;
				 uint32 code_patient;
				 uint32 code_medecin;
				 t_audiovoc appareil_off;
                 t_audiovoc appareil_on;
				 uint8 oreille;
				 uint8 nature;
				 uint8 controle;
				 uint8 reserved;
				 uint32 reserved2;
               } t_audiovoc_record,*p_audiovoc_record;  // 56 bytes


#pragma pack(pop)


#define AUDIOVOC_RECORD_SIZE sizeof(t_audiovoc_record)

#define AUDIOVOC_NATURE_AVEC_LL 0
#define AUDIOVOC_NATURE_SANS_LL 1

#define AUDIOVOC_OREILLE_DROITE      (1 << 1)
#define AUDIOVOC_OREILLE_GAUCHE      (1 << 2)
#define AUDIOVOC_OREILLE_CHAMP_LIBRE 1

#define AUDIOVOC_CONTROLE_MONOSYLLABIQUE 0
#define AUDIOVOC_CONTROLE_DISSYLLABIQUE  1


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_audiovocs_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_audiovocs_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif