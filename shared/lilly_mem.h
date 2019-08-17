#ifndef LILLY_MEM_H
#define LILLY_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>

extern opaque_ptr lilly_malloc(const unsigned_int mem_size);
extern opaque_ptr lilly_realloc(const opaque_ptr mem_block,const unsigned_int old_size,const unsigned_int new_size);
extern void lilly_free(const opaque_ptr mem_block,const unsigned_int optional_size);

#ifdef __cplusplus
}
#endif

#endif