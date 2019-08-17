//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <JPEG.hpp>

#include "Unit1.h"

#include <cmnfnc.h>

#include <lilly_db2.h>
#include <lilly_utils.h>
#include <lilly_os.h>
#include <lilly_io.h>
#include <db_signatures.h>


#include "Unit2.h"
#include "Unit4.h"
#include "Unit6.h"

#include "common.hpp"
#include "audiogram.hpp"
#include "tympano.hpp"
#include "consultation.hpp"
#include "patient.hpp"
#include "audiovoc.hpp"
#include "gainp.hpp"

#include "demographic_stats.h"
#include "geographic_stats.h"

#include "config_manager.hpp"

#include "Unit7.h"
#include "Unit16.h"
#include "Unit17.h"
#include "Unit18.h"

								//$00DBB7FF
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// INITIALIZATIONS et DESTRUCTIONS

TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{

    initialize_session();

	DoubleBuffered = true;

	PatientConsultationsTable = (p_offsets_table)malloc(sizeof(*PatientConsultationsTable));

    if (!PatientConsultationsTable)
    {
      report_event(error_code_to_string(MEM_ALLOC_ERROR),mtError,true);
      return;
    }

	avcore_memset(PatientConsultationsTable,0,sizeof(*PatientConsultationsTable));

	Navigate(8,8);
	//PageControl1->ActivePageIndex = 8;

}

//---------------------------------------------------------------------------


void __fastcall TForm1::initialize_session(void)
{
  unsigned_int error_code,session_id;
  bool activate_splash;
  UnicodeString app_path;


    //app_path = ExtractFilePath(ParamStr(0));

    app_path = L"C:\\Patient2k19\\databases\\";

    if (!FileExists(app_path + "\\db_session_config.ini",false))
    {
      app_path = "Echec lors de l'initialisation du logiciel ! le fichier [db_session_config.ini] est introuvable. \n\r\n\r";
      app_path = app_path + "Veuillez re-installer le logiciel afin de corriger cette erreur. Si le problème persiste encore, contactez alors Ben Hedibi Hassène.";
      report_event(app_path,mtError,true);
      return;
    }

    TSplshFrm *SplshFrm = NULL;

  try
    {

       TConfigManager *config_manager = new TConfigManager(app_path + "db_session_config.ini",TAppStartup_config);

       switch (config_manager->GetLastError())
       {
				   case ERROR_SUCCESS : break;

			case DATA_SIGNATURE_ERROR : app_path = "Echec lors de l'initialisation du logiciel ! le fichier [db_session_config.ini] a été altéré ! \n\r\n\r";
										app_path = app_path + "Veuillez re-installer le logiciel afin de corriger cette erreur. Si le problème persiste encore, contactez alors Ben Hedibi Hassène.";
										report_event(app_path,mtError,true);
					                    return;

		  case (unsigned_int)IO_ERROR : app_path = "Echec lors de l'initialisation du logiciel ! Erreur IO lors de la lecture de [db_session_config.ini] \n\r\n\r";
										app_path = app_path + "Veuillez contacter Ben Hedibi Hassène";
										report_event(app_path,mtError,true);
										return;

				 case MEM_ALLOC_ERROR : app_path = "Echec lors de l'initialisation du logiciel ! Mémoire insuffisante \n\r\n\r";
										app_path = app_path + "Veuillez contacter Ben Hedibi Hassène";
										report_event(app_path,mtError,true);
										return;

							  default : report_event(error_code_to_string(config_manager->GetLastError()),mtError,true);
										break;
       }

       UnicodeString value;

       value = config_manager->ReadParamByName("splsh");

       if (value == "") goto config_manager_error;

       if (value == "1")
       {
		 SplshFrm = new TSplshFrm(this);

		  Hide();

		  SplshFrm->Show();
	   }

	   value = config_manager->ReadParamByName("session");

	   if (value == "") goto config_manager_error;

	   session_id = StrToInt(value);

	   avcore_memset(&session_params,0,sizeof(session_params));

	   session_params.session_manager = get_new_session_manager((uint32)session_id,&error_code);

	   if (!session_params.session_manager)
	   {
		 app_path = "Echec lors de l'initialisation du logiciel ! Une erreur est survenue lors du chargement du module [sessions manager]. \n\r\n\r";
		 app_path = app_path + "Veuillez contacter Ben Hedibi Hassène";
		 report_event(app_path,mtError,true);
		 return;
	   }

	   {
		 p_session_manager_path path = (p_session_manager_path)malloc(sizeof(t_session_manager_path) * 16);

		 if (!path)
		 {
		   app_path = "Echec lors de l'initialisation du logiciel ! Mémoire insuffisante \n\r\n\r";
		   app_path = app_path + "Veuillez contacter Ben Hedibi Hassène";
		   report_event(app_path,mtError,true);
		   return;
		 }

		 avcore_memset(path,0,sizeof(t_session_manager_path) * 16);

		 session_params.operators_path = path++;
		 session_params.doctors_path = path++;
		 session_params.patients_path = path++;
		 session_params.audiograms_path = path++;
		 session_params.tympanograms_path = path++;
		 session_params.gainprot_path = path++;
		 session_params.audiovoc_path = path++;
		 session_params.consultations_path = path++;
		 session_params.blobs_path = path++;
		 session_params.gouv_path = path++;
		 session_params.jobrefs_path = path++;
		 session_params.gprefs_path = path++;
		 session_params.pays_path = path++;
		 session_params.femmes_path = path++;
		 session_params.unknown_femme_picture_path = path++;
		 session_params.unknown_homme_picture_path = path++;

		 session_params.femmes_names = new TStringList;
	   }

	   value = config_manager->ReadParamByName("blobs");

	   if (value == "") goto config_manager_error;

	   session_params.blobs_path->path_len = value.Length() * 2;

	   avcore_memcpy(&session_params.blobs_path->path_data,(puchar)value.c_str(),session_params.blobs_path->path_len);

	   value = config_manager->ReadParamByName("gouv");

	   if (value == "") goto config_manager_error;

	   session_params.gouv_path->path_len = value.Length() * 2;

	   avcore_memcpy(&session_params.gouv_path->path_data,(puchar)value.c_str(),session_params.gouv_path->path_len);

	   value = config_manager->ReadParamByName("gprefs");

	   if (value == "") goto config_manager_error;

	   session_params.gprefs_path->path_len = value.Length() * 2;

	   avcore_memcpy(&session_params.gprefs_path->path_data,(puchar)value.c_str(),session_params.gprefs_path->path_len);

	   value = config_manager->ReadParamByName("jobrefs");

	   if (value == "") goto config_manager_error;

	   session_params.jobrefs_path->path_len = value.Length() * 2;

	   avcore_memcpy(&session_params.jobrefs_path->path_data,(puchar)value.c_str(),session_params.jobrefs_path->path_len);

	   value = config_manager->ReadParamByName("pays");

	   if (value == "") goto config_manager_error;

	   session_params.pays_path->path_len = value.Length() * 2;

	   avcore_memcpy(&session_params.pays_path->path_data,(puchar)value.c_str(),session_params.pays_path->path_len);

	   value = config_manager->ReadParamByName("femmes");

	   if (value == "") goto config_manager_error;

	   session_params.femmes_path->path_len = value.Length() * 2;

	   avcore_memcpy(&session_params.femmes_path->path_data,(puchar)value.c_str(),session_params.femmes_path->path_len);

	   value = config_manager->ReadParamByName("f_inconnu_photo");

	   if (value == "") goto config_manager_error;

	   session_params.unknown_femme_picture_path->path_len = value.Length() * 2;

	   avcore_memcpy(&session_params.unknown_femme_picture_path->path_data,(puchar)value.c_str(),session_params.unknown_femme_picture_path->path_len);

       value = config_manager->ReadParamByName("h_inconnu_photo");

       if (value == "") goto config_manager_error;

       session_params.unknown_homme_picture_path->path_len = value.Length() * 2;

       avcore_memcpy(&session_params.unknown_homme_picture_path->path_data,(puchar)value.c_str(),session_params.unknown_homme_picture_path->path_len);

	   {
		 typedef struct {
						  PWCHAR engine_name;
						  p_engine_entry engine_entry;
						  p_session_manager_path path;
						  PWCHAR graph_name;
						  UnicodeString description_name;
						  uint32 engine_id;
						} TLoad_engine_params;

		 static const TLoad_engine_params load_engine_params[] = {
		 {(PWCHAR)L"operators",&session_params.engines.operators_engine,session_params.operators_path,NULL,"opérateurs",OPERATOR_DB_SIGNATURE},
		 {(PWCHAR)L"doctors",&session_params.engines.doctors_engine,session_params.doctors_path,NULL,"docteurs",DOCTOR_DB_SIGNATURE},
		 {(PWCHAR)L"patients",&session_params.engines.patients_engine,session_params.patients_path,NULL,"patients",PATIENT_DB_SIGNATURE},
		 {(PWCHAR)L"audiograms",&session_params.engines.audiograms_engine,session_params.audiograms_path,(PWCHAR)L"audiograms_grph_types","audiogrammes",AUDIOGRAM_DB_SIGNATURE},
		 {(PWCHAR)L"tympanograms",&session_params.engines.tympanograms_engine,session_params.tympanograms_path,(PWCHAR)L"tympanograms_grph_types","tympanogrammes",TYMPANOGRAM_DB_SIGNATURE},
		 {(PWCHAR)L"gainprot",&session_params.engines.gainprots_engine,session_params.gainprot_path,(PWCHAR)L"gainprot_grph_types","gains prothétiques",GAIN_PROTHETIQUE_DB_SIGNATURE},
		 {(PWCHAR)L"audiovoc",&session_params.engines.audiovocs_engine,session_params.audiovoc_path,(PWCHAR)L"audiovoc_grph_types","audiométries vocales",AUDIOMETRIE_VOCALE_DB_SIGNATURE},
		 {(PWCHAR)L"consultations",&session_params.engines.consultations_engine,session_params.consultations_path,NULL,"consultations",CONSULTATIONS_DB_SIGNATURE}};

		 unsigned_int engine_blob_path_len,len;
		 uchar engine_blob_path[260 * 2];

		   for (int i = 0; i < sizeof(load_engine_params) / sizeof(load_engine_params[0]); i++)
		   {
			 if (SplshFrm)
			 {
			   SplshFrm->StatusLbl->Caption = "Chargement de la bases de données des " + load_engine_params[i].description_name + "...";
			   Application->ProcessMessages();
			 }

			 value = config_manager->ReadParamByName(load_engine_params[i].engine_name);

			 if (value == "") goto config_manager_error;

			 load_engine_params[i].path->path_len = value.Length() * 2;

			 if (load_engine_params[i].path->path_len + 2 > sizeof(load_engine_params[i].path->path_data))
			 {
			   app_path = "Le chemin spécifié de la base est trop long [Buffer overflow] ! \n\r\n\r";
			   app_path = app_path + "Les fichiers de configurations sont peut être corrompus ! Veuillez contacter le support technique.";
			   report_event(app_path,mtError,true);
			   return;
			 }

			 avcore_memcpy(&load_engine_params[i].path->path_data,(puchar)value.c_str(),load_engine_params[i].path->path_len);

			 if (!session_params.session_manager->load_lilly_engine(session_params.session_manager,(puchar)&load_engine_params[i].path->path_data))
			 {
			   app_path = "Echec lors de l'initialisation du logiciel ! Une erreur est survenue lors du chargement de la base de données des " + load_engine_params[i].description_name + "\n\r\n\r";
			   app_path = app_path + error_code_to_string(session_params.session_manager->error_code) + "\n\r" + "Veuillez contacter Ben Hedibi Hassène.";
			   report_event(app_path,mtError,true);
			   return;
			 }

			 load_engine_params[i].engine_entry->db_handle = session_params.session_manager->request_db_handle(session_params.session_manager,load_engine_params[i].engine_id);

			 if (!load_engine_params[i].engine_entry->db_handle)
			 {
			   app_path = "Echec lors de l'initialisation du logiciel ! Une erreur est survenue lors du chargement de la base de données des " + load_engine_params[i].description_name + "\n\r\n\r";
			   app_path = app_path + "[request db handle]" + error_code_to_string(session_params.session_manager->error_code) + "\n\r" + "Veuillez contacter le support technique.";
			   report_event(app_path,mtError,true);
			   return;
			 }

			 load_engine_params[i].engine_entry->engine = session_params.session_manager->request_lilly_engine(session_params.session_manager,load_engine_params[i].engine_id);

			 if (!load_engine_params[i].engine_entry->engine)
			 {
			   app_path = "Echec lors de l'initialisation du logiciel ! Une erreur est survenue lors du chargement du moteur des " + load_engine_params[i].description_name + "\n\r\n\r";
			   app_path = app_path + "[request engine handle]" + error_code_to_string(session_params.session_manager->error_code) + "\n\r\n\r" + "Veuillez contacter le support technique.";
			   report_event(app_path,mtError,true);
			   return;
			 }

			 len = engine_blob_path_len = avcore_wstrlen((puchar)load_engine_params[i].engine_name) * 2;

			 if (len + session_params.blobs_path->path_len + 2 > sizeof(engine_blob_path) - 2)
			 {
               app_path = "Le chemin spécifié de la base est trop long [Buffer overflow] ! \n\r\n\r";
			   app_path = app_path + "Les fichiers de configurations sont peut être corrompus ! Veuillez contacter le support technique.";
			   report_event(app_path,mtError,true);
			   return;
			 }

			 len += session_params.blobs_path->path_len;

			 engine_blob_path[len++] = IO_FOLDER_SEPARATOR;
			 engine_blob_path[len++] = 0;

			 *(puint16)&engine_blob_path[len] = 0;

			 avcore_memcpy(&engine_blob_path,&session_params.blobs_path->path_data,session_params.blobs_path->path_len);
			 avcore_memcpy(&engine_blob_path[session_params.blobs_path->path_len],(puchar)load_engine_params[i].engine_name,engine_blob_path_len);

			 if (!lilly_db_set_blob_db_path(load_engine_params[i].engine_entry->db_handle,(puchar)&engine_blob_path,len))
			 {
			   app_path = "Echec lors de l'initialisation du logiciel ! Une erreur est survenue lors du chargement de la base de données des " + load_engine_params[i].description_name + "\n\r\n\r";
			   app_path = app_path + "[set blob path]" + error_code_to_string(lilly_db_get_last_error(session_params.engines.operators_engine.db_handle)) + "\n\r\n\r" + "Veuillez contacter le support technique.";
			   report_event(app_path,mtError,true);
			   return;
			 }

			 if (load_engine_params[i].graph_name)
			 {
			   load_engine_params[i].engine_entry->grph_types_db_path = config_manager->ReadParamByName(load_engine_params[i].graph_name);
			   if ((load_engine_params[i].engine_entry->grph_types_db_path == NULL) || (load_engine_params[i].engine_entry->grph_types_db_path == "")) goto config_manager_error;
             }

		   }
	   }

	   delete config_manager;

	   if (SplshFrm)
	   {
		 SplshFrm->StatusLbl->Caption = "Bases de données chargées avec succès. Lancement de l'application en cours...";

		 Application->ProcessMessages();

		 Sleep(2000);

		 SplshFrm->Close();

		 delete SplshFrm;

         Show();
	   }

	   return;

	   config_manager_error :

	   if (SplshFrm)
	   {
		 SplshFrm->Close();

		 delete SplshFrm;

         Show();
	   }

	   error_code = config_manager->GetLastError();

	   if (error_code == ERROR_SUCCESS)
	   {
		 app_path = "Echec lors de l'initialisation du logiciel ! le fichier [db_session_config.ini] a été altéré ! \n\r\n\r";
		 app_path = app_path + "Veuillez re-installer le logiciel afin de corriger cet erreur. Si le problème persiste encore, contactez alors Ben Hedibi Hassène.";
		 report_event(app_path,mtError,true);
	   }
	   else report_event(error_code_to_string(error_code),mtError,true);

       return;

	 }

   __except(EXCEPTION_EXECUTE_HANDLER)
	 {
	   app_path = "Une erreur indéfinie est survenue lors de l'initialisation du logiciel ! \n\r\n\r";
	   app_path = app_path + "Contactez Ben Hedibi Hassène.";
	   report_event(app_path,mtError,true);
	   return;
     }

}

void __fastcall TForm1::release_session(void)
{

}

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{

	release_session();

}

//---------------------------------------------------------------------------


void __fastcall TForm1::Navigate(const int from,const int to)
{
  bool unload_current_recs_flag = false;


	switch (from)
	{
	   case 0 : unload_patient(this);
				break;

	   case 1 : UnloadPatientListPage();
				break;

	   case 2 : unload_consultation(this);
				break;

	   case 3 : UnloadConsultationListPage();
				break;

	   case 4 : unload_audiogram(this);
				break;

	   case 5 : unload_tympanogram(this);
				break;

	   case 6 : unload_gainp(this);
				break;

	   case 7 : unload_audiovoc(this);
				break;

	   case 8 : UnloadMainPage();
				break;

       case 9 : UnloadStatistiquesPage();
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				return;
	}

	switch (to)
	{
	   case 0 : if ((from == 1) || (from == 2))
				{
				  session_params.engines.patients_engine.caller_page_index = from;
				}
				else session_params.engines.patients_engine.caller_page_index = 1;

				if (!LoadPatientPage()) return;

				break;

	   case 1 : session_params.engines.patients_engine.caller_page_index = from;

				if (!LoadPatientListPage()) return;

				unload_current_recs_flag = true;

				break;

	   case 2 : if ((from == 0) || (from == 3))
				{
				  session_params.engines.consultations_engine.caller_page_index = from;
				}
				else session_params.engines.consultations_engine.caller_page_index = 3;

				if (!load_consultation(this)) return;

				break;

	   case 3 : session_params.engines.consultations_engine.caller_page_index = from;

				if (!LoadConsultationListPage()) return;

				unload_current_recs_flag = true;

				break;

	   case 4 : session_params.engines.audiograms_engine.caller_page_index = from;

				if (!load_audiogram(this)) return;

				break;

	   case 5 : session_params.engines.tympanograms_engine.caller_page_index = from;

				if (!load_tympanogram(this)) return;

                break;

	   case 6 : session_params.engines.audiovocs_engine.caller_page_index = from;

				if (!load_audiovoc(this)) return;

				break;

	   case 7 : session_params.engines.gainprots_engine.caller_page_index = from;

				if (!load_gainp(this)) return;

				break;

	   case 8 : if (!LoadMainPage()) return;

				unload_current_recs_flag = true;

				break;

	   case 9 : if (!LoadStatistiquesPage()) return;

				unload_current_recs_flag = true;

				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				return;
	}

	if (unload_current_recs_flag)
	{
	  session_params.engines.patients_engine.current_record = NULL;
      session_params.engines.consultations_engine.current_record = NULL;
	}

	PageControl1->ActivePageIndex = to;

	return;
}

// gestion des pages

bool __fastcall TForm1::LoadMainPage(void)
{
  p_patient_record pat_record;
  p_operateur_record op_record;
  p_consultation_record consult_record;
  uint64 offset;
  unsigned_int error_code;
  t_date_time tmp;
  t_lilly_db_time_stamp_informations rec_time_stamp;
  t_lilly_db_database_infos db_infos;
  UnicodeString str;



	pat_record = (p_patient_record)lilly_db_get_last_record(session_params.engines.patients_engine.db_handle);

	if (pat_record)
	{

	  LastPatNameLbl->Caption = format_name((PWCHAR)&pat_record->nom_prenom);

	  LastPatNameLbl->Font->Color = clWindowText;

	  offset = lilly_db_get_current_record_offset(session_params.engines.patients_engine.db_handle);

	  if (!lilly_db_get_record_time_stamp_infos(session_params.engines.patients_engine.db_handle,offset,&rec_time_stamp))
	  {
		str = "Une erreur fatale est survenue au niveau de [GetRecTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
		str = str + "\n\r\n\r";
		str = str + "Veuillez contacter votre support technique";
		report_event(str,mtError,true);
		return false;
	  }

	  LastPatTimeLbl->Caption = datetime_to_string(&rec_time_stamp.creation_stamp.time_stamp);

	  op_record = (p_operateur_record)session_params.engines.operators_engine.engine->code_to_record(session_params.engines.operators_engine.engine,session_params.engines.operators_engine.db_handle,rec_time_stamp.creation_stamp.operator_id);

	  if (!op_record)
	  {
		str = "Une erreur fatale est survenue au niveau de [RecLookup] ! Moteur operateurs a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(session_params.engines.operators_engine.engine->error_code);
		str = str + "\n\r\n\r";
		str = str + "Veuillez contacter votre support technique";
		report_event(str,mtError,true);
		return false;
	  }

	  LastPatOpNameLbl->Caption = format_name((PWCHAR)&op_record->nom_prenom);

	}
	else
	{
	  error_code = lilly_db_get_last_error(session_params.engines.patients_engine.db_handle);

	  if (error_code != ERROR_SUCCESS)
	  {
		report_event(error_code_to_string(error_code),mtError,true);
		return false;
	  }

	  LastPatNameLbl->Caption = "Base de données vierge";
	  LastPatNameLbl->Font->Color = clMaroon;

	  LastPatTimeLbl->Caption = "Indéfinie";

	  LastPatOpNameLbl->Caption = "Non spécifié";
	  // continuer avec les autre valeurs et quitter
	}

	consult_record = (p_consultation_record)lilly_db_get_last_record(session_params.engines.consultations_engine.db_handle);

	if (!consult_record)
	{
	  str = "Une erreur fatale est survenue au niveau de [GetLastRec] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
	  str = str + "\n\r\n\r";
	  str = str + "Veuillez contacter votre support technique";
	  report_event(str,mtError,true);
	  return false;
	}

	pat_record = (p_patient_record)session_params.engines.patients_engine.engine->code_to_record(session_params.engines.patients_engine.engine,
	session_params.engines.patients_engine.db_handle,consult_record->patient_id);

	if (!pat_record)
	{
      str = "Une erreur fatale est survenue au niveau de [RecLookup] ! Moteur patients a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(session_params.engines.patients_engine.engine->error_code);
	  str = str + "\n\r\n\r";
	  str = str + "Veuillez contacter votre support technique";
	  report_event(str,mtError,true);
	  return false;
    }

	LastConsPatNameLbl->Caption = format_name((PWCHAR)&pat_record->nom_prenom);

	tmp = rec_time_stamp.creation_stamp.time_stamp;

	offset = lilly_db_get_current_record_offset(session_params.engines.consultations_engine.db_handle);

	if (!lilly_db_get_record_time_stamp_infos(session_params.engines.consultations_engine.db_handle,offset,&rec_time_stamp))
	{
	  str = "Une erreur fatale est survenue au niveau de [GetRecTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  str = str + "\n\r\n\r";
	  str = str + "Veuillez contacter votre support technique";
	  report_event(str,mtError,true);
	  return false;
	}

	LastConsTimeLbl->Caption = datetime_to_string(&rec_time_stamp.creation_stamp.time_stamp);

	if (lilly_compare_dates(&tmp,&rec_time_stamp.creation_stamp.time_stamp) == DATE_IS_GREAT) // parce que le logiciel d'importation ne met pas à jour correctement la date de création de la fiche patient
	{
	  LastPatTimeLbl->Caption = LastConsTimeLbl->Caption;
	}

	op_record = (p_operateur_record)session_params.engines.operators_engine.engine->code_to_record(session_params.engines.operators_engine.engine,
	session_params.engines.operators_engine.db_handle,rec_time_stamp.creation_stamp.operator_id);

	if (!op_record)
	{
	  str = "Une erreur fatale est survenue au niveau de [RecLookup] ! Moteur operateurs a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(session_params.engines.operators_engine.engine->error_code);
	  str = str + "\n\r\n\r";
	  str = str + "Veuillez contacter votre support technique";
	  report_event(str,mtError,true);
	  return false;
	}

	LastConOpNameLbl->Caption = format_name((PWCHAR)&op_record->nom_prenom);

	{
	  int index = 0;

	  str = "";

	  LastConsOpLbl1->Caption = "";
	  LastConsOpLbl2->Caption = "";

	  if (consult_record->audiogram_id)
	  {
		index++;
		LastConsOpLbl1->Caption = "Audiogramme";
	  }

	  if (consult_record->tympanogram_id)
	  {
		index++;

		if (LastConsOpLbl1->Caption != "")
		{
		  LastConsOpLbl1->Caption = LastConsOpLbl1->Caption + ", ";
		}

		LastConsOpLbl1->Caption = LastConsOpLbl1->Caption + "Tympanogramme";
	  }

	  if (consult_record->gainp_id)
	  {
		index++;

		if (index > 2)
		{
		  LastConsOpLbl2->Caption = "Gain prothétique";
		}
		else
		{
          if (LastConsOpLbl1->Caption != "")
		  {
			LastConsOpLbl1->Caption = LastConsOpLbl1->Caption + ", ";
		  }
		  LastConsOpLbl1->Caption = LastConsOpLbl1->Caption + "Gain prothétique";
		}
	  }

	  if (consult_record->audiovoc_id)
	  {
		index++;

        if (index > 2)
		{
		  LastConsOpLbl2->Caption = LastConsOpLbl2->Caption + ", Audiométrie";
		}
		else
		{
          if (LastConsOpLbl1->Caption != "")
		  {
			LastConsOpLbl1->Caption = LastConsOpLbl1->Caption + ", ";
		  }

		  LastConsOpLbl1->Caption = LastConsOpLbl1->Caption + "Audiométrie";
		}
	  }

	  if (!index)
	  {
		LastConsOpLbl1->Caption = "consultation vide !";
	  }

	  LastConsOpLbl2->Visible = (index > 2);
    }

	stats : // normalement tmp doit contenir la date du jour et non pas celle de la dernière consultation, mais c'est juste pour démonstration

	{
	  p_consultation_record filtered_consult_record;
	  t_consultation_filter_params filter_params;
	  unsigned_int operations[4] = {0,0,0,0};
	  unsigned_int consult_count = 0,new_patient_count = 0;
	  int max_index[2];

	  avcore_memset(&filter_params,0,sizeof(filter_params));

	  offset = lilly_db_get_current_record_offset(session_params.engines.consultations_engine.db_handle);

	  if (!lilly_db_get_record_time_stamp_infos(session_params.engines.consultations_engine.db_handle,offset,&rec_time_stamp))
	  {
		str = "Une erreur fatale est survenue au niveau de [GetRecTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
		str = str + "\n\r\n\r";
		str = str + "Veuillez contacter votre support technique";
		report_event(str,mtError,true);
		return false;
	  }

	  // lilly_os_get_current_time_stamp(&tmp); // normalement

	  rec_time_stamp.creation_stamp.time_stamp.hours = 0;
	  rec_time_stamp.creation_stamp.time_stamp.minutes = 0;
	  rec_time_stamp.creation_stamp.time_stamp.seconds = 0;
	  rec_time_stamp.creation_stamp.time_stamp.reserved = 0;

	  tmp = rec_time_stamp.creation_stamp.time_stamp;

	  while (lilly_compare_dates(&tmp,&rec_time_stamp.creation_stamp.time_stamp) == DATE_IS_EQUAL)
	  {
		consult_count++;

		if (consult_record->audiogram_id)
		{
		  operations[0]++;
		}

		if (consult_record->tympanogram_id)
		{
		  operations[1]++;
		}

		if (consult_record->gainp_id)
		{
		  operations[2]++;
		}

		if (consult_record->audiovoc_id)
		{
		  operations[3]++;
		}

		offset = lilly_db_get_current_record_offset(session_params.engines.consultations_engine.db_handle);  // ici parce que get_first_filtered_record va altérer l'état current record offset et ainsi il ya aura une endless loop entre get_filtered & previous record

		filter_params.patient_id = consult_record->patient_id;

		filtered_consult_record = (p_consultation_record)session_params.engines.consultations_engine.engine->get_first_filtered_record(session_params.engines.consultations_engine.engine,
		session_params.engines.consultations_engine.db_handle,&filter_params);

		if (filtered_consult_record == consult_record)
		{
          new_patient_count++;
        }

		lilly_db_set_current_record_offset(session_params.engines.consultations_engine.db_handle,offset);

		consult_record = (p_consultation_record)lilly_db_get_previous_record(session_params.engines.consultations_engine.db_handle);

		if (!consult_record) break;

		offset = lilly_db_get_current_record_offset(session_params.engines.consultations_engine.db_handle);

		if (!lilly_db_get_record_time_stamp_infos(session_params.engines.consultations_engine.db_handle,offset,&rec_time_stamp))
		{
		  str = "Une erreur fatale est survenue au niveau de [GetRecTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
		  str = str + "\n\r\n\r";
		  str = str + "Veuillez contacter votre support technique";
		  report_event(str,mtError,true);
		  return false;
		}

		rec_time_stamp.creation_stamp.time_stamp.hours = 0;
		rec_time_stamp.creation_stamp.time_stamp.minutes = 0;
		rec_time_stamp.creation_stamp.time_stamp.seconds = 0;
		rec_time_stamp.creation_stamp.time_stamp.reserved = 0;
	  }

	  QuotDateLbl->Caption = date_to_string(&tmp);

	  QuotConsCountLbl->Caption = IntToStr((int)consult_count);
	  QuotPatCountLbl->Caption = IntToStr((int)new_patient_count);

	  max_index[0] = 0;
	  max_index[1] = 0;

	  for (int i = 0; i < 4; i++)
	  {
		if (operations[i] > max_index[1])
		{
		  max_index[0] = i;
		  max_index[1] = operations[i];
		}
	  }

	  QuotOpCountLbl->Caption = "0";

	  if (operations[max_index[0]])
	  {
		switch (max_index[0])
		{
		  case 0 : QuotOpCountLbl->Caption = "Audiogramme";
				   break;

		  case 1 : QuotOpCountLbl->Caption = "Tympanogramme";
				   break;

		  case 2 : QuotOpCountLbl->Caption = "Gain Prothétique";
				   break;

		  case 3 : QuotOpCountLbl->Caption = "Audiométrie vocale";
				   break;
		}
      }
	}

	OpNameLbl->Caption = session_params.CurrentOpName;

    return true;
}

void __fastcall TForm1::UnloadMainPage(void)
{
	return;
}

bool __fastcall TForm1::LoadPatientPage(void)
{
	if (!load_patient(this)) return false;

	fill_old_consultations_treeview(PatConsultView);

	return true;
}

bool __fastcall TForm1::LoadPatientListPage(void)
{
  t_lilly_db_database_infos db_infos;


	if (!lilly_db_get_database_informations(session_params.engines.patients_engine.db_handle,&db_infos))
	{
	  UnicodeString err_str = "Erreur au niveau de [GetDabaseInformations] ! Le moteur des patients a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  report_event(err_str,mtError,true);
	  return false;
	}

	if (!db_infos.record_count) return true; // base de données vide

	CreateVtmBlocks(db_infos.record_count);

	LoadVtmBlocks(true);

	PatCntLbl->Caption = IntToStr((int)vtm_params.rec_count);

	PatListView->Items->Count = vtm_params.rec_count;

	return true;
}

void __fastcall TForm1::UnloadPatientListPage(void)
{

	PatListView->Items->Count = 0;

	DeleteVtmBlocks();

    return;
}

bool __fastcall TForm1::LoadConsultationListPage(void)
{
  unsigned_int error_code;
  t_lilly_db_database_infos db_infos;


	fill_combo_box(&session_params,ConsFltOpCombo,OPERATOR_DB_SIGNATURE);

	if (!lilly_db_get_database_informations(session_params.engines.consultations_engine.db_handle,&db_infos))
	{
	  UnicodeString err_str = "Erreur au niveau de [GetDabaseInformations] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  return false;
	}

	if (!db_infos.record_count) return true; // base de données vide

	CreateVtmBlocks(db_infos.record_count);

	LoadVtmBlocks(false);

	ConsCntLbl->Caption = IntToStr((int)vtm_params.rec_count);

	ConsListView->Items->Count = vtm_params.rec_count;

	ConsListView->Repaint();

	return true;
}

void __fastcall TForm1::UnloadConsultationListPage(void)
{

	ConsListView->Items->Count = 0;

	DeleteVtmBlocks();

    ConsFltOpCombo->Items->Clear();

	return;
}

bool __fastcall TForm1::LoadStatistiquesPage(void)
{
	return true;
}

void __fastcall TForm1::UnloadStatistiquesPage(void)
{
   return;
}

// --------------------------------------------------------------------------

// NAVIGATION PRINCIPALE

void __fastcall TForm1::AcceuilLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);

	label->GlowSize = 1;

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AcceuilLblMouseLeave(TObject *Sender)
{
   TLabel *label = static_cast<TLabel *>(Sender);

	label->GlowSize = 0;

	return;
}

//---------------------------------------------------------------------------


void __fastcall TForm1::InfoImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : AcceuilLbl->GlowSize = 1;
				break;

	   case 1 : ConsultLbl->GlowSize = 1;
				break;

	   case 2 : PatientLbl->GlowSize = 1;
				break;

	   case 3 : OpLbl->GlowSize = 1;
				break;

	   case 4 : MedLbl->GlowSize = 1;
				break;

	   case 5 : StatLbl->GlowSize = 1;
				break;

	   case 6 : ParamLbl->GlowSize = 1;
				break;

	   case 7 : InfoLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AcceuilleImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : AcceuilLbl->GlowSize = 0;
				break;

	   case 1 : ConsultLbl->GlowSize = 0;
				break;

	   case 2 : PatientLbl->GlowSize = 0;
				break;

	   case 3 : OpLbl->GlowSize = 0;
				break;

	   case 4 : MedLbl->GlowSize = 0;
				break;

	   case 5 : StatLbl->GlowSize = 0;
				break;

	   case 6 : ParamLbl->GlowSize = 0;
				break;

	   case 7 : InfoLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatValidImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : ConsPatValidLbl->GlowSize = 1;
				break;

	   case 1 : ConsPatEditLbl->GlowSize = 1;
				break;

	   case 2 : ConsPatDelLbl->GlowSize = 1;
				break;

	   case 3 : ConsPatCancelLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatValidImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : ConsPatValidLbl->GlowSize = 0;
				break;

	   case 1 : ConsPatEditLbl->GlowSize = 0;
				break;

	   case 2 : ConsPatDelLbl->GlowSize = 0;
				break;

	   case 3 : ConsPatCancelLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsListAddImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : ConsListAddLbl->GlowSize = 1;
				break;

	   case 1 : ConsListEditLbl->GlowSize = 1;
				break;

	   case 2 : ConsListDelLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsListAddImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : ConsListAddLbl->GlowSize = 0;
				break;

	   case 1 : ConsListEditLbl->GlowSize = 0;
				break;

	   case 2 : ConsListDelLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

void __fastcall TForm1::AudiogValidImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : AudiogValidLbl->GlowSize = 1;
				break;

	   case 1 : AudiogEditLbl->GlowSize = 1;
				break;

	   case 2 : AudiogDelLbl->GlowSize = 1;
				break;

	   case 3 : AudiogCancelLbl->GlowSize = 1;
				break;

	   case 4 : AudiogViewLbl->GlowSize = 1;
				break;

	   case 5 : AudiogAddGraphLbl->GlowSize = 1;
				break;

	   case 6 : AudiogDelGraphLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AudiogValidImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : AudiogValidLbl->GlowSize = 0;
				break;

	   case 1 : AudiogEditLbl->GlowSize = 0;
				break;

	   case 2 : AudiogDelLbl->GlowSize = 0;
				break;

	   case 3 : AudiogCancelLbl->GlowSize = 0;
				break;

	   case 4 : AudiogViewLbl->GlowSize = 0;
				break;

	   case 5 : AudiogAddGraphLbl->GlowSize = 0;
				break;

	   case 6 : AudiogDelGraphLbl->GlowSize = 0;
				break;


	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

void __fastcall TForm1::TympValidImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : TympValidLbl->GlowSize = 1;
				break;

	   case 1 : TympEditLbl->GlowSize = 1;
				break;

	   case 2 : TympDelLbl->GlowSize = 1;
				break;

	   case 3 : TympCancelLbl->GlowSize = 1;
				break;

	   case 4 : TympViewLbl->GlowSize = 1;
				break;

	   case 5 : TympAddGrphLbl->GlowSize = 1;
				break;

	   case 6 : TympDelGrphLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::TympValidImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : TympValidLbl->GlowSize = 0;
				break;

	   case 1 : TympEditLbl->GlowSize = 0;
				break;

	   case 2 : TympDelLbl->GlowSize = 0;
				break;

	   case 3 : TympCancelLbl->GlowSize = 0;
				break;

	   case 4 : TympViewLbl->GlowSize = 0;
				break;

	   case 5 : TympAddGrphLbl->GlowSize = 0;
				break;

	   case 6 : TympDelGrphLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocValidImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : AvocValidLbl->GlowSize = 1;
				break;

	   case 1 : AvocEditLbl->GlowSize = 1;
				break;

	   case 2 : AvocDelLbl->GlowSize = 1;
				break;

	   case 3 : AvocCancelLbl->GlowSize = 1;
				break;

	   case 4 : AvocViewLbl->GlowSize = 1;
				break;

	   case 5 : AvocAddGrphLbl->GlowSize = 1;
				break;

	   case 6 : AvocDelGrphLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocValidImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : AvocValidLbl->GlowSize = 0;
				break;

	   case 1 : AvocEditLbl->GlowSize = 0;
				break;

	   case 2 : AvocDelLbl->GlowSize = 0;
				break;

	   case 3 : AvocCancelLbl->GlowSize = 0;
				break;

	   case 4 : AvocViewLbl->GlowSize = 0;
				break;

	   case 5 : AvocAddGrphLbl->GlowSize = 0;
				break;

	   case 6 : AvocDelGrphLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpValidImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : GainpValidLbl->GlowSize = 1;
				break;

	   case 1 : GainpEditLbl->GlowSize = 1;
				break;

	   case 2 : GainpDelLbl->GlowSize = 1;
				break;

	   case 3 : GainpCancelLbl->GlowSize = 1;
				break;

	   case 4 : GainpViewLbl->GlowSize = 1;
				break;

	   case 5 : GainpAddGrphLbl->GlowSize = 1;
				break;

	   case 6 : GainpDelGrphLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpValidImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : GainpValidLbl->GlowSize = 0;
				break;

	   case 1 : GainpEditLbl->GlowSize = 0;
				break;

	   case 2 : GainpDelLbl->GlowSize = 0;
				break;

	   case 3 : GainpCancelLbl->GlowSize = 0;
				break;

	   case 4 : GainpViewLbl->GlowSize = 0;
				break;

	   case 5 : GainpAddGrphLbl->GlowSize = 0;
				break;

	   case 6 : GainpDelGrphLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatCancelImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : PatValidateLbl->GlowSize = 1;
				break;

	   case 1 : PatEditLbl->GlowSize = 1;
				break;

	   case 2 : PatDelLbl->GlowSize = 1;
				break;

	   case 3 : PatCancelLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatCancelImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : PatValidateLbl->GlowSize = 0;
				break;

	   case 1 : PatEditLbl->GlowSize = 0;
				break;

	   case 2 : PatDelLbl->GlowSize = 0;
				break;

	   case 3 : PatCancelLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatListDelImgMouseEnter(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : PatListAddLbl->GlowSize = 1;
				break;

	   case 1 : PatListEditLbl->GlowSize = 1;
				break;

	   case 2 : PatListDelLbl->GlowSize = 1;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatListDelImgMouseLeave(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);


	 if (!image)
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 switch (image->Tag)
	 {
	   case 0 : PatListAddLbl->GlowSize = 0;
				break;

	   case 1 : PatListEditLbl->GlowSize = 0;
				break;

	   case 2 : PatListDelLbl->GlowSize = 0;
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::OpNameLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpNameLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	label->Font->Color = clWindowText;

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::DemogLblMouseEnter(TObject *Sender)
{
  static const PWCHAR description_data[8] = {(PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par catégories d'ages et sexes etc...",
								 (PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par continents, pays, gouvernorats, régions, climats etc...",
								 (PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par types d'activités, métiers etc...",
								 (PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par Médecins traitants, Hôpitaux etc...",
								 (PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par type de graphiques Audiogrammes.",
								 (PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par type de graphiques Tympanogrammes.",
								 (PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par type de graphiques Audiométries vocales.",
								 (PWCHAR)L"Données statistiques regroupant tous les patients inscrits dans votre base de données par type de graphiques Gains Prothétiques."};

  int index;
  TLabel *label = dynamic_cast<TLabel *>(Sender);


	if (label)
	{
	  index = label->Tag;
	}
	else
	{
	  TImage *image = dynamic_cast<TImage *>(Sender);

	  if (!image)
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  index = image->Tag;
	}

	if (index > 7)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	StatDescriptLbl->Caption = description_data[index];

	if (label)
	{
	  AcceuilLblMouseEnter(Sender);
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DemogLblMouseLeave(TObject *Sender)
{

	StatDescriptLbl->Caption = "";

	AcceuilLblMouseLeave(Sender);

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::DemogLblClick(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	switch (label->Tag)
	{
	   case 0 : HandleDemographicStatistics();
				break;

	   case 1 : HandleGeographicStatistics();
				break;

	   case 2 : HandleJobStatistics();
                break;

	   case 3 : HandleMedStatistics();
                break;

	   case 4 : HandleAudiogramsStatistics();
				break;

	   case 5 : HandleTympanogramsStatistics();
                break;

	   case 6 : HandleAvocStatistics();
				break;

	   case 7 : HandleGainpStatistics();
                break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::GainpChlChkClick(TObject *Sender)
{

	if (GainpChlChk->State != cbChecked)
	{
	  GainpOdChk->State = cbUnchecked;
	  GainpOgChk->State = cbUnchecked;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpOdChkClick(TObject *Sender)
{
  TCheckBox *check_box = static_cast<TCheckBox *>(Sender);


	if (check_box->State != cbChecked)
	{
	  GainpChlChk->State = cbUnchecked;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocChlChkClick(TObject *Sender)
{

	if (AvocChlChk->State != cbChecked)
	{
	  AvocOdChk->State = cbUnchecked;
	  AvocOgChk->State = cbUnchecked;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocOgChkClick(TObject *Sender)
{
  TCheckBox *check_box = static_cast<TCheckBox *>(Sender);


	if (check_box->State != cbChecked)
	{
	  AvocChlChk->State = cbUnchecked;
	}

	return;
}

//---------------------------------------------------------------------------


void __fastcall TForm1::OdRsEdit1Exit(TObject *Sender)
{
  TEdit  *edit = static_cast<TEdit *>(Sender);


	if (edit->ToString() > 120)
	{
	  edit->Text = "120";
	}

	if (edit->Text == "")
	{
	  edit->Text = "0";
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::OdVaEdit1Enter(TObject *Sender)
{
  TEdit *edit = static_cast<TEdit *>(Sender);


	 edit->Color = clWindow;

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OdVaEdit1Exit(TObject *Sender)
{
  TEdit *edit = static_cast<TEdit *>(Sender);


	 if (edit->Text.ToInt() > 120)
	 {
	   edit->Text = "120";
	   edit->Color = TColor(0x8080FF);
	 }

	 if (edit->Text == "")
	 {
	   edit->Text = "0";
	 }

	 return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::OdVoEdit1Exit(TObject *Sender)
{
  TEdit *edit = static_cast<TEdit *>(Sender);


	 if (edit->Text.ToInt() > 70)
	 {
	   edit->Text = "70";
	   edit->Color = TColor(0x8080FF);
	 }

	 if (edit->Text == "")
	 {
	   edit->Text = "0";
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OdPressEdit1Exit(TObject *Sender)
{
  TEdit *edit = static_cast<TEdit *>(Sender);
  int ix,start = 1;
  bool virgule_found = false;


    if (edit->Text == "")
	{
	  edit->Text = "0";
      return;
	}

	if ((edit->Text[1] == L'.') || (edit->Text[1] == L','))
	{
	  edit->Text = edit->Text.Delete(1,1);
	  edit->Text = edit->Text.Insert("0,",1);
	  start += 2;
	  virgule_found = true;
	}
	else
	{
	  debut :
	  {
      }

	  switch (edit->Text[1])  // s'assurer que ça ne passe pas la limite de 5
	  {
		case '0' :
		case '1' :
		case '2' :
		case '3' :
		case '4' :
		case '5' : break;

		 default : edit->Text = "5";
				   return;
	  }

	  ix = edit->Text.Pos(".");

	  if (ix > 2)
	  {
		if (virgule_found)
		{
		  edit->Text = "0";
		  return;
		}
		else virgule_found = true;

		edit->Text = edit->Text.Delete(1,ix - 2);

		goto debut;
	  }
	  else
	  {
		ix = edit->Text.Pos(",");

		if (ix > 2)
		{
		  if (virgule_found)
		  {
			edit->Text = "0";
			return;
		  }
		  else virgule_found = true;

		  edit->Text = edit->Text.Delete(1,ix - 2);

		  goto debut;
		}
	  }
	}

	for (int i = start; i <= edit->Text.Length() ; i++)
	{
	  switch (edit->Text[i])
	  {
		case '0' :
		case '1' :
		case '2' :
		case '3' :
		case '4' :
		case '5' :
		case '6' :
		case '7' :
		case '8' :
		case '9' : break;

		case '.' : if (virgule_found)
				   {
					 edit->Text = "0";
					 return;
				   }

				   edit->Text = edit->Text.Delete(i,1);
				   edit->Text = edit->Text.Insert(",",i);

				   virgule_found = true;

				   break;

		case ',' : if (virgule_found)
				   {
					 edit->Text = "0";
					 return;
				   }

				   virgule_found = true;

                   break;

		 default : edit->Text = "0"; // invalider et quitter
				   return;
	  }
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AvapEdit10Exit(TObject *Sender)
{
  TEdit *edit = static_cast<TEdit *>(Sender);


	if (edit->Text == "")
	{
	  edit->Text = "0";
	}
	else if (edit->Text.ToInt() > 100)
	{
	  edit->Text = "100";
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::WeberEdit1Exit(TObject *Sender)
{
  TEdit *edit = static_cast<TEdit *>(Sender);

	if (edit->Text.ToInt() > 2)
	{
	  edit->Text = "2";
	}

    return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AcceuilleImgClick(TObject *Sender)
{
  TImage *image = dynamic_cast<TImage *>(Sender);
  int tag;


	 if (image)
	 {
	   tag = image->Tag;
	 }
	 else
	 {
	   TLabel *label = dynamic_cast<TLabel *>(Sender);

	   if (!label)
	   {
		 report_event(error_code_to_string(API_ERROR),mtError,true);
		 return;
	   }

	   tag = label->Tag;
	 }


	 switch (tag)
	 {
	   case 0 : Navigate(PageControl1->ActivePageIndex,8);
				break;

	   case 1 : Navigate(PageControl1->ActivePageIndex,3);
				break;

	   case 2 : Navigate(PageControl1->ActivePageIndex,1);
				break;

	   case 3 : HandleOperatorPage();
				break;

	   case 4 : HandleDoctorsPage();
				break;

	   case 5 : Navigate(PageControl1->ActivePageIndex,9);
				break;

	   case 6 : report_event(error_code_to_string(ERROR_NOT_IMPLEMENTED),mtError,false);
				break;

	   case 7 : HandleInfosPage();
				break;

	  default : report_event(error_code_to_string(API_ERROR),mtError,true);
				break;
	 }

	 return;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::AudiogListViewItemChecked(TObject *Sender, TListItem *Item)
{
  int index = Item->Index;
  int count = AudiogListView->Items->Count;


	if (!count) return;

	for (int i = 0; i < count; i++)
	{
	  if (i != index)
	  {
		AudiogListView->Items->Item[i]->Checked = false;
	  }
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AvocDelGrphImgClick(TObject *Sender) // partagée par tous les events delete graphique type
{
  p_engine_entry engine_entry;
  uint32 engine_id;
  TComboBox *combo_box;
  TComponent *component = dynamic_cast<TComponent *>(Sender);


	if (!component)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	if (component->Name.Pos("Audiog") == 1)
	{
	  engine_entry = &session_params.engines.audiograms_engine;
	  engine_id = AUDIOGRAM_DB_SIGNATURE;
	  combo_box = AudiogDefValCombo;
	}
	else if (component->Name.Pos("Tympano") == 1)
	{
	  engine_entry = &session_params.engines.tympanograms_engine;
	  engine_id = TYMPANOGRAM_DB_SIGNATURE;
	  combo_box = TympanoDefValCombo;
	}
	else if (component->Name.Pos("Avoc") == 1)
	{
	  engine_entry = &session_params.engines.audiovocs_engine;
	  engine_id = AUDIOMETRIE_VOCALE_DB_SIGNATURE;
	  combo_box = AvocDefValCombo;
	}
	else if (component->Name.Pos("Gainp") == 1)
	{
	  engine_entry = &session_params.engines.gainprots_engine;
	  engine_id = GAIN_PROTHETIQUE_DB_SIGNATURE;
	  //combo_box = AudiogDefValCombo;
	}
	else
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	delete_grph_item(engine_entry,engine_id,combo_box);

	return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::HandleOperatorPage(void)
{
  p_operateur_record op_record;
  struct t_lilly_db_handle *op_db_handle;

	 OpListFrm = new TOpListFrm(this);

   try
	 {


		OpListFrm->op_entry = &session_params.engines.operators_engine;
		OpListFrm->consult_entry = &session_params.engines.consultations_engine;

		OpListFrm->Caption = Caption;

		op_db_handle = session_params.session_manager->request_db_handle(session_params.session_manager,OPERATOR_DB_SIGNATURE);

		if (!op_db_handle)
		{
		  UnicodeString err_str = "Impossible de charger la liste des opérateurs ! Session Manager a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(session_params.session_manager->error_code);
		  report_event(err_str,mtError,true);
		  return;
		}

		op_record = (p_operateur_record)lilly_db_get_first_record(op_db_handle);

		if (!op_record)
		{
		  unsigned_int error_code = lilly_db_get_last_error(op_db_handle);

		  if (error_code == LILLY_DB_EMPTY_DATABASE_ERROR)
		  {
			OpListFrm->ShowModal();
			return;
		  }

		  UnicodeString err_str = "Erreur au niveau de [GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";

		  err_str = err_str + error_code_to_string(lilly_db_get_last_error(op_db_handle));

		  report_event(err_str,mtError,true);

		  return;
		}

		uint64 offset;
		TListItem *item;

		while (true)
		{
		  offset = lilly_db_get_current_record_offset(op_db_handle);

		  item = OpListFrm->ListView1->Items->Add();

		  item->Caption = IntToStr((int)offset);

		  item->SubItems->Add((PWCHAR)&op_record->nom_prenom);
		  item->SubItems->Add((PWCHAR)&op_record->phone_principal);

		  item->SubItems->Add("Non");

		  op_record = (p_operateur_record)lilly_db_get_next_record(op_db_handle);

		  if (!op_record) break;

		}

		if (lilly_db_get_last_error(op_db_handle) != ERROR_SUCCESS)
		{
		  UnicodeString err_str = "Erreur au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(lilly_db_get_last_error(op_db_handle));
		  report_event(err_str,mtError,true);
		  return;
		}

		OpListFrm->ShowModal();
	 }

   __finally
	 {
	   delete OpListFrm;
	 }

	 return;

}

void __fastcall TForm1::HandleDoctorsPage(void)
{
  MedListFrm = new TMedListFrm(this);
  p_medecin_record med_record;
  struct t_lilly_db_handle *med_db_handle;

   try
	 {
		MedListFrm->Caption = Caption;

		MedListFrm->med_entry = &session_params.engines.doctors_engine;

		MedListFrm->consult_entry = &session_params.engines.consultations_engine;

		MedListFrm->pays_path = session_params.pays_path;

		MedListFrm->gouv_path = session_params.gouv_path;

		med_db_handle = session_params.session_manager->request_db_handle(session_params.session_manager,DOCTOR_DB_SIGNATURE);

		if (!med_db_handle)
		{
		  UnicodeString err_str = "Impossible de charger la liste des médecins ! Session Manager a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(session_params.session_manager->error_code);
		  report_event(err_str,mtError,true);
		  return;
		}

		med_record = (p_medecin_record)lilly_db_get_first_record(med_db_handle);

		if (!med_record)
		{
		  unsigned_int error_code = lilly_db_get_last_error(med_db_handle);

		  if (error_code == LILLY_DB_EMPTY_DATABASE_ERROR)
		  {
			MedListFrm->ShowModal();
			return;
		  }

		  UnicodeString err_str = "Erreur au niveau de [GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";

		  err_str = err_str + error_code_to_string(lilly_db_get_last_error(med_db_handle));

		  report_event(err_str,mtError,true);

		  return;
		}


		uint64 offset;
		int index = 0;

		while (true)
		{
		  offset = lilly_db_get_current_record_offset(med_db_handle);

		  MedListFrm->ListView1->Items->Add();

		  MedListFrm->ListView1->Items->Item[index]->Caption = IntToStr((int)offset);

		  MedListFrm->ListView1->Items->Item[index]->SubItems->Add((PWCHAR)&med_record->nom_prenom);

		  switch (med_record->type)
		  {
			case MEDECIN_PRIVE_TYPE : MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Non");
									  MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Non");
									  MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Oui");
									  break;

				  case HOPITAL_TYPE : MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Oui");
									  MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Non");
									  MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Non");
									  break;

				 case CLINIQUE_TYPE : MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Non");
									  MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Oui");
									  MedListFrm->ListView1->Items->Item[index]->SubItems->Add("Non");
									  break;
		  }

		  med_record = (p_medecin_record)lilly_db_get_next_record(med_db_handle);

		  if (!med_record) break;

		  index++;
		}

		if (lilly_db_get_last_error(med_db_handle) != ERROR_SUCCESS)
		{
		  UnicodeString err_str = "Erreur au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(lilly_db_get_last_error(med_db_handle));
		  report_event(err_str,mtError,true);
		  return;
		}

		MedListFrm->ShowModal();
	 }

   __finally
	 {
	   delete MedListFrm;
	 }

	return;
}

void __fastcall TForm1::HandleInfosPage(void)
{
  InfosFrm = new TInfosFrm(this);
  t_lilly_db_database_infos db_infos;

	try
	  {
		InfosFrm->Caption = Caption;

		InfosFrm->VersionLbl->Caption = "0.921 / ";

		#ifdef COMPILATION_64BIT
		InfosFrm->VersionLbl->Caption = InfosFrm->VersionLbl->Caption + "Win64";
		#else
		InfosFrm->VersionLbl->Caption = InfosFrm->VersionLbl->Caption + "Win32";
		#endif

		if (!lilly_db_get_database_informations(session_params.engines.operators_engine.db_handle,&db_infos))
		{
		  UnicodeString str = "Une erreur est survenue au niveau de [GetDBInfos] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.operators_engine.db_handle));
		  str = str + "\n\r\n\r";
		  str = str + "Veuillez contacter Ben Hedibi Hassène";
		  report_event(str,mtError,true);
		  return;
		}

		InfosFrm->UsrCountLbl->Caption = IntToStr((int)db_infos.record_count);

		if (!lilly_db_get_database_informations(session_params.engines.patients_engine.db_handle,&db_infos))
		{
		  UnicodeString str = "Une erreur est survenue au niveau de [GetDBInfos] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.operators_engine.db_handle));
		  str = str + "\n\r\n\r";
		  str = str + "Veuillez contacter Ben Hedibi Hassène";
		  report_event(str,mtError,true);
		  return;
		}

		InfosFrm->PatCountLbl->Caption = IntToStr((int)db_infos.record_count);

		if (!lilly_db_get_database_informations(session_params.engines.consultations_engine.db_handle,&db_infos))
		{
		  UnicodeString str = "Une erreur est survenue au niveau de [GetDBInfos] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.operators_engine.db_handle));
		  str = str + "\n\r\n\r";
		  str = str + "Veuillez contacter Ben Hedibi Hassène";
		  report_event(str,mtError,true);
		  return;
		}

		InfosFrm->ConsultCountLbl->Caption = IntToStr((int)db_infos.record_count);

		if (!lilly_db_get_database_informations(session_params.engines.doctors_engine.db_handle,&db_infos))
		{
		  UnicodeString str = "Une erreur est survenue au niveau de [GetDBInfos] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.operators_engine.db_handle));
		  str = str + "\n\r\n\r";
		  str = str + "Veuillez contacter Ben Hedibi Hassène";
		  report_event(str,mtError,true);
		  return;
		}

		InfosFrm->DoctorCountLbl->Caption = IntToStr((int)db_infos.record_count);

		InfosFrm->ShowModal();
	  }

	__finally
	  {
		delete InfosFrm;
	  }

	return;
}

void __fastcall TForm1::ConsToggleClick(TObject *Sender)
{
  bool state;


	 state = (ConsToggle->State == tssOn);

	 ConsFltAudiogChk->Enabled = state;
	 ConsFltAudiogChk->Checked = state;

	 ConsFltAvocChk->Enabled = state;
	 ConsFltAvocChk->Checked = state;

	 ConsFltCodeEdit->Enabled = state;
	 ConsFltCodeEdit->Text = "";

	 ConsFltDateEdit1->Enabled = state;
	 ConsFltDateEdit1->Text = "";

	 ConsFltDateEdit2->Enabled = state;
	 ConsFltDateEdit2->Text = "";

	 ConsFltGpChk->Enabled = state;
	 ConsFltGpChk->Checked = state;

	 ConsFltNomEdit->Enabled = state;
	 ConsFltNomEdit->Text = "";

	 ConsFltTympanoChk->Enabled = state;
	 ConsFltTympanoChk->Checked = state;

	 ConsFltOpCombo->Enabled = state;
	 ConsFltOpCombo->ItemIndex = -1;

	 ConsFltImg->Enabled = state;
	 ConsFltLbl->Enabled = state;

	 if (!state)
	 {
	   vtm_params.filter_rec_count = vtm_params.rec_count;

	   ConsCntLbl->Caption = IntToStr((int)vtm_params.rec_count);

	   LoadVtmBlocks(false);

	   ConsListView->Items->Count = vtm_params.rec_count;

	   ConsListView->Repaint();
	 }

	 return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatAucunRadioClick(TObject *Sender)
{
  TRadioButton *button = static_cast<TRadioButton *>(Sender);
  int tag = button->Tag;


	 if ((tag < 0) || (tag > 2))
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
     }

	 PatQuickSrchEdit->Enabled = (tag != 0);

	 PatQuickSrchEdit->NumbersOnly = (tag > 1);

	 PatQuickSrchEdit->Text = "";

	 vtm_params.filter_rec_count = vtm_params.rec_count;

	 LoadVtmBlocks(true);

	 PatListView->Items->Count = vtm_params.rec_count;

	 PatListView->Repaint();

	 switch (tag)
	 {
	   case 0 : break;

	   case 1 : PatQuickSrchEdit->TextHint = "Spécifiez nom de patient";
				break;

	   case 2 : PatQuickSrchEdit->TextHint = "Spécifiez code de patient";
	 }

	 return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::MailKeyPress(TObject *Sender,System::WideChar &Key)
{

	 switch (Key)
	 {
	   case ' ' : Key = 0;
				  break;

	   case '@' :
	   case '.' : break;

		default : Key |= 0x0020;
				  break;

	 }

	 return;
}

void __fastcall TForm1::PhoneKeyPress(TObject *Sender, System::WideChar &Key)
{

	switch (Key)
	{
	   case ' ' :
	   case '0' :
	   case '1' :
	   case '2' :
	   case '3' :
	   case '4' :
	   case '5' :
	   case '6' :
	   case '7' :
	   case '8' :
	   case '9' :
	   case '+' :
	   case '(' :
	   case ')' : break;

	   default : Key = 0;
				 break;
	}

	return;
}

void __fastcall TForm1::PatTailleEditExit(TObject *Sender)
{

	if ((PatTailleEdit->Text != "") && ((PatTailleEdit->Text.ToInt() > 250) || (PatTailleEdit->Text.ToInt() < 45)))
	{
	  report_event("La taille que vous avez spécifié est invalide !",mtWarning,false);
	  ActiveControl = PatTailleEdit;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatPoidEditExit(TObject *Sender)
{

	if ((PatPoidEdit->Text != "") && ((PatPoidEdit->Text.ToInt() > 250) || (PatPoidEdit->Text.ToInt() < 4)))
	{
	  report_event("Le poids que vous avez spécifié est invalide !",mtWarning,false);
	  ActiveControl = PatPoidEdit;
	}

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatListAddImgClick(TObject *Sender)
{

	session_params.engines.patients_engine.current_record = NULL;
	session_params.engines.patients_engine.edit_mode = true;

	Navigate(1,0);

	return;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatListEditImgClick(TObject *Sender)
{
  puint64 offset;
  unsigned_int index;


	if ((!PatListView->SelCount) || (!vtm_params.filter_rec_count)) return;

	if (!vtm_params.vtm_manager)
	{
	  report_event("Erreur fatale ! VTM Manager indisponible.",mtError,true);
	  return;
	}

	index = (unsigned_int)PatListView->Selected->Index;

	if (index >= vtm_params.filter_rec_count)
	{
	  report_event("VTM Index out of range !! Veuillez contacter Ben Hedibi Hassène.",mtError,true);
	  return;
	}

	offset = (puint64)vtm_params.vtm_manager->GetData(index);

	if (vtm_params.vtm_manager->GetLastError() != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [GetData] ! VTM Manager a retourné l'erreur suivante : \n\r";
	  err_str = err_str + error_code_to_string(vtm_params.vtm_manager->GetLastError());
	  report_event(err_str,mtError,true);
	  return;
	}

	session_params.engines.patients_engine.current_record = (p_patient_record)lilly_db_read_record(session_params.engines.patients_engine.db_handle,PATIENT_RECORD_SIZE,*offset);

	if (!session_params.engines.patients_engine.current_record)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  report_event(err_str,mtError,true);
      return;
    }

	session_params.engines.patients_engine.edit_mode = true;

	Navigate(1,0);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatListDelImgClick(TObject *Sender)
{
  puint64 offset;
  unsigned_int index;
  p_patient_record pat_record;
  UnicodeString str;


	if ((!PatListView->SelCount) || (!vtm_params.filter_rec_count)) return;

	str = "Attention : vous êtes sur le point de supprimer une fiche patient ainsi que toutes les consultations associées ! \n\r\n\r";
	str = str + "Continuer quand même ?";

	if (!ask_event(str)) return;

	if (!vtm_params.vtm_manager)
	{
	  report_event("Erreur fatale ! VTM Manager indisponible.",mtError,true);
	  return;
	}

	index = (unsigned_int)PatListView->Selected->Index;

	if (index >= vtm_params.filter_rec_count)
	{
	  report_event("VTM Index out of range !! Veuillez contacter Ben Hedibi Hassène.",mtError,true);
	  return;
	}

	offset = (puint64)vtm_params.vtm_manager->GetData(index);

	if (vtm_params.vtm_manager->GetLastError() != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [GetData] ! VTM Manager a retourné l'erreur suivante : \n\r";
	  err_str = err_str + error_code_to_string(vtm_params.vtm_manager->GetLastError());
	  report_event(err_str,mtError,true);
	  return;
	}

	pat_record = (p_patient_record)lilly_db_read_record(session_params.engines.patients_engine.db_handle,sizeof(*pat_record),*offset);

	if (!pat_record)
	{
	  str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r";
	  str = str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  report_event(str,mtError,true);
	  return;
    }

	if (!session_params.session_manager->delete_patient_ex(session_params.session_manager,session_params.engines.patients_engine.db_handle,pat_record,*offset))
	{
	  str = "Une erreur est survenue lors de la suppression de la fiche patient sélectionnée ! Session Manager a retourné l'erreur suivante : \n\r";
	  str = str + error_code_to_string(session_params.session_manager->error_code);
	  report_event(str,mtError,true);
	  return;
	}

	report_event("Fiche supprimée avec succès",mtInformation,false);

	if (vtm_params.rec_count)
	{
	  vtm_params.rec_count--;
	}

	vtm_params.filter_rec_count = vtm_params.rec_count;

	LoadVtmBlocks(true);

	PatListView->Items->Count = vtm_params.filter_rec_count;

    PatListView->Repaint();

    return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::PatMailEditExit(TObject *Sender)
{

	if (PatMailEdit->Text == "") return;

	int len = PatMailEdit->Text.Length();
	int pos_at = PatMailEdit->Text.Pos("@");

	if ((len < 6) || (pos_at < 2) || ((PatMailEdit->Text[len - 2] != '.') && (PatMailEdit->Text[len - 3] != '.'))
	|| ((PatMailEdit->Text[len - 2] == '.') && (pos_at >= len - 3)) || ((PatMailEdit->Text[len - 3] == '.') && (pos_at >= len - 4)))
	{
	   report_event("L'adresse e-mail que vous avez spécifié est invalide !",mtWarning,false);
	   MarkFaultyComponent(PatMailEdit);
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::WarnLblTimerTimer(TObject *Sender)
{

	if ((--warn_label_animation.animation_loop_count <= 0) || (!warn_label_animation.label))
	{
	  WarnLblTimer->Enabled = false;

	  if (warn_label_animation.label)
	  {
		warn_label_animation.label->Visible = false;
	  }

	  warn_label_animation.label = NULL;

	  warn_label_animation.ping_pong = true;

	  warn_label_animation.animation_loop_count = 0;

	  return;
	}

	warn_label_animation.label->Visible = warn_label_animation.ping_pong;
	warn_label_animation.ping_pong ^= 1;

	return;

}

bool __fastcall TForm1::MarkFaultyComponent(TObject *Sender)
{

	 TEdit *edit = dynamic_cast<TEdit *>(Sender);


	 if (edit)
	 {
	   edit->Color = (TColor)0x00DBB7FF;
	  //ActiveControl = edit;
	   return true;
	 }

	 TLabeledEdit *labeled_edit = dynamic_cast<TLabeledEdit *>(Sender);

	 if (labeled_edit)
	 {
	   labeled_edit->Color = (TColor)0x00DBB7FF;
	  //ActiveControl = labeled_edit;
	   return true;
	 }

	 TMaskEdit *mask_edit = dynamic_cast<TMaskEdit *>(Sender);

	 if (mask_edit)
	 {
	   mask_edit->Color = (TColor)0x00DBB7FF;
	  //ActiveControl = mask_edit;
	   return true;
	 }

	 TComboBox *combo = dynamic_cast<TComboBox *>(Sender);

	 if (combo)
	 {
	   combo->Color = (TColor)0x00DBB7FF;
	   return true;
	 }

	 report_event("Erreur fatale au niveau de MarkFaultyComponent. Veuillez contacter Ben Hedibi Hassène !",mtError,true);

	 return false;

}

bool __fastcall TForm1::unMarkFaultyComponent(TObject *Sender)
{

    TEdit *edit = dynamic_cast<TEdit *>(Sender);


	if (edit)
	{
	  edit->Color = clWindow;
	  return true;
	}

	TLabeledEdit *labeled_edit = dynamic_cast<TLabeledEdit *>(Sender);

	if (labeled_edit)
	{
	  labeled_edit->Color = clWindow;
	  return true;
	}

	TMaskEdit *mask_edit = dynamic_cast<TMaskEdit *>(Sender);

	if (mask_edit)
	{
	  mask_edit->Color = clWindow;
	  return true;
	}

	TComboBox *combo = dynamic_cast<TComboBox *>(Sender);

	if (combo)
	{
	  combo->Color = clWindow;
	  return true;
	}

	report_event("Erreur fatale au niveau de unMarkFaultyComponent. Veuillez contacter Ben Hedibi Hassène !",mtError,true);

	return false;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatMailEditEnter(TObject *Sender)
{

	unMarkFaultyComponent(Sender);

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatNaissanceEditExit(TObject *Sender)
{
  t_date_time date,today;


	if (PatNaissanceEdit->Text == "  /  /    ")
	{
	  PatAgeLbl->Caption = "";
	  return;
	}

	if (!lilly_import_str_to_date_ex((puchar)PatNaissanceEdit->Text.c_str(),PatNaissanceEdit->Text.Length() * 2,&date))
	{
	  MarkFaultyComponent(PatNaissanceEdit);
	  report_event("La date de naissance que vous avez spécifié est invalide !",mtWarning,false);
	  return;
	}

	lilly_os_get_current_time_stamp(&today);

	if ((date.year > today.year) || (today.year - date.year <= 1))
	{
	  MarkFaultyComponent(PatNaissanceEdit);
	  report_event("La date de naissance que vous avez spécifié est illogique !",mtWarning,false);
	  return;
	}
	else if (date.year - today.year >= 110)
	{
	  MarkFaultyComponent(PatNaissanceEdit);
	  report_event("شنوة باش إترجعو كي سيدنا نوح ؟",mtWarning,false);
	  return;
	}

	PatAgeLbl->Caption = IntToStr((int)(today.year - date.year)) + " ans";

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatPaysComboSelect(TObject *Sender)
{

	if (PatPaysCombo->ItemIndex != 184)
	{
	  PatGouvCombo->ItemIndex = -1;
	  PatGouvCombo->Enabled = false;
	}
	else
	{
	  PatGouvCombo->Enabled = true;
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatListViewData(TObject *Sender, TListItem *Item)
{
  puint64 offset;
  p_patient_record pat_record;
  p_engine_entry pat_entry;
  int index = Item->Index;


	if (!vtm_params.vtm_manager)
	{
	  PatListView->Items->Count = 0;
	  return;
	}

	offset = (puint64)vtm_params.vtm_manager->GetData((unsigned_int)index);

	if (vtm_params.vtm_manager->GetLastError() != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Erreur au niveau du moteur TVTM_Manager ! [GetData] a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(vtm_params.vtm_manager->GetLastError());
	  report_event(err_str,mtError,true);
	  PatListView->Items->Count = 0;
	  return;
	}

	pat_entry = &session_params.engines.patients_engine;

	pat_record = (p_patient_record)lilly_db_read_record(pat_entry->db_handle,PATIENT_RECORD_SIZE,*offset);

	if (!pat_record)
	{
	  UnicodeString err_str = "Erreur au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(pat_entry->db_handle));
	  report_event(err_str,mtError,true);
	  PatListView->Items->Count = 0;
	  return;
	}

	Item->Caption = IntToStr((int)*offset);

	Item->SubItems->Add(IntToStr((int)pat_record->code_patient.unique_index));
    Item->SubItems->Add((PWCHAR)&pat_record->nom_prenom);

	if (!pat_record->date_naissance.year)
	{
	  Item->SubItems->Add("Non spécifiée");
	}
	else Item->SubItems->Add(date_to_string(&pat_record->date_naissance));

	Item->SubItems->Add((PWCHAR)&pat_record->ville);

	if (!pat_record->last_consultation_id)
	{
	  Item->SubItems->Add("Aucune !");
	}
	else
	{
	  t_lilly_db_time_stamp_informations time_stamp_infos;
	  p_engine_entry consult_entry = &session_params.engines.consultations_engine;

	  if (!lilly_db_get_record_time_stamp_infos(consult_entry->db_handle,lilly_db_index_to_record_offset(consult_entry->db_handle,pat_record->last_consultation_id),&time_stamp_infos))
	  {
		UnicodeString err_str = "Erreur au niveau de consultations [GetRecordTimeStampInfos] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
		report_event(err_str,mtError,true);
		PatListView->Items->Count = 0;
	  }

	  Item->SubItems->Add(date_to_string(&time_stamp_infos.creation_stamp.time_stamp));
	}

	Item->SubItems->Add("Non");

	return;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatListViewCustomDrawSubItem(TCustomListView *Sender, TListItem *Item,int SubItem, TCustomDrawState State, bool &DefaultDraw)
{
  TFont *font = PatListView->Canvas->Font;


	switch (SubItem)
	{
	  case 1 :
	  case 3 :
	  case 5 : font->Color = clBlue;
			   font->Style = TFontStyles();
			   break;

	  case 2 :
	  case 4 :
	  case 6 : font->Color = clBlack;
			   font->Style = TFontStyles();
			   break;
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatLastImgClick(TObject *Sender)
{

	PatListView->ItemIndex = vtm_params.rec_count - 1;

	PatListView->Items->Count = vtm_params.filter_rec_count;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatFirstImgClick(TObject *Sender)
{

	PatListView->ItemIndex = 0;

	PatListView->Items->Count = vtm_params.filter_rec_count;

	return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::PatQuickSrchEditKeyPress(TObject *Sender, System::WideChar &Key)
{
  uint64 offset;
  p_patient_record pat_record;
  unsigned_int error_code;
  int pattern_len;
  UnicodeString str;


	if (!vtm_params.vtm_manager) return;

	pattern_len = PatQuickSrchEdit->Text.Length();

	if ((PatNomRadio->Checked) && (pattern_len < 2 - (unsigned_int)((uint8)(Key == '\b')))) return;

	vtm_params.filter_rec_count = 0;

	pat_record = (p_patient_record)lilly_db_get_first_record(session_params.engines.patients_engine.db_handle);

	if (!pat_record)
	{
	  UnicodeString err_str = "Erreur au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  report_event(err_str,mtError,true);
	  PatListView->Items->Count = 0;
	  return;
	}

	str = PatQuickSrchEdit->Text;

	if (Key != '\b')
	{
	  str = str + Key;
	}
	else
	{
	  str.Delete(pattern_len--,1);
	}

	if (PatNomRadio->Checked)
	{
	  UnicodeString nom_str;

	  while (true)
	  {
		bool found = false;

		nom_str = (PWCHAR)&pat_record->nom_prenom;

		if (pattern_len > 3)
		{
		  found = (nom_str.Pos(str) > 0);
		}
		else found = (nom_str.Pos(str) == 1);

		if (found)
		{
		  offset = lilly_db_get_current_record_offset(session_params.engines.patients_engine.db_handle);
		  vtm_params.vtm_manager->UpdateBlock(vtm_params.filter_rec_count++,(opaque_ptr)&offset);
		}

		pat_record = (p_patient_record)lilly_db_get_next_record(session_params.engines.patients_engine.db_handle);

		if (!pat_record) break;
	  }
	}
	else
	{
	  UnicodeString converted;

	  while (true)
	  {
		converted = IntToStr((int)pat_record->code_patient.unique_index);

		if (converted.Pos(str) == 1)
		{
		  offset = lilly_db_get_current_record_offset(session_params.engines.patients_engine.db_handle);
		  vtm_params.vtm_manager->UpdateBlock(vtm_params.filter_rec_count++,(opaque_ptr)&offset);
		}

        pat_record = (p_patient_record)lilly_db_get_next_record(session_params.engines.patients_engine.db_handle);

		if (!pat_record) break;
	  }
	}

	error_code = lilly_db_get_last_error(session_params.engines.patients_engine.db_handle);

	if (error_code != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Erreur au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  report_event(err_str,mtError,true);
	  PatListView->Items->Count = 0;
	  return;
	}

	PatCntLbl->Caption = IntToStr((int)vtm_params.filter_rec_count);

	PatListView->Items->Count = vtm_params.filter_rec_count;

	PatListView->Repaint();

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::CreateVtmBlocks(const unsigned_int blocks_count)
{

	vtm_params.rec_count = blocks_count;

	vtm_params.filter_rec_count = blocks_count;

	vtm_params.vtm_manager = new TVTM_Manager(blocks_count,sizeof(uint64));

	if (vtm_params.vtm_manager->GetLastError() != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Erreur lors de l'initialisation du moteur TVTM_Manager ! Le moteur a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(vtm_params.vtm_manager->GetLastError());
	  report_event(err_str,mtError,true);
	}

	return;
}

void __fastcall TForm1::LoadVtmBlocks(const bool patient_vtm_block)
{
  uint64 offset;
  unsigned_int index,error_code;
  struct t_lilly_db_handle *db_handle;


	if (patient_vtm_block)
	{
	  db_handle = session_params.engines.patients_engine.db_handle;
	}
	else db_handle = session_params.engines.consultations_engine.db_handle;

	if (lilly_db_get_first_record(db_handle) == NULL)
	{
	  UnicodeString err_str = "Erreur au niveau de [GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(db_handle));
	  report_event(err_str,mtError,true);
	  return;
	}

	index = 0;

	error_code = ERROR_SUCCESS;

	while (true)
	{
	  offset = lilly_db_get_current_record_offset(db_handle);

	  if (!vtm_params.vtm_manager->UpdateBlock(index++,(opaque_ptr)&offset))
	  {
		error_code = vtm_params.vtm_manager->GetLastError();
		break;
      }

	  if (lilly_db_get_next_record(db_handle) == NULL) break;

	  //if (index >= patients_vtm_params.pat_rec_count) error bla bla
	}

	if (error_code != ERROR_SUCCESS)
	{
      UnicodeString err_str = "Erreur au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(error_code);
	  report_event(err_str,mtError,true);
	}
	else
	{
	  error_code = lilly_db_get_last_error(db_handle);

	  if (error_code != ERROR_SUCCESS)
	  {
		UnicodeString err_str = "Erreur au niveau du [UpdateBlock] ! VTM Manager a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(error_code);
		report_event(err_str,mtError,true);
	  }
	}

	return;
}

void __fastcall TForm1::DeleteVtmBlocks(void)
{

	if (vtm_params.vtm_manager)
	{
	  delete vtm_params.vtm_manager;
	}

	vtm_params.vtm_manager = NULL;
	vtm_params.rec_count = 0;
	vtm_params.filter_rec_count = 0;

    return;
}

void __fastcall TForm1::PatNomEditExit(TObject *Sender)
{
  int i,pos_str,len = PatNomEdit->Text.Length();
  bool found = false;


	if (len < 2) return;

	if (PatNomEdit->Text[len] == L'a')
	{
	  PatSexCombo->ItemIndex = 1;
	  return;
	}

	for (i = 0; i < session_params.femmes_names->Count; i++)
	{
	  if (session_params.femmes_names->Strings[i][1] == '!')
	  {
		if (!PatNomEdit->Text.Compare(session_params.femmes_names->Strings[i].SubString(2,session_params.femmes_names->Strings[i].Length() - 1)))
		{
		  found = true;
		  break;
		}
		else
		{
		  pos_str = PatNomEdit->Text.Pos(session_params.femmes_names->Strings[i].SubString(2,session_params.femmes_names->Strings[i].Length() - 1));

		  if ((pos_str > 1) && (PatNomEdit->Text[pos_str - 1] == ' '))
		  {
			found = true;
			break;
          }
		}
	  }
	  else if (PatNomEdit->Text.Pos(session_params.femmes_names->Strings[i]) > 0)
	  {
		found = true;
		break;
	  }
	}

	if (found)
	{
	  PatSexCombo->ItemIndex = 1;
	}
	else PatSexCombo->ItemIndex = 0;

	return;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::load_unknown_person_picture(TImage *image,const bool female)
{
  puchar image_path;


	image->Picture = NULL;

	if (!female)
	{
	  image_path = (puchar)&session_params.unknown_homme_picture_path->path_data;
	}
	else image_path = (puchar)&session_params.unknown_femme_picture_path->path_data;

	if (!lilly_io_file_exists(image_path))
	{
	  report_event("Certains fichiers sont introuvables ! Veuillez re-installer le logiciel pour résoudre le problème. Si le problème persiste encore après re-installation, veuillez alors contacter Ben Hedibi Hassène.",mtWarning,false);
	  return;
	}

	image->Picture->LoadFromFile((PWCHAR)image_path);

	return;
}

void __fastcall TForm1::PatSexComboSelect(TObject *Sender)
{
  t_date_time today,naissance;


	if ((patient_picture_loaded == true) || (PatSexCombo->ItemIndex < 0)) return;

	PatPicture->Picture = NULL;

	naissance.year = 0;

	if (PatNaissanceEdit->Text != "  /  /    ")
	{
	  t_date_time today,consult_date;

	  if (!lilly_import_str_to_date_ex((puchar)PatNaissanceEdit->Text.c_str(),PatNaissanceEdit->Text.Length() * 2,&naissance))
	  {
		MarkFaultyComponent(PatNaissanceEdit);
		report_event("La date de naissance que vous avez spécifié est invalide !",mtWarning,false);
		return;
	  }
	}

	lilly_os_get_current_time_stamp(&today);

	customize_picture(PatPicture,today.year - naissance.year,(PatSexCombo->ItemIndex == 0));

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatConsultViewClick(TObject *Sender)
{
  int index;


	if ((!PatConsultView->SelectionCount) || (!PatConsultView->Selected->Parent)) return;

	index = PatConsultView->Selected->Parent->Index;

	if ((index >= PatientConsultationsTable->count) || ((int64)PatientConsultationsTable->offsets[index] <= 0))
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}

	session_params.engines.consultations_engine.current_record = lilly_db_read_record(session_params.engines.consultations_engine.db_handle,CONSULTATION_RECORD_SIZE,
	PatientConsultationsTable->offsets[index]);

	if (session_params.engines.consultations_engine.current_record == NULL)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  return;
	}

	Navigate(0,2);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatCancelImgClick(TObject *Sender)
{
	cancel_patient(this);

    return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatDeleteImgClick(TObject *Sender)
{
	delete_patient(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PatEditImgClick(TObject *Sender)
{
	edit_patient(this);

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PatValidateImgClick(TObject *Sender)
{
	validate_patient(this);

    return;
}

//---------------------------------------------------------------------------


void __fastcall TForm1::PatListViewDblClick(TObject *Sender)
{
  puint64 offset;


	if (!PatListView->SelCount) return;

	offset = (puint64)vtm_params.vtm_manager->GetData(PatListView->Selected->Index);

	if (vtm_params.vtm_manager->GetLastError() != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau du VTM Manager ! Le moteur a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(vtm_params.vtm_manager->GetLastError());
	  err_str = err_str + "\n\r\n\r";
	  err_str = err_str + "Veuillez contacter Ben Hedibi Hassène";
	  report_event(err_str,mtError,true);
      return;
	}

	session_params.engines.patients_engine.current_record = (p_patient_record)lilly_db_read_record(session_params.engines.patients_engine.db_handle,PATIENT_RECORD_SIZE,*offset);

	if (!session_params.engines.patients_engine.current_record)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  err_str = err_str + "\n\r\n\r";
	  err_str = err_str + "Veuillez contacter Ben Hedibi Hassène";
	  report_event(err_str,mtError,true);
	}

	session_params.engines.patients_engine.edit_mode = false;

	Navigate(1,0);

	return;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::PatListViewKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{

	switch (Key)
	{
		case VK_ESCAPE : PatAucunRadio->Checked = true;
                         break;

		case VK_RETURN : PatListViewDblClick(Sender);
						 break;

		   case VK_ADD : PatListAddImgClick(Sender);
						 break;

	  case VK_SUBTRACT : PatListDelImgClick(Sender);
						 break;
	}

	return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ConsListViewData(TObject *Sender, TListItem *Item)
{
  static const WCHAR condition[2] = {'-','+'};

  puint64 offset;
  p_consultation_record consult_record;
  t_lilly_db_time_stamp_informations time_stamp_infos;
  int index = Item->Index;


	if (!vtm_params.vtm_manager)
	{
	  ConsListView->Items->Count = 0;
	  return;
	}

	offset = (puint64)vtm_params.vtm_manager->GetData((unsigned_int)index);

	if (vtm_params.vtm_manager->GetLastError() != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Erreur au niveau du moteur TVTM_Manager ! [GetData] a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(vtm_params.vtm_manager->GetLastError());
	  report_event(err_str,mtError,true);
	  ConsListView->Items->Count = 0;
	  return;
	}

	consult_record = (p_consultation_record)lilly_db_read_record(session_params.engines.consultations_engine.db_handle,CONSULTATION_RECORD_SIZE,*offset);

	if (!consult_record)
	{
	  UnicodeString err_str = "Erreur au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  ConsListView->Items->Count = 0;
	  return;
	}

	Item->Caption = IntToStr((int)*offset);

	Item->SubItems->Add(IntToStr((int)consult_record->patient_id));

	{
	  p_patient_record pat_record = (p_patient_record)session_params.engines.patients_engine.engine->code_to_record(session_params.engines.patients_engine.engine,session_params.engines.patients_engine.db_handle,consult_record->patient_id);

	  if (!pat_record)
	  {
		UnicodeString err_str = "Erreur au niveau de [RecordLookup] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
		report_event(err_str,mtError,true);
		ConsListView->Items->Count = 0;
		return;
	  }

	  Item->SubItems->Add((PWCHAR)&pat_record->nom_prenom);
	}

	if (!lilly_db_get_record_time_stamp_infos(session_params.engines.consultations_engine.db_handle,*offset,&time_stamp_infos))
	{
	  UnicodeString err_str = "Erreur au niveau de [GetRecordTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  ConsListView->Items->Count = 0;
	  return;
    }

	Item->SubItems->Add(date_to_string(&time_stamp_infos.creation_stamp.time_stamp));

	Item->SubItems->Add(condition[consult_record->audiogram_id != 0]);
	Item->SubItems->Add(condition[consult_record->tympanogram_id != 0]);
	Item->SubItems->Add(condition[consult_record->gainp_id != 0]);
	Item->SubItems->Add(condition[consult_record->audiovoc_id != 0]);

	{
	  p_operateur_record op_record = (p_operateur_record)session_params.engines.operators_engine.engine->code_to_record(session_params.engines.operators_engine.engine,
	  session_params.engines.operators_engine.db_handle,time_stamp_infos.creation_stamp.operator_id);

	  if (!op_record)
	  {
        UnicodeString err_str = "Erreur au niveau de [RecordLookup] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.operators_engine.db_handle));
		report_event(err_str,mtError,true);
		ConsListView->Items->Count = 0;
		return;
	  }

	  Item->SubItems->Add((PWCHAR)&op_record->nom_prenom);
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsListViewCustomDrawSubItem(TCustomListView *Sender, TListItem *Item,int SubItem, TCustomDrawState State, bool &DefaultDraw)
{
  TFont *font = ConsListView->Canvas->Font;


	switch (SubItem)
	{
	  case 1 :
	  case 3 : font->Color = clBlue;
			   font->Style = TFontStyles();
			   break;

	  case 2 :
	  case 8 : font->Color = clBlack;
			   font->Style = TFontStyles();
			   break;

	  case 4 :
	  case 5 :
	  case 6 :
	  case 7 : font->Color = clBlack;

			   if (Item->SubItems->Strings[SubItem - 1].c_str()[0] == '+')
			   {
				 font->Style = TFontStyles() << fsBold;
				 ConsListView->Canvas->Brush->Color = (TColor)0xFFCCCC;
			   }
			   else
			   {
				 font->Style = TFontStyles();
				 ConsListView->Canvas->Brush->Color = clWindow;
			   }

			   break;
	}

	return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ConsFirstImgClick(TObject *Sender)
{

	ConsListView->ItemIndex = 0;

	ConsListView->Items->Count = vtm_params.filter_rec_count;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsLastImgClick(TObject *Sender)
{

	ConsListView->ItemIndex = vtm_params.rec_count - 1;

	ConsListView->Items->Count = vtm_params.filter_rec_count;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsFltCodeEditKeyPress(TObject *Sender, System::WideChar &Key)
{

	ConsFltNomEdit->Text = "";

    if (vtm_params.rec_count != vtm_params.filter_rec_count)
	{
	  ConsCntLbl->Caption = IntToStr((int)vtm_params.rec_count);

	  vtm_params.filter_rec_count = vtm_params.rec_count;

	  LoadVtmBlocks(false);

	  ConsListView->Items->Count = vtm_params.rec_count;

	  ConsListView->Repaint();
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsFltNomEditKeyPress(TObject *Sender, System::WideChar &Key)
{

	ConsFltCodeEdit->Text = "";

	if (vtm_params.rec_count != vtm_params.filter_rec_count)
	{
	  ConsCntLbl->Caption = IntToStr((int)vtm_params.rec_count);

	  vtm_params.filter_rec_count = vtm_params.rec_count;

	  LoadVtmBlocks(false);

	  ConsListView->Items->Count = vtm_params.rec_count;

	  ConsListView->Repaint();
	}

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsFltLblMouseEnter(TObject *Sender)
{

	ConsFltLbl->Font->Color = clBlue;

	ConsFltShape->Pen->Color = clBlack;

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsFltLblMouseLeave(TObject *Sender)
{

	ConsFltLbl->Font->Color = clWindowText;

	ConsFltShape->Pen->Color = clMedGray;

	return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsFltImgClick(TObject *Sender)
{
  p_consultation_record consult_record;
  p_patient_record pat_record;
  p_operateur_record op_record;
  unsigned_int error_code;
  uint64 offset;
  t_date_time today;
  t_lilly_db_time_stamp_informations consult_time_stamp;
  t_consultations_filter_params filter_params;
  UnicodeString str;
  bool match_found;


	avcore_memset(&filter_params,0,sizeof(filter_params));

	filter_params.audiogram = ConsFltAudiogChk->Checked;
	filter_params.tympano = ConsFltTympanoChk->Checked;
	filter_params.gainp = ConsFltGpChk->Checked;
	filter_params.audiovoc = ConsFltAvocChk->Checked;

	if ((!filter_params.audiogram) && (!filter_params.tympano) && (!filter_params.gainp) && (!filter_params.audiovoc))
	{
	  report_event("La requête de filtrage est vide ! Vous devez cocher la case d'au moins 1 élément de consultation parmis ceux-ci : Audiogramme,Tympanogramme,Gain Prothétique et Audiométrie vocale",mtWarning,false);
	  return;
    }

	filter_params.Patient = ConsFltNomEdit->Text;

	if (filter_params.Patient != "")
	{
	  filter_params.Patient.UpperCase();
	}

	if (ConsFltCodeEdit->Text != "")
	{
	  filter_params.codep = (unsigned_int)StrToInt(ConsFltCodeEdit->Text);
	}

	lilly_os_get_current_time_stamp(&today);

	if (ConsFltDateEdit1->Text != "  /  /    ")
	{
	  if (!lilly_import_str_to_date_ex((puchar)ConsFltDateEdit1->Text.c_str(),ConsFltDateEdit1->Text.Length() * 2,&filter_params.date_debut))
	  {
		MarkFaultyComponent(ConsFltDateEdit1);
		report_event("La date que vous avez spécifié est invalide !",mtWarning,false);
		return;
	  }

	  if ((filter_params.date_debut.year > today.year) || ((filter_params.date_debut.year == today.year) && (filter_params.date_debut.month > today.month)) ||
	  ((filter_params.date_debut.year == today.year) && (filter_params.date_debut.month == today.month) && (filter_params.date_debut.day > today.day)))
	  {
		MarkFaultyComponent(ConsFltDateEdit1);
		report_event("La date que vous avez spécifié est illogique / dans le future !",mtWarning,false);
		return;
	  }
	}

	if (ConsFltDateEdit2->Text != "  /  /    ")
	{
	  if (!lilly_import_str_to_date_ex((puchar)ConsFltDateEdit2->Text.c_str(),ConsFltDateEdit2->Text.Length() * 2,&filter_params.date_fin))
	  {
		MarkFaultyComponent(ConsFltDateEdit2);
		report_event("La date que vous avez spécifié est invalide !",mtWarning,false);
		return;
	  }

	  if ((filter_params.date_fin.year > today.year) || ((filter_params.date_fin.year == today.year) && (filter_params.date_fin.month > today.month)) ||
	  ((filter_params.date_fin.year == today.year) && (filter_params.date_fin.month == today.month) && (filter_params.date_fin.day > today.day)))
	  {
		MarkFaultyComponent(ConsFltDateEdit2);
		report_event("La date que vous avez spécifié est illogique / dans le future !",mtWarning,false);
		return;
	  }
	}

	if (ConsFltOpCombo->Text != "")
	{
	  filter_params.Operateur = ConsFltOpCombo->Text;
      filter_params.Operateur.UpperCase();
	}

	vtm_params.filter_rec_count = 0;

	consult_record = (p_consultation_record)lilly_db_get_first_record(session_params.engines.consultations_engine.db_handle);

	if (!consult_record)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  return;
	}

	while (true)
	{
	  match_found = false;

	  if ((filter_params.codep) && (filter_params.codep != consult_record->patient_id)) goto next;

	  offset = lilly_db_get_current_record_offset(session_params.engines.consultations_engine.db_handle);

	  if (!lilly_db_get_record_time_stamp_infos(session_params.engines.consultations_engine.db_handle,offset,&consult_time_stamp))
	  {
		UnicodeString err_str = "Une erreur est survenue au niveau de [GetTimeStamp] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
		report_event(err_str,mtError,true);
		return;
	  }

	  if (filter_params.Patient != "")
	  {
		pat_record = (p_patient_record)session_params.engines.patients_engine.engine->code_to_record(session_params.engines.patients_engine.engine,session_params.engines.patients_engine.db_handle,consult_record->patient_id);

		if (!pat_record)
		{
		  UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur patient a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(session_params.engines.patients_engine.engine->error_code);
		  report_event(err_str,mtError,true);
		  return;
		}

		str = (PWCHAR)&pat_record->nom_prenom;

		if (filter_params.Patient.Length() > 3)
		{
		   match_found = (str.Pos(filter_params.Patient) > 0);
		}
		else match_found = (str.Pos(filter_params.Patient) == 1);

		if (!match_found) goto next;
	  }

	  if (filter_params.Operateur != "")
	  {
		op_record = (p_operateur_record)session_params.engines.operators_engine.engine->code_to_record(session_params.engines.operators_engine.engine,session_params.engines.operators_engine.db_handle,consult_time_stamp.creation_stamp.operator_id);

		if (!op_record)
		{
          UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur opérateurs a retourné l'erreur suivante : \n\r\n\r";
		  err_str = err_str + error_code_to_string(session_params.engines.operators_engine.engine->error_code);
		  report_event(err_str,mtError,true);
		  return;
		}

		str = (PWCHAR)&op_record->nom_prenom;

		str.UpperCase();

		if (filter_params.Operateur != str) goto next;
	  }

	  if (filter_params.date_debut.year)
	  {
		if (!filter_params.date_fin.year)
		{
		  match_found = (lilly_compare_dates(&filter_params.date_debut,&consult_time_stamp.creation_stamp.time_stamp) == DATE_IS_EQUAL);
		}
		else
		{
		  unsigned_int debut_match_result,fin_match_result;

		  debut_match_result = lilly_compare_dates(&consult_time_stamp.creation_stamp.time_stamp,&filter_params.date_debut);

		  fin_match_result = lilly_compare_dates(&consult_time_stamp.creation_stamp.time_stamp,&filter_params.date_fin);

		  match_found = (((debut_match_result == DATE_IS_EQUAL) || (debut_match_result == DATE_IS_GREAT)) &&
		  ((fin_match_result == DATE_IS_EQUAL) || (fin_match_result == DATE_IS_LESS)));
		}

		if (!match_found) goto next;
	  }


	  match_found = (filter_params.audiogram && (consult_record->audiogram_id != 0)) || (filter_params.tympano && (consult_record->tympanogram_id != 0)) ||
	  (filter_params.gainp && (consult_record->gainp_id != 0)) || (filter_params.audiovoc && (consult_record->audiovoc_id != 0));

	  if (match_found)
	  {
		matched :

		offset = lilly_db_get_current_record_offset(session_params.engines.consultations_engine.db_handle);

		vtm_params.vtm_manager->UpdateBlock(vtm_params.filter_rec_count++,(opaque_ptr)&offset);
	  }

	  next :

	  consult_record = (p_consultation_record)lilly_db_get_next_record(session_params.engines.consultations_engine.db_handle);

	  if (!consult_record) break;

	  Application->ProcessMessages();
	}

	if (lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle) != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.consultations_engine.db_handle));
	  report_event(err_str,mtError,true);
	  return;
	}

	ConsCntLbl->Caption = IntToStr((int)vtm_params.filter_rec_count);

	ConsListView->Items->Count = vtm_params.filter_rec_count;

	ConsListView->Repaint();

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsFltDateEdit1Enter(TObject *Sender)
{

	unMarkFaultyComponent(Sender);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsFltDateEdit1KeyPress(TObject *Sender, System::WideChar &Key)
{

	if (vtm_params.rec_count != vtm_params.filter_rec_count)
	 {
	   ConsCntLbl->Caption = IntToStr((int)vtm_params.rec_count);

	   vtm_params.filter_rec_count = vtm_params.rec_count;

	   LoadVtmBlocks(false);

	   ConsListView->Items->Count = vtm_params.rec_count;

	   ConsListView->Repaint();
	 }

	 return;
}

void __fastcall TForm1::fill_old_consultations_treeview(TTreeView *treeview)
{
  p_consultation_record consult_record;
  TTreeNode *child,*parent;
  t_lilly_db_time_stamp_informations consult_timestamp_infos;


	 if ((!PatientConsultationsTable) || ((signed_int)PatientConsultationsTable->count <= 0))
	 {
	   report_event(error_code_to_string(API_ERROR),mtError,true);
	   return;
	 }

	 if (treeview->Items->Count)
	 {
	   treeview->Items->Clear();
	 }

	 for (int i = 0; i < PatientConsultationsTable->count; i++)
	 {
	   consult_record = (p_consultation_record)lilly_db_read_record(session_params.engines.consultations_engine.db_handle,sizeof(*consult_record),
	   PatientConsultationsTable->offsets[i]);

	   if ((!consult_record) || (!lilly_db_get_record_time_stamp_infos(session_params.engines.consultations_engine.db_handle,
	   PatientConsultationsTable->offsets[i],&consult_timestamp_infos))) break;

	   if (!consult_timestamp_infos.creation_stamp.time_stamp.year)
	   {
		 parent = treeview->Items->AddChild(NULL,"Non spécifiée");
	   }
	   else parent = treeview->Items->AddChild(NULL,date_to_string(&consult_timestamp_infos.creation_stamp.time_stamp));

	   if (consult_record->audiogram_id)
	   {
		 child = treeview->Items->AddChild(parent,"Audiogramme");
	   }

	   if (consult_record->tympanogram_id)
	   {
		 child = treeview->Items->AddChild(parent,"Tympanogramme");
	   }

	   if (consult_record->gainp_id)
	   {
		 child = treeview->Items->AddChild(parent,"Gain Prothétique");
	   }

	   if (consult_record->audiovoc_id)
	   {
		 child = treeview->Items->AddChild(parent,"Audiométrie Vocale");
	   }
	 }

     return;
}

void __fastcall TForm1::ConsListViewDblClick(TObject *Sender)
{
  puint64 offset;


	if (!ConsListView->SelCount) return;

	offset = (puint64)vtm_params.vtm_manager->GetData(ConsListView->Selected->Index);

	if (vtm_params.vtm_manager->GetLastError() != ERROR_SUCCESS)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau du VTM Manager ! Le moteur a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(vtm_params.vtm_manager->GetLastError());
	  err_str = err_str + "\n\r\n\r";
	  err_str = err_str + "Veuillez contacter Ben Hedibi Hassène";
	  report_event(err_str,mtError,true);
      return;
	}

	session_params.engines.consultations_engine.current_record = lilly_db_read_record(session_params.engines.consultations_engine.db_handle,CONSULTATION_RECORD_SIZE,*offset);

	if (!session_params.engines.consultations_engine.current_record)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [ReadRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(lilly_db_get_last_error(session_params.engines.patients_engine.db_handle));
	  err_str = err_str + "\n\r\n\r";
	  err_str = err_str + "Veuillez contacter Ben Hedibi Hassène";
	  report_event(err_str,mtError,true);
	  return;
	}

	session_params.engines.patients_engine.current_record = session_params.engines.patients_engine.engine->code_to_record(session_params.engines.patients_engine.engine,session_params.engines.patients_engine.db_handle,
	((p_consultation_record)session_params.engines.consultations_engine.current_record)->patient_id);

	if (!session_params.engines.patients_engine.current_record)
	{
	  UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur patients a retourné l'erreur suivante : \n\r\n\r";
	  err_str = err_str + error_code_to_string(session_params.engines.patients_engine.engine->error_code);
	  err_str = err_str + "\n\r\n\r";
	  err_str = err_str + "Veuillez contacter Ben Hedibi Hassène";
	  report_event(err_str,mtError,true);
      return;
	}

	session_params.engines.consultations_engine.edit_mode = false;

	Navigate(3,2);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsListAddImgClick(TObject *Sender)
{
   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsListEditImgClick(TObject *Sender)
{
   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsListDelImgClick(TObject *Sender)
{
   return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsListViewKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{

    switch (Key)
	{
		case VK_ESCAPE : if (vtm_params.rec_count != vtm_params.filter_rec_count)
						 {
						   ConsCntLbl->Caption = IntToStr((int)vtm_params.rec_count);
						   vtm_params.filter_rec_count = vtm_params.rec_count;
						   LoadVtmBlocks(false);
						   ConsListView->Items->Count = vtm_params.rec_count;
						   ConsListView->Repaint();
						 }

						 break;

		case VK_RETURN : ConsListViewDblClick(Sender);
						 break;

		   case VK_ADD : ConsListAddImgClick(Sender);
						 break;

	  case VK_SUBTRACT : ConsListDelImgClick(Sender);
						 break;
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatListViewClick(TObject *Sender)
{
  p_consultation_record consult_record;
  p_engine_entry engine_entry;


	if (!ConsPatListView->SelCount) return;

	consult_record = (p_consultation_record)session_params.engines.consultations_engine.current_record;

	if (!consult_record)
	{
	  report_event("Vous devez commencer par valider la consultation !",mtWarning,false);
	  return;
	}

	if (!ConsPatListView->Selected->ImageIndex)
	{
	  t_date_time today,consult_date;

	  if (!session_params.engines.consultations_engine.edit_mode)
	  {
		report_event("Vous devez mettre la consultation en mode édition pour pouvoir ajouter des nouvelles opérations !",mtWarning,false);
		return;
	  }

	  if (!string_to_date_stamp((puchar)ConsPatDateLbl->Caption.c_str(),20,&consult_date))
	  {
		report_event(error_code_to_string(API_ERROR),mtError,true);
		return;
	  }

	  lilly_os_get_current_time_stamp(&today);

	  if ((today.day != consult_date.day) && (today.month != consult_date.month) && (today.year != consult_date.year))
	  {
		UnicodeString str = "Vous ne pouvez pas ajouter des nouvelles opérations à une ancienne consultation, vous pouvez juste modifier ou supprimer les opérations qui sont déjà associées. \n\r\n\r";
		str = str + "Si vous voulez insérer un nouveau audiogramme ou toute autre opération, vous devez créer une nouvelle consultation.";
		report_event(str,mtWarning,false);
		return;
	  }
	}

	switch (ConsPatListView->Selected->Index)
	{
		 case 0 : engine_entry = &session_params.engines.audiograms_engine;

				  engine_entry->current_record = NULL;

				  if ((consult_record) && (consult_record->audiogram_id))
				  {
					engine_entry->current_record = engine_entry->engine->code_to_record(engine_entry->engine,engine_entry->db_handle,consult_record->audiogram_id);

					if (!engine_entry->current_record)
					{
					  UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur des audiogrammes a retourné l'erreur suivante : \n\r\n\r";
					  err_str = err_str + error_code_to_string(engine_entry->engine->error_code);
					  report_event(err_str,mtError,true);
					  return;
                    }
				  }

				  engine_entry->edit_mode = (engine_entry->current_record == NULL);

				  Navigate(2,4);

				  break;

		 case 1 : engine_entry = &session_params.engines.tympanograms_engine;

				  engine_entry->current_record = NULL;

				  if ((consult_record) && (consult_record->tympanogram_id))
				  {
					engine_entry->current_record = engine_entry->engine->code_to_record(engine_entry->engine,engine_entry->db_handle,consult_record->tympanogram_id);

					if (!engine_entry->current_record)
					{
					  UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur des tympanogrammes a retourné l'erreur suivante : \n\r\n\r";
					  err_str = err_str + error_code_to_string(engine_entry->engine->error_code);
					  report_event(err_str,mtError,true);
					  return;
                    }
				  }

				  engine_entry->edit_mode = (engine_entry->current_record == NULL);

				  Navigate(2,5);

				  break;

		 case 2 : engine_entry = &session_params.engines.gainprots_engine;

				  engine_entry->current_record = NULL;

				  if ((consult_record) && (consult_record->gainp_id))
				  {
					engine_entry->current_record = engine_entry->engine->code_to_record(engine_entry->engine,engine_entry->db_handle,consult_record->gainp_id);

					if (!engine_entry->current_record)
					{
					  UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur des Gains Prothétiques a retourné l'erreur suivante : \n\r\n\r";
					  err_str = err_str + error_code_to_string(engine_entry->engine->error_code);
					  report_event(err_str,mtError,true);
					  return;
                    }
				  }

				  engine_entry->edit_mode = (engine_entry->current_record == NULL);

				  Navigate(2,7);

				  break;

		 case 3 : engine_entry = &session_params.engines.audiovocs_engine;

				  engine_entry->current_record = NULL;

				  if ((consult_record) && (consult_record->audiovoc_id))
				  {
					engine_entry->current_record = engine_entry->engine->code_to_record(engine_entry->engine,engine_entry->db_handle,consult_record->audiovoc_id);

					if (!engine_entry->current_record)
					{
					  UnicodeString err_str = "Une erreur est survenue au niveau de [RecordLookup] ! Le moteur des Audiométries vocales a retourné l'erreur suivante : \n\r\n\r";
					  err_str = err_str + error_code_to_string(engine_entry->engine->error_code);
					  report_event(err_str,mtError,true);
					  return;
                    }
				  }

				  engine_entry->edit_mode = (engine_entry->current_record == NULL);

				  Navigate(2,6);

				  break;

	   default : report_event(error_code_to_string(API_ERROR),mtError,true);
				  break;
	}

	return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AudiogCancelImgClick(TObject *Sender)
{

	cancel_audiogram(this);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AudiogDelImgClick(TObject *Sender)
{
	delete_audiogram(this);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AudiogEditImgClick(TObject *Sender)
{

	edit_audiogram(this);

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AudiogValidImgClick(TObject *Sender)
{

	validate_audiogram(this);

    return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AudiogViewImgClick(TObject *Sender)
{
	preview_audiogram_grph(this);

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::AudiogAddGraphImgClick(TObject *Sender)
{

	add_audiogram_grph_type(this);

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::TympCancelImgClick(TObject *Sender)
{

	cancel_tympanogram(this);

	return;
}

void __fastcall TForm1::TympDelImgClick(TObject *Sender)
{
	delete_tympanogram(this);

    return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TympEditImgClick(TObject *Sender)
{
	edit_tympanogram(this);

    return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::TympValidImgClick(TObject *Sender)
{
	validate_tympanogram(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TympViewImgClick(TObject *Sender)
{

	preview_tympanogram_grph(this);

	return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AvocValidImgClick(TObject *Sender)
{

	validate_audiovoc(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocEditImgClick(TObject *Sender)
{
	edit_audiovoc(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocDelImgClick(TObject *Sender)
{
	delete_audiovoc(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocCancelImgClick(TObject *Sender)
{
	cancel_audiovoc(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocViewImgClick(TObject *Sender)
{
    preview_audiovoc_grph(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AvocAddGrphImgClick(TObject *Sender)
{
	add_audiovoc_grph_type(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpValidImgClick(TObject *Sender)
{
	validate_gainp(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpEditImgClick(TObject *Sender)
{
	edit_gainp(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpDelImgClick(TObject *Sender)
{
	delete_gainp(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpViewImgClick(TObject *Sender)
{
	preview_gainp_grph(this);

    return;
}

//---------------------------------------------------------------------------


void __fastcall TForm1::GainpCancelImgClick(TObject *Sender)
{
	cancel_gainp(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GainpAddGrphImgClick(TObject *Sender)
{
	add_gainp_grph_type(this);

	return;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ConsPatValidImgClick(TObject *Sender)
{
	return validate_consultation(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatEditImgClick(TObject *Sender)
{
	edit_consultation(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatDelImgClick(TObject *Sender)
{
	delete_consultation(this);

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatCancelImgClick(TObject *Sender)
{

	cancel_consultation(this);

	return;
}
//---------------------------------------------------------------------------

bool __fastcall TForm1::customize_picture(TImage *image,const int age,const bool male_gender)
{
  UnicodeString filename;
  TMemoryStream *mem_strm;
  TBitmap *bitmap;


	if (age <= 3)
	{
	  filename = "bb.dat";
	}
	else if (age < 11)
	{
	  if (male_gender)
	  {
		filename = "childm.dat";
	  }
	  else filename = "childf.dat";

	}
	else if (age < 20)
	{
	   if (male_gender)
	   {
		 filename = "adom.dat";
	   }
	   else filename = "adof.dat";

	}
	else if (age < 50)
	{
	   if (male_gender)
	   {
		 filename = "m.dat";
	   }
	   else filename = "f.dat";
	}
	else
	{
	  if (male_gender)
	  {
		filename = "gm.dat";
	  }
	  else filename = "gf.dat";
	}

  try
	{
	  resize_picture(image,filename);

      return true;
	}

  __except(EXCEPTION_EXECUTE_HANDLER)
	{
	  return false;
    }
}

void __fastcall TForm1::ConsPatNameLblMouseEnter(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


	if (session_params.engines.consultations_engine.edit_mode) return;

	label->Font->Color = clBlue;

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatNameLblMouseLeave(TObject *Sender)
{
  TLabel *label = static_cast<TLabel *>(Sender);


    if (session_params.engines.consultations_engine.edit_mode) return;

	label->Font->Color = clWindowText;

	return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::ConsPatNameLblClick(TObject *Sender)
{

	if (session_params.engines.consultations_engine.edit_mode) return;

	Navigate(2,0);

	return;
}

void __fastcall TForm1::OpNameLblClick(TObject *Sender)
{

   if (ask_event("Êtes-vous sûres de vouloir vous déconnecter ?"))
   {
	 LogOff();
   }

   return;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::LogOff()
{

	session_params.CurrentOpName = "";

	session_params.current_operator_id = 0;

	if (!LogIn())
	{
      Application->Terminate();
	}

	Navigate(0,8);

	Show();

	Application->RestoreTopMosts();

	return;
}

bool __fastcall TForm1::LogIn()
{
  UnicodeString str;
  TLoginFrm *login_frm = new TLoginFrm(this);


  Hide();

  try
	  {
		login_frm->Caption = Caption;

		try_again :

		switch (login_frm->ShowModal())
		{
			  case mrOk : if (Check_Credentials(login_frm->LoginEdit->Text,login_frm->PassEdit->Text)) return true;

						 if (ask_event("Login ou mot de passe invalide. Voulez-vous essayer encore ?")) goto try_again;

						 return false;

		  case mrCancel : if (ask_event("Vous devez vous identifier comme opérateur pour continuer. Voulez-vous essayer encore ?")) goto try_again;

						  return false;

				default : report_event(error_code_to_string(API_ERROR),mtError,true);
						  return false;
		}

	  }

	__finally
	  {
		delete login_frm;
	  }
}

bool __fastcall TForm1::Check_Credentials(UnicodeString login,UnicodeString password)
{
  p_operateur_record op_record;
  p_engine_entry op_entry;
  uint32 psw_hash;


	if ((login.UpperCase() == "ADMIN") && (password.UpperCase() == ""))
	{
	  session_params.CurrentOpName = "Admin / Super User";
	  session_params.current_operator_id = 0;
	  return true;
	}
	else if (password.Length() < 8) return false;

	op_entry = &session_params.engines.operators_engine;

	op_record = (p_operateur_record)lilly_db_get_first_record(op_entry->db_handle);

	if (!op_record)
	{
	  UnicodeString str;
	  unsigned_int error_code = lilly_db_get_last_error(op_entry->db_handle);

	  if (error_code == ERROR_SUCCESS)
	  {
		HandleOperatorPage();

		op_record = (p_operateur_record)lilly_db_get_first_record(op_entry->db_handle);

		if (!op_record)
		{
		  report_event("Vous ne pourrez pas utiliser le logiciel tant que vous n'avez pas crée un nouvel profil opérateur !",mtError,true);
		  return false;
		}
		else
		{
		  str = "Votre profil opérateur a été crée avec succès. Le logiciel va maintenant se terminer, veuillez donc redémarrer le logiciel. \n\r";
		  str = str + "Le nom d'opérateur que vous avez spécifié est désormais votre login, vous utiliserez le mot de passe qui vous a été communiqué par le logiciel pour vous connecter";
		  report_event(str,mtInformation,true);
		  return true;
        }
	  }
	  else
	  {
		str = "Une erreur est survenue au niveau de [GetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(error_code);
		str = str + "\n\r\n\r";
		str = str + "Veuillez contacter votre support technique !";
		report_event(str,mtError,true);
		return false;
      }
	}

	psw_hash = avcore_whex_to_dword((puchar)password.c_str());

	while (true)
	{
	  if ((avcore_memcmp(&op_record->nom_prenom,(puchar)login.c_str(),login.Length() * 2)) && (psw_hash == op_record->code_operateur.crc32))
	  {
		session_params.CurrentOpName = format_name((PWCHAR)&op_record->nom_prenom);
		session_params.current_operator_id = op_record->code_operateur.crc32;
		return true;
      }

	  op_record = (p_operateur_record)lilly_db_get_next_record(op_entry->db_handle);

	  if (!op_record) break;
	}

	if (!op_record)
	{
	  unsigned_int error_code = lilly_db_get_last_error(op_entry->db_handle);

	  if (error_code != ERROR_SUCCESS)
	  {
		UnicodeString str;

		str = "Une erreur est survenue au niveau de [GetNextRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
		str = str + error_code_to_string(error_code);
		str = str + "\n\r\n\r";
		str = str + "Veuillez contacter votre support technique !";

		report_event(str,mtError,true);
	  }
	}

	return false;
}

void __fastcall TForm1::Consultation_OnChange_Event_Handler(const uint32 caller_engine_id,const uint32 record_id,const t_consultation_onchange_event_type ChangeEventType)
{
  p_consultation_record consult_record;
  p_engine_entry consult_entry;
  bool found = false;


	consult_entry = &session_params.engines.consultations_engine;

	consult_record = (p_consultation_record)consult_entry->current_record;

	if (!consult_record)
	{
	  report_event(error_code_to_string(API_ERROR),mtError,true);
	  return;
	}


	switch (ChangeEventType)
	{
		 case t_record_id_change_type : if (!record_id)
										{
										  report_event(error_code_to_string(API_ERROR),mtError,true);
										  return;
										}

										consult_record = (p_consultation_record)lilly_db_get_first_record(consult_entry->db_handle);

										if (!consult_record)
										{
										  UnicodeString str = "Une erreur est survenue au niveau de [ConsultationGetFirstRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
										  str = str + error_code_to_string(lilly_db_get_last_error(consult_entry->db_handle));
										  str = str + "\n\r\n\rVeuillez contacter votre support technique";
										  report_event(str,mtError,true);
										  return;
										}

										while (true)
										{
										  switch (caller_engine_id)
										  {
													   case PATIENT_DB_SIGNATURE : found = (consult_record->patient_id == record_id);
																				   break;

													 case AUDIOGRAM_DB_SIGNATURE : found = (consult_record->audiogram_id == record_id);
																				   break;

												   case TYMPANOGRAM_DB_SIGNATURE : found = (consult_record->tympanogram_id = record_id);
																				   break;

											  case GAIN_PROTHETIQUE_DB_SIGNATURE : found = (consult_record->gainp_id == record_id);
																				   break;

											case AUDIOMETRIE_VOCALE_DB_SIGNATURE : found = (consult_record->audiovoc_id == record_id);
																				   break;

																		 default : report_event(error_code_to_string(API_ERROR),mtError,true);
																				   return;
										  }

										  if (found) break;

										  consult_record = (p_consultation_record)lilly_db_get_next_record(consult_entry->db_handle);

										  if (!consult_record) break;
										}

										if (!consult_record)
										{
										  report_event(error_code_to_string(INDEX_OUT_OF_RANGE),mtError,false);
										  return;
										}

										consult_entry->current_record = consult_record;

                                        break;

	  case t_record_state_change_type : switch (caller_engine_id)
										{
													 case PATIENT_DB_SIGNATURE : consult_record->patient_id = record_id;
																				 break;

												   case AUDIOGRAM_DB_SIGNATURE : consult_record->audiogram_id = record_id;
																				 break;

												 case TYMPANOGRAM_DB_SIGNATURE : consult_record->tympanogram_id = record_id;
																				 break;

											case GAIN_PROTHETIQUE_DB_SIGNATURE : consult_record->gainp_id = record_id;
																				 break;

										  case AUDIOMETRIE_VOCALE_DB_SIGNATURE : consult_record->audiovoc_id = record_id;
																				 break;

																	   default : report_event(error_code_to_string(API_ERROR),mtError,true);
                                                                                 return;
										}

										if (!consult_entry->engine->edit_record(consult_entry->engine,consult_entry->db_handle,consult_record,
										lilly_db_index_to_record_offset(consult_entry->db_handle,consult_record->code_consultation.unique_index)))
										{
										  UnicodeString str = "Une erreur est survenue au niveau de [ConsultationEditRecord] ! LillyDB a retourné l'erreur suivante : \n\r\n\r";
										  str = str + error_code_to_string(lilly_db_get_last_error(consult_entry->db_handle));
										  str = str + "\n\r\n\rVeuillez contacter votre support technique";
										  report_event(str,mtError,true);
										  return;
										}

                                        break;

							  default : break;
	}

	return;
}

void __fastcall TForm1::Switch_Annuler_Retour_Button(const uint32 caller_engine_id,const bool edit_mode)
{

	switch (caller_engine_id)
	{
				 case PATIENT_DB_SIGNATURE : if (edit_mode)
											 {
											   PatCancelLbl->Left = 704;
											   PatCancelLbl->Caption = "&Annuler";
											 }
											 else
											 {
											   PatCancelLbl->Left = 706;
											   PatCancelLbl->Caption = "&Retour";
											 }

											 break;

			   case AUDIOGRAM_DB_SIGNATURE : if (edit_mode)
											 {
											   AudiogCancelLbl->Left = 536;
											   AudiogCancelLbl->Caption = "&Annuler";
											 }
											 else
											 {
											   AudiogCancelLbl->Left = 540;
											   AudiogCancelLbl->Caption = "&Retour";
											 }

											 break;

			 case TYMPANOGRAM_DB_SIGNATURE : if (edit_mode)
											 {
											   TympCancelLbl->Left = 523;
											   TympCancelLbl->Caption = "&Annuler";
											 }
											 else
											 {
											   TympCancelLbl->Left = 526;
											   TympCancelLbl->Caption = "&Retour";
											 }

											 break;

		case GAIN_PROTHETIQUE_DB_SIGNATURE : if (edit_mode)
											 {
											   GainpCancelLbl->Left = 492;
											   GainpCancelLbl->Caption = "&Annuler";
											 }
											 else
											 {
											   GainpCancelLbl->Left = 494;
											   GainpCancelLbl->Caption = "&Retour";
											 }

											 break;

	  case AUDIOMETRIE_VOCALE_DB_SIGNATURE : if (edit_mode)
											 {
											   AvocCancelLbl->Left = 509;
											   AvocCancelLbl->Caption = "&Annuler";
											 }
											 else
											 {
											   AvocCancelLbl->Left = 512;
											   AvocCancelLbl->Caption = "&Retour";
											 }

											 break;

		   case CONSULTATIONS_DB_SIGNATURE : if (edit_mode)
											 {
											   ConsPatCancelLbl->Left = 713;
											   ConsPatCancelLbl->Caption = "&Annuler";
											 }
											 else
											 {
											   ConsPatCancelLbl->Left = 716;
											   ConsPatCancelLbl->Caption = "&Retour";
											 }

											 break;

								   default : report_event(error_code_to_string(API_ERROR),mtError,true);
											 break;
	}

	return;
}

void __fastcall TForm1::HandleDemographicStatistics(void)
{
  TDemoStatFrm *demo_stat_frm = NULL;
  unsigned_int error_code;
  t_demographic_stat_table stat_table;


	error_code = collect_demographic_statistics_data(&stat_table,session_params.engines.patients_engine.db_handle,105);

	if (error_code != ERROR_SUCCESS)
	{
	  UnicodeString str = "Une erreur est survenue ! Le moteur statistiques a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(error_code) + "\n\r\n\r";
	  str = str + "Veuillez contacter votre support technique.";
	  report_event(str,mtError,false);
	  return;
	}

	demo_stat_frm = new TDemoStatFrm(this);

 try
	{

	  demo_stat_frm->stat_table = &stat_table;

	  demo_stat_frm->FullStats(true);

      demo_stat_frm->ShowModal();
	}

  __finally
	{
	  delete demo_stat_frm;
	}

	return;
}

void __fastcall TForm1::HandleGeographicStatistics(void)
{
  TGeoFrm *geo_stat_frm = NULL;
  TStringList *list = NULL;
  unsigned_int error_code;
  t_geographic_stat_table stat_table;


	error_code = collect_geographic_statistics_data(&stat_table,session_params.engines.patients_engine.db_handle,105);

	if (error_code != ERROR_SUCCESS)
	{
	  UnicodeString str = "Une erreur est survenue ! Le moteur statistiques a retourné l'erreur suivante : \n\r\n\r";
	  str = str + error_code_to_string(error_code) + "\n\r\n\r";
	  str = str + "Veuillez contacter votre support technique.";
	  report_event(str,mtError,false);
	  return;
	}

	geo_stat_frm = new TGeoFrm(this);

 try
	{
	  list = new TStringList;

	  list->LoadFromFile((PWCHAR)&session_params.pays_path->path_data);

	  geo_stat_frm->stat_table = &stat_table;
	  geo_stat_frm->list = list;

	  geo_stat_frm->GlobalStats();

	  geo_stat_frm->ShowModal();
	}

  __finally
	{
	  if (list)
	  {
		list->Clear();
		delete list;
	  }

	  delete geo_stat_frm;
	}

	return;
}

void __fastcall TForm1::HandleJobStatistics(void)
{
	return;
}

void __fastcall TForm1::HandleMedStatistics(void)
{
   return;
}

void __fastcall TForm1::HandleAudiogramsStatistics(void)
{
	return;
}

void __fastcall TForm1::HandleTympanogramsStatistics(void)
{
	return;
}

void __fastcall TForm1::HandleAvocStatistics(void)
{
   return;
}

void __fastcall TForm1::HandleGainpStatistics(void)
{
   return;
}


