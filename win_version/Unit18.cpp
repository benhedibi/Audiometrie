//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit18.h"

#include "common.hpp"

#include <lilly_io.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGeoFrm *GeoFrm;
//---------------------------------------------------------------------------
__fastcall TGeoFrm::TGeoFrm(TComponent* Owner) : TForm(Owner)
{
	PageControl1->ActivePageIndex = 0;

    return;
}
//---------------------------------------------------------------------------

void __fastcall TGeoFrm::Navigate(const int page_index)
{

	switch (page_index)
	{
	   case 0 : GlobalStats();
				break;

	   case 1 : Gouvernorats_Stats();
				break;

	   case 2 : Regions_Stats(t_nord);
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,false);
				break;
	}

	PageControl1->ActivePageIndex = page_index;

	return;
}

void __fastcall TGeoFrm::GlobalStats()
{
  TListItem *item;


	if ((!stat_table) || (!list))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	ListView1->Items->Clear();

	for (int i = 0; i < sizeof(stat_table->pays) / sizeof(stat_table->pays[0]); i++)
	{
	  if (stat_table->pays[i])
	  {
		item = ListView1->Items->Add();
		item->Caption = list->Strings[i];
		item->SubItems->Add(IntToStr((int)stat_table->pays[i]));
      }
	}

	for (int i = 0; i < sizeof(stat_table->continents) / sizeof(stat_table->continents[0]); i++)
	{
	  ListView2->Items->Item[i]->SubItems->Strings[0] = IntToStr((int)stat_table->continents[i]);
	}

	return;
}

void __fastcall TGeoFrm::Gouvernorats_Stats()
{
  PWCHAR gouvernorat_names[24] = {(PWCHAR)L"Ariana",(PWCHAR)L"Béja",(PWCHAR)L"Ben Arous",(PWCHAR)L"Bizerte",(PWCHAR)L"Gabès",(PWCHAR)L"Gafsa",(PWCHAR)L"Jendouba",
								  (PWCHAR)L"Kairouan",(PWCHAR)L"Kasserine",(PWCHAR)L"Kébili",(PWCHAR)L"Kef",(PWCHAR)L"Mahdia",(PWCHAR)L"Mannouba",(PWCHAR)L"Médenine",
								  (PWCHAR)L"Monastir",(PWCHAR)L"Nabeul",(PWCHAR)L"Sfax",(PWCHAR)L"Sidi Bouzid",(PWCHAR)L"Siliana",(PWCHAR)L"Sousse",(PWCHAR)L"Tataouine",
								  (PWCHAR)L"Tozeur",(PWCHAR)L"Tunis",(PWCHAR)L"Zaghouan"};


    if (!stat_table)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	for (int i = 0; i < this->ComponentCount; i++)
	{
	  if (Components[i]->ClassNameIs("TShape") == true)
	  {
		TShape *shape = dynamic_cast<TShape *>(Components[i]);
		shape->Hint = gouvernorat_names[shape->Tag];
        shape->Hint = shape->Hint + " | Hommes : " + IntToStr((int)stat_table->gouvernorats[shape->Tag].male_count) + " / Femmes : " + IntToStr((int)stat_table->gouvernorats[shape->Tag].female_count);
	  }
	}

	ArHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_ariana].male_count);
	ArFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_ariana].female_count);
	ArTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_ariana].count);

	BejHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_beja].male_count);
	BejFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_beja].female_count);
	BejTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_beja].count);

	BenHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_ben_arous].male_count);
	BenFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_ben_arous].female_count);
	BenTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_ben_arous].count);

	BizHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_bizerte].male_count);
	BizFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_bizerte].female_count);
	BizTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_bizerte].count);

	GabHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_gabes].male_count);
	GabFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_gabes].female_count);
	GabTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_gabes].count);

	GafHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_gafsa].male_count);
	GaFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_gafsa].female_count);
	GafTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_gafsa].count);

	JenHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_jendouba].male_count);
	JenFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_jendouba].female_count);
	JenTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_jendouba].count);

	KairHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kairouan].male_count);
	KairFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kairouan].female_count);
	KairTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kairouan].count);

	KassHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kasserine].male_count);
	KassFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kasserine].female_count);
	KassTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kasserine].count);

	KebHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kebili].male_count);
	KebFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kebili].female_count);
	KebTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kebili].count);

	KefHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kef].male_count);
	KeFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kef].female_count);
	KefTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_kef].count);

	MaHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_mahdia].male_count);
	MahFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_mahdia].female_count);
	MahTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_mahdia].count);

	ManHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_mannouba].male_count);
	ManFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_mannouba].female_count);
	ManTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_mannouba].count);

	MeHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_medenine].male_count);
	MedFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_medenine].female_count);
	MedTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_medenine].count);

	MonHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_monastir].male_count);
	MonFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_monastir].female_count);
	MonTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_monastir].count);

	NabHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_nabeul].male_count);
	NabFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_nabeul].female_count);
	NabeulTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_nabeul].count);

	SfaxHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sfax].male_count);
	SfaxFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sfax].female_count);
	SfaxTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sfax].count);

	SidHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sidi_bouzid].male_count);
	SidiFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sidi_bouzid].female_count);
	SidiTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sidi_bouzid].count);

	SilHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_siliana].male_count);
	SilFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_siliana].female_count);
	SilTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_siliana].count);

	SoussHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sousse].male_count);
	SoussFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sousse].female_count);
	SousseTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_sousse].count);

	TatHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tataouine].male_count);
	TatFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tataouine].female_count);
	TataTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tataouine].count);

	TozHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tozeur].male_count);
	TozFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tozeur].female_count);
	TozTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tozeur].count);

	TunHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tunis].male_count);
	TunFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tunis].female_count);
	TunTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_tunis].count);

	ZagHPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_zaghouan].male_count);
	ZagFPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_zaghouan].female_count);
	ZagTotPanel->Caption = IntToStr((int)stat_table->gouvernorats[t_zaghouan].count);

	return;

}

void __fastcall TGeoFrm::Regions_Stats(const t_tunisia_region_types region_type)
{
  int gouv_count;
  UnicodeString map_path;


    if (!stat_table)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	Image2->Picture = NULL;

	switch (region_type)
	{
		 case t_nord : gouv_count = 10;
					   break;

		case t_sahel : gouv_count = 3;
					   break;

	  case t_cap_bon : gouv_count = 1;
					   break;

	   case t_centre : gouv_count = 5;
					   break;

		  case t_sud : gouv_count = 4;
					   break;

			 default : report_event(error_code_to_string(API_ERROR),mtError,false);
					   return;
	}

	GouvPanel->Caption = IntToStr((int)gouv_count);

	HPanel->Caption = IntToStr((int)stat_table->regions[(unsigned_int)region_type].male_count);
	FPanel->Caption = IntToStr((int)stat_table->regions[(unsigned_int)region_type].female_count);
	TotalPanel->Caption = IntToStr((int)stat_table->regions[(unsigned_int)region_type].count);

	map_path = IntToStr((int)region_type) + ".map";

	if (!lilly_io_file_exists((puchar)map_path.c_str()))
	{
	  map_path = "Un composant du logiciel est introuvable ! Veuillez re-installer le logiciel pour corriger le problème.\n\r\n\r";
	  map_path = map_path + "Si le problème persiste encore, veuillez alors contacter votre support technique.";
	  report_event(map_path,mtError,false);
	}
	else if (!load_image(Image2,map_path))
	{
	  report_event("Une erreur est survenue lors du chargement du composant [TUNISIE_MAP] ! Veuillez contacter votre support technique",mtError,false);
	}

    return;
}

void __fastcall TGeoFrm::Label1MouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->GlowSize = 1;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGeoFrm::Label1MouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->GlowSize = 0;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGeoFrm::Label1Click(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	Navigate(label->Tag);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TGeoFrm::NordRadioClick(TObject *Sender)
{
  TRadioButton *radio = static_cast<TRadioButton *>(Sender);


	Regions_Stats((t_tunisia_region_types)radio->Tag);

    return;
}
//---------------------------------------------------------------------------

