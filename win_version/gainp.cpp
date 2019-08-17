#pragma hdrstop

#include "gainp.hpp"

#include <operators_engine.h>
#include <patients_engine.h>
#include <consultations_engine.h>
#include <gainp_engine.h>

#include <db_signatures.h>

#include <lilly_io.h>
#include <lilly_os.h>
#include <lilly_utils.h>

#include "unit10.h"


static const PWCHAR GAINP_VA  = (PWCHAR)L"GainpVaEdit";
static const PWCHAR GAINP_VO  = (PWCHAR)L"GainpVoEdit";
static const PWCHAR GAINP_UCL = (PWCHAR)L"GainpUclEdit";


static bool __fastcall load_mesures(TForm1 *main_frm,const p_gainp_mesures mesures,const bool read_only)
{
  TEdit *edit;
  bool max_va,max_vo,max_ucl;


	max_va = false;
	max_vo = false;
	max_ucl = false;

	for (int i = 1; i < 12; i++)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_VA + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if ((!mesures) || (max_va))
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)mesures->sa[i - 1]);

		if (edit->Text.ToInt() == 120)
		{
		  max_va = true;
		  edit->Color = TColor(0x8080FF);
		}
	  }

	  edit->ReadOnly = read_only;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_VO + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if ((!mesures) || (max_vo))
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)mesures->sp[i - 1]);

		if (edit->Text.ToInt() == 70)
		{
		  max_vo = true;
		  edit->Color = TColor(0x8080FF);
		}
	  }

	  edit->ReadOnly = read_only;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_UCL + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if ((!mesures) || (max_ucl))
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)mesures->mcl[i - 1]);

		if (edit->Text.ToInt() == 120)
		{
		  max_ucl = true;
		  edit->Color = TColor(0x8080FF);
		}
	  }

	  edit->ReadOnly = read_only;
	}

	return true;
}

static bool __fastcall save_mesures(TForm1 *main_frm,const p_gainp_mesures mesures)
{
  TEdit *edit;
  int row_hits = 0;


	if (!mesures)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	for (int i = 1; i < 12; i++)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_VA + IntToStr(i)));

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

	  mesures->sa[i - 1] = StrToInt(edit->Text);

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_VO + IntToStr(i)));

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

	  mesures->sp[i - 1] = StrToInt(edit->Text);

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_UCL + IntToStr(i)));

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

	  mesures->mcl[i - 1] = StrToInt(edit->Text);
	}

	return (row_hits > 0);

}

bool __fastcall load_gainp(TForm1 *main_frm)
{
  p_engine_entry gainp_entry;
  p_patient_record pat_record;
  p_gainp_record gainp_record;


	gainp_entry = &main_frm->session_params.engines.gainprots_engine;

	pat_record = (p_patient_record)main_frm->session_params.engines.patients_engine.current_record;

	if ((!pat_record) || ((!gainp_entry->current_record) && (!gainp_entry->edit_mode)))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	if (!load_old_data_to_listview(&main_frm->session_params,GAIN_PROTHETIQUE_DB_SIGNATURE,pat_record->code_patient.unique_index,main_frm->GainpListView)) return false;

	gainp_record = (p_gainp_record)gainp_entry->current_record;

	if (!lilly_io_file_exists((puchar)&main_frm->session_params.gprefs_path->path_data))
	{
	  report_event("Un composant nécessaire au bon fonctionnement du logiciel a été supprimé ! Pour corriger ce problème veuillez re-installer le logiciel.",mtError,true);
	  return false;
    }

	main_frm->GainpRefCombo->Items->LoadFromFile((PWCHAR)&main_frm->session_params.gprefs_path->path_data);

	main_frm->Switch_Annuler_Retour_Button(AUDIOMETRIE_VOCALE_DB_SIGNATURE,gainp_entry->edit_mode);

	if (!gainp_record)
	{
	  if (!load_mesures(main_frm,NULL,false)) return false;

	  main_frm->GainpOgChk->Checked = false;
	  main_frm->GainpOdChk->Checked = false;
	  main_frm->GainpChlChk->Checked = false;

	  main_frm->PulseRadio->Checked = true;
	  main_frm->ContourRadio->Checked = true;

	  main_frm->GainpObsMemo->ReadOnly = false;

	  main_frm->GainpDefValCombo->Enabled = true;

	  main_frm->GainpRefCombo->Visible = true;
	  main_frm->GainpRefCombo->ItemIndex = -1;

	  main_frm->GainpRefLbl->Visible = false;

	  return true;
	}

	if (!load_mesures(main_frm,&gainp_record->mesures,(gainp_entry->edit_mode == false))) return false;

	if (CHECK_ATTRIBUTE(gainp_record->oreille,GAINP_OREILLE_CHAMPS_LIBRE))
	{
	  main_frm->GainpChlChk->State = cbChecked;
	  main_frm->GainpOdChk->State = cbUnchecked;
	  main_frm->GainpOgChk->State = cbUnchecked;
	}
	else
	{
	  if (CHECK_ATTRIBUTE(gainp_record->oreille,GAINP_OREILLE_DROITE))
	  {
		main_frm->GainpOdChk->State = cbChecked;
	  }
	  else main_frm->GainpOdChk->State = cbUnchecked;

	  if (CHECK_ATTRIBUTE(gainp_record->oreille,GAINP_OREILLE_GAUCHE))
	  {
		main_frm->GainpOgChk->State = cbChecked;
	  }
	  else main_frm->GainpOgChk->State = cbUnchecked;

      main_frm->GainpChlChk->State = cbUnchecked;
    }

	if (gainp_record->nature == GAINP_NATURE_SON_PULSE)
	{
	  main_frm->PulseRadio->Checked = true;
	}
	else if (gainp_record->nature == GAINP_NATURE_SON_PURE)
	{
	  main_frm->PurRadio->Checked = true;
	}
	else if (gainp_record->nature == GAINP_NATURE_SON_BLANC)
	{
      main_frm->BlancRadio->Checked = true;
    }

	if (gainp_record->prothese == GAINP_PROTHESE_TYPE_CONTOUR)
	{
	  main_frm->ContourRadio->Checked = true;
	}
	else if (gainp_record->prothese == GAINP_PROTHESE_TYPE_INTRA)
	{
	  main_frm->MesureRadio->Checked = true;
	}
	else if (gainp_record->prothese == GAINP_PROTHESE_TYPE_RIC)
	{
      main_frm->RicRadio->Checked = true;
    }

	main_frm->GainpObsMemo->ReadOnly = (gainp_entry->edit_mode == false);

	main_frm->GainpDefValCombo->Enabled = gainp_entry->edit_mode;

	if ((int)gainp_record->appareil_id >= main_frm->GainpRefCombo->Items->Count)
	{
	  report_event("Un composant nécessaire au bon fonctionnement du logiciel a été altéré ! veuillez re-installer le logiciel.",mtError,true);
	  return false;
	}

	main_frm->GainpRefCombo->ItemIndex = (int)gainp_record->appareil_id;

	if ((gainp_record->appareil_id != 0) && (gainp_record->appareil_id != MAXWORD))
	{
      main_frm->GainpRefCombo->ItemIndex = main_frm->GainpRefCombo->ItemIndex + 1;
	}

	if (gainp_entry->edit_mode)
	{
	  main_frm->GainpRefCombo->Visible = true;
	  main_frm->GainpRefLbl->Visible = false;
	}
	else
	{
	  main_frm->GainpRefCombo->Visible = false;
	  main_frm->GainpRefLbl->Caption = main_frm->GainpRefCombo->Items->Strings[main_frm->GainpRefCombo->ItemIndex - 1];
	  main_frm->GainpRefLbl->Visible = true;
	}

	load_blob(gainp_entry,main_frm->GainpObsMemo,gainp_record->code_gainp.unique_index,t_lilly_db_observations_confidentielles_blob_type);

	if (main_frm->GainpObsMemo->Lines->Count > 0)
	{
	  gainp_entry->observation_crc32 = lilly_crc32_buffer((puchar)main_frm->GainpObsMemo->Text.c_str(),main_frm->GainpObsMemo->Text.Length() * 2,0);
	}

	if (!gainp_entry->edit_mode)
	{
	  return true;
	}
	else return load_grph_list(gainp_entry,GAIN_PROTHETIQUE_DB_SIGNATURE,main_frm->GainpDefValCombo);
}

void __fastcall unload_gainp(TForm1 *main_frm)
{

	main_frm->GainpRefCombo->Items->Clear();

	main_frm->GainpObsMemo->Lines->Clear();

	main_frm->GainpRefCombo->Items->Clear();

    main_frm->GainpListView->Items->Clear();

	main_frm->GainpRefLbl->Caption = "";
	main_frm->GainpRefLbl->Visible = true;

	main_frm->session_params.engines.gainprots_engine.current_record = NULL;
	main_frm->session_params.engines.gainprots_engine.observation_crc32 = 0;
	main_frm->session_params.engines.gainprots_engine.edit_mode = false;

    return;
}

void __fastcall validate_gainp(TForm1 *main_frm)
{
  p_engine_entry gainp_entry;
  p_gainp_record gainp_record,rec_ptr;
  p_consultation_record consult_record;
  p_lilly_db_engine db_engine;
  uint64 offset;
  t_gainp_record record;


	gainp_entry = &main_frm->session_params.engines.gainprots_engine;

	if (!gainp_entry->edit_mode)
	{
	  main_frm->Navigate(7,gainp_entry->caller_page_index);
	  return;
	}

	db_engine = gainp_entry->engine;

	consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if ((!consult_record) || (!db_engine))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	avcore_memset(&record,0,sizeof(record));

	gainp_record = (p_gainp_record)gainp_entry->current_record;

	if (!gainp_record)
	{
	  rec_ptr = &record;
	}
	else rec_ptr = gainp_record;

	if (!save_mesures(main_frm,&rec_ptr->mesures))
	{
	  report_event("Vous ne pouvez pas valider un Gain Prothétique vide !",mtWarning,false);
	  return;
	}

	if (main_frm->GainpChlChk->State == cbChecked)
	{
	  rec_ptr->oreille = GAINP_OREILLE_CHAMPS_LIBRE;
	}
	else
	{
	  if (main_frm->GainpOdChk->State == cbChecked)
	  {
		SET_ATTRIBUTE(rec_ptr->oreille,GAINP_OREILLE_DROITE);
	  }

	  if (main_frm->GainpOgChk->State == cbChecked)
	  {
		SET_ATTRIBUTE(rec_ptr->oreille,GAINP_OREILLE_GAUCHE);
	  }
	}

	if (main_frm->PulseRadio->Checked == true)
	{
	  rec_ptr->nature = GAINP_NATURE_SON_PULSE;
	}
	else if (main_frm->PurRadio->Checked == true)
	{
	  rec_ptr->nature = GAINP_NATURE_SON_PURE;
	}
	else if (main_frm->BlancRadio->Checked == true)
	{
	  rec_ptr->nature = GAINP_NATURE_SON_BLANC;
	}

	if (main_frm->ContourRadio->Checked == true)
	{
	  rec_ptr->prothese = GAINP_PROTHESE_TYPE_CONTOUR;
	}
	else if (main_frm->MesureRadio->Checked == true)
	{
	  rec_ptr->prothese = GAINP_PROTHESE_TYPE_INTRA;
	}
	else if (main_frm->RicRadio->Checked)
	{
	  rec_ptr->prothese = GAINP_PROTHESE_TYPE_RIC;
	}

	rec_ptr->appareil_id = (uint16)main_frm->GainpRefCombo->ItemIndex;

	if (!gainp_record)
	{
	  if (consult_record->gainp_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  if (!db_engine->append_record(db_engine,gainp_entry->db_handle,rec_ptr))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur Gains Prothétiques a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(gainp_entry->db_handle);

	  gainp_record = (p_gainp_record)lilly_db_read_record(gainp_entry->db_handle,sizeof(record),offset);

	  if (!gainp_record)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(gainp_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  main_frm->Consultation_OnChange_Event_Handler(GAIN_PROTHETIQUE_DB_SIGNATURE,gainp_record->code_gainp.unique_index,t_record_state_change_type);

	  report_event("Gain Prothétique ajouté avec succès.",mtInformation,false);
	}
	else
	{
	  if (!consult_record->gainp_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(gainp_entry->db_handle);

	  if (!db_engine->edit_record(db_engine,gainp_entry->db_handle,rec_ptr,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur Gains Prothétiques a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  report_event("Gain Prothétique modifié avec succès.",mtInformation,false);
	}

	if ((gainp_entry->observation_crc32) && (main_frm->GainpObsMemo->Text == ""))
	{
	  delete_blob(gainp_entry,consult_record->gainp_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((!gainp_entry->observation_crc32) && (main_frm->GainpObsMemo->Text != ""))
	{
	  add_blob(gainp_entry,main_frm->GainpObsMemo,consult_record->gainp_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((gainp_entry->observation_crc32) && (main_frm->GainpObsMemo->Text != ""))
	{
	  update_blob(gainp_entry,main_frm->GainpObsMemo,consult_record->gainp_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}

	main_frm->Switch_Annuler_Retour_Button(AUDIOMETRIE_VOCALE_DB_SIGNATURE,false);

	//main_frm->Navigate(7,gainp_entry->caller_page_index);

	return;
}

void __fastcall edit_gainp(TForm1 *main_frm)
{
  TEdit *edit;


	if (main_frm->session_params.engines.gainprots_engine.edit_mode) return;

	if (!ask_event("Modifier ce Gain Prothétique ?")) return;

	main_frm->session_params.engines.gainprots_engine.edit_mode = true;

	main_frm->GainpDefValCombo->Enabled = true;

	main_frm->GainpObsMemo->ReadOnly = false;

	main_frm->GainpRefLbl->Caption = "";
	main_frm->GainpRefLbl->Visible = false;

	main_frm->GainpRefCombo->Visible = true;

	for (int i = 11; i > 0; i--)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_VA + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_VO + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(GAINP_UCL + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  edit->ReadOnly = false;

	}

	main_frm->Switch_Annuler_Retour_Button(AUDIOMETRIE_VOCALE_DB_SIGNATURE,true);

	return;
}

void __fastcall delete_gainp(TForm1 *main_frm)
{
  p_engine_entry gainp_entry;
  p_gainp_record gainp_record;
  uint64 offset;


	if (!main_frm->session_params.engines.consultations_engine.current_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	gainp_entry = &main_frm->session_params.engines.gainprots_engine;

	gainp_record = (p_gainp_record)gainp_entry->current_record;

	if (!ask_event("Êtes-vous sûres de vouloir supprimer ce Gain Prothétique ?")) return;

	if (!gainp_record)
	{
	  p_consultation_record consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	  if ((!consult_record) || (consult_record->gainp_id != gainp_record->code_gainp.unique_index))
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(gainp_entry->db_handle);

	  if (!lilly_db_delete_record(gainp_entry->db_handle,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [DeleteRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(gainp_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  consult_record->gainp_id = 0;

	  main_frm->session_params.engines.consultations_engine.edit_mode = true;

	  report_event("Gain Prothétique supprimé avec succès.",mtInformation,false);
	}

	main_frm->Consultation_OnChange_Event_Handler(GAIN_PROTHETIQUE_DB_SIGNATURE,0,t_record_state_change_type);

	main_frm->Navigate(7,gainp_entry->caller_page_index);

	return;
}

void __fastcall cancel_gainp(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.gainprots_engine.edit_mode)
	{
	  if (!ask_event("Annuler l'opération en cours ?")) return;
	}

	main_frm->Navigate(7,main_frm->session_params.engines.gainprots_engine.caller_page_index);

	return;
}

void __fastcall load_gainp_grph_type(TForm1 *main_frm)
{
  p_engine_entry gainp_entry;
  TGainprot_Def_Values *def_values;
  p_gainp_data data;


	gainp_entry = &main_frm->session_params.engines.gainprots_engine;

	if ((!gainp_entry->edit_mode) || (main_frm->GainpDefValCombo->ItemIndex < 0)) return;

	if (!ask_event("Voulez-vous charger le graphique type " + main_frm->GainpDefValCombo->Items[main_frm->GainpDefValCombo->ItemIndex].Text + " ? \n\r\n\r" +
	"Attention : les données de l'audiogramme en cours seront ecrasées par celles du graphique type !")) return;

	def_values = new TGainprot_Def_Values(gainp_entry->grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_gainp_data)def_values->GetData(main_frm->GainpDefValCombo->ItemIndex);

	  if (!data)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types [GetData] ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  if (!load_mesures(main_frm,&data->mesures,false)) return;

	  if (data->oreille == GAINP_OREILLE_CHAMPS_LIBRE)
	  {
		main_frm->GainpChlChk->State = cbChecked;
		main_frm->GainpOdChk->State = cbUnchecked;
		main_frm->GainpOgChk->State = cbUnchecked;
	  }
	  else
	  {
		if (CHECK_ATTRIBUTE(data->oreille,GAINP_OREILLE_DROITE))
		{
		  main_frm->GainpOdChk->State = cbChecked;
		}
		else main_frm->GainpOdChk->State = cbUnchecked;

		if (CHECK_ATTRIBUTE(data->oreille,GAINP_OREILLE_GAUCHE))
		{
		  main_frm->GainpOgChk->State = cbChecked;
		}
		else main_frm->GainpOgChk->State = cbUnchecked;

		main_frm->GainpChlChk->State = cbUnchecked;
	  }

	  if (data->nature == GAINP_NATURE_SON_PULSE)
	  {
		main_frm->PulseRadio->Checked = true;
	  }
	  else if (data->nature == GAINP_NATURE_SON_PURE)
	  {
		main_frm->PurRadio->Checked = true;
	  }
	  else if (data->nature == GAINP_NATURE_SON_BLANC)
	  {
		main_frm->BlancRadio->Checked = true;
	  }

	  if (data->prothese == GAINP_PROTHESE_TYPE_CONTOUR)
	  {
		main_frm->ContourRadio->Checked = true;
	  }
	  else if (data->prothese == GAINP_PROTHESE_TYPE_INTRA)
	  {
		main_frm->MesureRadio->Checked = true;
	  }
	  else if (data->prothese == GAINP_PROTHESE_TYPE_RIC)
	  {
		main_frm->RicRadio->Checked = true;
	  }

	  report_event(main_frm->GainpDefValCombo->Items[main_frm->GainpDefValCombo->ItemIndex].Text + " chargé avec succès.",mtInformation,false);

	}

  __finally
	{
	  delete def_values;
	}

    return;
}

void __fastcall add_gainp_grph_type(TForm1 *main_frm)
{
  TGainprot_Def_Values *def_values;
  p_gainp_data data;
  t_gainp_data current_data;
  UnicodeString str;


	if (!ask_event("Ajouter les mesures actuelles à la base de données des Graphiques Types ?")) return;

	if (main_frm->GainpDefValCombo->Items->Count >= 12)
	{
	  report_event("Impossible d'ajouter un autre graphique type ! La limite définie est de 12 graphiques.",mtWarning,false);
	  return;
	}

	avcore_memset(&current_data,0,sizeof(current_data));

	if (!save_mesures(main_frm,&current_data.mesures))
	{
	  report_event("Opération annulée ! l'audiogramme est vide, veuillez procéder à la saisie des mesures afin de profiter de cette fonctionalité.",mtWarning,false);
	  return;
	}

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

    if (main_frm->GainpChlChk->State == cbChecked)
	{
	  current_data.oreille = GAINP_OREILLE_CHAMPS_LIBRE;
	}
	else
	{
	  if (main_frm->GainpOdChk->State == cbChecked)
	  {
		SET_ATTRIBUTE(current_data.oreille,GAINP_OREILLE_DROITE);
	  }

	  if (main_frm->GainpOgChk->State == cbChecked)
	  {
		SET_ATTRIBUTE(current_data.oreille,GAINP_OREILLE_GAUCHE);
	  }
	}

	if (main_frm->PulseRadio->Checked == true)
	{
	  current_data.nature = GAINP_NATURE_SON_PULSE;
	}
	else if (main_frm->PurRadio->Checked == true)
	{
	  current_data.nature = GAINP_NATURE_SON_PURE;
	}
	else if (main_frm->BlancRadio->Checked == true)
	{
	  current_data.nature = GAINP_NATURE_SON_BLANC;
	}

	if (main_frm->ContourRadio->Checked == true)
	{
	  current_data.prothese = GAINP_PROTHESE_TYPE_CONTOUR;
	}
	else if (main_frm->MesureRadio->Checked == true)
	{
	  current_data.prothese = GAINP_PROTHESE_TYPE_INTRA;
	}
	else if (main_frm->RicRadio->Checked)
	{
	  current_data.prothese = GAINP_PROTHESE_TYPE_RIC;
	}

	def_values = new TGainprot_Def_Values(main_frm->session_params.engines.gainprots_engine.grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_gainp_data)def_values->GetFirstData();

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
		  else if (avcore_memcmp(&current_data.mesures,&data->mesures,sizeof(current_data) - sizeof(current_data.name)))
		  {
			str = "Opération annulée : votre base de données contient déjà un graphique type identique à celui que vous comptez ajouter ! \n\r\n\r";
			str = str + "graphique identique = " + (PWCHAR)&data->name;
			report_event(str,mtWarning,false);
			return;
		  }

		  data = (p_gainp_data)def_values->GetNextData();

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

	  main_frm->GainpDefValCombo->Items->Add(str);

      report_event("Graphique type ajouté avec succès",mtInformation,false);
	}

  __finally
	{
	  delete def_values;
	}

	return;
}

void __fastcall preview_gainp_grph(TForm1 *main_frm)
{
  p_engine_entry gainp_entry;
  p_consultation_record consult_record;
  p_gainp_record gainp_record;
  t_lilly_db_time_stamp_informations time_stamp_infos;
  bool empty;


	consult_record= (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if (!consult_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	gainp_entry = &main_frm->session_params.engines.gainprots_engine;

	gainp_record = (p_gainp_record)gainp_entry->current_record;

	if ((!gainp_record) || (gainp_entry->edit_mode))
	{
	  report_event("Vous devez commencer par valider cet Gain Prothétique afin de pouvoir voir et imprimer le graphique !",mtWarning,false);
	  return;
	}

	GainpPrevFrm = new TGainpPrevFrm(main_frm);

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

		 GainpPrevFrm->NomLbl->Caption = format_name((PWCHAR)&pat_record->nom_prenom);
		 GainpPrevFrm->CodepLbl->Caption = IntToStr((int)consult_record->patient_id);
		 GainpPrevFrm->adresse = format_name((PWCHAR)&pat_record->ville);
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

		 GainpPrevFrm->MedLbl->Caption = format_name((PWCHAR)&med_record->nom_prenom);
	   }

	   {
		 t_date_time today;

		 lilly_os_get_current_time_stamp(&today);

		 GainpPrevFrm->DateImpLbl->Caption = date_to_string(&today);
	   }

	   if (!lilly_db_get_record_time_stamp_infos(gainp_entry->db_handle,lilly_db_index_to_record_offset(gainp_entry->db_handle,gainp_record->code_gainp.unique_index),&time_stamp_infos))
	   {
		 UnicodeString str = "Une erreur est survenue au niveau de [GetTimeStamp] ! Le LillyDB a retourné l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(lilly_db_get_last_error(gainp_entry->db_handle));
		 report_event(str,mtError,true);
		 return;
	   }

	   GainpPrevFrm->GainpGrphDateLbl->Caption = "Gain Prothétique du : " + date_to_string(&time_stamp_infos.creation_stamp.time_stamp);

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

		 GainpPrevFrm->OpLbl->Caption = format_name((PWCHAR)&op_record->nom_prenom);
	   }

	   if (CHECK_ATTRIBUTE(gainp_record->oreille,GAINP_OREILLE_CHAMPS_LIBRE))
	   {
		 GainpPrevFrm->OreilleLbl->Caption = "Champ Libre";
	   }
	   else
	   {
		 GainpPrevFrm->OreilleLbl->Caption = "";

		 if (CHECK_ATTRIBUTE(gainp_record->oreille,GAINP_OREILLE_DROITE))
		 {
		   GainpPrevFrm->OreilleLbl->Caption = "Droite";
		 }

		 if (CHECK_ATTRIBUTE(gainp_record->oreille,GAINP_OREILLE_GAUCHE))
		 {
		   if (GainpPrevFrm->OreilleLbl->Caption != "")
		   {
			 GainpPrevFrm->OreilleLbl->Caption = GainpPrevFrm->OreilleLbl->Caption + " et ";
		   }

		   GainpPrevFrm->OreilleLbl->Caption = "Gauche";
		 }
       }

	   switch (gainp_record->nature)
	   {
		 case GAINP_NATURE_SON_PULSE : GainpPrevFrm->NatureLbl->Caption = "Sons PULSE";
									   break;

		  case GAINP_NATURE_SON_PURE : GainpPrevFrm->NatureLbl->Caption = "Sons PUR";
									   break;

		 case GAINP_NATURE_SON_BLANC : GainpPrevFrm->NatureLbl->Caption = "Bruit Blanc";
									   break;
	   }

	   switch (gainp_record->prothese)
	   {
		 case GAINP_PROTHESE_TYPE_CONTOUR : GainpPrevFrm->TypeProtLbl->Caption = "Contour";
											break;

		   case GAINP_PROTHESE_TYPE_INTRA : GainpPrevFrm->TypeProtLbl->Caption = "Intra";
											break;

			 case GAINP_PROTHESE_TYPE_RIC : GainpPrevFrm->TypeProtLbl->Caption = "RIC";
											break;

	   }

	   GainpPrevFrm->RefLbl->Caption = main_frm->GainpRefLbl->Caption;

	   {
		 int seuil_audition_count,seuil_prothetique_count,mcl_count;
		 float seuil_audition,seuil_prothetique,gain_prothetique,mcl,dynamique;

		 seuil_audition_count = seuil_prothetique_count = mcl_count = 0;
		 seuil_audition = seuil_prothetique = gain_prothetique = mcl = dynamique = 0;

		 for (int i = 0; i < sizeof(gainp_record->mesures.sa) / sizeof(gainp_record->mesures.sa[0]); i++)
		 {
		   if (gainp_record->mesures.sa[i])
		   {
			 seuil_audition_count = i + 1;
			 seuil_audition += gainp_record->mesures.sa[i];
		   }

		   if (gainp_record->mesures.sp[i])
		   {
			 seuil_prothetique_count = i + 1;
			 seuil_prothetique += gainp_record->mesures.sp[i];
		   }

		   if (gainp_record->mesures.mcl[i])
		   {
			 mcl_count = i + 1;
			 mcl += gainp_record->mesures.mcl[i];
		   }
		 }

		 seuil_audition /= seuil_audition_count;
		 seuil_prothetique /= seuil_prothetique_count;
		 mcl /= mcl_count;

		 gain_prothetique = seuil_audition - seuil_prothetique;
         dynamique = mcl - seuil_prothetique;

		 GainpPrevFrm->AuditionLbl->Caption = FloatToStrF(seuil_audition,ffGeneral,3,3);
		 GainpPrevFrm->SeuilProtLbl->Caption = FloatToStrF(seuil_prothetique,ffGeneral,3,3);
		 GainpPrevFrm->DynaLbl->Caption = FloatToStrF(dynamique,ffGeneral,3,3);
		 GainpPrevFrm->MclLbl->Caption = FloatToStrF(mcl,ffGeneral,3,3);
		 GainpPrevFrm->GainpLbl->Caption = FloatToStrF(gain_prothetique,ffGeneral,3,3);
	   }

	   GainpPrevFrm->Chart1->Title->Caption = "";

	   GainpPrevFrm->gainp_record = gainp_record;

	   GainpPrevFrm->ShowModal();
	}

  __finally
	{
	  delete GainpPrevFrm;
	}

    return;
}
