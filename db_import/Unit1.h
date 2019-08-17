//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *OpSrcLbl;
	TOpenDialog *OpenDialog1;
	TButton *Button1;
	TLabel *Label1;
	TLabel *OpstatLbl;
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *OpPage;
	TTabSheet *MedPage;
	TTabSheet *ConsulPage;
	TTabSheet *RefGpPage;
	TTabSheet *PatPage;
	TTabSheet *AudiogPage;
	TTabSheet *TympanoPage;
	TTabSheet *AudiovPage;
	TTabSheet *GpPage;
	TGroupBox *GroupBox9;
	TLabeledEdit *DocSrcEdit;
	TButton *Button13;
	TLabel *Label17;
	TLabel *DocStatLbl;
	TLabeledEdit *LabeledEdit2;
	TButton *Button2;
	TLabel *Label3;
	TLabel *ConsStatLbl;
	TLabeledEdit *RefGainpEdit;
	TButton *Button14;
	TLabel *Label19;
	TLabel *JobStatLbl;
	TLabeledEdit *PatSrcEdit;
	TButton *Button7;
	TButton *Button8;
	TLabeledEdit *PatDestEdit;
	TLabel *PatStatLbl;
	TLabel *Label10;
	TLabeledEdit *AudiogSrcEdit;
	TButton *Button15;
	TButton *Button16;
	TLabeledEdit *AudiogDestEdit;
	TLabel *AudiogStatLbl;
	TLabel *Label12;
	TLabeledEdit *TympanoSrcEdit;
	TButton *Button17;
	TButton *Button18;
	TLabeledEdit *TympanoDestEdit;
	TLabel *TympanoStatLbl;
	TLabel *Label22;
	TLabeledEdit *AvSrcEdit;
	TButton *Button19;
	TButton *Button20;
	TLabeledEdit *AvDestEdit;
	TLabel *AvStatLbl;
	TLabel *Label24;
	TLabeledEdit *GainpSrcEdit;
	TButton *Button21;
	TButton *Button22;
	TLabeledEdit *GainpDestEdit;
	TLabel *GainpStatLbl;
	TLabel *Label26;
	TGroupBox *GroupBox1;
	TImage *Image1;
	TLabeledEdit *SessionIDLbl;
	TCheckBox *CryptChk;
	TCheckBox *CompressChk;
	TCheckBox *CrcChk;
	TCheckBox *SupUserChk;
	TCheckBox *SessionLockChk;
	TCheckBox *MacLockChk;
	TLabel *Label6;
	TButton *Button4;
	TLabeledEdit *OpDestLbl;
	TButton *Button5;
	TButton *Button6;
	TLabeledEdit *ConsDestEdit;
	TButton *Button9;
	TButton *Button10;
	TLabeledEdit *DocDestEdit;
	TButton *Button11;
	TButton *Button12;
	TButton *Button23;
	TLabeledEdit *JobEdit;
	TButton *Button24;
	TButton *Button25;
	TButton *Button26;
	TComboBox *ComboBox1;
	TSaveDialog *SaveDialog1;
	TButton *Button27;
	TButton *Button28;
	TButton *Button29;
	TButton *Button30;
	TTabSheet *TabSheet1;
	TLabel *Label2;
	TLabel *OrphPatStatLbl;
	TButton *Button32;
	TMemo *Memo1;
	TTabSheet *TabSheet2;
	TEdit *SortSrcEdit;
	TButton *Button31;
	TEdit *SortDestEdit;
	TButton *Button33;
	TButton *Button34;
	TLabel *Label4;
	TLabel *SortStateLbl;
	TButton *Button3;
	TLabeledEdit *DbPathEdit;
	TCheckBox *ReadOnlyChk;
	TCheckBox *IndexChk;
	TButton *Button35;
	TComboBox *DbTypeCombo;
	TLabel *Label5;
	TCheckBox *CrashChk;
	TTabSheet *TabSheet3;
	TEdit *LastConsEdit;
	TButton *Button36;
	TLabel *LastConsStatLbl;
	TLabel *Label8;
	TButton *Button37;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button24Click(TObject *Sender);
	void __fastcall Button26Click(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button30Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button32Click(TObject *Sender);
	void __fastcall Button31Click(TObject *Sender);
	void __fastcall Button33Click(TObject *Sender);
	void __fastcall Button34Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button35Click(TObject *Sender);
	void __fastcall Button36Click(TObject *Sender);
	void __fastcall Button37Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
    void __fastcall  report_event(const UnicodeString event,const TMsgDlgType dlg_type,const boolean fatal);
	__fastcall TForm1(TComponent* Owner);

	
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
