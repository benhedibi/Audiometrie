//---------------------------------------------------------------------------

#ifndef Unit12H
#define Unit12H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeSpline.hpp>
//---------------------------------------------------------------------------

#include <audiovocs_engine.h>



class TAvocPrevFrm : public TForm
{
__published:	// IDE-managed Components
	TImage *PrintImg;
	TLabel *ImpLbl;
	TLabel *PreviewLbl;
	TImage *PreviewImg;
	TImage *CancelImg;
	TLabel *CancelLbl;
	TGroupBox *GroupBox1;
	TShape *Shape1;
	TLabel *Label16;
	TShape *Shape2;
	TLabel *Label17;
	TShape *Shape3;
	TLabel *Label18;
	TLabel *GainpGrphDateLbl;
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
	TGroupBox *GroupBox3;
	TLabel *Label1;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *OreilleLbl;
	TLabel *NatureLbl;
	TLabel *ControlLbl;
	TImage *Image1;
	TImage *Image2;
	TLabel *Label11;
	TLabel *Label12;
	TImage *Image3;
	TLabel *Label13;
	TLabel *AvocDateLbl;
	TChart *Chart1;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TGroupBox *GroupBox4;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *MisaPanel;
	TPanel *SisaPanel;
	TPanel *TdsaPanel;
	TPanel *MiaaPanel;
	TPanel *SiaaPanel;
	TPanel *TdaaPanel;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TLabel *Label10;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label9;
	TLabel *Label24;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelImgClick(TObject *Sender);
	void __fastcall CancelLblMouseEnter(TObject *Sender);
	void __fastcall CancelLblMouseLeave(TObject *Sender);
	void __fastcall CancelImgMouseEnter(TObject *Sender);
	void __fastcall CancelImgMouseLeave(TObject *Sender);
	void __fastcall PreviewImgMouseEnter(TObject *Sender);
	void __fastcall PreviewImgMouseLeave(TObject *Sender);
	void __fastcall PrintImgMouseEnter(TObject *Sender);
	void __fastcall PrintImgMouseLeave(TObject *Sender);
	void __fastcall PreviewImgClick(TObject *Sender);
	void __fastcall PrintImgClick(TObject *Sender);
private:	// User declarations

	void __fastcall fill_quick_report(const opaque_ptr qrfrm_ptr);

public:		// User declarations

	p_audiovoc_record avoc_record;
    UnicodeString adresse,audiovoc_date;
	__fastcall TAvocPrevFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAvocPrevFrm *AvocPrevFrm;
//---------------------------------------------------------------------------
#endif
