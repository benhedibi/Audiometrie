#pragma hdrstop

#include "common.hpp"

#include <JPEG.hpp>

#include <lilly_db2.h>
#include <cmnfnc.h>

#include <operators_engine.h>
#include <doctors_engine.h>
#include <patients_engine.h>
#include <audiograms_engine.h>
#include <tympano_engine.h>
#include <gainp_engine.h>
#include <audiovocs_engine.h>

#include <db_signatures.h>


void __fastcall report_event(const UnicodeString event,const TMsgDlgType dlg_type,const boolean fatal)
{
  unsigned_int beep_value;


   switch (dlg_type)
   {

			case TMsgDlgType::mtWarning : beep_value = MB_ICONWARNING;
										  break;

			  case TMsgDlgType::mtError : beep_value = MB_ICONERROR;
										  break;

		case TMsgDlgType::mtInformation : beep_value = MB_ICONINFORMATION;
										  break;

	   case TMsgDlgType::mtConfirmation : beep_value = MB_ICONASTERISK;
										  break;

			 case TMsgDlgType::mtCustom :
								default : beep_value = IO_ERROR;
										  break;

   }

   MessageBeep(beep_value);

   MessageDlg(event,dlg_type,TMsgDlgButtons() << mbOK,0);

   if (fatal) Application->Terminate();

   return;

}

bool __fastcall ask_event(const UnicodeString event)
{

	if (event == "") return FALSE;

	return (MessageDlg(event,mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,0) == mrYes);
}

UnicodeString __fastcall error_code_to_string(const unsigned_int error_code)
{

	switch (error_code)
	{
		  case LILLY_DB_EMPTY_DATABASE_ERROR : return "Opération impossible, la base de données est encore vide !";

		case LILLY_DB_DUPLICATE_RECORD_ERROR : return "La fiche que vous essayez d'ajouter existe déjà dans la base de données !";

		  case LILLY_DB_IO_FILE_EXISTS_ERROR : return "Opération impossible, le fichier que vous avez spécifié existe déjà !";

			   case LILLY_DB_SIGNATURE_ERROR : return "Le fichier que vous essayer d'ouvrir n'est pas une base de données valide !";

				case LILLY_DB_IO_STATE_ERROR : return "Opération impossible, le moteur de la base de données n'a pas été initialisé correctement !";

	  case LILLY_DB_CORRUPTED_DATABASE_ERROR : return "Impossible de charger la base de données que vous avez spécifié, les données sont corrompues !";

	   case LILLY_DB_TAMPERED_DATABASE_ERROR : return "Impossible de charger la base de données que vous avez spécifié, les données sont altérées !";

	   case LILLY_DB_UNSPECIFIED_FATAL_ERROR :
			  case (unsigned_int)FATAL_ERROR : {
												 UnicodeString err_str = "Une erreur fatale est survenue, l'application va maintenant se terminer ! \n\r\n\r";
												 err_str = err_str + "Veuillez contacter le support technique.";
												 report_event(err_str,mtError,true);
												 return "";
											   }

		  case LILLY_DB_SERIALIZE_DATA_ERROR : return "Opération impossible à cause d'une erreur de serialization des données !";

          case LILLY_DB_USER_PRIVILEGE_ERROR : return "Impossible de charger la base de données spécifiée, vous n'avez pas les privilèges d'utilisation adéquats !";

				 case (unsigned_int)IO_ERROR : return "Une erreur IO est survenue, opération impossible !";

							  case API_ERROR : {
												 UnicodeString error_str = "Une erreur fatale est survenue au niveau de l'API du logiciel ! \n\r\n\r";
												 error_str = error_str + "Veuillez contacter le support technique.";
												 report_event(error_str,mtError,true);
												 return "";
											   }

						case MEM_ALLOC_ERROR : {
												 UnicodeString error_str = "Opération impossible, l'application est à court de mémoire RAM ! \n\r\n\r";
												 error_str = error_str + "Veuillez contacter le support technique.";
												 report_event(error_str,mtError,true);
												 return "";
											   }

				  case ERROR_NOT_IMPLEMENTED : {
												 UnicodeString error_str = "Fonctionalité indisponible ! \n\r\n\r";
												 error_str = error_str + "Veuillez contacter le support technique.";
												 return error_str;
											   }

									 default : break;
	}

	return "Erreur non spécifée !";
}

UnicodeString __fastcall date_to_string(const p_date_time date)
{
  UnicodeString result = "";


	if (date->day < 10)
	{
	  result = "0";
	}

	result = result + IntToStr((int)date->day) + "/";

	if (date->month < 10)
	{
	  result = result + "0";
	}

	result = result + IntToStr((int)date->month) + "/" + IntToStr((int)date->year);

    return result;

}

UnicodeString __fastcall datetime_to_string(const p_date_time datetime)
{
  UnicodeString date_str = "";


	if (!datetime->year) return "Non spécifiée";

	if (datetime->day < 10)
	{
	  date_str = "0";
    }

	date_str = date_str + IntToStr((int)datetime->day) + "/";

	if (datetime->month < 10)
	{
	  date_str = date_str + "0";
    }

	date_str = date_str + IntToStr((int)datetime->month) + "/" + IntToStr((int)datetime->year);

	if ((!datetime->hours) && (!datetime->minutes) && (!datetime->seconds)) return date_str;

	date_str = date_str + " à ";

	if (datetime->hours < 10)
	{
	  date_str = date_str + "0";
	}

	date_str = date_str + IntToStr((int)datetime->hours) + ":";

	if (datetime->minutes < 10)
	{
	  date_str = date_str + "0";
	}

	date_str = date_str + IntToStr((int)datetime->minutes) + ":";

	if (datetime->seconds < 10)
	{
	  date_str = date_str + "0";
	}

	date_str = date_str + IntToStr((int)datetime->seconds);

	return date_str;

}

bool __fastcall string_to_date_stamp(const puchar date_field,const int date_field_len,const p_date_time date_result)
{
  int i,sep_index;
  UnicodeString jours,mois,annee;
  uchar c;


	 if ((date_field_len < 6) || (date_field[0] == '/') || (date_field[0] == '-') || (date_field[date_field_len - 2] == '/') ||
	 (date_field[date_field_len - 4] == '/') || (date_field[date_field_len - 2] == '-') || (date_field[date_field_len - 4] == '-')) return false;

	 sep_index = 0;

	 jours = "";
	 mois = "";
	 annee = "";

	 for (i = 0; i < date_field_len; i += 2)
	 {
	   c = date_field[i];

	   if ((c == '/') || (c == '-'))
	   {
		 if (sep_index > 2) return false;
		 sep_index++;
		 continue;
       }

	   switch (sep_index)
	   {
		 case 0 : jours = jours + (WCHAR)c;
				  break;

		 case 1 : mois = mois + (WCHAR)c;
				  break;

		 case 2 : annee = annee + (WCHAR)c;
				  break;

	   }
	 }

	 avcore_memset(date_result,0,sizeof(*date_result));

   try
	 {
	   date_result->day = StrToInt(jours);
	   date_result->month = StrToInt(mois);
	   date_result->year = StrToInt(annee);
	 }

   __except(EXCEPTION_EXECUTE_HANDLER)
	 {
	   return false;
	 }

	 return true;
}

UnicodeString __fastcall format_name(UnicodeString name)
{
  UnicodeString str;
  bool do_it = true;

	 str = name;

	 for (int i = 1; i <= str.Length(); i++)
	 {
	   if (do_it)
	   {
		 str[i] = UpperCase(str[i])[1];
	   }
	   else str[i] = LowerCase(str[i])[1];

	   do_it = (str[i] == ' ');
	 }

	 return str;
}

bool __fastcall load_blob(const p_engine_entry engine_entry,TObject *object,const uint32 record_id,const t_lilly_db_blob_type blob_type)
{
  struct t_lilly_db_blob_handle* blob_handle;
  t_blob_buffer blob_buffer;
  t_lilly_db_blob_name blob_id;
  bool result;

	if (!lilly_db_record_id_to_blob_name_id(engine_entry->db_handle,&blob_id,record_id,blob_type))
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [RecID_to_BlobID] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
	  report_event(err_str,mtError,false);
	  return false;
	}

	blob_handle = lilly_db_open_blob(engine_entry->db_handle,&blob_id);

	if (!blob_handle)
	{
	  unsigned_int error_code = lilly_db_get_last_error(engine_entry->db_handle);

	  if (error_code != LILLY_DB_BLOB_OBJECT_NOT_FOUND)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [OpenBlob] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
		report_event(err_str,mtError,false);
	  }

	  return false;
	}

	blob_buffer.data = NULL;

	result = false;

  try
	{

	  blob_buffer.size = (unsigned_int)lilly_db_get_blob_data_size(blob_handle);

	  if ((signed_int)blob_buffer.size <= 0)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [GetBlobSize] ! Le moteur Blob a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_blob_last_error(blob_handle));
		report_event(err_str,mtError,false);
		return false;
	  }

	  blob_buffer.data = (puchar)malloc(blob_buffer.size);

	  if (!blob_buffer.data)
	  {
		report_event(error_code_to_string(MEM_ALLOC_ERROR),mtError,true);
		return false;
	  }

	  if (!lilly_db_read_blob(blob_handle,blob_buffer.data,blob_buffer.size))
	  {
		unsigned_int error_code = lilly_db_get_blob_last_error(blob_handle);

		if (error_code != ERROR_SUCCESS)
		{
		  UnicodeString err_str = "Une erreur est survenue au niveau de [ReadBlobData] ! Le moteur Blob a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(error_code);
		  report_event(err_str,mtError,false);
		}

		return false;
	  }

	  result = blob_buffer_to_component(&blob_buffer,object,blob_type);
	}

  __finally
	{
	  lilly_db_close_blob(blob_handle);

	  if (blob_buffer.data)
	  {
		free(blob_buffer.data);
      }
	}

    return result;
}

bool __fastcall add_blob(const p_engine_entry engine_entry,TObject *object,const uint32 record_id,const uint32 operator_id,const t_lilly_db_blob_type blob_type)
{
  t_blob_buffer blob_buffer;
  t_lilly_db_blob_name blob_id;
  bool result = false;

	if (!component_to_blob_buffer(&blob_buffer,object,blob_type)) return false;

  try
	{
	   if (!lilly_db_record_id_to_blob_name_id(engine_entry->db_handle,&blob_id,record_id,blob_type))
	   {
		 UnicodeString err_str = "Une erreur est survenue au niveau de [RecID_to_BlobID] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		 err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
		 report_event(err_str,mtError,false);
		 return false;
	   }

		if (!lilly_db_create_blob(engine_entry->db_handle,&blob_id,blob_buffer.data,blob_buffer.size,operator_id))
	   {
		 UnicodeString err_str = "Une erreur est survenue au niveau de [CreateBlob] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		 err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
		 report_event(err_str,mtError,false);
		 return false;
	   }

	   result = true;
	}

  __finally
	{
	  free(blob_buffer.data);
	}

    return result;
}

bool __fastcall delete_blob(const p_engine_entry engine_entry,const uint32 record_id,const t_lilly_db_blob_type blob_type)
{
  t_lilly_db_blob_name blob_id;


	if (!lilly_db_record_id_to_blob_name_id(engine_entry->db_handle,&blob_id,record_id,blob_type))
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [RecID_to_BlobID] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
	  report_event(err_str,mtError,false);
	  return false;
	}

	if (!lilly_db_delete_blob(engine_entry->db_handle,&blob_id))
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [DelBlob] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
	  report_event(err_str,mtError,false);
	  return false;
	}

	return true;
}

bool __fastcall update_blob(const p_engine_entry engine_entry,TObject *object,const uint32 record_id,const uint32 operator_id,const t_lilly_db_blob_type blob_type)
{

	return ((delete_blob(engine_entry,record_id,blob_type)) && (add_blob(engine_entry,object,record_id,operator_id,blob_type)));

}

bool __fastcall blob_buffer_to_component(const p_blob_buffer blob_buffer,TObject *component,const t_lilly_db_blob_type blob_type)
{


	switch (blob_type)
	{
							   case t_lilly_db_bin_blob_type : report_event(error_code_to_string(ERROR_NOT_IMPLEMENTED),mtWarning,false);
															   return false;

					 case t_lilly_db_notes_medecin_blob_type :
	  case t_lilly_db_observations_confidentielles_blob_type : {
																 UnicodeString str = "";

																 for (int i = 0; i < blob_buffer->size / 2; i++)
																 {
																   str = str + (WCHAR)blob_buffer->data[i * 2];
																 }

																 TMemo *memo = dynamic_cast<TMemo *>(component);

																 if (!memo)
																 {
																   report_event(error_code_to_string(API_ERROR),mtError,true);
																   return false;
																 }

																 memo->Lines->Add(str);

																 str.~UnicodeString();
															   }

															   break;

							 case t_lilly_db_photo_blob_type : {
																 TMemoryStream *mem_strm;
																 TImage *image = dynamic_cast<TImage *>(component);

																 if (!image)
																 {
																   report_event(error_code_to_string(API_ERROR),mtError,true);
																   return false;
																 }

																 mem_strm = new TMemoryStream;

																 try
																   {
																	 mem_strm->WriteBuffer(blob_buffer->data,blob_buffer->size);

																	 mem_strm->Position = 0;

																	 image->Picture->LoadFromStream(mem_strm);
																   }

																 __finally
																   {
																	 delete mem_strm;
																   }
															   }

															   break;

													 default : report_event(error_code_to_string(API_ERROR),mtError,true);
															   return false;
	}

	return true;

}

bool __fastcall component_to_blob_buffer(const p_blob_buffer blob_buffer,TObject *component,const t_lilly_db_blob_type blob_type)
{

	blob_buffer->size = 0;

	blob_buffer->data = NULL;

	switch (blob_type)
	{
							   case t_lilly_db_bin_blob_type : report_event(error_code_to_string(ERROR_NOT_IMPLEMENTED),mtWarning,false);
															   return false;

					 case t_lilly_db_notes_medecin_blob_type :
	  case t_lilly_db_observations_confidentielles_blob_type : {
																 TMemo *memo = dynamic_cast<TMemo *>(component);

																 if (!memo)
																 {
																   report_event(error_code_to_string(API_ERROR),mtError,true);
																   return false;
																 }

																 blob_buffer->size = memo->Lines->Text.Length() * 2;

																 if ((signed_int)blob_buffer->size <= 0)
																 {
																   report_event(error_code_to_string(API_ERROR),mtError,true);
																   return false;
																 }

																 blob_buffer->size += 2;

																 blob_buffer->data = (puchar)malloc(blob_buffer->size);

																 if (!blob_buffer->data)
																 {
																   report_event(error_code_to_string(MEM_ALLOC_ERROR),mtError,true);
                                                                   return false;
																 }

																 *(puint16)&blob_buffer->data[blob_buffer->size - 2] = 0;

																 avcore_memcpy(blob_buffer->data,(puchar)memo->Lines->Text.c_str(),blob_buffer->size - 2);
															   }

															   break;

							 case t_lilly_db_photo_blob_type : {
																 TMemoryStream *mem_strm;
																 TImage *image = dynamic_cast<TImage *>(component);

																 if (!image)
																 {
																   report_event(error_code_to_string(API_ERROR),mtError,true);
																   return false;
																 }

																 mem_strm = new TMemoryStream;

																 try
																   {
																	 image->Picture->SaveToStream(mem_strm);

																	 mem_strm->Position = 0;

																	 blob_buffer->size = (unsigned_int)mem_strm->Size;

																	 if ((signed_int)blob_buffer->size <= 0)
																	 {
																	   report_event("L'image que vous avez spécifié semble être corrompue !",mtError,false);
                                                                       return false;
																	 }

																	 blob_buffer->data = (puchar)malloc(blob_buffer->size);

																	 if (!blob_buffer->data)
																	 {
																	   report_event(error_code_to_string(MEM_ALLOC_ERROR),mtError,true);
                                                                       return false;
																	 }

																	 mem_strm->Write(blob_buffer->data,(int)blob_buffer->size);
																   }

																 __finally
																   {
																	 delete mem_strm;
																   }
															   }

															   break;

													 default : report_event(error_code_to_string(API_ERROR),mtError,true);
															   return false;
	}

	return true;
}

void __fastcall fill_combo_box(const p_session_params session_params,TComboBox *combo_box,const uint32 engine_signature)
{
  opaque_ptr record_ptr;
  struct t_lilly_db_handle *db_handle;
  puchar nom;

	 switch (engine_signature)
	 {
				 case OPERATOR_DB_SIGNATURE :
				   case DOCTOR_DB_SIGNATURE : if (engine_signature == OPERATOR_DB_SIGNATURE)
											  {
												db_handle = session_params->engines.operators_engine.db_handle;
											  }
											  else db_handle = session_params->engines.doctors_engine.db_handle;

											  record_ptr = lilly_db_get_first_record(db_handle);

											  if (!record_ptr)
											  {
												UnicodeString str;
												str = "Une erreur est survenue au niveau de [GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
												str = str + error_code_to_string(lilly_db_get_last_error(db_handle));
												report_event(str,mtError,true);
												break;
											  }

											  if (combo_box->Items->Count)
											  {
												combo_box->Items->Clear();
											  }

											  while (true)
											  {
												if (engine_signature == OPERATOR_DB_SIGNATURE)
												{
												  nom = (puchar)&((p_operateur_record)record_ptr)->nom_prenom;
												}
												else nom = (puchar)&((p_medecin_record)record_ptr)->nom_prenom;

												combo_box->Items->Add((PWCHAR)nom);

												record_ptr = lilly_db_get_next_record(db_handle);

												if (!record_ptr) break;
											  }

											  if (lilly_db_get_last_error(db_handle) != ERROR_SUCCESS)
											  {
                                                UnicodeString str;
												str = "Une erreur est survenue au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
												str = str + error_code_to_string(lilly_db_get_last_error(db_handle));
												report_event(str,mtError,true);
											  }

                                              break;

				case AUDIOGRAM_DB_SIGNATURE :
			  case TYMPANOGRAM_DB_SIGNATURE :
		 case GAIN_PROTHETIQUE_DB_SIGNATURE :
	   case AUDIOMETRIE_VOCALE_DB_SIGNATURE :
			case CONSULTATIONS_DB_SIGNATURE : report_event(error_code_to_string(ERROR_NOT_IMPLEMENTED),mtError,false);
											  break;

									default : report_event(error_code_to_string(API_ERROR),mtError,true);
											  break;
	 }

     return;
}

puint32 __fastcall Load_MedId_Table(const p_session_params session_params,TComboBox *combo_box)
{
  puint32 PatientPageMed_Ids;
  p_engine_entry med_entry;
  p_medecin_record med_record,pat_med_record;
  unsigned_int error_code;
  t_lilly_db_database_infos med_db_infos;


	med_entry = &session_params->engines.doctors_engine;

	if (!lilly_db_get_database_informations(med_entry->db_handle,&med_db_infos))
	{
	  UnicodeString err_str = "Erreur au niveau de [GetDabaseInformations] ! Le moteur Doctors a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(med_entry->db_handle));
	  report_event(err_str,mtError,true);
	  return NULL;
	}

	if (!med_db_infos.record_count) return NULL;

	PatientPageMed_Ids = (puint32)malloc(med_db_infos.record_count * sizeof(*PatientPageMed_Ids));

	if (!PatientPageMed_Ids)
	{
	  report_event(error_code_to_string(MEM_ALLOC_ERROR),mtError,true);
	  return NULL;
	}

	pat_med_record = NULL;

	if ((combo_box) && (session_params->engines.patients_engine.current_record))
	{
	  pat_med_record = (p_medecin_record)med_entry->engine->code_to_record(med_entry->engine, med_entry->db_handle,
	  ((p_patient_record)session_params->engines.patients_engine.current_record)->code_medecin);

	  if (!pat_med_record)
	  {
		UnicodeString err_str = "Localisation impossible de la fiche médecin associée à ce patient ! Le moteur médecins a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(med_entry->engine->error_code);
		report_event(err_str,mtError,true);
		return NULL;
	  }
	}

	med_record = (p_medecin_record)lilly_db_get_first_record(med_entry->db_handle);

	if (!med_record)
	{
	  UnicodeString err_str = "Erreur au niveau de [medecins/GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(med_entry->db_handle));
	  report_event(err_str,mtError,true);
	  return NULL;
	}

	int index = 0;
	int pat_med_index = -1;

	while (true)
	{
	  if ((combo_box) && (pat_med_record) && (pat_med_index < 0) && (avcore_memcmp(&pat_med_record->nom_prenom,&med_record->nom_prenom,avcore_wstrlen((puchar)&pat_med_record->nom_prenom) * 2)))
	  {
		pat_med_index = index;
	  }

	  PatientPageMed_Ids[index++] = med_record->code_medecin.unique_index;

	  med_record = (p_medecin_record)lilly_db_get_next_record(med_entry->db_handle);

	  if (!med_record) break;

	  if (index >= med_db_infos.record_count)
	  {
		report_event("Index out of range au niveau de la base de données des médecins. Veuillez contacter Ben Hedibi Hassène.",mtError,true);
		return NULL;
	  }
	}

	error_code = lilly_db_get_last_error(med_entry->db_handle);

	if (error_code != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Erreur au niveau de [medecins/GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(error_code);
	  report_event(err_str,mtError,true);
	  return false;
	}

	if (combo_box)
	{
      fill_combo_box(session_params,combo_box,DOCTOR_DB_SIGNATURE);
	  combo_box->ItemIndex = pat_med_index;
	}

	return PatientPageMed_Ids;
}

void __fastcall Unload_MedId_Table(const puint32 PatientPageMed_Ids)
{

	if (PatientPageMed_Ids)
	{
	  free(PatientPageMed_Ids);
	}

	return;
}

bool __fastcall load_old_data_to_listview(const p_session_params session_params,const uint32 engine_id,const uint32 patient_id,TListView *listview)
{
  p_engine_entry engine_entry;
  opaque_ptr iterator;
  uint32 current_consultation_id = 0;


    current_consultation_id--; // égal à moins 1, plus rapide que load register with 0xfffff...

	switch (engine_id)
	{
			   case AUDIOGRAM_DB_SIGNATURE : engine_entry = &session_params->engines.audiograms_engine;

											 if (engine_entry->current_record)
											 {
											   current_consultation_id = ((p_audiogram_record)engine_entry->current_record)->code_audiogram.unique_index;
											 }

											 break;

			 case TYMPANOGRAM_DB_SIGNATURE : engine_entry = &session_params->engines.tympanograms_engine;

											 if (engine_entry->current_record)
											 {
											   current_consultation_id = ((p_tympanogram_record)engine_entry->current_record)->code_tympanogram.unique_index;
											 }

											 break;

		case GAIN_PROTHETIQUE_DB_SIGNATURE : engine_entry = &session_params->engines.gainprots_engine;

											 if (engine_entry->current_record)
											 {
											   current_consultation_id = ((p_gainp_record)engine_entry->current_record)->code_gainp.unique_index;
											 }

											 break;

	  case AUDIOMETRIE_VOCALE_DB_SIGNATURE : engine_entry = &session_params->engines.audiovocs_engine;

											 if (engine_entry->current_record)
											 {
											   current_consultation_id = ((p_audiovoc_record)engine_entry->current_record)->code_audiovoc.unique_index;
											 }

											 break;

								   default : report_event(error_code_to_string(API_ERROR),mtError,true);
											 return false;
	}

	iterator = lilly_db_get_first_record(engine_entry->db_handle);

	if (iterator)
	{
	  uint64 offset;
	  p_operateur_record op_record;
	  int index;
	  uint32 codep,code_consultation;
	  t_lilly_db_time_stamp_informations time_stamp_infos;

      index = 0;

	  while (true)
	  {
		switch (engine_id)
		{
				   case AUDIOGRAM_DB_SIGNATURE : code_consultation = ((p_audiogram_record)iterator)->code_audiogram.unique_index;
												 codep = ((p_audiogram_record)iterator)->code_patient;
												 break;

				 case TYMPANOGRAM_DB_SIGNATURE : code_consultation = ((p_tympanogram_record)iterator)->code_tympanogram.unique_index;
												 codep = ((p_tympanogram_record)iterator)->code_patient;
												 break;

			case GAIN_PROTHETIQUE_DB_SIGNATURE : code_consultation = ((p_gainp_record)iterator)->code_gainp.unique_index;
												 codep = ((p_gainp_record)iterator)->code_patient;
												 break;

		  case AUDIOMETRIE_VOCALE_DB_SIGNATURE : code_consultation = ((p_audiovoc_record)iterator)->code_audiovoc.unique_index;
												 codep = ((p_audiovoc_record)iterator)->code_patient;
												 break;
        }

		if (codep == patient_id)
		{
		  if ((engine_entry->current_record) && (code_consultation == current_consultation_id)) goto next;

		  offset = lilly_db_get_current_record_offset(engine_entry->db_handle);

		  if (!lilly_db_get_record_time_stamp_infos(engine_entry->db_handle,offset,&time_stamp_infos))
		  {
			UnicodeString err_str = "Une erreur est survenue au niveau de [GetTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
			err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
			report_event(err_str,mtError,true);
			return false;
		  }

		  listview->Items->Add();
		  listview->Items->Item[index]->Caption = date_to_string(&time_stamp_infos.creation_stamp.time_stamp);

		  op_record = (p_operateur_record)session_params->engines.operators_engine.engine->code_to_record(session_params->engines.operators_engine.engine,
		  session_params->engines.operators_engine.db_handle,time_stamp_infos.creation_stamp.operator_id);

		  if (!op_record)
		  {
			UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur des opérateurs a retourné l'erreur suivante : \n\r\n\r";
			err_str = err_str + error_code_to_string(session_params->engines.operators_engine.engine->error_code);
			report_event(err_str,mtError,true);
			return false;
		  }

		  listview->Items->Item[index]->SubItems->Add((PWCHAR)&op_record->nom_prenom);

		  listview->Items->Item[index]->SubItems->Add(IntToStr((int)offset));

		  index++;
		}

		next :

		iterator = lilly_db_get_next_record(engine_entry->db_handle);

		if (!iterator) break;
	  }

	  if (lilly_db_get_last_error(engine_entry->db_handle) != ERROR_SUCCESS)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(engine_entry->db_handle));
		report_event(err_str,mtError,true);
		return false;
	  }
	}

	return true;
}

bool __fastcall load_grph_list(const p_engine_entry engine_entry,const uint32 engine_id,TComboBox *combo_box)
{
  TDef_Values *def_values;
  opaque_ptr data;
  bool result = false;


	switch (engine_id)
	{
			   case AUDIOGRAM_DB_SIGNATURE : def_values = new TAudiograms_Def_Values(engine_entry->grph_types_db_path,12);
											 break;

			 case TYMPANOGRAM_DB_SIGNATURE : def_values = new TTympanograms_Def_Values(engine_entry->grph_types_db_path,12);
											 break;

		case GAIN_PROTHETIQUE_DB_SIGNATURE : report_event(error_code_to_string(API_ERROR),mtError,true);
											 break;

	  case AUDIOMETRIE_VOCALE_DB_SIGNATURE : def_values = new TAudiovoc_Def_Values(engine_entry->grph_types_db_path,12);
											 break;

								   default : report_event(error_code_to_string(API_ERROR),mtError,true);
											 return false;
	}

  try
	{
	   if (def_values->GetLastError() != ERROR_SUCCESS)
	   {
		 UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(def_values->GetLastError());
		 report_event(str,mtError,true);
		 return false;
	   }

	   data = def_values->GetFirstData();

	   if (!data)
	   {
		 if (def_values->GetLastError() != ERROR_SUCCESS)
		 {
		   UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		   str = str + error_code_to_string(def_values->GetLastError());
		   report_event(str,mtError,true);
		   return false;
		 }

		 result = true;

		 return true;
	   }

	   while (true)
	   {
		 combo_box->Items->Add((PWCHAR)data);

		 data = def_values->GetNextData();

		 if (!data) break;
	   }

	   if (def_values->GetLastError() != ERROR_SUCCESS)
	   {
		 UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(def_values->GetLastError());
		 report_event(str,mtError,false);
		 return false;
	   }

	   result = true;
	}

  __finally
	{
	  delete def_values;
	}

    return result;
}

void __fastcall delete_grph_item(const p_engine_entry engine_entry,const uint32 engine_id,TComboBox *combo_box)
{
  TDef_Values *def_values;
  opaque_ptr data;


	if (combo_box->ItemIndex == -1) return;

	if (!ask_event("Êtes-vous sûres de vouloir supprimer le graphique type " + combo_box->Items[combo_box->ItemIndex].Text + " ?")) return;

    switch (engine_id)
	{
			   case AUDIOGRAM_DB_SIGNATURE : def_values = new TAudiograms_Def_Values(engine_entry->grph_types_db_path,12);
											 break;

			 case TYMPANOGRAM_DB_SIGNATURE : def_values = new TTympanograms_Def_Values(engine_entry->grph_types_db_path,12);
											 break;

		case GAIN_PROTHETIQUE_DB_SIGNATURE : report_event(error_code_to_string(API_ERROR),mtError,true);
											 break;

	  case AUDIOMETRIE_VOCALE_DB_SIGNATURE : def_values = new TAudiovoc_Def_Values(engine_entry->grph_types_db_path,12);
											 break;

								   default : report_event(error_code_to_string(API_ERROR),mtError,true);
											 return;
	}

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  if (!def_values->Delete(combo_box->ItemIndex))
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types [Delete] ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  combo_box->DeleteSelected();

	  report_event("Graphique type supprimé avec succès.",mtInformation,false);

	}

  __finally
	{
	  delete def_values;
	}

	return;
}

bool __fastcall set_opname_and_time(const p_engine_entry engine_entry,const uint32 engine_id,const opaque_ptr record,TLabel *op_lbl,TLabel *time_lbl)
{
	return false;
}

bool __fastcall load_image(TImage *image,const UnicodeString image_path)
{
  TMemoryStream *mem_strm = new TMemoryStream;

	try
	  {
		mem_strm->LoadFromFile(image_path);

		mem_strm->Position = 0;

		image->Picture->LoadFromStream(mem_strm);

	  }

	__finally
	  {
		delete mem_strm;
	  }

    return true;
}

#include <VCLTee.Chart.hpp>
#include <QRCtrls.hpp>

void __fastcall draw_chart_in_quickreport(const opaque_ptr chart_ptr,const opaque_ptr quick_report_image_ptr)
{
  TChart *chart = (TChart *)chart_ptr;
  TQRImage *quick_report_image = (TQRImage *)quick_report_image_ptr;
  TBitmap *bitmap = NULL; // = new TBitmap;
  TMemoryStream *mem_strm = NULL;


	if ((!chart_ptr) || (!quick_report_image_ptr))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	try
	  {
		// bitmap->Width = chart->Width;
		// bitmap->Height = chart->Height;

		 //chart->Draw(bitmap->Canvas,TRect(0,0,bitmap->Width,bitmap->Height));
		 bitmap = chart->TeeCreateBitmap(chart->Color,Rect(0,0,chart->Width,chart->Height),pf24bit,72);

		 if (!bitmap) return;

		 mem_strm = new TMemoryStream;

		 bitmap->SaveToStream(mem_strm);

		 delete bitmap;

		 bitmap = NULL;

		 mem_strm->Position = 0;

		 quick_report_image->Picture->LoadFromStream(mem_strm);
	  }

	__finally
	  {
		 if (mem_strm)
		 {
		   delete mem_strm;
		 }

		 if (bitmap)
		 {
		   delete bitmap;
		 }
	  }

	return;
}

void __fastcall resize_picture(TImage *image,const UnicodeString image_path)
{
  TBitmap *image_source = NULL;
  TMemoryStream *mem_strm = new TMemoryStream;


  try
	{
	  mem_strm->LoadFromFile(image_path);

	  mem_strm->Position = 0;

	  image_source = new TBitmap;

	  image_source->LoadFromStream(mem_strm);

	  delete mem_strm;

	  mem_strm = NULL;

	  image->Picture->Bitmap = new TBitmap;

	  image->Picture->Bitmap->Height = image->Height;
	  image->Picture->Bitmap->Width = image->Width;

	  resize_picture_ex(image_source,image->Picture->Bitmap);
	}

  __finally
	{
	  if (mem_strm)
	  {
		delete mem_strm;
	  }

	  if (image_source)
	  {
		delete image_source;
	  }
	}

	return;
}

#include <math.hpp>

void __fastcall resize_picture_ex(TBitmap *image_src,TBitmap *image_destination)
{
  typedef TRGBTriple t_rgb_array;//[32768];
  typedef t_rgb_array *p_rgb_array;

  int ifrom_y,ifrom_x,to_y,to_x,new_red,new_green,new_blue,ix,iy;
  float xscale,yscale,sfrom_y,sfrom_x,weight,total_red,total_green,total_blue;
  float weight_x[2],weight_y[2];
  p_rgb_array sli,slo;


  image_src->PixelFormat = pf24bit;
  image_destination->PixelFormat = pf24bit;

  xscale = (float)image_destination->Width / (float)(image_src->Width - 1);
  yscale = (float)image_destination->Height / (float)(image_src->Height - 1);

  for (to_y = 0; to_y < image_destination->Height; to_y++)
  {
	sfrom_y = (float)to_y / yscale;

	ifrom_y = sfrom_y; //Trunc(sfrom_y);

	weight_y[1] = (float)(sfrom_y - ifrom_y);

	weight_y[0] = (float)(1 - weight_y[1]);

	for (to_x = 0; to_x < image_destination->Width; to_x++)
    {
	  sfrom_x = (float)to_x / xscale;

	  ifrom_x = sfrom_x; //Trunc(sfrom_x);

	  weight_x[1] = (float)(sfrom_x - ifrom_x);

	  weight_x[0] = (float)(1 - weight_x[1]);

	  total_red = 0.0;

	  total_green = 0.0;

	  total_blue = 0.0;

	  for (ix = 0; ix < 2; ix++)
	  {
		for (iy = 0; iy < 2; iy++)
		{
		  sli = (p_rgb_array)image_src->ScanLine[ifrom_y + iy];
		  new_red = sli[ifrom_x + ix].rgbtRed;
		  new_green = sli[ifrom_x + ix].rgbtGreen;
		  new_blue = sli[ifrom_x + ix].rgbtBlue;
		  weight = (float)(weight_x[ix] * weight_y[iy]);
		  total_red = (float)(total_red + (float)new_red * weight);
		  total_green = (float)(total_green + (float)new_green * weight);
		  total_blue = (float)(total_blue + (float)new_blue * weight);
		}
	  }

	  slo = (p_rgb_array)image_destination->ScanLine[to_y];

	  slo[to_x].rgbtRed = total_red;

	  slo[to_x].rgbtGreen = total_green;

	  slo[to_x].rgbtBlue = total_blue;
	}

  }

  return;

}



