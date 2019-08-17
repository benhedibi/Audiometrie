//---------------------------------------------------------------------------

#ifndef Unit16H
#define Unit16H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TLoginFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *ConnectLbl;
	TImage *Image1;
	TLabel *Label3;
	TEdit *LoginEdit;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *PassEdit;
	TImage *Image2;
	TLabel *Label6;
	TPanel *Panel2;
	TLabel *CancelLbl;
	void __fastcall CancelLblMouseEnter(TObject *Sender);
	void __fastcall CancelLblMouseLeave(TObject *Sender);
	void __fastcall CancelLblClick(TObject *Sender);
	void __fastcall ConnectLblClick(TObject *Sender);
	void __fastcall Label6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations

    int operator_id;
	__fastcall TLoginFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoginFrm *LoginFrm;
//---------------------------------------------------------------------------
#endif
