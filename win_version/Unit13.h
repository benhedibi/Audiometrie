//---------------------------------------------------------------------------

#ifndef Unit13H
#define Unit13H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "QRCtrls.hpp"
#include "QuickRpt.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TAvocImpFrm : public TForm
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
	TQRLabel *QRLabel13;
	TQRLabel *QRLabel14;
	TQRLabel *QRLabel15;
	TQRLabel *QRLabel17;
	TQRLabel *QRLabel18;
	TQRLabel *QRLabel19;
	TQRLabel *OreilleLbl;
	TQRLabel *NatureLbl;
	TQRLabel *ControlLbl;
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
	TQRShape *QRShape3;
	TLabel *Label13;
	TLabel *Label11;
	TLabel *Label12;
	TQRShape *QRShape4;
	TQRImage *QRImage1;
	TQRImage *QRImage2;
	TQRImage *QRImage3;
	TQRLabel *QRLabel16;
	TQRLabel *QRLabel20;
	TQRLabel *SisaLbl;
	TQRLabel *MisaLbl;
	TQRLabel *TdsaLbl;
	TQRLabel *MiaaLbl;
	TQRLabel *SiaaLbl;
	TQRLabel *TdaaLbl;
	TQRLabel *QRLabel27;
	TQRLabel *QRLabel28;
	TQRLabel *QRLabel29;
	TQRLabel *QRLabel30;
	TQRLabel *QRLabel31;
	TQRLabel *QRLabel32;
	TQRLabel *QRLabel33;
	TQRLabel *DateAvoc;
	TQRLabel *QRLabel35;
	TQRLabel *QRLabel36;
	TQRLabel *QRLabel37;
	TQRLabel *QRLabel38;
private:	// User declarations
public:		// User declarations
	__fastcall TAvocImpFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAvocImpFrm *AvocImpFrm;
//---------------------------------------------------------------------------
#endif
