//---------------------------------------------------------------------------

#pragma hdrstop

#include "def_values.hpp"

#include <cmnfnc.h>
#include <lilly_io.h>
#include <lilly_utils.h>

#include <db_signatures.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)


#define FREE_DEF_RECORD_STATE      0
#define ACTIVE_DEF_RECORD_STATE    1
#define UNDEFINED_DEF_RECORD_STATE 3

#define SLOT_MARKER 0x5047

typedef struct {
				 uint16 marker;
				 uint8 state;
				 uint8 reserved;
				 uint32 slot_crc;
			   } t_slot_block_hdr,*p_slot_block_hdr;


uint8 __fastcall TDef_Values::get_slot_state(const opaque_ptr slot_data)
{
  p_slot_block_hdr block_hdr = (p_slot_block_hdr)slot_data;


	if (block_hdr->marker != SLOT_MARKER)
	{
	  error_code = TAMPERED_DATA_ERROR;
	  return UNDEFINED_DEF_RECORD_STATE;
	}

	return block_hdr->state;
}

bool __fastcall TDef_Values::set_slot_state(const opaque_ptr slot_data,const uint8 slot_state)
{
  p_slot_block_hdr block_hdr = (p_slot_block_hdr)slot_data;


	if (slot_state > UNDEFINED_DEF_RECORD_STATE)
	{
	  error_code = TAMPERED_DATA_ERROR;
	  return false;
	}

	block_hdr->marker = SLOT_MARKER;
	block_hdr->state = slot_state;

    return true;
}

opaque_ptr __fastcall TDef_Values::iterate(const int index)
{
  puchar p = (puchar)db_header;


	if (index > slot_counts) return NULL;

	p += sizeof(*db_header) + (index * slot_size);

	if (get_slot_state(p) == UNDEFINED_DEF_RECORD_STATE)
	{
	  p = NULL;
	}

	return p;
}

bool __fastcall TDef_Values::update_file()
{

	error_code = ERROR_SUCCESS;

	db_header->crc32 = lilly_crc32_buffer((puchar)db_header,4,0);

	db_header->crc32 = lilly_crc32_buffer((puchar)((unsigned_int)db_header + sizeof(*db_header)),handle_size - sizeof(*db_header),db_header->crc32);

	if (!lilly_io_file_write(handle,(puchar)db_header,handle_size))
	{
	  error_code = IO_ERROR;
	}

	return (error_code == ERROR_SUCCESS);
}

opaque_ptr __fastcall TDef_Values::read_data(const opaque_ptr data)
{

	return (opaque_ptr)((unsigned_int)data + sizeof(t_slot_block_hdr));
}

void __fastcall TDef_Values::write_data(opaque_ptr slot_ptr,const opaque_ptr user_data)
{

	avcore_memcpy((puchar)slot_ptr + sizeof(t_slot_block_hdr),user_data,slot_size - sizeof(t_slot_block_hdr));

    return;
}

__fastcall TDef_Values::TDef_Values(const UnicodeString data_path,const uint32 db_signature,const int def_slot_size,const int def_slot_counts)
{
  int default_size,i;
  opaque_ptr p;


	db_header = NULL;

	handle = 0;

	handle_size = 0;

	error_code = ERROR_SUCCESS;

	def_data_path = data_path;

	if ((def_data_path == "") || (!db_signature) || (def_slot_size <= 0) || (def_slot_counts <= 0))
	{
	  error_code = API_ERROR;
	  return;
	}

	slot_size = def_slot_size + sizeof(t_slot_block_hdr);

	slot_counts = def_slot_counts;

	current_slot_index = 0;

	free_slot_counts = 0;

	if (lilly_io_file_exists((puchar)def_data_path.c_str()))
	{
	  handle = lilly_io_open_file((puchar)def_data_path.c_str(),lilly_io_fmOpen,lilly_io_faReadWrite);
	}
	else handle = lilly_io_create_file((puchar)def_data_path.c_str());

	if ((signed_int)handle <= 0)
	{
	  error_code = IO_ERROR;
	  return;
	}

	handle_size = lilly_io_get_file_size_ex(handle);

	if ((int64)handle_size < 0)
	{
	  error_code = IO_ERROR;
	  return;
	}

	default_size = sizeof(t_def_values_db_header) + (slot_size * slot_counts);

	if (handle_size)
	{
	  uint32 crc_value;
	  uint8 state;

	  if (handle_size < default_size)
	  {
		error_code = FATAL_ERROR;
		return;
	  }

	  db_header = (struct t_def_values_db_header *)malloc(handle_size);

	  if (!db_header)
	  {
		error_code = MEM_ALLOC_ERROR;
		return;
	  }

	  if (!lilly_io_file_read(handle,(puchar)db_header,handle_size))
	  {
		error_code = IO_ERROR;
		return;
	  }

	  if (db_header->signature != db_signature)
	  {
		error_code = DATA_SIGNATURE_ERROR;
		return;
	  }

	  crc_value = lilly_crc32_buffer((puchar)db_header,4,0);

	  crc_value = lilly_crc32_buffer((puchar)((unsigned_int)db_header + sizeof(*db_header)),handle_size - sizeof(*db_header),crc_value);

	  if (crc_value != db_header->crc32)
	  {
		error_code = DATA_SIGNATURE_ERROR;
		return;
	  }

	  i = 0;

	  while (true)
	  {
		p = iterate(i++);

		if (!p) break;

		state = get_slot_state(p);

		if (state == FREE_DEF_RECORD_STATE)
		{
		  free_slot_counts++;
		}
		else if (state == UNDEFINED_DEF_RECORD_STATE) break;
	  }

	  if (error_code != ERROR_SUCCESS) return;

	}
	else
	{
	  handle_size = default_size;

	  db_header = (struct t_def_values_db_header *)malloc(handle_size);

	  if (!db_header)
	  {
		error_code = MEM_ALLOC_ERROR;
		return;
	  }

	  avcore_memset(db_header,0,handle_size);

	  db_header->signature = db_signature;

	  i = 0;

	  while (true)
	  {
		p = iterate(i++);
		if ((!p) || (!set_slot_state(p,FREE_DEF_RECORD_STATE))) break;
	  }

	  if ((error_code == ERROR_SUCCESS) && (update_file()))
	  {
        free_slot_counts = slot_counts;
	  }
	}

	return;
}

__fastcall TDef_Values::~TDef_Values()
{

	if ((signed_int)handle > 0)
	{
	  lilly_io_close_file(handle);
	  handle = 0;
	}

	if (db_header)
	{
	  free(db_header);
	  db_header = NULL;
	}

    return;
}

bool __fastcall TDef_Values::Add(const opaque_ptr def_data)
{
  opaque_ptr rec_data;
  int i;
  uint8 state;


	error_code = ERROR_SUCCESS;

	if (!def_data)
	{
	  error_code = API_ERROR;
	  return false;
	}

	if (!free_slot_counts)
	{
      error_code = NO_MORE_FREE_SLOTS_ERROR;
	  return false;
	}

	i = 0;

	while (true)
	{
	  rec_data = iterate(i++);

	  if (!rec_data) break;

	  state = get_slot_state(rec_data);

	  if (state != ACTIVE_DEF_RECORD_STATE) break;
    }

	switch (state)
	{
		 case ACTIVE_DEF_RECORD_STATE : if (!rec_data)
										{
										  error_code = NO_MORE_FREE_SLOTS_ERROR;
										  free_slot_counts = 0;
										}

										return false;

	  case UNDEFINED_DEF_RECORD_STATE : return false;

							  default : break;
	}


	if (!set_slot_state(rec_data,ACTIVE_DEF_RECORD_STATE)) return false;

	write_data(rec_data,def_data);

	if (!update_file()) return false;

	free_slot_counts--;

    return true;
}

bool __fastcall TDef_Values::Delete(const int index)
{
  opaque_ptr rec_data;
  int i;
  uint8 state;


	error_code = ERROR_SUCCESS;

	if (index < 0)
	{
	  error_code = API_ERROR;
	  return false;
	}
	else if (index >= slot_counts)
	{
	  error_code = INDEX_OUT_OF_RANGE;
      return false;
	}
	else if (free_slot_counts >= slot_counts) return true;

	current_slot_index = 0;

	while (true)
	{
	  rec_data = iterate(current_slot_index++);

	  if (!rec_data) break;

	  state = get_slot_state(rec_data);

	  if (state == UNDEFINED_DEF_RECORD_STATE)
	  {
		return false;
	  }
	  else if (state == ACTIVE_DEF_RECORD_STATE)
	  {
		if (i == index) break;
		i++;
	  }
	}

	if ((!rec_data) || (i != index))
	{
	  error_code = INDEX_OUT_OF_RANGE;
	  return false;
    }

	if ((!set_slot_state(rec_data,FREE_DEF_RECORD_STATE)) || (!update_file())) return false;

	free_slot_counts++;

	return true;
}

opaque_ptr __fastcall TDef_Values::GetFirstData()
{
  opaque_ptr data;
  uint8 state;


	error_code = ERROR_SUCCESS;

	if (free_slot_counts >= slot_counts)
	{
	  free_slot_counts = slot_counts;
	  error_code = EMPTY_FILE_ERROR;
	  return NULL;
	}

	current_slot_index = 0;

	while (true)
	{
	  data = iterate(current_slot_index++);

	  if (!data) break;

	  state = get_slot_state(data);

	  if (state == UNDEFINED_DEF_RECORD_STATE)
	  {
		return false;
	  }
	  else if (state == ACTIVE_DEF_RECORD_STATE) break;
	}

	if (!data)
	{
	  error_code = TAMPERED_DATA_ERROR;
	  return NULL;
	}

	return read_data(data);
}

opaque_ptr __fastcall TDef_Values::GetNextData()
{
  opaque_ptr data;
  uint8 state;


	if (free_slot_counts >= slot_counts)
	{
	  free_slot_counts = slot_counts;
	  error_code = EMPTY_FILE_ERROR;
	  return NULL;
	}

	error_code = ERROR_SUCCESS;

	if (current_slot_index >= slot_counts) return false;

	while (true)
	{
	  data = iterate(current_slot_index++);

	  if (!data) break;

	  state = get_slot_state(data);

	  if (state == UNDEFINED_DEF_RECORD_STATE)
	  {
		return false;
	  }
	  else if (state == ACTIVE_DEF_RECORD_STATE) break;
	}

	if (data)
	{
	  return read_data(data);
	}

    return false;
}

opaque_ptr __fastcall TDef_Values::GetData(const int index)
{
  opaque_ptr rec_data;
  int i;
  uint8 state;


	error_code = ERROR_SUCCESS;

	if (index < 0)
	{
	  error_code = API_ERROR;
	  return NULL;
	}
	else if (index >= slot_counts)
	{
	  error_code = INDEX_OUT_OF_RANGE;
	  return NULL;
	}

	current_slot_index = 0;

	while (true)
	{
	  rec_data = iterate(current_slot_index++);

	  if (!rec_data) break;

	  state = get_slot_state(rec_data);

	  if (state == UNDEFINED_DEF_RECORD_STATE)
	  {
		return NULL;
	  }
	  else if (state == ACTIVE_DEF_RECORD_STATE)
	  {
		if (i == index) break;
		i++;
	  }
	}

	if ((!rec_data) || (i != index))
	{
	  error_code = INDEX_OUT_OF_RANGE;
	  return NULL;
    }

	return read_data(rec_data);
}

__fastcall TAudiograms_Def_Values::TAudiograms_Def_Values(const UnicodeString data_path,const int slot_counts) : TDef_Values(data_path,AUDIOGRAM_DB_SIGNATURE,sizeof(t_audiogram_data),slot_counts)
{
	return; // tout le travail est fait dans la base class, ce qu'il reste c'est vérifier depuis le caller si tout est bien avec getlasterror
}

__fastcall TAudiograms_Def_Values::~TAudiograms_Def_Values()
{
	return;
}

__fastcall TTympanograms_Def_Values::TTympanograms_Def_Values(const UnicodeString data_path,const int slot_counts) : TDef_Values(data_path,TYMPANOGRAM_DB_SIGNATURE,sizeof(t_tympanogram_data),slot_counts)
{
	return; // tout le travail est fait dans la base class, ce qu'il reste c'est vérifier depuis le caller si tout est bien avec getlasterror
}

__fastcall TTympanograms_Def_Values::~TTympanograms_Def_Values()
{
	return;
}

__fastcall TAudiovoc_Def_Values::TAudiovoc_Def_Values(const UnicodeString data_path,const int slot_counts) : TDef_Values(data_path,AUDIOMETRIE_VOCALE_DB_SIGNATURE,sizeof(t_audiovoc_data),slot_counts)
{
	return; // tout le travail est fait dans la base class, ce qu'il reste c'est vérifier depuis le caller si tout est bien avec getlasterror
}

__fastcall TAudiovoc_Def_Values::~TAudiovoc_Def_Values()
{
	return;
}

__fastcall TGainprot_Def_Values::TGainprot_Def_Values(const UnicodeString data_path,const int slot_counts) : TDef_Values(data_path,GAIN_PROTHETIQUE_DB_SIGNATURE,sizeof(t_gainp_data),slot_counts)
{
	return; // tout le travail est fait dans la base class, ce qu'il reste c'est vérifier depuis le caller si tout est bien avec getlasterror
}

__fastcall TGainprot_Def_Values::~TGainprot_Def_Values()
{
	return;
}


