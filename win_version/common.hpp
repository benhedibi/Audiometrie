#ifndef commonH

#define commonH


#include <System.Classes.hpp>
#include <VCL.Dialogs.hpp>


#include "def_values.hpp"

#include <globaldef.h>
#include <cmnfnc.h>

#include <lilly_session_manager.h>


typedef struct {
				 unsigned_int size;
				 puchar data;
			   } t_blob_buffer,*p_blob_buffer;

typedef struct {
				 struct t_lilly_db_handle *db_handle;
				 p_lilly_db_engine engine;
				 opaque_ptr current_record;
				 int caller_page_index;
				 uint32 observation_crc32;
				 UnicodeString grph_types_db_path;
				 bool edit_mode;
				 bool updated_picture;
				 bool deleted_picture;
				 bool reserved[4];
			   } t_engine_entry,*p_engine_entry;

typedef struct {
				 t_engine_entry operators_engine;
				 t_engine_entry doctors_engine;
				 t_engine_entry patients_engine;
				 t_engine_entry consultations_engine;
				 t_engine_entry audiograms_engine;
				 t_engine_entry tympanograms_engine;
				 t_engine_entry gainprots_engine;
				 t_engine_entry audiovocs_engine;
			   } t_engines_container,*p_engines_container;

typedef struct {
				 int path_len;
				 uchar path_data[260 * 2];
			   } t_session_manager_path,*p_session_manager_path;

typedef struct {
				 p_lilly_db_session_manager session_manager;
                 TStringList *femmes_names;
				 p_session_manager_path blobs_path;
				 p_session_manager_path operators_path;
				 p_session_manager_path doctors_path;
				 p_session_manager_path patients_path;
				 p_session_manager_path audiograms_path;
				 p_session_manager_path tympanograms_path;
				 p_session_manager_path gainprot_path;
				 p_session_manager_path audiovoc_path;
				 p_session_manager_path consultations_path;
				 p_session_manager_path gouv_path;
				 p_session_manager_path gprefs_path;
                 p_session_manager_path jobrefs_path;
				 p_session_manager_path pays_path;
				 p_session_manager_path femmes_path;
				 p_session_manager_path unknown_femme_picture_path;
				 p_session_manager_path unknown_homme_picture_path;
				 t_engines_container engines;
				 uint32 current_operator_id;
                 UnicodeString CurrentOpName;
			   } t_session_params,*p_session_params;

 typedef enum {
			   t_undefined_state_change_type,
			   t_record_id_change_type,
			   t_record_state_change_type
			 } t_consultation_onchange_event_type;


void __fastcall report_event(const UnicodeString event,const TMsgDlgType dlg_type,const boolean fatal);
bool __fastcall ask_event(const UnicodeString event);

UnicodeString __fastcall error_code_to_string(const unsigned_int error_code);

UnicodeString __fastcall date_to_string(const p_date_time date);
UnicodeString __fastcall datetime_to_string(const p_date_time datetime);
bool __fastcall string_to_date_stamp(const puchar date_field,const int date_field_len,const p_date_time date_result);

UnicodeString __fastcall format_name(UnicodeString name);

void __fastcall record_id_to_blob_path(struct t_lilly_db_handle *db_handle,const puchar blob_path,const unsigned_int max_len,const uint32 record_id,const t_lilly_db_blob_type blob_type);

bool __fastcall load_blob(const p_engine_entry engine_entry,TObject *object,const uint32 record_id,const t_lilly_db_blob_type blob_type);
bool __fastcall add_blob(const p_engine_entry engine_entry,TObject *object,const uint32 record_id,const uint32 operator_id,const t_lilly_db_blob_type blob_type);
bool __fastcall delete_blob(const p_engine_entry engine_entry,const uint32 record_id,const t_lilly_db_blob_type blob_type);
bool __fastcall update_blob(const p_engine_entry engine_entry,TObject *object,const uint32 record_id,const uint32 operator_id,const t_lilly_db_blob_type blob_type);

bool __fastcall blob_buffer_to_component(const p_blob_buffer blob_buffer,TObject *component,const t_lilly_db_blob_type blob_type);
bool __fastcall component_to_blob_buffer(const p_blob_buffer blob_buffer,TObject *component,const t_lilly_db_blob_type blob_type);

void __fastcall fill_combo_box(const p_session_params session_params,TComboBox *combo_box,const uint32 engine_signature);

puint32 __fastcall Load_MedId_Table(const p_session_params session_params,TComboBox *combo_box);
void __fastcall Unload_MedId_Table(const puint32 PatientPageMed_Ids);

bool __fastcall load_old_data_to_listview(const p_session_params session_params,const uint32 engine_id,const uint32 patient_id,TListView *listview);

bool __fastcall load_grph_list(const p_engine_entry engine_entry,const uint32 engine_id,TComboBox *combo_box);
void __fastcall delete_grph_item(const p_engine_entry engine_entry,const uint32 engine_id,TComboBox *combo_box);

bool __fastcall set_opname_and_time(const p_engine_entry engine_entry,const uint32 engine_id,opaque_ptr record,TLabel *op_lbl,TLabel *time_lbl);

void __fastcall draw_chart_in_quickreport(const opaque_ptr chart_ptr,const opaque_ptr quick_report_image_ptr);

bool __fastcall load_image(TImage *image,const UnicodeString image_path);

void __fastcall resize_picture(TImage *image,const UnicodeString image_path);
void __fastcall resize_picture_ex(TBitmap *image_src,TBitmap *image_destination);

#endif