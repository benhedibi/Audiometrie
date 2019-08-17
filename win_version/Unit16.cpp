//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit16.h"

#include "common.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoginFrm *LoginFrm;
//---------------------------------------------------------------------------
__fastcall TLoginFrm::TLoginFrm(TComponent* Owner) : TForm(Owner)
{
	operator_id = -1;
}
//---------------------------------------------------------------------------
void __fastcall TLoginFrm::CancelLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------
void __fastcall TLoginFrm::CancelLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}

//---------------------------------------------------------------------------

void __fastcall TLoginFrm::CancelLblClick(TObject *Sender)
{

	ModalResult = mrCancel;

    return;
}
//---------------------------------------------------------------------------

void __fastcall TLoginFrm::ConnectLblClick(TObject *Sender)
{

	if (PassEdit->Text == "12345678")
	{
	  report_event("Mot de passe d'acc�s est vide ! Veuillez sp�cifier un mot de passe valide.",mtWarning,false);
	  return;
	}

	ModalResult = mrOk;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TLoginFrm::Label6Click(TObject *Sender)
{
	report_event("Fonctionalit� indisponible pour le moment !",mtWarning,false);

    return;
}
//---------------------------------------------------------------------------

