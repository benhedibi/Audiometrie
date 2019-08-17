#include <lilly_utils.h>
#include <cmnfnc.h>
#include <crc32.h>

uint64 lilly_db_generate_fnv1_hash(const puchar data,const unsigned_int data_size)
{
  #define HASH_PRIME ((uint64)0x100000001b3UI64)
  #define HASH_BASIS ((uint64)0xcbf29ce484222325UI64)


  unsigned_int i;
  uint64 hash;


	hash = HASH_BASIS;

	for (i = 0; i < data_size; i++)
	{
	  hash ^= data[i];
	  hash *= HASH_PRIME;
	}

	#undef HASH_PRIME
	#undef HASH_BASIS

	return hash;

}

uint32 lilly_crc32_buffer(const puchar buffer,const unsigned_int buffer_size,const uint32 previous_crc)
{
	 if ((!buffer) || ((signed_int)buffer_size <= 0)) return 0;
	 else return crc32_data(buffer,buffer_size,previous_crc);
}

uint32 lilly_crc32_serialized_result(const p_lilly_serialized_string serialized_result,const uint32 previous_crc)
{
	 if ((!serialized_result) || ((signed_int)serialized_result->len <= 0) || (serialized_result->len > sizeof(serialized_result->data))) return 0;
	 else return crc32_data((puchar)&serialized_result->data,serialized_result->len,previous_crc);
}

boolean lilly_serialize_string_field(const puchar string_field,unsigned_int string_field_size,const p_lilly_serialized_string serialized_result)
{
  #ifdef COMPILATION_64BIT
  #define LOW_CASE_MASK 0x0020002000200020
  #else
  #define LOW_CASE_MASK 0x00200020
  #endif

  punsigned_int dw_source = (punsigned_int)string_field;
  punsigned_int dw_target;


	 if ((!dw_source) || ((signed_int)string_field_size <= 0) || (!serialized_result) || (string_field_size > sizeof(serialized_result->data))) return FALSE;

	 serialized_result->len = string_field_size;

	 dw_target = (punsigned_int)&serialized_result->data[0];

	 while (string_field_size >= sizeof(*dw_target) * 8)
	 {
	   dw_target[0] = dw_source[0] | LOW_CASE_MASK;
	   dw_target[1] = dw_source[1] | LOW_CASE_MASK;
	   dw_target[2] = dw_source[2] | LOW_CASE_MASK;
	   dw_target[3] = dw_source[3] | LOW_CASE_MASK;
	   dw_target[4] = dw_source[4] | LOW_CASE_MASK;
	   dw_target[5] = dw_source[5] | LOW_CASE_MASK;
	   dw_target[6] = dw_source[6] | LOW_CASE_MASK;
	   dw_target[7] = dw_source[7] | LOW_CASE_MASK;

	   string_field_size -= sizeof(*dw_target) * 8;
	   dw_target += 8;
	   dw_source += 8;
	 }

	 while (string_field_size >= sizeof(*dw_target) * 4)
	 {
	   dw_target[0] = dw_source[0] | LOW_CASE_MASK;
	   dw_target[1] = dw_source[1] | LOW_CASE_MASK;
	   dw_target[2] = dw_source[2] | LOW_CASE_MASK;
	   dw_target[3] = dw_source[3] | LOW_CASE_MASK;

	   string_field_size -= sizeof(*dw_target) * 4;
	   dw_target += 4;
	   dw_source += 4;
	 }

	 while (string_field_size >= sizeof(*dw_target))
	 {
	   *dw_target = *dw_source | LOW_CASE_MASK;
	   string_field_size -= sizeof(*dw_target);
	   dw_target++;
       dw_source++;
	 }

	 {
	   puint16 pw_target = (puint16)dw_target;
	   puint16 pw_source = (puint16)dw_source;

	   while ((signed_int)string_field_size > 0)
	   {
		 *pw_target++ = *pw_source++ | 0x0020;
		 string_field_size -= 2;
	   }
	 }

     return TRUE;

#undef LOW_CASE_MASK

}

boolean lilly_serialize_phone_field(const puchar phone_field,unsigned_int phone_field_size,const p_lilly_serialized_string serialized_result)
{
  puchar src,dest;


	 if ((!phone_field) || ((signed_int)phone_field_size <= 0) || (!serialized_result) || (phone_field_size > sizeof(serialized_result->data))) return FALSE;

	 serialized_result->len = 0;

	 src = phone_field;

	 dest = (puchar)&serialized_result->data[0];

	 while (TRUE)
	 {
	   switch (*src)
	   {
         case ' ' :
		 case '(' :
		 case '-' :
		 case ')' : break;

		  default : *dest++ = *src;
					 serialized_result->len += 2;
					 *dest++ = 0;
                     break;
	   }

	   phone_field_size -= 2;

	   if ((signed_int)phone_field_size <= 0) break;

	   src += 2;
	 }

     return (serialized_result->len > 0);

}

boolean lilly_is_valid_email_field(const puchar email_field,const unsigned_int email_field_size)
{
  unsigned_int i = email_field_size - 6;
  puchar p = email_field + i;
  boolean domaine_found = FALSE;


	 if ((!email_field) || ((signed_int)email_field_size <= 12)) return FALSE;

	 if (*p == '.')
	 {
	   domaine_found = TRUE;
	   p -= 2;
	   i -= 2;
	 }
	 else if (*(p - 2) == '.')
	 {
	   domaine_found = TRUE;
	   p -= 4;
	   i -= 4;
	 }

	 if (!domaine_found) return FALSE;

	 while (TRUE)
	 {
	   if (*p == '@') return TRUE;

	   i -= 2;

	   if ((signed_int)i <= 0) return FALSE;

	   p -= 2;
	 }

}

boolean lilly_import_str_to_date(const puchar str,const unsigned_int len,const p_date_time date)
{
  unsigned_int i,sep_index,rem_len;
  unsigned_int sep_indexes[2];
  uchar days[6];
  uchar months[6];
  uchar years[10];


	 if ((!str) || (*str == 0) || ((signed_int)len <= 0) || (!date)) return FALSE;

	 sep_index = 0;

	 for (i = 0; i < len; i += 2)
	 {
	   switch (str[i])
	   {
		 case '.' :
		 case '-' :
		 case '/' : if (sep_index >= 2) return FALSE;
					sep_indexes[sep_index++] = i;
					break;

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

		  default : return FALSE;
	   }
	 }

	 switch (sep_index)
	 {
	   case 0 : if (len < 4) return FALSE;

				days[0] = '1';

				months[0] = '1';

				if (len < 8)
				{
				  *(puint32)&years = *(puint32)str;
				}
				else *(puint64)&years = *(puint64)str;

				rem_len = len;

				break;

	   case 1 : rem_len = len - (sep_indexes[0] + 2);

				if (rem_len < 4) return FALSE;

				switch (sep_indexes[0])
				{
				  case 2 : *(puint16)&months = *(puint16)str;
						   break;

				  case 4 : *(puint32)&months = *(puint32)str;
						   break;

				  default : return FALSE;
				}

				*(puint16)&months[sep_indexes[0]] = 0;

				sep_indexes[0] += 2;

				days[0] = '1';

				if (rem_len < 8)
				{
				  *(puint32)&years = *(puint32)&str[sep_indexes[0]];
				}
				else *(puint64)&years = *(puint64)&str[sep_indexes[0]];

				break;

	   case 2 : rem_len = len - (sep_indexes[1] + 2);

				if (rem_len < 4) return FALSE;

				switch (sep_indexes[0])
				{
				  case 2 : *(puint16)&days = *(puint16)str;
						   break;

				  case 4 : *(puint32)&days = *(puint32)str;
						   break;

				  default : return FALSE;
				}

				*(puint16)&days[sep_indexes[0]] = 0;

				sep_indexes[0] += 2;

				switch (sep_indexes[1] - sep_indexes[0])
				{
				  case 2 : *(puint16)&months = *(puint16)&str[sep_indexes[0]];
						   *(puint16)&months[2] = 0;
						   break;

				  case 4 : *(puint32)&months = *(puint32)&str[sep_indexes[0]];
						   *(puint16)&months[4] = 0;
						   break;

				  default : return FALSE;
				}

				sep_indexes[1] += 2;

				switch (rem_len)
				{
				  case 4 : *(puint32)&years = *(puint32)&str[sep_indexes[1]];
						   break;

				  case 8 : *(puint64)&years = *(puint64)&str[sep_indexes[1]];
						   break;

				 default : return FALSE;
				}

				break;
	 }

	 *(puint16)&years[rem_len] = 0;

	 *(puint64)date = 0;

	 date->day = avcore_watoi((puchar)&days);
	 date->month = avcore_watoi((puchar)&months);
	 date->year = avcore_watoi((puchar)&years);

	/* while (TRUE)
	 {
	   switch (*p)
	   {
		 case '.' :
		 case '-' :
		 case '/' : if (sep_index++ > 2) return FALSE;

					p += 2;

					goto bottom_loop;

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

		  default : return FALSE;
	   }

	   switch (sep_index)
	   {
		 case 0 : if (days_len > 4) return FALSE;
				  days[days_len] = *p;
				  days[days_len + 1] = 0;
				  p += 2;
				  days_len += 2;
				  break;

		 case 1 : if (months_len > 4) return FALSE;
				  months[months_len] = *p;
				  months[months_len + 1] = 0;
				  p += 2;
				  months_len += 2;
				  break;

		 case 2 : if (years_len > 8) return FALSE;
				  years[years_len] = *p;
				  years[years_len + 1] = 0;
				  p += 2;
				  years_len += 2;
                  break;
	   }

	   bottom_loop :

	   i -= 2;

	   if ((signed_int)i <= 0) break;
	 }   */


	 if (date->year < 100)
	 {
	   date->year += 1900;
	 }

	 return ((date->day > 0) && (date->day <= 31) && (date->month > 0) && (date->month <= 12) && (date->year >= 1900) && (date->year < 3000));

}

boolean lilly_import_str_to_date_ex(const puchar str,const unsigned_int len,const p_date_time date)
{
  unsigned_int sep_index,days_len,months_len,years_len,i;
  puchar p;
  uchar days[6];
  uchar months[6];
  uchar years[10];


	 if ((!str) || (*str == 0) || ((signed_int)len <= 0) || (!date)) return FALSE;

	 sep_index = 0;

	 days_len = 0;
	 months_len = 0;
	 years_len = 0;

	 i = len;

	 p = str;

	 while (TRUE)
	 {
	   switch (*p)
	   {

		 case '/' : if (sep_index++ > 2) return FALSE;

					p += 2;

					goto bottom_loop;

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

		  default : return FALSE;
	   }

	   switch (sep_index)
	   {
		 case 0 : if (days_len > 4) return FALSE;

				  days[days_len] = *p;
				  days[days_len + 1] = 0;
				  p += 2;
				  days_len += 2;

				  break;

		 case 1 : if (months_len > 4) return FALSE;

				  months[months_len] = *p;
				  months[months_len + 1] = 0;
				  p += 2;
				  months_len += 2;

				  break;

		 case 2 : if (years_len > 8) return FALSE;

				  years[years_len] = *p;
				  years[years_len + 1] = 0;
				  p += 2;
				  years_len += 2;

				  break;
	   }

	   bottom_loop :

	   i -= 2;

	   if ((signed_int)i <= 0) break;
	 }

     *(puint64)date = 0;

	 days[days_len] = 0;
	 months[months_len] = 0;
	 years[years_len] = 0;

	 date->day = avcore_watoi((puchar)&days);
	 date->month = avcore_watoi((puchar)&months);
	 date->year = avcore_watoi((puchar)&years);

	 return ((date->day > 0) && (date->day <= 31) && (date->month > 0) && (date->month <= 12) && (date->year >= 1900) && (date->year < 2050));

}

unsigned_int lilly_compare_dates(const p_date_time src_date,const p_date_time dest_date)
{
  uint32 date1,date2;


	if ((!src_date) || (!dest_date)) return DATE_IS_UNDEFINED;


	date1 = *(puint32)&src_date->day;
	date2 = *(puint32)&dest_date->day;

	if (date1 < date2) return DATE_IS_LESS;
	else if (date1 == date2) return DATE_IS_EQUAL;
	else if (date1 > date2) return DATE_IS_GREAT;

}
