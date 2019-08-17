#pragma hdrstop

#include "consultation.hpp"

#include <lilly_os.h>

#include <operators_engine.h>
#include <doctors_engine.h>
#include <patients_engine.h>
#include <consultations_engine.h>
#include <audiograms_engine.h>
#include <tympano_engine.h>
#include <gainp_engine.h>
#include <audiovocs_engine.h>

#include <lilly_utils.h>

#include "Unit2.h"

bool __fastcall load_consultation(TForm1 *main_frm)
{
  p_patient_record pat_record;
  p_engine_entry consult_entry;
  p_consultation_record consult_record;
  int age_patient;
  t_date_time today;


	main_frm->ConsPatCancelLbl->Caption = "Retour";

	pat_record = (p_patient_record)main_frm->session_params.engines.patients_engine.current_record;

	if (!pat_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	main_frm->PatientPageMed_Ids = Load_MedId_Table(&main_frm->session_params,main_frm->ConsPatMedCombo);

	if (!main_frm->PatientPageMed_Ids) return false;

	consult_entry = &main_frm->session_params.engines.consultations_engine;

	consult_record = (p_consultation_record)consult_entry->current_record;

	lilly_os_get_current_time_stamp(&today);

	main_frm->ConsPatNameLbl->Caption = format_name((PWCHAR)&pat_record->nom_prenom);

	main_frm->ConsPatCodeLbl->Caption = IntToStr((int)pat_record->code_patient.unique_index);

    if (!load_blob(consult_entry,main_frm->ConsPatImage,consult_record->patient_id,t_lilly_db_photo_blob_type))
	{
	  main_frm->customize_picture(main_frm->ConsPatImage,today.year - pat_record->date_naissance.year,(pat_record->sexe == 0));
	}

	if (consult_record)
	{
	  uint64 offset;
	  p_operateur_record op_record;
	  t_lilly_db_time_stamp_informations time_stamp_infos;

	  offset = lilly_db_get_current_record_offset(consult_entry->db_handle);

	  if (!lilly_db_get_record_time_stamp_infos(consult_entry->db_handle,offset,&time_stamp_infos))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [GetTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(consult_entry->db_handle));
		report_event(err_str,mtError,true);
		return false;
	  }

	  main_frm->ConsPatAgeLbl->Caption = IntToStr((int)(time_stamp_infos.creation_stamp.time_stamp.year - pat_record->date_naissance.year));

	  main_frm->ConsPatDateLbl->Caption = datetime_to_string(&time_stamp_infos.creation_stamp.time_stamp);

	  op_record = (p_operateur_record)main_frm->session_params.engines.operators_engine.engine->code_to_record(main_frm->session_params.engines.operators_engine.engine,
	  main_frm->session_params.engines.operators_engine.db_handle,time_stamp_infos.creation_stamp.operator_id);

	  if (!op_record)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur des opérateurs a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(main_frm->session_params.engines.operators_engine.engine->error_code);
		report_event(err_str,mtError,true);
        return false;
	  }

	  main_frm->ConsPatOpLbl->Caption = format_name((PWCHAR)&op_record->nom_prenom);

	  main_frm->ConsPatListView->Items->Item[0]->ImageIndex = (int)((bool)(consult_record->audiogram_id != 0));
	  main_frm->ConsPatListView->Items->Item[1]->ImageIndex = (int)((bool)(consult_record->tympanogram_id != 0));
	  main_frm->ConsPatListView->Items->Item[2]->ImageIndex = (int)((bool)(consult_record->gainp_id != 0));
	  main_frm->ConsPatListView->Items->Item[3]->ImageIndex = (int)((bool)(consult_record->audiovoc_id != 0));

	  load_blob(consult_entry,main_frm->ConsPatObsMemo,consult_record->patient_id,t_lilly_db_observations_confidentielles_blob_type);

	  if (main_frm->ConsPatObsMemo->Lines->Count > 0)
	  {
		consult_entry->observation_crc32 = lilly_crc32_buffer((puchar)main_frm->ConsPatObsMemo->Text.c_str(),main_frm->ConsPatObsMemo->Text.Length() * 2,0);
	  }
	}
	else
	{
	  main_frm->ConsPatAgeLbl->Caption = IntToStr((int)(today.year - pat_record->date_naissance.year));
	  main_frm->ConsPatDateLbl->Caption = datetime_to_string(&today);
	  main_frm->ConsPatOpLbl->Caption = main_frm->session_params.CurrentOpName;

	  main_frm->ConsPatListView->Items->Item[0]->ImageIndex = 0;
	  main_frm->ConsPatListView->Items->Item[1]->ImageIndex = 0;
	  main_frm->ConsPatListView->Items->Item[2]->ImageIndex = 0;
	  main_frm->ConsPatListView->Items->Item[3]->ImageIndex = 0;
	}

	main_frm->ConsPatMedCombo->Enabled = main_frm->session_params.engines.consultations_engine.edit_mode;
	main_frm->ConsPatObsMemo->ReadOnly = (main_frm->session_params.engines.consultations_engine.edit_mode == false);

	return true;
}

void __fastcall unload_consultation(TForm1 *main_frm)
{

	main_frm->ConsPatMedCombo->Items->Clear();

	main_frm->ConsPatObsMemo->Lines->Clear();

	main_frm->ConsPatImage->Picture = NULL;

	main_frm->session_params.engines.consultations_engine.observation_crc32 = 0;
	main_frm->session_params.engines.consultations_engine.edit_mode = false;

	Unload_MedId_Table(main_frm->PatientPageMed_Ids);

	return;
}

void __fastcall validate_consultation(TForm1 *main_frm)
{
  p_patient_record pat_record;
  p_engine_entry consult_entry;
  p_consultation_record consult_record;
  t_consultation_record record;
  t_date_time today;


	pat_record = (p_patient_record)main_frm->session_params.engines.patients_engine.current_record;

	if (!pat_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	consult_entry = &main_frm->session_params.engines.consultations_engine;

	consult_record = (p_consultation_record)consult_entry->current_record;

	if (consult_record)
	{
	  if (!consult_entry->engine->edit_record(consult_entry->engine,consult_entry->db_handle,consult_record,lilly_db_get_current_record_offset(consult_entry->db_handle)))
	  {
		UnicodeString str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur Consultations a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(consult_entry->engine->error_code) + "\n\r";
		str = str + "Veuillez contacter le support technique !";
		report_event(str,mtError,true);
		return;
	  }

	  report_event("Consultation modifiée avec succès.",mtInformation,false);
	  return;
	}

    if (main_frm->ConsPatMedCombo->ItemIndex == -1)
	{
	  if (main_frm->ConsPatMedCombo->Text != "")
	  {
		UnicodeString msg;
		bool data_updated;

		main_frm->MarkFaultyComponent(main_frm->ConsPatMedCombo);

		msg = main_frm->ConsPatMedCombo->Text;

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

		main_frm->PatientPageMed_Ids = Load_MedId_Table(&main_frm->session_params,main_frm->ConsPatMedCombo);
	  }

      return;
	}

	avcore_memset(&record,0,sizeof(record));

	record.patient_id = pat_record->code_patient.unique_index;
	record.medecin_id = main_frm->PatientPageMed_Ids[main_frm->ConsPatMedCombo->ItemIndex];

	if (!consult_entry->current_record)
	{
	  if (!consult_entry->engine->append_record(consult_entry->engine,consult_entry->db_handle,&record))
	  {
		UnicodeString str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur Consultations a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(consult_entry->engine->error_code) + "\n\r";
		str = str + "Veuillez contacter le support technique !";
		report_event(str,mtError,true);
		return;
	  }
	}
	else
	{
	  uint32 crc = consult_entry->engine->get_record_crc(consult_entry->engine,consult_entry->db_handle,&record);

	  if (!crc)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [GetDataCrc] ! Le moteur Consultations a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(consult_entry->engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  if (crc != consult_record->code_consultation.crc32)
	  {
        if (!consult_entry->engine->edit_record(consult_entry->engine,consult_entry->db_handle,consult_record,lilly_db_get_current_record_offset(consult_entry->db_handle)))
		{
		  UnicodeString str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur Consultations a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(consult_entry->engine->error_code) + "\n\r";
		  str = str + "Veuillez contacter le support technique !";
		  report_event(str,mtError,true);
		  return;
		}
      }
    }

    uint32 rec_id;

	if ((!consult_record) && (main_frm->PatObsMemo->Text != ""))
	{
      uint64 offset;

	  offset = lilly_db_get_current_record_offset(consult_entry->db_handle);

	  main_frm->session_params.engines.consultations_engine.current_record = (p_consultation_record)lilly_db_read_record(consult_entry->db_handle,CONSULTATION_RECORD_SIZE,offset);

	  if (!main_frm->session_params.engines.consultations_engine.current_record)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! Le moteur Consultations a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(consult_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  rec_id = ((p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record)->code_consultation.unique_index;
	}
	else if (consult_record)
	{
	  rec_id = consult_record->code_consultation.unique_index;
	}

	if ((consult_entry->observation_crc32) && (main_frm->ConsPatObsMemo->Text == ""))
	{
	  delete_blob(consult_entry,rec_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((!consult_entry->observation_crc32) && (main_frm->ConsPatObsMemo->Text != ""))
	{
	  add_blob(consult_entry,main_frm->ConsPatObsMemo,rec_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((consult_entry->observation_crc32) && (main_frm->ConsPatObsMemo->Text != ""))
	{
	  update_blob(consult_entry,main_frm->ConsPatObsMemo,rec_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}

	main_frm->session_params.engines.consultations_engine.edit_mode = false;

	main_frm->ConsPatMedCombo->Enabled = false;
	main_frm->ConsPatObsMemo->ReadOnly = true;

	if (consult_record)
	{
	  report_event("Consultation modifiée avec succès.",mtInformation,false);
	}
	else
	{
	  report_event("Consultation ajoutée avec succès.",mtInformation,false);
    }

	main_frm->ConsPatCancelLbl->Caption = "Retour";

	return;
}

void __fastcall edit_consultation(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.consultations_engine.edit_mode) return;

	if (!main_frm->session_params.engines.consultations_engine.current_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	main_frm->ConsPatCancelLbl->Caption = "Annuler";

	main_frm->ConsPatMedCombo->Enabled = true;

	main_frm->ConsPatObsMemo->ReadOnly = false;

	main_frm->session_params.engines.consultations_engine.edit_mode = true;

    return;
}

void __fastcall delete_consultation(TForm1 *main_frm)
{
  UnicodeString str;


	 if (!main_frm->session_params.engines.consultations_engine.current_record) return;

	 str = "Attention la suppression de cette consultation va entrainer une suppression définitive de toutes les opérations associées à celle-ci : Audiogramme,Tympanogramme... \n\r";
	 str = str + "Voulez-vous procéder à la suppression ?";

	 if (!ask_event(str)) return;

	 if (!main_frm->session_params.session_manager->delete_consultation_ex(main_frm->session_params.session_manager,main_frm->session_params.engines.consultations_engine.db_handle,
     main_frm->session_params.engines.consultations_engine.current_record,lilly_db_get_current_record_offset(main_frm->session_params.engines.consultations_engine.db_handle)))
	 {
	   str = "Une erreur est survenue lors de la suppression de la consultation ! Session Manager a retourné l'erreur suivante : \n\r\n\r";
	   str = str + error_code_to_string(main_frm->session_params.session_manager->error_code) + "\n\r";
	   str = str + "Veuillez contacter votre support technique !";
	   return;
	 }

	 report_event("La consultation est supprimée avec succès.",mtInformation,false);

	 main_frm->session_params.engines.consultations_engine.current_record = NULL;

	 main_frm->Navigate(2,main_frm->session_params.engines.consultations_engine.caller_page_index);

     return;
}

void __fastcall cancel_consultation(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.consultations_engine.edit_mode)
	{
	  if (!ask_event("Annuler l'opération en cours ?")) return;
	}

	main_frm->Navigate(2,main_frm->session_params.engines.consultations_engine.caller_page_index);

	return;
}