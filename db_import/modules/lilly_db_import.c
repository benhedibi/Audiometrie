#include <lilly_db_import.h>
#include <cmnfnc.h>


boolean lilly_import_read_db_field(const p_db_field_buffer field_buffer,unsigned_int field_index,puchar data,unsigned_int data_size)
{
  const puchar null_field = (puchar)L"** NULL **";
  const null_field_len = 20;

  puint16 pw;
  boolean guillemet_found = FALSE;


	 if ((signed_int)field_index < 0) return FALSE;

	 while (field_index)
	 {
	   field_index -= (*data == ',');
	   data += 2;
	   data_size -= 2;
	   if ((signed_int)data_size <=0) return FALSE;
	 }

	 if (*data == '"')
	 {
	   guillemet_found = TRUE;
	   data += 2;
	   data_size -= 2;
	 }

	 if ((*data == '*') && (data_size >= null_field_len)) // is it an empty field ?
	 {
	   if (avcore_memcmp(data,null_field,null_field_len))
	   {
		 field_buffer->field_len = 0;
		 field_buffer->data[0] = 0;
		 return TRUE;
       }
	 }

	 if ((signed_int)data_size <= 0) return FALSE;

	 while (*data == ' ') // clean space at the beginning
	 {
	   data += 2;
	   data_size -= 2;
	   if ((signed_int)data_size <= 0) return FALSE;
	 }

	 field_buffer->field_len = 0;

	 pw = (puint16)&field_buffer->data[0];

	 while (TRUE)
	 {
	   if (((signed_int)data_size <= 0) || (*data == 0x0D) || (*data == ',') || (field_buffer->field_len >= sizeof(field_buffer->data) - 2)) break;

	   *pw = *(puint16)data;

	   data_size -= 2;

	   data += 2;

	   pw++;

	   field_buffer->field_len += 2;
	 }

	 if (!field_buffer->field_len) return FALSE; // something went wrong

	 pw -= (int)guillemet_found;

	 *pw = 0;

	 field_buffer->field_len -= ((int)guillemet_found * 2);

	 return TRUE;

}

puchar lilly_import_get_first_field(const puchar buffer,const punsigned_int size_left)
{
  puchar p = buffer;


	 if (((signed_int)*size_left <= 2) || (*(puint16)p != 0xFEFF)) return NULL;

	 while (TRUE)
	 {
	   if (*p == 0x0D)
	   {
		 *size_left -= 4;

		 if ((signed_int)*size_left <= 0) break;

		 return (p + 4);
	   }

	   *size_left -= 2;

	   if ((signed_int)*size_left <= 0) break;

	   p += 2;
	 }

	 return NULL;

}

puchar lilly_import_get_next_field(const puchar buffer,const punsigned_int size_left)
{
  puchar p = buffer;


	 if ((signed_int)*size_left <= 0) return NULL;

	 while (TRUE)
	 {
	   if (*p == 0x0D)
	   {
		 *size_left -= 4;

		 if ((signed_int)*size_left <= 0) break;

		 return (p + 4);
	   }

	   *size_left -= 2;

	   if ((signed_int)*size_left <= 0) break;

	   p += 2;
	 }

	 return NULL;
}
