#include "geographic_stats.h"

#include <patients_engine.h>
#include <cmnfnc.h>

#include <lilly_os.h>
#include <lilly_mem.h>

static __inline t_tunisia_region_types gouvernoart_to_region(const t_gouvernorat_types gouvernorat)
{

	switch (gouvernorat)
	{
		 case t_jendouba :
			 case t_beja :
		  case t_bizerte :
		   case t_ariana :
			case t_tunis :
		case t_ben_arous :
		 case t_zaghouan :
			  case t_kef :
		 case t_mannouba :
		  case t_siliana : return t_nord;

		   case t_nabeul : return t_cap_bon;

		   case t_mahdia :
		 case t_monastir :
		   case t_sousse : return t_sahel;

			 case t_sfax :
		 case t_kairouan :
		case t_kasserine :
	  case t_sidi_bouzid :
			case t_gafsa : return t_centre;

			case t_gabes :
		 case t_medenine :
		case t_tataouine :
		   case t_kebili : return t_sud;
	}

    return t_nord;
}

static __inline t_continent_types pays_to_continent(const uint8 pays)
{

	switch (pays)
	{
	   case 0 : return t_asie;
	   case 1 : return t_afrique;
	   case 2 : return t_europe;
	   case 3 : return t_afrique;
	   case 4 :
	   case 5 : return t_europe;
	   case 6 : return t_afrique;
	   case 7 : return t_amerique_nord;
	   case 8 : return t_asie;
	   case 9 : return t_amerique_sud;
	  case 10 : return t_europe;
	  case 11 : return t_oceanie;
	  case 12 : return t_europe;
	  case 13 : return t_asie;
	  case 14 : return t_amerique_nord;
	  case 15 :
	  case 16 : return t_asie;
	  case 17 : return t_amerique_nord;
	  case 18 : return t_europe;
	  case 19 : return t_amerique_nord;
	  case 20 : return t_afrique;
	  case 21 : return t_asie;
	  case 22 : return t_europe;
	  case 23 : return t_asie;
	  case 24 : return t_amerique_sud;
	  case 25 : return t_europe;
	  case 26 : return t_afrique;
	  case 27 : return t_amerique_sud;
	  case 28 : return t_asie;
	  case 29 : return t_europe;
	  case 30 :
	  case 31 : return t_afrique;
	  case 32 : return t_asie;
	  case 33 : return t_afrique;
	  case 34 : return t_amerique_nord;
	  case 35 :
	  case 36 : return t_afrique;
	  case 37 : return t_amerique_sud;
	  case 38 : return t_asie;
	  case 39 : return t_europe;
	  case 40 : return t_amerique_sud;
	  case 41 :
	  case 42 :
	  case 43 : return t_afrique;
	  case 44 : return t_oceanie;
	  case 45 :
	  case 46 : return t_asie;
	  case 47 : return t_amerique_sud;
	  case 48 : return t_afrique;
	  case 49 : return t_europe;
	  case 50 : return t_amerique_nord;
	  case 51 : return t_europe;
	  case 52 : return t_afrique;
	  case 53 : return t_amerique_nord;
	  case 54 : return t_amerique_sud;
	  case 55 : return t_afrique;
	  case 56 : return t_asie;
	  case 57 : return t_amerique_sud;
	  case 58 : return t_afrique;
	  case 59 :
	  case 60 : return t_europe;
	  case 61 : return t_amerique_nord;
	  case 62 : return t_afrique;
	  case 63 : return t_asie;
	  case 64 :
	  case 65 : return t_europe;
	  case 66 :
	  case 67 : return t_afrique;
	  case 68 : return t_asie;
	  case 69 : return t_afrique;
	  case 70 : return t_europe;
	  case 71 :
	  case 72 : return t_amerique_nord;
	  case 73 :
	  case 74 :
	  case 75 : return t_afrique;
	  case 76 : return t_amerique_sud;
	  case 77 : return t_amerique_nord;
	  case 78 : return t_amerique_sud;
	  case 79 : return t_europe;
	  case 80 :
	  case 81 :
	  case 82 :
	  case 83 : return t_asie;
	  case 84 :
	  case 85 : return t_europe;
	  case 86 : return t_asie;
	  case 87 : return t_europe;
	  case 88 : return t_amerique_nord;
	  case 89 :
	  case 90 :
	  case 91 : return t_asie;
	  case 92 : return t_afrique;
	  case 93 : return t_asie;
	  case 94 : return t_oceanie;
	  case 95 :
	  case 96 : return t_asie;
	  case 97 : return t_afrique;
	  case 98 : return t_europe;
	  case 99 : return t_asie;
	  case 100 :
	  case 101 : return t_afrique;
	  case 102 :
	  case 103 :
	  case 104 :
	  case 105 : return t_europe;
	  case 106 : return t_afrique;
	  case 107 : return t_asie;
	  case 108 : return t_afrique;
	  case 109 : return t_asie;
	  case 110 : return t_afrique;
	  case 111 : return t_europe;
	  case 112 : return t_afrique;
	  case 113 : return t_oceanie;
	  case 114 :
	  case 115 : return t_afrique;
	  case 116 :
	  case 117 : return t_amerique_nord;
	  case 118 :
	  case 119 : return t_europe;
	  case 120 : return t_asie;
	  case 121 : return t_europe;
	  case 122 :
	  case 123 : return t_afrique;
	  case 124 : return t_oceanie;
	  case 125 : return t_asie;
	  case 126 : return t_amerique_sud;
	  case 127 :
	  case 128 : return t_afrique;
	  case 129 : return t_oceanie;
	  case 130 : return t_europe;
	  case 131 : return t_oceanie;
	  case 132 : return t_asie;
	  case 133 : return t_afrique;
	  case 134 :
	  case 135 : return t_asie;
	  case 136 : return t_amerique_nord;
	  case 137 : return t_asie;
	  case 138 : return t_amerique_nord;
	  case 139 : return t_oceanie;
	  case 140 : return t_amerique_sud;
	  case 141 : return t_europe;
	  case 142 : return t_amerique_sud;
	  case 143 : return t_asie;
	  case 144 :
	  case 145 : return t_europe;
	  case 146 : return t_asie;
	  case 147 :
	  case 148 :
	  case 149 : return t_europe;
	  case 150 : return t_afrique;
	  case 151 : return t_amerique_nord;
	  case 152 : return t_europe;
	  case 153 :
	  case 154 : return t_amerique_nord;
	  case 155 : return t_oceanie;
	  case 156 : return t_amerique_sud;
	  case 157 : return t_oceanie;
	  case 158 :
	  case 159 : return t_afrique;
	  case 160 : return t_europe;
	  case 161 :
	  case 162 : return t_afrique;
	  case 163 : return t_asie;
	  case 164 :
	  case 165 : return t_europe;
	  case 166 :
	  case 167 :
	  case 168 :
	  case 169 : return t_afrique;
	  case 170 :
	  case 171 : return t_europe;
	  case 172 :
	  case 173 : return t_afrique;
	  case 174 :
	  case 175 : return t_asie;
	  case 176 :
	  case 177 : return t_afrique;
	  case 178 : return t_europe;
	  case 179 :
	  case 180 : return t_asie;
	  case 181 : return t_afrique;
	  case 182 : return t_oceanie;
	  case 183 : return t_amerique_sud;
	  case 184 : return t_afrique;
	  case 185 :
	  case 186 : return t_asie;
	  case 187 : return t_oceanie;
	  case 188 : return t_europe;
	  case 189 : return t_amerique_sud;
	  case 190 : return t_oceanie;
	  case 191 : return t_europe;
	  case 192 : return t_amerique_sud;
	  case 193 :
	  case 194 : return t_asie;
	  case 195 :
	  case 196 : return t_afrique;
	}

    return t_afrique;
}

unsigned_int LILLY_CALL_CONVENTION collect_geographic_statistics_data(const p_geographic_stat_table stat_table,const struct t_lilly_db_handle *patient_db_handle,const unsigned_int max_age)
{
  p_patient_record iterator;
  t_tunisia_region_types region;


    if ((!stat_table) || (!patient_db_handle)) return API_ERROR;

	avcore_memset(stat_table,0,sizeof(*stat_table));

	iterator = (p_patient_record)lilly_db_get_first_record(patient_db_handle);

	if (!iterator)
	{
	  return lilly_db_get_last_error(patient_db_handle);
	}

	while (TRUE)
	{
	  if (iterator->pays > 196) goto next;

	  stat_table->pays[iterator->pays]++;

	  stat_table->continents[pays_to_continent(iterator->pays)]++;

	  if ((iterator->age_consultation <= max_age) && (iterator->pays == 184) && ((t_gouvernorat_types)iterator->gouvernorat <= MAX_GOUVERNORAT))
	  {
		stat_table->gouvernorats[(unsigned_int)iterator->gouvernorat].count++;
		stat_table->gouvernorats[(unsigned_int)iterator->gouvernorat].age = iterator->age_consultation;

		region = gouvernoart_to_region((t_gouvernorat_types)iterator->gouvernorat);

		stat_table->regions[(unsigned_int)region].count++;
		stat_table->regions[(unsigned_int)region].age = iterator->age_consultation;

		if (iterator->sexe == MALE_GENDER)
		{
		  stat_table->gouvernorats[(unsigned_int)iterator->gouvernorat].male_count++;
		  stat_table->regions[(unsigned_int)region].male_count++;
		}
		else
		{
		  stat_table->gouvernorats[(unsigned_int)iterator->gouvernorat].female_count++;
		  stat_table->regions[(unsigned_int)region].female_count++;
		}
      }

	  next :

	  iterator = (p_patient_record)lilly_db_get_next_record(patient_db_handle);

	  if (!iterator) break;
	}

    return lilly_db_get_last_error(patient_db_handle);
}
