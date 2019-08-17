#ifndef DEMOGRAPHIC_H
#define DEMOGRAPHIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>
#include <lilly_db2.h>


typedef enum {
			   t_nourrisson = 0,
			   t_enfant = 1,
			   t_adolescent = 2,
			   t_jeune = 3,
			   t_adulte = 4,
			   t_cinquantenaire = 5,
			   t_vieux = 6
			 } t_age_category_type;

typedef enum {
			   t_male,
			   t_female,
			 } t_sex_type;


typedef struct {
				 unsigned_int total_count;
				 unsigned_int male_count;
				 unsigned_int female_count;
				// t_age_category_type category;
			   } t_demographic_stat_record,*p_demographic_stat_record;

typedef struct {
				 unsigned_int count;
				 unsigned_int age;
				 unsigned_int male_count;
				 unsigned_int female_count;
			   } t_age_bucket,*p_age_bucket;

typedef struct {
				 unsigned_int age;
				 float pourcentage_hommes;
                 float pourcentage_femmes;
				 t_age_category_type age_category;
			   } t_age_parity,*p_age_parity;

typedef struct {
				 unsigned_int total_males;
				 unsigned_int total_females;
				 t_demographic_stat_record current_age_records[7];
				 t_demographic_stat_record first_consult_age_records[7];
				 t_age_bucket pyramide_demographique[112];
				 t_age_bucket first_consult_top_10_ages[10];
				 t_age_parity max_age_parity;
				 t_age_parity min_age_parity;
			   } t_demographic_stat_table,*p_demographic_stat_table;


extern unsigned_int LILLY_CALL_CONVENTION collect_demographic_statistics_data(const p_demographic_stat_table stat_table,const struct t_lilly_db_handle *patient_db_handle,const unsigned_int max_age);

#ifdef __cplusplus
}
#endif

#endif