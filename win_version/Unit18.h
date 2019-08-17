//---------------------------------------------------------------------------

#ifndef Unit18H
#define Unit18H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>

#include "geographic_stats.h"
#include <Vcl.Imaging.jpeg.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

//---------------------------------------------------------------------------
class TGeoFrm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TSplitView *SplitView1;
	TLabel *Label4;
	TLabel *Label5;
	TListView *ListView1;
	TListView *ListView2;
	TScrollBox *ScrollBox1;
	TImage *Image1;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TPanel *Panel15;
	TPanel *Panel16;
	TPanel *Panel17;
	TPanel *Panel18;
	TPanel *Panel19;
	TPanel *Panel20;
	TPanel *Panel21;
	TPanel *Panel22;
	TPanel *Panel23;
	TPanel *Panel24;
	TPanel *Panel25;
	TPanel *Panel26;
	TPanel *Panel27;
	TPanel *Panel28;
	TPanel *ArHPanel;
	TPanel *BejHPanel;
	TPanel *BenHPanel;
	TPanel *BizHPanel;
	TPanel *GabHPanel;
	TPanel *GafHPanel;
	TPanel *JenHPanel;
	TPanel *KairHPanel;
	TPanel *KassHPanel;
	TPanel *KebHPanel;
	TPanel *KefHPanel;
	TPanel *MaHPanel;
	TPanel *ManHPanel;
	TPanel *MeHPanel;
	TPanel *MonHPanel;
	TPanel *NabHPanel;
	TPanel *SfaxHPanel;
	TPanel *SidHPanel;
	TPanel *SilHPanel;
	TPanel *SoussHPanel;
	TPanel *TatHPanel;
	TPanel *TozHPanel;
	TPanel *TunHPanel;
	TPanel *ZagHPanel;
	TPanel *ArFPanel;
	TPanel *BejFPanel;
	TPanel *BenFPanel;
	TPanel *BizFPanel;
	TPanel *GabFPanel;
	TPanel *GaFPanel;
	TPanel *JenFPanel;
	TPanel *KairFPanel;
	TPanel *KassFPanel;
	TPanel *KebFPanel;
	TPanel *KeFPanel;
	TPanel *MahFPanel;
	TPanel *ManFPanel;
	TPanel *MedFPanel;
	TPanel *MonFPanel;
	TPanel *NabFPanel;
	TPanel *SfaxFPanel;
	TPanel *SidiFPanel;
	TPanel *SilFPanel;
	TPanel *SoussFPanel;
	TPanel *TatFPanel;
	TPanel *TozFPanel;
	TPanel *TunFPanel;
	TPanel *ZagFPanel;
	TPanel *ArTotPanel;
	TPanel *BejTotPanel;
	TPanel *BenTotPanel;
	TPanel *BizTotPanel;
	TPanel *GabTotPanel;
	TPanel *GafTotPanel;
	TPanel *JenTotPanel;
	TPanel *KairTotPanel;
	TPanel *KassTotPanel;
	TPanel *KebTotPanel;
	TPanel *KefTotPanel;
	TPanel *MahTotPanel;
	TPanel *ManTotPanel;
	TPanel *MedTotPanel;
	TPanel *MonTotPanel;
	TPanel *NabeulTotPanel;
	TPanel *SfaxTotPanel;
	TPanel *SidiTotPanel;
	TPanel *SilTotPanel;
	TPanel *SousseTotPanel;
	TPanel *TataTotPanel;
	TPanel *TozTotPanel;
	TPanel *TunTotPanel;
	TPanel *ZagTotPanel;
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TShape *Shape4;
	TShape *Shape5;
	TShape *Shape6;
	TShape *Shape7;
	TShape *Shape8;
	TShape *Shape9;
	TShape *Shape10;
	TShape *Shape11;
	TShape *Shape12;
	TShape *Shape13;
	TShape *Shape14;
	TShape *Shape15;
	TShape *Shape16;
	TShape *Shape17;
	TShape *Shape18;
	TShape *Shape19;
	TShape *Shape20;
	TShape *Shape21;
	TShape *Shape22;
	TShape *Shape23;
	TShape *Shape24;
	TScrollBox *ScrollBox2;
	TImage *Image2;
	TPanel *Panel29;
	TPanel *GouvPanel;
	TPanel *Panel40;
	TPanel *Panel55;
	TPanel *Panel56;
	TPanel *HPanel;
	TPanel *FPanel;
	TPanel *TotalPanel;
	TRadioButton *NordRadio;
	TRadioButton *CapBonRadio;
	TRadioButton *SahelRadio;
	TRadioButton *CentreRadio;
	TGroupBox *GroupBox1;
	TRadioButton *RadioButton1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TBalloonHint *BalloonHint1;
	void __fastcall Label1MouseEnter(TObject *Sender);
	void __fastcall Label1MouseLeave(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall NordRadioClick(TObject *Sender);
private:	// User declarations

	void __fastcall Navigate(const int page_index);

	void __fastcall Gouvernorats_Stats();
	void __fastcall Regions_Stats(const t_tunisia_region_types region_type);

public:		// User declarations

	p_geographic_stat_table stat_table;
	TStringList *list;

	void __fastcall GlobalStats();

	__fastcall TGeoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGeoFrm *GeoFrm;
//---------------------------------------------------------------------------
#endif
