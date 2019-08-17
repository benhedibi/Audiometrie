//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit14.h"
#include "Unit15.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAudiogPrevFrm *AudiogPrevFrm;
//---------------------------------------------------------------------------
__fastcall TAudiogPrevFrm::TAudiogPrevFrm(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TAudiogPrevFrm::CancelLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::CancelLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::CancelImgMouseEnter(TObject *Sender)
{
	CancelLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::CancelImgMouseLeave(TObject *Sender)
{
	CancelLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::PreviewImgMouseEnter(TObject *Sender)
{
	PreviewLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::PreviewImgMouseLeave(TObject *Sender)
{
	PreviewLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::PrintImgMouseEnter(TObject *Sender)
{
	ImpLbl->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::PrintImgMouseLeave(TObject *Sender)
{
    ImpLbl->Font->Color = clWindowText;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::CancelImgClick(TObject *Sender)
{
	ModalResult = mrCancel;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::PreviewImgClick(TObject *Sender)
{
  TAudiogImpFrm *qr_frm = new TAudiogImpFrm(this);


	try
	  {
		 fill_quick_report(qr_frm);

		 qr_frm->QuickRep1->Preview();
	  }

	__finally
	  {
		delete qr_frm;
	  }

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::PrintImgClick(TObject *Sender)
{
  TAudiogImpFrm *qr_frm = new TAudiogImpFrm(this);


	try
	  {
		 fill_quick_report(qr_frm);

		 qr_frm->QuickRep1->Print();
	  }

	__finally
	  {
		delete qr_frm;
	  }

	return;
}
//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::draw_chart(TChart *chart,const p_audiogram_oreille oreille,const p_audiogram_oreille ancien_va_oreille)
{
  TArrowSeries *serie = NULL;
  int val;


	for (int i = 0; i < 13; i++)
	{
	  val = oreille->va[i];

	  if (val)
	  {
		chart->Series[0]->AddXY(i + 1,val);

		if (val >= 120)
		{
		  serie = (TArrowSeries *)chart->Series[3];
		  val = i + 1;
		  serie->AddArrow(val,120,val,125);
          chart->Axes->Left->Maximum = 130;
		  break;
		}
	  }
	}

	for (int i = 0; i < 13; i++)
	{
	  val = oreille->vo[i];

	  if (val)
	  {
		chart->Series[1]->AddXY(i + 1,val);

		if (val >= 70)
		{
		  serie = (TArrowSeries *)chart->Series[4];
		  val = i + 1;
		  serie->AddArrow(val,70,val,75);
		  break;
		}
	  }
	}

	for (int i = 0; i < 13; i++)
	{
	  val = oreille->ucl[i];

	  if (val)
	  {
		chart->Series[2]->AddXY(i + 1,val);

		if (val >= 120)
		{
		  serie = (TArrowSeries *)chart->Series[5];
		  val = i + 1;
		  serie->AddArrow(val,120,val,125);
		  chart->Axes->Left->Maximum = 130;
		  break;
		}
	  }
	}

	if (!ancien_va_oreille) return;

	for (int i = 0; i < 13; i++)
	{
	  val = ancien_va_oreille->va[i];

	  if (val)
	  {
		chart->Series[6]->AddXY(i + 1,val);

		if (val >= 120)
		{
		  serie = (TArrowSeries *)chart->Series[7];
		  val = i + 1;
		  serie->AddArrow(val,120,val,125);
		  chart->Axes->Left->Maximum = 130;
		  break;
		}
	  }
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TAudiogPrevFrm::FormShow(TObject *Sender)
{
  p_audiogram_oreille ancien_va_oreille;


	if (!ancien_va_record)
	{
	  ancien_va_oreille = NULL;
	}
	else ancien_va_oreille = (p_audiogram_oreille)&ancien_va_record->oreille_droite;

	draw_chart(Chart1,&audiog_record->oreille_droite,ancien_va_oreille);

    if (!ancien_va_record)
	{
	  ancien_va_oreille = NULL;
	}
	else ancien_va_oreille = (p_audiogram_oreille)&ancien_va_record->oreille_gauche;

	draw_chart(Chart2,&audiog_record->oreille_gauche,ancien_va_oreille);

	return;
}
//---------------------------------------------------------------------------

#include "common.hpp"

void __fastcall TAudiogPrevFrm::fill_quick_report(const opaque_ptr qrfrm_ptr)
{
  TAudiogImpFrm *qrfrm = (TAudiogImpFrm *)qrfrm_ptr;


	qrfrm->DateLbl->Caption = DateImpLbl->Caption;

	qrfrm->NomLbl->Caption = NomLbl->Caption;
	qrfrm->CodepLbl->Caption = CodepLbl->Caption;
	qrfrm->AdressLbl->Caption = adresse;
	qrfrm->MedLbl->Caption = MedLbl->Caption;

	qrfrm->DateAudiog->Caption = audiogram_date;

	qrfrm->DateTemoin->Caption = "";

	if (ancien_va_record)
	{
	  qrfrm->DateTemoin->Caption = ancien_va_date;
	}
	else
	{
	  qrfrm->AncienVaShape->Height = 0;
	  qrfrm->AncienVaShape->Width = 0;
	}

	draw_chart_in_quickreport(Chart1,qrfrm->OdImg);
	draw_chart_in_quickreport(Chart2,qrfrm->OgImg);

	qrfrm->WeberImg1->Picture->Assign(WeberImg1->Picture);
	qrfrm->WeberImg2->Picture->Assign(WeberImg2->Picture);
	qrfrm->WeberImg3->Picture->Assign(WeberImg3->Picture);
	qrfrm->WeberImg4->Picture->Assign(WeberImg4->Picture);
	qrfrm->WeberImg5->Picture->Assign(WeberImg5->Picture);

    return;
}

