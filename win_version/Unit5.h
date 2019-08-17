//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TOpInfoFrm : public TForm
{
__published:	// IDE-managed Components
	TLabel *ValidLbl;
	TLabel *CancelLbl;
	TGroupBox *GroupBox1;
	TLabeledEdit *NomEdit;
	TLabeledEdit *Tel1Edit;
	TLabeledEdit *Tel2Edit;
	TLabeledEdit *MailEdit;
	TGroupBox *GroupBox2;
	TImage *BiomImg;
	TLabel *BiomLbl;
	TLabel *Label1;
	TLabel *PswLbl;
	void __fastcall BiomLblMouseEnter(TObject *Sender);
	void __fastcall BiomLblMouseLeave(TObject *Sender);
	void __fastcall BiomImgMouseEnter(TObject *Sender);
	void __fastcall BiomImgMouseLeave(TObject *Sender);
	void __fastcall CancelLblClick(TObject *Sender);
	void __fastcall ValidLblClick(TObject *Sender);
	void __fastcall BiomImgClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MailEditKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations

	bool edit_mode;

	__fastcall TOpInfoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOpInfoFrm *OpInfoFrm;
//---------------------------------------------------------------------------
#endif
