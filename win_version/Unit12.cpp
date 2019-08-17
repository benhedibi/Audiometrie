//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit12.h"
#include "Unit13.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAvocPrevFrm *AvocPrevFrm;
//---------------------------------------------------------------------------
__fastcall TAvocPrevFrm::TAvocPrevFrm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TAvocPrevFrm::CancelLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::CancelLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}

void __fastcall TAvocPrevFrm::CancelImgMouseEnter(TObject *Sender)
{
	CancelLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::CancelImgMouseLeave(TObject *Sender)
{
	CancelLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::PreviewImgMouseEnter(TObject *Sender)
{
    PreviewLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::PreviewImgMouseLeave(TObject *Sender)
{
	PreviewLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::PrintImgMouseEnter(TObject *Sender)
{
	ImpLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::PrintImgMouseLeave(TObject *Sender)
{
	ImpLbl->Font->Color = clWindowText;

	return;
}

//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::CancelImgClick(TObject *Sender)
{

	ModalResult = mbCancel;

	return;
}

//---------------------------------------------------------------------------
void __fastcall TAvocPrevFrm::FormShow(TObject *Sender)
{
  static const double courbe_temoin_values[21] = {0,0.5,2,4.5,8,12.5,18,24.5,32,40.5,50,59.5,68,75.5,82,87.5,92,95.5,98,99.5,100};

  int i,x;


	for (i = 0; i < 21; i++)
	{
	  Chart1->Series[0]->AddXY(i,courbe_temoin_values[i]);
	}

	for (i = 0; i < 111; i++) // tracer la barre mediane à 50 db
	{
	  Chart1->Series[1]->AddXY(i,50);
    }

	x = 10;

	for (i = 0; i < 10; i++)
	{
	  Chart1->Series[2]->AddXY(x,avoc_record->appareil_off.valeurs[i]);
	  x += 10;
	}

	x = 10;

	for (i = 0; i < 10; i++)
	{
	  Chart1->Series[3]->AddXY(x,avoc_record->appareil_on.valeurs[i]);
      x += 10;
	}

	return;
}

void __fastcall TAvocPrevFrm::PreviewImgClick(TObject *Sender)
{
  AvocImpFrm = new TAvocImpFrm(this);


	try
	  {
		 fill_quick_report(AvocImpFrm);

		 AvocImpFrm->QuickRep1->Preview();
	  }

	__finally
	  {
		delete AvocImpFrm;
	  }

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAvocPrevFrm::PrintImgClick(TObject *Sender)
{
  AvocImpFrm = new TAvocImpFrm(this);


	try
	  {
		 fill_quick_report(AvocImpFrm);

		 AvocImpFrm->QuickRep1->Print();
	  }

	__finally
	  {
		delete AvocImpFrm;
	  }

	return;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include "common.hpp"

void __fastcall TAvocPrevFrm::fill_quick_report(const opaque_ptr qrfrm_ptr)
{
  TAvocImpFrm *qrfrm = (TAvocImpFrm *)qrfrm_ptr;


	qrfrm->DateLbl->Caption = DateImpLbl->Caption;

	qrfrm->NomLbl->Caption = NomLbl->Caption;
	qrfrm->CodepLbl->Caption = CodepLbl->Caption;
	qrfrm->AdressLbl->Caption = adresse;
	qrfrm->MedLbl->Caption = MedLbl->Caption;

	qrfrm->DateAvoc->Caption = "du " + audiovoc_date;

	qrfrm->OreilleLbl->Caption = OreilleLbl->Caption;
	qrfrm->NatureLbl->Caption = NatureLbl->Caption;
	qrfrm->ControlLbl->Caption = ControlLbl->Caption;

	qrfrm->MisaLbl->Caption = MisaPanel->Caption;
	qrfrm->MiaaLbl->Caption = MiaaPanel->Caption;
	qrfrm->SisaLbl->Caption = SisaPanel->Caption;
	qrfrm->SiaaLbl->Caption = SiaaPanel->Caption;
	qrfrm->TdsaLbl->Caption = TdsaPanel->Caption;
	qrfrm->TdaaLbl->Caption = TdaaPanel->Caption;

	draw_chart_in_quickreport(Chart1,qrfrm->GainpImg);

	return;
}


