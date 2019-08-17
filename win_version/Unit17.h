//---------------------------------------------------------------------------

#ifndef Unit17H
#define Unit17H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>

#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Graphics.hpp>

#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include "VCLTee.TeeDoubleHorizBar.hpp"
#include "VCLTee.TeeSubChart.hpp"

#include "demographic_stats.h"
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>

//---------------------------------------------------------------------------
class TDemoStatFrm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TSplitView *SplitView1;
	TLabel *Label1;
	TChart *Chart1;
	TBarSeries *Series1;
	TImage *Image1;
	TImage *Image3;
	TImage *Image2;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TLabel *Label2;
	TLabel *Label5;
	TLabel *Label8;
	TLabel *Label11;
	TLabel *Label14;
	TLabel *Label17;
	TLabel *Label20;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TLabel *ChildmLbl;
	TLabel *ChildfLbl;
	TLabel *AdomLbl;
	TLabel *AdofLbl;
	TLabel *JeunemLbl;
	TLabel *JeunefLbl;
	TLabel *AdultfLbl;
	TLabel *AdultmLbl;
	TLabel *CinquantfLbl;
	TLabel *CinquantmLbl;
	TLabel *PafLbl;
	TLabel *PamLbl;
	TImage *Image8;
	TImage *Image9;
	TImage *Image7;
	TImage *Image10;
	TImage *Image11;
	TImage *Image12;
	TImage *Image13;
	TImage *Image14;
	TImage *Image15;
	TImage *Image16;
	TImage *Image17;
	TImage *Image18;
	TImage *Image19;
	TImage *Image20;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label9;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TChart *Chart2;
	TPieSeries *Series2;
	TTeeGDIPlus *TeeGDIPlus1;
	TRadioButton *PercentFirstConsultRadio;
	TPanel *Panel1;
	TRadioButton *PercentCurrentAgeRadio;
	TCheckBox *PercenthChk;
	TCheckBox *PercentfChk;
	TImage *Image21;
	TImage *Image22;
	TChart *Chart3;
	TDoubleHorizBarSeries *Series3;
	TLabel *Label10;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label21;
	TLabel *Label31;
	TLabel *Label32;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *Label35;
	TPanel *Panel2;
	TImage *Image23;
	TImage *Image24;
	TRadioButton *PariteFirstConsultRadio;
	TRadioButton *PariteCurrentAgeRadio;
	TChart *Chart4;
	TPieSeries *PieSeries1;
	TRadioButton *PariteEnfantRadio;
	TRadioButton *PariteAdoRadio;
	TRadioButton *PariteJeuneRadio;
	TRadioButton *PariteAdultRadio;
	TRadioButton *Parite50Radio;
	TRadioButton *PariteVieuxRadio;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TPanel *Panel3;
	TLabel *Label40;
	TLabel *Label41;
	TLabel *Label42;
	TLabel *Label43;
	TLabel *Label44;
	TLabel *Label45;
	TLabel *Label46;
	TLabel *Label47;
	TLabel *Label48;
	TLabel *Label49;
	TLabel *Label53;
	TLabel *PatCntLbl;
	TLabel *MaleCntLbl;
	TLabel *FemaleCntLbl;
	TLabel *EquityCatLbl;
	TLabel *EquityAgeLbl;
	TLabel *NoEquityCatLbl;
	TLabel *NoEquityAgeLbl;
	TListView *ListView1;
	void __fastcall Label21MouseEnter(TObject *Sender);
	void __fastcall Label21MouseLeave(TObject *Sender);
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall PercentFirstConsultRadioClick(TObject *Sender);
	void __fastcall PariteFirstConsultRadioClick(TObject *Sender);
private:	// User declarations

	void __fastcall Navigate(const int page_index);

	void __fastcall Pourcentage(const boolean current_age);
	void __fastcall Pyramid(const boolean current_age);
	void __fastcall PariteSexes(const boolean current_age,const t_age_category_type age_category);
	void __fastcall Cross_Stats();

public:		// User declarations

   p_demographic_stat_table stat_table;

   void __fastcall FullStats(const boolean current_age);

	__fastcall TDemoStatFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDemoStatFrm *DemoStatFrm;
//---------------------------------------------------------------------------
#endif
