#ifndef GEOGRAPHIC_H
#define GEOGRAPHIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>
#include <lilly_db2.h>

#include "demographic_stats.h"

typedef enum {
			   t_afrique = 0,
			   t_europe = 1,
			   t_asie = 2,
			   t_amerique_nord = 3,
			   t_amerique_sud = 4,
			   t_oceanie = 5,
			   MAX_CONTINENT = t_oceanie
			 } t_continent_types;

typedef enum {
			   t_ariana = 0,
			   t_beja = 1,
			   t_ben_arous = 2,
			   t_bizerte = 3,
			   t_gabes = 4,
			   t_gafsa = 5,
			   t_jendouba = 6,
			   t_kairouan = 7,
			   t_kasserine = 8,
			   t_kebili = 9,
			   t_kef = 10,
			   t_mahdia = 11,
			   t_mannouba = 12,
			   t_medenine = 13,
			   t_monastir = 14,
			   t_nabeul = 15,
			   t_sfax = 16,
			   t_sidi_bouzid = 17,
			   t_siliana = 18,
			   t_sousse = 19,
			   t_tataouine = 20,
			   t_tozeur = 21,
			   t_tunis = 22,
			   t_zaghouan = 23,
			   MAX_GOUVERNORAT = t_zaghouan
			 } t_gouvernorat_types;

typedef enum {
			   t_nord = 0,
			   t_sahel = 1,
			   t_cap_bon = 2,
			   t_centre = 3,
			   t_sud = 4,
			   MAX_REGION = t_sud
			 } t_tunisia_region_types;

typedef struct {
				 unsigned_int continents[(unsigned_int)MAX_CONTINENT + 1];
				 unsigned_int pays[197];
				 t_age_bucket gouvernorats[(unsigned_int)MAX_GOUVERNORAT + 1];
                 t_age_bucket regions[(unsigned_int)MAX_REGION + 1];
			   } t_geographic_stat_table,*p_geographic_stat_table;


extern unsigned_int LILLY_CALL_CONVENTION collect_geographic_statistics_data(const p_geographic_stat_table stat_table,const struct t_lilly_db_handle *patient_db_handle,const unsigned_int max_age);


#ifdef __cplusplus
}
#endif

#endif