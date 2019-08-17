//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"

#include <doctors_engine.h>
#include <consultations_engine.h>
#include "Unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMedListFrm *MedListFrm;
//---------------------------------------------------------------------------
__fastcall TMedListFrm::TMedListFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMedListFrm::DelLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::DelLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TMedListFrm::DelImgMouseEnter(TObject *Sender)
{
	DelLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::DelImgMouseLeave(TObject *Sender)
{
	DelLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::EditImgMouseEnter(TObject *Sender)
{
	EditLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::EditImgMouseLeave(TObject *Sender)
{
	EditLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::AddImgMouseEnter(TObject *Sender)
{
	AddLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::AddImgMouseLeave(TObject *Sender)
{
	AddLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::ListView1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{

	if (Key == VK_RETURN)
	{
	  ListView1DblClick(Sender);
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::DelImgClick(TObject *Sender)
{
  uint64 offset;
  p_consultation_record iterator;
  p_medecin_record med_record;
  unsigned_int error_code;
  bool found = false;


	if (!ListView1->SelCount) return;

	if ((!med_entry) || (!consult_entry) || (!ask_event("Êtes-vous sûres de vouloir supprimer cette fiche médecin ?")))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	offset = (uint64)ListView1->Selected->Caption.ToInt();

	med_record = (p_medecin_record)lilly_db_read_record(med_entry->db_handle,MEDECIN_RECORD_SIZE,offset);

	if (!med_record)
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(med_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
	  report_event(str,mtError,true);
	  return;
	}

	iterator = (p_consultation_record)lilly_db_get_first_record(consult_entry->db_handle);

	if (!iterator)
	{
	  error_code = lilly_db_get_last_error(consult_entry->db_handle);

	  if (error_code != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau de [GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		report_event(str,mtError,true);
		return;
	  }
	}
	else
	{
	  while (true)
	  {
		if (iterator->medecin_id == med_record->code_medecin.unique_index)
		{
		  found = true;
		  break;
		}

		iterator = (p_consultation_record)lilly_db_get_next_record(consult_entry->db_handle);

		if (!iterator) break;
	  }

	  error_code = lilly_db_get_last_error(consult_entry->db_handle);

	  if (error_code != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		report_event(str,mtError,true);
		return;
      }
	}

	if (found)
	{
	  UnicodeString str = "Cette fiche médecin que vous essayez de supprimer est déjà associée à une ou plusieurs autres consultations ! \n\r\n\r";
	  str = str + "La suppression n'est donc pas possible dans ce cas puisqu'il ya d'autres fiches de consultations qui dépendent de celle-ci.";
	  report_event(str,mtWarning,false);
	  return;
	}

	if (!med_entry->engine->delete_record(med_entry->engine,med_entry->db_handle,offset))
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [DeleteRecord] ! Le moteur médecins a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(med_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
	  report_event(str,mtError,true);
	}
	else
	{
	  ListView1->Selected->Delete();

	  report_event("Ficher médecin supprimée avec succès",mtInformation,false);
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::EditImgClick(TObject *Sender)
{
  uint64 offset;
  p_medecin_record med_record;
  unsigned_int error_code;
  TMedInfoFrm *med_infos_frm;


	if (!ListView1->SelCount) return;

	if ((!med_entry) || (!consult_entry) || (!pays_path) || (!gouv_path))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	offset = (uint64)ListView1->Selected->Caption.ToInt();

	med_record = (p_medecin_record)lilly_db_read_record(med_entry->db_handle,MEDECIN_RECORD_SIZE,offset);

	if (!med_record)
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(med_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
	  report_event(str,mtError,true);
	  return;
	}

	med_infos_frm = new TMedInfoFrm(this);

  try
	{
	  t_medecin_record record;
	  uint32 crc;

	  med_infos_frm->edit_mode = true;

	  med_infos_frm->Caption = "  Modifier informations médecin :";

	  med_infos_frm->PaysCombo->Items->LoadFromFile((PWCHAR)&pays_path->path_data);

	  med_infos_frm->GouvCombo->Items->LoadFromFile((PWCHAR)&gouv_path->path_data);

	  med_infos_frm->NomEdit->Text = (PWCHAR)&med_record->nom_prenom;

	  med_infos_frm->PaysCombo->ItemIndex = med_record->pays;

	  med_infos_frm->GouvCombo->ItemIndex = med_record->gouvernorat;

	  switch (med_record->type)
	  {
		case MEDECIN_PRIVE_TYPE : med_infos_frm->PriveRadio->Checked = true;
								  break;

			  case HOPITAL_TYPE : med_infos_frm->HopitalRadio->Checked = true;
								  break;

			 case CLINIQUE_TYPE : med_infos_frm->CliniqueRadio->Checked = true;
								  break;

						default : report_event(error_code_to_string(API_ERROR),mtError,true);
								  return;
	  }

	  med_infos_frm->Tel1Edit->Text = (PWCHAR)&med_record->phone_principal;
	  med_infos_frm->Tel2Edit->Text = (PWCHAR)&med_record->phone_secondaire;
	  med_infos_frm->FaxEdit->Text = (PWCHAR)&med_record->fax;
	  med_infos_frm->MailEdit->Text = (PWCHAR)&med_record->email;

	  if (med_infos_frm->ShowModal() != mrOk) return;

	  avcore_memset(&record,0,sizeof(record));

	  record.code_medecin.unique_index = med_record->code_medecin.unique_index;

	  avcore_memcpy(&record.nom_prenom,(puchar)med_infos_frm->NomEdit->Text.c_str(),med_infos_frm->NomEdit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_principal,(puchar)med_infos_frm->Tel1Edit->Text.c_str(),med_infos_frm->Tel1Edit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_secondaire,(puchar)med_infos_frm->Tel2Edit->Text.c_str(),med_infos_frm->Tel2Edit->Text.Length() * 2);
	  avcore_memcpy(&record.fax,(puchar)med_infos_frm->FaxEdit->Text.c_str(),med_infos_frm->FaxEdit->Text.Length() * 2);
	  avcore_memcpy(&record.email,(puchar)med_infos_frm->MailEdit->Text.c_str(),med_infos_frm->MailEdit->Text.Length() * 2);

	  record.pays = (uint8)med_infos_frm->PaysCombo->ItemIndex;
	  record.gouvernorat = (uint8)med_infos_frm->GouvCombo->ItemIndex;

	  if (med_infos_frm->PriveRadio->Checked == true)
	  {
		record.type = MEDECIN_PRIVE_TYPE;
	  }
	  else if (med_infos_frm->HopitalRadio->Checked == true)
	  {
		record.type = HOPITAL_TYPE;
	  }
	  else
	  {
		record.type = CLINIQUE_TYPE;
	  }

	  crc = med_entry->engine->get_record_crc(med_entry->engine,med_entry->db_handle,&record);

	  if (!crc)
	  {
		UnicodeString str = "Une erreur est survenue au niveau de [GetRecordCrc] ! Le moteur médecins a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(med_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		report_event(str,mtError,true);
		return;
	  }

	  if (crc == med_record->code_medecin.crc32) return;

	  if (!med_entry->engine->edit_record(med_entry->engine,med_entry->db_handle,&record,offset))
	  {
		UnicodeString str;

		if (med_entry->engine->error_code == LILLY_DB_DUPLICATE_RECORD_ERROR)
		{
		  str = "Après vos modifications apportées à cette fiche, le logiciel a détecté que celle-ci est maintenant identique à une autre fiche médecin déjà inscrite \n\r";
		  str = str + "dans votre base de données ! \n\r\n\r";
		  str = "Modifications annulées !";
          report_event(str,mtWarning,false);
		}
		else
		{
		  str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur médecins a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(med_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		  report_event(str,mtError,true);
		}
	  }
	  else
	  {
		TListItem *item = ListView1->Selected;

		item->Caption = med_infos_frm->NomEdit->Text;

		switch (record.type)
		{
		  case MEDECIN_PRIVE_TYPE : item->SubItems->Strings[0] = "Non";
									item->SubItems->Strings[1] = "Non";
									item->SubItems->Strings[2] = "Oui";
									break;

				case HOPITAL_TYPE : item->SubItems->Strings[0] = "Oui";
									item->SubItems->Strings[1] = "Non";
									item->SubItems->Strings[2] = "Non";
									break;

			   case CLINIQUE_TYPE : item->SubItems->Strings[0] = "Non";
									item->SubItems->Strings[1] ="Oui";
									item->SubItems->Strings[2] = "Non";
									break;
		}

		report_event("Fiche médecin modifiée avec succès",mtInformation,false);
	  }

	}

  __finally
	{
	  delete med_infos_frm;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedListFrm::AddImgClick(TObject *Sender)
{
  uint64 offset;
  unsigned_int error_code;
  TMedInfoFrm *med_infos_frm;


	if ((!med_entry) || (!consult_entry) || (!pays_path) || (!gouv_path))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	med_infos_frm = new TMedInfoFrm(this);

  try
	{
	  t_medecin_record record;
	  uint32 crc;

	  med_infos_frm->edit_mode = true;

	  med_infos_frm->Caption = "  Ajouter nouveau médecin :";

	  med_infos_frm->PaysCombo->Items->LoadFromFile((PWCHAR)&pays_path->path_data);

	  med_infos_frm->GouvCombo->Items->LoadFromFile((PWCHAR)&gouv_path->path_data);

	  med_infos_frm->PaysCombo->ItemIndex = 184;

	  med_infos_frm->GouvCombo->ItemIndex = 22;

	  med_infos_frm->edit_mode = true;

	  if (med_infos_frm->ShowModal() != mrOk) return;

	  avcore_memset(&record,0,sizeof(record));

	  avcore_memcpy(&record.nom_prenom,(puchar)med_infos_frm->NomEdit->Text.c_str(),med_infos_frm->NomEdit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_principal,(puchar)med_infos_frm->Tel1Edit->Text.c_str(),med_infos_frm->Tel1Edit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_secondaire,(puchar)med_infos_frm->Tel2Edit->Text.c_str(),med_infos_frm->Tel2Edit->Text.Length() * 2);
	  avcore_memcpy(&record.fax,(puchar)med_infos_frm->FaxEdit->Text.c_str(),med_infos_frm->FaxEdit->Text.Length() * 2);
	  avcore_memcpy(&record.email,(puchar)med_infos_frm->MailEdit->Text.c_str(),med_infos_frm->MailEdit->Text.Length() * 2);

	  record.pays = (uint8)med_infos_frm->PaysCombo->ItemIndex;

	  record.gouvernorat = (uint8)med_infos_frm->GouvCombo->ItemIndex;

	  if (med_infos_frm->PriveRadio->Checked == true)
	  {
		record.type = MEDECIN_PRIVE_TYPE;
	  }
	  else if (med_infos_frm->HopitalRadio->Checked == true)
	  {
		record.type = HOPITAL_TYPE;
	  }
	  else
	  {
		record.type = CLINIQUE_TYPE;
	  }

	  if (!med_entry->engine->append_record(med_entry->engine,med_entry->db_handle,&record))
	  {
		UnicodeString str;

		if (med_entry->engine->error_code == LILLY_DB_DUPLICATE_RECORD_ERROR)
		{
		  str = "Le logiciel a détecté que votre base contient déjà une fiche médecin identique à celle que vous essayez d'ajouter ! \n\r\n\r";
		  str = "Opération annulée !";
          report_event(str,mtWarning,false);
		}
		else
		{
		 str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur médecins a retourné l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(med_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";;
		 report_event(str,mtError,true);
		}
	  }
	  else
	  {
		TListItem *item = ListView1->Items->Add();

		item->Caption = med_infos_frm->NomEdit->Text;

		switch (record.type)
		{
		  case MEDECIN_PRIVE_TYPE : item->SubItems->Add("Non");
									item->SubItems->Add("Non");
									item->SubItems->Add("Oui");
									break;

				case HOPITAL_TYPE : item->SubItems->Add("Oui");
									item->SubItems->Add("Non");
									item->SubItems->Add("Non");
									break;

			   case CLINIQUE_TYPE : item->SubItems->Add("Non");
									item->SubItems->Add("Oui");
									item->SubItems->Add("Non");
									break;
		}

		report_event("Fiche médecin ajoutée avec succès",mtInformation,false);
	  }

	}

  __finally
	{
	  delete med_infos_frm;
	}

	return;
}

void __fastcall TMedListFrm::ListView1DblClick(TObject *Sender)
{
  uint64 offset;
  p_medecin_record med_record;
  unsigned_int error_code;
  TMedInfoFrm *med_infos_frm;


	if (!ListView1->SelCount) return;

	if ((!med_entry) || (!consult_entry) || (!pays_path) || (!gouv_path))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	offset = (uint64)ListView1->Selected->Caption.ToInt();

	med_record = (p_medecin_record)lilly_db_read_record(med_entry->db_handle,MEDECIN_RECORD_SIZE,offset);

	if (!med_record)
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(med_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";;
	  report_event(str,mtError,true);
	  return;
	}

	med_infos_frm = new TMedInfoFrm(this);

  try
	{
	  med_infos_frm->Caption = "  Informations médecin :";

	  med_infos_frm->PaysCombo->Items->LoadFromFile((PWCHAR)&pays_path->path_data);

	  med_infos_frm->GouvCombo->Items->LoadFromFile((PWCHAR)&gouv_path->path_data);

	  med_infos_frm->NomEdit->Text = (PWCHAR)&med_record->nom_prenom;

	  med_infos_frm->PaysCombo->ItemIndex = med_record->pays;

	  med_infos_frm->GouvCombo->ItemIndex = med_record->gouvernorat;

	  switch (med_record->type)
	  {
		case MEDECIN_PRIVE_TYPE : med_infos_frm->PriveRadio->Checked = true;
								  break;

			  case HOPITAL_TYPE : med_infos_frm->HopitalRadio->Checked = true;
								  break;

			 case CLINIQUE_TYPE : med_infos_frm->CliniqueRadio->Checked = true;
								  break;

						default : report_event(error_code_to_string(API_ERROR),mtError,true);
								  return;
	  }

	  med_infos_frm->Tel1Edit->Text = (PWCHAR)&med_record->phone_principal;
	  med_infos_frm->Tel2Edit->Text = (PWCHAR)&med_record->phone_secondaire;
	  med_infos_frm->FaxEdit->Text = (PWCHAR)&med_record->fax;
	  med_infos_frm->MailEdit->Text = (PWCHAR)&med_record->email;

	  med_infos_frm->ShowModal();

	}

  __finally
	{
	  delete med_infos_frm;
	}

	return;
}
//---------------------------------------------------------------------------

