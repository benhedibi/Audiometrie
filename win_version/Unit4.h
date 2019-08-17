//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Menus.hpp>

#include <lilly_db2.h>
#include "common.hpp"

//---------------------------------------------------------------------------
class TOpListFrm : public TForm
{
__published:	// IDE-managed Components
	TListView *ListView1;
	TImage *Image4;
	TImage *AddImg;
	TLabel *AddLbl;
	TImage *EditImg;
	TLabel *EditLbl;
	TImage *DelImg;
	TLabel *DelLbl;
	TLabel *Label1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Rechercher1;
	TMenuItem *Suivant1;
	void __fastcall AddLblMouseEnter(TObject *Sender);
	void __fastcall AddLblMouseLeave(TObject *Sender);
	void __fastcall DelImgMouseEnter(TObject *Sender);
	void __fastcall DelImgMouseLeave(TObject *Sender);
	void __fastcall EditImgMouseEnter(TObject *Sender);
	void __fastcall EditImgMouseLeave(TObject *Sender);
	void __fastcall AddImgMouseEnter(TObject *Sender);
	void __fastcall AddImgMouseLeave(TObject *Sender);
	void __fastcall AddImgClick(TObject *Sender);
	void __fastcall EditImgClick(TObject *Sender);
	void __fastcall DelImgClick(TObject *Sender);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall ListView1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Rechercher1Click(TObject *Sender);
	void __fastcall Suivant1Click(TObject *Sender);

private:	// User declarations
    int current_item_index;
	UnicodeString srch;
public:		// User declarations

	p_engine_entry op_entry,consult_entry;

	__fastcall TOpListFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOpListFrm *OpListFrm;
//---------------------------------------------------------------------------
#endif
