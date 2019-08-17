//---------------------------------------------------------------------------

#ifndef Unit8H
#define Unit8H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------

#include <tympano_engine.h>
#include <VCLTee.TeeSpline.hpp>

class TTympPrevFrm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox4;
	TLabel *Label58;
	TEdit *OdRsEdit1;
	TEdit *OdRsEdit2;
	TEdit *OdRsEdit3;
	TEdit *OdRsEdit4;
	TPanel *Panel79;
	TPanel *Panel78;
	TPanel *Panel77;
	TPanel *Panel76;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *OgRsEdit1;
	TEdit *OgRsEdit2;
	TEdit *OgRsEdit3;
	TEdit *OgRsEdit4;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TGroupBox *GroupBox2;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TShape *OdShape1;
	TLabel *Label6;
	TLabel *ImpLbl;
	TImage *PrintImg;
	TLabel *OdTympDate1Lbl;
	TImage *PreviewImg;
	TLabel *PreviewLbl;
	TImage *CancelImg;
	TLabel *CancelLbl;
	TLabel *NomLbl;
	TLabel *CodepLbl;
	TLabel *MedLbl;
	TLabel *DateImpLbl;
	TLabel *OpLbl;
	TLabel *OdTympDate2Lbl;
	TShape *OdShape2;
	TChart *Chart2;
	TLineSeries *LineSeries1;
	TLineSeries *Series3;
	TChart *Chart1;
	TLineSeries *LineSeries2;
	TLineSeries *LineSeries3;
	TLabel *OgTympDate1Lbl;
	TShape *OgShape1;
	TShape *OgShape2;
	TLabel *OgTympDate2Lbl;
	void __fastcall ImpLblMouseEnter(TObject *Sender);
	void __fastcall ImpLblMouseLeave(TObject *Sender);
	void __fastcall PrintImgMouseEnter(TObject *Sender);
	void __fastcall PrintImgMouseLeave(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelImgClick(TObject *Sender);
	void __fastcall PreviewImgClick(TObject *Sender);
	void __fastcall PrintImgClick(TObject *Sender);
	void __fastcall PreviewImgMouseEnter(TObject *Sender);
	void __fastcall PreviewImgMouseLeave(TObject *Sender);
	void __fastcall CancelImgMouseEnter(TObject *Sender);
	void __fastcall CancelImgMouseLeave(TObject *Sender);

private:

	void __fastcall fill_quick_report(const opaque_ptr qrfrm_ptr);

public:		// User declarations

	p_tympanogram_record tympano1,tympano2;
    UnicodeString adresse;
	__fastcall TTympPrevFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTympPrevFrm *TympPrevFrm;
//---------------------------------------------------------------------------
#endif
