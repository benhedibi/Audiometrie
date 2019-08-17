#ifndef CRC32_H
#define CRC32_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>

extern uint32 crc32_data(const puchar data,const unsigned_int data_size,const uint32 previous_crc);

#ifdef __cplusplus
}
#endif

#endif