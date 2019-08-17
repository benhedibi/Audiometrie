//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Mask.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.WinXCtrls.hpp>


#include <globaldef.h>

#include <lilly_db2.h>
#include <lilly_session_manager.h>

#include <operators_engine.h>
#include <doctors_engine.h>
#include <patients_engine.h>
#include <consultations_engine.h>
#include <audiograms_engine.h>
#include <tympano_engine.h>
#include <gainp_engine.h>
#include <audiovocs_engine.h>

#include "common.hpp"
#include "vtm_manager.hpp"


typedef struct {
				 TVTM_Manager *vtm_manager;
				 unsigned_int rec_count;
				 unsigned_int filter_rec_count;
			   } t_listview_vtm_params,*p_list_view_vtm_params;

typedef struct {
				 unsigned_int count;
				 uint64 offsets[64];
			   } t_offsets_table,*p_offsets_table;

typedef struct {
				 unsigned_int codep;
				 t_date_time date_debut;
				 t_date_time date_fin;
				 bool audiogram;
				 bool tympano;
				 bool gainp;
				 bool audiovoc;
				 UnicodeString Patient;
				 UnicodeString Operateur;
			   } t_consultations_filter_params,*p_consultations_filter_params;

typedef struct {
				 TLabel *label;
				 int animation_loop_count;
				 bool ping_pong;
			   } t_warn_label_animation_params;

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TImage *PatPicture;
	TShape *Shape1;
	TTreeView *PatConsultView;
	TMaskEdit *PatNaissanceEdit;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *PatNomEdit;
	TComboBox *PatSexCombo;
	TLabel *Label9;
	TLabel *PatConsAgeLbl;
	TEdit *PatTailleEdit;
	TEdit *PatPoidEdit;
	TComboBox *PatMedCombo;
	TComboBox *PatPaysCombo;
	TLabel *Label11;
	TEdit *PatVilleEdit;
	TLabel *Label12;
	TLabel *Label13;
	TComboBox *PatGouvCombo;
	TLabel *Label14;
	TEdit *PatPhone1Edit;
	TEdit *PatPhone2Edit;
	TLabel *Label15;
	TEdit *PatMailEdit;
	TLabel *Label16;
	TComboBox *PatJobCombo;
	TLabel *Label17;
	TMemo *PatObsMemo;
	TLabel *Label18;
	TShape *Shape2;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TListView *PatListView;
	TSearchBox *PatQuickSrchEdit;
	TRadioButton *PatNomRadio;
	TRadioButton *PatAucunRadio;
	TRadioButton *PatCodeRadio;
	TListView *ConsListView;
	TEdit *ConsFltNomEdit;
	TMaskEdit *ConsFltDateEdit1;
	TMaskEdit *ConsFltDateEdit2;
	TCheckBox *ConsFltAudiogChk;
	TCheckBox *ConsFltTympanoChk;
	TCheckBox *ConsFltGpChk;
	TCheckBox *ConsFltAvocChk;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TImage *Image15;
	TEdit *ConsFltCodeEdit;
	TLabel *Label31;
	TToggleSwitch *ConsToggle;
	TLabel *Label32;
	TLabel *Label33;
	TLabel *ConsCntLbl;
	TImage *PatFirstImg;
	TImage *PatLastImg;
	TLabel *Label34;
	TLabel *PatCntLbl;
	TShape *Shape3;
	TLabel *Label35;
	TLabel *Label36;
	TComboBox *ConsPatMedCombo;
	TImage *ConsPatImage;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TLabel *Label43;
	TImageList *ImageList1;
	TImage *Image17;
	TShape *Shape4;
	TLabel *Label44;
	TMemo *ConsPatObsMemo;
	TListView *ConsPatListView;
	TLabel *Label40;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TTabSheet *TabSheet7;
	TTabSheet *TabSheet8;
	TImage *Image18;
	TLabel *Label41;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TPanel *Panel16;
	TPanel *Panel17;
	TPanel *Panel18;
	TPanel *Panel19;
	TEdit *OdVaEdit1;
	TPanel *Panel20;
	TPanel *Panel15;
	TEdit *OdVaEdit2;
	TEdit *OdVaEdit3;
	TEdit *OdVaEdit4;
	TEdit *OdVaEdit5;
	TEdit *OdVaEdit6;
	TEdit *OdVaEdit7;
	TEdit *OdVaEdit8;
	TEdit *OdVaEdit9;
	TEdit *OdVaEdit10;
	TEdit *OdVaEdit11;
	TEdit *OdVoEdit1;
	TEdit *OdVoEdit2;
	TEdit *OdVoEdit3;
	TEdit *OdVoEdit4;
	TEdit *OdVoEdit5;
	TEdit *OdVoEdit6;
	TEdit *OdVoEdit7;
	TEdit *OdVoEdit8;
	TEdit *OdVoEdit9;
	TEdit *OdVoEdit10;
	TEdit *OdVoEdit11;
	TEdit *OdUclEdit1;
	TEdit *OdUclEdit2;
	TEdit *OdUclEdit3;
	TEdit *OdUclEdit4;
	TEdit *OdUclEdit5;
	TEdit *OdUclEdit6;
	TEdit *OdUclEdit7;
	TEdit *OdUclEdit8;
	TEdit *OdUclEdit9;
	TEdit *OdUclEdit10;
	TEdit *OdUclEdit11;
	TLabel *Label42;
	TPanel *Panel21;
	TPanel *Panel22;
	TPanel *Panel23;
	TPanel *Panel24;
	TEdit *OgUclEdit1;
	TEdit *OgVoEdit1;
	TEdit *OgVaEdit1;
	TPanel *Panel25;
	TPanel *Panel26;
	TPanel *Panel27;
	TPanel *Panel28;
	TPanel *Panel29;
	TPanel *Panel30;
	TPanel *Panel31;
	TPanel *Panel32;
	TPanel *Panel33;
	TPanel *Panel34;
	TPanel *Panel35;
	TEdit *OgVaEdit11;
	TEdit *OgVoEdit11;
	TEdit *OgUclEdit11;
	TEdit *OgUclEdit10;
	TEdit *OgVoEdit10;
	TEdit *OgVaEdit10;
	TEdit *OgVaEdit9;
	TEdit *OgVoEdit9;
	TEdit *OgUclEdit9;
	TEdit *OgUclEdit8;
	TEdit *OgVoEdit8;
	TEdit *OgVaEdit8;
	TEdit *OgVaEdit7;
	TEdit *OgVoEdit7;
	TEdit *OgUclEdit7;
	TEdit *OgUclEdit6;
	TEdit *OgVoEdit6;
	TEdit *OgVaEdit6;
	TEdit *OgVaEdit5;
	TEdit *OgVoEdit5;
	TEdit *OgUclEdit5;
	TEdit *OgUclEdit4;
	TEdit *OgVoEdit4;
	TEdit *OgVaEdit4;
	TEdit *OgVaEdit3;
	TEdit *OgVoEdit3;
	TEdit *OgUclEdit3;
	TEdit *OgUclEdit2;
	TEdit *OgVoEdit2;
	TEdit *OgVaEdit2;
	TPanel *Panel37;
	TCheckBox *ObsConChk1;
	TCheckBox *ObsConChk2;
	TCheckBox *ObsConChk3;
	TCheckBox *ObsConChk4;
	TCheckBox *ObsConChk5;
	TCheckBox *ObsConChk6;
	TCheckBox *ObsConChk7;
	TCheckBox *ObsConChk8;
	TCheckBox *ObsConChk9;
	TCheckBox *ObsConChk10;
	TCheckBox *ObsConChk11;
	TCheckBox *ObsConChk12;
	TCheckBox *ObsConChk13;
	TCheckBox *ObsConChk20;
	TCheckBox *ObsConChk21;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TCheckBox *ObsConChk14;
	TCheckBox *ObsConChk15;
	TCheckBox *ObsConChk16;
	TCheckBox *ObsConChk22;
	TCheckBox *ObsConChk17;
	TCheckBox *ObsConChk18;
	TCheckBox *ObsConChk19;
	TPanel *Panel36;
	TPanel *Panel38;
	TPanel *Panel39;
	TPanel *Panel40;
	TPanel *Panel41;
	TMemo *AudiogObsMemo;
	TEdit *WeberEdit1;
	TEdit *WeberEdit2;
	TEdit *WeberEdit3;
	TEdit *WeberEdit4;
	TEdit *WeberEdit5;
	TLabel *Label45;
	TLabel *Label46;
	TListView *AudiogListView;
	TLabel *Label47;
	TComboBox *AudiogDefValCombo;
	TPanel *Panel43;
	TLabel *Label51;
	TImage *Image24;
	TImage *Image25;
	TImage *Image19;
	TImage *Image26;
	TPanel *Panel46;
	TLabel *Label54;
	TEdit *OdPressEdit1;
	TEdit *OdPressEdit2;
	TPanel *Panel47;
	TPanel *Panel48;
	TEdit *OdPressEdit3;
	TEdit *OdPressEdit4;
	TPanel *Panel49;
	TPanel *Panel50;
	TEdit *OdPressEdit5;
	TPanel *Panel45;
	TPanel *Panel51;
	TPanel *Panel52;
	TPanel *Panel53;
	TPanel *Panel54;
	TPanel *Panel55;
	TPanel *Panel56;
	TPanel *Panel57;
	TEdit *OdPressEdit6;
	TEdit *OdPressEdit7;
	TEdit *OdPressEdit8;
	TEdit *OdPressEdit9;
	TEdit *OdPressEdit10;
	TEdit *OdPressEdit11;
	TEdit *OdPressEdit12;
	TEdit *OdPressEdit13;
	TListView *TympanoListView;
	TLabel *Label55;
	TPanel *Panel58;
	TComboBox *TympanoDefValCombo;
	TPanel *Panel59;
	TPanel *Panel60;
	TPanel *Panel61;
	TPanel *Panel62;
	TEdit *OdRsEdit1;
	TEdit *OdRsEdit2;
	TEdit *OdRsEdit3;
	TEdit *OdRsEdit4;
	TLabel *Label56;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TLabel *Label57;
	TLabel *Label58;
	TEdit *OgPressEdit6;
	TEdit *OgPressEdit1;
	TEdit *OgPressEdit2;
	TEdit *OgPressEdit3;
	TEdit *OgPressEdit4;
	TEdit *OgPressEdit5;
	TEdit *OgPressEdit7;
	TEdit *OgPressEdit8;
	TEdit *OgPressEdit9;
	TEdit *OgPressEdit10;
	TEdit *OgPressEdit11;
	TEdit *OgPressEdit12;
	TEdit *OgPressEdit13;
	TEdit *OgRsEdit1;
	TEdit *OgRsEdit2;
	TEdit *OgRsEdit3;
	TEdit *OgRsEdit4;
	TPanel *Panel63;
	TPanel *Panel64;
	TPanel *Panel65;
	TPanel *Panel66;
	TPanel *Panel67;
	TPanel *Panel68;
	TPanel *Panel69;
	TPanel *Panel70;
	TPanel *Panel71;
	TPanel *Panel72;
	TPanel *Panel73;
	TPanel *Panel74;
	TPanel *Panel75;
	TPanel *Panel76;
	TPanel *Panel77;
	TPanel *Panel78;
	TPanel *Panel79;
	TMemo *TympanoObsMemo;
	TLabel *Label59;
	TPanel *Panel80;
	TPanel *Panel81;
	TPanel *Panel82;
	TPanel *Panel83;
	TPanel *Panel84;
	TPanel *Panel85;
	TPanel *Panel86;
	TPanel *Panel87;
	TPanel *Panel88;
	TPanel *Panel89;
	TEdit *SaapEdit1;
	TEdit *SaapEdit2;
	TEdit *SaapEdit3;
	TEdit *SaapEdit4;
	TEdit *SaapEdit5;
	TEdit *SaapEdit6;
	TEdit *SaapEdit7;
	TEdit *SaapEdit8;
	TEdit *SaapEdit9;
	TEdit *SaapEdit10;
	TPanel *Panel90;
	TEdit *AvapEdit1;
	TPanel *Panel91;
	TEdit *AvapEdit2;
	TEdit *AvapEdit3;
	TEdit *AvapEdit4;
	TEdit *AvapEdit5;
	TEdit *AvapEdit6;
	TEdit *AvapEdit7;
	TEdit *AvapEdit8;
	TEdit *AvapEdit9;
	TEdit *AvapEdit10;
	TGroupBox *GroupBox5;
	TCheckBox *AvocOgChk;
	TCheckBox *AvocOdChk;
	TCheckBox *AvocChlChk;
	TGroupBox *GroupBox6;
	TGroupBox *GroupBox7;
	TGroupBox *GroupBox8;
	TImage *Image33;
	TLabel *Label62;
	TListView *AvocListView;
	TMemo *AvocObsMemo;
	TLabel *Label64;
	TPanel *Panel93;
	TComboBox *AvocDefValCombo;
	TRadioButton *AvocAallRadio;
	TRadioButton *AvocSallRadio;
	TRadioButton *AvocMonoChk;
	TRadioButton *AvocDissRadio;
	TPanel *Panel94;
	TPanel *Panel95;
	TPanel *Panel96;
	TPanel *Panel97;
	TPanel *Panel98;
	TEdit *GainpVaEdit1;
	TEdit *GainpVoEdit1;
	TEdit *GainpUclEdit1;
	TPanel *Panel99;
	TEdit *GainpVaEdit2;
	TEdit *GainpVoEdit2;
	TEdit *GainpUclEdit2;
	TPanel *Panel100;
	TEdit *GainpVaEdit3;
	TEdit *GainpVoEdit3;
	TEdit *GainpUclEdit3;
	TPanel *Panel101;
	TEdit *GainpVaEdit4;
	TEdit *GainpVoEdit4;
	TEdit *GainpUclEdit4;
	TPanel *Panel102;
	TEdit *GainpVaEdit5;
	TEdit *GainpVoEdit5;
	TEdit *GainpUclEdit5;
	TPanel *Panel103;
	TEdit *GainpVaEdit6;
	TEdit *GainpVoEdit6;
	TEdit *GainpUclEdit6;
	TPanel *Panel104;
	TEdit *GainpVaEdit7;
	TEdit *GainpVoEdit7;
	TEdit *GainpUclEdit7;
	TPanel *Panel105;
	TEdit *GainpVaEdit8;
	TEdit *GainpVoEdit8;
	TEdit *GainpUclEdit8;
	TPanel *Panel106;
	TEdit *GainpVaEdit9;
	TEdit *GainpVoEdit9;
	TEdit *GainpUclEdit9;
	TPanel *Panel107;
	TEdit *GainpVaEdit10;
	TEdit *GainpVoEdit10;
	TEdit *GainpUclEdit10;
	TPanel *Panel108;
	TEdit *GainpVaEdit11;
	TEdit *GainpVoEdit11;
	TEdit *GainpUclEdit11;
	TGroupBox *GroupBox9;
	TCheckBox *GainpOgChk;
	TCheckBox *GainpOdChk;
	TCheckBox *GainpChlChk;
	TGroupBox *GroupBox10;
	TRadioButton *PurRadio;
	TRadioButton *BlancRadio;
	TGroupBox *GroupBox11;
	TGroupBox *GroupBox12;
	TComboBox *GainpDefValCombo;
	TPanel *Panel110;
	TMemo *GainpObsMemo;
	TLabel *Label67;
	TLabel *Label68;
	TListView *GainpListView;
	TPanel *Panel111;
	TComboBox *GainpRefCombo;
	TRadioButton *PulseRadio;
	TRadioButton *ContourRadio;
	TRadioButton *MesureRadio;
	TRadioButton *RicRadio;
	TImage *TopBannerImg;
	TImage *Image6;
	TImage *Image7;
	TImage *Image8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TTabSheet *TabSheet9;
	TImage *Image3;
	TImage *AcceuilleImg;
	TImage *ConsultImg;
	TImage *PatImg;
	TImage *OpImg;
	TImage *MedImg;
	TImage *StatImg;
	TImage *ParamImg;
	TImage *InfoImg;
	TLabel *AcceuilLbl;
	TLabel *ConsultLbl;
	TLabel *PatientLbl;
	TLabel *OpLbl;
	TLabel *MedLbl;
	TLabel *StatLbl;
	TLabel *ParamLbl;
	TLabel *InfoLbl;
	TImage *ConsListAddImg;
	TImage *ConsListEditImg;
	TImage *ConsListDelImg;
	TComboBox *ConsFltOpCombo;
	TImage *PatValidateImg;
	TImage *PatEditImg;
	TImage *PatDeleteImg;
	TImage *PatCancelImg;
	TImage *PatListAddImg;
	TImage *PatListEditImg;
	TImage *PatListDelImg;
	TLabel *Label1;
	TLabel *Label19;
	TLabel *PatAgeLbl;
	TTimer *WarnLblTimer;
	TLabel *PatValidateLbl;
	TLabel *PatEditLbl;
	TLabel *PatDelLbl;
	TLabel *PatCancelLbl;
	TLabel *PatListAddLbl;
	TLabel *PatListEditLbl;
	TLabel *PatListDelLbl;
	TLabel *ConsListAddLbl;
	TLabel *ConsListEditLbl;
	TLabel *ConsListDelLbl;
	TImageList *ImageList2;
	TImage *ConsFirstImg;
	TLabel *Label52;
	TLabel *Label53;
	TImage *ConsLastImg;
	TImage *ConsFltImg;
	TLabel *ConsFltLbl;
	TShape *ConsFltShape;
	TLabel *ConsPatNameLbl;
	TLabel *ConsPatCodeLbl;
	TLabel *ConsPatAgeLbl;
	TLabel *ConsPatDateLbl;
	TLabel *ConsPatOpLbl;
	TImage *ConsPatValidImg;
	TImage *ConsPatEditImg;
	TImage *ConsPatDelImg;
	TLabel *ConsPatDelLbl;
	TLabel *ConsPatEditLbl;
	TLabel *ConsPatValidLbl;
	TLabel *ConsPatCancelLbl;
	TImage *ConsPatCancelImg;
	TImage *AudiogValidImg;
	TImage *AudiogEditImg;
	TImage *AudiogDelImg;
	TImage *AudiogCancelImg;
	TLabel *AudiogCancelLbl;
	TLabel *AudiogDelLbl;
	TLabel *AudiogEditLbl;
	TLabel *AudiogValidLbl;
	TImage *AudiogViewImg;
	TLabel *AudiogViewLbl;
	TImage *AudiogAddGraphImg;
	TLabel *AudiogAddGraphLbl;
	TLabel *AudiogDelGraphLbl;
	TImage *AudiogDelGraphImg;
	TImage *TympValidImg;
	TLabel *TympValidLbl;
	TLabel *TympEditLbl;
	TImage *TympEditImg;
	TImage *TympDelImg;
	TLabel *TympDelLbl;
	TLabel *TympCancelLbl;
	TImage *TympCancelImg;
	TImage *TympViewImg;
	TLabel *TympViewLbl;
	TLabel *TympAddGrphLbl;
	TImage *TympAddGrphImg;
	TImage *TympDelGrphImg;
	TLabel *TympDelGrphLbl;
	TImage *AvocValidImg;
	TLabel *AvocValidLbl;
	TLabel *AvocEditLbl;
	TImage *AvocEditImg;
	TImage *AvocDelImg;
	TLabel *AvocDelLbl;
	TLabel *AvocCancelLbl;
	TImage *AvocCancelImg;
	TImage *AvocViewImg;
	TLabel *AvocViewLbl;
	TLabel *AvocAddGrphLbl;
	TImage *AvocAddGrphImg;
	TImage *AvocDelGrphImg;
	TLabel *AvocDelGrphLbl;
	TImage *Image1;
	TImage *Image2;
	TLabel *Label26;
	TImage *Image5;
	TLabel *Label48;
	TLabel *Label49;
	TImage *Image12;
	TImage *Image13;
	TLabel *Label50;
	TLabel *Label60;
	TImage *Image14;
	TImage *Image21;
	TLabel *Label61;
	TLabel *Label65;
	TImage *Image22;
	TImage *Image23;
	TImage *GainpValidImg;
	TLabel *GainpValidLbl;
	TLabel *GainpEditLbl;
	TImage *GainpEditImg;
	TImage *GainpDelImg;
	TLabel *GainpDelLbl;
	TLabel *GainpCancelLbl;
	TImage *GainpCancelImg;
	TImage *GainpViewImg;
	TLabel *GainpViewLbl;
	TLabel *GainpAddGrphLbl;
	TImage *GainpAddGrphImg;
	TImage *GainpDelGrphImg;
	TLabel *GainpDelGrphLbl;
	TLabel *GainpRefLbl;
	TImage *Image4;
	TLabel *Label63;
	TImage *Image16;
	TLabel *Label66;
	TImage *Image20;
	TLabel *Label69;
	TImage *Image27;
	TLabel *Label70;
	TLabel *Label71;
	TLabel *Label72;
	TLabel *LastPatNameLbl;
	TLabel *Label74;
	TLabel *LastConsPatNameLbl;
	TLabel *Label77;
	TLabel *Label78;
	TLabel *Label79;
	TImage *Image28;
	TLabel *Label84;
	TLabel *Label85;
	TLabel *Label89;
	TLabel *Label92;
	TLabel *SyncStateLbl;
	TLabel *Label81;
	TLabel *Label104;
	TLabel *FaceRecStateLbl;
	TLabel *Label82;
	TLabel *Label83;
	TLabel *ConnectionStateLbl;
	TImage *Image29;
	TLabel *Label88;
	TLabel *UpdateModeLbl;
	TLabel *Label91;
	TLabel *Label94;
	TLabel *LastPatTimeLbl;
	TLabel *LastPatOpNameLbl;
	TLabel *LastConsTimeLbl;
	TLabel *LastConOpNameLbl;
	TLabel *LastConsOpLbl1;
	TLabel *LastConsOpLbl2;
	TLabel *SyncTimeLbl;
	TLabel *SyncStatusLbl;
	TLabel *UpdateTimeLbl;
	TLabel *UpdateStatusLbl;
	TLabel *QuotConsCountLbl;
	TLabel *QuotPatCountLbl;
	TLabel *QuotOpCountLbl;
	TLabel *FaceRecOpSupportLbl;
	TLabel *FaceRecPatSupportLbl;
	TLabel *QuotDateLbl;
	TLabel *Label75;
	TLabel *OpNameLbl;
	TBalloonHint *BalloonHint1;
	TTabSheet *TabSheet10;
	TImage *Image30;
	TImage *Image31;
	TImage *Image32;
	TImage *Image34;
	TImage *Image35;
	TImage *Image36;
	TImage *Image39;
	TImage *Image40;
	TLabel *Label10;
	TLabel *DemogLbl;
	TLabel *GeoLbl;
	TLabel *StatJobLbl;
	TLabel *StatMedLbl;
	TLabel *StatAudiogLbl;
	TLabel *StatTympanoLbl;
	TLabel *StatAvocLbl;
	TLabel *StatGainpLbl;
	TLabel *StatDescriptLbl;
	TImage *Image37;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall InfoImgMouseEnter(TObject *Sender);
	void __fastcall AcceuilleImgMouseLeave(TObject *Sender);
	void __fastcall AcceuilleImgClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ConsToggleClick(TObject *Sender);
	void __fastcall PatAucunRadioClick(TObject *Sender);
	void __fastcall PatTailleEditExit(TObject *Sender);
	void __fastcall PatPoidEditExit(TObject *Sender);
	void __fastcall PatListAddImgClick(TObject *Sender);
	void __fastcall PatMailEditExit(TObject *Sender);
	void __fastcall WarnLblTimerTimer(TObject *Sender);
	void __fastcall PatMailEditEnter(TObject *Sender);
	void __fastcall PatNaissanceEditExit(TObject *Sender);
	void __fastcall PatPaysComboSelect(TObject *Sender);
    void __fastcall PatListViewData(TObject *Sender, TListItem *Item);
	void __fastcall PatListViewCustomDrawSubItem(TCustomListView *Sender, TListItem *Item,int SubItem, TCustomDrawState State, bool &DefaultDraw);
	void __fastcall PatLastImgClick(TObject *Sender);
	void __fastcall PatFirstImgClick(TObject *Sender);
	void __fastcall PatQuickSrchEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall PatListEditImgClick(TObject *Sender);
	void __fastcall PatListDelImgClick(TObject *Sender);
	void __fastcall PatNomEditExit(TObject *Sender);
	void __fastcall PatSexComboSelect(TObject *Sender);
	void __fastcall PatConsultViewClick(TObject *Sender);
	void __fastcall PatCancelImgClick(TObject *Sender);
	void __fastcall PatDeleteImgClick(TObject *Sender);
	void __fastcall PatListViewDblClick(TObject *Sender);
	void __fastcall PatEditImgClick(TObject *Sender);
	void __fastcall PatValidateImgClick(TObject *Sender);
	void __fastcall PatListViewKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ConsListViewData(TObject *Sender, TListItem *Item);
	void __fastcall ConsListViewCustomDrawSubItem(TCustomListView *Sender, TListItem *Item,int SubItem, TCustomDrawState State, bool &DefaultDraw);
	void __fastcall ConsFirstImgClick(TObject *Sender);
	void __fastcall ConsLastImgClick(TObject *Sender);
	void __fastcall ConsFltCodeEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ConsFltNomEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ConsFltLblMouseEnter(TObject *Sender);
	void __fastcall ConsFltLblMouseLeave(TObject *Sender);
	void __fastcall ConsFltImgClick(TObject *Sender);
	void __fastcall ConsFltDateEdit1Enter(TObject *Sender);
	void __fastcall ConsFltDateEdit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ConsPatValidImgMouseEnter(TObject *Sender);
	void __fastcall ConsPatValidImgMouseLeave(TObject *Sender);
	void __fastcall ConsListAddImgMouseEnter(TObject *Sender);
	void __fastcall ConsListAddImgMouseLeave(TObject *Sender);
	void __fastcall ConsListViewDblClick(TObject *Sender);
	void __fastcall ConsListAddImgClick(TObject *Sender);
	void __fastcall ConsListEditImgClick(TObject *Sender);
	void __fastcall ConsListDelImgClick(TObject *Sender);
	void __fastcall ConsListViewKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ConsPatListViewClick(TObject *Sender);
    void __fastcall OdVaEdit1Enter(TObject *Sender);
	void __fastcall OdVaEdit1Exit(TObject *Sender);
	void __fastcall AudiogValidImgMouseEnter(TObject *Sender);
	void __fastcall AudiogValidImgMouseLeave(TObject *Sender);
	void __fastcall AudiogCancelImgClick(TObject *Sender);
	void __fastcall AudiogDelImgClick(TObject *Sender);
	void __fastcall AudiogEditImgClick(TObject *Sender);
	void __fastcall AudiogValidImgClick(TObject *Sender);
	void __fastcall AudiogAddGraphImgClick(TObject *Sender);
    void __fastcall OdRsEdit1Exit(TObject *Sender);
	void __fastcall OdPressEdit1Exit(TObject *Sender);
	void __fastcall TympValidImgMouseEnter(TObject *Sender);
	void __fastcall TympValidImgMouseLeave(TObject *Sender);
	void __fastcall AcceuilLblMouseEnter(TObject *Sender);
	void __fastcall AcceuilLblMouseLeave(TObject *Sender);
	void __fastcall TympCancelImgClick(TObject *Sender);
	void __fastcall TympDelImgClick(TObject *Sender);
	void __fastcall TympEditImgClick(TObject *Sender);
	void __fastcall TympValidImgClick(TObject *Sender);
	void __fastcall AvapEdit10Exit(TObject *Sender);
	void __fastcall AvocValidImgClick(TObject *Sender);
	void __fastcall AvocEditImgClick(TObject *Sender);
	void __fastcall AvocDelImgClick(TObject *Sender);
	void __fastcall AvocCancelImgClick(TObject *Sender);
	void __fastcall AvocViewImgClick(TObject *Sender);
	void __fastcall AvocAddGrphImgClick(TObject *Sender);
	void __fastcall AvocDelGrphImgClick(TObject *Sender);
	void __fastcall AvocValidImgMouseEnter(TObject *Sender);
	void __fastcall AvocValidImgMouseLeave(TObject *Sender);
	void __fastcall GainpValidImgMouseEnter(TObject *Sender);
	void __fastcall GainpValidImgMouseLeave(TObject *Sender);
	void __fastcall OdVoEdit1Exit(TObject *Sender);
	void __fastcall GainpValidImgClick(TObject *Sender);
	void __fastcall GainpEditImgClick(TObject *Sender);
	void __fastcall GainpDelImgClick(TObject *Sender);
	void __fastcall GainpCancelImgClick(TObject *Sender);
	void __fastcall GainpAddGrphImgClick(TObject *Sender);
	void __fastcall GainpChlChkClick(TObject *Sender);
	void __fastcall GainpOdChkClick(TObject *Sender);
	void __fastcall AvocChlChkClick(TObject *Sender);
	void __fastcall AvocOgChkClick(TObject *Sender);
	void __fastcall ConsPatValidImgClick(TObject *Sender);
	void __fastcall ConsPatEditImgClick(TObject *Sender);
	void __fastcall ConsPatDelImgClick(TObject *Sender);
	void __fastcall ConsPatCancelImgClick(TObject *Sender);
	void __fastcall TympViewImgClick(TObject *Sender);
	void __fastcall GainpViewImgClick(TObject *Sender);
	void __fastcall AudiogViewImgClick(TObject *Sender);
	void __fastcall AudiogListViewItemChecked(TObject *Sender, TListItem *Item);
	void __fastcall WeberEdit1Exit(TObject *Sender);
	void __fastcall ConsPatNameLblMouseEnter(TObject *Sender);
	void __fastcall ConsPatNameLblMouseLeave(TObject *Sender);
	void __fastcall ConsPatNameLblClick(TObject *Sender);
	void __fastcall OpNameLblMouseEnter(TObject *Sender);
	void __fastcall OpNameLblMouseLeave(TObject *Sender);
	void __fastcall OpNameLblClick(TObject *Sender);
	void __fastcall PatCancelImgMouseEnter(TObject *Sender);
	void __fastcall PatCancelImgMouseLeave(TObject *Sender);
	void __fastcall PatListDelImgMouseEnter(TObject *Sender);
	void __fastcall PatListDelImgMouseLeave(TObject *Sender);
	void __fastcall DemogLblMouseEnter(TObject *Sender);
	void __fastcall DemogLblMouseLeave(TObject *Sender);
	void __fastcall DemogLblClick(TObject *Sender);


private:	// User declarations

	t_listview_vtm_params vtm_params;

	void __fastcall initialize_session(void);
	void __fastcall release_session(void);

	void __fastcall HandleOperatorPage(void);

	void __fastcall HandleDoctorsPage(void);

	void __fastcall HandleInfosPage(void);

	bool __fastcall LoadMainPage(void);
	void __fastcall UnloadMainPage(void);

	bool __fastcall LoadPatientPage(void);

	bool __fastcall LoadPatientListPage(void);
	void __fastcall UnloadPatientListPage(void);

	bool __fastcall LoadConsultationListPage(void);
	void __fastcall UnloadConsultationListPage(void);

	void __fastcall CreateVtmBlocks(const unsigned_int blocks_count);
	void __fastcall LoadVtmBlocks(const bool patient_vtm_block);
	void __fastcall DeleteVtmBlocks(void);

	void __fastcall fill_old_consultations_treeview(TTreeView *treeview);

	void __fastcall LogOff();
	bool __fastcall LogIn();
	bool __fastcall Check_Credentials(UnicodeString login,UnicodeString password);

	bool __fastcall LoadStatistiquesPage(void);
	void __fastcall UnloadStatistiquesPage(void);

	void __fastcall HandleDemographicStatistics(void);
	void __fastcall HandleGeographicStatistics(void);
	void __fastcall HandleJobStatistics(void);
	void __fastcall HandleMedStatistics(void);
	void __fastcall HandleAudiogramsStatistics(void);
	void __fastcall HandleTympanogramsStatistics(void);
	void __fastcall HandleAvocStatistics(void);
	void __fastcall HandleGainpStatistics(void);

public:		// User declarations

	puint32 PatientPageMed_Ids;

	p_offsets_table PatientConsultationsTable;

	t_session_params session_params;

	bool patient_picture_loaded;

	t_warn_label_animation_params warn_label_animation;

	__fastcall TForm1(TComponent* Owner);

	void __fastcall Navigate(const int from,const int to);

	void __fastcall MailKeyPress(TObject *Sender,System::WideChar &Key);
	void __fastcall PhoneKeyPress(TObject *Sender, System::WideChar &Key);

	bool __fastcall MarkFaultyComponent(TObject *Sender);
	bool __fastcall unMarkFaultyComponent(TObject *Sender);

	void __fastcall load_unknown_person_picture(TImage *image,const bool female);

	bool __fastcall customize_picture(TImage *image,const int age,const bool male_gender);

	void __fastcall Consultation_OnChange_Event_Handler(const uint32 caller_engine_id,const uint32 record_id,const t_consultation_onchange_event_type ChangeEventType);
	void __fastcall Switch_Annuler_Retour_Button(const uint32 caller_engine_id,const bool edit_mode);


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
