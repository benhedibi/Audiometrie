//---------------------------------------------------------------------------

#ifndef Unit9H
#define Unit9H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <QuickRpt.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "QRCtrls.hpp"
//---------------------------------------------------------------------------
class TTympImpFrm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *QuickRep1;
	TQRBand *TitleBand1;
	TQRBand *PageFooterBand1;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel2;
	TQRLabel *QRLabel3;
	TQRLabel *QRLabel4;
	TQRLabel *QRLabel5;
	TQRShape *QRShape1;
	TQRBand *SummaryBand1;
	TQRLabel *QRLabel11;
	TQRLabel *QRLabel12;
	TQRBand *QRBand1;
	TQRLabel *QRLabel7;
	TQRLabel *QRLabel6;
	TQRLabel *QRLabel8;
	TQRLabel *QRLabel9;
	TQRLabel *QRLabel10;
	TQRLabel *DateLbl;
	TQRLabel *NomLbl;
	TQRLabel *CodepLbl;
	TQRLabel *AdressLbl;
	TQRLabel *MedLbl;
	TQRShape *QRShape2;
	TQRMemo *QRMemo1;
	TQRImage *OgImg;
	TQRImage *OdImg;
	TQRLabel *OdDate1;
	TQRShape *OdShape1;
	TQRShape *OdShape2;
	TQRLabel *OdDate2;
	TQRLabel *OgDate1;
	TQRShape *OgShape1;
	TQRShape *OgShape2;
	TQRLabel *OgDate2;
	TQRLabel *QRLabel22;
	TQRLabel *QRLabel23;
	TQRLabel *QRLabel24;
	TQRLabel *QRLabel25;
	TQRLabel *QRLabel26;
	TQRLabel *QRLabel27;
	TQRLabel *OdRsLbl1;
	TQRLabel *OdRsLbl2;
	TQRLabel *OdRsLbl3;
	TQRLabel *OdRsLbl4;
	TQRLabel *QRLabel32;
	TQRLabel *QRLabel33;
	TQRLabel *OgRsLbl1;
	TQRLabel *OgRsLbl2;
	TQRLabel *QRLabel36;
	TQRLabel *OgRsLbl3;
	TQRLabel *OgRsLbl4;
	TQRLabel *QRLabel39;
private:	// User declarations
public:		// User declarations
	__fastcall TTympImpFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTympImpFrm *TympImpFrm;
//---------------------------------------------------------------------------
#endif
