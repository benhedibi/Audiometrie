#include "demographic_stats.h"
#include <patients_engine.h>
#include <cmnfnc.h>

#include <lilly_os.h>
#include <lilly_mem.h>



static void LILLY_CALL_CONVENTION bubbleSort(const punsigned_int table,const unsigned_int element_count)
{
  unsigned_int i,j,tmp;


	for (i = 0; i < element_count - 1; i++)
	{
	  for (j = 0; j < element_count - i - 1; j++)
	  {
		if (table[j] < table[j + 1])
		{
		  tmp = table[j];
		  table[j] = table[j + 1];
		  table[j + 1] = tmp;
        }
	  }
	}

	return;
}

static void AvCALL_CONVENTION swap_callback(const opaque_ptr user_data,const p_age_bucket src,const p_age_bucket dest)
{
  t_age_bucket tmp;

	tmp = *src;
	*src = *dest;
	*dest = tmp;

	return;
}

static t_quicksort_cmp_value_result_types AvCALL_CONVENTION cmp_values_callback(const opaque_ptr user_data,const p_age_bucket src,const p_age_bucket dest)
{
	if (src->count <= dest->count)
	{
	  return t_quicksort_less_or_equal_result;
	}
	else if (src->count >= dest->count)
	{
	  return t_quicksort_great_or_equal_result;
	}
    else return t_quicksort_no_result;
}

static AvCALL_CONVENTION opaque_ptr malloc_callback(const opaque_ptr user_data,const unsigned_int mem_size)
{
	return lilly_malloc(mem_size);
}

static AvCALL_CONVENTION void free_callback(const opaque_ptr user_data,const opaque_ptr mem,const unsigned_int mem_size)
{

	lilly_free(mem,mem_size);

	return;
}

static boolean LILLY_CALL_CONVENTION make_top_10(const p_demographic_stat_table stat_table)
{
  t_non_recursive_quicksort_params quicksort_params;
  t_age_bucket ages[sizeof(stat_table->pyramide_demographique) / sizeof(stat_table->pyramide_demographique[0])];


	avcore_memcpy(&ages,&stat_table->pyramide_demographique,sizeof(stat_table->pyramide_demographique));

	quicksort_params.user_data = NULL;
	quicksort_params.array = &ages;
	quicksort_params.array_element_size = sizeof(t_age_bucket);
	quicksort_params.l = 0;
	quicksort_params.h = (sizeof(stat_table->pyramide_demographique) / sizeof(stat_table->pyramide_demographique[0])) - 1;
	quicksort_params.malloc_callback = malloc_callback;
	quicksort_params.free_callback = free_callback;
	quicksort_params.swap_callback = swap_callback;
	quicksort_params.cmp_values_callback = cmp_values_callback;

	if (!quicksort_ex(&quicksort_params)) return FALSE;

	avcore_memcpy(&stat_table->first_consult_top_10_ages,&ages,10 * sizeof(t_age_bucket));

    return TRUE;
}

static __inline t_age_category_type age_to_category(const unsigned_int age) // ugly code but will be optimised to death by any stupid compiler :p
{

	switch (age)
	{
		case 1 :
		case 2 :
		case 3 : return t_nourrisson;

		case 4 :
		case 5 :
		case 6 :
		case 7 :
		case 8 :
		case 9 :
	   case 10 : return t_enfant;

	   case 11 :
	   case 12 :
	   case 13 :
	   case 14 :
	   case 15 :
	   case 16 :
	   case 17 : return t_adolescent;;

	   case 18 :
	   case 19 :
	   case 20 :
	   case 21 :
	   case 22 :
	   case 23 :
	   case 24 : return t_jeune;

	   case 25 :
	   case 26 :
	   case 27 :
	   case 28 :
	   case 29 :
	   case 30 :
	   case 31 :
	   case 32 :
	   case 33 :
	   case 34 :
	   case 35 :
	   case 36 :
	   case 37 :
	   case 38 :
	   case 39 :
	   case 40 :
	   case 41 :
	   case 42 :
	   case 43 :
	   case 44 :
	   case 45 :
	   case 46 :
	   case 47 :
	   case 48 :
	   case 49 : return t_adulte;

	   case 50 :
	   case 51 :
	   case 52 :
	   case 53 :
	   case 54 :
	   case 55 :
	   case 56 :
	   case 57 :
	   case 58 :
	   case 59 : return t_cinquantenaire;

	   default : break;
	}

	return t_vieux;
}

static void LILLY_CALL_CONVENTION get_age_parity_level(const p_demographic_stat_table stat_table)
{
  float min_parite,max_parite,pourcentage_male,pourcentage_female,x;
  p_age_bucket bucket;
  int i;
  boolean max_parite_found,min_parite_found;


	min_parite = max_parite = pourcentage_male = pourcentage_female = 0;

	max_parite_found = min_parite_found = FALSE;

	for (i = 0; i < sizeof(stat_table->pyramide_demographique) / sizeof(stat_table->pyramide_demographique[0]); i++)
	{

	  bucket = (p_age_bucket)&stat_table->pyramide_demographique[i];

	  if (bucket->count < 2) continue;

	  if ((min_parite_found) && (max_parite_found)) break;

	  if ((!max_parite_found) && ((!bucket->male_count) || (!bucket->female_count)))
	  {
		max_parite_found = TRUE;

		stat_table->max_age_parity.age = bucket->age;

		if (!bucket->male_count)
		{
		  stat_table->max_age_parity.pourcentage_femmes = 100;
		}
		else stat_table->max_age_parity.pourcentage_hommes = 100;

		continue;
	  }

	  pourcentage_male = (float)(((float)bucket->male_count / (float)bucket->count) * 100);

	  pourcentage_female = (float)(((float)bucket->female_count / (float)bucket->count) * 100);

	  if (pourcentage_male > pourcentage_female)
	  {
		x = pourcentage_male - pourcentage_female;
	  }
	  else if (pourcentage_male < pourcentage_female)
	  {
		x = pourcentage_female - pourcentage_male;
	  }
	  else x = 0;

	  if (!min_parite_found)
	  {
		if (x == 0)
		{
		  min_parite_found = TRUE;
		  stat_table->min_age_parity.age = bucket->age;
		  stat_table->min_age_parity.pourcentage_hommes = 50;
		  stat_table->min_age_parity.pourcentage_femmes = 50;
		  continue;
		}

		if (!min_parite)
		{
		  min_parite = x;
		}
		else if (min_parite > x)
		{
		  min_parite = x;
		  stat_table->min_age_parity.age = bucket->age;
		  stat_table->min_age_parity.pourcentage_hommes = pourcentage_male;
		  stat_table->min_age_parity.pourcentage_femmes = pourcentage_female;
		}
	  }

	  if (!max_parite_found)
	  {
		if (!max_parite)
		{
		  max_parite = x;
		}
		else if (max_parite < x)
		{
		  max_parite = x;
		  stat_table->max_age_parity.age = bucket->age;
		  stat_table->max_age_parity.pourcentage_hommes = pourcentage_male;
		  stat_table->max_age_parity.pourcentage_femmes = pourcentage_female;
		}
	  }
	}

	if ((stat_table->max_age_parity.pourcentage_hommes > 0) || (stat_table->max_age_parity.pourcentage_femmes > 0))
	{
	  stat_table->max_age_parity.age_category = age_to_category(stat_table->max_age_parity.age);
	}

	if ((stat_table->min_age_parity.pourcentage_hommes > 0) || (stat_table->min_age_parity.pourcentage_femmes > 0))
	{
	  stat_table->min_age_parity.age_category = age_to_category(stat_table->min_age_parity.age);
	}

	return;

}
unsigned_int LILLY_CALL_CONVENTION collect_demographic_statistics_data(const p_demographic_stat_table stat_table,const struct t_lilly_db_handle *patient_db_handle,const unsigned_int age_limit)
{
  p_patient_record iterator;
  unsigned_int age;
  t_date_time today;
  p_demographic_stat_record record_ptr;
  punsigned_int count_ptr;
  t_age_category_type category;


	if ((!stat_table) || (!patient_db_handle)) return API_ERROR;

	avcore_memset(stat_table,0,sizeof(*stat_table));

	lilly_os_get_current_time_stamp(&today);

	iterator = (p_patient_record)lilly_db_get_first_record(patient_db_handle);

	if (!iterator)
	{
	  return lilly_db_get_last_error(patient_db_handle);
	}

	while (TRUE)
	{
	  if (!iterator->age_consultation) goto next;

	  age = (unsigned_int)(today.year - iterator->date_naissance.year);

	  if ((!age) || (age > age_limit)) goto next;

	  category = age_to_category(age);

	  stat_table->current_age_records[(unsigned_int)category].total_count++;

	  switch (iterator->sexe)
	  {
		  case MALE_GENDER : stat_table->total_males++;
							 stat_table->current_age_records[(unsigned_int)category].male_count++;
							 break;

		case FEMALE_GENDER : stat_table->total_females++;
							 stat_table->current_age_records[(unsigned_int)category].female_count++;
							 break;
	  }

	  age = iterator->age_consultation;

	  if (age)
	  {
		category = age_to_category((unsigned_int)iterator->age_consultation);

		stat_table->first_consult_age_records[(unsigned_int)category].total_count++;

		switch (iterator->sexe)
		{
			case MALE_GENDER : stat_table->first_consult_age_records[(unsigned_int)category].male_count++;
							   break;

		  case FEMALE_GENDER : stat_table->first_consult_age_records[(unsigned_int)category].female_count++;
							   break;
		}

		if ((age <= age_limit) && (age < sizeof(stat_table->pyramide_demographique) / sizeof(stat_table->pyramide_demographique[0])))
		{
		  p_age_bucket age_bucket = (p_age_bucket)&stat_table->pyramide_demographique[age];

		  age_bucket->count++;

		  age_bucket->age = age;

		  if (iterator->sexe == MALE_GENDER)
		  {
			age_bucket->male_count++;
		  }
		  else if (iterator->sexe == FEMALE_GENDER)
		  {
			age_bucket->female_count++;
          }
        }
      }

	  next :

	  iterator = (p_patient_record)lilly_db_get_next_record(patient_db_handle);

	  if (!iterator) break;
	}

	{
	  unsigned_int error_code = lilly_db_get_last_error(patient_db_handle);

	  if (error_code != ERROR_SUCCESS) return error_code;
	}

	if (stat_table->pyramide_demographique > sizeof(stat_table->first_consult_top_10_ages))
	{
	  if (!make_top_10(stat_table)) return MEM_ALLOC_ERROR;
	}

	get_age_parity_level(stat_table);

	return ERROR_SUCCESS;
}
