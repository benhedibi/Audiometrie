#include <lilly_session_manager.h>
#include <lilly_mem.h>
#include <lilly_io.h>
#include <lilly_utils.h>
#include <operators_engine.h>
#include <doctors_engine.h>
#include <patients_engine.h>
#include <audiograms_engine.h>
#include <tympano_engine.h>
#include <gainp_engine.h>
#include <audiovocs_engine.h>
#include <consultations_engine.h>
#include <db_signatures.h>

#include <cmnfnc.h>

typedef struct {
				 p_lilly_db_engine db_engine;
				 struct t_lilly_db_handle *db_handle;
			   } t_session_db_tulple,*p_session_db_tulpe;

typedef struct {
				 uint32 operator_id;
				 uint32 session_id;
				 unsigned_int flags;
				 unsigned_int tulpes_count;
				 t_session_db_tulple db_tulpes[16];
			   } t_session_manager_rtm_params,*p_session_manager_rtm_params;


#define DB_SIGNATURE_TO_TULPE_INDEX(db_signature) (uint8)((db_signature))
#define IS_VALID_TULPE_INDEX(index) ((index) <= 7)

static p_session_db_tulpe LILLY_CALL_CONVENTION request_db_tulpe(const p_lilly_db_session_manager self,const uint32 database_signature)
{
  unsigned_int index;
  p_session_manager_rtm_params rtm;


	 self->error_code = ERROR_SUCCESS;

	 index = DB_SIGNATURE_TO_TULPE_INDEX(database_signature);

	 if (!IS_VALID_TULPE_INDEX(index))
	 {
	   self->error_code = LILLY_SESSION_MANAGER_BAD_ID_ERROR;
	   return NULL;
	 }

	 rtm = (p_session_manager_rtm_params)self->rtm_params;

	 return (p_session_db_tulpe)&rtm->db_tulpes[index];

	 //return &((p_session_manager_rtm_params)self->rtm_params)->db_tulpes[index];

}

static p_lilly_db_engine LILLY_CALL_CONVENTION load_engine(const p_lilly_db_session_manager self,const uint32 db_signature)
{
  p_lilly_db_engine db_engine;

	 self->error_code = ERROR_SUCCESS;


	 switch (db_signature)
	 {
				 case OPERATOR_DB_SIGNATURE : db_engine = get_operators_db_engine(self,&self->error_code);
											  break;

				  case PATIENT_DB_SIGNATURE : db_engine = get_patients_db_engine(self,&self->error_code);
											  break;

				   case DOCTOR_DB_SIGNATURE : db_engine = get_doctors_db_engine(self,&self->error_code);
											  break;

				case AUDIOGRAM_DB_SIGNATURE : db_engine = get_audiograms_db_engine(self,&self->error_code);
											  break;

			  case TYMPANOGRAM_DB_SIGNATURE : db_engine = get_tympano_db_engine(self,&self->error_code);
											  break;

		 case GAIN_PROTHETIQUE_DB_SIGNATURE : db_engine = get_gainp_db_engine(self,&self->error_code);
											  break;

	   case AUDIOMETRIE_VOCALE_DB_SIGNATURE : db_engine = get_audiovocs_db_engine(self,&self->error_code);
											  break;

			case CONSULTATIONS_DB_SIGNATURE : db_engine = get_consultations_db_engine(self,&self->error_code);
											  break;

									default : self->error_code = LILLY_SESSION_MANAGER_BAD_ID_ERROR;
											  db_engine = NULL;
											  break;
	 }

	 return db_engine;
}

static p_lilly_db_engine LILLY_CALL_CONVENTION register_lilly_engine(const p_lilly_db_session_manager self,const uint32 engine_id)
{
  p_lilly_db_engine db_engine;
  p_session_db_tulpe db_tulpe;


	 self->error_code = ERROR_SUCCESS;

	 db_tulpe = request_db_tulpe(self,engine_id);

	 if (!db_tulpe) return NULL;

	 if (!db_tulpe->db_engine)
	 {
	   db_tulpe->db_engine = load_engine(self,engine_id);
     }

	 return db_tulpe->db_engine;
}

static boolean LILLY_CALL_CONVENTION load_lilly_engine(const p_lilly_db_session_manager self,const puchar engine_database_path)
{
  p_session_db_tulpe db_tulpe;
  unsigned_int fhandle;
  uint32 db_signature;


	 if (!self) return FALSE;

	 self->error_code = ERROR_SUCCESS;

	 if (!engine_database_path)
	 {
	   self->error_code = API_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_file_exists(engine_database_path))
	 {
	   self->error_code = IO_ERROR;
	   return FALSE;
	 }

	 fhandle = lilly_io_open_file(engine_database_path,lilly_io_fmOpen,lilly_io_faRead);

	 if ((signed_int)fhandle <= 0)
	 {
	   self->error_code = IO_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_file_read(fhandle,(puchar)&db_signature,sizeof(db_signature)))
	 {
	   self->error_code = IO_ERROR;
	 }

	 lilly_io_close_file(fhandle);

     if (self->error_code != ERROR_SUCCESS) return FALSE;

	 db_tulpe = request_db_tulpe(self,db_signature);

	 if (!db_tulpe) return FALSE;

	 if (!db_tulpe->db_engine)
	 {
	   db_tulpe->db_engine = load_engine(self,db_signature);
	   if (!db_tulpe->db_engine) return FALSE;
	 }

	 if (!db_tulpe->db_handle)
	 {
	   db_tulpe->db_handle = db_tulpe->db_engine->load_database(db_tulpe->db_engine,engine_database_path,avcore_wstrlen(engine_database_path) * 2,
	   ((p_session_manager_rtm_params)self->rtm_params)->operator_id,((p_session_manager_rtm_params)self->rtm_params)->session_id);

	   if (!db_tulpe->db_handle)
	   {
		 self->error_code = db_tulpe->db_engine->error_code;
		 return FALSE;
       }
	 }

	 return TRUE;
}

static void LILLY_CALL_CONVENTION release_lilly_engine(const p_lilly_db_session_manager self,const uint32 database_id)
{
  p_session_db_tulpe db_tulpe;


	 self->error_code = ERROR_SUCCESS;

	 db_tulpe = request_db_tulpe(self,database_id);

	 if (!db_tulpe) return;

	 if (db_tulpe->db_handle)
	 {
	   if (!db_tulpe->db_engine) // corner case, au cas où ;)
	   {
		 db_tulpe->db_engine = load_engine(self,database_id);

		 if (!db_tulpe->db_engine) return; // je peux plus faire plus
	   }

	   db_tulpe->db_engine->close_database(db_tulpe->db_engine,db_tulpe->db_handle);
	 }

	 if (db_tulpe->db_engine)
	 {
	   switch (database_id)
	   {
				 case OPERATOR_DB_SIGNATURE : release_operators_db_engine(db_tulpe->db_engine);
											  break;

				  case PATIENT_DB_SIGNATURE : release_patients_db_engine(db_tulpe->db_engine);
											  break;

				   case DOCTOR_DB_SIGNATURE : release_doctors_db_engine(db_tulpe->db_engine);
											  break;

				case AUDIOGRAM_DB_SIGNATURE : release_audiograms_db_engine(db_tulpe->db_engine);
											  break;

			  case TYMPANOGRAM_DB_SIGNATURE : release_tympano_db_engine(db_tulpe->db_engine);
											  break;

		 case GAIN_PROTHETIQUE_DB_SIGNATURE : release_gainp_db_engine(db_tulpe->db_engine);
											  break;

	   case AUDIOMETRIE_VOCALE_DB_SIGNATURE : release_audiovocs_db_engine(db_tulpe->db_engine);
											  break;

			case CONSULTATIONS_DB_SIGNATURE : release_consultations_db_engine(db_tulpe->db_engine);
											  break;
	   }
	 }

	 db_tulpe->db_engine = NULL;
	 db_tulpe->db_handle = NULL;

	 return;
}

static p_lilly_db_engine LILLY_CALL_CONVENTION request_lilly_engine(const p_lilly_db_session_manager self,const uint32 database_signature)
{
  p_session_db_tulpe db_tulpe;


	 self->error_code = ERROR_SUCCESS;

	 db_tulpe = request_db_tulpe(self,database_signature);

	 if (!db_tulpe) return NULL;

	 if (!db_tulpe->db_engine)
	 {
	   self->error_code = LILLY_SESSION_MANAGER_ENGINE_UNLOADED;
	 }

	 return db_tulpe->db_engine;
}

static struct t_lilly_db_handle* LILLY_CALL_CONVENTION request_db_handle(const p_lilly_db_session_manager self,const uint32 database_signature)
{
  p_session_db_tulpe db_tulpe;


     self->error_code = ERROR_SUCCESS;

	 db_tulpe = request_db_tulpe(self,database_signature);

	 if (!db_tulpe) return NULL;

	 if (!db_tulpe->db_handle)
	 {
	   self->error_code = LILLY_SESSION_MANAGER_DB_UNLOADED;
	 }

	 return db_tulpe->db_handle;

}

static opaque_ptr LILLY_CALL_CONVENTION code_to_record(const p_lilly_db_session_manager self,const uint32 engine_id,const uint32 code)
{
  p_session_db_tulpe db_tulpe;
  opaque_ptr record;


	 self->error_code = ERROR_SUCCESS;

	 db_tulpe = request_db_tulpe(self,engine_id);

	 if (!db_tulpe) return NULL;

	 if (!db_tulpe->db_engine)
	 {
	   self->error_code = LILLY_SESSION_MANAGER_ENGINE_UNLOADED;
	   return NULL;
	 }

	 if (!db_tulpe->db_handle)
	 {
	   self->error_code = LILLY_SESSION_MANAGER_DB_UNLOADED;
	   return NULL;
	 }

	 record = db_tulpe->db_engine->code_to_record(db_tulpe->db_engine,db_tulpe->db_handle,code);

	 self->error_code = db_tulpe->db_engine->error_code;

	 return record;

}

static puchar LILLY_CALL_CONVENTION record_id_to_name(const p_lilly_db_session_manager self,const uint32 engine_id,const uint32 record_id,const punsigned_int name_len)
{
  opaque_ptr record;
  puchar p;


	 if (!self) return NULL;

	 self->error_code = ERROR_SUCCESS;

	 switch (engine_id)
	 {
	   case OPERATOR_DB_SIGNATURE :
		case PATIENT_DB_SIGNATURE :
		 case DOCTOR_DB_SIGNATURE : break;

						  default : self->error_code = LILLY_SESSION_MANAGER_UNSUPPORTED_ID;
                                    return NULL;
	 }

	 record = self->code_to_record(self,engine_id,record_id);

	 if (!record) return 0;

     switch (engine_id)
	 {
	   case OPERATOR_DB_SIGNATURE : p = &((p_operateur_record)record)->nom_prenom[0];
									break;

		case PATIENT_DB_SIGNATURE : p = &((p_patient_record)record)->nom_prenom[0];
									break;

		 case DOCTOR_DB_SIGNATURE : p = &((p_medecin_record)record)->nom_prenom[0];
									break;
	 }

	 *name_len = avcore_wstrlen(p) * 2;

	 if (*name_len == 0)
	 {
	   self->error_code = FATAL_ERROR;
	   return 0;
	 }

	 return p;
}

static opaque_ptr LILLY_CALL_CONVENTION record_id_to_consultation_record(const p_lilly_db_session_manager self,const uint32 engine_id,const uint32 record_id)
{
  p_consultation_record iterator;
  struct t_lilly_db_handle *db_handle;
  boolean found;

	 if (!self) return NULL;

	 self->error_code = ERROR_SUCCESS;

	 if (!engine_id)
	 {
	   self->error_code = API_ERROR;
	   return NULL;
	 }

	 db_handle = self->request_db_handle(self,CONSULTATIONS_DB_SIGNATURE);

     if (!db_handle) return IO_ERROR;

	 iterator = (p_consultation_record)lilly_db_get_first_record(db_handle);

	 if (!iterator)
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return IO_ERROR;
	 }

	 found = FALSE;

	 while (TRUE)
	 {
	   switch (record_id)
	   {
				  case AUDIOGRAM_DB_SIGNATURE : found = (iterator->audiogram_id == record_id);
												break;

				case TYMPANOGRAM_DB_SIGNATURE : found = (iterator->tympanogram_id == record_id);
												break;

		   case GAIN_PROTHETIQUE_DB_SIGNATURE : found = (iterator->gainp_id == record_id);
												break;

		 case AUDIOMETRIE_VOCALE_DB_SIGNATURE : found = (iterator->audiovoc_id == record_id);
												break;

									  default : self->error_code = API_ERROR;
												return NULL;
	   }

	   if (found == TRUE)
	   {
		 return iterator;
	   }

	   iterator = (p_consultation_record)lilly_db_get_next_record(db_handle);

	   if (!iterator) break;
	 }

	 self->error_code = lilly_db_get_last_error(db_handle);

	 return NULL;

}

static boolean LILLY_CALL_CONVENTION delete_consultation_ex(const p_lilly_db_session_manager self,const struct t_lilly_db_handle* db_handle,const opaque_ptr consultation_record,const uint64 offset)
{
  p_consultation_record consult_record = (p_consultation_record)consultation_record;
  p_session_db_tulpe db_tulpe;
  signed_int i;
  uint64 rec_offset;
  uint32 table[4][2] = {{AUDIOGRAM_DB_SIGNATURE,0},{TYMPANOGRAM_DB_SIGNATURE,0},{GAIN_PROTHETIQUE_DB_SIGNATURE,0},{AUDIOMETRIE_VOCALE_DB_SIGNATURE,0}};
  t_lilly_db_blob_name blob_id;


	 if (!self) return FALSE;

	 self->error_code = ERROR_SUCCESS;

	 if ((!db_handle) || (!consult_record) || ((int64)offset <= 0))
	 {
	   self->error_code = API_ERROR;
	   return FALSE;
	 }

	 table[0][1] = consult_record->audiogram_id;
	 table[1][1] = consult_record->tympanogram_id;
	 table[2][1] = consult_record->gainp_id;
	 table[3][1] = consult_record->audiovoc_id;

	 for (i = 3; i >= 0; i--)
	 {
	   if (table[i][1] == 0) continue;

	   db_tulpe = request_db_tulpe(self,table[i][0]);

	   if (!db_tulpe) return FALSE;

	   if (!db_tulpe->db_engine)
	   {
		 self->error_code = LILLY_SESSION_MANAGER_ENGINE_UNLOADED;
		 return FALSE;
	   }

	   if (!db_tulpe->db_handle)
	   {
		 self->error_code = LILLY_SESSION_MANAGER_DB_UNLOADED;
		 return FALSE;
	   }

	   if (!db_tulpe->db_engine->code_to_record(db_tulpe->db_engine,db_tulpe->db_handle,table[i][1]))
	   {
		 self->error_code = db_tulpe->db_engine->error_code;
		 return FALSE;
	   }

	   rec_offset = lilly_db_get_current_record_offset(db_tulpe->db_handle);

	   if ((!lilly_db_record_id_to_blob_name_id(db_tulpe->db_handle,&blob_id,table[i][1],t_lilly_db_observations_confidentielles_blob_type)) ||
	   (!lilly_db_delete_blob(db_tulpe->db_handle,&blob_id)) || (!lilly_db_delete_record(db_tulpe->db_handle,rec_offset)))
	   {
		 self->error_code = lilly_db_get_last_error(db_tulpe->db_handle);
		 return FALSE;
	   }

	 }

	 if ((!lilly_db_record_id_to_blob_name_id(db_handle,&blob_id,consult_record->code_consultation.unique_index,t_lilly_db_observations_confidentielles_blob_type)) ||
	 (!lilly_db_delete_blob(db_handle,&blob_id)) || (!lilly_db_delete_record(db_handle,offset)))
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return FALSE;
	 }

	 return (self->error_code == ERROR_SUCCESS);
}

static boolean LILLY_CALL_CONVENTION delete_consultation(const p_lilly_db_session_manager self,const uint32 consultation_id)
{
  p_consultation_record consult_record;
  struct t_lilly_db_handle* db_handle;


	 if (!self) return FALSE;

	 self->error_code = ERROR_SUCCESS;

	 consult_record = self->code_to_record(self,CONSULTATIONS_DB_SIGNATURE,consultation_id);

	 if (!consult_record)
	 {
	   if (self->error_code == ERROR_SUCCESS)
	   {
		 self->error_code = LILLY_DB_RECORD_LOOKUP_ERROR;
	   }

       return FALSE;
	 }

	 db_handle = self->request_db_handle(self,CONSULTATIONS_DB_SIGNATURE);

	 if (!db_handle)
	 {
	   if (self->error_code == ERROR_SUCCESS)
	   {
		 self->error_code = LILLY_SESSION_MANAGER_DB_UNLOADED;
	   }

	   return FALSE;
	 }

	 return self->delete_consultation_ex(self,db_handle,consult_record,lilly_db_get_current_record_offset(db_handle));
}

static unsigned_int LILLY_CALL_CONVENTION delete_patient_ex(const p_lilly_db_session_manager self,const struct t_lilly_db_handle* db_handle,const opaque_ptr patient_record,const uint64 offset)
{
  p_patient_record pat_record = (p_patient_record)patient_record;
  p_consultation_record iterator;
  struct t_lilly_db_handle* consult_db_handle;
  unsigned_int result;
  t_lilly_db_blob_name blob_id;


	 if (!self) return 0;

	 self->error_code = ERROR_SUCCESS;

	 if ((!db_handle) || (!pat_record) || ((int64)offset <= 0))
	 {
	   self->error_code = API_ERROR;
	   return 0;
	 }

	 consult_db_handle = self->request_db_handle(self,CONSULTATIONS_DB_SIGNATURE);

	 if (!consult_db_handle)
	 {
	   if (self->error_code == ERROR_SUCCESS)
	   {
		 self->error_code = LILLY_SESSION_MANAGER_DB_UNLOADED;
	   }

	   return 0;
	 }

	 iterator = lilly_db_get_first_record(consult_db_handle);

	 if (!iterator)
	 {
	   self->error_code = lilly_db_get_last_error(consult_db_handle);
	   return 0;
	 }

	 result = 0;

	 while (TRUE)
	 {
	   if (pat_record->code_patient.unique_index == iterator->patient_id)
	   {
		 if (!self->delete_consultation_ex(self,consult_db_handle,iterator,lilly_db_get_current_record_offset(consult_db_handle))) return result;

         result++;
	   }

	   iterator = lilly_db_get_next_record(consult_db_handle);

	   if (!iterator) break;
	 }

	 self->error_code = lilly_db_get_last_error(consult_db_handle);

	 if (self->error_code != ERROR_SUCCESS) return result;

	 if ((!lilly_db_record_id_to_blob_name_id(db_handle,&blob_id,pat_record->code_patient.unique_index,t_lilly_db_observations_confidentielles_blob_type)) ||
	 (!lilly_db_delete_blob(db_handle,&blob_id)) || (!lilly_db_delete_record(db_handle,offset)))
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	 }

     return result;
}

static unsigned_int LILLY_CALL_CONVENTION delete_patient(const p_lilly_db_session_manager self,const uint32 patient_id)
{
  p_patient_record pat_record;
  struct t_lilly_db_handle* db_handle;

	 if (!self) return 0;

	 pat_record = self->code_to_record(self,PATIENT_DB_SIGNATURE,patient_id);

	 if (!pat_record)
	 {
	   if (self->error_code == ERROR_SUCCESS)
	   {
		 self->error_code = LILLY_DB_RECORD_LOOKUP_ERROR;
	   }

	   return 0;
	 }

	 db_handle = self->request_db_handle(self,PATIENT_DB_SIGNATURE);

	 if (!db_handle)
	 {
	   if (self->error_code == ERROR_SUCCESS)
	   {
		 self->error_code = LILLY_SESSION_MANAGER_DB_UNLOADED;
	   }

	   return 0;
	 }

	 return self->delete_patient_ex(self,db_handle,pat_record,lilly_db_get_current_record_offset(db_handle));
}


/* helpers pour le programme d'importation des bases DBASE */

static uint32 LILLY_CALL_CONVENTION operator_name_to_id(const p_lilly_db_session_manager self,const puchar name,const unsigned_int name_len)
{
  p_operateur_record iterator;
  struct t_lilly_db_handle *db_handle;

	 self->error_code = ERROR_SUCCESS;

	 if ((!name) || (*name == 0) || ((signed_int)name_len <= 0) || (name_len > sizeof(iterator->nom_prenom)))
	 {
	   self->error_code = API_ERROR;
	   return IO_ERROR;
	 }

	 db_handle = self->request_db_handle(self,OPERATOR_DB_SIGNATURE);

	 if (!db_handle) return IO_ERROR;

	 iterator = (p_operateur_record)lilly_db_get_first_record(db_handle);

	 if (!iterator)
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return IO_ERROR;
	 }

	 while (TRUE)
	 {
	   if (avcore_cmpWString(name,(puchar)&iterator->nom_prenom,name_len))
	   {
		 return iterator->code_operateur.unique_index;
	   }

	   iterator = (p_operateur_record)lilly_db_get_next_record(db_handle);

       if (!iterator) break;
     }

	 self->error_code = lilly_db_get_last_error(db_handle);

	 return IO_ERROR;
}

static uint32 LILLY_CALL_CONVENTION doctor_name_to_id(const p_lilly_db_session_manager self,const puchar name,const unsigned_int name_len)
{
  p_medecin_record iterator;
  struct t_lilly_db_handle *db_handle;

	 self->error_code = ERROR_SUCCESS;

	 if ((!name) || (*name == 0) || ((signed_int)name_len <= 0) || (name_len > sizeof(iterator->nom_prenom)))
	 {
	   self->error_code = API_ERROR;
	   return IO_ERROR;
	 }

	 db_handle = self->request_db_handle(self,DOCTOR_DB_SIGNATURE);

	 if (!db_handle) return IO_ERROR;

	 iterator = (p_medecin_record)lilly_db_get_first_record(db_handle);

	 if (!iterator)
	 {
	   self->error_code = lilly_db_get_last_error(db_handle);
	   return IO_ERROR;
	 }

	 while (TRUE)
	 {
	   if (avcore_cmpWString(name,(puchar)&iterator->nom_prenom,name_len))
	   {
		 return iterator->code_medecin.unique_index;
	   }

	   iterator = (p_medecin_record)lilly_db_get_next_record(db_handle);

       if (!iterator) break;
     }

	 self->error_code = lilly_db_get_last_error(db_handle);

	 return IO_ERROR;
}

static uint32 LILLY_CALL_CONVENTION code_patient_to_operator_id(const struct t_lilly_db_session_manager *self,const uint32 codep)
{

}

/*    fin helpers */

static void LILLY_CALL_CONVENTION set_current_operator_id(const p_lilly_db_session_manager self,const uint32 operator_id)
{

	if (!self) return;

	self->error_code = ERROR_SUCCESS;

	if (!self->rtm_params)
	{
	  self->error_code = LILLY_SESSION_MANAGER_INIT_ERROR;
	}
	else ((p_session_manager_rtm_params)self->rtm_params)->operator_id = operator_id;

	return;
}

static uint32 LILLY_CALL_CONVENTION get_current_operator_id(const p_lilly_db_session_manager self)
{

	if (!self) return 0;

	self->error_code = ERROR_SUCCESS;

	if (!self->rtm_params)
	{
	  self->error_code = LILLY_SESSION_MANAGER_INIT_ERROR;
	  return 0;
	}

	return ((p_session_manager_rtm_params)self->rtm_params)->operator_id;

}

static uint32 LILLY_CALL_CONVENTION get_current_session_id(const p_lilly_db_session_manager self)
{

	if (!self) return 0;

	self->error_code = ERROR_SUCCESS;

	if (!self->rtm_params)
	{
	  self->error_code = LILLY_SESSION_MANAGER_INIT_ERROR;
	  return 0;
	}

	return ((p_session_manager_rtm_params)self->rtm_params)->session_id;
}

p_lilly_db_session_manager LILLY_CALL_CONVENTION get_new_session_manager(const uint32 session_id,const punsigned_int error_code)
{
  p_session_manager_rtm_params rtm_params;
  p_lilly_db_session_manager session_manager;


	 if (!error_code) return NULL;

	 rtm_params = (p_session_manager_rtm_params)lilly_malloc(sizeof(*rtm_params));

	 if (!rtm_params)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   return NULL;
     }

	 avcore_memset(rtm_params,0,sizeof(*rtm_params));

	 rtm_params->session_id = session_id;

	 session_manager = (p_lilly_db_session_manager)lilly_malloc(sizeof(*session_manager));

	 if (!session_manager)
	 {
       *error_code = MEM_ALLOC_ERROR;
	   return NULL;
     }

	 session_manager->error_code = ERROR_SUCCESS;

	 session_manager->rtm_params = rtm_params;
	 session_manager->rtm_params_size = sizeof(*rtm_params);

     session_manager->register_lilly_engine = (p_register_lilly_engine)register_lilly_engine;
	 session_manager->load_lilly_engine = (p_load_lilly_engine)load_lilly_engine;
     session_manager->release_lilly_engine = (p_release_lilly_engine)release_lilly_engine;
	 session_manager->request_lilly_engine = (p_request_lilly_engine)request_lilly_engine;
	 session_manager->request_db_handle = (p_request_db_handle)request_db_handle;
	 session_manager->code_to_record = (p_code_to_record)code_to_record;
	 session_manager->record_id_to_name = (p_record_id_to_name)record_id_to_name;
	 session_manager->record_id_to_consultation_record = (p_record_id_to_consultation_record)record_id_to_consultation_record;
	 session_manager->delete_consultation = (p_delete_consultation)delete_consultation;
	 session_manager->delete_consultation_ex = (p_delete_consultation_ex)delete_consultation_ex;
	 session_manager->delete_patient = (p_delete_patient)delete_patient;
     session_manager->delete_patient_ex = (p_delete_patient_ex)delete_patient_ex;
	 session_manager->operator_name_to_id = (p_operator_name_to_id)operator_name_to_id;
	 session_manager->doctor_name_to_id = (p_doctor_name_to_id)doctor_name_to_id;
     session_manager->code_patient_to_operator_id = (p_code_patient_to_operator_id)code_patient_to_operator_id;
	 session_manager->set_current_operator_id = (p_set_current_operator_id)set_current_operator_id;
	 session_manager->get_current_operator_id = (p_get_current_operator_id)get_current_operator_id;
	 session_manager->get_current_session_id = (p_get_current_session_id)get_current_session_id;

     return session_manager;

}

void LILLY_CALL_CONVENTION release_session_manager(const p_lilly_db_session_manager session_manager)
{

	 if (session_manager)
	 {
	   if ((session_manager->rtm_params) && ((signed_int)session_manager->rtm_params_size > 0))
	   {
		 avcore_memset(session_manager->rtm_params,0,session_manager->rtm_params_size);
		 lilly_free(session_manager->rtm_params,session_manager->rtm_params_size);
	   }

	   avcore_memset(session_manager,0,sizeof(*session_manager));

       lilly_free(session_manager,sizeof(*session_manager));
	 }

     return;

}