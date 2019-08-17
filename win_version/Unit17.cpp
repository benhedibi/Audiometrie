//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit17.h"

#include "common.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.TeePyramid"
#pragma link "VCLTee.TeeDoubleHorizBar"
#pragma link "VCLTee.TeeSubChart"
#pragma resource "*.dfm"
TDemoStatFrm *DemoStatFrm;

//---------------------------------------------------------------------------
__fastcall TDemoStatFrm::TDemoStatFrm(TComponent* Owner) : TForm(Owner)
{
	PageControl1->ActivePageIndex = 0;

    return;
}

//---------------------------------------------------------------------------

void __fastcall TDemoStatFrm::Label21MouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->GlowSize = 1;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TDemoStatFrm::Label21MouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->GlowSize = 0;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TDemoStatFrm::Navigate(const int page_index)
{

	switch (page_index)
	{
	   case 0 : FullStats(RadioButton1->Checked == true);
				break;

	   case 1 : Pourcentage(false);
				break;

	   case 2 : Pyramid(false);
				break;

	   case 3 : PariteSexes(true,t_enfant);
				break;

	   case 4 : Cross_Stats();
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,false);
				break;
	}

	PageControl1->ActivePageIndex = page_index;

	return;
}

void __fastcall TDemoStatFrm::FullStats(const boolean current_age)
{
  p_demographic_stat_record stat_record;
  unsigned_int enfants_m,enfants_f,adultes_m,adultes_f,vieux_m,vieux_f,max_axis;


    if (!stat_table)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	if (current_age)
	{
	  stat_record = (p_demographic_stat_record)&stat_table->current_age_records;
	}
	else stat_record = (p_demographic_stat_record)&stat_table->first_consult_age_records;

	enfants_m = stat_record[t_nourrisson].male_count + stat_record[t_enfant].male_count + stat_record[t_adolescent].male_count;
	enfants_f = stat_record[t_nourrisson].female_count + stat_record[t_enfant].female_count + stat_record[t_adolescent].female_count;

	max_axis = MACRO_MAX_VALUE(enfants_m,enfants_f);

	adultes_m = stat_record[t_jeune].male_count + stat_record[t_adulte].male_count;

	max_axis = MACRO_MAX_VALUE(adultes_m,max_axis);

	adultes_f = stat_record[t_jeune].female_count + stat_record[t_adulte].female_count;

	max_axis = MACRO_MAX_VALUE(adultes_f,max_axis);

	vieux_m = stat_record[t_cinquantenaire].male_count + stat_record[t_vieux].male_count;

	max_axis = MACRO_MAX_VALUE(vieux_m,max_axis);

	vieux_f = stat_record[t_cinquantenaire].female_count + stat_record[t_vieux].female_count;

	max_axis = MACRO_MAX_VALUE(vieux_f,max_axis);

	Chart1->Series[0]->Clear();

	Chart1->Axes->Left->Maximum = max_axis + (max_axis / 4);

	Chart1->Series[0]->AddXY(1,enfants_m,"12%",clHotLight);
	Chart1->Series[0]->AddXY(2,enfants_f,"12%",clFuchsia);
	Chart1->Series[0]->AddXY(3,adultes_m,"12%",clHighlight);
	Chart1->Series[0]->AddXY(4,adultes_f,"12%",clFuchsia);
	Chart1->Series[0]->AddXY(5,vieux_m,"12%",clHighlight);
	Chart1->Series[0]->AddXY(6,vieux_f,"12%",clFuchsia);

	ChildmLbl->Caption = IntToStr((int)(stat_record[t_nourrisson].male_count + stat_record[t_enfant].male_count));
	ChildfLbl->Caption = IntToStr((int)(stat_record[t_nourrisson].female_count + stat_record[t_enfant].female_count));

	AdomLbl->Caption = IntToStr((int)(stat_record[t_adolescent].male_count));
	AdofLbl->Caption = IntToStr((int)(stat_record[t_adolescent].female_count));

	JeunemLbl->Caption = IntToStr((int)(stat_record[t_jeune].male_count));
	JeunefLbl->Caption = IntToStr((int)(stat_record[t_jeune].female_count));

	AdultmLbl->Caption = IntToStr((int)(stat_record[t_adulte].male_count));
	AdultfLbl->Caption = IntToStr((int)(stat_record[t_adulte].female_count));

	CinquantmLbl->Caption = IntToStr((int)(stat_record[t_cinquantenaire].male_count));
	CinquantfLbl->Caption = IntToStr((int)(stat_record[t_cinquantenaire].female_count));

	PamLbl->Caption = IntToStr((int)(stat_record[t_vieux].male_count));
	PafLbl->Caption = IntToStr((int)(stat_record[t_vieux].female_count));

	return;

}

void __fastcall TDemoStatFrm::Pourcentage(const boolean current_age)
{
  p_demographic_stat_record stat_record;
  unsigned_int enfants_m,enfants_f,enfants_t,adolescents_m,adolescents_f,adolescents_t,jeunes_m,jeunes_f,jeunes_t,adultes_m,adultes_f,adultes_t,
  cinquante_m,cinquante_f,cinquante_t,vieux_m,vieux_f,vieux_t;


	if (!stat_table)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	if (current_age)
	{
	  stat_record = (p_demographic_stat_record)&stat_table->current_age_records;
	}
	else stat_record = (p_demographic_stat_record)&stat_table->first_consult_age_records;

	if (this->PercenthChk->State == cbChecked)
	{
	  enfants_m = stat_record[t_nourrisson].male_count + stat_record[t_enfant].male_count;
	  adolescents_m = stat_record[t_adolescent].male_count;
	  jeunes_m = stat_record[t_jeune].male_count;
	  adultes_m = stat_record[t_adulte].male_count;
	  cinquante_m = stat_record[t_cinquantenaire].male_count;
	  vieux_m = stat_record[t_vieux].male_count;
	}
	else
	{
	  enfants_m = 0;
	  adolescents_m = 0;
	  jeunes_m = 0;
	  adultes_m = 0;
	  cinquante_m = 0;
	  vieux_m = 0;
	}

	if (this->PercentfChk->State == cbChecked)
	{
	  enfants_f = stat_record[t_nourrisson].female_count + stat_record[t_enfant].female_count;
	  adolescents_f = stat_record[t_adolescent].female_count;
	  jeunes_f = stat_record[t_jeune].female_count;
	  adultes_f = stat_record[t_adulte].female_count;
	  cinquante_f = stat_record[t_cinquantenaire].female_count;
	  vieux_f = stat_record[t_vieux].female_count;
	}
	else
	{
	  enfants_f = 0;
	  adolescents_f = 0;
	  jeunes_f = 0;
	  adultes_f = 0;
	  cinquante_f = 0;
	  vieux_f = 0;
	}

	enfants_t = enfants_m + enfants_f;
	adolescents_t = adolescents_m + adolescents_f;
	jeunes_t = jeunes_m + jeunes_f;
	adultes_t = adultes_m + adultes_f;
	cinquante_t = cinquante_m + cinquante_f;
	vieux_t = vieux_m + vieux_f;

	Chart2->Series[0]->Clear();

	Chart2->Series[0]->AddY(enfants_t,"Enfants");
	Chart2->Series[0]->AddY(adolescents_t,"Adolescents");
	Chart2->Series[0]->AddY(jeunes_t,"Jeunes");
	Chart2->Series[0]->AddY(adultes_t,"Adultes");
	Chart2->Series[0]->AddY(cinquante_t,"50 à 60 ans");
	Chart2->Series[0]->AddY(vieux_t,"Pers.Agées");

	return;
}

void __fastcall TDemoStatFrm::Pyramid(const boolean current_age)
{
  unsigned_int max_axis;
  TDoubleHorizBarSeries *serie;


	if (!stat_table)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	max_axis = 0;

	for (int i = 0; i < sizeof(stat_table->pyramide_demographique) / sizeof(stat_table->pyramide_demographique[0]); i++)
	{
	  max_axis = MACRO_MAX_VALUE(max_axis,MACRO_MAX_VALUE(stat_table->pyramide_demographique[i].male_count,stat_table->pyramide_demographique[i].female_count));
	}

	if (!max_axis)
	{
	  report_event("Une erreur indéfinie est survenue au niveau du [STAT_TABLE/PYRAMIDE] ! Veuillez contacter votre support technique",mtError,false);
	  return;
    }

	max_axis += (max_axis / 8);

	Chart3->LeftAxis->Maximum = sizeof(stat_table->pyramide_demographique) / sizeof(stat_table->pyramide_demographique[0]);

	Chart3->BottomAxis->Maximum = max_axis;

	serie = (TDoubleHorizBarSeries *)Chart3->Series[0];

	serie->Clear();

	serie->LeftChart()->Series[0]->Clear();

	for (int i = 0; i < sizeof(stat_table->pyramide_demographique) / sizeof(stat_table->pyramide_demographique[0]); i++)
	{
	  serie->AddX(stat_table->pyramide_demographique[i].female_count);
	  serie->LeftChart()->Series[0]->AddX(stat_table->pyramide_demographique[i].male_count);
	}

	return;
}

void __fastcall TDemoStatFrm::PariteSexes(const boolean current_age,const t_age_category_type age_category)
{
  p_demographic_stat_record stat_record;
  unsigned_int total_m,total_f;


	if (!stat_table)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	if (current_age)
	{
	  stat_record = (p_demographic_stat_record)&stat_table->current_age_records;
	}
	else stat_record = (p_demographic_stat_record)&stat_table->first_consult_age_records;

	total_m = stat_record[age_category].male_count;
	total_f = stat_record[age_category].female_count;

	if (age_category == t_enfant)
	{
	  total_m += stat_record[t_nourrisson].male_count;
	  total_f += stat_record[t_nourrisson].female_count;
	}

	Chart4->Series[0]->Clear();

	Chart4->Series[0]->AddY(total_m,"Hommes",clBlue);
	Chart4->Series[0]->AddY(total_f,"Femmes",clFuchsia);

	return;
}

void __fastcall TDemoStatFrm::Cross_Stats()
{
  float total_male_percent,total_female_percent;


	if (!stat_table)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,false);
	  return;
	}

	PatCntLbl->Caption = IntToStr((int)(stat_table->total_males + stat_table->total_females));

	{
	  unsigned_int total = stat_table->total_males + stat_table->total_females;

	  total_male_percent = ((float)stat_table->total_males / (float)total) * 100;
	  total_female_percent = ((float)stat_table->total_females / (float)total) * 100;
	}

	MaleCntLbl->Caption = IntToStr((int)stat_table->total_males) + " (" + FloatToStrF((double)total_male_percent,ffGeneral,3,2) + "%)";

	FemaleCntLbl->Caption = IntToStr((int)stat_table->total_females) + " (" + FloatToStrF((double)total_female_percent,ffGeneral,3,2) + "%)";

	EquityAgeLbl->Caption = IntToStr((int)stat_table->min_age_parity.age);

	switch (stat_table->min_age_parity.age_category)
	{
		  case t_nourrisson :
			  case t_enfant : EquityCatLbl->Caption = "Enfants";
							  break;

		  case t_adolescent : EquityCatLbl->Caption = "Adolescents";
							  break;

			   case t_jeune : EquityCatLbl->Caption = "Jeunes";
							  break;

			  case t_adulte : EquityCatLbl->Caption = "Adultes";
							  break;

	  case t_cinquantenaire : EquityCatLbl->Caption = "Cinquantenaires";
							  break;

			   case t_vieux : EquityCatLbl->Caption = "Personnes agées";
							  break;

					default : EquityCatLbl->Caption = "Erreur / Indéfinie !";
							  break;
	}

	EquityCatLbl->Caption = EquityCatLbl->Caption + " (H : " + FloatToStrF((double)stat_table->min_age_parity.pourcentage_hommes,ffGeneral,4,2) + "% / F : " + FloatToStrF((double)stat_table->min_age_parity.pourcentage_femmes,ffGeneral,4,2) + "%)";

	NoEquityAgeLbl->Caption = IntToStr((int)stat_table->max_age_parity.age);

	switch (stat_table->max_age_parity.age_category)
	{
		  case t_nourrisson :
			  case t_enfant : NoEquityCatLbl->Caption = "Enfants";
							  break;

		  case t_adolescent : NoEquityCatLbl->Caption = "Adolescents";
							  break;

			   case t_jeune : NoEquityCatLbl->Caption = "Jeunes";
							  break;

			  case t_adulte : NoEquityCatLbl->Caption = "Adultes";
							  break;

	  case t_cinquantenaire : NoEquityCatLbl->Caption = "Cinquantenaires";
							  break;

			   case t_vieux : NoEquityCatLbl->Caption = "Personnes agées";
							  break;

					default : NoEquityCatLbl->Caption = "Erreur / Indéfinie !";
							  break;
	}

	NoEquityCatLbl->Caption = NoEquityCatLbl->Caption + " (H : " + FloatToStrF((double)stat_table->max_age_parity.pourcentage_hommes,ffGeneral,4,2) + "% / F : " + FloatToStrF((double)stat_table->max_age_parity.pourcentage_femmes,ffGeneral,4,2) + "%)";

	for (int i = 0; i < sizeof(stat_table->first_consult_top_10_ages) / sizeof(stat_table->first_consult_top_10_ages[0]); i++)
	{
	  TListItem *item;

	  if (!stat_table->first_consult_top_10_ages[i].count) break;

	  item = ListView1->Items->Add();

	  item->SubItems->Add(IntToStr((int)stat_table->first_consult_top_10_ages[i].age) + " ans");
	  item->SubItems->Add(IntToStr((int)stat_table->first_consult_top_10_ages[i].count) + " fois");

	}

	return;
}

void __fastcall TDemoStatFrm::RadioButton1Click(TObject *Sender)
{
  TRadioButton *button = static_cast<TRadioButton *>(Sender);

	FullStats((button->Tag == 0));

	return;
}

//---------------------------------------------------------------------------

void __fastcall TDemoStatFrm::PercentFirstConsultRadioClick(TObject *Sender)
{
  TRadioButton *button = static_cast<TRadioButton *>(Sender);

	Pourcentage((button->Tag == 1));

	return;
}

//---------------------------------------------------------------------------

void __fastcall TDemoStatFrm::Label1Click(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	Navigate(label->Tag);

	return;

}

//---------------------------------------------------------------------------


void __fastcall TDemoStatFrm::PariteFirstConsultRadioClick(TObject *Sender)
{
  TRadioButton *radio = static_cast<TRadioButton *>(Sender);
  int modus_operandi = 0;
  t_age_category_type age_category = t_nourrisson;
  bool current_age;


	switch (radio->Tag)
	{
	   case 0 : modus_operandi = 1;
				break;

	   case 1 : modus_operandi = 2;
				break;

	   case 2 : age_category = t_enfant;
				break;

	   case 3 : age_category = t_adolescent;
				break;

	   case 4 : age_category = t_jeune;
				break;

	   case 5 : age_category = t_adulte;
				break;

	   case 6 : age_category = t_cinquantenaire;
				break;

	   case 7 : age_category = t_vieux;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,false);
				return;
	}

	if (modus_operandi > 0)
	{
	  current_age = (modus_operandi > 1);
	}
	else
	{
	  current_age = PariteCurrentAgeRadio->Checked;
	}

	if (age_category == t_nourrisson)
	{
	  if (PariteEnfantRadio->Checked)
	  {
		age_category = t_enfant;
	  }
	  else if (PariteAdoRadio->Checked)
	  {
		age_category = t_adolescent;
	  }
	  else if (PariteJeuneRadio->Checked)
	  {
		age_category = t_jeune;
	  }
	  else if (PariteAdultRadio->Checked)
	  {
		age_category = t_adulte;
	  }
	  else if (Parite50Radio->Checked)
	  {
		age_category = t_cinquantenaire;
	  }
	  else age_category = t_vieux;
    }

	PariteSexes(current_age,age_category);

    return;
}
//---------------------------------------------------------------------------

