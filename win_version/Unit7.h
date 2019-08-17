//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TInfosFrm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TTreeView *TreeView1;
	TLabel *Label4;
	TLabel *VersionLbl;
	TPanel *Panel1;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *LicenseUsrLbl;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *LicenseTypeLbl;
	TLabel *Label17;
	TLabel *SyncLbl;
	TLabel *Label19;
	TLabel *UsrCountLbl;
	TLabel *Label21;
	TLabel *PatCountLbl;
	TLabel *Label23;
	TLabel *ConsultCountLbl;
	TLabel *Label25;
	TLabel *DoctorCountLbl;
private:	// User declarations
public:		// User declarations
	__fastcall TInfosFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInfosFrm *InfosFrm;
//---------------------------------------------------------------------------
#endif
