//---------------------------------------------------------------------------

#ifndef config_managerH
#define config_managerH
//---------------------------------------------------------------------------
#endif

#include <System.Classes.hpp>
#include <globaldef.h>

typedef enum {
			   TUndefined_config_manager_type,
			   TAppStartup_config,
			   TAppOptions_config,
			   MAX_CONFIG_MANAGER_TYPE = TAppOptions_config
			 } TConfigManagerType;


class TConfigManager
{
  private :


	 struct t_ini_buffer
			{
			  struct t_ini_buffer *next;
			  puchar section_name;
			  unsigned_int section_name_len;
			  puchar param_name;
			  unsigned_int param_name_len;
			  puchar param_data;
			  unsigned_int param_data_len;
			};

	 puchar buffer;
	 unsigned_int buffer_size,startup_config_section_count;
	 struct t_ini_buffer *ini_buffer;
	 unsigned_int error_code;
	 TConfigManagerType Manager_Type;

	 bool __fastcall load_app_startup_buffer(const UnicodeString config_object_path);
	 bool __fastcall load_app_startup_config();

  public :

	 __fastcall TConfigManager(const UnicodeString config_object_path,const TConfigManagerType manager_type);
	 __fastcall ~TConfigManager();

	 __fastcall TConfigManagerType GetManagerType() { return Manager_Type; }
	 unsigned_int __fastcall GetLastError() { return error_code; }

	 UnicodeString __fastcall ReadParamByName(const UnicodeString ParamName);
     UnicodeString __fastcall ReadParamByID(const unsigned_int id);

};