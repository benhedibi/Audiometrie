//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit10.h"
#include "Unit11.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGainpPrevFrm *GainpPrevFrm;
//---------------------------------------------------------------------------
__fastcall TGainpPrevFrm::TGainpPrevFrm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TGainpPrevFrm::CancelImgClick(TObject *Sender)
{

	ModalResult = mbCancel;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::CancelLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::CancelLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::CancelImgMouseEnter(TObject *Sender)
{
	CancelLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::CancelImgMouseLeave(TObject *Sender)
{

	CancelLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::PreviewImgMouseEnter(TObject *Sender)
{
	PreviewLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::PreviewImgMouseLeave(TObject *Sender)
{
	PreviewLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::PrintImgMouseEnter(TObject *Sender)
{
	ImpLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::PrintImgMouseLeave(TObject *Sender)
{

	ImpLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::FormShow(TObject *Sender)
{
  TArrowSeries *serie = NULL;
  int val;


	for (int i = 0; i < 13; i++)
	{
	  val = gainp_record->mesures.sa[i];

	  if (val)
	  {
		Chart1->Series[0]->AddXY(i + 1,val);

		if (val >= 120)
		{
		  serie = (TArrowSeries *)Chart1->Series[3];
		  val = i + 1;
		  serie->AddArrow(val,120,val,125);
          Chart1->Axes->Left->Maximum = 130;
		  break;
		}
	  }
	}

	for (int i = 0; i < 13; i++)
	{
	  val = gainp_record->mesures.sp[i];

	  if (val)
	  {
		Chart1->Series[1]->AddXY(i + 1,val);

		if (val >= 120)
		{
		  serie = (TArrowSeries *)Chart1->Series[4];
		  val = i + 1;
		  serie->AddArrow(val,120,val,125);
		  Chart1->Axes->Left->Maximum = 130;
		  break;
		}
	  }
	}

    for (int i = 0; i < 13; i++)
	{
	  val = gainp_record->mesures.mcl[i];

	  if (val)
	  {
		Chart1->Series[2]->AddXY(i + 1,val);

		if (val >= 120)
		{
		  serie = (TArrowSeries *)Chart1->Series[5];
		  val = i + 1;
		  serie->AddArrow(val,120,val,125);
          Chart1->Axes->Left->Maximum = 130;
		  break;
		}
	  }
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::PreviewImgClick(TObject *Sender)
{
  GainpImpFrm = new TGainpImpFrm(this);


	try
	  {
		 fill_quick_report(GainpImpFrm);

		 GainpImpFrm->QuickRep1->Preview();
	  }

	__finally
	  {
		delete GainpImpFrm;
	  }

	return;
}

//---------------------------------------------------------------------------

void __fastcall TGainpPrevFrm::PrintImgClick(TObject *Sender)
{
  GainpImpFrm = new TGainpImpFrm(this);


	try
	  {
		 fill_quick_report(GainpImpFrm);

		 GainpImpFrm->QuickRep1->Print();
	  }

	__finally
	  {
		delete GainpImpFrm;
	  }

	return;
}

//---------------------------------------------------------------------------

#include "common.hpp"

void __fastcall TGainpPrevFrm::fill_quick_report(const opaque_ptr qrfrm_ptr)
{
  TGainpImpFrm *qrfrm = (TGainpImpFrm *)qrfrm_ptr;


	qrfrm->DateLbl->Caption = DateImpLbl->Caption;

	qrfrm->NomLbl->Caption = NomLbl->Caption;
	qrfrm->CodepLbl->Caption = CodepLbl->Caption;
	qrfrm->AdressLbl->Caption = adresse;
	qrfrm->MedLbl->Caption = MedLbl->Caption;

	qrfrm->OreilleLbl->Caption = OreilleLbl->Caption;
	qrfrm->NatureLbl->Caption = NatureLbl->Caption;
	qrfrm->ProtLbl->Caption = TypeProtLbl->Caption;
	qrfrm->RefLbl->Caption = RefLbl->Caption;

	qrfrm->SeuilAuditionLbl->Caption = AuditionLbl->Caption;
	qrfrm->SeuilProtLbl->Caption = SeuilProtLbl->Caption;
	qrfrm->DynLbl->Caption = DynaLbl->Caption;
	qrfrm->MclLbl->Caption = MclLbl->Caption;
	qrfrm->GpLbl->Caption = GainpLbl->Caption;

	draw_chart_in_quickreport(Chart1,qrfrm->GainpImg);

	return;
}

