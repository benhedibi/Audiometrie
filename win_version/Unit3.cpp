//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"

#include "common.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMedInfoFrm *MedInfoFrm;
//---------------------------------------------------------------------------
__fastcall TMedInfoFrm::TMedInfoFrm(TComponent* Owner) : TForm(Owner)
{
	edit_mode = false;

	return;
}

//---------------------------------------------------------------------------
void __fastcall TMedInfoFrm::Label4MouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clBlue;

	return;
}

//---------------------------------------------------------------------------

void __fastcall TMedInfoFrm::Label4MouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}

//---------------------------------------------------------------------------

void __fastcall TMedInfoFrm::Label4Click(TObject *Sender)
{

	if ((edit_mode) && (!ask_event("Êtes-vous sûres de vouloir annuler ?"))) return;

	ModalResult = mrCancel;

    return;
}
//---------------------------------------------------------------------------

void __fastcall TMedInfoFrm::Label3Click(TObject *Sender)
{

	if (!edit_mode)
	{
	  ModalResult = mrOk;
	  return;
	}

	if (NomEdit->Text.Length() == 0)
	{
	  report_event("Vous devez spécifier le nom du médecin ou de l'organisme !",mtWarning,false);
	  return;
	}

	if (PaysCombo->ItemIndex == -1)
	{
	  report_event("Vous devez spécifier un pays !",mtWarning,false);
	  return;
	}

    if (MailEdit->Text != "")
	{
	  int len = MailEdit->Text.Length();
	  int pos_at = MailEdit->Text.Pos("@");

	  if ((len < 6) || (pos_at < 2) || ((MailEdit->Text[len - 2] != '.') && (MailEdit->Text[len - 3] != '.'))
	  || ((MailEdit->Text[len - 2] == '.') && (pos_at >= len - 3)) || ((MailEdit->Text[len - 3] == '.') && (pos_at >= len - 4)))
	  {
		report_event("L'adresse e-mail que vous avez spécifié est invalide !",mtWarning,false);
		return;
	  }
	}

    ModalResult = mrOk;

}
//---------------------------------------------------------------------------

void __fastcall TMedInfoFrm::PaysComboSelect(TObject *Sender)
{

	if (PaysCombo->ItemIndex != 184)
	{
	  GouvCombo->ItemIndex = -1;
	  GouvCombo->Enabled = false;
	}
	else
	{
	  GouvCombo->Enabled = true;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TMedInfoFrm::FormShow(TObject *Sender)
{

	ActiveControl = GroupBox1;

	NomEdit->ReadOnly = (edit_mode == false);

	PaysCombo->Enabled = edit_mode;
	GouvCombo->Enabled = edit_mode;

	PriveRadio->Enabled = edit_mode;
	HopitalRadio->Enabled = edit_mode;
	CliniqueRadio->Enabled = edit_mode;

	Tel1Edit->ReadOnly = (edit_mode == false);
	Tel2Edit->ReadOnly = (edit_mode == false);
	FaxEdit->ReadOnly = (edit_mode == false);
	MailEdit->ReadOnly = (edit_mode == false);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TMedInfoFrm::MailEditKeyPress(TObject *Sender, System::WideChar &Key)
{

     switch (Key)
	 {
	   case ' ' : Key = 0;
				  break;

	   case '@' :
	   case '.' : break;

		default : Key |= 0x0020;
				  break;

	 }

	 return;
}
//---------------------------------------------------------------------------

