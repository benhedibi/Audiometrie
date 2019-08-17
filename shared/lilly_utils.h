#ifndef LILLY_UTILS_H
#define LILLY_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>

#pragma pack(push,1)

typedef struct {
				 unsigned_int len;
				 uchar data[64];
			   } t_lilly_serialized_string,*p_lilly_serialized_string;

#pragma pack(pop)


#define DATE_IS_LESS      0
#define DATE_IS_EQUAL     1
#define DATE_IS_GREAT     2
#define DATE_IS_UNDEFINED 3


extern uint64 lilly_generate_fnv1_hash(const puchar data,const unsigned_int data_size);
extern uint32 lilly_crc32_buffer(const puchar buffer,const unsigned_int buffer_size,const uint32 previous_crc);
extern uint32 lilly_crc32_serialized_result(const p_lilly_serialized_string serialized_result,const uint32 previous_crc);
extern boolean lilly_serialize_string_field(const puchar string_field,unsigned_int string_field_size,const p_lilly_serialized_string serialized_result);
extern boolean lilly_serialize_phone_field(const puchar phone_field,unsigned_int phone_field_size,const p_lilly_serialized_string serialized_result);
extern boolean lilly_is_valid_email_field(const puchar email_field,const unsigned_int email_field_size);
extern boolean lilly_import_str_to_date(const puchar str,const unsigned_int len,const p_date_time date);
extern boolean lilly_import_str_to_date_ex(const puchar str,const unsigned_int len,const p_date_time date);
extern unsigned_int lilly_compare_dates(const p_date_time src_date,const p_date_time dest_date);

#ifdef __cplusplus
}
#endif

#endif