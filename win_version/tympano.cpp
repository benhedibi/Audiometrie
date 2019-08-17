#pragma hdrstop

#include "tympano.hpp"

#include <operators_engine.h>
#include <patients_engine.h>
#include <consultations_engine.h>
#include <tympano_engine.h>

#include <lilly_utils.h>
#include <lilly_os.h>

#include <db_signatures.h>

#include "unit8.h"


static const PWCHAR TYMP_PRESSION[2] = {(PWCHAR)L"OdPressEdit",(PWCHAR)L"OgPressEdit"};


static bool __fastcall load_tympanogram_oreille(TForm1 *main_frm,const p_tympano_oreille oreille,const bool oreille_gauche,const bool read_only)
{
  TEdit *edit = NULL;


	for (int i = 13; i > 0; i--)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(TYMP_PRESSION[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if (!oreille)
	  {
		edit->Text = "0";
	  }
	  else edit->Text = FloatToStrF(oreille->valeurs[i - 1],ffGeneral,2,2);

	  edit->ReadOnly = read_only;
	}

	if (!oreille)
	{
	  if (!oreille_gauche)
	  {
		main_frm->OdRsEdit1->Text = "0";
		main_frm->OdRsEdit2->Text = "0";
		main_frm->OdRsEdit3->Text = "0";
		main_frm->OdRsEdit4->Text = "0";
	  }
	  else
	  {
		main_frm->OgRsEdit1->Text = "0";
		main_frm->OgRsEdit2->Text = "0";
		main_frm->OgRsEdit3->Text = "0";
		main_frm->OgRsEdit4->Text = "0";
	  }
	}
	else
	{
	  if (!oreille_gauche)
	  {
		main_frm->OdRsEdit1->Text = IntToStr((int)oreille->reflexes[0]);
		main_frm->OdRsEdit2->Text = IntToStr((int)oreille->reflexes[1]);
		main_frm->OdRsEdit3->Text = IntToStr((int)oreille->reflexes[2]);
		main_frm->OdRsEdit4->Text = IntToStr((int)oreille->reflexes[3]);
	  }
	  else
	  {
		main_frm->OgRsEdit1->Text = IntToStr((int)oreille->reflexes[0]);
		main_frm->OgRsEdit2->Text = IntToStr((int)oreille->reflexes[1]);
		main_frm->OgRsEdit3->Text = IntToStr((int)oreille->reflexes[2]);
		main_frm->OgRsEdit4->Text = IntToStr((int)oreille->reflexes[3]);
	  }
	}

	return true;
}

static bool __fastcall fill_tympanogram_oreille(TForm1 *main_frm,const p_tympano_oreille oreille,const bool oreille_gauche)
{
  int row_hits = 0;
  TEdit *edit = NULL;


	if (!oreille)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

    for (int i = 13; i > 0; i--)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(TYMP_PRESSION[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if (edit->Text != "0")
	  {
		row_hits++;
	  }

	  oreille->valeurs[i] = StrToFloat(edit->Text);
	}

	if (!oreille_gauche)
	{
	  oreille->reflexes[0] = (uint8)StrToInt(main_frm->OdRsEdit1->Text);
	  oreille->reflexes[1] = (uint8)StrToInt(main_frm->OdRsEdit2->Text);
	  oreille->reflexes[2] = (uint8)StrToInt(main_frm->OdRsEdit3->Text);
	  oreille->reflexes[3] = (uint8)StrToInt(main_frm->OdRsEdit4->Text);
	}
	else
	{
	  oreille->reflexes[0] = (uint8)StrToInt(main_frm->OgRsEdit1->Text);
	  oreille->reflexes[1] = (uint8)StrToInt(main_frm->OgRsEdit2->Text);
	  oreille->reflexes[2] = (uint8)StrToInt(main_frm->OgRsEdit3->Text);
	  oreille->reflexes[3] = (uint8)StrToInt(main_frm->OgRsEdit4->Text);
	}

	return (row_hits > 0);

}

bool __fastcall load_tympanogram(TForm1 *main_frm)
{
  p_engine_entry tympano_entry;
  p_patient_record pat_record;
  p_tympanogram_record tympano_record;


	tympano_entry = &main_frm->session_params.engines.tympanograms_engine;

	pat_record = (p_patient_record)main_frm->session_params.engines.patients_engine.current_record;

	if ((!pat_record) || ((!tympano_entry->current_record) && (!tympano_entry->edit_mode)))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	if (!load_old_data_to_listview(&main_frm->session_params,TYMPANOGRAM_DB_SIGNATURE,pat_record->code_patient.unique_index,main_frm->TympanoListView)) return false;

	main_frm->Switch_Annuler_Retour_Button(TYMPANOGRAM_DB_SIGNATURE,tympano_entry->edit_mode);

	tympano_record = (p_tympanogram_record)tympano_entry->current_record;

	if (!tympano_record)
	{
	  if ((!load_tympanogram_oreille(main_frm,NULL,false,false)) || (!load_tympanogram_oreille(main_frm,NULL,true,false))) return false;

	  main_frm->OdRsEdit1->ReadOnly = false;
	  main_frm->OdRsEdit1->Text = "0";

	  main_frm->OdRsEdit2->ReadOnly = false;
	  main_frm->OdRsEdit2->Text = "0";

	  main_frm->OdRsEdit3->ReadOnly = false;
	  main_frm->OdRsEdit3->Text = "0";

	  main_frm->OdRsEdit4->ReadOnly = false;
	  main_frm->OdRsEdit4->Text = "0";

	  main_frm->OgRsEdit1->ReadOnly = false;
	  main_frm->OgRsEdit1->Text = "0";

	  main_frm->OgRsEdit2->ReadOnly = false;
	  main_frm->OgRsEdit2->Text = "0";

	  main_frm->OgRsEdit3->ReadOnly = false;
	  main_frm->OgRsEdit3->Text = "0";

	  main_frm->OgRsEdit4->ReadOnly = false;
	  main_frm->OgRsEdit4->Text = "0";

	  return true;
	}

	if ((!load_tympanogram_oreille(main_frm,&tympano_record->oreille_droite,false,(tympano_entry->edit_mode == false))) ||
	(!load_tympanogram_oreille(main_frm,&tympano_record->oreille_gauche,true,(tympano_entry->edit_mode == false)))) return false;

	main_frm->OdRsEdit1->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OdRsEdit1->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[0]);

	main_frm->OdRsEdit2->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OdRsEdit2->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[1]);

	main_frm->OdRsEdit3->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OdRsEdit3->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[2]);

	main_frm->OdRsEdit4->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OdRsEdit4->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[3]);

	main_frm->OgRsEdit1->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OgRsEdit1->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[0]);

	main_frm->OgRsEdit2->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OgRsEdit2->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[1]);

	main_frm->OgRsEdit2->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OgRsEdit2->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[2]);

	main_frm->OgRsEdit2->ReadOnly = (tympano_entry->edit_mode == false);
	main_frm->OgRsEdit2->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[3]);

	main_frm->TympanoObsMemo->ReadOnly = tympano_entry->edit_mode;

	main_frm->TympanoDefValCombo->Enabled = tympano_entry->edit_mode;

	load_blob(tympano_entry,main_frm->TympanoObsMemo,tympano_record->code_tympanogram.unique_index,t_lilly_db_observations_confidentielles_blob_type);

	if (main_frm->TympanoObsMemo->Lines->Count > 0)
	{
	  tympano_entry->observation_crc32 = lilly_crc32_buffer((puchar)main_frm->TympanoObsMemo->Text.c_str(),main_frm->TympanoObsMemo->Text.Length() * 2,0);
	}

	if (!tympano_entry->edit_mode)
	{
	  return true;
	}
	else return load_grph_list(tympano_entry,TYMPANOGRAM_DB_SIGNATURE,main_frm->TympanoDefValCombo);
}

void __fastcall unload_tympanogram(TForm1 *main_frm)
{

	main_frm->TympanoListView->Items->Clear();

	main_frm->TympanoDefValCombo->Items->Clear();

	main_frm->TympanoObsMemo->Lines->Clear();

	main_frm->session_params.engines.tympanograms_engine.current_record = NULL;
	main_frm->session_params.engines.tympanograms_engine.observation_crc32 = 0;
	main_frm->session_params.engines.tympanograms_engine.edit_mode = false;

	return;
}

void __fastcall validate_tympanogram(TForm1 *main_frm)
{
  p_engine_entry tympano_entry;
  p_lilly_db_engine db_engine;
  p_consultation_record consult_record;
  p_tympanogram_record tympano_record,rec_ptr;
  uint64 offset;
  t_tympanogram_record record;


	tympano_entry = &main_frm->session_params.engines.tympanograms_engine;

	if (!tympano_entry->edit_mode)
	{
	  main_frm->Navigate(5,tympano_entry->caller_page_index);
	  return;
	}

	db_engine = tympano_entry->engine;

	consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if ((!consult_record) || (!db_engine))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	avcore_memset(&record,0,sizeof(record));

	tympano_record = (p_tympanogram_record)tympano_entry->current_record;

	if (!tympano_record)
	{
	  rec_ptr = &record;
	}
	else rec_ptr = tympano_record;

	if ((!fill_tympanogram_oreille(main_frm,&rec_ptr->oreille_droite,false)) && (!fill_tympanogram_oreille(main_frm,&rec_ptr->oreille_gauche,true)))
	{
	  report_event("Vous ne pouvez pas valider un Tympanogramme vide !",mtWarning,false);
	  return;
	}

	rec_ptr->oreille_droite.reflexes[0] = (uint8)StrToInt(main_frm->OdRsEdit1->Text);
	rec_ptr->oreille_droite.reflexes[1] = (uint8)StrToInt(main_frm->OdRsEdit2->Text);
	rec_ptr->oreille_droite.reflexes[2] = (uint8)StrToInt(main_frm->OdRsEdit3->Text);
	rec_ptr->oreille_droite.reflexes[3] = (uint8)StrToInt(main_frm->OdRsEdit4->Text);

	rec_ptr->oreille_gauche.reflexes[0] = (uint8)StrToInt(main_frm->OgRsEdit1->Text);
	rec_ptr->oreille_gauche.reflexes[1] = (uint8)StrToInt(main_frm->OgRsEdit2->Text);
	rec_ptr->oreille_gauche.reflexes[2] = (uint8)StrToInt(main_frm->OgRsEdit3->Text);
	rec_ptr->oreille_gauche.reflexes[3] = (uint8)StrToInt(main_frm->OgRsEdit4->Text);

	if (!tympano_record)
	{
	  if (consult_record->tympanogram_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  if (!db_engine->append_record(db_engine,tympano_entry->db_handle,rec_ptr))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur des Tympanogrammes a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(tympano_entry->db_handle);

	  tympano_record = (p_tympanogram_record)lilly_db_read_record(tympano_entry->db_handle,sizeof(record),offset);

	  if (!tympano_record)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(tympano_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  main_frm->Consultation_OnChange_Event_Handler(TYMPANOGRAM_DB_SIGNATURE,tympano_record->code_tympanogram.unique_index,t_record_state_change_type);

	  report_event("Tympanogramme ajouté avec succès.",mtInformation,false);
	}
	else
	{
	  if (!consult_record->tympanogram_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(tympano_entry->db_handle);

	  if (!db_engine->edit_record(db_engine,tympano_entry->db_handle,rec_ptr,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur des Tympanogrammes a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  report_event("Tympanogramme modifié avec succès.",mtInformation,false);
	}

	if ((tympano_entry->observation_crc32) && (main_frm->TympanoObsMemo->Text == ""))
	{
	  delete_blob(tympano_entry,consult_record->tympanogram_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((!tympano_entry->observation_crc32) && (main_frm->TympanoObsMemo->Text != ""))
	{
	  add_blob(tympano_entry,main_frm->TympanoObsMemo,consult_record->tympanogram_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((tympano_entry->observation_crc32) && (main_frm->TympanoObsMemo->Text != ""))
	{
	  update_blob(tympano_entry,main_frm->TympanoObsMemo,consult_record->tympanogram_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}

	main_frm->Switch_Annuler_Retour_Button(TYMPANOGRAM_DB_SIGNATURE,false);

	//main_frm->Navigate(5,tympano_entry->caller_page_index);

	return;
}

void __fastcall edit_tympanogram(TForm1 *main_frm)
{
  TEdit *edit = NULL;


	if (main_frm->session_params.engines.tympanograms_engine.edit_mode) return;

	if (!ask_event("Modifier ce Tympanogramme ?")) return;

	main_frm->session_params.engines.tympanograms_engine.edit_mode = true;

	main_frm->OdRsEdit1->ReadOnly = false;
	main_frm->OdRsEdit2->ReadOnly = false;
	main_frm->OdRsEdit3->ReadOnly = false;
	main_frm->OdRsEdit4->ReadOnly = false;

	main_frm->OgRsEdit1->ReadOnly = false;
	main_frm->OgRsEdit2->ReadOnly = false;
	main_frm->OgRsEdit3->ReadOnly = false;
	main_frm->OgRsEdit4->ReadOnly = false;

	for (int i = 13; i > 0; i--)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(TYMP_PRESSION[0] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(TYMP_PRESSION[1] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;
	}

	main_frm->TympanoObsMemo->ReadOnly = false;

	main_frm->TympanoDefValCombo->Enabled = true;

	main_frm->Switch_Annuler_Retour_Button(TYMPANOGRAM_DB_SIGNATURE,true);

	return;
}

void __fastcall delete_tympanogram(TForm1 *main_frm)
{
  p_engine_entry tympano_entry;
  p_tympanogram_record tympano_record;
  uint64 offset;


	tympano_entry = &main_frm->session_params.engines.tympanograms_engine;

	tympano_record = (p_tympanogram_record)tympano_entry->current_record;

	if (!ask_event("Êtes-vous sûres de vouloir supprimer ce Tympanogramme ?")) return;

	if (tympano_record)
	{
	  p_consultation_record consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	  if ((!consult_record) || (consult_record->tympanogram_id != tympano_record->code_tympanogram.unique_index))
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(tympano_entry->db_handle);

	  if (!lilly_db_delete_record(tympano_entry->db_handle,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [DeleteRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(tympano_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  consult_record->tympanogram_id = 0;

	  tympano_entry->current_record = NULL;
	  tympano_entry->edit_mode = false;

	  main_frm->session_params.engines.consultations_engine.edit_mode = true;

	  report_event("Tympanogramme supprimé avec succès.",mtInformation,false);
	}

	main_frm->Consultation_OnChange_Event_Handler(TYMPANOGRAM_DB_SIGNATURE,0,t_record_state_change_type);

	main_frm->Navigate(5,tympano_entry->caller_page_index);

	return;
}

void __fastcall cancel_tympanogram(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.tympanograms_engine.edit_mode)
	{
	  if (!ask_event("Annuler l'opération en cours ?")) return;

	  main_frm->session_params.engines.tympanograms_engine.current_record = NULL;

	  main_frm->session_params.engines.tympanograms_engine.edit_mode = false;
	}

	main_frm->Navigate(5,main_frm->session_params.engines.tympanograms_engine.caller_page_index);

	return;
}

void __fastcall load_tympanogram_grph_type(TForm1 *main_frm)
{
  p_engine_entry tympano_entry;
  TTympanograms_Def_Values *def_values;
  p_tympanogram_data data;


	tympano_entry = &main_frm->session_params.engines.tympanograms_engine;

	if ((!tympano_entry->edit_mode) || (main_frm->TympanoDefValCombo->ItemIndex < 0)) return;

	if (!ask_event("Voulez-vous charger le graphique type " + main_frm->TympanoDefValCombo->Items[main_frm->TympanoDefValCombo->ItemIndex].Text + " ? \n\r\n\r" +
	"Attention : les données de l'audiogramme en cours seront ecrasées par celles du graphique type !")) return;

	def_values = new TTympanograms_Def_Values(tympano_entry->grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_tympanogram_data)def_values->GetData(main_frm->TympanoDefValCombo->ItemIndex);

	  if (!data)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types [GetData] ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  if ((!load_tympanogram_oreille(main_frm,&data->oreille_droite,false,false)) || (!load_tympanogram_oreille(main_frm,&data->oreille_gauche,true,false))) return;

	  main_frm->OdRsEdit1->Text = IntToStr((int)data->oreille_droite.reflexes[0]);
	  main_frm->OdRsEdit2->Text = IntToStr((int)data->oreille_droite.reflexes[1]);
	  main_frm->OdRsEdit3->Text = IntToStr((int)data->oreille_droite.reflexes[2]);
	  main_frm->OdRsEdit4->Text = IntToStr((int)data->oreille_droite.reflexes[3]);

	  main_frm->OgRsEdit1->Text = IntToStr((int)data->oreille_gauche.reflexes[0]);
	  main_frm->OgRsEdit2->Text = IntToStr((int)data->oreille_gauche.reflexes[1]);
	  main_frm->OgRsEdit3->Text = IntToStr((int)data->oreille_gauche.reflexes[2]);
	  main_frm->OgRsEdit4->Text = IntToStr((int)data->oreille_gauche.reflexes[3]);

	  report_event(main_frm->TympanoDefValCombo->Items[main_frm->TympanoDefValCombo->ItemIndex].Text + " chargé avec succès.",mtInformation,false);

	}

  __finally
	{
	  delete def_values;
	}

	return;
}

void __fastcall add_tympanogram_grph_type(TForm1 *main_frm)
{
  TTympanograms_Def_Values *def_values;
  p_tympanogram_data data;
  t_tympanogram_data current_data;
  UnicodeString str;


	if (!ask_event("Ajouter les valeurs actuelles à la base de données des Graphiques Types ?")) return;

	if (main_frm->TympanoDefValCombo->Items->Count >= 12)
	{
	  report_event("Impossible d'ajouter un autre graphique type ! La limite définie est de 12 graphiques.",mtWarning,false);
	  return;
	}

	avcore_memset(&current_data,0,sizeof(current_data));

	if ((!fill_tympanogram_oreille(main_frm,&current_data.oreille_droite,false)) && (!fill_tympanogram_oreille(main_frm,&current_data.oreille_gauche,true)))
	{
	  report_event("Opération annulée ! le tympanogramme est vide, veuillez saisir les mesures de votre tympanogramme pour pouvoir utiliser cette fonctionnalité.",mtWarning,false);
	  return;
	}

	current_data.oreille_droite.reflexes[0] = (uint8)main_frm->OdRsEdit1->Text.ToInt();
	current_data.oreille_droite.reflexes[1] = (uint8)main_frm->OdRsEdit2->Text.ToInt();
	current_data.oreille_droite.reflexes[2] = (uint8)main_frm->OdRsEdit3->Text.ToInt();
	current_data.oreille_droite.reflexes[3] = (uint8)main_frm->OdRsEdit4->Text.ToInt();

	current_data.oreille_gauche.reflexes[0] = (uint8)main_frm->OgRsEdit1->Text.ToInt();
	current_data.oreille_gauche.reflexes[1] = (uint8)main_frm->OgRsEdit2->Text.ToInt();
	current_data.oreille_gauche.reflexes[2] = (uint8)main_frm->OgRsEdit3->Text.ToInt();
	current_data.oreille_gauche.reflexes[3] = (uint8)main_frm->OgRsEdit4->Text.ToInt();

	if (!InputQuery(main_frm->Caption,"Veuillez saisir le nom du Graphique Type :",str)) return;

	if (str == "")
	{
	  report_event("Opération annulée : vous ne pouvez pas ajouter un Graphique Type sans nom à votre base de données !",mtWarning,false);
	  return;
    }
	else if (str.Length() >= 23)
	{
	  report_event("Opération annulée : vous ne pouvez pas sépcifier un nom qui contient plus de 23 lettres !",mtWarning,false);
	  return;
	}

	str = str.LowerCase();

	avcore_memcpy(&current_data.name,(puchar)str.c_str(),str.Length() * 2);

	def_values = new TTympanograms_Def_Values(main_frm->session_params.engines.tympanograms_engine.grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_tympanogram_data)def_values->GetFirstData();

	  if (!data)
	  {
        if (def_values->GetLastError() != ERROR_SUCCESS)
		{
		  str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(def_values->GetLastError());
		  report_event(str,mtError,false);
		  return;
		}
	  }
	  else
	  {
		while (true)
		{
		  if (avcore_memcmp(&data->name,&current_data.name,str.Length() * 2))
		  {
			report_event("Opération annulée : vous avez déjà ajouté un graphique type du nom de " + str,mtWarning,false);
			return;
		  }
		  else if (avcore_memcmp(&current_data.oreille_droite,&data->oreille_droite,sizeof(current_data) - sizeof(current_data.name)))
		  {
			str = "Opération annulée : votre base de données contient déjà un graphique type identique à celui que vous comptez ajouter ! \n\r\n\r";
			str = str + "graphique identique = " + (PWCHAR)&data->name;
			report_event(str,mtWarning,false);
			return;
		  }

		  data = (p_tympanogram_data)def_values->GetNextData();

		  if (!data) break;
		}

		if (def_values->GetLastError() != ERROR_SUCCESS)
		{
		  str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(def_values->GetLastError());
		  report_event(str,mtError,false);
		  return;
        }
	  }

	  if (!def_values->Add(&current_data))
	  {
        str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  main_frm->TympanoDefValCombo->Items->Add(str);

      report_event("Graphique type ajouté avec succès",mtInformation,false);
	}

  __finally
	{
	  delete def_values;
	}

	return;
}

void __fastcall preview_tympanogram_grph(TForm1 *main_frm)
{
  p_engine_entry tympano_entry;
  p_consultation_record consult_record;
  p_tympanogram_record tympano_record;
  t_lilly_db_time_stamp_informations time_stamp_infos;
  bool empty;


	consult_record= (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if (!consult_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	tympano_entry = &main_frm->session_params.engines.tympanograms_engine;

	tympano_record = (p_tympanogram_record)tympano_entry->current_record;

	if ((!tympano_record) || (tympano_entry->edit_mode))
	{
	  report_event("Vous devez commencer par valider ce tympanogramme afin de pouvoir voir et imprimer le graphique !",mtWarning,false);
	  return;
	}

	TympPrevFrm = new TTympPrevFrm(main_frm);

  try
	{
	   {
		 p_patient_record pat_record = (p_patient_record)main_frm->session_params.engines.patients_engine.engine->code_to_record(main_frm->session_params.engines.patients_engine.engine,
		 main_frm->session_params.engines.patients_engine.db_handle,consult_record->patient_id);

		 if (!pat_record)
		 {
		   UnicodeString str = "Une erreur est survenue au niveau de [RecLookup] ! Le moteur patients a retourné l'erreur suivante : \n\r\n\r";
		   str = str + error_code_to_string(main_frm->session_params.engines.patients_engine.engine->error_code);
		   report_event(str,mtError,true);
		   return;
		 }

		 TympPrevFrm->NomLbl->Caption = format_name((PWCHAR)&pat_record->nom_prenom);
		 TympPrevFrm->CodepLbl->Caption = IntToStr((int)consult_record->patient_id);
         TympPrevFrm->adresse = format_name((PWCHAR)&pat_record->ville);
	   }

	   {
		 p_medecin_record med_record = (p_medecin_record)main_frm->session_params.engines.doctors_engine.engine->code_to_record(main_frm->session_params.engines.doctors_engine.engine,
		 main_frm->session_params.engines.doctors_engine.db_handle,consult_record->medecin_id);

		 if (!med_record)
		 {
		   UnicodeString str = "Une erreur est survenue au niveau de [RecLookup] ! Le moteur medecins a retourné l'erreur suivante : \n\r\n\r";
		   str = str + error_code_to_string(main_frm->session_params.engines.doctors_engine.engine->error_code);
		   report_event(str,mtError,true);
		   return;
		 }

		 TympPrevFrm->MedLbl->Caption = format_name((PWCHAR)&med_record->nom_prenom);
	   }

	   {
		 t_date_time today;

		 lilly_os_get_current_time_stamp(&today);

		 TympPrevFrm->DateImpLbl->Caption = date_to_string(&today);
	   }

	   if (!lilly_db_get_record_time_stamp_infos(tympano_entry->db_handle,lilly_db_index_to_record_offset(tympano_entry->db_handle,
	   tympano_record->code_tympanogram.unique_index),&time_stamp_infos))
	   {
		 UnicodeString str = "Une erreur est survenue au niveau de [GetTimeStamp] ! Le LillyDB a retourné l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(lilly_db_get_last_error(tympano_entry->db_handle));
		 report_event(str,mtError,true);
		 return;
	   }

	   {
		 p_operateur_record op_record = (p_operateur_record)main_frm->session_params.engines.operators_engine.engine->code_to_record(main_frm->session_params.engines.operators_engine.engine,
		 main_frm->session_params.engines.operators_engine.db_handle,time_stamp_infos.creation_stamp.operator_id);

		 if (!op_record)
		 {
		   UnicodeString str = "Une erreur est survenue au niveau de [RecLookup] ! Le moteur opérateurs a retourné l'erreur suivante : \n\r\n\r";
		   str = str + error_code_to_string(main_frm->session_params.engines.operators_engine.engine->error_code);
		   report_event(str,mtError,true);
		   return;
		 }

		 TympPrevFrm->OpLbl->Caption = format_name((PWCHAR)&op_record->nom_prenom);
	   }

	   empty = true;

	   for (int i = 0; i < sizeof(tympano_record->oreille_droite.valeurs) / sizeof(tympano_record->oreille_droite.valeurs[0]); i++)
	   {
		 if (tympano_record->oreille_droite.valeurs[i] != 0)
		 {
		   empty = false;
		   break;
		 }
	   }

	   TympPrevFrm->OdShape1->Visible = (empty == false);

	   if (!empty)
	   {
		 TympPrevFrm->OdTympDate1Lbl->Caption = "Tympanogramme du : " + date_to_string(&time_stamp_infos.creation_stamp.time_stamp);
	   }

	   empty = true;

	   for (int i = 0; i < sizeof(tympano_record->oreille_gauche.valeurs) / sizeof(tympano_record->oreille_gauche.valeurs[0]); i++)
	   {
		 if (tympano_record->oreille_gauche.valeurs[i] != 0)
		 {
		   empty = false;
		   break;
		 }
	   }

	   TympPrevFrm->OgShape1->Visible = (empty == false);

	   if (!empty)
	   {
		 TympPrevFrm->OgTympDate1Lbl->Caption = "Tympanogramme du : " + date_to_string(&time_stamp_infos.creation_stamp.time_stamp);
	   }

	   TympPrevFrm->tympano1 = tympano_record;
	   TympPrevFrm->tympano2 = NULL;

	   {
		 uint64 offset = 0;
		 int index = 0;

		  for (int i = 0; i < main_frm->TympanoListView->Items->Count; i++)
		  {
			if (main_frm->TympanoListView->Items->Item[i]->Checked)
			{
			  if (!offset)
			  {
				offset = (uint64)main_frm->TympanoListView->Items->Item[i]->SubItems->Strings[2].ToInt();
				index = i;
			  }
			  else
			  {
				report_event("Bien que vous avez sélectionné plusieurs Tympanogrammes, le logiciel ne prendra en compte que le premier Tympanogramme sélectionné.",mtInformation,false);
				break;
              }
			}
		  }

          TympPrevFrm->OdShape2->Visible = (offset != 0);
		  TympPrevFrm->OgShape2->Visible = (offset != 0);

		  if (offset)
		  {
			TympPrevFrm->tympano2 = (p_tympanogram_record)lilly_db_read_record(tympano_entry->db_handle,TYMPANOGRAM_RECORD_SIZE,offset);

			if (!TympPrevFrm->tympano2)
			{
			  UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
			  str = str + error_code_to_string(lilly_db_get_last_error(tympano_entry->db_handle));
			  report_event(str,mtError,true);
			  return;
			}

            empty = true;

			for (int i = 0; i < sizeof(TympPrevFrm->tympano2->oreille_droite.valeurs) / sizeof(TympPrevFrm->tympano2->oreille_droite.valeurs[0]); i++)
			{
			  if (TympPrevFrm->tympano2->oreille_droite.valeurs[i] != 0)
			  {
				empty = false;
				break;
			  }
			}

			TympPrevFrm->OdShape2->Visible = (empty == false);

			if (!empty)
			{
			  TympPrevFrm->OdTympDate2Lbl->Caption = "Tympanogramme du : " + main_frm->TympanoListView->Items->Item[index]->Caption;
			}

			empty = true;

			for (int i = 0; i < sizeof(TympPrevFrm->tympano2->oreille_gauche.valeurs) / sizeof(TympPrevFrm->tympano2->oreille_gauche.valeurs[0]); i++)
			{
			  if (TympPrevFrm->tympano2->oreille_gauche.valeurs[i] != 0)
			  {
				empty = false;
				break;
			  }
			}

			TympPrevFrm->OgShape2->Visible = (empty == false);

			if (!empty)
			{
			  TympPrevFrm->OgTympDate2Lbl->Caption = "Tympanogramme du : " + main_frm->TympanoListView->Items->Item[index]->Caption;
			}
		  }
	   }

	   TympPrevFrm->OdRsEdit1->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[0]);
	   TympPrevFrm->OdRsEdit2->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[1]);
	   TympPrevFrm->OdRsEdit3->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[2]);
	   TympPrevFrm->OdRsEdit4->Text = IntToStr((int)tympano_record->oreille_droite.reflexes[3]);

	   TympPrevFrm->OgRsEdit1->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[0]);
	   TympPrevFrm->OgRsEdit2->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[1]);
	   TympPrevFrm->OgRsEdit3->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[2]);
	   TympPrevFrm->OgRsEdit4->Text = IntToStr((int)tympano_record->oreille_gauche.reflexes[3]);

	   TympPrevFrm->Chart1->Title->Caption = "";
	   TympPrevFrm->Chart2->Title->Caption = "";

	   TympPrevFrm->ShowModal();
	}

  __finally
	{
	  delete TympPrevFrm;
	}

    return;
}


