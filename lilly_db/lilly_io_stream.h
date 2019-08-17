#ifndef LILLY_IO_STRM_H
#define LILLY_IO_STRM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <globaldef.h>


extern opaque_ptr lilly_io_strm_create_stream(const puchar file_path,const unsigned_int io_buffer_size,const punsigned_int error_code,const uint32 encryption_key,const boolean data_compress);
extern opaque_ptr lilly_io_strm_open_stream(const puchar file_path,const unsigned_int io_buffer_size,const punsigned_int error_code,const uint32 encryption_key,const unsigned_int data_cache_size,const boolean data_compress,const boolean read_only);
extern void lilly_io_strm_close_stream(const opaque_ptr stream_handle);

extern boolean lilly_io_strm_truncate_stream(const opaque_ptr stream_handle,const puchar file_path,const unsigned_int trunc_offset);

extern uint64 lilly_io_strm_get_stream_size(const opaque_ptr stream_handle);
extern uint32 lilly_io_strm_get_stream_cache_size(const opaque_ptr stream_handle);

extern boolean lilly_io_strm_set_current_stream_offset(const opaque_ptr stream_handle,const uint64 stream_offset,const boolean write_mode);
extern uint64 lilly_io_strm_get_current_stream_offset(const opaque_ptr stream_handle);

extern puchar lilly_io_strm_get_stream_buffer(const opaque_ptr stream_handle,const uint64 stream_offset);
extern void lilly_io_strm_clear_io_buffer(const opaque_ptr stream_handle);

extern puchar lilly_io_strm_read_stream(const opaque_ptr stream_handle,const uint64 stream_offset);
extern boolean lilly_io_strm_write_stream(const opaque_ptr stream_handle,const puchar data,const uint64 stream_offset);

extern boolean lilly_io_strm_read_stream_ex(const opaque_ptr stream_handle,const puchar data,const unsigned_int data_size,const uint64 stream_offset);
extern boolean lilly_io_strm_write_stream_ex(const opaque_ptr stream_handle,const puchar data,const unsigned_int data_size,const uint64 stream_offset);

extern unsigned_int lilly_io_strm_get_last_error(const opaque_ptr stream_handle);



#ifdef __cplusplus
}
#endif

#endif
