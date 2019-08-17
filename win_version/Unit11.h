//---------------------------------------------------------------------------

#ifndef Unit11H
#define Unit11H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "QRCtrls.hpp"
#include "QuickRpt.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGainpImpFrm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *QuickRep1;
	TQRBand *TitleBand1;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel2;
	TQRLabel *QRLabel3;
	TQRLabel *QRLabel4;
	TQRLabel *QRLabel5;
	TQRShape *QRShape1;
	TQRBand *PageFooterBand1;
	TQRLabel *QRLabel11;
	TQRMemo *QRMemo1;
	TQRBand *SummaryBand1;
	TQRLabel *QRLabel12;
	TQRImage *GainpImg;
	TQRLabel *OdDate1;
	TQRShape *OdShape1;
	TQRShape *OdShape2;
	TQRLabel *OdDate2;
	TQRLabel *OgDate1;
	TQRShape *OgShape1;
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
	TQRLabel *QRLabel13;
	TQRLabel *QRLabel14;
	TQRLabel *QRLabel15;
	TQRLabel *QRLabel16;
	TQRLabel *QRLabel17;
	TQRLabel *QRLabel18;
	TQRLabel *QRLabel19;
	TQRLabel *QRLabel20;
	TQRLabel *QRLabel21;
	TQRLabel *SeuilAuditionLbl;
	TQRLabel *SeuilProtLbl;
	TQRLabel *GpLbl;
	TQRLabel *DynLbl;
	TQRLabel *MclLbl;
	TQRLabel *OreilleLbl;
	TQRLabel *NatureLbl;
	TQRLabel *ProtLbl;
	TQRLabel *RefLbl;
	TQRLabel *QRLabel22;
	TQRLabel *QRLabel23;
private:	// User declarations
public:		// User declarations
	__fastcall TGainpImpFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGainpImpFrm *GainpImpFrm;
//---------------------------------------------------------------------------
#endif
