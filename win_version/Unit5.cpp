//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"

#include "common.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpInfoFrm *OpInfoFrm;
//---------------------------------------------------------------------------
__fastcall TOpInfoFrm::TOpInfoFrm(TComponent* Owner): TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TOpInfoFrm::BiomLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::BiomLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::BiomImgMouseEnter(TObject *Sender)
{
	BiomLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::BiomImgMouseLeave(TObject *Sender)
{
    BiomLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::CancelLblClick(TObject *Sender)
{

    if ((edit_mode) && (!ask_event("Êtes-vous sûres de vouloir annuler ?"))) return;

	ModalResult = mrCancel;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::ValidLblClick(TObject *Sender)
{

	if (!edit_mode)
	{
	  ModalResult = mrOk;
	  return;
	}

	if (NomEdit->Text.Length() == 0)
	{
	  report_event("Vous devez spécifier le nom de l'opérateur !",mtWarning,false);
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

	return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::BiomImgClick(TObject *Sender)
{
	report_event(error_code_to_string(ERROR_NOT_IMPLEMENTED),mtWarning,false);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::FormShow(TObject *Sender)
{

	ActiveControl = GroupBox1;

	NomEdit->ReadOnly = (edit_mode == false);

	Tel1Edit->ReadOnly = (edit_mode == false);
	Tel2Edit->ReadOnly = (edit_mode == false);

	MailEdit->ReadOnly = (edit_mode == false);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TOpInfoFrm::MailEditKeyPress(TObject *Sender, System::WideChar &Key)
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

