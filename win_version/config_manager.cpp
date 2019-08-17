//---------------------------------------------------------------------------

#pragma hdrstop

#include "config_manager.hpp"

#include <cmnfnc.h>
#include <lilly_io.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)


bool __fastcall TConfigManager::load_app_startup_buffer(const UnicodeString config_object_path)
{
  unsigned_int fhandle;


	 error_code = ERROR_SUCCESS;

	 fhandle = lilly_io_open_file((puchar)config_object_path.c_str(),lilly_io_fmOpen,lilly_io_faRead);

	 if ((signed_int)fhandle <= 0)
	 {
	   error_code = IO_ERROR;
	   return false;
	 }

  try
	 {
		buffer_size = lilly_io_get_file_size_ex(fhandle);

		if ((signed_int)buffer_size <= 32)
		{
		  error_code = IO_ERROR;
		  return false;
		}

		buffer = (puchar)malloc(buffer_size);

		if (!buffer)
		{
		  error_code = MEM_ALLOC_ERROR;
		  return false;
		}

		if (!lilly_io_file_read(fhandle,buffer,buffer_size))
		{
		  error_code = IO_ERROR;
		  return false;
		}

		if (*(puint16)buffer != 0xFEFF) // unicode only
		{
		  error_code = DATA_SIGNATURE_ERROR;
		  return false;
		}

		return true;
	 }

 __finally
	 {
	   if (fhandle)
	   {
		 lilly_io_close_file(fhandle);
	   }
	 }

}

bool __fastcall TConfigManager::load_app_startup_config()
{
  puchar p = buffer + 2;
  puchar section_name,param_name,param_value;
  unsigned_int size_left,section_name_len,param_name_len,param_value_len;
  struct t_ini_buffer *last_iterator = NULL;


	 size_left = buffer_size - 2;

	 while (true)
	 {
		if (*p == '[')
		{
		  section_name_len = 0;

		  p += 2;

		  size_left -= 2;

		  if ((signed_int)size_left <= 0) return false;

		  section_name = p;

		  while (*p != ']')
		  {
			p += 2;
			size_left -= 2;
			if (((signed_int)size_left <= 0) || ((size_left >= 4) && (*(puint32)p == 0x000A000D))) return false;
			section_name_len += 2;
		  }
		}

		if (!section_name_len) return false;

		p += 2;

		size_left -= 2;

		if (((signed_int)size_left <= 4) || (*(puint32)p != 0x000A000D)) return false;

		while (*(puint32)p == 0x000A000D)
		{
		  p += 4;
		  size_left -= 4;
		  if ((signed_int)size_left <= 0) return false;
          if (size_left < 4) break;
		}

		param_name = p;

		param_name_len = 0;

		while (*p != '=')
		{
		  p += 2;
		  size_left -= 2;
		  if (((signed_int)size_left <= 0) || ((size_left >= 4) && (*(puint32)p == 0x000A000D))) return false;
		  param_name_len += 2;
		}

		if (!param_name_len) return false;

		p += 2;

		size_left -= 2;

		if ((signed_int)size_left <= 0) return false;

		param_value = p;

		param_value_len = 0;

		while (*(puint32)p != 0x000A000D)
		{
		  p += 2;
		  size_left -= 2;
		  if ((signed_int)size_left <= 0) return false;
		  if (size_left < 4) break;
		  param_value_len += 2;
		}

		while (((signed_int)size_left >= 4) && (*(puint32)p == 0x000A000D))
		{
		  p += 4;
		  size_left -= 4;
		  if ((signed_int)size_left <= 0) return false;
		}

		{
		  struct t_ini_buffer *iterator = (struct t_ini_buffer *)malloc(sizeof(*iterator));

		   if (!iterator)
		  {
			error_code = MEM_ALLOC_ERROR;
			return false;
		  }

		  if (!last_iterator)
		  {
			last_iterator = iterator;
		  }
		  else
		  {
			last_iterator->next = iterator;
			last_iterator = iterator;
		  }

		  if (!ini_buffer)
		  {
			ini_buffer = iterator;
		  }

		  iterator->next = NULL;

		  iterator->section_name = section_name;
		  iterator->section_name_len = section_name_len;
		  iterator->param_name = param_name;
		  iterator->param_name_len = param_name_len;
		  iterator->param_data = param_value;
		  iterator->param_data_len = param_value_len;

		  startup_config_section_count++;

		}

		if (((signed_int)size_left <= 0) || (*p == ';')) break;

	 }

	 return true;

}

__fastcall TConfigManager::TConfigManager(const UnicodeString config_object_path,const TConfigManagerType manager_type)
{
  unsigned_int fhandle;


	 buffer = NULL;

	 buffer_size = 0;

	 startup_config_section_count = 0;

	 ini_buffer = NULL;

	 error_code = ERROR_SUCCESS;

	 Manager_Type = TUndefined_config_manager_type;

	 if ((config_object_path == "") || (manager_type == Manager_Type) || (manager_type > MAX_CONFIG_MANAGER_TYPE))
	 {
	   error_code = API_ERROR;
	   return;
     }

	 Manager_Type = manager_type;

	 if (!lilly_io_file_exists((puchar)config_object_path.c_str()))
	 {
	   error_code = IO_ERROR;
	   return;
	 }

	 switch (Manager_Type)
	 {
	   case TAppStartup_config : if (!load_app_startup_buffer(config_object_path)) break;

								 if (!load_app_startup_config())
								 {
								   if (error_code == ERROR_SUCCESS)
								   {
									 error_code = DATA_SIGNATURE_ERROR;
									 break;
								   }
								 }

								 break;

	   case TAppOptions_config : error_code = ERROR_NOT_IMPLEMENTED;
								 break;
	 }

	 return;

}

__fastcall TConfigManager::~TConfigManager()
{

	 if (buffer)
	 {
	   free(buffer);
	   buffer = NULL;
	   buffer_size = 0;
	 }

	 struct t_ini_buffer *iterator,*next_iterator;

	 iterator = ini_buffer;

	 while (true)
	 {
	   next_iterator = iterator->next;
	   free(iterator);
	   iterator = next_iterator;
	   if (!iterator) break;
	 }

	 ini_buffer = NULL;

	 startup_config_section_count = 0;

     return;
}

UnicodeString __fastcall TConfigManager::ReadParamByName(const UnicodeString ParamName)
{
  UnicodeString result;


	result = "";

	error_code = ERROR_SUCCESS;

	if (ParamName == "")
	{
	  error_code = API_ERROR;
	  return result;
	}

	switch (Manager_Type)
	{
	  case TUndefined_config_manager_type : error_code = API_ERROR;
									   break;

				  case TAppStartup_config : {
											  struct t_ini_buffer *iterator;
											  puchar p = (puchar)ParamName.c_str();

											  iterator = ini_buffer;

											  while (true)
											  {
												if ((iterator->section_name_len == ParamName.Length() * 2) && (avcore_cmpWString(iterator->section_name,p,iterator->section_name_len)))
												{
												  for (int i = 0; i < iterator->param_data_len / 2; i++)
												  {
													result = result + (WCHAR)iterator->param_data[i * 2];
												  }

												  break;
												}

												iterator = iterator->next;

												if (!iterator) break;
											  }
											}

											break;

				  case TAppOptions_config : error_code = ERROR_NOT_IMPLEMENTED;
											break;

								  default : error_code = API_ERROR;
											break;
	}

	return result;
}

UnicodeString __fastcall TConfigManager::ReadParamByID(const unsigned_int id)
{
  UnicodeString result;


	result = "";

	error_code = ERROR_SUCCESS;

	if ((signed_int)id < 0)
	{
	  error_code = API_ERROR;
	  return result;
	}

	switch (Manager_Type)
	{
	  TUndefined_config_manager_type : error_code = API_ERROR;
									   break;

				  TAppStartup_config : {
										 struct t_ini_buffer *iterator;
										 unsigned_int index = 0;

										 iterator = ini_buffer;

										 while (true)
										 {
										   if (index++ == id)
										   {
											 result = (PWCHAR)iterator->param_name;
											 break;
										   }

										   iterator = iterator->next;

										   if (!iterator) break;
										 }
									   }

									   break;

				  TAppOptions_config : error_code = ERROR_NOT_IMPLEMENTED;
									   break;

							 default : error_code = API_ERROR;
									   break;
	}

	return result;
}


