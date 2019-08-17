#pragma hdrstop

#include "audiogram.hpp"

#include <operators_engine.h>
#include <patients_engine.h>
#include <consultations_engine.h>
#include <audiograms_engine.h>

#include <lilly_utils.h>
#include <lilly_os.h>

#include <db_signatures.h>

#include "unit14.h"


static const PWCHAR VA[2] = {(PWCHAR)L"OdVaEdit",(PWCHAR)L"OgVaEdit"};
static const PWCHAR VO[2] = {(PWCHAR)L"OdVoEdit",(PWCHAR)L"OgVoEdit"};
static const PWCHAR UCL[2] = {(PWCHAR)L"OdUclEdit",(PWCHAR)L"OgUclEdit"};


static bool __fastcall load_audiogram_oreille(TForm1 *main_frm,const p_audiogram_oreille oreille,const bool oreille_gauche,const bool read_only)
{
  TEdit *edit;
  bool max_va,max_vo,max_ucl;


	max_va = false;
	max_vo = false;
	max_ucl = false;

	for (int i = 1; i < 12; i++)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VA[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if ((!oreille) || (max_va))
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)oreille->va[i - 1]);

		if (edit->Text.ToInt() == 120)
		{
		  max_va = true;
		  edit->Color = TColor(0x8080FF);
		}
		else edit->Color = clWindow;
	  }

	  edit->ReadOnly = read_only;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VO[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if ((!oreille) || (max_vo))
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)oreille->vo[i - 1]);

		if (edit->Text.ToInt() == 70)
		{
		  max_vo = true;
		  edit->Color = TColor(0x8080FF);
		}
		else edit->Color = clWindow;
	  }

	  edit->ReadOnly = read_only;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(UCL[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if ((!oreille) || (max_ucl))
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)oreille->ucl[i - 1]);

		if (edit->Text.ToInt() == 120)
		{
		  max_ucl = true;
		  edit->Color = TColor(0x8080FF);
		}
		else edit->Color = clWindow;
	  }

	  edit->ReadOnly = read_only;
	}

	return true;
}

static bool __fastcall fill_audiogram_oreille(TForm1 *main_frm,const p_audiogram_oreille oreille,const bool oreille_gauche)
{
  TEdit *edit;
  int row_hits = 0;


	if (!oreille)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	for (int i = 1; i < 12; i++)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VA[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if (edit->Text == "")
	  {
		edit->Text = "0";
	  }

      if (edit->Text != "0")
	  {
		row_hits++;
	  }

	  oreille->va[i - 1] = StrToInt(edit->Text);

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VO[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if (edit->Text == "")
	  {
		edit->Text = "0";
	  }

	  if (edit->Text != "0")
	  {
		row_hits++;
	  }

	  oreille->vo[i - 1] = StrToInt(edit->Text);

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(UCL[oreille_gauche] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

      if (edit->Text == "")
	  {
		edit->Text = "0";
	  }

      if (edit->Text != "0")
	  {
		row_hits++;
	  }

	  oreille->ucl[i - 1] = StrToInt(edit->Text);
	}

	return (row_hits > 0);

}

static bool __fastcall load_confidential_checkboxes(TForm1 *main_frm,const uint64 parametres_confidentiels,const bool read_only)
{
  TCheckBox *check_box;

	for (int i = 22; i > 0; i--)
	{
	  check_box = dynamic_cast<TCheckBox *>(main_frm->FindComponent("ObsConChk" + IntToStr(i)));

	  if (!check_box)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  check_box->Checked = CHECK_ATTRIBUTE(parametres_confidentiels,(uint64)(1 << i));
	}

    return true;
}

static bool __fastcall fill_confidential_checkboxes(TForm1 *main_frm,const puint64 parametres_confidentiels)
{
  TCheckBox *check_box;


	for (int i = 22; i > 0; i--)
	{
	  check_box = dynamic_cast<TCheckBox *>(main_frm->FindComponent("ObsConChk" + IntToStr(i)));

	  if (!check_box)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  SET_ATTRIBUTE(*parametres_confidentiels,(uint64)((int)check_box->Checked << i));
	}

	return true;
}

bool __fastcall load_audiogram(TForm1 *main_frm)
{
  p_engine_entry audiogram_entry;
  p_patient_record pat_record;
  p_audiogram_record audiog_record;


	audiogram_entry = &main_frm->session_params.engines.audiograms_engine;

	pat_record = (p_patient_record)main_frm->session_params.engines.patients_engine.current_record;

	if ((!pat_record) || ((!audiogram_entry->current_record) && (!audiogram_entry->edit_mode)))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	if (!load_old_data_to_listview(&main_frm->session_params,AUDIOGRAM_DB_SIGNATURE,pat_record->code_patient.unique_index,main_frm->AudiogListView)) return false;

	audiog_record = (p_audiogram_record)audiogram_entry->current_record;

	main_frm->Switch_Annuler_Retour_Button(AUDIOGRAM_DB_SIGNATURE,audiogram_entry->edit_mode);

	if (!audiog_record)
	{
	  if ((!load_audiogram_oreille(main_frm,NULL,false,false)) || (!load_audiogram_oreille(main_frm,NULL,true,false)) || (!load_confidential_checkboxes(main_frm,0,false))) return false;

	  main_frm->WeberEdit1->ReadOnly = false;
	  main_frm->WeberEdit2->ReadOnly = false;
	  main_frm->WeberEdit3->ReadOnly = false;
	  main_frm->WeberEdit4->ReadOnly = false;
	  main_frm->WeberEdit5->ReadOnly = false;

	  main_frm->WeberEdit1->Text = "0";
	  main_frm->WeberEdit2->Text = "0";
	  main_frm->WeberEdit3->Text = "0";
	  main_frm->WeberEdit4->Text = "0";
	  main_frm->WeberEdit5->Text = "0";

	  return true;
	}

	if ((!load_audiogram_oreille(main_frm,&audiog_record->oreille_droite,false,(audiogram_entry->edit_mode == false))) ||
	(!load_audiogram_oreille(main_frm,&audiog_record->oreille_gauche,true,(audiogram_entry->edit_mode == false))) ||
	(!load_confidential_checkboxes(main_frm,audiog_record->parametres_confidentiels,(audiogram_entry->edit_mode == false)))) return false;

	main_frm->WeberEdit1->ReadOnly = (audiogram_entry->edit_mode == false);
	main_frm->WeberEdit2->ReadOnly = (audiogram_entry->edit_mode == false);
	main_frm->WeberEdit3->ReadOnly = (audiogram_entry->edit_mode == false);
	main_frm->WeberEdit4->ReadOnly = (audiogram_entry->edit_mode == false);
	main_frm->WeberEdit5->ReadOnly = (audiogram_entry->edit_mode == false);

	main_frm->WeberEdit1->Text = IntToStr((int)audiog_record->weber[0]);
	main_frm->WeberEdit2->Text = IntToStr((int)audiog_record->weber[1]);
	main_frm->WeberEdit3->Text = IntToStr((int)audiog_record->weber[2]);
	main_frm->WeberEdit4->Text = IntToStr((int)audiog_record->weber[3]);
	main_frm->WeberEdit5->Text = IntToStr((int)audiog_record->weber[4]);

	main_frm->AudiogObsMemo->ReadOnly = (audiogram_entry->edit_mode == false);

	main_frm->AudiogDefValCombo->Enabled = audiogram_entry->edit_mode;

	load_blob(audiogram_entry,main_frm->AudiogObsMemo,audiog_record->code_audiogram.unique_index,t_lilly_db_observations_confidentielles_blob_type);

	if (main_frm->AudiogObsMemo->Lines->Count > 0)
	{
	  audiogram_entry->observation_crc32 = lilly_crc32_buffer((puchar)main_frm->AudiogObsMemo->Text.c_str(),main_frm->AudiogObsMemo->Text.Length() * 2,0);
	}

	if (!audiogram_entry->edit_mode)
	{
	  return true;
	}
	else return load_grph_list(audiogram_entry,AUDIOGRAM_DB_SIGNATURE,main_frm->AudiogDefValCombo);
}

void __fastcall unload_audiogram(TForm1 *main_frm)
{

	main_frm->AudiogListView->Items->Clear();

	main_frm->AudiogDefValCombo->Items->Clear();

	main_frm->AudiogObsMemo->Lines->Clear();

	main_frm->session_params.engines.audiograms_engine.current_record = NULL;
	main_frm->session_params.engines.audiograms_engine.observation_crc32 = 0;
	main_frm->session_params.engines.audiograms_engine.edit_mode = false;

	return;
}

void __fastcall validate_audiogram(TForm1 *main_frm)
{
  p_engine_entry audiogram_entry;
  p_audiogram_record audiog_record,rec_ptr;
  p_consultation_record consult_record;
  p_lilly_db_engine db_engine;
  uint64 offset;
  t_audiogram_record record;


	audiogram_entry = &main_frm->session_params.engines.audiograms_engine;

	if (!audiogram_entry->edit_mode)
	{
	  main_frm->Navigate(4,audiogram_entry->caller_page_index);
	  return;
	}

	db_engine = audiogram_entry->engine;

	consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if ((!consult_record) || (!db_engine))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	avcore_memset(&record,0,sizeof(record));

	audiog_record = (p_audiogram_record)audiogram_entry->current_record;

	if (!audiog_record)
	{
	  rec_ptr = &record;
	}
	else rec_ptr = audiog_record;

	if ((!fill_audiogram_oreille(main_frm,&rec_ptr->oreille_droite,false)) && (!fill_audiogram_oreille(main_frm,&rec_ptr->oreille_gauche,true)))
	{
	  report_event("Vous ne pouvez pas valider un Audiogramme vide !",mtWarning,false);
	  return;
	}

	rec_ptr->weber[0] = (uint8)main_frm->WeberEdit1->Text.ToInt();
	rec_ptr->weber[1] = (uint8)main_frm->WeberEdit2->Text.ToInt();
	rec_ptr->weber[2] = (uint8)main_frm->WeberEdit3->Text.ToInt();
	rec_ptr->weber[3] = (uint8)main_frm->WeberEdit4->Text.ToInt();
	rec_ptr->weber[4] = (uint8)main_frm->WeberEdit5->Text.ToInt();

	if (!fill_confidential_checkboxes(main_frm,&rec_ptr->parametres_confidentiels)) return;

	if (!audiog_record)
	{
	  if (consult_record->audiogram_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  if (!db_engine->append_record(db_engine,audiogram_entry->db_handle,rec_ptr))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur Audiogrammes a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(audiogram_entry->db_handle);

	  audiog_record = (p_audiogram_record)lilly_db_read_record(audiogram_entry->db_handle,sizeof(record),offset);

	  if (!audiog_record)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(audiogram_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  main_frm->Consultation_OnChange_Event_Handler(AUDIOGRAM_DB_SIGNATURE,audiog_record->code_audiogram.unique_index,t_record_state_change_type);

	  report_event("Audiogramme ajouté avec succès.",mtInformation,false);
	}
	else
	{
      if (!consult_record->audiogram_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(audiogram_entry->db_handle);

	  if (!db_engine->edit_record(db_engine,audiogram_entry->db_handle,rec_ptr,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur Audiogrammes a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  report_event("Audiogramme modifié avec succès.",mtInformation,false);
	}

	if ((audiogram_entry->observation_crc32) && (main_frm->AudiogObsMemo->Text == ""))
	{
	  delete_blob(audiogram_entry,consult_record->audiogram_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((!audiogram_entry->observation_crc32) && (main_frm->AudiogObsMemo->Text != ""))
	{
	  add_blob(audiogram_entry,main_frm->AudiogObsMemo,consult_record->audiogram_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((audiogram_entry->observation_crc32) && (main_frm->AudiogObsMemo->Text != ""))
	{
	  update_blob(audiogram_entry,main_frm->AudiogObsMemo,consult_record->audiogram_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}

	audiogram_entry->edit_mode = false;

	main_frm->Switch_Annuler_Retour_Button(AUDIOGRAM_DB_SIGNATURE,false);

	//main_frm->Navigate(4,audiogram_entry->caller_page_index);

	return;
}

void __fastcall edit_audiogram(TForm1 *main_frm)
{
  TEdit *edit;


	if (main_frm->session_params.engines.audiograms_engine.edit_mode) return;

	if (!ask_event("Modifier cet Audiogramme ?")) return;

	main_frm->session_params.engines.audiograms_engine.edit_mode = true;

	main_frm->WeberEdit1->ReadOnly = false;
	main_frm->WeberEdit2->ReadOnly = false;
	main_frm->WeberEdit3->ReadOnly = false;
	main_frm->WeberEdit4->ReadOnly = false;
	main_frm->WeberEdit5->ReadOnly = false;

	main_frm->AudiogDefValCombo->Enabled = true;

	main_frm->AudiogObsMemo->ReadOnly = false;

	for (int i = 11; i > 0; i--)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VA[0] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VA[1] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VO[0] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(VO[1] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(UCL[0] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(UCL[1] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;
	}

	main_frm->Switch_Annuler_Retour_Button(AUDIOGRAM_DB_SIGNATURE,true);

	return;
}

void __fastcall delete_audiogram(TForm1 *main_frm)
{
  p_engine_entry audiogram_entry;
  p_audiogram_record audiog_record;
  uint64 offset;


	if (!main_frm->session_params.engines.consultations_engine.current_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	audiogram_entry = &main_frm->session_params.engines.audiograms_engine;

	audiog_record = (p_audiogram_record)audiogram_entry->current_record;

	if (!ask_event("Êtes-vous sûres de vouloir supprimer cet Audiogramme ?")) return;

	if (!audiog_record)
	{
	  p_consultation_record consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	  if ((!consult_record) || (consult_record->audiogram_id != audiog_record->code_audiogram.unique_index))
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(audiogram_entry->db_handle);

	  if (!lilly_db_delete_record(audiogram_entry->db_handle,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [DeleteRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(audiogram_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  audiogram_entry->current_record = NULL;
	  audiogram_entry->edit_mode = false;

	  report_event("Audiogramme supprimé avec succès.",mtInformation,false);
	}

	main_frm->Consultation_OnChange_Event_Handler(AUDIOGRAM_DB_SIGNATURE,0,t_record_state_change_type);

	main_frm->Navigate(4,audiogram_entry->caller_page_index);

	return;
}

void __fastcall cancel_audiogram(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.audiograms_engine.edit_mode)
	{
	  if (!ask_event("Annuler l'opération en cours ?")) return;

	  main_frm->session_params.engines.audiograms_engine.current_record = NULL;

	  main_frm->session_params.engines.audiograms_engine.edit_mode = false;
	}

	main_frm->Navigate(4,main_frm->session_params.engines.audiograms_engine.caller_page_index);

	return;
}

void __fastcall load_audiogram_grph_type(TForm1 *main_frm)
{
  p_engine_entry audiogram_entry;
  TAudiograms_Def_Values *def_values;
  p_audiogram_data data;


	audiogram_entry = &main_frm->session_params.engines.audiograms_engine;

	if ((!audiogram_entry->edit_mode) || (main_frm->AudiogDefValCombo->ItemIndex < 0)) return;

	if (!ask_event("Voulez-vous charger le graphique type " + main_frm->AudiogDefValCombo->Items[main_frm->AudiogDefValCombo->ItemIndex].Text + " ? \n\r\n\r" +
	"Attention : les données de l'audiogramme en cours seront ecrasées par celles du graphique type !")) return;

	def_values = new TAudiograms_Def_Values(audiogram_entry->grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_audiogram_data)def_values->GetData(main_frm->AudiogDefValCombo->ItemIndex);

	  if (!data)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types [GetData] ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  if ((!load_audiogram_oreille(main_frm,&data->oreille_droite,false,false)) || (!load_audiogram_oreille(main_frm,&data->oreille_gauche,true,false))) return;

	  main_frm->WeberEdit1->Text = IntToStr((int)data->weber[0]);
	  main_frm->WeberEdit2->Text = IntToStr((int)data->weber[1]);
	  main_frm->WeberEdit3->Text = IntToStr((int)data->weber[2]);
	  main_frm->WeberEdit4->Text = IntToStr((int)data->weber[3]);
	  main_frm->WeberEdit5->Text = IntToStr((int)data->weber[4]);

	  report_event(main_frm->AudiogDefValCombo->Items[main_frm->AudiogDefValCombo->ItemIndex].Text + " chargé avec succès.",mtInformation,false);

	}

  __finally
	{
	  delete def_values;
	}

    return;
}

void __fastcall add_audiogram_grph_type(TForm1 *main_frm)
{
  TAudiograms_Def_Values *def_values;
  p_audiogram_data data;
  t_audiogram_data current_data;
  UnicodeString str;


	if (!ask_event("Ajouter les mesures actuelles à la base de données des Graphiques Types ?")) return;

	if (main_frm->AudiogDefValCombo->Items->Count >= 12)
	{
	  report_event("Impossible d'ajouter un autre graphique type ! La limite définie est de 12 graphiques.",mtWarning,false);
	  return;
	}

	avcore_memset(&current_data,0,sizeof(current_data));

	if ((!fill_audiogram_oreille(main_frm,&current_data.oreille_droite,false)) && (!fill_audiogram_oreille(main_frm,&current_data.oreille_gauche,true)))
	{
	  report_event("Opération annulée ! l'audiogramme est vide, veuillez procéder à la saisie des mesures afin de profiter de cette fonctionalité.",mtWarning,false);
	  return;
	}

	current_data.weber[0] = (uint8)main_frm->WeberEdit1->Text.ToInt();
	current_data.weber[1] = (uint8)main_frm->WeberEdit2->Text.ToInt();
	current_data.weber[2] = (uint8)main_frm->WeberEdit3->Text.ToInt();
	current_data.weber[3] = (uint8)main_frm->WeberEdit4->Text.ToInt();
	current_data.weber[4] = (uint8)main_frm->WeberEdit5->Text.ToInt();

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

	def_values = new TAudiograms_Def_Values(main_frm->session_params.engines.audiograms_engine.grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_audiogram_data)def_values->GetFirstData();

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

		  data = (p_audiogram_data)def_values->GetNextData();

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

	  main_frm->AudiogDefValCombo->Items->Add(str);

      report_event("Graphique type ajouté avec succès",mtInformation,false);
	}

  __finally
	{
	  delete def_values;
	}

	return;
}

void __fastcall preview_audiogram_grph(TForm1 *main_frm)
{
  p_engine_entry audiog_entry;
  p_consultation_record consult_record;
  p_audiogram_record audiog_record,ancien_va_record;
  int selected_va_index;
  t_lilly_db_time_stamp_informations time_stamp_infos;
  bool od_empty,og_empty,od1_empty,og1_empty;


	consult_record= (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if (!consult_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	audiog_entry = &main_frm->session_params.engines.audiograms_engine;

	audiog_record = (p_audiogram_record)audiog_entry->current_record;

	if ((!audiog_record) || (audiog_entry->edit_mode))
	{
	  report_event("Vous devez commencer par valider cet Audiogramme afin de pouvoir prévisualiser et imprimer le graphique !",mtWarning,false);
	  return;
	}

	TAudiogPrevFrm *AudioPrevFrm = new TAudiogPrevFrm(main_frm);

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

		 AudioPrevFrm->NomLbl->Caption = format_name((PWCHAR)&pat_record->nom_prenom);
		 AudioPrevFrm->CodepLbl->Caption = IntToStr((int)consult_record->patient_id);
		 AudioPrevFrm->adresse = format_name((PWCHAR)&pat_record->ville);
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

		 AudioPrevFrm->MedLbl->Caption = format_name((PWCHAR)&med_record->nom_prenom);
	   }

	   {
		 t_date_time today;

		 lilly_os_get_current_time_stamp(&today);

		 AudioPrevFrm->DateImpLbl->Caption = date_to_string(&today);
	   }

	   if (!lilly_db_get_record_time_stamp_infos(audiog_entry->db_handle,lilly_db_index_to_record_offset(audiog_entry->db_handle,audiog_record->code_audiogram.unique_index),&time_stamp_infos))
	   {
		 UnicodeString str = "Une erreur est survenue au niveau de [GetTimeStamp] ! Le LillyDB a retourné l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(lilly_db_get_last_error(audiog_entry->db_handle));
		 report_event(str,mtError,true);
		 return;
	   }

	   AudioPrevFrm->audiogram_date = date_to_string(&time_stamp_infos.creation_stamp.time_stamp);

	   AudioPrevFrm->OdDateLbl->Caption = "Audiogramme du : " + AudioPrevFrm->audiogram_date;
	   AudioPrevFrm->OgDateLbl->Caption = AudioPrevFrm->OdDateLbl->Caption;

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

		 AudioPrevFrm->OpLbl->Caption = format_name((PWCHAR)&op_record->nom_prenom);
	   }

	   od_empty = true;

	   for (int i = 0; i < 13 ; i++)
	   {
		 if ((audiog_record->oreille_droite.va[i]) || (audiog_record->oreille_droite.vo[i]) || (audiog_record->oreille_droite.ucl[i]))
		 {
		   od_empty = false;
		   break;
		 }
	   }

	   og_empty = true;

	   for (int i = 0; i < 13 ; i++)
	   {
		 if ((audiog_record->oreille_gauche.va[i]) || (audiog_record->oreille_gauche.vo[i]) || (audiog_record->oreille_gauche.ucl[i]))
		 {
		   og_empty = false;
		   break;
		 }
	   }

	   selected_va_index = -1;

	   for (int i = 0; i < main_frm->AudiogListView->Items->Count; i++)
	   {
		 if (main_frm->AudiogListView->Items->Item[i]->Checked)
		 {
		   selected_va_index = i;
		   break;
		 }
	   }

	   if (selected_va_index < 0)
	   {
		 ancien_va_record = NULL;
		 AudioPrevFrm->OdVaShape->Visible = false;
		 AudioPrevFrm->OgVaShape->Visible = false;
	   }
	   else
	   {
		 uint64 offset = (uint64)StrToInt(main_frm->AudiogListView->Items->Item[selected_va_index]->SubItems->Strings[1]);

		 ancien_va_record = (p_audiogram_record)lilly_db_read_record(audiog_entry->db_handle,AUDIOGRAM_RECORD_SIZE,offset);

		 if (!ancien_va_record)
		 {
		   UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		   str = str + error_code_to_string(lilly_db_get_last_error(audiog_entry->db_handle));
		   report_event(str,mtError,true);
		   return;
		 }

		 od1_empty = true;

		 for (int i = 0; i < 13 ; i++)
		 {
		   if ((ancien_va_record->oreille_droite.va[i]) || (ancien_va_record->oreille_droite.vo[i]) || (ancien_va_record->oreille_droite.ucl[i]))
		   {
			 od1_empty = false;
			 break;
		   }
		 }

		 og1_empty = true;

		 for (int i = 0; i < 13 ; i++)
		 {
		   if ((ancien_va_record->oreille_gauche.va[i]) || (ancien_va_record->oreille_gauche.vo[i]) || (ancien_va_record->oreille_gauche.ucl[i]))
		   {
			 og1_empty = false;
			 break;
		   }
		 }

		 if (!lilly_db_get_record_time_stamp_infos(audiog_entry->db_handle,offset,&time_stamp_infos))
		 {
		   UnicodeString str = "Une erreur est survenue au niveau de [GetTimeStamp] ! Le LillyDB a retourné l'erreur suivante : \n\r\n\r";
		   str = str + error_code_to_string(lilly_db_get_last_error(audiog_entry->db_handle));
		   report_event(str,mtError,true);
		   return;
		 }

		 AudioPrevFrm->ancien_va_date = date_to_string(&time_stamp_infos.creation_stamp.time_stamp);

		 if (!od1_empty)
		 {
		   AudioPrevFrm->OdVaDateLbl->Caption = "VA du " + AudioPrevFrm->ancien_va_date;
		 }

		 if (!og1_empty)
		 {
		   AudioPrevFrm->OgVaDateLbl->Caption = "VA du " + AudioPrevFrm->ancien_va_date;
		 }

		 AudioPrevFrm->OdVaShape->Visible = (od1_empty == false);
		 AudioPrevFrm->OgVaDateLbl->Visible = (og1_empty == false);
	   }

	   AudioPrevFrm->ImageList1->GetBitmap(audiog_record->weber[0],AudioPrevFrm->WeberImg1->Picture->Bitmap);
	   AudioPrevFrm->ImageList1->GetBitmap(audiog_record->weber[0],AudioPrevFrm->WeberImg2->Picture->Bitmap);
	   AudioPrevFrm->ImageList1->GetBitmap(audiog_record->weber[0],AudioPrevFrm->WeberImg3->Picture->Bitmap);
	   AudioPrevFrm->ImageList1->GetBitmap(audiog_record->weber[0],AudioPrevFrm->WeberImg4->Picture->Bitmap);
	   AudioPrevFrm->ImageList1->GetBitmap(audiog_record->weber[0],AudioPrevFrm->WeberImg5->Picture->Bitmap);

	   AudioPrevFrm->Chart1->Title->Caption = "";

	   AudioPrevFrm->audiog_record = audiog_record;
	   AudioPrevFrm->ancien_va_record = ancien_va_record;

	   AudioPrevFrm->ShowModal();
	}

  __finally
	{
	  delete AudioPrevFrm;
	}

    return;
}


