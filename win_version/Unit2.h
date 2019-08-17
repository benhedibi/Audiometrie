//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

#include <lilly_db2.h>
#include "common.hpp"
#include <Vcl.Menus.hpp>

//---------------------------------------------------------------------------
class TMedListFrm : public TForm
{
__published:	// IDE-managed Components
	TListView *ListView1;
	TLabel *Label1;
	TImage *AddImg;
	TLabel *AddLbl;
	TImage *EditImg;
	TLabel *EditLbl;
	TLabel *DelLbl;
	TImage *DelImg;
	TImage *Image4;
	TPopupMenu *PopupMenu1;
	TMenuItem *Rechercher1;
	void __fastcall DelLblMouseEnter(TObject *Sender);
	void __fastcall DelLblMouseLeave(TObject *Sender);
	void __fastcall DelImgClick(TObject *Sender);
	void __fastcall EditImgClick(TObject *Sender);
	void __fastcall AddImgClick(TObject *Sender);
	void __fastcall DelImgMouseEnter(TObject *Sender);
	void __fastcall DelImgMouseLeave(TObject *Sender);
	void __fastcall EditImgMouseEnter(TObject *Sender);
	void __fastcall EditImgMouseLeave(TObject *Sender);
	void __fastcall AddImgMouseEnter(TObject *Sender);
	void __fastcall AddImgMouseLeave(TObject *Sender);
	void __fastcall ListView1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ListView1DblClick(TObject *Sender);

private:	// User declarations
public:		// User declarations

	p_engine_entry med_entry,consult_entry;
	p_session_manager_path gouv_path;
    p_session_manager_path pays_path;
	bool data_updated;
	__fastcall TMedListFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMedListFrm *MedListFrm;
//---------------------------------------------------------------------------
#endif
