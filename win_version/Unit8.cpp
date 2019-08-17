//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit8.h"
#include "Unit1.h"
#include "Unit9.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TTympPrevFrm *TympPrevFrm;
//---------------------------------------------------------------------------
__fastcall TTympPrevFrm::TTympPrevFrm(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall TTympPrevFrm::ImpLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::ImpLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::PrintImgMouseEnter(TObject *Sender)
{
	ImpLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::PrintImgMouseLeave(TObject *Sender)
{
	ImpLbl->Font->Color = clWindowText;

    return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::PreviewImgMouseEnter(TObject *Sender)
{

	PreviewLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::PreviewImgMouseLeave(TObject *Sender)
{
	PreviewLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::CancelImgMouseEnter(TObject *Sender)
{
	CancelLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::CancelImgMouseLeave(TObject *Sender)
{
    CancelLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------


void __fastcall TTympPrevFrm::FormShow(TObject *Sender)
{
  float x;


	if (tympano1)
	{
	  x = -300;

	  for (int i = 0; i < sizeof(tympano1->oreille_droite.valeurs) / sizeof(tympano1->oreille_droite.valeurs[0]) ; i++)
	  {
		Chart1->Series[0]->AddXY(x,tympano1->oreille_droite.valeurs[i]);
		x += 50;
	  }

	  x = -300;

	  for (int i = 0; i < sizeof(tympano1->oreille_gauche.valeurs) / sizeof(tympano1->oreille_gauche.valeurs[0]) ; i++)
	  {
		Chart2->Series[0]->AddXY(x,tympano1->oreille_gauche.valeurs[i]);
		x += 50;
	  }
	}

	if (tympano2)
	{
	  x = -300;

	  for (int i = 0; i < sizeof(tympano2->oreille_droite.valeurs) / sizeof(tympano2->oreille_droite.valeurs[0]) ; i++)
	  {
		Chart1->Series[0]->AddXY(x,tympano2->oreille_droite.valeurs[i]);
		x += 50;
	  }

	  x = -300;

	  for (int i = 0; i < sizeof(tympano2->oreille_gauche.valeurs) / sizeof(tympano2->oreille_gauche.valeurs[0]) ; i++)
	  {
		Chart2->Series[0]->AddXY(x,tympano2->oreille_gauche.valeurs[i]);
		x += 50;
	  }
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::CancelImgClick(TObject *Sender)
{
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::PreviewImgClick(TObject *Sender)
{
  TympImpFrm = new TTympImpFrm(this);


	try
	  {
		 fill_quick_report(TympImpFrm);

		 TympImpFrm->QuickRep1->Preview();
	  }

	__finally
	  {
		delete TympImpFrm;
	  }

	return;

}
//---------------------------------------------------------------------------

void __fastcall TTympPrevFrm::PrintImgClick(TObject *Sender)
{
  TympImpFrm = new TTympImpFrm(this);


	try
	  {
		 fill_quick_report(TympImpFrm);

		 TympImpFrm->QuickRep1->Print();
	  }

	__finally
	  {
		delete TympImpFrm;
	  }

	return;
}

//---------------------------------------------------------------------------

#include "common.hpp"

void __fastcall TTympPrevFrm::fill_quick_report(const opaque_ptr qrfrm_ptr)
{
  TTympImpFrm *qrfrm = (TTympImpFrm *)qrfrm_ptr;


	qrfrm->DateLbl->Caption = DateImpLbl->Caption;

	qrfrm->NomLbl->Caption = NomLbl->Caption;
	qrfrm->CodepLbl->Caption = CodepLbl->Caption;
	qrfrm->AdressLbl->Caption = adresse;
	qrfrm->MedLbl->Caption = MedLbl->Caption;

	if (!OdShape1->Visible)
	{
	  qrfrm->OdShape1->Height = 0;
	  qrfrm->OdShape1->Width = 0;
    }

	qrfrm->OdDate1->Caption = OdTympDate1Lbl->Caption;

	if (!OdShape2->Visible)
	{
	  qrfrm->OdShape2->Height = 0;
	  qrfrm->OdShape2->Width = 0;
    }

	qrfrm->OdDate2->Caption = OdTympDate2Lbl->Caption;

	if (!OgShape1->Visible)
	{
	  qrfrm->OgShape1->Height = 0;
	  qrfrm->OgShape1->Width = 0;
	}

	qrfrm->OgDate1->Caption = OgTympDate1Lbl->Caption;

	if (!OgShape2->Visible)
	{
	  qrfrm->OgShape2->Height = 0;
	  qrfrm->OgShape2->Width = 0;
    }

	qrfrm->OgDate2->Caption = OgTympDate2Lbl->Caption;

	qrfrm->OdRsLbl1->Caption = this->OdRsEdit1->Text;
	qrfrm->OdRsLbl2->Caption = this->OdRsEdit2->Text;
	qrfrm->OdRsLbl3->Caption = this->OdRsEdit3->Text;
	qrfrm->OdRsLbl4->Caption = this->OdRsEdit4->Text;

	qrfrm->OgRsLbl1->Caption = this->OgRsEdit1->Text;
	qrfrm->OgRsLbl2->Caption = this->OgRsEdit2->Text;
	qrfrm->OgRsLbl3->Caption = this->OgRsEdit3->Text;
	qrfrm->OgRsLbl4->Caption = this->OgRsEdit4->Text;

	draw_chart_in_quickreport(Chart1,qrfrm->OdImg);
	draw_chart_in_quickreport(Chart2,qrfrm->OgImg);

	return;
}


