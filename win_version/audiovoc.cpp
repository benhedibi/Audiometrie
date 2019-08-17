#pragma hdrstop

#include "audiovoc.hpp"

#include <operators_engine.h>
#include <patients_engine.h>
#include <consultations_engine.h>
#include <audiovocs_engine.h>

#include <lilly_utils.h>
#include <lilly_os.h>

#include <db_signatures.h>

#include "unit12.h"

#include <math.hpp>


static const PWCHAR NAMES[2] = {(PWCHAR)L"SaapEdit",(PWCHAR)L"AvapEdit"};


static bool __fastcall load_mesures(TForm1 *main_frm,const p_audiovoc_record record,const bool read_only)
{
  TEdit *edit;


	for (int i = 10; i > 0; i--)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(NAMES[0] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if (!record)
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)record->appareil_off.valeurs[i - 1]);

		if (edit->Text.ToInt() == 100)
		{
		  edit->Color = TColor(0x8080FF);
		}
	  }

	  edit->ReadOnly = read_only;

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(NAMES[1] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if (!record)
	  {
		edit->Text = "0";
	  }
	  else
	  {
		edit->Text = IntToStr((int)record->appareil_on.valeurs[i - 1]);

		if (edit->Text.ToInt() == 100)
		{
		  edit->Color = TColor(0x8080FF);
		}
	  }

	  edit->ReadOnly = read_only;
	}

	return true;
}

static bool __fastcall save_mesures(TForm1 *main_frm,const p_audiovoc_record record)
{
  TEdit *edit;
  int hits_count = 0;


	if (!record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	for (int i = 10; i > 0; i--)
	{
	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(NAMES[0] + IntToStr(i)));

	  if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

	  if (edit->Text.ToInt() > 0)
	  {
		hits_count++;
	  }

	  record->appareil_off.valeurs[i - 1] = (uint8)edit->Text.ToInt();

	  edit = dynamic_cast<TEdit *>(main_frm->FindComponent(NAMES[1] + IntToStr(i)));

      if (!edit)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return false;
	  }

      if (edit->Text.ToInt() > 0)
	  {
		hits_count++;
	  }

      record->appareil_on.valeurs[i - 1] = (uint8)edit->Text.ToInt();
	}

	return (hits_count > 0);
}

bool __fastcall load_audiovoc(TForm1 *main_frm)
{
  p_engine_entry avoc_entry;
  p_audiovoc_record avoc_record;
  p_patient_record pat_record;


	avoc_entry = &main_frm->session_params.engines.audiovocs_engine;

	avoc_record = (p_audiovoc_record)avoc_entry->current_record;

	pat_record = (p_patient_record)main_frm->session_params.engines.patients_engine.current_record;

	if ((!pat_record) || ((!avoc_record) && (!avoc_entry->edit_mode)))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return false;
	}

	if (!load_old_data_to_listview(&main_frm->session_params,AUDIOMETRIE_VOCALE_DB_SIGNATURE,pat_record->code_patient.unique_index,main_frm->AvocListView)) return false;

	if (!load_mesures(main_frm,avoc_record,(avoc_entry->edit_mode == false))) return false;

    main_frm->AvocDefValCombo->ItemIndex = -1;

	main_frm->Switch_Annuler_Retour_Button(AUDIOMETRIE_VOCALE_DB_SIGNATURE,avoc_entry->edit_mode);

	if (!avoc_record)
	{
	  main_frm->AvocDefValCombo->Enabled = true;

	  main_frm->AvocObsMemo->ReadOnly = false;

	  main_frm->AvocOdChk->Checked = false;
	  main_frm->AvocOgChk->Checked = false;
	  main_frm->AvocChlChk->Checked = false;

	  main_frm->AvocAallRadio->Checked = true;
	  main_frm->AvocMonoChk->Checked = true;

	  return true;
	}

	main_frm->AvocOdChk->Checked = CHECK_ATTRIBUTE(avoc_record->oreille,AUDIOVOC_OREILLE_DROITE);
	main_frm->AvocOgChk->Checked = CHECK_ATTRIBUTE(avoc_record->oreille,AUDIOVOC_OREILLE_GAUCHE);
	main_frm->AvocChlChk->Checked = (avoc_record->oreille == AUDIOVOC_OREILLE_CHAMP_LIBRE);

	if (avoc_record->nature == AUDIOVOC_NATURE_AVEC_LL)
	{
	  main_frm->AvocAallRadio->Checked = true;
	}
	else main_frm->AvocSallRadio->Checked = true;

	if (avoc_record->controle == AUDIOVOC_CONTROLE_MONOSYLLABIQUE)
	{
	 main_frm->AvocMonoChk->Checked = true;
	}
	else main_frm->AvocDissRadio->Checked = true;

	load_blob(avoc_entry,main_frm->AvocObsMemo,avoc_record->code_audiovoc.unique_index,t_lilly_db_observations_confidentielles_blob_type);

	if (main_frm->AvocObsMemo->Lines->Count > 0)
	{
	  avoc_entry->observation_crc32 = lilly_crc32_buffer((puchar)main_frm->AvocObsMemo->Text.c_str(),main_frm->AvocObsMemo->Text.Length() * 2,0);
	}

	if (!avoc_entry->edit_mode)
	{
	  return true;
	}
    else return load_grph_list(avoc_entry,AUDIOMETRIE_VOCALE_DB_SIGNATURE,main_frm->AvocDefValCombo);
}

void __fastcall unload_audiovoc(TForm1 *main_frm)
{
	main_frm->AvocObsMemo->Lines->Clear();
	main_frm->AvocDefValCombo->Items->Clear();
	main_frm->AvocListView->Items->Clear();

	main_frm->session_params.engines.audiovocs_engine.current_record = NULL;
	main_frm->session_params.engines.audiovocs_engine.observation_crc32 = 0;
	main_frm->session_params.engines.audiovocs_engine.edit_mode = false;

	return;
}

void __fastcall validate_audiovoc(TForm1 *main_frm)
{
  p_engine_entry audiovoc_entry;
  p_lilly_db_engine db_engine;
  p_consultation_record consult_record;
  p_audiovoc_record audiovoc_record,rec_ptr;
  uint64 offset;
  t_audiovoc_record record;


	audiovoc_entry = &main_frm->session_params.engines.audiovocs_engine;

	if (!audiovoc_entry->edit_mode)
	{
	  audiovoc_entry->current_record = NULL;
      main_frm->Navigate(6,audiovoc_entry->caller_page_index);
	  return;
	}

	db_engine = audiovoc_entry->engine;

    consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if ((!consult_record) || (!db_engine))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	audiovoc_record = (p_audiovoc_record)audiovoc_entry->current_record;

	if (!audiovoc_record)
	{
	  rec_ptr = &record;
	}
	else rec_ptr = audiovoc_record;

	if (!save_mesures(main_frm,rec_ptr)) return;

	if (main_frm->AvocChlChk->State == cbChecked)
	{
	  rec_ptr->oreille = AUDIOVOC_OREILLE_CHAMP_LIBRE;
	}
	else
	{
	  if (main_frm->AvocOdChk->State == cbChecked)
	  {
		SET_ATTRIBUTE(rec_ptr->oreille,AUDIOVOC_OREILLE_DROITE);
	  }

	  if (main_frm->AvocOgChk->State == cbChecked)
	  {
		SET_ATTRIBUTE(rec_ptr->oreille,AUDIOVOC_OREILLE_GAUCHE);
      }
	}

	if (main_frm->AvocAallRadio->Checked)
	{
	  rec_ptr->nature = AUDIOVOC_NATURE_AVEC_LL;
	}
	else rec_ptr->nature = AUDIOVOC_NATURE_SANS_LL;

	if (main_frm->AvocMonoChk->Checked)
	{
	  rec_ptr->controle = AUDIOVOC_CONTROLE_MONOSYLLABIQUE;
	}
	else rec_ptr->controle = AUDIOVOC_CONTROLE_DISSYLLABIQUE;

	if (!audiovoc_record)
	{
	  if (consult_record->audiovoc_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
        return;
	  }

	  if (!db_engine->append_record(db_engine,audiovoc_entry->db_handle,rec_ptr))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur Audiométries vocales a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(audiovoc_entry->db_handle);

	  audiovoc_record = (p_audiovoc_record)lilly_db_read_record(audiovoc_entry->db_handle,sizeof(record),offset);

	  if (!audiovoc_record)
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(audiovoc_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  main_frm->Consultation_OnChange_Event_Handler(AUDIOMETRIE_VOCALE_DB_SIGNATURE,audiovoc_record->code_audiovoc.unique_index,t_record_state_change_type);

	  report_event("Audiométrie vocale ajoutée avec succès.",mtInformation,false);
	}
	else
	{
      if (!consult_record->audiovoc_id)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
        return;
	  }

	  offset = lilly_db_get_current_record_offset(audiovoc_entry->db_handle);

	  if (!db_engine->edit_record(db_engine,audiovoc_entry->db_handle,rec_ptr,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur Audiométries vocales a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(db_engine->error_code);
		report_event(err_str,mtError,true);
		return;
	  }

	  report_event("Audiométrie vocale modifiée avec succès.",mtInformation,false);
	}

	if ((audiovoc_entry->observation_crc32) && (main_frm->AvocObsMemo->Text == ""))
	{
	  delete_blob(audiovoc_entry,consult_record->audiovoc_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((!audiovoc_entry->observation_crc32) && (main_frm->AvocObsMemo->Text != ""))
	{
	  add_blob(audiovoc_entry,main_frm->AvocObsMemo,consult_record->audiovoc_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}
	else if ((audiovoc_entry->observation_crc32) && (main_frm->AvocObsMemo->Text != ""))
	{
	  update_blob(audiovoc_entry,main_frm->AvocObsMemo,consult_record->audiovoc_id,main_frm->session_params.current_operator_id,t_lilly_db_observations_confidentielles_blob_type);
	}

	audiovoc_entry->current_record = NULL;
	audiovoc_entry->edit_mode = false;

	main_frm->Switch_Annuler_Retour_Button(AUDIOMETRIE_VOCALE_DB_SIGNATURE,false);

	//main_frm->Navigate(6,audiovoc_entry->caller_page_index);

	return;
}

void __fastcall edit_audiovoc(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.audiovocs_engine.edit_mode) return;

	if (!ask_event("Modifier cette Audiométrie vocale ?")) return;

	main_frm->session_params.engines.audiovocs_engine.edit_mode = true;

	if (!load_mesures(main_frm,NULL,false)) return;

	main_frm->AvocObsMemo->ReadOnly = false;
	main_frm->AvocDefValCombo->Enabled = true;

    main_frm->Switch_Annuler_Retour_Button(AUDIOMETRIE_VOCALE_DB_SIGNATURE,true);

	return;
}

void __fastcall delete_audiovoc(TForm1 *main_frm)
{
  p_engine_entry audiovoc_entry;
  p_audiovoc_record audiovoc_record;
  uint64 offset;


	audiovoc_entry = &main_frm->session_params.engines.audiovocs_engine;

	audiovoc_record = (p_audiovoc_record)audiovoc_entry->current_record;

	if (!ask_event("Êtes-vous sûres de vouloir supprimer cette Audiométrie vocale ?")) return;

	if (audiovoc_record)
	{
	  p_consultation_record consult_record = (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	  if ((!consult_record) || (consult_record->audiovoc_id != audiovoc_record->code_audiovoc.unique_index))
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  offset = lilly_db_get_current_record_offset(audiovoc_entry->db_handle);

	  if (!lilly_db_delete_record(audiovoc_entry->db_handle,offset))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [DeleteRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(audiovoc_entry->db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  consult_record->audiovoc_id = 0;

	  audiovoc_entry->current_record = NULL;
	  audiovoc_entry->edit_mode = false;

	  main_frm->session_params.engines.consultations_engine.edit_mode = true;

	  report_event("Audiométrie vocale supprimée avec succès.",mtInformation,false);
	}

	main_frm->Consultation_OnChange_Event_Handler(AUDIOMETRIE_VOCALE_DB_SIGNATURE,0,t_record_state_change_type);

	main_frm->Navigate(6,audiovoc_entry->caller_page_index);

	return;
}

void __fastcall cancel_audiovoc(TForm1 *main_frm)
{

	if (main_frm->session_params.engines.audiovocs_engine.edit_mode)
	{
	  if (!ask_event("Annuler l'opération en cours ?")) return;

	  main_frm->session_params.engines.audiovocs_engine.current_record = NULL;

	  main_frm->session_params.engines.audiovocs_engine.edit_mode = false;
	}

	main_frm->Navigate(6,main_frm->session_params.engines.audiovocs_engine.caller_page_index);

	return;
}

void __fastcall load_audiovoc_grph_type(TForm1 *main_frm)
{
  p_engine_entry audiovoc_entry;
  TAudiovoc_Def_Values *def_values;
  p_audiovoc_data data;
  t_audiovoc_record tmp;


	audiovoc_entry = &main_frm->session_params.engines.audiovocs_engine;

	if ((!audiovoc_entry->edit_mode) || (main_frm->AvocDefValCombo->ItemIndex < 0)) return;

	if (!ask_event("Voulez-vous charger le graphique type " + main_frm->AvocDefValCombo->Items[main_frm->AvocDefValCombo->ItemIndex].Text + " ? \n\r\n\r" +
	"Attention : les données de l'audiométrie vocale en cours seront ecrasées par celles du graphique type !")) return;

	def_values = new TAudiovoc_Def_Values(audiovoc_entry->grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_audiovoc_data)def_values->GetData(main_frm->AvocDefValCombo->ItemIndex);

	  if (!data)
	  {
		UnicodeString str = "Une erreur est survenue au niveau du moteur des Graphiques Types [GetData] ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  avcore_memset(&tmp,0,sizeof(tmp));

	  avcore_memcpy(&tmp.appareil_off,&data->appareil_off,sizeof(*data) - sizeof(data->name));

	  if (!load_mesures(main_frm,&tmp,false)) return;

	  main_frm->AvocOdChk->Checked = CHECK_ATTRIBUTE(tmp.oreille,AUDIOVOC_OREILLE_DROITE);
	  main_frm->AvocOgChk->Checked = CHECK_ATTRIBUTE(tmp.oreille,AUDIOVOC_OREILLE_GAUCHE);
	  main_frm->AvocChlChk->Checked = tmp.oreille == AUDIOVOC_OREILLE_CHAMP_LIBRE;

	  if CHECK_ATTRIBUTE(tmp.nature,AUDIOVOC_NATURE_AVEC_LL)
	  {
		main_frm->AvocAallRadio->Checked = true;
	  }
	  else main_frm->AvocSallRadio->Checked = true;

	  if CHECK_ATTRIBUTE(tmp.controle,AUDIOVOC_CONTROLE_MONOSYLLABIQUE)
	  {
	   main_frm->AvocMonoChk->Checked = true;
	  }
	  else main_frm->AvocDissRadio->Checked = true;

	  report_event(main_frm->AvocDefValCombo->Items[main_frm->AvocDefValCombo->ItemIndex].Text + " chargé avec succès.",mtInformation,false);

	}

  __finally
	{
	  delete def_values;
	}
	return;
}

void __fastcall add_audiovoc_grph_type(TForm1 *main_frm)
{
  TAudiovoc_Def_Values *def_values;
  p_audiovoc_data data;
  t_audiovoc_data current_data;
  t_audiovoc_record record;
  UnicodeString str;


	if (!ask_event("Ajouter les valeurs actuelles à la base de données des Graphiques Types ?")) return;

	if (main_frm->TympanoDefValCombo->Items->Count >= 12)
	{
	  report_event("Impossible d'ajouter un autre graphique type ! La limite définie est de 12 graphiques.",mtWarning,false);
	  return;
	}

	avcore_memset(&record,0,sizeof(record));

	if (!save_mesures(main_frm,&record)) return;

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

	avcore_memset(&current_data,0,sizeof(current_data));

	avcore_memcpy(&current_data.name,(puchar)str.c_str(),str.Length() * 2);

	def_values = new TAudiovoc_Def_Values(main_frm->session_params.engines.audiovocs_engine.grph_types_db_path,12);

  try
	{
	  if (def_values->GetLastError() != ERROR_SUCCESS)
	  {
		str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  data = (p_audiovoc_data)def_values->GetFirstData();

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
		  else if (avcore_memcmp(&record.appareil_off,&data->appareil_off,sizeof(*data) - sizeof(data->name)))
		  {
			str = "Opération annulée : votre base de données contient déjà un graphique type identique à celui que vous comptez ajouter ! \n\r\n\r";
			str = str + "graphique identique = " + (PWCHAR)&data->name;
			report_event(str,mtWarning,false);
			return;
		  }

		  data = (p_audiovoc_data)def_values->GetNextData();

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

	  avcore_memcpy(&current_data.appareil_off,&record.appareil_off,sizeof(current_data) - sizeof(current_data.name));

	  if (!def_values->Add(&current_data))
	  {
        str = "Une erreur est survenue au niveau du moteur des Graphiques Types ! le moteur a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(def_values->GetLastError());
		report_event(str,mtError,false);
		return;
	  }

	  main_frm->AvocDefValCombo->Items->Add(str);

	  report_event("Graphique type ajouté avec succès",mtInformation,false);

	}

  __finally
	{
	  delete def_values;
	}

	return;
}


typedef struct {
				 double max_intel;
				 double max_intel_db;
				 double seuil_intel;
				 double taux_discrimination;
				 double discrimination_db;
			   } t_audiovoc_results,*p_audiovoc_results;


static void __fastcall get_audiovoc_results(const p_audiovoc values,const p_audiovoc_results results)
{
  double a,b,rech_x,rech_y;
  int db1,db2,y1,y2;
  uint8 max_y,max_y_db;


	db1 = db2 = y1 = y2 = 0;
	max_y = max_y_db = 0;

	{
	  int index,val;
	  bool process = true;

	  index = 0;

	  while (true)
	  {
		val = values->valeurs[index];

		if ((process) && (val < 50))
		{
		  db1 = index + 1;
		  y1 = val;
		}
		else process = false;

		if (val > max_y)
		{
		  max_y = val;
		  max_y_db = index + 1;
		}

		if (index + 1 > 10) break;

		index++;
	  }

	  if ((db1 < 10) || (values->valeurs[db1] == 50))
	  {
		db2 = (db1 + 1) * 10;
		y2 = values->valeurs[db1];
	  }

      if (db1)
	  {
		db1 *= 10;
	  }

	  if (max_y_db)
	  {
		max_y_db *= 10;
	  }
	}

	rech_x = 0;

	if ((db1 > 0) && (db2 > 0))
	{
	  if ((db1 == db2) || (y1 == y2))
	  {
		rech_x = db1;
	  }
	  else
	  {
		a = ((double)y2 - (double)y1) / ((double)db2 - (double)db1);
		b = (double)y2 - (a * (double)db2);
		rech_x = (50 - b) / a;
	  }
	}

	if (rech_x > 0)
	{
	  double pt_y = rech_x + 35;
	  int index;

	  db2 = y2 = 0;

	  db1 = (int)(floor(pt_y)) / 10;

	  index = db1;

	  y1 = values->valeurs[index - 1];

	  db1 *= 10;

	  if (index != 10)
	  {
		db2 = db1 + 10;
		y2 = values->valeurs[index];
	  }

	  rech_y = 0;

	  if ((db1) && (db2))
	  {
		if ((db1 == db2) || (y1 == y2))
		{
		  rech_y = y1;
		}
		else
		{
		  a = ((double)y2 - (double)y1) / ((double)db2 - (double)db1);
		  b = (double)y2 - (a * (double)db2);
		  rech_y = a * pt_y + b;
		}
	  }

	  if (rech_y > 0)
	  {
		results->taux_discrimination = RoundTo((Extended)rech_y,-1);
	  }

	  results->discrimination_db = RoundTo((Extended)(rech_x + 25),-1);
	  results->seuil_intel = RoundTo(Extended(rech_x - 10),-1);
	}

	if (max_y > 0)
	{
	  if (values->valeurs[0] == max_y)
	  {
		max_y_db = 10;
      }
    }

	results->max_intel = max_y;

	if (values->valeurs[0] == max_y)
	{
	  results->max_intel_db = 10;
	}
	else
	{
	  int index = 0;

	  while (true)
	  {
		if (values->valeurs[index] == max_y) break;
		index++;
	  }

	  results->max_intel_db = (index + 1) * 10;
	}

    return;
}

void __fastcall preview_audiovoc_grph(TForm1 *main_frm)
{
  p_engine_entry avoc_entry;
  p_consultation_record consult_record;
  p_audiovoc_record avoc_record;
  t_lilly_db_time_stamp_informations time_stamp_infos;
  t_audiovoc_results audiovoc_results;
  bool empty;


	consult_record= (p_consultation_record)main_frm->session_params.engines.consultations_engine.current_record;

	if (!consult_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	avoc_entry = &main_frm->session_params.engines.audiovocs_engine;

	avoc_record = (p_audiovoc_record)avoc_entry->current_record;

	if ((!avoc_record) || (avoc_entry->edit_mode))
	{
	  report_event("Vous devez commencer par valider cette Audiométrie vocale afin de pouvoir prévisualiser et imprimer le graphique !",mtWarning,false);
	  return;
	}

	AvocPrevFrm = new TAvocPrevFrm(main_frm);

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

		 AvocPrevFrm->NomLbl->Caption = format_name((PWCHAR)&pat_record->nom_prenom);
		 AvocPrevFrm->CodepLbl->Caption = IntToStr((int)consult_record->patient_id);
		 AvocPrevFrm->adresse = format_name((PWCHAR)&pat_record->ville);
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

		 AvocPrevFrm->MedLbl->Caption = format_name((PWCHAR)&med_record->nom_prenom);
	   }

	   {
		 t_date_time today;

		 lilly_os_get_current_time_stamp(&today);

		 AvocPrevFrm->DateImpLbl->Caption = date_to_string(&today);
	   }

	   if (!lilly_db_get_record_time_stamp_infos(avoc_entry->db_handle,lilly_db_index_to_record_offset(avoc_entry->db_handle,avoc_record->code_audiovoc.unique_index),&time_stamp_infos))
	   {
		 UnicodeString str = "Une erreur est survenue au niveau de [GetTimeStamp] ! Le LillyDB a retourné l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(lilly_db_get_last_error(avoc_entry->db_handle));
		 report_event(str,mtError,true);
		 return;
	   }

	   AvocPrevFrm->audiovoc_date = date_to_string(&time_stamp_infos.creation_stamp.time_stamp);
	   AvocPrevFrm->AvocDateLbl->Caption = "Audiométrie vocale du : " + AvocPrevFrm->audiovoc_date;

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

		 AvocPrevFrm->OpLbl->Caption = format_name((PWCHAR)&op_record->nom_prenom);
	   }

	   if (CHECK_ATTRIBUTE(avoc_record->oreille,AUDIOVOC_OREILLE_CHAMP_LIBRE))
	   {
		 AvocPrevFrm->OreilleLbl->Caption = "Champ Libre";
	   }
	   else
	   {
		 AvocPrevFrm->OreilleLbl->Caption = "";

		 if (CHECK_ATTRIBUTE(avoc_record->oreille,AUDIOVOC_OREILLE_DROITE))
		 {
		   AvocPrevFrm->OreilleLbl->Caption = "Droite";
		 }

		 if (CHECK_ATTRIBUTE(avoc_record->oreille,AUDIOVOC_OREILLE_GAUCHE))
		 {
		   if (AvocPrevFrm->OreilleLbl->Caption != "")
		   {
			 AvocPrevFrm->OreilleLbl->Caption = AvocPrevFrm->OreilleLbl->Caption + " et ";
		   }

		   AvocPrevFrm->OreilleLbl->Caption = "Gauche";
		 }
       }

	   if (avoc_record->nature == AUDIOVOC_NATURE_AVEC_LL)
	   {
		 AvocPrevFrm->NatureLbl->Caption = "Avec LL";
	   }
	   else AvocPrevFrm->NatureLbl->Caption = "Sans LL";

	   if (avoc_record->controle == AUDIOVOC_CONTROLE_MONOSYLLABIQUE)
	   {
		 AvocPrevFrm->ControlLbl->Caption = "Monosyllabique";
	   }
	   else AvocPrevFrm->ControlLbl->Caption = "Dissyllabique";

	   avcore_memset(&audiovoc_results,0,sizeof(audiovoc_results));

	   get_audiovoc_results(&avoc_record->appareil_off,&audiovoc_results);

	   if (audiovoc_results.max_intel > 0)
	   {
		 AvocPrevFrm->MisaPanel->Caption = FloatToStrF(audiovoc_results.max_intel,ffGeneral,6,1) + "% à " + IntToStr((int)audiovoc_results.max_intel_db) + "db";
	   }

	   AvocPrevFrm->SisaPanel->Caption = FloatToStrF(audiovoc_results.seuil_intel,ffGeneral,6,1);

	   if (audiovoc_results.taux_discrimination)
	   {
		 AvocPrevFrm->TdsaPanel->Caption = FloatToStrF(audiovoc_results.taux_discrimination,ffGeneral,6,1) + "% à " + FloatToStrF(audiovoc_results.discrimination_db,ffGeneral,6,1) + "db";
	   }

	   avcore_memset(&audiovoc_results,0,sizeof(audiovoc_results));

	   get_audiovoc_results(&avoc_record->appareil_on,&audiovoc_results);

       if (audiovoc_results.max_intel > 0)
	   {
		 AvocPrevFrm->MiaaPanel->Caption = FloatToStrF(audiovoc_results.max_intel,ffGeneral,2,1) + "% à " + IntToStr((int)audiovoc_results.max_intel_db) + "db";
	   }

	   AvocPrevFrm->SiaaPanel->Caption = FloatToStrF(audiovoc_results.seuil_intel,ffGeneral,2,1);

       if (audiovoc_results.taux_discrimination)
	   {
		 AvocPrevFrm->TdaaPanel->Caption = FloatToStrF(audiovoc_results.taux_discrimination,ffGeneral,2,1) + "% à " + FloatToStrF(audiovoc_results.discrimination_db,ffGeneral,2,1) + "db";
	   }

	   AvocPrevFrm->Chart1->Title->Caption = "";

	   AvocPrevFrm->avoc_record = avoc_record;

	   AvocPrevFrm->ShowModal();
	}

  __finally
	{
	  delete AvocPrevFrm;
	}

    return;
}


