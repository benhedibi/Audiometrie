#ifndef LILLY_IO_H
#define LILLY_IO_H

#include <globaldef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
			   lilly_io_fmCreateNew,
			   lilly_io_fmCreate,
               lilly_io_fmOpen,
			   lilly_io_fmOpenOrCreate,
			   lilly_io_fmTruncate,
			   lilly_io_fmAppend
			 } t_lilly_io_file_modes;

typedef enum {
			   lilly_io_faRead,
			   lilly_io_faWrite,
			   lilly_io_faReadWrite
			 } t_lilly_io_file_acess;

typedef enum {
			   lilly_soFromBeginning,
			   lilly_soFromCurrent,
               lilly_soFromEnd
			 } t_lilly_seek_modes;

extern unsigned_int lilly_io_open_file(const puchar path,const t_lilly_io_file_modes file_mode,const t_lilly_io_file_acess file_access);
extern unsigned_int lilly_io_create_file(const puchar path);

extern void lilly_io_close_file(const unsigned_int file_handle);

extern boolean lilly_io_delete_file(const puchar path);
extern boolean lilly_io_file_exists(const puchar path);
extern boolean lilly_io_file_copy(const puchar source_path,const puchar destination_path,const boolean fail_if_exist);

extern boolean lilly_io_file_read(const unsigned_int file_handle,const puchar buffer,const unsigned_int buffer_size);
extern boolean lilly_io_file_write(const unsigned_int file_handle,const puchar buffer,const unsigned_int buffer_size);
extern uint64 lilly_io_file_seek(const unsigned_int file_handle,const uint64 offset,const t_lilly_seek_modes seek_mode);

extern uint64 lilly_io_get_file_size(const puchar path);
extern uint64 lilly_io_get_file_size_ex(const unsigned_int file_handle);

#ifdef __cplusplus
}
#endif

#endif