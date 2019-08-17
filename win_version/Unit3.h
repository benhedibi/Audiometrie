//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMedInfoFrm : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *NomEdit;
	TGroupBox *GroupBox1;
	TComboBox *PaysCombo;
	TComboBox *GouvCombo;
	TLabeledEdit *Tel1Edit;
	TLabeledEdit *Tel2Edit;
	TLabeledEdit *FaxEdit;
	TLabeledEdit *MailEdit;
	TLabel *Label1;
	TLabel *Label2;
	TRadioButton *PriveRadio;
	TRadioButton *CliniqueRadio;
	TRadioButton *HopitalRadio;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall Label4MouseEnter(TObject *Sender);
	void __fastcall Label4MouseLeave(TObject *Sender);
	void __fastcall Label4Click(TObject *Sender);
	void __fastcall Label3Click(TObject *Sender);
	void __fastcall PaysComboSelect(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MailEditKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations

    bool edit_mode;
	__fastcall TMedInfoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMedInfoFrm *MedInfoFrm;
//---------------------------------------------------------------------------
#endif
