#ifndef FACES_ENGINE_H
#define FACES_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <lilly_engine.h>


#pragma pack(push,1)


typedef struct {
				 t_lilly_db_record_id code_face;
				 uint8 image_template_data[1040]; // as defined by luxand
			   } t_face_record,*p_face_record;


#pragma pack(pop)


#define FACE_RECORD_SIZE sizeof(t_face_record)


extern p_lilly_db_engine LILLY_CALL_CONVENTION get_faces_db_engine(const opaque_ptr session_manager,const punsigned_int error_code);
extern void LILLY_CALL_CONVENTION release_faces_db_engine(const p_lilly_db_engine db_engine);


#ifdef __cplusplus
}
#endif

#endif