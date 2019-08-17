//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <lilly_io.h>
#include <lilly_db_import.h>
#include <operators_engine.h>
#include <patients_engine.h>
#include <doctors_engine.h>
#include <audiograms_engine.h>
#include <audiovocs_engine.h>
#include <consultations_engine.h>
#include <gainp_engine.h>
#include <tympano_engine.h>
#include <lilly_session_manager.h>
#include <patients_import.h>
#include <audiog_import.h>
#include <tympano_import.h>
#include <gp_import.h>
#include <audiov_import.h>

#include <lilly_utils.h>

#include <cmnfnc.h>

#include <db_signatures.h>

#include "Unit1.h"

#include <system.strutils.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

p_lilly_db_session_manager session_manager;
TStringList *gainp_proth_refs,*orphan_codep,*femmes,*bad_gouv;

UnicodeString operators_db_path,doctors_db_path,patients_db_path,consultations_db_path,audiograms_db_path,tympanograms_db_path,gainp_db_path,audiovocs_db_path;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


UnicodeString __fastcall job_serializer(UnicodeString job)
{
	// a long journey mother fucker LOL


	job = job.LowerCase();

	if ((job == "") || (job == ".") || (job == "1975") || (job == "1976") || (job == "/"))
	{
	  job = "non spécifié";
	  return job;
	}

	if ((job == "se") || (job == "se;"))
	{
	  job = "sans emploi";
	  return job;
	}
	
	if (job.Pos("administrareur") > 0)
	{
	  job = ReplaceText(job,"administrareur","administrateur");
	  return job;
	}
	else if (job.Pos("adminitrateur") > 0)
	{
      job = ReplaceText(job,"adminitrateur","administrateur");
	  return job;
    }
	else if (job.Pos("adminstrateur") > 0)
	{
	  job = ReplaceText(job,"adminstrateur","administrateur");
	  return job;
	}
	else if (job.Pos("admnistrateur") > 0)
	{
      job = ReplaceText(job,"admnistrateur","administrateur");
	  return job;
	}

	if ((job == "agent banq") || (job == "agent banque") || (job == "banque") || (job == "bauque") || (job == "bad") || (job.Pos("chef d agence") > 0) ||
	(job.Pos("biat") > 0) || (job.Pos("bna") > 0) || (job.Pos("stb") > 0) || (job.Pos("uib") > 0) || (job.Pos("ubci") > 0))
	{
	  job = "banquier";
	  return job;
	}

	if (job == "aide compt")
	{
	  job = "aide comptable";
	  return job;
	}

	if (job == "analyste fin")
	{
	  job = "analyste financier";
	  return job;
    }

	if (job == "argheologue")
	{
	  job = "archeologue";
	  return job;
	}

	if ((job.Pos("arme") > 0) || (job == "def nat") || (job == "militaire"))
	{
	  job = "ministère de la défense";
	  return job;
	}

	if (job == "artisan")
	{
	  job = "artisant";
	  return job;
	}

	if ((job == "assis direc fin") || (job == "assistante de direc"))
	{
	  job = "assistante de direction";
	  return job;
	}

	if (job.Pos("asistante") > 0)
	{
	  job = ReplaceText(job,"asistante","assistante");
	  return job;
	}
	else if (job.Pos("asistant") > 0)
	{
	  job = ReplaceText(job,"asistant","assistant");
	  return job;
	}

	if ((job == "assurance") || (job == "star"))
	{	
	  job = "assurances";
	  return job;
	}

	if (job == "avoct")
	{
	  job = "avocat";
	  return job;
	}
	
	if (job.Pos("bct") > 0)
	{
	  job = "banque centrale";
	  return job;
	}

	if (job.Pos("bibliothequaire") > 0)
	{
	  job = "bibliothécaire";
	  return job;
	}

	if (job == "cadre s")
	{
	  job = "cadre";
	  return job;
	}
			
	if (job.Pos("taxi") > 0)
	{
	  job = "taxiste";
	  return job;
	}

	if (job.Pos("chaufeur") > 0)
	{
	  job = ReplaceText(job,"chaufeur","chauffeur");
	  return job;
	}
	else if (job.Pos("cjhauffeur") > 0)
	{
	  job = ReplaceText(job,"cjhauffeur","chauffeur");
	  return job;
	}
	
	if ((job.Pos("chaumeur") > 0) || (job.Pos("chomeur") > 0) || (job.Pos("chômeur") > 0))
	{
	  job = "sans emploi";
	  return job;
	}

	if ((job.Pos("chef de service") > 0) || (job.Pos("chef service") > 0))
	{
	  job = "chef de service";
	  return job;
	}

	if ((job.Pos("clinique") > 0) || (job.Pos("clinic") > 0))
	{
	  job = "clinique privée";
	  return job;
	}

	if (job.Pos("coca") > 0)
	{
	  job = "coca-cola";
	  return job;
	}

	if (job.Pos("coiffeu") > 0)
	{
	  job = "coiffure";
	  return job;
	}

	if (job == "commandant gn")
	{
	  job = "Ministère de l'intérieur";
	  return job;
	}

	if ((job == "comercant") || (job == "comerçant") || (job == "commecant") || (job == "commercant") || (job == "commercante") || (job == "commrcant"))
	{
	  job = "commerce";
	  return job;
	}

	if (job == "conducteur trav")
	{
	  job = "conducteur travaux";
	  return job;
	}

	if (job == "confiction")
	{
	  job = "confection";
	  return job;
	}

	if ((job == "conseil fisc") || (job == "controle d impo") || (job == "courtuere") || (job == "controleur fin"))
	{
	  job = "finances";
	  return job;
	}

	if (job == "croi rou libie")
	{
	  job = "croix rouge";
	  return job;
	}

	if (job == "dar lanouar")
	{
	  job = "journaliste";
	  return job;
	}

	if ((job == "conseille") || (job == "conseillee") || (job == "conseille general"))
	{
	  job = "conseiller";
	  return job;
	}

	if (job == "conseille d asministrateur")
	{
	  job = "cadre d'entreprise";
	  return job;
    }

	if ((job == "conseille jueid") || (job == "conseille juridique"))
	{
	  job = "juriste";
	  return job;
    }

	if ((job == "conseille telephonique") || (job.Pos("operateur") > 0) || (job.Pos("operatrice") > 0) || (job == "tele diffusion") || (job.Pos("tele perf") > 0) ||
	(job.Pos("teleperform") > 0) || (job == "teleoperateur"))
	{
	  job = "téléopérateur téléphonique";
      return job;
    }

	if (job == "de")
	{
	  job = "Directeur Entreprise";
	  return job;
	}

	if (job == "delegue commerc")
	{
	  job = "délégué commerçial";
	  return job;
	}

	if ((job == "dga") || (job == "direc gen") || (job.Pos("direct") > 0))
	{
	  job = "directeur";
	  return job;
	}

	if ((job == "e") || (job == "e%ployee"))
	{
	  job = "employé";
	  return job;
	}

	if (job == "ecretaire")
	{
	  job = "secrétaire";
	  return job;
	}

	if ((job == "eieve") || (job.Pos("elev") > 0) || (job == "elrve") || (job == "elve") || (job == "zleve") || (job == "eleve"))
	{
	  job = "élève";
	  return job;
	}

	if (job == "elec et gaz")
	{
	  job = "technicien";
	  return job;
	}

	if (job == "electromecanicien")
	{
	  job = "mécanicien";
	  return job;
    }

	if ((job == "emlpoye") || (job == "emplmoyee") || (job == "employe") || (job == "employer") || (job == "emplye") || (job == "emplyee") || (job == "employee ate"))
	{
	  job = "employé";
	  return job;
	}

	if ((job == "employe banque") || (job == "employe de banque") || (job == "employee de banque"))
	{
	  job = "banquier";
	  return job;
	}

	if ((job.Pos("ens") == 1) || (job == "ienseignante") || (job == "maitre assis univ") || (job.Pos("prof ") == 1) || (job == "professeur"))
	{
	  job = "enseignant";
	  return job;
    }

	if (job == "esthticienne")
	{
	  job = "esthéticienne";
	  return job;
	}

	if (job.Pos("etud") == 1)
	{
	  job = "étudiant";
	  return job;
	}

	if (job.Pos("expert compt") == 1)
	{
	  job = "expert comptable";
	  return job;
	}

	if (job == "expert juridique")
	{
	  job = "juriste";
	  return job;
	}

	if (job == "f")
	{
	  job = "femme de ménage";
	  return job;
	}

	if (job.Pos("financ") == 1)
	{
	  job = "finances";
	  return job;
	}

	if ((job.Pos("police") > 0) || (job == "garde nationale") || (job == "inspecteur") || (job == "interieur"))
	{
	  job = "ministère de l'intérieur";
	  return job;
	}

	if ((job.Pos("fonct") == 1) || (job == "fontionnaire") || (job == "fonvtionnaire"))
	{
	  job = "fonctionnaire";
	  return job;
	}

	if (job == "forgerant")
	{
	  job = "forgeron";
	  return job;
	}

	if (job.Pos("format") == 1)
	{
	  job = "formateur";
      return job;
	}

	if (job.Pos("gerant") == 1)
	{
	  job = "gerant";
	  return job;
	}

	if ((job == "hotesse") || (job == "hotesse air") || (job == "hotesse de l air"))
	{
	  job = "hotesse de l'air";
	  return job;
	}

	if ((job == "in?genieur") || (job.Pos("ingegnieur") > 0) || (job == "ingenenieur") || (job == "ingegnieur"))
	{
	  job = "ingénieur";
	  return job;
	}

	if (job.Pos("inform") == 1)
	{
	  job = "informaticien";
	  return job;
	}

	if (job == "inspec gen d ens")
	{
	  job = "ministère de l'éducation";
	  return job;
	}

	if (job == "inspect finance")
	{
	  job = "finances";
	  return job;
	}

	if (job == "infermier")
	{
	  job = "infirmier";
	  return job;
	}

	if ((job == "jounalier") || (job == "journalier"))
	{
	  job = "ouvrier";
	  return job;
	}

	if ((job.Pos("kenis") == 1) || (job.Pos("kine") == 1))
	{
	  job = "kinésithérapeute";
	  return job;
    }

	if (job == "m.interne")
	{
	  job = "médecine";
	  return job;
	}

	if ((job == "macanicien") || (job == "mecanicien?") || (job == "mecanique"))
	{
	  job = "mécanicien";
	  return job;
	}

	if (job == "macon")
	{
	  job = "maçon";
	  return job;
	}

	if (job == "magazinier")
	{
	  job = "magasinier";
	  return job;
    }

	if (job == "manuisier allu")
	{
	  job = "menuisier";
	  return job;
	}

	if (job == "marconnerie")
	{
	  job = "maroquinnerie";
	  return job;
    }

	if ((job == "mecanicien  avion") || (job == "mecanicien av"))
	{
	  job = "mécanicien avion";
	  return job;
	}

	if (job.Pos("medecin") == 1)
	{
	  job = "médecin";
	  return job;
	}

	if (job == "menage")
	{
	  job = "femme de ménage";
	  return job;
	}

	if ((job.Pos("minis inter") == 1) || (job == "minis l interieur") || (job == "ministere de l interieur"))
	{
	  job = "ministère de l'intérieur";
	  return job;
	}

	if (job.Pos("ministere de l educ") == 1)
	{
	  job = "ministère de l'éducation";
	  return job;
	}

	if ((job.Pos("pfizer") == 1) || (job.Pos("pharmaci") == 1))
	{
	  job = "pharmacie";
	  return job;
	}

	if (job == "pizayeur")
	{
	  job = "pizzaiolo";
	  return job;
	}

	if ((job.Pos("rerait") == 1) || (job.Pos("retait") == 1) || (job == "reteaite") || (job == "reteraite") || (job == "retraié") || (job.Pos("retrait") == 1) ||
	(job == "retreaitee") || (job == "retrete") || (job == "rettraite") || (job == "reyraite") || (job == "rtetraite") || (job == "trtraite"))
	{
	  job = "retraité";
	  return job;
	}

	if (job == "residente")
	{
	  job = "médecine";
	  return job;
	}

	if (job.Pos("resp") == 1)
	{
	  job = "responsable";
	  return job;
	}

	if (job == "sage  femme")
	{
	  job = "sage femme";
	  return job;
	}

	if (job.Pos("sante") == 1)
	{
	  job = "santé publique";
	  return job;
    }

	if ((job.Pos("secr") == 1) || (job == "secrt medic"))
	{
	  job = "secrétaire";
	  return job;
    }

	if (job == "ser")
	{
	  job = "serveur";
	  return job;
    }

	return job;
}

void __fastcall serialize_gouvernorat(const p_db_field_buffer field_buffer)
{


	if (field_buffer->data[0] == '.')
	{
	  field_buffer->data[0] = 22;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"ariana",12))
	{
	  field_buffer->data[0] = 0;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"beja",8)) || (avcore_memcmp(&field_buffer->data,L"béja",8)))
	{
	  field_buffer->data[0] = 1;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"ben arous",18))
	{
	  field_buffer->data[0] = 2;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"bizerte",14))
	{
	  field_buffer->data[0] = 3;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"gabes",10)) || (avcore_memcmp(&field_buffer->data,L"gabès",10)))
	{
	  field_buffer->data[0] = 4;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"gafsa",10))
	{
	  field_buffer->data[0] = 5;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"jendouba",16)) || (avcore_memcmp(&field_buffer->data,L"jandouba",16)))
	{
	  field_buffer->data[0] = 6;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"kairouan",16))
	{
	  field_buffer->data[0] = 7;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"kasserine",18)) || (avcore_memcmp(&field_buffer->data,L"kassrine",16)))
	{
	  field_buffer->data[0] = 8;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"kébili",12)) || (avcore_memcmp(&field_buffer->data,L"kebili",12)) || (avcore_memcmp(&field_buffer->data,L"kebelli",14)) ||
	(avcore_memcmp(&field_buffer->data,L"kebilli",14)) || (avcore_memcmp(&field_buffer->data,L"guebelli",16)))
	{
	  field_buffer->data[0] = 9;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"kef",6)) || (avcore_memcmp(&field_buffer->data,L"el kef",12)) || (avcore_memcmp(&field_buffer->data,L"le kef",12)))
	{
	  field_buffer->data[0] = 10;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"mahdia",12))
	{
	  field_buffer->data[0] = 11;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"mannouba",16)) || (avcore_memcmp(&field_buffer->data,L"la mannouba",22)) || (avcore_memcmp(&field_buffer->data,L"manouba",14)))
	{
	  field_buffer->data[0] = 12;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"médenine",16)) || (avcore_memcmp(&field_buffer->data,L"medenine",16)) || (avcore_memcmp(&field_buffer->data,L"mednine",14)))
	{
	  field_buffer->data[0] = 13;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"monastir",16))
	{
	  field_buffer->data[0] = 14;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"nabeul",12))
	{
	  field_buffer->data[0] = 15;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"sfax",8))
	{
	  field_buffer->data[0] = 16;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"sidi bouzid",22)) || (avcore_memcmp(&field_buffer->data,L"sidibouzid",20)))
	{
	  field_buffer->data[0] = 17;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"siliana",14)) || (avcore_memcmp(&field_buffer->data,L"seliana",14)))
	{
	  field_buffer->data[0] = 18;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"sousse",12))
	{
	  field_buffer->data[0] = 19;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"tataouine",18))
	{
	  field_buffer->data[0] = 20;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"tozeur",12)) || (avcore_memcmp(&field_buffer->data,L"tozeutunisie",24)))
	{
	  field_buffer->data[0] = 21;
	  return;
	}

	if (avcore_memcmp(&field_buffer->data,L"tunis",10))
	{
	  field_buffer->data[0] = 22;
	  return;
	}

	if ((avcore_memcmp(&field_buffer->data,L"zaghouan",16)) || (avcore_memcmp(&field_buffer->data,L"zaghouen",16)))
	{
	  field_buffer->data[0] = 23;
	  return;
	}

	//bad_gouv->Add((PWCHAR)&field_buffer->data);

	field_buffer->data[0] = MAXBYTE;

	return;
}

void __fastcall serialize_pays(const p_db_field_buffer field_buffer)
{
  const puchar list[197] = {(puchar)L"afghanistan",(puchar)L"afrique du sud",(puchar)L"albanie",(puchar)L"algérie",(puchar)L"allemagne",(puchar)L"andorre",(puchar)L"angola",(puchar)L"antigua-et-barbuda",(puchar)L"arabie saoudite",(puchar)L"argentine",
							(puchar)L"arménie",(puchar)L"australie",(puchar)L"autriche",(puchar)L"azerbaïdjan",(puchar)L"bahamas",(puchar)L"bahreïn",(puchar)L"bangladesh",(puchar)L"barbade",(puchar)L"belgique",(puchar)L"belize",(puchar)L"bénin",(puchar)L"bhoutan",
							(puchar)L"biélorussie",(puchar)L"birmanie",(puchar)L"bolivie",(puchar)L"bosnie-herzégovine",(puchar)L"botswana",(puchar)L"brésil",(puchar)L"brunei",(puchar)L"bulgarie",(puchar)L"burkina faso",(puchar)L"burundi",(puchar)L"cambodge",
							(puchar)L"cameroun",(puchar)L"canada",(puchar)L"cap-vert",(puchar)L"république centrafricaine",(puchar)L"chili",(puchar)L"chine",(puchar)L"chypre",(puchar)L"colombie",(puchar)L"comores",(puchar)L"république du congo",
							(puchar)L"république démocratique du congo",(puchar)L"îles cook",(puchar)L"corée du nord",(puchar)L"corée du sud",(puchar)L"costa rica",(puchar)L"côte d’ivoire",(puchar)L"croatie",(puchar)L"cuba",(puchar)L"danemark",
							(puchar)L"djibouti",(puchar)L"république dominicaine",(puchar)L"dominique",(puchar)L"égypte",(puchar)L"émirats arabes unis",(puchar)L"équateur",(puchar)L"érythrée",(puchar)L"espagne",(puchar)L"estonie",(puchar)L"états-unis / USA",
							(puchar)L"éthiopie",(puchar)L"fidji",(puchar)L"finlande",(puchar)L"france",(puchar)L"gabon",(puchar)L"gambie",(puchar)L"géorgie",(puchar)L"ghana",(puchar)L"grèce",(puchar)L"grenade",(puchar)L"guatemala",(puchar)L"guinée",(puchar)L"guinée-bissau",
							(puchar)L"guinée équatoriale",(puchar)L"guyana",(puchar)L"haïti",(puchar)L"honduras",(puchar)L"hongrie",(puchar)L"inde",(puchar)L"indonésie",(puchar)L"irak",(puchar)L"iran",(puchar)L"irlande",(puchar)L"islande",(puchar)L"israël",(puchar)L"italie",
							(puchar)L"jamaïque",(puchar)L"japon",(puchar)L"jordanie",(puchar)L"kazakhstan",(puchar)L"kenya",(puchar)L"kirghizistan",(puchar)L"kiribati",(puchar)L"koweït",(puchar)L"laos",(puchar)L"lesotho",(puchar)L"lettonie",(puchar)L"liban",(puchar)L"liberia",
							(puchar)L"libye",(puchar)L"liechtenstein",(puchar)L"lituanie",(puchar)L"luxembourg",(puchar)L"macédoine",(puchar)L"madagascar",(puchar)L"malaisie",(puchar)L"malawi",(puchar)L"maldives",(puchar)L"mali",(puchar)L"malte",(puchar)L"maroc",
							(puchar)L"îles marshall",(puchar)L"maurice",(puchar)L"mauritanie",(puchar)L"mexique",(puchar)L"micronésie",(puchar)L"moldavie",(puchar)L"monaco",(puchar)L"mongolie",(puchar)L"monténégro",(puchar)L"mozambique",(puchar)L"namibie",
							(puchar)L"nauru",(puchar)L"népal",(puchar)L"nicaragua",(puchar)L"niger",(puchar)L"nigeria",(puchar)L"niue",(puchar)L"norvège",(puchar)L"nouvelle-zélande",(puchar)L"oman",(puchar)L"ouganda",(puchar)L"ouzbékistan",(puchar)L"pakistan",
							(puchar)L"palaos",(puchar)L"palestine",(puchar)L"panamá",(puchar)L"papouasie-nouvelle-guinée",(puchar)L"paraguay",(puchar)L"pays-bas",(puchar)L"pérou",(puchar)L"philippines",(puchar)L"pologne",(puchar)L"portugal",(puchar)L"qatar",
							(puchar)L"roumanie",(puchar)L"royaume-uni",(puchar)L"russie",(puchar)L"rwanda",(puchar)L"saint-christophe-et-niévès",(puchar)L"saint-marin",(puchar)L"saint-vincent-et-les grenadines",(puchar)L"sainte-lucie",
							(puchar)L"îles salomon",(puchar)L"salvador",(puchar)L"samoa",(puchar)L"são tomé-et-principe",(puchar)L"sénégal",(puchar)L"serbie",(puchar)L"seychelles",(puchar)L"sierra leone",(puchar)L"singapour",(puchar)L"slovaquie",
							(puchar)L"slovénie",(puchar)L"somalie",(puchar)L"soudan",(puchar)L"soudan du sud",(puchar)L"sri lanka",(puchar)L"suède",(puchar)L"suisse",(puchar)L"suriname",(puchar)L"swaziland",(puchar)L"syrie",(puchar)L"tadjikistan",(puchar)L"tanzanie",
							(puchar)L"tchad",(puchar)L"république tchèque",(puchar)L"thaïlande",(puchar)L"timor oriental",(puchar)L"togo",(puchar)L"tonga",(puchar)L"trinité-et-tobago",(puchar)L"tunis",(puchar)L"turkménistan",(puchar)L"turquie",(puchar)L"tuvalu",
							(puchar)L"ukraine",(puchar)L"uruguay",(puchar)L"vanuatu",(puchar)L"vatican",(puchar)L"venezuela",(puchar)L"viêtnam",(puchar)L"yémen",(puchar)L"zambie",(puchar)L"zimbabwe"};


	UnicodeString str;

	str = (PWCHAR)&field_buffer->data;

	str = str.LowerCase();

	if ((str == "algerie") || (str == "algarie") || (str == "alegerie") || (str == "algetrie"))
	{
	  str = "algérie";
	}
	else if (str == "suede")
	{
	  str = "suède";
	}
	else if ((str == "benin") || (str == "benine"))
	{
	  str = L"bénine";
	}
	else if (str == "koweit")
	{
	  str = "koweït";
	}
	else if ((str == "emirat") || (str == "doubei") || (str == "dubai"))
	{
	  str = "émirats arabes unis";
	}
	else if (str == "senegal")
	{
      str = "sénégal";
	}
	else if (str == "ethiopie")
	{
	  str = "éthiopie";
	}
	else if (str == "usa")
	{
	  str = "états-unis / USA";
	}
	else if ((str ==  "tripoli") || (str == "libie") || (str == "libya") || (str == "lybie"))
	{
	  str = "libye";
	}
	else if ((str == "kairouan") || (str == "bizerte") || (str == "gabes") || (str == "tubnisie") || (str == "tun isie") || (str == "tunsie") ||
	(str == "tuinisie") || (str == "ttunisie") || (str == "tiunisie") || (str == "trunisie") || (str == "tyunisie") || (str == "sidi bouzid") || (str == "tunisue") ||
	(str == "ariana") || (str == "tuni") || (str == "tusie") || (str == "tunisde") || (str == "tinisie") || (str == "sousse") || (str == "medenine") || (str == "beja") ||
	(str == "mannouba") || (str == "tuniie") || (str == "t") || (str == "yunisie") || (str == "siliana"))
	{
      str = "tunis";
	}
	else if (str == "angleterre")
	{
	  str = "royaume-uni";
	}
	else if ((str == "cote d'ivoire") || (str == "cote d'ivoire/tunisi") || (str == "abidjon") || (str == "cote d'ivoir"))
	{
	  str = "côte d’ivoire";
	}
	else if ((str == "moritanie") || (str == "mouritanie") || (str == "nouak chot"))
	{
      str = "mauritanie";
	}
	else if (str == "cammeroun")
	{
      str = "cameroun";
	}
	else if (str == "soumal")
	{
      str = "somalie";
	}
	else if ((str == "gongo") || (str == "congo"))
	{
      str = "république du congo";
	}
	else if (str == "congo kinchassa")
	{
	  str = "république démocratique du congo";
    }
	else if (str == "italy")
	{
      str = "italie";
	}
	else if ((str == "negeria") || (str == "nijeria"))
	{
      str = "nigéria";
	}
	else if (str == "arabie saoudi")
	{
      str = "arabie saoudite";
	}
	else if (str == "turkie")
	{
      str = "turquie";
	}
	else if (str == "montreal")
	{
      str = "canada";
	}
	else if (str == "maly")
	{
      str = "mali";
    }
	else if (str == "guinee")
	{
	  str = "guinée";
	}
	else if (str == "egypte")
	{
	  str = "égypte";
	}
	else if (str == "yemen")
	{
      str = "yémen";
    }

	for (int i = 0; i < 197; i++)
	{
	  if (str.Pos((PWCHAR)list[i]) > 0)
	  {
		field_buffer->data[0] = (uint8)i;
		return;
	  }
	}

	field_buffer->data[0] = 184;

	return;
}

static void doctor_name_serializer(const p_db_field_buffer field_buffer)
{
  UnicodeString str = (PWCHAR)&field_buffer->data;
  UnicodeString processed_str = "";


	if ((str.Pos("CHUR") > 0) || (str.Pos("RABTA") > 0) || (str.Pos("RABATA") > 0))
	{
	  processed_str = "CHU Rabta";
	}
	else if ((str.Pos("THAMEUR") > 0) || (str.Pos("HHT") > 0) || (str.Pos("THAMER") > 0) || (str.Pos("HOP H TH") > 0))
	{
	  processed_str = "CHU Habib Thameur";
	}
	else if (str.Pos("MONASTIR") > 0)
	{
	  processed_str = "CHU Fattouma Bourguiba";
	}
	else if ((str.Pos("CHU MIL") > 0) || (str.Pos("MILITAIRE") > 0))
	{
      processed_str = "CHU Militaire";
	}
	else if (str.Pos("NABEUL") > 0)
	{
      processed_str = "CHU Nabeul";
	}
	else if (str.Pos("SOUSSE") > 0)
	{
	  processed_str = "CHU Sahloul";
    }
	else if (str.Pos("SFAX") > 0)
	{
	  processed_str = "CHU Hédi Chaker";
	}
	else if ((str.Pos("HCN") > 0) || (str.Pos("C.N") > 0) || (str.Pos("CHARLES") > 0))
	{
      processed_str = "CHU Charles Nicolle";
	}
	else if (str.Pos("JENDOUBA") > 0)
	{
	  processed_str = "HR Jendouba";
	}
	else if ((str.Pos("MARSA") > 0) || (str.Pos("MONJI") > 0) || (str.Pos("MONGI") > 0))
	{
	  processed_str = "CHU Mongi Slim";
	}
	else if (str.Pos("BEJA") > 0)
	{
      processed_str = "HR Béja";
	}
	else if ((str == "CHU") || (str == "CHUR"))
	{
	  processed_str = "CHU Rabta";
	}
	else if (str.Pos("KHAIREDDINE") > 0)
	{
	  processed_str = "HR Kheireddine";
	}
	else if (str.Pos("ZAGHOUAN") > 0)
	{
      processed_str = "HR Zaghouan";
	}
	else if (str.Pos("SILIANA") > 0)
	{
      processed_str = "HR Siliana";
    }

	if (processed_str != "")
	{
	  field_buffer->field_len = processed_str.Length() * 2;
	  *(puint16)&field_buffer->data[field_buffer->field_len] = 0;
	  avcore_memcpy(&field_buffer->data,(puchar)processed_str.c_str(),field_buffer->field_len);
	}

    return;
}

static void patient_name_serializer(const p_db_field_buffer field_buffer)
{
  UnicodeString PatNomEdit;
  int i,pos_str;
  bool found = false;


	//avcore_wstrlower((puchar)&field_buffer->data,field_buffer->field_len);

	if (field_buffer->field_len < 2) return;

	if (field_buffer->data[field_buffer->field_len - 2] == 'A')
	{
	  field_buffer->data[sizeof(field_buffer->data) - 1] = 1;
	  return;
	}

	PatNomEdit = (PWCHAR)&field_buffer->data;

	for (i = 0; i < femmes->Count; i++)
	{
	  if (femmes->Strings[i][1] == '!')
	  {
		if (!PatNomEdit.Compare(femmes->Strings[i].SubString(2,femmes->Strings[i].Length() - 1)))
		{
		  found = true;
		  break;
		}
		else
		{
		  pos_str = PatNomEdit.Pos(femmes->Strings[i].SubString(2,femmes->Strings[i].Length() - 1));

		  if ((pos_str > 1) && (PatNomEdit[pos_str - 1] == ' '))
		  {
			found = true;
			break;
          }
		}
	  }
	  else if (PatNomEdit.Pos(femmes->Strings[i]) > 0)
	  {
		found = true;
		break;
	  }
	}

	if (found)
	{
	  field_buffer->data[sizeof(field_buffer->data) - 1] = 1;
	}
	else field_buffer->data[sizeof(field_buffer->data) - 1] = 0;

	return;
}

void __fastcall db_field_serializer(const p_db_field_buffer field_buffer,const t_lilly_db_import_serializer_mode serializer_mode)
{
  UnicodeString str;

   switch (serializer_mode)
   {
	 case t_lilly_db_import_generic_string_serializer : avcore_wstrlower((puchar)&field_buffer->data,field_buffer->field_len);
														break;

				case t_lilly_db_import_job_serializer : str = (PWCHAR)&field_buffer->data;

														str = job_serializer(str);

														field_buffer->field_len = (unsigned_int)str.Length() * 2;

														*(puint16)&field_buffer->data[field_buffer->field_len] = 0;

														avcore_memcpy(&field_buffer->data,(puchar)str.c_str(),field_buffer->field_len);

														break;
																		 
	  case t_lilly_db_import_operator_name_serializer : if (field_buffer->field_len == 2)
														{
														  switch (field_buffer->data[0])
														  {
															case 'L' :
															case 'l' : avcore_memcpy(&field_buffer->data,DEFAULT_OPERATOR_NAME,DEFAULT_OPERATOR_NAME_LEN);
																	   break;

															case 't' :
															case 'T' : avcore_memcpy(&field_buffer->data,L"Taoufik",14);
																	   break;
														  }
														}

														break;
														
		case t_lilly_db_import_doctor_name_serializer : doctor_name_serializer(field_buffer);
                                                        break;

			   case t_lilly_db_import_pays_serializer : serialize_pays(field_buffer);
                                                        break;

			  case t_lilly_db_import_ville_serializer : avcore_wstrlower((puchar)&field_buffer->data,field_buffer->field_len);
														break;

		case t_lilly_db_import_gouvernorat_serializer : avcore_wstrlower((puchar)&field_buffer->data,field_buffer->field_len);
                                                        serialize_gouvernorat(field_buffer);
														break;

 case t_lilly_db_import_gainp_prothese_ref_serializer : {UnicodeString reference;

														reference = (PWCHAR)&field_buffer->data;

														for (int i = 0; i < gainp_proth_refs->Count; i++)
														{
														  if (gainp_proth_refs->Strings[i] == reference)
														  {
															*(puint16)&field_buffer->data[0] = (uint16)i;
															return;
														  }
														}

														*(puint16)&field_buffer->data[0] = 0;
														}
														break;

			  case t_lilly_db_import_codep_serializer : {
														  UnicodeString codep;

														if (!orphan_codep) break;

														codep = (PWCHAR)&field_buffer->data;

														for (int i = 0; i < orphan_codep->Count; i++)
														{
														  if (orphan_codep->Strings[i] == codep)
														  {
															field_buffer->field_len = 0;
															return;
														  }
														}
														}

														break;

	   case t_lilly_db_import_patient_name_serializer : patient_name_serializer(field_buffer);
														break;
   }

   return;
}

void __fastcall TForm1::report_event(const UnicodeString event,const TMsgDlgType dlg_type,const boolean fatal)
{
  unsigned_int beep_value;


   switch (dlg_type)
   {

			case TMsgDlgType::mtWarning : beep_value = MB_ICONWARNING;
										  break;

			  case TMsgDlgType::mtError : beep_value = MB_ICONERROR;
										  break;

		case TMsgDlgType::mtInformation : beep_value = MB_ICONINFORMATION;
										  break;

	   case TMsgDlgType::mtConfirmation : beep_value = MB_ICONASTERISK;
										  break;

			 case TMsgDlgType::mtCustom :
								default : beep_value = IO_ERROR;
										  break;

   }

   MessageBeep(beep_value);

   MessageDlg(event,dlg_type,TMsgDlgButtons() << mbOK,0);

   if (fatal) Application->Terminate();

   return;

}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  unsigned_int error_code;


	session_manager = get_new_session_manager(921979,&error_code);

	PageControl1->ActivePage = OpPage;

	femmes = new TStringList(this);

	femmes->LoadFromFile("C:\\Patient2k19\\databases\\femmes.dat");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	SessionIDLbl->Text = IntToStr(Random(MAXDWORD));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (OpenDialog1->Execute())
	{
	  OpSrcLbl->Text = OpenDialog1->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
   if (SaveDialog1->Execute())
   {
	 OpDestLbl->Text = SaveDialog1->FileName;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  p_lilly_db_engine db_engine;
  puchar buffer;
  unsigned_int buffer_size;
  t_operateur_record record;


   if ((OpSrcLbl->Text == "") || (OpDestLbl->Text == ""))
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   unsigned_int fhandle = lilly_io_open_file((puchar)OpSrcLbl->Text.c_str(),lilly_io_fmOpen,lilly_io_faRead);

   if ((signed_int)fhandle <= 0)
   {
	 report_event("open file error !",mtError,false);
	 return;
   }

   buffer_size = (unsigned_int)lilly_io_get_file_size_ex(fhandle);

   if ((signed_int)buffer_size <= 0)
   {
	 report_event("get file size error !",mtError,false);
	 return;
   }

   buffer = (puchar)malloc(buffer_size);

   if (!buffer)
   {
	 report_event("application out of memory !",mtError,true);
	 return;
   }

   if (!lilly_io_file_read(fhandle,buffer,buffer_size))
   {
	 report_event("read file error !",mtError,true);
	 return;
   }

   lilly_io_close_file(fhandle);

   db_engine = session_manager->register_lilly_engine(session_manager,OPERATOR_DB_SIGNATURE);

   if (!db_engine)
   {
	 report_event("request db engine error !",mtError,false);
	 return;
   }

   struct t_lilly_db_handle * db_handle = db_engine->new_database(db_engine,(puchar)OpDestLbl->Text.c_str(),OpDestLbl->Text.Length() * 2,0,0,921979);

   if (!db_handle)
   {
	 report_event("request db handle error !",mtError,false);
	 return;
   }

   unsigned_int count = 0;
   unsigned_int index = 0;

   t_db_field_buffer field_buffer;
   unsigned_int size_left = buffer_size;
   puchar data = lilly_import_get_first_field(buffer,&size_left);

   if ((!data) || ((signed_int)size_left <= 0))
   {
	 report_event("get field error !",mtError,false);
	 return;
   }

   while (TRUE)
   {
	 avcore_memset(&record,0,sizeof(record));

	 if (!lilly_import_read_db_field(&field_buffer,12,data,size_left))
	 {
	   report_event("read db field error !",mtError,false);
	   return;
	 }

	 if (!field_buffer.field_len)
	 {
	   avcore_memcpy((puchar)&record.nom_prenom[0],DEFAULT_OPERATOR_NAME,DEFAULT_OPERATOR_NAME_LEN);
	 }
	 else if (field_buffer.field_len == 2)
	 {
	   switch (field_buffer.data[0])
	   {
		 case 'L' :
		 case 'l' : avcore_memcpy(&record.nom_prenom[0],DEFAULT_OPERATOR_NAME,DEFAULT_OPERATOR_NAME_LEN);
					break;

		 case 't' :
		 case 'T' : avcore_memcpy(&record.nom_prenom[0],L"Taoufik",14);
					break;

		 default : record.nom_prenom[0] = field_buffer.data[0];
				   break;
	   }
	 }
	 else
	 {
	   if (field_buffer.field_len > sizeof(record.nom_prenom) - 2)
	   {
		 report_event("Nom operateur trop long ou erreur parsing du field [OP] !",mtError,false);
		 return;
	   }

	   avcore_memcpy(&record.nom_prenom[0],&field_buffer.data[0],field_buffer.field_len);
	 }

	 if (!db_engine->append_record(db_engine,db_handle,&record))
	 {
	   if(db_engine->error_code != LILLY_DB_DUPLICATE_RECORD_ERROR)
	   {
		 report_event("erreur est survenue lors de la tentative d'ajout d'un record !",mtError,false);
		 return;
       }
	 }
	 else count++;

	 index++;

	 OpstatLbl->Caption = IntToStr((int)index) + " fiches traitées";

	 Application->ProcessMessages();

	 data = lilly_import_get_next_field(data,&size_left);

	 if ((!data) || ((signed_int)size_left <= 0)) break;
   }

   free(buffer);

   OpstatLbl->Caption = "Operation terminée. /" + IntToStr((int)count) + " fiches ajoutées.";

   return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{

   if (OpenDialog1->Execute())
   {
	 DocSrcEdit->Text = OpenDialog1->FileName;
   }

   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	  DocDestEdit->Text = SaveDialog1->FileName;
	}

	return;
}

//---------------------------------------------------------------------------

static int MedNameToHopitalIndex(const UnicodeString MedName)
{
  static const puchar names[] = {(puchar)L"CHU Mongi Slim",(puchar)L"CHU Habib Thameur",(puchar)L"Hôpital Aziza Othmana",(puchar)L"CHU Charles Nicolle",(puchar)L"CHU La Rabta",
								 (puchar)L"Hôpital d'Enfants",(puchar)L"CHU Sahloul",(puchar)L"CHU Farhat Hached",(puchar)L"CHU Fattouma Bourguiba",(puchar)L"CHU Hédi Chaker",
								 (puchar)L"CHU Habib Bourguiba",(puchar)L"HR Kheireddine",(puchar)L"HR Menzel Bourguiba",(puchar)L"HR Nabeul",(puchar)L"CHU Nabeul",
								 (puchar)L"HR Menzel Temim",(puchar)L"HR Zaghouan",(puchar)L"HR Jendouba",(puchar)L"HR Béja",(puchar)L"HR Mjez El Bab",(puchar)L"HR Kef",
								 (puchar)L"HR Siliana",(puchar)L"HR Kasserine",(puchar)L"HR Kairouan",(puchar)L"HR Msaken",(puchar)L"CHU Mahdia",(puchar)L"HR Ksar Hellal",
								 (puchar)L"HR Kerkennah",(puchar)L"HR Gafsa",(puchar)L"HR Tozeur",(puchar)L"HR Sidi Bouzid",(puchar)L"HR Gabès",(puchar)L"HR Kébili",
								 (puchar)L"HR Médenine",(puchar)L"HR Djerba",(puchar)L"HR Moknine",(puchar)L"HR Ben Guerdane",(puchar)L"HR Jebiniana",(puchar)L"HR Ben Arous",
								 (puchar)L"HR Mahres",(puchar)L"CHU Bizerte",(puchar)L"HR Metlaoui",(puchar)L"HR Zarzis",(puchar)L"HR Tataouin",(puchar)L"HR Mahmoud El Matri",
								 (puchar)L"CHU Hopital FSI",(puchar)L"CHU Militaire"};

  UnicodeString str;

	 for (int i = 0; i < sizeof(names) / sizeof(names[0]); i++)
	 {
	   str = (PWCHAR)names[i];
	   if ((MedName.Length() == str.Length()) && (MedName == str)) return i;
	 }

     return -1;
}

static boolean FillHopitalRecord(const int HopitalIndex,const p_medecin_record med_record)
{
  typedef struct {
				   puchar nom;
				   uint8 pays;
				   uint8 gouvernorat;
				   puchar tel1;
				   puchar tel2;
				   puchar fax;
				   puchar mail;
				 } t_hopital_infos,*p_hopital_infos;

  static t_hopital_infos hopitaux[] = {{(puchar)L"CHU Mongi Slim",184,22,(puchar)L"71 764 325",(puchar)L"71 765 118",NULL},
											 {(puchar)L"CHU Habib Thameur",184,22,(puchar)L"71 492 773",(puchar)L"71 397 000",(puchar)L"71 492 163",NULL},
											 {(puchar)L"Hôpital Aziza Othmana",184,22,(puchar)L"71 560 763",(puchar)L"71 570 777",(puchar)L"71 560 763",NULL},
											 {(puchar)L"CHU Charles Nicolle",184,22,(puchar)L"71 262 740",(puchar)L"71 578 007",(puchar)L"71 262 740",NULL},
											 {(puchar)L"CHU Rabta",184,22,(puchar)L"71 263 980",NULL,(puchar)L"71 263 980",NULL},
											 {(puchar)L"Hôpital d'enfants",184,22,(puchar)L"71 262 987",(puchar)L"71 577 700",(puchar)L"71 262 987",NULL},
											 {(puchar)L"CHU Sahloul",184,19,(puchar)L"73 241 411",(puchar)L"73 369 411",(puchar)L"73 241 411",NULL},
											 {(puchar)L"CHU Farhat Hached",184,19,(puchar)L"73 222 293",(puchar)L"73 221 425",(puchar)L"73 222 293",NULL},
											 {(puchar)L"CHU Fattouma Bourguiba",184,14,(puchar)L"73 460 309",(puchar)L"73 460 411",(puchar)L"73 460 309",NULL},
											 {(puchar)L"CHU Hédi Chaker",184,16,(puchar)L"74 242 181",(puchar)L"74 244 422",(puchar)L"74 242 181",NULL},
											 {(puchar)L"CHU Habib Bourguiba",184,16,(puchar)L"74 242 333",(puchar)L"74 241 511",(puchar)L"74 242 333",NULL},
											 {(puchar)L"HR Kheireddine",184,22,(puchar)L"71 731 860",(puchar)L"71 730 100",(puchar)L"71 734 864",NULL},
											 {(puchar)L"HR Menzel Bourguiba",184,3,(puchar)L"72 460 284",(puchar)L"72 460 455",(puchar)L"72 464 411",NULL},
											 {(puchar)L"HR Nabeul",184,15,(puchar)L"72 285 673",(puchar)L"72 285 633",(puchar)L"72 285 673",NULL},
											 {(puchar)L"CHU Nabeul",184,15,(puchar)L"72 285 673",(puchar)L"72 285 022",(puchar)L"72 285 673",NULL},
											 {(puchar)L"HR Menzel Temim",184,15,(puchar)L"72 344 167",(puchar)L"72 344 155",(puchar)L"72 344 167",NULL},
											 {(puchar)L"HR Zaghouan",184,23,(puchar)L"72 676 700",(puchar)L"72 675 772",(puchar)L"72 676 700",NULL},
											 {(puchar)L"HR Jendouba",184,6,(puchar)L"78 630 110",(puchar)L"78 603 600",(puchar)L"78 630 110",NULL},
											 {(puchar)L"HR Béja",184,1,(puchar)L"78 454 355",(puchar)L"78 455 431",(puchar)L"78 454 355",NULL},
											 {(puchar)L"HR Mjez El Bab",184,1,(puchar)L"78 460 600",(puchar)L"78 560 600",(puchar)L"78 460 600",NULL},
											 {(puchar)L"HR Kef",184,10,(puchar)L"78 228 160",(puchar)L"78 228 900",(puchar)L"78 228 160",NULL},
											 {(puchar)L"HR Siliana",184,18,(puchar)L"78 870 372",(puchar)L"78 872 800",(puchar)L"78 870 372",NULL},
											 {(puchar)L"HR Kasserine",184,8,(puchar)L"77 474 910",(puchar)L"77 447 022",NULL,NULL},
											 {(puchar)L"HR Kairouan",184,7,(puchar)L"77 227 177",(puchar)L"77 226 300",(puchar)L"77 229 712",NULL},
											 {(puchar)L"HR Msaken",184,19,(puchar)L"73 260 431",(puchar)L"73 259 106",(puchar)L"73 260 431",NULL},
											 {(puchar)L"CHU Mahdia",184,11,(puchar)L"73 671 744",NULL,(puchar)L"73 671 579",NULL},
											 {(puchar)L"HR Ksar Hellal",184,14,(puchar)L"73 476 054",(puchar)L"73 476 275",(puchar)L"73 476 054",NULL},
											 {(puchar)L"HR Kerkennah",184,16,(puchar)L"74 281 119",(puchar)L"74 481 052",(puchar)L"74 281 119",NULL},
											 {(puchar)L"HR Gafsa",184,5,(puchar)L"76 226 278",(puchar)L"76 225 055",(puchar)L"76 226 278",NULL},
											 {(puchar)L"HR Tozeur",184,21,(puchar)L"76 453 400",NULL,NULL,NULL},
											 {(puchar)L"HR Sidi Bouzid",184,17,(puchar)L"76 632 175",(puchar)L"76 632 500",(puchar)L"76 632 175",NULL},
											 {(puchar)L"HR Gabès",184,4,(puchar)L"75 282 530",(puchar)L"75 282 700",(puchar)L"75 282 530",NULL},
											 {(puchar)L"HR Kébili",184,9,(puchar)L"75 490 210",(puchar)L"75 490 027",(puchar)L"75 490 210",NULL},
											 {(puchar)L"HR Médenine",184,13,(puchar)L"75 640 044",NULL,NULL,NULL},
											 {(puchar)L"HR Djerba",184,13,(puchar)L"75 650 160",(puchar)L"75 650 018",(puchar)L"75 650 160",NULL},
											 {(puchar)L"HR Moknine",184,14,(puchar)L"73 476 508",(puchar)L"73 476 444",(puchar)L"73 476 508",NULL},
											 {(puchar)L"HR Ben Guerdane",184,13,(puchar)L"75 710 050",NULL,NULL,NULL},
											 {(puchar)L"HR Jebiniana",184,16,(puchar)L"74 880 031",NULL,(puchar)L"74 880 023",NULL},
											 {(puchar)L"HR Ben Arous",184,2,(puchar)L"71 315 600",NULL,NULL,NULL},
											 {(puchar)L"HR Mahres",184,16,(puchar)L"74 290 012",(puchar)L"74 290 293",(puchar)L"74 290 012",NULL},
											 {(puchar)L"CHU Bizerte",184,3,(puchar)L"72 460 284",(puchar)L"72 431 422",(puchar)L"72 464 411",NULL},
											 {(puchar)L"HR Metlaoui",184,21,(puchar)L"76 241 600",(puchar)L"76 241 502",(puchar)L"76 241 600",NULL},
											 {(puchar)L"HR Zarzis",184,13,(puchar)L"75 680 726",(puchar)L"75 694 400",(puchar)L"75 680 726",NULL},
											 {(puchar)L"HR Tataouin",184,20,(puchar)L"75 862 005",(puchar)L"75 870 114",(puchar)L"75 862 005",NULL},
											 {(puchar)L"HR Mahmoud El Matri",184,0,(puchar)L"71 821 286",(puchar)L"71 821 621",NULL,NULL},
											 {(puchar)L"CHU Hopital FSI",184,22,(puchar)L"71 745 644",(puchar)L"71 746 373",NULL,NULL},
											 {(puchar)L"CHU Militaire",184,22,(puchar)L"71 399 111",(puchar)L"71 391 133",(puchar)L"71 391 099",(puchar)L"hmpit@defense.tn"}};


	 if (HopitalIndex > sizeof(hopitaux) / sizeof(hopitaux[0])) return false;

	 p_hopital_infos hop_infos = &hopitaux[HopitalIndex];

	 avcore_memset(med_record,0,sizeof(*med_record));

	 int len = avcore_wstrlen(hop_infos->nom) * 2;

	 if (len >= sizeof(med_record->nom_prenom)) return false;

	 avcore_memcpy(&med_record->nom_prenom,hop_infos->nom,len);

	 med_record->pays = hop_infos->pays;
	 med_record->gouvernorat = hop_infos->gouvernorat;
	 med_record->type = HOPITAL_TYPE;

	 if (hop_infos->tel1)
	 {
	   len = avcore_wstrlen(hop_infos->tel1) * 2;
	   if (len >= sizeof(med_record->phone_principal)) return false;
	   avcore_memcpy(&med_record->phone_principal,hop_infos->tel1,len);
	 }

	 if (hop_infos->tel2)
	 {
	   len = avcore_wstrlen(hop_infos->tel2) * 2;
	   if (len >= sizeof(med_record->phone_secondaire)) return false;
	   avcore_memcpy(&med_record->phone_secondaire,hop_infos->tel2,len);
	 }

	 if (hop_infos->mail)
	 {
	   len = avcore_wstrlen(hop_infos->mail) * 2;
	   if (len >= sizeof(med_record->email)) return false;
	   avcore_memcpy(&med_record->email,hop_infos->mail,len);
	 }

	 return true;

}

void __fastcall TForm1::Button12Click(TObject *Sender)
{
  p_lilly_db_engine db_engine;
  puchar buffer;
  unsigned_int buffer_size;
  int hop_index;
  t_medecin_record record;


   if ((DocSrcEdit->Text == "") || (DocDestEdit->Text == ""))
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   unsigned_int fhandle = lilly_io_open_file((puchar)DocSrcEdit->Text.c_str(),lilly_io_fmOpen,lilly_io_faRead);

   if ((signed_int)fhandle <= 0)
   {
	 report_event("open file error !",mtError,false);
	 return;
   }

   buffer_size = (unsigned_int)lilly_io_get_file_size_ex(fhandle);

   if ((signed_int)buffer_size <= 0)
   {
	 report_event("get file size error !",mtError,false);
	 return;
   }

   buffer = (puchar)malloc(buffer_size);

   if (!buffer)
   {
	 report_event("application out of memory !",mtError,true);
	 return;
   }

   if (!lilly_io_file_read(fhandle,buffer,buffer_size))
   {
	 report_event("read file error !",mtError,true);
	 return;
   }

   lilly_io_close_file(fhandle);

   db_engine = session_manager->register_lilly_engine(session_manager,DOCTOR_DB_SIGNATURE);

   if (!db_engine)
   {
	 report_event("request db engine error !",mtError,false);
	 return;
   }

   struct t_lilly_db_handle * db_handle = db_engine->new_database(db_engine,(puchar)DocDestEdit->Text.c_str(),DocDestEdit->Text.Length() * 2,0,0,921979);

   if (!db_handle)
   {
	 report_event("request db handle error !",mtError,false);
	 return;
   }

   unsigned_int count = 0;
   unsigned_int index = 0;

   t_db_field_buffer field_buffer;
   unsigned_int size_left = buffer_size;
   puchar data = lilly_import_get_first_field(buffer,&size_left);

   if ((!data) || ((signed_int)size_left <= 0))
   {
	 report_event("get field error !",mtError,false);
	 return;
   }

   //TStringList *list = new TStringList(this);

   avcore_memset(&record,0,sizeof(record));

   record.gouvernorat = 21;
   record.pays = 184;

   while (TRUE)
   {
	 avcore_memset(&record,0,sizeof(record));

     record.gouvernorat = 21;
     record.pays = 184;

	 if (!lilly_import_read_db_field(&field_buffer,7,data,size_left))
	 {
	   report_event("read db field error !",mtError,false);
	   return;
	 }

	 if ((!field_buffer.field_len) || (field_buffer.data[0] == '.'))
	 {
	   avcore_memcpy((puchar)&record.nom_prenom[0],DEFAULT_NAME,DEFAULT_NAME_LEN);
	 }
	 else
	 {
	   doctor_name_serializer(&field_buffer);

	   hop_index = MedNameToHopitalIndex((PWCHAR)&field_buffer.data);

	   if (hop_index != -1)
	   {
		 if (!FillHopitalRecord(hop_index,&record))
		 {
		   report_event("erreur est survenue au niveau de FillHopitalRecord !",mtError,false);
		   return;
		 }
	   }
	   else
	   {
		 if (field_buffer.field_len > sizeof(record.nom_prenom) - 2)
		 {
		   report_event("Nom operateur trop long ou erreur parsing du field [CODEMED] !",mtError,false);
		   return;
		 }

		 avcore_memcpy(&record.nom_prenom[0],&field_buffer.data[0],field_buffer.field_len);
	   }
	 }

	 if (!db_engine->append_record(db_engine,db_handle,&record))
	 {
	   if(db_engine->error_code != LILLY_DB_DUPLICATE_RECORD_ERROR)
	   {
		 report_event("erreur est survenue lors de la tentative d'ajout d'un record !",mtError,false);
		 return;
	   }
	 }
	 else
	 {
	   count++;

	 }

	 index++;
	 //if (index == 75) asm int 03;
	 //if (index == 4) asm int 03;
	 DocStatLbl->Caption = IntToStr((int)index) + " fiches traitées";

	 Application->ProcessMessages();

	 data = lilly_import_get_next_field(data,&size_left);

	 if ((!data) || ((signed_int)size_left <= 0)) break;
   }

   free(buffer);

   DocStatLbl->Caption = "Operation terminée." + IntToStr((int)count) + " fiches ajoutées.";
   //list->SaveToFile("c:\\patient 2019\\med.txt");
   return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{

	if (OpenDialog1->Execute())
	{
	  RefGainpEdit->Text = OpenDialog1->FileName;
	}

    return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button24Click(TObject *Sender)
{

	if (OpenDialog1->Execute())
	{
	  JobEdit->Text = OpenDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------

static bool __fastcall is_duplicate_job(TStringList *list,const UnicodeString job)
{
  int count = list->Count;


	for (int i = 0; i < count ; i++)
	{
	  if (list->Strings[i] == job) return true;
	}

	return false;
}

void __fastcall TForm1::Button26Click(TObject *Sender)
{
  puchar buffer;
  unsigned_int buffer_size;



   if (JobEdit->Text == "")
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   unsigned_int fhandle = lilly_io_open_file((puchar)JobEdit->Text.c_str(),lilly_io_fmOpen,lilly_io_faRead);

   if ((signed_int)fhandle <= 0)
   {
	 report_event("open file error !",mtError,false);
	 return;
   }

   buffer_size = (unsigned_int)lilly_io_get_file_size_ex(fhandle);

   if ((signed_int)buffer_size <= 0)
   {
	 report_event("get file size error !",mtError,false);
	 return;
   }

   buffer = (puchar)malloc(buffer_size);

   if (!buffer)
   {
	 report_event("application out of memory !",mtError,true);
	 return;
   }

   if (!lilly_io_file_read(fhandle,buffer,buffer_size))
   {
	 report_event("read file error !",mtError,true);
	 return;
   }

   lilly_io_close_file(fhandle);

   unsigned_int count = 0;
   unsigned_int index = 0;

   t_db_field_buffer field_buffer;
   unsigned_int size_left = buffer_size;
   puchar data = lilly_import_get_first_field(buffer,&size_left);

   if ((!data) || ((signed_int)size_left <= 0))
   {
	 report_event("get field error !",mtError,false);
	 return;
   }

   TStringList *list = new TStringList(this);
   UnicodeString job;

   while (TRUE)
   {

	 if (!lilly_import_read_db_field(&field_buffer,3,data,size_left))
	 {
	   report_event("read db field error !",mtError,false);
	   return;
	 }

	 if (!field_buffer.field_len)
	 {
	   job = (PWCHAR)DEFAULT_NAME;
	 }
	 else
	 {
	   job = (PWCHAR)&field_buffer.data;
	 }

	 job = job.LowerCase();

	 if (!is_duplicate_job(list,job))
	 {
	   list->Add(job);
	   count++;
	 }

	 index++;

	 JobStatLbl->Caption = IntToStr((int)index) + " fiches traitées";

	 Application->ProcessMessages();

	 data = lilly_import_get_next_field(data,&size_left);

	 if ((!data) || ((signed_int)size_left <= 0)) break;
   }

   free(buffer);

   list->Sorted = true;

   list->SaveToFile("c:\\patient2k19\\databases\\job_refs.dat");

   delete list;

   JobStatLbl->Caption = "Operation terminée." + IntToStr((int)count) + " entrées ajoutées.";

   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button23Click(TObject *Sender)
{
  unsigned_int error_code;
  struct t_lilly_db_handle *db_handle;

   //bad_gouv = new TStringList;

   if ((PatSrcEdit->Text == "") || (PatDestEdit->Text == ""))
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   PatStatLbl->Caption = "working...";

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\operateurs.lilly"))
   {
	 PatStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\medecins.lilly"))
   {
	 PatStatLbl->Caption = "Erreur chargement moteur et base docteurs !";
	 return;
   }

    orphan_codep = NULL;

   if (lilly_io_file_exists((puchar)L"c:\\patient2k19\\orphelines.txt"))
   {
	 orphan_codep = new TStringList;

	 orphan_codep->LoadFromFile("c:\\patient2k19\\orphelines.txt");
   }

   puchar src = (puchar)PatSrcEdit->Text.c_str();
   puchar dest = (puchar)PatDestEdit->Text.c_str();
   unsigned_int len = PatDestEdit->Text.Length() * 2;
   uchar tmp[260];
   uint32 bad_dates[256];

   memset(&tmp,0,sizeof(tmp));
   memcpy(&tmp,PatDestEdit->Text.c_str(),len);
   memset(&bad_dates,0,sizeof(bad_dates));

   db_handle = patients_import_execute(session_manager,src,(puchar)&tmp,len,0,0,921979,(p_serializer_callback)db_field_serializer,&error_code,(puint32)&bad_dates);
  // db_handle = patients_import_execute(session_manager,(puchar)"12",(puchar)"3",12,0,0,921979,(p_serializer_callback)db_field_serializer,&error_code);

   if (!db_handle)
   {
	 PatStatLbl->Caption = "Une erreur est survenue !";
	 dest = (puchar)PatDestEdit->Text.c_str();
	 PatStatLbl->Caption = (PWCHAR)dest;
   }
   else
   {
	 lilly_db_close_db_handle(db_handle);
	 PatStatLbl->Caption = "Opérations terminées avec succes !";
   }

   TStringList *list = new TStringList(this);

   int i = 0;

   while (true)
   {
	 if (bad_dates[i] == 0) break;
	 list->Add(IntToStr((int)bad_dates[i]));
	 i++;
	 if (i >= sizeof(bad_dates)) break;
   }

   if (i)
   {
	 list->SaveToFile("c:\\patient2k19\\bad dates.txt");
   }

   delete list;

   //bad_gouv->SaveToFile("c:\\patient2k19\\bad gouv.txt");
   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{

	if (OpenDialog1->Execute())
	{
	  PatSrcEdit->Text = OpenDialog1->FileName;
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	 PatDestEdit->Text = SaveDialog1->FileName;
	}

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{

	if (OpenDialog1->Execute())
	{
	  AudiogSrcEdit->Text = OpenDialog1->FileName;
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	  AudiogDestEdit->Text = SaveDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button27Click(TObject *Sender)
{
  unsigned_int error_code;
  struct t_lilly_db_handle *db_handle;


   if ((AudiogSrcEdit->Text == "") || (AudiogDestEdit->Text == ""))
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   AudiogStatLbl->Caption = "working...";

   Application->ProcessMessages();

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\operateurs.lilly"))
   {
	 AudiogStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\patients.lilly"))
   {
	 AudiogStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   puchar src = (puchar)AudiogSrcEdit->Text.c_str();
   puchar dest = (puchar)AudiogDestEdit->Text.c_str();
   unsigned_int len = AudiogDestEdit->Text.Length() * 2;
   uchar tmp[260];

   memset(&tmp,0,sizeof(tmp));
   memcpy(&tmp,AudiogDestEdit->Text.c_str(),len);

   db_handle = audiog_import_execute(session_manager,src,(puchar)&tmp,len,0,0,921979,NULL,&error_code);
  // db_handle = patients_import_execute(session_manager,(puchar)"12",(puchar)"3",12,0,0,921979,(p_serializer_callback)db_field_serializer,&error_code);

   if ((!db_handle) || (error_code != ERROR_SUCCESS))
   {
	 AudiogStatLbl->Caption = "Une erreur est survenue !";
   }
   else
   {
	 lilly_db_close_db_handle(db_handle);
	 AudiogStatLbl->Caption = "Opérations terminées avec succes !";
   }

   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
	if (OpenDialog1->Execute())
	{
	  TympanoSrcEdit->Text = OpenDialog1->FileName;
	}

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
	if (SaveDialog1->Execute())
	{
	  TympanoDestEdit->Text = SaveDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------


static float __fastcall str_to_float_callback(const puchar str)
{
    return StrToFloat((PWCHAR)str);
}

void __fastcall TForm1::Button28Click(TObject *Sender)
{
  unsigned_int error_code;
  struct t_lilly_db_handle *db_handle;


   if ((TympanoSrcEdit->Text == "") || (TympanoDestEdit->Text == ""))
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   TympanoStatLbl->Caption = "working...";

   Application->ProcessMessages();

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\operateurs.lilly"))
   {
	 TympanoStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\patients.lilly"))
   {
	 TympanoStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   puchar src = (puchar)TympanoSrcEdit->Text.c_str();
   puchar dest = (puchar)TympanoDestEdit->Text.c_str();
   unsigned_int len = TympanoDestEdit->Text.Length() * 2;
   uchar tmp[260];

   memset(&tmp,0,sizeof(tmp));
   memcpy(&tmp,TympanoDestEdit->Text.c_str(),len);

   db_handle = tympano_import_execute(session_manager,src,(puchar)&tmp,len,0,0,921979,(p_str_to_float_callback)str_to_float_callback,&error_code);
  // db_handle = patients_import_execute(session_manager,(puchar)"12",(puchar)"3",12,0,0,921979,(p_serializer_callback)db_field_serializer,&error_code);

   if (!db_handle)
   {
	 TympanoStatLbl->Caption = "Une erreur est survenue !";
   }
   else
   {
	 lilly_db_close_db_handle(db_handle);
	 TympanoStatLbl->Caption = "Opérations terminées avec succes !";
   }

   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button21Click(TObject *Sender)
{

	if (OpenDialog1->Execute())
	{
	  GainpSrcEdit->Text = OpenDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button22Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	  GainpDestEdit->Text = SaveDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button29Click(TObject *Sender)
{
  unsigned_int error_code;
  struct t_lilly_db_handle *db_handle;


   if ((GainpSrcEdit->Text == "") || (GainpDestEdit->Text == ""))
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   GainpStatLbl->Caption = "working...";

   Application->ProcessMessages();

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\operateurs.lilly"))
   {
	 GainpStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\patients.lilly"))
   {
	 GainpStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   gainp_proth_refs = new TStringList(this);

   gainp_proth_refs->LoadFromFile("c:\\patient2k19\\databases\\gp_refs.dat");

   if (!gainp_proth_refs->Count)
   {
	 GainpStatLbl->Caption = "Erreur chargement base reférences GP !";
	 return;
   }

   puchar src = (puchar)GainpSrcEdit->Text.c_str();
   puchar dest = (puchar)GainpDestEdit->Text.c_str();
   unsigned_int len = GainpDestEdit->Text.Length() * 2;
   uchar tmp[260];

   memset(&tmp,0,sizeof(tmp));
   memcpy(&tmp,GainpDestEdit->Text.c_str(),len);

   db_handle = gainp_import_execute(session_manager,src,(puchar)&tmp,len,0,0,921979,(p_serializer_callback)db_field_serializer,&error_code);
  // db_handle = patients_import_execute(session_manager,(puchar)"12",(puchar)"3",12,0,0,921979,(p_serializer_callback)db_field_serializer,&error_code);

   if (!db_handle)
   {
	 GainpStatLbl->Caption = "Une erreur est survenue !";
   }
   else
   {
	 lilly_db_close_db_handle(db_handle);
	 GainpStatLbl->Caption = "Opérations terminées avec succes !";
   }

   delete gainp_proth_refs;

   gainp_proth_refs = NULL;

   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{

	if (OpenDialog1->Execute())
	{
	  AvSrcEdit->Text = OpenDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button20Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	  AvDestEdit->Text = SaveDialog1->FileName;
	}

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button30Click(TObject *Sender)
{
  unsigned_int error_code;
  struct t_lilly_db_handle *db_handle;


   if ((AvSrcEdit->Text == "") || (AvDestEdit->Text == ""))
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   AvStatLbl->Caption = "working...";

   Application->ProcessMessages();

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\operateurs.lilly"))
   {
	 AvStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\patients.lilly"))
   {
	 AvStatLbl->Caption = "Erreur chargement moteur et base operateurs !";
	 return;
   }

   puchar src = (puchar)AvSrcEdit->Text.c_str();
   puchar dest = (puchar)AvDestEdit->Text.c_str();
   unsigned_int len = AvDestEdit->Text.Length() * 2;
   uchar tmp[260];

   memset(&tmp,0,sizeof(tmp));
   memcpy(&tmp,AvDestEdit->Text.c_str(),len);

   db_handle = audiovoc_import_execute(session_manager,src,(puchar)&tmp,len,0,0,921979,NULL,&error_code);
  // db_handle = patients_import_execute(session_manager,(puchar)"12",(puchar)"3",12,0,0,921979,(p_serializer_callback)db_field_serializer,&error_code);

   if (!db_handle)
   {
	 AvStatLbl->Caption = "Une erreur est survenue !";
   }
   else
   {
	 lilly_db_close_db_handle(db_handle);
	 AvStatLbl->Caption = "Opérations terminées avec succes !";
   }

   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	  ConsDestEdit->Text = SaveDialog1->FileName;
	}

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
  typedef struct {
				   uint32 id;
				   t_lilly_db_time_stamp_informations time_stamp_infos;
				 } t_consul_engine_record,*p_consul_engine_record;



  unsigned_int error_code,audiog_table_count,tympano_table_count,gp_table_count,audiovoc_table_count;
  struct t_lilly_db_handle *op_db_handle,*med_db_handle,*pat_db_handle,*audiog_db_handle,*tympano_db_handle,*gp_db_handle,*audiovoc_db_handle,*consult_db_handle;
  p_operateur_record op_iterator;
  p_medecin_record med_iterator;
  p_patient_record pat_iterator;
  p_audiogram_record audiog_iterator;
  p_tympanogram_record tympano_iterator;
  p_gainp_record gp_iterator;
  p_audiovoc_record audiovoc_iterator;
  p_lilly_db_engine op_engine,med_engine,pat_engine,audiog_engine,tympano_engine,gp_engine,audiovoc_engine,consultation_engine;
  t_consultation_record consultation_record;
  uint32 op_id;
  t_consul_engine_record audiog_table[128],tympano_table[128],gp_table[128],audiovoc_table[128];


   if (ConsDestEdit->Text == "")
   {
	 report_event("Paramètres incomplets !",mtError,false);
	 return;
   }

   ConsStatLbl->Caption = "working...";

   Application->ProcessMessages();

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\operateurs.lilly"))
   {
	 report_event("cannot load operateurs database !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   op_db_handle = session_manager->request_db_handle(session_manager,OPERATOR_DB_SIGNATURE);

   if (!op_db_handle)
   {
	 report_event("operators request db handle error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   op_engine = session_manager->request_lilly_engine(session_manager,OPERATOR_DB_SIGNATURE);

   if (!op_engine)
   {
	 report_event("operators request engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\medecins.lilly"))
   {
	 report_event("cannot load doctors database !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   med_db_handle = session_manager->request_db_handle(session_manager,DOCTOR_DB_SIGNATURE);

   if (!med_db_handle)
   {
	 report_event("doctors request db handle error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   med_engine = session_manager->request_lilly_engine(session_manager,DOCTOR_DB_SIGNATURE);

   if (!med_engine)
   {
	 report_event("doctors request engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\patients.lilly"))
   {
	 report_event("cannot load patients database !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   pat_db_handle = session_manager->request_db_handle(session_manager,PATIENT_DB_SIGNATURE);

   if (!pat_db_handle)
   {
	 report_event("patients request db handle error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   pat_engine = session_manager->request_lilly_engine(session_manager,PATIENT_DB_SIGNATURE);

   if (!pat_engine)
   {
	 report_event("patients request engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\audiograms.lilly"))
   {
	 report_event("cannot load audiograms database !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   audiog_db_handle = session_manager->request_db_handle(session_manager,AUDIOGRAM_DB_SIGNATURE);

   if (!audiog_db_handle)
   {
	 report_event("audiograms request db handle error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   audiog_engine = session_manager->request_lilly_engine(session_manager,AUDIOGRAM_DB_SIGNATURE);

   if (!audiog_engine)
   {
	 report_event("audiograms request engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\tympanograms.lilly"))
   {
	 report_event("cannot load tympanograms database !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   tympano_db_handle = session_manager->request_db_handle(session_manager,TYMPANOGRAM_DB_SIGNATURE);

   if (!tympano_db_handle)
   {
	 report_event("tympanograms request db handle error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   tympano_engine = session_manager->request_lilly_engine(session_manager,TYMPANOGRAM_DB_SIGNATURE);

   if (!tympano_engine)
   {
	 report_event("tympanograms request engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\gainprot.lilly"))
   {
	 report_event("cannot load gainprot database !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   gp_db_handle = session_manager->request_db_handle(session_manager,GAIN_PROTHETIQUE_DB_SIGNATURE);

   if (!gp_db_handle)
   {
	 report_event("gainprot request db handle error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   gp_engine = session_manager->request_lilly_engine(session_manager,GAIN_PROTHETIQUE_DB_SIGNATURE);

   if (!gp_engine)
   {
	 report_event("gainprot request engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\audiovocs.lilly"))
   {
	 report_event("cannot load audiovocs database !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   audiovoc_db_handle = session_manager->request_db_handle(session_manager,AUDIOMETRIE_VOCALE_DB_SIGNATURE);

   if (!audiovoc_db_handle)
   {
	 report_event("audiovoc request db handle error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   audiovoc_engine = session_manager->request_lilly_engine(session_manager,AUDIOMETRIE_VOCALE_DB_SIGNATURE);

   if (!audiovoc_engine)
   {
	 report_event("audiovoc request engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   consultation_engine = session_manager->register_lilly_engine(session_manager,CONSULTATIONS_DB_SIGNATURE);

   if (!consultation_engine)
   {
	 report_event("register consultation engine error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   unsigned_int db_path_len;
   uchar db_path[260 * 2];

   db_path_len = ConsDestEdit->Text.Length() * 2;

   *(puint16)&db_path[db_path_len] = 0;

   avcore_memcpy(&db_path,(puchar)ConsDestEdit->Text.c_str(),db_path_len);

   consult_db_handle = consultation_engine->new_database(consultation_engine,(puchar)&db_path,db_path_len,0,0,9021979);

   if (!consult_db_handle)
   {
	 report_event("Consultation database creation error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   uint64 offset;
   int pat_rec_index,consult_rec_index;
   t_lilly_db_time_stamp_informations pat_time_stamp_infos;

   pat_rec_index = 0;

   consult_rec_index = 0;

   pat_iterator = (p_patient_record)lilly_db_get_first_record(pat_db_handle);

   boogie :

   audiog_table_count = 0;
   tympano_table_count = 0;
   gp_table_count = 0;
   audiovoc_table_count = 0;

   if (!pat_iterator)
   {
	 if (lilly_db_get_last_error(pat_db_handle) != ERROR_SUCCESS)
	 {
	   report_event("patient get first record error !",mtError,false);
	   ConsStatLbl->Caption = "erreur";
	 }
	 else report_event("travail terminé avec succès.",mtInformation,false);

	 return;
   }

   offset = lilly_db_get_current_record_offset(pat_db_handle);

   lilly_db_get_record_time_stamp_infos(pat_db_handle,offset,&pat_time_stamp_infos);

   pat_rec_index++;

   //if (pat_rec_index == 1358) asm int 03;

   audiog_iterator = (p_audiogram_record)lilly_db_get_first_record(audiog_db_handle);

   if (!audiog_iterator)
   {
	 report_event("audiograms get first record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   while (true)
   {
	 if (audiog_iterator->code_patient == pat_iterator->code_patient.unique_index)
	 {
	   audiog_table[audiog_table_count].id = audiog_iterator->code_audiogram.unique_index;

	   offset = lilly_db_get_current_record_offset(audiog_db_handle);

	   if (!lilly_db_get_record_time_stamp_infos(audiog_db_handle,offset,&audiog_table[audiog_table_count].time_stamp_infos))
	   {
		 report_event("audiograms get timestamp infos error !",mtError,false);
		 ConsStatLbl->Caption = "erreur";
		 return;
	   }

	   audiog_table_count++;

	 }

	 audiog_iterator = (p_audiogram_record)lilly_db_get_next_record(audiog_db_handle);

	 if (!audiog_iterator) break;
   }

   if (lilly_db_get_last_error(audiog_db_handle) != ERROR_SUCCESS)
   {
	 report_event("audiograms get next record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   tympano_iterator = (p_tympanogram_record)lilly_db_get_first_record(tympano_db_handle);

   if (!tympano_iterator)
   {
	 report_event("tympangrams get first record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   //if (pat_iterator->code_patient.unique_index == 2871) asm int 03;

   while (true)
   {
	 if (tympano_iterator->code_patient == pat_iterator->code_patient.unique_index)
	 {
	   tympano_table[tympano_table_count].id = tympano_iterator->code_tympanogram.unique_index;

	   offset = lilly_db_get_current_record_offset(tympano_db_handle);

	   if (!lilly_db_get_record_time_stamp_infos(tympano_db_handle,offset,&tympano_table[tympano_table_count].time_stamp_infos))
	   {
		 report_event("tympanograms get timestamp infos error !",mtError,false);
		 ConsStatLbl->Caption = "erreur";
		 return;
	   }

	   tympano_table_count++;

     }

	 tympano_iterator = (p_tympanogram_record)lilly_db_get_next_record(tympano_db_handle);

	 if (!tympano_iterator) break;
   }

   if (lilly_db_get_last_error(tympano_db_handle) != ERROR_SUCCESS)
   {
	 report_event("tympanograms get next record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   gp_iterator = (p_gainp_record)lilly_db_get_first_record(gp_db_handle);

   if (!gp_iterator)
   {
	 report_event("gainp get first record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   while (true)
   {
	 if (gp_iterator->code_patient == pat_iterator->code_patient.unique_index)
	 {
	   gp_table[gp_table_count].id = gp_iterator->code_gainp.unique_index;

	   offset = lilly_db_get_current_record_offset(gp_db_handle);

	   if (!lilly_db_get_record_time_stamp_infos(gp_db_handle,offset,&gp_table[gp_table_count].time_stamp_infos))
	   {
		 report_event("gainp get timestamp infos error !",mtError,false);
		 ConsStatLbl->Caption = "erreur";
		 return;
	   }

	   gp_table_count++;

	 }

	 gp_iterator = (p_gainp_record)lilly_db_get_next_record(gp_db_handle);

	 if (!gp_iterator) break;
   }

   if (lilly_db_get_last_error(gp_db_handle) != ERROR_SUCCESS)
   {
     report_event("gainp get next record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   audiovoc_iterator = (p_audiovoc_record)lilly_db_get_first_record(audiovoc_db_handle);

   if (!audiovoc_iterator)
   {
     report_event("audiovoc get first record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   while (true)
   {
	 if (audiovoc_iterator->code_patient == pat_iterator->code_patient.unique_index)
	 {
	   audiovoc_table[audiovoc_table_count].id = audiovoc_iterator->code_audiovoc.unique_index;

	   offset = lilly_db_get_current_record_offset(audiovoc_db_handle);

	   if (!lilly_db_get_record_time_stamp_infos(audiovoc_db_handle,offset,&audiovoc_table[audiovoc_table_count].time_stamp_infos))
	   {
		 report_event("audiovoc get timestamp infos error !",mtError,false);
		 ConsStatLbl->Caption = "erreur";
		 return;
	   }

	   audiovoc_table_count++;
	 }

	 audiovoc_iterator = (p_audiovoc_record)lilly_db_get_next_record(audiovoc_db_handle);

	 if (!audiovoc_iterator) break;
   }

   if (lilly_db_get_last_error(audiovoc_db_handle) != ERROR_SUCCESS)
   {
	 report_event("audiovoc get next record error !",mtError,false);
	 ConsStatLbl->Caption = "erreur";
	 return;
   }

   avcore_memset(&consultation_record,0,sizeof(consultation_record));

   if (audiog_table_count)
   {
	 for (int i = 0; i < audiog_table_count; i++)
	 {
	   consultation_record.audiogram_id = audiog_table[i].id;
	   consultation_record.patient_id = pat_iterator->code_patient.unique_index;
       consultation_record.medecin_id = pat_iterator->code_medecin;

	   audiog_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(audiog_table[i].time_stamp_infos.creation_stamp.operator_id,pat_time_stamp_infos.creation_stamp.operator_id);

	   for (int x = 0; x < tympano_table_count; x++)
	   {
		 if ((tympano_table[x].id) && (tympano_table[x].time_stamp_infos.creation_stamp.time_stamp.day == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.day) &&
		 (tympano_table[x].time_stamp_infos.creation_stamp.time_stamp.month == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.month) &&
		 (tympano_table[x].time_stamp_infos.creation_stamp.time_stamp.year == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.year))
		 {
		   consultation_record.tympanogram_id = tympano_table[x].id;
		   audiog_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(audiog_table[i].time_stamp_infos.creation_stamp.operator_id,tympano_table[x].time_stamp_infos.creation_stamp.operator_id);
		   tympano_table[x].id = 0;
		   break;
		 }
	   }

	   for (int x = 0; x < gp_table_count; x++)
	   {
		 if ((gp_table[x].id) && (gp_table[x].time_stamp_infos.creation_stamp.time_stamp.day == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.day) &&
		 (gp_table[x].time_stamp_infos.creation_stamp.time_stamp.month == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.month) &&
		 (gp_table[x].time_stamp_infos.creation_stamp.time_stamp.year == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.year))
		 {
		   consultation_record.gainp_id = gp_table[x].id;
		   audiog_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(audiog_table[i].time_stamp_infos.creation_stamp.operator_id,gp_table[x].time_stamp_infos.creation_stamp.operator_id);
		   gp_table[x].id = 0;
		   break;
		 }
	   }

	   for (int x = 0; x < audiovoc_table_count; x++)
	   {
		 if ((audiovoc_table[x].id) && (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.day == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.day) &&
		 (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.month == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.month) &&
		 (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.year == audiog_table[i].time_stamp_infos.creation_stamp.time_stamp.year))
		 {
		   consultation_record.audiovoc_id = audiovoc_table[x].id;
		   audiog_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(audiog_table[i].time_stamp_infos.creation_stamp.operator_id,audiovoc_table[x].time_stamp_infos.creation_stamp.operator_id);
		   audiovoc_table[x].id = 0;
		   break;
		 }
	   }

	   if (!consultation_engine->append_record(consultation_engine,consult_db_handle,&consultation_record))
	   {
		 report_event("consultation append record error !",mtError,false);
		 ConsStatLbl->Caption = "erreur";
		 return;
	   }

	   consult_rec_index++;

	   ConsStatLbl->Caption = IntToStr(pat_rec_index) + " / " + IntToStr(consult_rec_index) + " consultations ajoutées";

	   Application->ProcessMessages();

	   offset = lilly_db_get_current_record_offset(consult_db_handle);

	   if (!lilly_db_set_record_creation_time(consult_db_handle,offset,&audiog_table[i].time_stamp_infos.creation_stamp,true))
	   {
		 report_event("consultation set operator error !",mtError,false);
		 ConsStatLbl->Caption = "erreur";
		 return;
	   }
	 }
   }

   if (tympano_table_count)
   {
	 for (int i = 0; i < tympano_table_count; i++)
	 {
	   if (tympano_table[i].id)
	   {
		 avcore_memset(&consultation_record,0,sizeof(consultation_record));

		 consultation_record.tympanogram_id = tympano_table[i].id;
		 consultation_record.patient_id = pat_iterator->code_patient.unique_index;
		 consultation_record.medecin_id = pat_iterator->code_medecin;

		 tympano_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(tympano_table[i].time_stamp_infos.creation_stamp.operator_id,pat_time_stamp_infos.creation_stamp.operator_id);

		 for (int x = 0; x < gp_table_count; x++)
		 {
		   if ((gp_table[x].id) && (gp_table[x].time_stamp_infos.creation_stamp.time_stamp.day == tympano_table[i].time_stamp_infos.creation_stamp.time_stamp.day) &&
		   (gp_table[x].time_stamp_infos.creation_stamp.time_stamp.month == tympano_table[i].time_stamp_infos.creation_stamp.time_stamp.month) &&
		   (gp_table[x].time_stamp_infos.creation_stamp.time_stamp.year == tympano_table[i].time_stamp_infos.creation_stamp.time_stamp.year))
		   {
			 consultation_record.gainp_id = gp_table[x].id;

			 tympano_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(tympano_table[i].time_stamp_infos.creation_stamp.operator_id,gp_table[x].time_stamp_infos.creation_stamp.operator_id);

			 gp_table[x].id = 0;
			 break;
		   }
		 }

		 for (int x = 0; x < audiovoc_table_count; x++)
		 {
		   if ((audiovoc_table[x].id) && (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.day == tympano_table[i].time_stamp_infos.creation_stamp.time_stamp.day) &&
		   (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.month == tympano_table[i].time_stamp_infos.creation_stamp.time_stamp.month) &&
		   (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.year == tympano_table[i].time_stamp_infos.creation_stamp.time_stamp.year))
		   {
			 consultation_record.audiovoc_id = audiovoc_table[x].id;

			 tympano_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(tympano_table[i].time_stamp_infos.creation_stamp.operator_id,audiovoc_table[x].time_stamp_infos.creation_stamp.operator_id);

			 audiovoc_table[x].id = 0;
			 break;
		   }
		 }

		 if (!consultation_engine->append_record(consultation_engine,consult_db_handle,&consultation_record))
		 {
		   report_event("consultation append record error !",mtError,false);
		   ConsStatLbl->Caption = "erreur";
		   return;
		 }

		 consult_rec_index++;

		 ConsStatLbl->Caption = IntToStr(pat_rec_index) + " / " + IntToStr(consult_rec_index) + " consultations ajoutées";

		 Application->ProcessMessages();

		 offset = lilly_db_get_current_record_offset(consult_db_handle);

		 if (!lilly_db_set_record_creation_time(consult_db_handle,offset,&tympano_table[i].time_stamp_infos.creation_stamp,true))
		 {
		   report_event("consultation set operator error !",mtError,false);
		   ConsStatLbl->Caption = "erreur";
		   return;
		 }
	   }
	 }
   }

   if (gp_table_count)
   {
	 for (int i = 0; i < gp_table_count; i++)
	 {
	   if (gp_table[i].id)
	   {
		 avcore_memset(&consultation_record,0,sizeof(consultation_record));

		 consultation_record.gainp_id = gp_table[i].id;
		 consultation_record.patient_id = pat_iterator->code_patient.unique_index;
		 consultation_record.medecin_id = pat_iterator->code_medecin;

		 gp_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(gp_table[i].time_stamp_infos.creation_stamp.operator_id,pat_time_stamp_infos.creation_stamp.operator_id);

		 for (int x = 0; x < audiovoc_table_count; x++)
		 {
		   if ((audiovoc_table[x].id) && (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.day == gp_table[i].time_stamp_infos.creation_stamp.time_stamp.day) &&
		   (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.month == gp_table[i].time_stamp_infos.creation_stamp.time_stamp.month) &&
		   (audiovoc_table[x].time_stamp_infos.creation_stamp.time_stamp.year == gp_table[i].time_stamp_infos.creation_stamp.time_stamp.year))
		   {
			 consultation_record.audiovoc_id = audiovoc_table[x].id;

			 gp_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(gp_table[i].time_stamp_infos.creation_stamp.operator_id,audiovoc_table[x].time_stamp_infos.creation_stamp.operator_id);

			 audiovoc_table[x].id = 0;
			 break;
		   }
		 }

		 if (!consultation_engine->append_record(consultation_engine,consult_db_handle,&consultation_record))
		 {
		   report_event("consultation append record error !",mtError,false);
		   ConsStatLbl->Caption = "erreur";
		   return;
		 }

		 consult_rec_index++;

		 ConsStatLbl->Caption = IntToStr(pat_rec_index) + " / " + IntToStr(consult_rec_index) + " consultations ajoutées";

		 Application->ProcessMessages();

		 offset = lilly_db_get_current_record_offset(consult_db_handle);

		 //if (gp_table[i].time_stamp_infos.creation_stamp.time_stamp.year == 2099) asm int 03;

		 if (!lilly_db_set_record_creation_time(consult_db_handle,offset,&gp_table[i].time_stamp_infos.creation_stamp,true))
		 {
		   report_event("consultation set operator error !",mtError,false);
		   ConsStatLbl->Caption = "erreur";
		   return;
		 }
	   }
	 }
   }

   if (audiovoc_table_count)
   {
	 for (int i = 0; i < audiovoc_table_count; i++)
	 {
	   if (audiovoc_table[i].id)
	   {
		 consultation_record.audiovoc_id = audiovoc_table[i].id;
		 consultation_record.patient_id = pat_iterator->code_patient.unique_index;
		 consultation_record.medecin_id = pat_iterator->code_medecin;

		 audiovoc_table[i].time_stamp_infos.creation_stamp.operator_id = MACRO_MAX_VALUE(audiovoc_table[i].time_stamp_infos.creation_stamp.operator_id,pat_time_stamp_infos.creation_stamp.operator_id);

		 if (!consultation_engine->append_record(consultation_engine,consult_db_handle,&consultation_record))
		 {
		   report_event("consultation append record error !",mtError,false);
		   ConsStatLbl->Caption = "erreur";
		   return;
		 }

		 consult_rec_index++;

		 ConsStatLbl->Caption = IntToStr(pat_rec_index) + " / " + IntToStr(consult_rec_index) + " consultations ajoutées";

		 Application->ProcessMessages();

		 offset = lilly_db_get_current_record_offset(consult_db_handle);

		 if (!lilly_db_set_record_creation_time(consult_db_handle,offset,&audiovoc_table[i].time_stamp_infos.creation_stamp,true))
		 {
		   report_event("consultation set operator error !",mtError,false);
		   ConsStatLbl->Caption = "erreur";
		   return;
		 }
	   }
	 }
   }

   pat_iterator = (p_patient_record)lilly_db_get_next_record(pat_db_handle);

   //if (pat_iterator->code_patient.unique_index == 39643) asm int 03;
   goto boogie;

   return;

}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::Button32Click(TObject *Sender)
{
  unsigned_int error_code;
  struct t_lilly_db_handle *pat_db_handle,*consult_db_handle;
  p_patient_record pat_iterator;
  p_consultation_record consult_iterator;


   OrphPatStatLbl->Caption = "working...";

   Application->ProcessMessages();

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\patients.lilly"))
   {
	 report_event("cannot load patients database !",mtError,false);
	 OrphPatStatLbl->Caption = "erreur";
	 return;
   }

   pat_db_handle = session_manager->request_db_handle(session_manager,PATIENT_DB_SIGNATURE);

   if (!pat_db_handle)
   {
	 report_event("patients request db handle error !",mtError,false);
	 OrphPatStatLbl->Caption = "erreur";
	 return;
   }

   if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\consultations.lilly"))
   {
	 report_event("cannot load consultation database !",mtError,false);
	 OrphPatStatLbl->Caption = "erreur";
	 return;
   }

   consult_db_handle = session_manager->request_db_handle(session_manager,CONSULTATIONS_DB_SIGNATURE);

   if (!consult_db_handle)
   {
	 report_event("consultations request db handle error !",mtError,false);
	 OrphPatStatLbl->Caption = "erreur";
	 return;
   }

   int index = 0;

   TStringList *list = new TStringList;

   pat_iterator = (p_patient_record)lilly_db_get_first_record(pat_db_handle);

   while (true)
   {
	 consult_iterator = (p_consultation_record)lilly_db_get_first_record(consult_db_handle);

	 bool found = false;

	 while (true)
	 {
	   if (consult_iterator->patient_id == pat_iterator->code_patient.unique_index)
	   {
		 found = true;
		 break;
	   }

	   consult_iterator = (p_consultation_record)lilly_db_get_next_record(consult_db_handle);

	   if (!consult_iterator) break;
	 }

	 if (!found)
	 {
	   list->Add(IntToStr((int)pat_iterator->code_patient.unique_index));
	 }

	 pat_iterator = (p_patient_record)lilly_db_get_next_record(pat_db_handle);

	 if (!pat_iterator) break;

	 OrphPatStatLbl->Caption = "processing " + IntToStr(index++);

	 Application->ProcessMessages();
   }

   if (list->Count)
   {
	 list->SaveToFile("c:\\patient2k19\\orphelines.txt");
   }

   list->Clear();

   delete list;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button31Click(TObject *Sender)
{

	if (OpenDialog1->Execute())
	{
	  SortSrcEdit->Text = OpenDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button33Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	  SortDestEdit->Text = SaveDialog1->FileName;
	}

	return;
}
//---------------------------------------------------------------------------

typedef struct {
				 uint64 offset;
				 uint64 time;
				 uint32 op_id;
			   } t_entry,*p_entry;


static __inline void swap(const p_entry a, p_entry b)
{
  t_entry t = *a;

	*a = *b;

	*b = t;

	return;
}

/* This function is same in both iterative and recursive*/
static int partition(const p_entry arr, int l, int h)
{
	p_entry x = &arr[h];
    int i = (l - 1);

	for (int j = l; j <= h - 1; j++)
	{
	  if (arr[j].time <= x->time)
	  {
		i++;
		swap(&arr[i], &arr[j]);
	  }
    }

	swap(&arr[i + 1], &arr[h]);

	return (i + 1);
}

static void quick_sort(const p_entry arr,int l,int h)
{
  int top,p;
   // Create an auxiliary stack
  int *stack;

	stack = (int *)malloc((h - l) + 1);

	// initialize top of stack
	top = -1;

    // push initial values of l and h to stack
	stack[++top] = l;
	stack[++top] = h;

    // Keep popping from stack while is not empty
	while (top >= 0)
	{
        // Pop h and l
	   h = stack[top--];
	   l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
		p = partition(arr, l, h);

        // If there are elements on left side of pivot,
        // then push left side to stack
		if (p - 1 > l)
		{
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
	}

	return;
}

void __fastcall TForm1::Button34Click(TObject *Sender)
{
  struct t_lilly_db_handle *src_db_handle,*dest_db_handle;
  p_consultation_record iterator;
  p_lilly_db_session_manager dest_session_manager;
  p_lilly_db_engine engine;
  unsigned_int db_path_len,index,error_code;
  uint64 offset;
  p_entry table;
  t_lilly_db_database_infos db_infos;
  t_lilly_db_time_stamp_informations time_stamp_infos;
  uchar db_path[260 * 2];


	if ((SortSrcEdit->Text == "") || (SortDestEdit->Text == ""))
	{
	  SortStateLbl->Caption = "Vous n'avez pas sépcifié les chemins";
	  return;
	}

	SortStateLbl->Caption = "working...";

	if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\consultations.lilly"))
	{
	  report_event("cannot load consultation database !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	src_db_handle = session_manager->request_db_handle(session_manager,CONSULTATIONS_DB_SIGNATURE);

	if (!src_db_handle)
	{
	  report_event("consultations request db handle error !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	if (!lilly_db_get_database_informations(src_db_handle,&db_infos))
	{
	  report_event("Get DB infos error !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	if ((int32)db_infos.record_count <= 0)
	{
	  report_event("Src database corrupted or empty !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	table = (p_entry)malloc(db_infos.record_count * sizeof(*table));

	if (!table)
	{
	  report_event("Application out of memory !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	iterator = (p_consultation_record)lilly_db_get_first_record(src_db_handle);

	if (!iterator)
	{
	  report_event("Get First Record error !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	index = 0;

	while (true)
	{
	  table[index].offset = lilly_db_get_current_record_offset(src_db_handle);

	  if (!lilly_db_get_record_time_stamp_infos(src_db_handle,table[index].offset,&time_stamp_infos))
	  {
		report_event("Get Record TimeStamp Error !",mtError,false);
		SortStateLbl->Caption = "erreur";
		return;
	  }

	  table[index].time = *(puint64)&time_stamp_infos.creation_stamp.time_stamp;

	  table[index++].op_id = time_stamp_infos.creation_stamp.operator_id;

	  SortStateLbl->Caption = IntToStr((int)index) + " / " + IntToStr((int)db_infos.record_count);

	  Application->ProcessMessages();

	  iterator = (p_consultation_record)lilly_db_get_next_record(src_db_handle);

	  if (!iterator) break;
	}

	if (lilly_db_get_last_error(src_db_handle) != ERROR_SUCCESS)
	{
	  report_event("Get NextRecord Error !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
    }

	dest_session_manager = get_new_session_manager(921979,&error_code);

	engine = dest_session_manager->register_lilly_engine(dest_session_manager,CONSULTATIONS_DB_SIGNATURE);

	if (!engine)
	{
	  report_event("register consultation engine error !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	SortStateLbl->Caption = "Sorting database...";

	Application->ProcessMessages();

	quick_sort(table,0,db_infos.record_count - 1);

	db_path_len = SortDestEdit->Text.Length() * 2;

	*(puint16)&db_path[db_path_len] = 0;

	avcore_memcpy(&db_path,(puchar)SortDestEdit->Text.c_str(),db_path_len);

	dest_db_handle = engine->new_database(engine,(puchar)&db_path,db_path_len,0,0,9021979);

	if (!dest_db_handle)
	{
	  report_event("Consultation database creation error !",mtError,false);
	  SortStateLbl->Caption = "erreur";
	  return;
	}

	for (unsigned_int i = 0; i < (unsigned_int)db_infos.record_count; i++)
	{
	  iterator = (p_consultation_record)lilly_db_read_record(src_db_handle,CONSULTATION_RECORD_SIZE,table[i].offset);

	  if (!iterator)
	  {
		report_event("ReadRecod error !",mtError,false);
		SortStateLbl->Caption = "erreur";
		return;
	  }

	  if (!engine->append_record(engine,dest_db_handle,iterator))
	  {
		report_event("AppendRecord error !",mtError,false);
		SortStateLbl->Caption = "erreur";
		return;
	  }

	  offset = lilly_db_get_current_record_offset(dest_db_handle);

	  if (!lilly_db_get_record_time_stamp_infos(dest_db_handle,offset,&time_stamp_infos))
	  {
		report_event("GetTimeStampInfos error !",mtError,false);
		SortStateLbl->Caption = "erreur";
		return;
	  }

	  time_stamp_infos.creation_stamp.operator_id = table[i].op_id;

	  *(puint64)&time_stamp_infos.creation_stamp.time_stamp = table[i].time;

	  if (!lilly_db_set_record_creation_time(dest_db_handle,offset,&time_stamp_infos.creation_stamp,true))
	  {
		report_event("SetCreationTime error !",mtError,false);
		SortStateLbl->Caption = "erreur";
		return;
	  }

	  SortStateLbl->Caption = "Adding : " + IntToStr((int)i + 1) + " / " + IntToStr((int)db_infos.record_count);

	  Application->ProcessMessages();
	}

	SortStateLbl->Caption = SortStateLbl->Caption + " Job done !";


	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  static const uint32 db_id[8] = {OPERATOR_DB_SIGNATURE,PATIENT_DB_SIGNATURE,DOCTOR_DB_SIGNATURE,AUDIOGRAM_DB_SIGNATURE,TYMPANOGRAM_DB_SIGNATURE,
								  GAIN_PROTHETIQUE_DB_SIGNATURE,AUDIOMETRIE_VOCALE_DB_SIGNATURE,CONSULTATIONS_DB_SIGNATURE};

  struct t_lilly_db_handle *db_handle;
  p_lilly_db_engine engine;
  t_lilly_db_database_infos db_infos;


	if (DbTypeCombo->ItemIndex == -1)
	{
	  report_event("Veuillez spécifier un DB TYPE !",mtWarning,false);
	  return;
	}

	if (!OpenDialog1->Execute()) return;

	DbPathEdit->Text = OpenDialog1->FileName;

	if (!session_manager->load_lilly_engine(session_manager,(puchar)DbPathEdit->Text.c_str()))
	{
	  report_event("cannot load consultation database !",mtError,false);
	  return;
	}

	db_handle = session_manager->request_db_handle(session_manager,db_id[DbTypeCombo->ItemIndex]);

	if (!db_handle)
	{
	  report_event("Request db handle error !",mtError,false);
	  return;
	}

	if (!lilly_db_get_database_informations(db_handle,&db_infos))
	{
	  report_event("Get DB Infos error !",mtError,false);
	  return;
	}

	session_manager->release_lilly_engine(session_manager,db_id[DbTypeCombo->ItemIndex]);

	SessionIDLbl->Text = IntToStr((int)db_infos.session_id);

	CryptChk->Checked = db_infos.encryption;
	CompressChk->Checked = db_infos.compression;
	CrcChk->Checked = db_infos.integrity_check;
	MacLockChk->Checked = db_infos.mac_address_lock;
	SupUserChk->Checked = db_infos.power_user_only;
	SessionLockChk->Checked = db_infos.session_id_lock;
	ReadOnlyChk->Checked = db_infos.read_only;
	IndexChk->Checked = db_infos.indexing;
	CrashChk->Checked = db_infos.crash_flag;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button35Click(TObject *Sender)
{
  static const uint32 db_id[8] = {OPERATOR_DB_SIGNATURE,PATIENT_DB_SIGNATURE,DOCTOR_DB_SIGNATURE,AUDIOGRAM_DB_SIGNATURE,TYMPANOGRAM_DB_SIGNATURE,
								  GAIN_PROTHETIQUE_DB_SIGNATURE,AUDIOMETRIE_VOCALE_DB_SIGNATURE,CONSULTATIONS_DB_SIGNATURE};

  struct t_lilly_db_handle *db_handle;
  p_lilly_db_engine engine;
  t_lilly_db_database_infos db_infos;


	if (MessageDlg("Appliquer les changements ?",mtWarning,TMsgDlgButtons() << mbYes << mbNo,0) == mrNo) return;

	if (DbTypeCombo->ItemIndex == -1)
	{
	  report_event("Veuillez spécifier un DB TYPE !",mtWarning,false);
	  return;
	}

	if (DbPathEdit->Text == "")
	{
	  report_event("Veuillez spécifier une base !",mtError,false);
	  return;
	}

	if (!session_manager->load_lilly_engine(session_manager,(puchar)DbPathEdit->Text.c_str()))
	{
	  report_event("cannot load consultation database !",mtError,false);
	  return;
	}

	db_handle = session_manager->request_db_handle(session_manager,db_id[DbTypeCombo->ItemIndex]);

	if (!db_handle)
	{
	  report_event("Request db handle error !",mtError,false);
	  return;
	}

	if (!lilly_db_get_database_informations(db_handle,&db_infos))
	{
	  report_event("Get DB Infos error !",mtError,false);
	  return;
	}

	db_infos.session_id = StrToInt(SessionIDLbl->Text);

	db_infos.encryption = CryptChk->Checked;
	db_infos.compression = CompressChk->Checked;
	db_infos.integrity_check = CrcChk->Checked;
	db_infos.mac_address_lock = MacLockChk->Checked;
	db_infos.power_user_only = SupUserChk->Checked;
	db_infos.session_id_lock = SessionLockChk->Checked;
	db_infos.read_only = ReadOnlyChk->Checked;
	db_infos.indexing = IndexChk->Checked;
	db_infos.crash_flag = CrashChk->Checked;

	if (!lilly_db_set_database_informations(db_handle,&db_infos))
	{
	  report_event("Set DB Infos error !",mtError,false);
	  return;
	}

	session_manager->release_lilly_engine(session_manager,db_id[DbTypeCombo->ItemIndex]);

	report_event("Nouveaux paramètres appliqués avec succès",mtInformation,false);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button36Click(TObject *Sender)
{

	if (SaveDialog1->Execute())
	{
	  LastConsEdit->Text = SaveDialog1->FileName;
	}

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button37Click(TObject *Sender)
{
  struct t_lilly_db_handle *consult_db_handle,*patient_db_handle;
  p_consultation_record consult_iterator;
  p_patient_record patient_iterator;
  unsigned_int db_path_len,index,error_code;
  p_lilly_db_engine db_engine;
  uint64 offset;
  t_date_time max_date;
  t_lilly_db_database_infos db_infos;
  t_lilly_db_time_stamp_informations time_stamp_infos;
  t_patient_record record;
  uint32 max_id;



	if (LastConsEdit->Text == "")
	{
	  SortStateLbl->Caption = "Vous n'avez pas sépcifié le chemin de destination";
	  return;
	}

	LastConsStatLbl->Caption = "working...";

	if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\consultations.lilly"))
	{
	  report_event("cannot load consultation database !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	consult_db_handle = session_manager->request_db_handle(session_manager,CONSULTATIONS_DB_SIGNATURE);

	if (!consult_db_handle)
	{
	  report_event("consultations request db handle error !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	if (!lilly_db_get_database_informations(consult_db_handle,&db_infos))
	{
	  report_event("Get Consultations DB infos error !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	if ((int32)db_infos.record_count <= 0)
	{
	  report_event("Consultations database corrupted or empty !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	if (!session_manager->load_lilly_engine(session_manager,(puchar)L"c:\\patient2k19\\databases\\patients.lilly"))
	{
	  report_event("cannot load patients database !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	patient_db_handle = session_manager->request_db_handle(session_manager,PATIENT_DB_SIGNATURE);

	if (!patient_db_handle)
	{
	  report_event("Patients request db handle error !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	if (!lilly_db_get_database_informations(patient_db_handle,&db_infos))
	{
	  report_event("Get Patients DB infos error !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	if ((int32)db_infos.record_count <= 0)
	{
	  report_event("Patients database corrupted or empty !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	patient_iterator = (p_patient_record)lilly_db_get_first_record(patient_db_handle);

	if (!patient_iterator)
	{
	  report_event("Get First Patient Record error !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	db_engine = session_manager->request_lilly_engine(session_manager,PATIENT_DB_SIGNATURE);

	if (!db_engine)
	{
	  report_event("Request patient db engine error !",mtError,false);
	  LastConsStatLbl->Caption = "erreur";
	  return;
	}

	index = 0;

	while (true)
	{
	  consult_iterator = (p_consultation_record)lilly_db_get_first_record(consult_db_handle);

	  if (!consult_iterator)
	  {
		report_event("Get First Consultation Record error !",mtError,false);
		LastConsStatLbl->Caption = "erreur";
		return;
	  }

	 // if (index == 36012) asm int 03;

	  *(puint64)&max_date = 0;

	  max_id = -1;

	  while (true)
	  {
		if (consult_iterator->patient_id == patient_iterator->code_patient.unique_index)
		{
		  offset = lilly_db_get_current_record_offset(consult_db_handle);

		  if (!lilly_db_get_record_time_stamp_infos(consult_db_handle,offset,&time_stamp_infos))
		  {
			report_event("Get time stamp infos error !",mtError,false);
			LastConsStatLbl->Caption = "erreur";
			return;
		  }

		  if (lilly_compare_dates(&max_date,&time_stamp_infos.creation_stamp.time_stamp) == DATE_IS_LESS)
		  {
			max_date = time_stamp_infos.creation_stamp.time_stamp;
			max_id = consult_iterator->code_consultation.unique_index;
		  }
		}

		consult_iterator = (p_consultation_record)lilly_db_get_next_record(consult_db_handle);

		if (!consult_iterator) break;
	  }

	  if (lilly_db_get_last_error(consult_db_handle) != ERROR_SUCCESS)
	  {
		report_event("Get Next Consultation error !",mtError,false);
		LastConsStatLbl->Caption = "erreur";
		return;
	  }

	  if (max_id == -1)
	  {
		report_event("index was not found error !",mtError,false);
		LastConsStatLbl->Caption = "erreur";
		return;
	  }

	  avcore_memcpy(&record,patient_iterator,sizeof(*patient_iterator));

	  record.last_consultation_id = max_id;

	  offset = lilly_db_get_current_record_offset(patient_db_handle);

	  if (!db_engine->edit_record(db_engine,patient_db_handle,&record,offset))
	  {
        report_event("edit record error !",mtError,false);
		LastConsStatLbl->Caption = "erreur";
        return;
      }

	  LastConsStatLbl->Caption = "Processing " + IntToStr((int)index++) + " / " + IntToStr((int)db_infos.record_count);

	  patient_iterator = (p_patient_record)lilly_db_get_next_record(patient_db_handle);

	  if (!patient_iterator) break;

	  Application->ProcessMessages();
	}

	session_manager->release_lilly_engine(session_manager,PATIENT_DB_SIGNATURE);

	return;
}
//---------------------------------------------------------------------------

