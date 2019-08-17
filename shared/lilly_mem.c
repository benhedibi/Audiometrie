#include <lilly_mem.h>
#include <alloc.h>
#include <cmnfnc.h>


opaque_ptr lilly_malloc(const unsigned_int mem_size)
{
  opaque_ptr mem_block;


	 mem_block = malloc(mem_size);

	 return mem_block;
}

opaque_ptr lilly_realloc(const opaque_ptr mem_block,const unsigned_int old_size,const unsigned_int new_size)
{
  opaque_ptr new_block;
  unsigned_int copy_block_size;


	 if ((!mem_block) || ((signed_int)new_size <= 0)) return NULL;

	 if (old_size == new_size) return mem_block;

	 if (old_size > new_size) copy_block_size = new_size;
	 else copy_block_size = old_size;

	 new_block = lilly_malloc(new_size);

	 if (!new_block) goto fin; // to avoid lefting mem buffers

	 avcore_memcpy(new_block,mem_block,copy_block_size);

	 fin :

	 lilly_free(mem_block,old_size);

	 return new_block;

}

void lilly_free(const opaque_ptr mem_block,const unsigned_int optional_size)
{
   if (!mem_block) return;

   free(mem_block);
}