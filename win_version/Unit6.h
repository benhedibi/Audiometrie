//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TSplshFrm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *Label1;
	TLabel *StatusLbl;
	TPanel *Panel1;
private:	// User declarations
public:		// User declarations
	__fastcall TSplshFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSplshFrm *SplshFrm;
//---------------------------------------------------------------------------
#endif
