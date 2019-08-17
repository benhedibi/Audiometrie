#ifndef JOB_STATS_H
#define JOB_STATS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>
#include <lilly_db2.h>

#include "demographic_stats.h"

typedef enum {
               t_undefined_job_sector,
			   t_sans_emplois,
			   t_banques_et_finances,
               t_hauts_cadres,
			   t_industriels,
			   t_eleves_et_etudiants,
			   t_forces_de_securite,
               t_forces_armees,
			   t_enseignement,
			   t_corps_medical,
			   t_administratif,
			   t_audiovisuel,
               t_musiciens,
			   t_commerce,
			   t_conducteurs,
			   t_travail_manuel,
			   t_diplomates,
			   t_tic,
			   t_aerospatial,
			   t_juristes,
			   MAX_JOB_FAMILIES = t_juristes
			 } t_job_sectors;


typedef struct {
				 t_age_bucket jobs_sectors[(unsigned_int)MAX_JOB_FAMILIES + 1];
			   } t_job_stat_table,*p_job_stat_table;


extern unsigned_int LILLY_CALL_CONVENTION collect_job_statistics_data(const p_job_stat_table stat_table,const struct t_lilly_db_handle *patient_db_handle);


#ifdef __cplusplus
}
#endif

#endif