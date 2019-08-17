//---------------------------------------------------------------------------

#ifndef vtm_managerH
#define vtm_managerH
//---------------------------------------------------------------------------
#endif

#include <System.Classes.hpp>
#include <globaldef.h>



class TVTM_Manager
{
  private :

	 opaque_ptr vtm_block_pool;
	 unsigned_int vtm_block_count;
	 unsigned_int vtm_block_size;
	 unsigned_int error_code;


  public :

	 __fastcall TVTM_Manager(const unsigned_int block_count,const unsigned_int block_size);
	 __fastcall ~TVTM_Manager();

	 bool __fastcall UpdateBlock(const unsigned_int block_index,const opaque_ptr data);
	 opaque_ptr __fastcall GetData(const unsigned_int block_index);

	 __fastcall unsigned_int GetLastError() { return error_code; }

};