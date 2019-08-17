//---------------------------------------------------------------------------

#ifndef Unit14H
#define Unit14H
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
#include <VCLTee.ArrowCha.hpp>
#include <VCLTee.Series.hpp>

#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

#include <audiograms_engine.h>

//---------------------------------------------------------------------------
class TAudiogPrevFrm : public TForm
{
__published:	// IDE-managed Components
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
	TGroupBox *GroupBox1;
	TShape *Shape1;
	TLabel *Label16;
	TShape *Shape2;
	TLabel *Label17;
	TShape *Shape3;
	TLabel *Label18;
	TLabel *GainpGrphDateLbl;
	TGroupBox *GroupBox3;
	TLabel *Label9;
	TImage *PrintImg;
	TLabel *ImpLbl;
	TLabel *PreviewLbl;
	TImage *PreviewImg;
	TImage *CancelImg;
	TLabel *CancelLbl;
	TChart *Chart1;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TArrowSeries *Series4;
	TArrowSeries *Series5;
	TArrowSeries *Series6;
	TLineSeries *Series7;
	TArrowSeries *Series8;
	TChart *Chart2;
	TLineSeries *LineSeries1;
	TLineSeries *LineSeries2;
	TLineSeries *LineSeries3;
	TArrowSeries *ArrowSeries1;
	TArrowSeries *ArrowSeries2;
	TArrowSeries *ArrowSeries3;
	TLineSeries *LineSeries4;
	TArrowSeries *ArrowSeries4;
	TShape *OdVaShape;
	TLabel *OdVaDateLbl;
	TShape *Shape5;
	TLabel *Label7;
	TShape *Shape6;
	TLabel *Label8;
	TShape *Shape7;
	TLabel *Label10;
	TShape *OgVaShape;
	TLabel *OgVaDateLbl;
	TLabel *OgDateLbl;
	TLabel *OdDateLbl;
	TPanel *Panel1;
	TPanel *WeberPanel1;
	TPanel *WeberPanel2;
	TPanel *WeberPanel3;
	TPanel *WeberPanel4;
	TPanel *WeberPanel5;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TImage *WeberImg1;
	TImage *WeberImg2;
	TImage *WeberImg3;
	TImage *WeberImg4;
	TImage *WeberImg5;
	TImageList *ImageList1;
	void __fastcall CancelLblMouseEnter(TObject *Sender);
	void __fastcall CancelLblMouseLeave(TObject *Sender);
	void __fastcall CancelImgMouseEnter(TObject *Sender);
	void __fastcall CancelImgMouseLeave(TObject *Sender);
	void __fastcall PreviewImgMouseEnter(TObject *Sender);
	void __fastcall PreviewImgMouseLeave(TObject *Sender);
	void __fastcall PrintImgMouseEnter(TObject *Sender);
	void __fastcall PrintImgMouseLeave(TObject *Sender);
	void __fastcall CancelImgClick(TObject *Sender);
	void __fastcall PreviewImgClick(TObject *Sender);
	void __fastcall PrintImgClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations

	void __fastcall draw_chart(TChart *chart,const p_audiogram_oreille oreille,const p_audiogram_oreille ancien_va_oreille);
	void __fastcall fill_quick_report(const opaque_ptr qrfrm_ptr);

public:		// User declarations

	p_audiogram_record audiog_record,ancien_va_record;
	UnicodeString adresse,audiogram_date,ancien_va_date;

	__fastcall TAudiogPrevFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAudiogPrevFrm *AudiogPrevFrm;
//---------------------------------------------------------------------------
#endif
