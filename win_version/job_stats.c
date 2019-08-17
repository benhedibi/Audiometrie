#include "job_stats.h"
#include <patients_engine.h>
#include <cmnfnc.h>

#include <lilly_os.h>
#include <lilly_mem.h>


static boolean LILLY_CALL_CONVENTION is_jobless(const puchar job_name,const unsigned_int job_name_len)
{
	return ((job_name_len == 22) && (avcore_memcmp(job_name,(puchar)L"sans emploi",22)));
}

static boolean LILLY_CALL_CONVENTION is_bank_financial(const puchar job_name,const unsigned_int job_name_len)
{

	if ((avcore_wstrpos(job_name,(puchar)L"banqu",job_name_len)) || (avcore_wstrpos(job_name,(puchar)L"banc",job_name_len)))
	{
	  return TRUE;
	}

	if ((job_name_len == 6) && ((avcore_memcmp(job_name,(puchar)L"uib",6) || (avcore_memcmp(job_name,(puchar)L"stb",6)) ||
	(avcore_memcmp(job_name,(puchar)L"atb",6)) || (avcore_memcmp(job_name,(puchar)L"bna",6)))))
	{
	  return TRUE;
	}

	if ((job_name == 8) && (avcore_memcmp(job_name,(puchar)L"ubci",8))) return TRUE;

	if ((job_name_len == 26) && (avcore_memcmp(job_name,(puchar)L"chef d'agence",26))) return TRUE;

	if ((job_name == 10) && (avcore_memcmp(job_name,(puchar)L"b.a.d",10))) return TRUE;

	if (avcore_wstrpos(job_name,(puchar)L"financ",job_name_len)) return TRUE;

	if (avcore_wstrpos(job_name,(puchar)L"assur",job_name_len)) return TRUE;

	if (avcore_wstrpos(job_name,(puchar)L"compta",job_name_len)) return TRUE;

	if (avcore_wstrpos(job_name,(puchar)L"gestionnaire",job_name_len)) return TRUE;

    return FALSE;
}

static boolean LILLY_CALL_CONVENTION is_haut_cadre(const puchar job_name,const unsigned_int job_name_len)
{

	if (avcore_wstrpos(job_name,(puchar)L"cadre",job_name_len)) return TRUE;

	if ((avcore_wstrpos(job_name,(puchar)L"directeur",job_name_len)) || (avcore_wstrpos(job_name,(puchar)L"directrice",job_name_len))) return TRUE;

	if (avcore_wstrpos(job_name,(puchar)L"entrepreneur",job_name_len)) return TRUE;

	if (avcore_wstrpos(job_name,(puchar)L"gérant",job_name_len)) return TRUE;

	if (avcore_wstrpos(job_name,(puchar)L"homme d'affaires",job_name_len)) return TRUE;

	if ((job_name_len == 26) && (avcore_memcmp(job_name,(puchar)L"chef d'équipe",26))) return TRUE;

	if ((job_name_len == 30) && ((avcore_memcmp(job_name,(puchar)L"chef de cuisine",30)) ||
	(avcore_memcmp(job_name,(puchar)L"chef de service",30)) || (avcore_memcmp(job_name,(puchar)L"chef de section",30)))) return TRUE;

	if ((job_name_len == 32) && (avcore_memcmp(job_name,(puchar)L"chef de chantier",32))) return TRUE;

	if ((job_name_len == 34) && (avcore_memcmp(job_name,(puchar)L"chef d'entreprise",34))) return TRUE;

	if ((job_name_len == 24) && (avcore_memcmp(job_name,(puchar)L"chef d'unité",24))) return TRUE;

    return FALSE;
}

static boolean LILLY_CALL_CONVENTION is_industriel(const puchar job_name,const unsigned_int job_name_len)
{
    return FALSE;
}

static boolean LILLY_CALL_CONVENTION is_student(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_law_enforcement(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_military(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_enseignement(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_medical(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_administratif(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_audiovisuel(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_musicians(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_commerce(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_driver(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_manual_work(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_diplomatic(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_tic(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_aerospatial(const puchar job_name,const unsigned_int job_name_len)
{

}

static boolean LILLY_CALL_CONVENTION is_jurist(const puchar job_name,const unsigned_int job_name_len)
{

}

static t_job_sectors LILLY_CALL_CONVENTION job_name_to_job_sector(const puchar job_name,const unsigned_int job_name_len)
{
  typedef boolean LILLY_CALL_CONVENTION t_is_job_type_callback(const puchar job_name,const unsigned_int job_name_len);
  typedef t_is_job_type_callback *p_is_job_type_callback;

  static const p_is_job_type_callback callbacks[(unsigned_int)MAX_JOB_FAMILIES + 1] = {NULL,is_jobless,is_bank_financial,is_haut_cadre,is_industriel,is_student,is_law_enforcement,
																					   is_military,is_enseignement,is_medical,is_administratif,is_audiovisuel,is_musicians,
																					   is_commerce,is_driver,is_manual_work,is_diplomatic,is_tic,is_aerospatial,is_jurist};

  int i;


	for (i = 1; i < (unsigned_int)MAX_JOB_FAMILIES; i++)
	{
	  if (callbacks[i](job_name,job_name_len))
	  {
		return (t_job_sectors)i;
      }
	}

	return t_undefined_job_sector;
}

unsigned_int LILLY_CALL_CONVENTION collect_job_statistics_data(const p_job_stat_table stat_table,const struct t_lilly_db_handle *patient_db_handle)
{
  p_patient_record iterator;
  t_job_sectors job_sector;


    if ((!stat_table) || (!patient_db_handle)) return API_ERROR;

	avcore_memset(stat_table,0,sizeof(*stat_table));

    iterator = (p_patient_record)lilly_db_get_first_record(patient_db_handle);

	if (!iterator)
	{
	  return lilly_db_get_last_error(patient_db_handle);
	}

	while (TRUE)
	{

	  if (iterator->travail[0] == 0) goto next;

	  job_sector = job_name_to_job_sector((puchar)&iterator->travail,MACRO_MAX_VALUE(avcore_wstrlen((puchar)&iterator->travail),sizeof(iterator->travail)));

	  stat_table->jobs_sectors[(unsigned_int)job_sector].count++;
	  stat_table->jobs_sectors[(unsigned_int)job_sector].age = iterator->age_consultation;

	  if (iterator->sexe == MALE_GENDER)
	  {
		stat_table->jobs_sectors[(unsigned_int)job_sector].male_count++;
	  }
	  else stat_table->jobs_sectors[(unsigned_int)job_sector].female_count++;

	  next :

	  iterator = (p_patient_record)lilly_db_get_next_record(patient_db_handle);

	  if (!iterator) break;
	}

	return lilly_db_get_last_error(patient_db_handle);
}
