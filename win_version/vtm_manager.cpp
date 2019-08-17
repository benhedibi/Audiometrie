//---------------------------------------------------------------------------

#pragma hdrstop

#include "vtm_manager.hpp"

#include <cmnfnc.h>
#include <lilly_io.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TVTM_Manager::TVTM_Manager(const unsigned_int block_count,const unsigned_int block_size)
{


	 error_code = ERROR_SUCCESS;

	 if ((block_size != 4) && (block_size != 8))
	 {
	   error_code = API_ERROR;
	   return;
	 }

	 vtm_block_count = block_count + 1;  // add for convenance and safety bla bla bla
	 vtm_block_size = block_size;

	 vtm_block_pool = malloc(block_count * block_size);

	 if (!vtm_block_pool)
	 {
	   error_code = MEM_ALLOC_ERROR;
	 }

	 return;

}

__fastcall TVTM_Manager::~TVTM_Manager()
{

	if ((vtm_block_pool) && ((signed_int)vtm_block_count > 0) && ((signed_int)vtm_block_size > 0))
	{
	  free(vtm_block_pool);
	}

	vtm_block_pool = NULL;
	vtm_block_count = 0;
	vtm_block_size = 0;

    return;

}

bool __fastcall TVTM_Manager::UpdateBlock(const unsigned_int block_index,const opaque_ptr data)
{

	error_code = ERROR_SUCCESS;

	if (((signed_int)block_index < 0) || (block_index > vtm_block_count))
	{
	  error_code = INDEX_OUT_OF_RANGE;
	  return false;
	}

	if (vtm_block_size < 8)
	{
	  puint32 ptr = (puint32)vtm_block_pool;

	  ptr[block_index] = *(puint32)data;
	}
	else
	{
	  puint64 ptr = (puint64)vtm_block_pool;

	  ptr[block_index]= *(puint64)data;
	}

	return true;

}

opaque_ptr __fastcall TVTM_Manager::GetData(const unsigned_int block_index)
{

    error_code = ERROR_SUCCESS;

	if (((signed_int)block_index < 0) || (block_index > vtm_block_count))
	{
	  error_code = INDEX_OUT_OF_RANGE;
	  return NULL;
	}

	if (vtm_block_size < 8)
	{
	  puint32 ptr = (puint32)vtm_block_pool;

	  return (opaque_ptr)&ptr[block_index];
	}
	else
	{
	  puint64 ptr = (puint64)vtm_block_pool;

	  return (opaque_ptr)&ptr[block_index];
	}

}

