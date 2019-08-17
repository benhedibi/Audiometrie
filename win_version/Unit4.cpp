//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "Unit5.h"

#include <operators_engine.h>
#include <consultations_engine.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpListFrm *OpListFrm;

//---------------------------------------------------------------------------
__fastcall TOpListFrm::TOpListFrm(TComponent* Owner) : TForm(Owner)
{
	srch = "";

    current_item_index = 0;
}

//---------------------------------------------------------------------------

void __fastcall TOpListFrm::AddLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::AddLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::DelImgMouseEnter(TObject *Sender)
{

	DelLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::DelImgMouseLeave(TObject *Sender)
{
	DelLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::EditImgMouseEnter(TObject *Sender)
{
	EditLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::EditImgMouseLeave(TObject *Sender)
{
	EditLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::AddImgMouseEnter(TObject *Sender)
{
	AddLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::AddImgMouseLeave(TObject *Sender)
{
    AddLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::AddImgClick(TObject *Sender)
{
  uint64 offset;
  unsigned_int error_code;
  TOpInfoFrm *op_infos_frm;


	if ((!op_entry) || (!consult_entry))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	op_infos_frm = new TOpInfoFrm(this);

  try
	{
	  t_operateur_record record;
	  uint32 crc;

	  op_infos_frm->Caption = "  Ajouter un nouvel op�rateur :";

	  op_infos_frm->edit_mode = true;

	  if (op_infos_frm->ShowModal() != mrOk) return;

	  avcore_memset(&record,0,sizeof(record));

	  avcore_memcpy(&record.nom_prenom,(puchar)op_infos_frm->NomEdit->Text.c_str(),op_infos_frm->NomEdit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_principal,(puchar)op_infos_frm->Tel1Edit->Text.c_str(),op_infos_frm->Tel1Edit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_secondaire,(puchar)op_infos_frm->Tel2Edit->Text.c_str(),op_infos_frm->Tel2Edit->Text.Length() * 2);
	  avcore_memcpy(&record.email,(puchar)op_infos_frm->MailEdit->Text.c_str(),op_infos_frm->MailEdit->Text.Length() * 2);

	  if (!op_entry->engine->append_record(op_entry->engine,op_entry->db_handle,&record))
	  {
		UnicodeString str;

		if (op_entry->engine->error_code == LILLY_DB_DUPLICATE_RECORD_ERROR)
		{
		  str = "Le logiciel a d�tect� que votre base contient d�j� une fiche op�rateur identique � celle que vous essayez d'ajouter ! \n\r\n\r";
		  str = "Op�ration annul�e !";
          report_event(str,mtWarning,false);
		}
		else
		{
		 str = "Une erreur est survenue au niveau de [AppendRecord] ! Le moteur op�rateurs a retourn� l'erreur suivante : \n\r\n\r";
		 str = str + error_code_to_string(op_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";;
		 report_event(str,mtError,true);
		}
	  }
	  else
	  {
		p_operateur_record op_record;
        UnicodeString str;
		TListItem *item = ListView1->Items->Add();

		item->Caption = op_infos_frm->NomEdit->Text;

		item->SubItems->Add(op_infos_frm->Tel1Edit->Text);

		item->SubItems->Add("Non");

		op_record = (p_operateur_record)lilly_db_read_record(op_entry->db_handle,OPERATEUR_RECORD_SIZE,lilly_db_get_current_record_offset(op_entry->db_handle));

		if (!op_record)
		{
		  str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(op_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		  report_event(str,mtError,true);
		  return;
		}
		else
		{
		  str = "Fiche op�rateur ajout�e avec succ�s \n\r\n\r";
		  str = str + "Veuillez prendre note du nouveau mot de passe d'acc�s : " + IntToHex((int)op_record->code_operateur.crc32);
		  report_event(str,mtInformation,false);
		}
	  }

	}

  __finally
	{
	  delete op_infos_frm;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::EditImgClick(TObject *Sender)
{
  uint64 offset;
  p_operateur_record op_record;
  unsigned_int error_code;
  TOpInfoFrm *op_infos_frm;


	if (!ListView1->SelCount) return;

	if ((!op_entry) || (!consult_entry))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	offset = (uint64)ListView1->Selected->Caption.ToInt();

	op_record = (p_operateur_record)lilly_db_read_record(op_entry->db_handle,OPERATEUR_RECORD_SIZE,offset);

	if (!op_record)
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(op_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
	  report_event(str,mtError,true);
	  return;
	}

	op_infos_frm = new TOpInfoFrm(this);

  try
	{
	  t_operateur_record record;
	  uint32 crc;

	  op_infos_frm->Caption = "  Modifier informations op�rateur :";

	  op_infos_frm->edit_mode = true;

      op_infos_frm->PswLbl->Font->Color = clBlue;

	  op_infos_frm->NomEdit->Text = format_name((PWCHAR)&op_record->nom_prenom);
	  op_infos_frm->PswLbl->Caption = IntToHex((int)op_record->code_operateur.crc32);
	  op_infos_frm->Tel1Edit->Text = (PWCHAR)&op_record->phone_principal;
	  op_infos_frm->Tel2Edit->Text = (PWCHAR)&op_record->phone_secondaire;
	  op_infos_frm->MailEdit->Text = (PWCHAR)&op_record->email;

	  if (op_infos_frm->ShowModal() != mrOk) return;

	  avcore_memset(&record,0,sizeof(record));

	  op_infos_frm->NomEdit->Text.UpperCase();

	  avcore_memcpy(&record.nom_prenom,(puchar)op_infos_frm->NomEdit->Text.c_str(),op_infos_frm->NomEdit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_principal,(puchar)op_infos_frm->Tel1Edit->Text.c_str(),op_infos_frm->Tel1Edit->Text.Length() * 2);
	  avcore_memcpy(&record.phone_secondaire,(puchar)op_infos_frm->Tel2Edit->Text.c_str(),op_infos_frm->Tel2Edit->Text.Length() * 2);
	  avcore_memcpy(&record.email,(puchar)op_infos_frm->MailEdit->Text.c_str(),op_infos_frm->MailEdit->Text.Length() * 2);

	  crc = op_entry->engine->get_record_crc(op_entry->engine,op_entry->db_handle,&record);

	  if (!crc)
	  {
		UnicodeString str = "Une erreur est survenue au niveau de [GetRecordCrc] ! Le moteur op�rateurs a retourn� l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(op_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		report_event(str,mtError,true);
		return;
	  }

	  if (crc == op_record->code_operateur.crc32) return;

	  if (!op_entry->engine->edit_record(op_entry->engine,op_entry->db_handle,&record,offset))
	  {
		UnicodeString str;

		if (op_entry->engine->error_code == LILLY_DB_DUPLICATE_RECORD_ERROR)
		{
		  str = "Apr�s vos modifications apport�es � cette fiche, le logiciel a d�tect� que celle-ci est maintenant identique � une autre fiche op�rateur d�j� inscrite \n\r";
		  str = str + "dans votre base de donn�es ! \n\r\n\r";
		  str = "Modifications annul�es !";
          report_event(str,mtWarning,false);
		}
		else
		{
		  str = "Une erreur est survenue au niveau de [EditRecord] ! Le moteur op�rateurs a retourn� l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(op_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		  report_event(str,mtError,true);
		}
	  }
	  else
	  {
		UnicodeString str;
		TListItem *item = ListView1->Selected;

		item->Caption = op_infos_frm->NomEdit->Text;
		item->SubItems->Add(op_infos_frm->Tel1Edit->Text);
		item->SubItems->Add("Non");

		op_record = (p_operateur_record)lilly_db_read_record(op_entry->db_handle,OPERATEUR_RECORD_SIZE,offset);

		if (!op_record)
		{
		  str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(op_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		  report_event(str,mtError,true);
		  return;
		}
		else
		{
		  str = "Fiche op�rateur modifi�e avec succ�s \n\r\n\r";
		  str = str + "Veuillez prendre note du nouveau mot de passe d'acc�s : " + IntToHex((int)op_record->code_operateur.crc32);
		  report_event(str,mtInformation,false);
		}
	  }

	}

  __finally
	{
	  delete op_infos_frm;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::DelImgClick(TObject *Sender)
{
  uint64 offset;
  p_consultation_record iterator;
  p_operateur_record op_record;
  unsigned_int error_code;
  bool found = false;


	if (!ListView1->SelCount) return;

	if ((!op_entry) || (!consult_entry) || (!ask_event("�tes-vous s�res de vouloir supprimer cette fiche op�rateur ?")))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	offset = (uint64)ListView1->Selected->Caption.ToInt();

	op_record = (p_operateur_record)lilly_db_read_record(op_entry->db_handle,OPERATEUR_RECORD_SIZE,offset);

	if (!op_record)
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(op_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
	  report_event(str,mtError,true);
	  return;
	}

	iterator = (p_consultation_record)lilly_db_get_first_record(consult_entry->db_handle);

	if (!iterator)
	{
	  error_code = lilly_db_get_last_error(consult_entry->db_handle);

	  if (error_code != ERROR_SUCCESS)
	  {
		UnicodeString str = "Une erreur est survenue au niveau de [GetFirstRecord] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		report_event(str,mtError,true);
		return;
	  }
	}
	else
	{
	  uint64 offset_consult;
	  t_lilly_db_time_stamp_informations time_stamp_infos;

	  while (true)
	  {
		offset_consult = lilly_db_get_current_record_offset(op_entry->db_handle);

		if (!lilly_db_get_record_time_stamp_infos(consult_entry->db_handle,offset_consult,&time_stamp_infos))
		{
		  UnicodeString str = "Une erreur est survenue au niveau de [GetTimeStampInfos] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(consult_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		  report_event(str,mtError,true);
		  return;
		}

		if (time_stamp_infos.creation_stamp.operator_id == op_record->code_operateur.unique_index)
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
		UnicodeString str = "Une erreur est survenue au niveau de [GetNextRecord] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
		report_event(str,mtError,true);
		return;
      }
	}

	if (found)
	{
	  UnicodeString str = "Cette fiche op�rateur que vous essayez de supprimer est d�j� associ�e � une ou plusieurs autres consultations ! \n\r\n\r";
	  str = str + "La suppression n'est donc pas possible dans ce cas, puisqu'il ya d'autres fiches de consultations qui d�pendent de celle-ci.";
	  report_event(str,mtWarning,false);
	  return;
	}

	if (!op_entry->engine->delete_record(op_entry->engine,op_entry->db_handle,offset))
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [DeleteRecord] ! Le moteur op�rateurs a retourn� l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(op_entry->engine->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
	  report_event(str,mtError,true);
	}
	else
	{
	  ListView1->Selected->Delete();

	  report_event("Ficher op�rateur supprim�e avec succ�s",mtInformation,false);
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::ListView1DblClick(TObject *Sender)
{
  uint64 offset;
  p_operateur_record op_record;
  unsigned_int error_code;
  TOpInfoFrm *op_infos_frm;


	if (!ListView1->SelCount) return;

	if ((!op_entry) || (!consult_entry))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	offset = (uint64)ListView1->Selected->Caption.ToInt();

	op_record = (p_operateur_record)lilly_db_read_record(op_entry->db_handle,OPERATEUR_RECORD_SIZE,offset);

	if (!op_record)
	{
	  UnicodeString str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourn� l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(op_entry->db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
	  report_event(str,mtError,true);
	  return;
	}

	op_infos_frm = new TOpInfoFrm(this);

  try
	{
	  t_operateur_record record;
	  uint32 crc;

	  op_infos_frm->Caption = "  Modifier informations op�rateur :";

	  op_infos_frm->edit_mode = false;

	  op_infos_frm->PswLbl->Font->Color = clBlue;

	  op_infos_frm->NomEdit->Text = (PWCHAR)&op_record->nom_prenom;
	  op_infos_frm->PswLbl->Caption = IntToHex((int)op_record->code_operateur.crc32);
	  op_infos_frm->Tel1Edit->Text = (PWCHAR)&op_record->phone_principal;
	  op_infos_frm->Tel2Edit->Text = (PWCHAR)&op_record->phone_secondaire;
	  op_infos_frm->MailEdit->Text = (PWCHAR)&op_record->email;

	  op_infos_frm->ShowModal();

	}

  __finally
	{
	  delete op_infos_frm;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::ListView1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{

	if (Key == VK_RETURN)
	{
	  ListView1DblClick(Sender);
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::Rechercher1Click(TObject *Sender)
{

	if (!ListView1->Items->Count)
	{
	  UnicodeString msg = "Base de donn�es des op�rateurs est encore vide ! \n\r\n\r";
	  msg = msg + "Op�ration annul�e";
	  report_event(msg,mtWarning,false);
	  return;
	}

	if (!InputQuery("Rechercher op�rateur(s) :","Sp�cifier le nom ou une partie du nom de l'op�rateur(s) :",srch))
	{
	  srch = "";
	  return;
	}

	srch = srch.UpperCase();

	ListView1->ItemIndex = 0;

	for (int i = 0; i < ListView1->Items->Count; i++)
	{
	  if (ListView1->Items->Item[i]->SubItems->Strings[0].Pos(srch) > 0)
	  {
		current_item_index = i;
		ListView1->ItemIndex = i;
		PopupMenu1->Items->Items[1]->Enabled = true;
		return;
	  }
	}

	ListView1->ItemIndex = 0;

	srch = "";

	report_event("Aucune correspondance trouv�e avec les param�tres de recherche que vous avez sp�cifi� !",mtInformation,false);

    return;

}
//---------------------------------------------------------------------------

void __fastcall TOpListFrm::Suivant1Click(TObject *Sender)
{

	if ((srch == "") || (!ListView1->Items->Count) || (current_item_index == ListView1->Items->Count - 1))
	{
	  PopupMenu1->Items->Items[1]->Enabled = false;
      return;
    }

	for (int i = current_item_index + 1; i < ListView1->Items->Count; i++)
	{
	  if (ListView1->Items->Item[i]->SubItems->Strings[0].Pos(srch) > 0)
	  {
		current_item_index = i;
		ListView1->ItemIndex = i;
		return;
	  }
	}

	PopupMenu1->Items->Items[1]->Enabled = false;

    ListView1->ItemIndex = 0;

	current_item_index = 0;

	srch = "";

	report_event("Aucune autre correspondance trouv�e !",mtInformation,false);

	return;

}
//---------------------------------------------------------------------------

