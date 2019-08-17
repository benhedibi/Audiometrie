#pragma hdrstop

#include "patient.hpp"

#include <lilly_os.h>
#include <lilly_io.h>
#include <lilly_utils.h>

#include <operators_engine.h>
#include <doctors_engine.h>
#include <patients_engine.h>
#include <consultations_engine.h>

#include <lilly_utils.h>
#include <db_signatures.h>

#include "Unit2.h"


bool __fastcall load_patient(TForm1 *main_frm)
{
  p_engine_entry patient_entry;
  p_patient_record patient_record;
  p_medecin_record med_record,pat_med_record;
  p_consultation_record consult_record;
  unsigned_int error_code;
  struct t_lilly_db_handle *med_db_handle;
  t_lilly_db_database_infos med_db_infos;
  t_date_time today;


	main_frm->PatPaysCombo->Items->LoadFromFile((PWCHAR)&main_frm->session_params.pays_path->path_data);

	main_frm->PatGouvCombo->Items->LoadFromFile((PWCHAR)&main_frm->session_params.gouv_path->path_data);

	main_frm->PatJobCombo->Items->LoadFromFile((PWCHAR)&main_frm->session_params.jobrefs_path->path_data);

	main_frm->session_params.femmes_names->LoadFromFile((PWCHAR)&main_frm->session_params.femmes_path->path_data);

	med_db_handle = main_frm->session_params.engines.doctors_engine.db_handle;

	if (!lilly_db_get_database_informations(med_db_handle,&med_db_infos))
	{
	  UnicodeString err_str = "Erreur au niveau de [GetDabaseInformations] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(med_db_handle));
	  report_event(err_str,mtError,true);
	  return false;
	}

	if (!med_db_infos.record_count)
	{
	  bool data_updated;

	  if (patient_record)
	  {
		report_event("Une erreur indéfinie au niveau de [GetDatabaseInformations] ! Veuillez contactez Ben Hedibi Hassène.",mtError,true);
		return false;
	  }

	  report_event("Votre base de données des médecins est vide ! Vous devez saisir une fiche médecin au moins pour pouvoir ajouter des patients et des consultations.",mtInformation,false);

	  process_again :

	  MedListFrm = new TMedListFrm(main_frm);

	  MedListFrm->Caption = main_frm->Caption;

	  MedListFrm->data_updated = false;

	  try
		 {
			MedListFrm->ShowModal();

			data_updated = MedListFrm->data_updated;
		 }

	  __finally
		{
		   delete MedListFrm;
		   MedListFrm = NULL;
		}

	  if (data_updated == false)
	  {
		if (ask_event("Vous n'avez ajouté aucune fiche médecin à votre base de données. Voulez-vous donc annuler la saisie d'un nouveau patient ?")) return false;
		goto process_again;
	  }

	  if (!lilly_db_get_database_informations(med_db_handle,&med_db_infos))
	  {
		UnicodeString err_str = "Erreur au niveau de [GetDabaseInformations] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(med_db_handle));
		report_event(err_str,mtError,true);
		return false;
	  }

	}

	main_frm->PatientPageMed_Ids = Load_MedId_Table(&main_frm->session_params,main_frm->PatMedCombo);

	if (!main_frm->PatientPageMed_Ids) return false;

	patient_entry = &main_frm->session_params.engines.patients_engine;

	main_frm->Switch_Annuler_Retour_Button(PATIENT_DB_SIGNATURE,patient_entry->edit_mode);

	main_frm->PatNomEdit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatNaissanceEdit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatPoidEdit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatTailleEdit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatVilleEdit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatPhone1Edit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatPhone2Edit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatMailEdit->ReadOnly = (patient_entry->edit_mode == false);
	main_frm->PatPaysCombo->Enabled = (patient_entry->edit_mode == true);
	main_frm->PatGouvCombo->Enabled = (patient_entry->edit_mode == true);
	main_frm->PatSexCombo->Enabled = (patient_entry->edit_mode == true);
	main_frm->PatJobCombo->Enabled = (patient_entry->edit_mode == true);

	patient_record = (p_patient_record)patient_entry->current_record;

	if (!patient_record)
	{
	  if (!patient_entry->edit_mode)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  main_frm->PatNomEdit->Text = "";
	  main_frm->PatNaissanceEdit->Text = "";
	  main_frm->PatConsAgeLbl->Caption = "0";
	  main_frm->PatAgeLbl->Caption = "";
	  main_frm->PatPoidEdit->Text = "";
	  main_frm->PatTailleEdit->Text = "";
	  main_frm->PatVilleEdit->Text = "";
	  main_frm->PatPhone1Edit->Text = "";
	  main_frm->PatPhone2Edit->Text = "";
	  main_frm->PatMailEdit->Text = "";
	  main_frm->PatPaysCombo->ItemIndex = 184;
	  main_frm->PatGouvCombo->ItemIndex = 22;
	  main_frm->PatSexCombo->ItemIndex = -1;
	  main_frm->PatJobCombo->ItemIndex = -1;

	  return true;
	}

	main_frm->PatNomEdit->Text = format_name((PWCHAR)&patient_record->nom_prenom);

	if (patient_record->date_naissance.year)
	{
	  main_frm->PatNaissanceEdit->Text = date_to_string(&patient_record->date_naissance);

	  main_frm->PatConsAgeLbl->Caption = IntToStr((int)patient_record->age_consultation);

	  lilly_os_get_current_time_stamp(&today);

	  main_frm->PatAgeLbl->Caption = IntToStr((int)(today.year - patient_record->date_naissance.year)) + " ans";
	}
	else
	{
	  main_frm->PatNaissanceEdit->Text = "";
	  main_frm->PatConsAgeLbl->Caption = "0";
	  main_frm->PatAgeLbl->Caption = "";
	}

	main_frm->PatSexCombo->ItemIndex = (int)patient_record->sexe;

	main_frm->patient_picture_loaded = load_blob(patient_entry,main_frm->PatPicture,patient_record->code_patient.unique_index,t_lilly_db_photo_blob_type);

	if (!main_frm->patient_picture_loaded)
	{
	  main_frm->customize_picture(main_frm->PatPicture,(int)(today.year - patient_record->date_naissance.year),(patient_record->sexe == 0));
	}

	if (load_blob(patient_entry,main_frm->PatObsMemo,patient_record->code_patient.unique_index,t_lilly_db_observations_confidentielles_blob_type))
	{
	  patient_entry->observation_crc32 = lilly_crc32_buffer((puchar)main_frm->PatObsMemo->Text.c_str(),main_frm->PatObsMemo->Text.Length() * 2,0);
	}

	main_frm->PatPoidEdit->Text = IntToStr((int)patient_record->poids);

	main_frm->PatTailleEdit->Text = IntToStr((int)patient_record->taille);

	main_frm->PatPaysCombo->ItemIndex = (int)patient_record->pays;

	main_frm->PatVilleEdit->Text = (PWCHAR)&patient_record->ville;

	main_frm->PatGouvCombo->ItemIndex = (int)patient_record->gouvernorat;

	main_frm->PatPhone1Edit->Text = (PWCHAR)&patient_record->phone_principal;

	main_frm->PatPhone2Edit->Text = (PWCHAR)&patient_record->phone_secondaire;

	main_frm->PatMailEdit->Text = (PWCHAR)&patient_record->email;

	main_frm->PatJobCombo->Text = (PWCHAR)&patient_record->travail;

	consult_record = (p_consultation_record)lilly_db_get_first_record(main_frm->session_params.engines.consultations_engine.db_handle);

	if (!consult_record)
	{
	  UnicodeString err_str = "Erreur au niveau de [Consultations/GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(main_frm->session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  return false;
	}

	main_frm->PatientConsultationsTable->count = 0;

	error_code = ERROR_SUCCESS;

	while (true)
	{
	  if (consult_record->patient_id == patient_record->code_patient.unique_index)
	  {
		main_frm->PatientConsultationsTable->offsets[main_frm->PatientConsultationsTable->count++] = lilly_db_get_current_record_offset(main_frm->session_params.engines.consultations_engine.db_handle);

		if (main_frm->PatientConsultationsTable->count >= sizeof(main_frm->PatientConsultationsTable->offsets) / sizeof(main_frm->PatientConsultationsTable->offsets[0]))
		{
		  error_code = INDEX_OUT_OF_RANGE;
		  break;
		}
	  }

	  consult_record = (p_consultation_record)lilly_db_get_next_record(main_frm->session_params.engines.consultations_engine.db_handle);

	  if (!consult_record) break;
	}

	if (error_code != ERROR_SUCCESS)
	{
	  report_event("Détection d'un possible STACK OVERFLOW au niveau de [PatientConsultationsTable] ! Veuillez contacter Ben Hedibi Hassène.",mtError,true);
	  return false;
	}

	error_code = lilly_db_get_last_error(main_frm->session_params.engines.consultations_engine.db_handle);

	if (error_code != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Erreur au niveau de [Consultations/GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(main_frm->session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  return false;
	}

	return true;
}

void __fastcall unload_patient(TForm1 *main_frm)
{

	Unload_MedId_Table(main_frm->PatientPageMed_Ids);

	main_frm->session_params.femmes_names->Clear();

	main_frm->PatMedCombo->Items->Clear();

	main_frm->PatPaysCombo->Items->Clear();

	main_frm->PatGouvCombo->Items->Clear();

	main_frm->PatJobCombo->Items->Clear();

	main_frm->PatConsultView->Items->Clear();

	main_frm->PatPicture->Picture = NULL;

	main_frm->PatObsMemo->Lines->Clear();

   //	main_frm->session_params.engines.patients_engine.current_record = NULL;
	main_frm->session_params.engines.patients_engine.observation_crc32 = 0;
    main_frm->session_params.engines.patients_engine.edit_mode = false;

	return;
}

void __fastcall validate_patient(TForm1 *main_frm)
{
  p_engine_entry patient_entry;
  unsigned_int error_code;
  t_patient_record patient_record;


	patient_entry = &main_frm->session_params.engines.patients_engine;

	if (!patient_entry->edit_mode)
	{
	  main_frm->Navigate(0,patient_entry->caller_page_index);
      return;
	}

	avcore_memset(&patient_record,0,sizeof(patient_record));

	if (main_frm->PatNomEdit->Text == "")
	{
	  main_frm->MarkFaultyComponent(main_frm->PatNomEdit);
	  report_event("Vous devez spécifier le nom / prénom du patient !",mtWarning,false);
	  return;
	}

	main_frm->PatNomEdit->Text.UpperCase();

	avcore_memcpy(&patient_record.nom_prenom,(puchar)main_frm->PatNomEdit->Text.c_str(),main_frm->PatNomEdit->Text.Length() * 2);

	main_frm->PatNomEdit->Text = format_name(main_frm->PatNomEdit->Text);

	if (main_frm->PatNaissanceEdit->Text != "  /  /    ")
	{
	  t_date_time today,consult_date;

	  if (!lilly_import_str_to_date_ex((puchar)main_frm->PatNaissanceEdit->Text.c_str(),main_frm->PatNaissanceEdit->Text.Length() * 2,&patient_record.date_naissance))
	  {
		main_frm->MarkFaultyComponent(main_frm->PatNaissanceEdit);
		report_event("La date de naissance que vous avez spécifié est invalide !",mtWarning,false);
		return;
	  }

	  if (!patient_entry->current_record)
	  {
		lilly_os_get_current_time_stamp(&today);
		patient_record.age_consultation = (uint8)(today.year - patient_record.date_naissance.year);
		main_frm->PatConsAgeLbl->Caption = IntToStr((int)patient_record.age_consultation);
	  }
	  else
	  {
		if (((p_patient_record)patient_entry->current_record)->age_consultation == 0)
		{
          TTreeNode *node;

		  node = main_frm->PatConsultView->Items->GetFirstNode();

		  if (node)
		  {
			today.year = 0;

			while (true)
			{
			  node = node->GetNext();

			  if(!string_to_date_stamp((puchar)node->Text.c_str(),node->Text.Length() * 2,&consult_date))
			  {
				report_event("Une erreur est survenue au niveau de Consultations [StrToDate] ! Veuillez contacter Ben Hedibi Hassène.",mtError,false);
				return;
			  }

			  if (consult_date.year < patient_record.date_naissance.year)
			  {
				main_frm->MarkFaultyComponent(main_frm->PatNaissanceEdit);
				report_event("Date de naissance invalide ! Le patient ne peut pas avoir une date de consultation inférieure à sa date de naissance !",mtWarning,false);
			  }

			  if (!today.year)
			  {
				today.year = consult_date.year;
			  }
			  else today.year = MACRO_MIN_VALUE(today.year,consult_date.year);

			  if (!node) break;
			}

			patient_record.age_consultation = (uint8)(today.year - patient_record.date_naissance.year);
		  }
		}
		else
		{
		  if (patient_record.date_naissance.year > ((p_patient_record)patient_entry->current_record)->date_naissance.year)
		  {
			patient_record.age_consultation -= (uint8)(patient_record.date_naissance.year - ((p_patient_record)patient_entry->current_record)->date_naissance.year);
		  }
		  else patient_record.age_consultation += (uint8)(((p_patient_record)patient_entry->current_record)->date_naissance.year - patient_record.date_naissance.year);
		}
	  }
	}

	if (main_frm->PatSexCombo->ItemIndex == -1)
	{
	  main_frm->MarkFaultyComponent(main_frm->PatSexCombo);
	  report_event("Vous devez spécifier le sexe du patient.",mtWarning,false);
	  return;
	}

	if (main_frm->PatTailleEdit->Text != "")
	{
	  patient_record.taille = StrToInt(main_frm->PatTailleEdit->Text);
	}

	if (main_frm->PatPoidEdit->Text != "")
	{
	  patient_record.poids = StrToInt(main_frm->PatPoidEdit->Text);
	}

	if (main_frm->PatMedCombo->ItemIndex == -1)
	{
	  if (main_frm->PatMedCombo->Text != "")
	  {
		UnicodeString msg;
		bool data_updated;

		main_frm->MarkFaultyComponent(main_frm->PatMedCombo);

		msg = main_frm->PatMedCombo->Text;

		msg = msg + "n'est pas inscrit dans votre base de données ! \n\r";

		msg = msg + "Voulez-vous procéder avec la saisie du nouveau médecin ou plutôt annuler l'opération en cours ?";

		if (!ask_event(msg)) return;

		MedListFrm = new TMedListFrm(main_frm);

		try
		  {
			MedListFrm->Caption = main_frm->Caption;

			MedListFrm->data_updated = false;

			MedListFrm->ShowModal();

			data_updated = MedListFrm->data_updated;
		  }

		__finally
		  {
			delete MedListFrm;
		  }

		if (!data_updated)
		{
		  report_event("Vous ne pouvez pas valider vos modifications tant que vous n'avez pas inscrit et assigné le médecin spécifié dans votre base de données !",mtWarning,false);
		  return;
		}

		Unload_MedId_Table(main_frm->PatientPageMed_Ids);

		main_frm->PatientPageMed_Ids = Load_MedId_Table(&main_frm->session_params,main_frm->PatMedCombo);
	  }
	}

	if (main_frm->PatPaysCombo->ItemIndex < 0)
	{
	  main_frm->MarkFaultyComponent(main_frm->PatPaysCombo);
	  report_event("Vous n'avez pas spécifié le Pays !",mtWarning,false);
	  return;
	}

	patient_record.pays = (uint8)main_frm->PatPaysCombo->ItemIndex;

	if (main_frm->PatVilleEdit->Text != "")
	{
	  avcore_memcpy(&patient_record.ville,(puchar)main_frm->PatVilleEdit->Text.c_str(),main_frm->PatVilleEdit->Text.Length() * 2);
	}

	if ((main_frm->PatGouvCombo->Enabled) && (main_frm->PatGouvCombo->ItemIndex < 0))
	{
	  main_frm->MarkFaultyComponent(main_frm->PatPaysCombo);
      report_event("Vous n'avez pas spécifié le Gouvernorat !",mtWarning,false);
	  return;
	}

	if (main_frm->PatGouvCombo->Enabled)
	{
	  patient_record.gouvernorat = (uint8)main_frm->PatGouvCombo->ItemIndex;
	}
	else patient_record.gouvernorat = 0xFF;

	if (main_frm->PatPhone1Edit->Text != "")
	{
	  avcore_memcpy(&patient_record.phone_principal,(puchar)main_frm->PatPhone1Edit->Text.c_str(),main_frm->PatPhone1Edit->Text.Length() * 2);
	}

	if (main_frm->PatPhone2Edit->Text != "")
	{
	  avcore_memcpy(&patient_record.phone_secondaire,(puchar)main_frm->PatPhone2Edit->Text.c_str(),main_frm->PatPhone2Edit->Text.Length() * 2);
	}

	if (main_frm->PatMailEdit->Text != "")
	{
	  avcore_memcpy(&patient_record.email,(puchar)main_frm->PatMailEdit->Text.c_str(),main_frm->PatMailEdit->Text.Length() * 2);
	}

	if (main_frm->PatJobCombo->Text != "")
	{
	  bool found = false;

	  avcore_memcpy(&patient_record.travail,(puchar)main_frm->PatJobCombo->Text.c_str(),main_frm->PatJobCombo->Text.Length() * 2);

	  for (int i = 0; i < main_frm->PatJobCombo->Items->Count; i++)
	  {
		if (main_frm->PatJobCombo->Items[i].Text == main_frm->PatJobCombo->Text)
	    {
	      found = true;
	      break;
		}
	  }

	  if (!found)
	  {
		main_frm->PatJobCombo->Items->Add(main_frm->PatJobCombo->Text);

		main_frm->PatJobCombo->Sorted = true;

		if (lilly_io_delete_file((puchar)&main_frm->session_params.jobrefs_path->path_data))
	    {
		  main_frm->PatJobCombo->Items->SaveToFile((PWCHAR)&main_frm->session_params.jobrefs_path->path_data);
	    }
	  }
	}

	if (!patient_entry->current_record)
	{
	  if (!patient_entry->engine->append_record(patient_entry->engine,patient_entry->db_handle,&patient_record))
	  {
		UnicodeString err_str;
		error_code = patient_entry->engine->error_code;

		if (error_code != LILLY_DB_DUPLICATE_RECORD_ERROR)
	    {
		  err_str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur Patients DB a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(error_code);
	      report_event(err_str,mtError,true);
		  return;
		}
		else
		{
		  err_str = "Une patient du nom de " + main_frm->PatNomEdit->Text + " est déjà inscrit dans votre base de données et avec les mêmes informations relatives \n\r\n\r";
		  err_str = err_str + "Opération d'ajout est annulée.";
		  report_event(err_str,mtError,false);
		  return;
        }
	  }
	}
	else
	{
	  uint32 crc = patient_entry->engine->get_record_crc(patient_entry->engine,patient_entry->db_handle,&patient_record);

	  if (!crc)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [GetDataCrc] ! Le moteur Patients DB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(patient_entry->engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  if (crc != ((p_patient_record)patient_entry->current_record)->code_patient.crc32)
	  {
		if (!patient_entry->engine->edit_record(patient_entry->engine,patient_entry->db_handle,&patient_record,lilly_db_get_current_record_offset(patient_entry->db_handle)))
		{
		  error_code = patient_entry->engine->error_code;

		  if (error_code != LILLY_DB_DUPLICATE_RECORD_ERROR)
		  {
			UnicodeString err_str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur Patients DB a retourné l'erreur suivante : \n\r\n\r";
			err_str = err_str + error_code_to_string(error_code);
			report_event(err_str,mtError,true);
			return;
		  }
		}
	  }
	}

	uint32 rec_id;

	if ((patient_entry->current_record == NULL) && ((patient_entry->updated_picture) || (main_frm->PatObsMemo->Text != "")))
	{
      uint64 offset;
	  p_patient_record tmp;

	  offset = lilly_db_get_current_record_offset(patient_entry->db_handle);

	  tmp = (p_patient_record)lilly_db_read_record(patient_entry->db_handle,PATIENT_RECORD_SIZE,offset);

	  if (!tmp)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! Le moteur Patients DB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(patient_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  rec_id = tmp->code_patient.unique_index;
	}
	else if (patient_entry->current_record)
	{
	  rec_id = ((p_patient_record)patient_entry->current_record)->code_patient.unique_index;
	}

	// handle observations

	if ((patient_entry->observation_crc32) && (main_frm->PatObsMemo->Text == ""))
	{
	  delete_blob(patient_entry,rec_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((!patient_entry->observation_crc32) && (main_frm->PatObsMemo->Text != ""))
	{
	  add_blob(patient_entry,main_frm->PatObsMemo,rec_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((patient_entry->observation_crc32) && (main_frm->PatObsMemo->Text != ""))
	{
	  update_blob(patient_entry,main_frm->PatObsMemo,rec_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}

	// handle picture

	if (patient_entry->updated_picture)
	{
	  update_blob(patient_entry,main_frm->PatPicture,rec_id,main_frm->session_params.current_operator_id,t_lilly_db_photo_blob_type);
	}
	else if (patient_entry->deleted_picture)
	{
	  delete_blob(patient_entry,rec_id,t_lilly_db_photo_blob_type);
	}

	if (patient_entry->current_record)
	{
	  report_event("Fiche modifiée avec succès.",mtInformation,false);
	}
	else report_event("Fiche ajoutée avec succès !",mtInformation,false);

	main_frm->Switch_Annuler_Retour_Button(PATIENT_DB_SIGNATURE,false);

	//main_frm->Navigate(0,patient_entry->caller_page_index);

	return;
}

void __fastcall edit_patient(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.patients_engine.edit_mode) return;
	else
	{
	  UnicodeString str = "Êtes-vous sûre de vouloir modifer la fiche de ";
	  str = str + (PWCHAR)(&((p_patient_record)main_frm->session_params.engines.patients_engine.current_record)->nom_prenom);
	  if (!ask_event(str)) return;
	}

	main_frm->session_params.engines.patients_engine.edit_mode = true;

	main_frm->PatNomEdit->ReadOnly = false;
	main_frm->PatNaissanceEdit->ReadOnly = false;
	main_frm->PatSexCombo->Enabled = true;
	main_frm->PatTailleEdit->ReadOnly = false;
	main_frm->PatPoidEdit->ReadOnly = false;
	main_frm->PatMedCombo->Enabled = true;
	main_frm->PatPaysCombo->Enabled = true;
	main_frm->PatVilleEdit->ReadOnly = false;
	main_frm->PatGouvCombo->Enabled = true;
	main_frm->PatPhone1Edit->ReadOnly = false;
	main_frm->PatPhone2Edit->ReadOnly = false;
	main_frm->PatMailEdit->ReadOnly = false;
	main_frm->PatJobCombo->Enabled = true;
	main_frm->PatObsMemo->ReadOnly = false;
	main_frm->PatConsultView->Enabled = true;

	main_frm->Switch_Annuler_Retour_Button(PATIENT_DB_SIGNATURE,true);

	return;
}

void __fastcall delete_patient(TForm1 *main_frm)
{
  UnicodeString err_str;

	if (main_frm->session_params.engines.patients_engine.edit_mode)
	{
	  report_event("Opération impossible : la suppression n'est pas possible lorsque la fiche du patient est en mode ajout ou edition.",mtWarning,false);
	  return;
	}

	if (!main_frm->session_params.engines.patients_engine.current_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	err_str = "Attention : vous êtes sur le point de supprimer une fiche patient ainsi que toutes les consultations associées ! \n\r\n\r";
	err_str = err_str + "Continuer quand même ?";

	if (!ask_event(err_str)) return;

	if (!main_frm->session_params.session_manager->delete_patient(main_frm->session_params.session_manager,
	((p_patient_record)main_frm->session_params.engines.patients_engine.current_record)->code_patient.unique_index))
	{
	  err_str = "Une erreur est survenue au niveau de [DeleteRecord] ! Session Manager a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(main_frm->session_params.session_manager->error_code);
	  err_str = err_str + "\n\r\n\r";
	  err_str = err_str + "Veuillez contacter Ben Hedibi Hassène.";
	  report_event(err_str,mtError,true);
      return;
    }

	report_event("Fiche supprimée avec succès.",mtInformation,false);

	main_frm->session_params.engines.patients_engine.edit_mode = false;
	main_frm->session_params.engines.patients_engine.current_record = NULL;

	main_frm->Navigate(0,1); // retourner toujours à la liste des patients puisque les consultations et les mesures sont supprimés

	return;
}

void __fastcall cancel_patient(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.patients_engine.edit_mode)
	{
	  if (!ask_event("Annuler l'opération en cours ?")) return;
	}

	main_frm->Navigate(0,main_frm->session_params.engines.patients_engine.caller_page_index);

	return;
}

