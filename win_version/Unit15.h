//---------------------------------------------------------------------------

#ifndef Unit15H
#define Unit15H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "QRCtrls.hpp"
#include "QuickRpt.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAudiogImpFrm : public TForm
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
	TQRImage *OdImg;
	TQRLabel *OdDate1;
	TQRShape *OdShape1;
	TQRShape *OdShape2;
	TQRLabel *OdDate2;
	TQRLabel *DateTemoin;
	TQRShape *AncienVaShape;
	TQRLabel *OreilleLbl;
	TQRShape *QRShape3;
	TQRLabel *DateAudiog;
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
	TQRImage *OgImg;
	TQRImage *WeberImg1;
	TQRImage *WeberImg2;
	TQRImage *WeberImg3;
	TQRImage *WeberImg4;
	TQRImage *WeberImg5;
	TQRShape *QRShape4;
	TQRLabel *QRLabel13;
	TQRLabel *QRLabel14;
	TQRLabel *QRLabel15;
	TQRLabel *QRLabel16;
	TQRLabel *QRLabel17;
	TQRLabel *QRLabel18;
private:	// User declarations
public:		// User declarations
	__fastcall TAudiogImpFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAudiogImpFrm *AudiogImpFrm;
//---------------------------------------------------------------------------
#endif
