//---------------------------------------------------------------------------

#ifndef Unit10H
#define Unit10H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <VCLTee.ArrowCha.hpp>

#include <gainp_engine.h>

//---------------------------------------------------------------------------
class TGainpPrevFrm : public TForm
{
__published:	// IDE-managed Components
	TChart *Chart1;
	TGroupBox *GroupBox1;
	TLineSeries *Series1;
	TGroupBox *GroupBox2;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *NomLbl;
	TLabel *CodepLbl;
	TLabel *MedLbl;
	TLabel *DateImpLbl;
	TLabel *OpLbl;
	TImage *PrintImg;
	TLabel *ImpLbl;
	TLabel *PreviewLbl;
	TImage *PreviewImg;
	TImage *CancelImg;
	TLabel *CancelLbl;
	TGroupBox *GroupBox3;
	TLabel *Label1;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *OreilleLbl;
	TLabel *NatureLbl;
	TLabel *TypeProtLbl;
	TLabel *RefLbl;
	TShape *Shape1;
	TLabel *Label16;
	TShape *Shape2;
	TLabel *Label17;
	TShape *Shape3;
	TLabel *Label18;
	TLabel *Label10;
	TLabel *AuditionLbl;
	TLabel *SeuilProtLbl;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *GainpLbl;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *DynaLbl;
	TLabel *MclLbl;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TArrowSeries *Series4;
	TArrowSeries *Series5;
	TArrowSeries *Series6;
	TLabel *GainpGrphDateLbl;
	void __fastcall CancelImgClick(TObject *Sender);
	void __fastcall CancelLblMouseEnter(TObject *Sender);
	void __fastcall CancelLblMouseLeave(TObject *Sender);
	void __fastcall CancelImgMouseEnter(TObject *Sender);
	void __fastcall CancelImgMouseLeave(TObject *Sender);
	void __fastcall PreviewImgMouseEnter(TObject *Sender);
	void __fastcall PreviewImgMouseLeave(TObject *Sender);
	void __fastcall PrintImgMouseEnter(TObject *Sender);
	void __fastcall PrintImgMouseLeave(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall PreviewImgClick(TObject *Sender);
	void __fastcall PrintImgClick(TObject *Sender);

private:	// User declarations

	void __fastcall fill_quick_report(const opaque_ptr qrfrm_ptr);

public:		// User declarations

    p_gainp_record gainp_record;
	UnicodeString adresse;
	__fastcall TGainpPrevFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGainpPrevFrm *GainpPrevFrm;
//---------------------------------------------------------------------------
#endif
