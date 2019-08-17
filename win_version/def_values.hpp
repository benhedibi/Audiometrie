//---------------------------------------------------------------------------

#ifndef def_valuesH

#define def_valuesH


#include <System.Classes.hpp>
#include <globaldef.h>

#include <audiograms_engine.h>
#include <tympano_engine.h>
#include <audiovocs_engine.h>
#include <gainp_engine.h>

#define NO_MORE_FREE_SLOTS_ERROR (1984 * 1979)
#define TAMPERED_DATA_ERROR      (1985 * 1979)
#define EMPTY_FILE_ERROR         (1986 * 1979)

class TDef_Values
{
  private :

	 #pragma pack(push,1)

	 struct t_def_values_db_header {
									 uint32 signature;
									 uint32 crc32;
			                       } t_def_values_db_header;

	 #pragma pack(pop)

	 uint8 __fastcall get_slot_state(const opaque_ptr slot_data);
	 bool __fastcall set_slot_state(const opaque_ptr slot_data,const uint8 slot_state);

	 opaque_ptr __fastcall iterate(const int index);

	 bool __fastcall update_file();

	 opaque_ptr __fastcall read_data(const opaque_ptr data);
	 void __fastcall write_data(const opaque_ptr slot_ptr,const opaque_ptr user_data);

     struct t_def_values_db_header *db_header;
	 unsigned_int handle;
	 int slot_size,slot_counts,current_slot_index,free_slot_counts;
	 uint64 handle_size;
	 unsigned_int error_code;
	 UnicodeString def_data_path;

  public :

	 __fastcall TDef_Values(const UnicodeString data_path,const uint32 db_signature,const int def_slot_size,const int def_slot_counts);
	 __fastcall ~TDef_Values();

	 bool __fastcall Add(const opaque_ptr def_data);
	 bool __fastcall Delete(const int index);

	 opaque_ptr __fastcall GetFirstData();
	 opaque_ptr __fastcall GetNextData();

     opaque_ptr __fastcall GetData(const int index);

	 __fastcall unsigned_int GetLastError() { return error_code; }

};

#pragma pack(push,1)

typedef struct {
                 uchar name[48];
				 t_audiogram_oreille oreille_droite;
				 t_audiogram_oreille oreille_gauche;
				 uint8 weber[8];
			   } t_audiogram_data,*p_audiogram_data;

#pragma pack(pop)

class TAudiograms_Def_Values : public TDef_Values
{
   public :


	 __fastcall TAudiograms_Def_Values(const UnicodeString data_path,const int slot_counts);
	 __fastcall ~TAudiograms_Def_Values();

};


#pragma pack(push,1)

typedef struct {
                 uchar name[48];
				 t_tympano_oreille oreille_droite;
				 t_tympano_oreille oreille_gauche;
			   } t_tympanogram_data,*p_tympanogram_data;

#pragma pack(pop)

class TTympanograms_Def_Values : public TDef_Values
{
   public :


	 __fastcall TTympanograms_Def_Values(const UnicodeString data_path,const int slot_counts);
	 __fastcall ~TTympanograms_Def_Values();

};


#pragma pack(push,1)

typedef struct {
				 uchar name[48];
				 t_audiovoc appareil_off;
                 t_audiovoc appareil_on;
				 uint8 oreille;
				 uint8 nature;
				 uint8 controle;
			   } t_audiovoc_data,*p_audiovoc_data;

#pragma pack(pop)

class TAudiovoc_Def_Values : public TDef_Values
{
   public :


	 __fastcall TAudiovoc_Def_Values(const UnicodeString data_path,const int slot_counts);
	 __fastcall ~TAudiovoc_Def_Values();

};


#pragma pack(push,1)

typedef struct {
                 uchar name[48];
				 t_gainp_mesures mesures; // 48
				 uint8 oreille;
				 uint8 nature;
				 uint8 prothese;
			   } t_gainp_data,*p_gainp_data;

#pragma pack(pop)

class TGainprot_Def_Values : public TDef_Values
{
   public :


	 __fastcall TGainprot_Def_Values(const UnicodeString data_path,const int slot_counts);
	 __fastcall ~TGainprot_Def_Values();

};

#endif


