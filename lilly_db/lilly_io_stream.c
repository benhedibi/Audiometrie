#include <lilly_io_stream.h>
#include <lilly_io.h>
#include <lilly_mem.h>
#include <cmnfnc.h>



typedef struct {
				 unsigned_int error_code;
				 unsigned_int cache_size;
				 puchar cache_mem;
				 unsigned_int io_handle;
				 uint64 io_size;
				 unsigned_int io_buffer_size;
				 puchar io_buffer;
				 unsigned_int last_io_size;
                 uint64 current_offset;
				 uint32 encryption_key;
				 boolean data_compress;
				 boolean read_only;
			   } t_lilly_io_strm_handle,*p_lilly_io_strm_handle;



opaque_ptr lilly_io_strm_create_stream(const puchar file_path,const unsigned_int io_buffer_size,const punsigned_int error_code,const uint32 encryption_key,const boolean data_compress)
{
  p_lilly_io_strm_handle handle;


	 if (!error_code) return NULL;

	 *error_code = ERROR_SUCCESS;

	 if ((!file_path) || ((signed_int)io_buffer_size <= 0))
	 {
	   *error_code = API_ERROR;
	   return NULL;
	 }

	 if (lilly_io_file_exists(file_path))
	 {
	   *error_code = IO_ERROR;
	   return NULL;
	 }

	 handle = (p_lilly_io_strm_handle)lilly_malloc(sizeof(*handle));

	 if (!handle)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   return NULL;
	 }

	 avcore_memset(handle,0,sizeof(*handle));

	 handle->io_handle = lilly_io_create_file(file_path);

	 if ((signed_int)handle->io_handle <= 0)
	 {
	   *error_code = IO_ERROR;
	   lilly_io_strm_close_stream(handle);
	   return NULL;
	 }

	 handle->io_buffer_size = io_buffer_size;

	 handle->io_buffer = lilly_malloc(io_buffer_size);

	 if (!handle->io_buffer)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   lilly_io_strm_close_stream(handle);
	   return NULL;
	 }

	 avcore_memset(handle->io_buffer,0,io_buffer_size);

	 handle->encryption_key = encryption_key;
	 handle->data_compress = data_compress;

	 return handle;

}

opaque_ptr lilly_io_strm_open_stream(const puchar file_path,const unsigned_int io_buffer_size,const punsigned_int error_code,const uint32 encryption_key,const unsigned_int data_cache_size,const boolean data_compress,const boolean read_only)
{
  static const t_lilly_io_file_acess access_flags[2] = {lilly_io_faReadWrite,lilly_io_faRead};

  p_lilly_io_strm_handle handle;


	 if (!error_code) return NULL;

      *error_code = ERROR_SUCCESS;

	 if ((!file_path) || ((signed_int)io_buffer_size <= 0) || ((signed_int)data_cache_size < 0))
	 {
	   *error_code = API_ERROR;
	   return NULL;
	 }

	 if (!lilly_io_file_exists(file_path))
	 {
	   *error_code = IO_ERROR;
	   return NULL;
	 }

	 handle = (p_lilly_io_strm_handle)lilly_malloc(sizeof(*handle));

	 if (!handle)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   return NULL;
	 }

	 avcore_memset(handle,0,sizeof(*handle));

	 handle->io_handle = lilly_io_open_file(file_path,lilly_io_fmOpen,access_flags[read_only]);

	 if ((signed_int)handle->io_handle <= 0)
	 {
	   *error_code = IO_ERROR;
	   lilly_io_strm_close_stream(handle);
	   return NULL;
	 }

	 handle->io_size = lilly_io_get_file_size_ex(handle->io_handle);

	 if ((int64)handle->io_size < 0)
	 {
	   *error_code = IO_ERROR;
	   lilly_io_strm_close_stream(handle);
	   return NULL;
     }

	 if ((signed_int)data_cache_size > 0)
	 {
	   handle->cache_size = MACRO_MIN_VALUE((uint64)data_cache_size,handle->io_size);

	   if (handle->cache_size)
	   {
         handle->cache_mem = lilly_malloc((unsigned_int)handle->cache_size);

		 if (!handle->cache_mem)
		 {
		   *error_code = MEM_ALLOC_ERROR;
		   lilly_io_strm_close_stream(handle);
		   return NULL;
		 }

		 if (!lilly_io_file_read(handle->io_handle,handle->cache_mem,(unsigned_int)handle->cache_size))
		 {
		   *error_code = IO_ERROR;
		   lilly_io_strm_close_stream(handle);
		   return NULL;
		 }
       }
	 }

	 handle->io_buffer_size = io_buffer_size;

	 handle->io_buffer = lilly_malloc(io_buffer_size);

	 if (!handle->io_buffer)
	 {
	   *error_code = MEM_ALLOC_ERROR;
	   lilly_io_strm_close_stream(handle);
	   return NULL;
	 }

	 avcore_memset(handle->io_buffer,0,io_buffer_size);

	 handle->encryption_key = encryption_key;
	 handle->data_compress = data_compress;

	 return handle;
}

void lilly_io_strm_close_stream(const opaque_ptr stream_handle)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (!handle) return;

	 if ((signed_int)handle->io_handle > 0)
	 {
	   lilly_io_close_file(handle->io_handle);
	   handle->io_handle = 0;
	 }

	 if ((handle->cache_mem) && ((int64)handle->cache_size > 0))
	 {
	   lilly_free(handle->cache_mem,(unsigned_int)handle->cache_size);
	   handle->cache_size = 0;
	   handle->cache_mem = NULL;
	 }

	 if ((handle->io_buffer) && ((signed_int)handle->io_buffer_size > 0))
	 {
	   lilly_free(handle->io_buffer,handle->io_buffer_size);
	   handle->io_buffer = NULL;
	   handle->io_buffer_size = 0;
	 }

	 lilly_free(handle,sizeof(*handle));

	 return;
}

boolean lilly_io_strm_truncate_stream(const opaque_ptr stream_handle,const puchar file_path,const unsigned_int trunc_offset)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;
  puchar buffer;


	 if (!handle) return FALSE;

	 if (((signed_int)trunc_offset < 0) || ((uint64)trunc_offset > handle->io_size) || (trunc_offset > (unsigned_int)MAXWORD) || (!file_path) ||(*file_path == 0) || (!handle->io_handle))
	 {
	   handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 if (handle->cache_mem)
	 {
	   lilly_free(handle->cache_mem,handle->cache_size);
	   handle->cache_mem = NULL;
	   handle->cache_size = 0;
	 }

	 if (!trunc_offset)
	 {
	   lilly_io_close_file(handle->io_handle);

	   handle->io_handle = 0;

	   if (!lilly_io_delete_file(file_path))
	   {
		 handle->error_code = IO_ERROR;
		 return FALSE;
	   }

	   handle->io_handle = lilly_io_create_file(file_path);

	   if ((signed_int)handle->io_handle <= 0)
	   {
		 handle->error_code = IO_ERROR;
		 return FALSE;
	   }

	   return TRUE;
	 }

	 buffer = lilly_malloc(trunc_offset);

	 if (!buffer)
	 {
	   handle->error_code = MEM_ALLOC_ERROR;
	   return FALSE;
	 }

	 if ((lilly_io_file_seek(handle->io_handle,0,lilly_soFromBeginning) != 0) || (!lilly_io_file_read(handle->io_handle,buffer,trunc_offset)))
	 {
	   handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 lilly_io_close_file(handle->io_handle);

	 handle->io_handle = 0;

	 if (!lilly_io_delete_file(file_path))
	 {
	   handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 handle->io_handle = lilly_io_create_file(file_path);

	 if ((signed_int)handle->io_handle <= 0)
	 {
	   handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_file_write(handle->io_handle,buffer,trunc_offset))
	 {
	   handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 handle->current_offset = trunc_offset;

	 handle->last_io_size = trunc_offset;

	 return TRUE;

}

uint64 lilly_io_strm_get_stream_size(const opaque_ptr stream_handle)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (!handle) return IO_ERROR;

	 handle->io_size = lilly_io_get_file_size_ex(handle->io_handle);

	 if ((int64)handle->io_size < 0)
	 {
	   handle->error_code = IO_ERROR;
	 }

     return handle->io_size;
}

uint32 lilly_io_strm_get_stream_cache_size(const opaque_ptr stream_handle)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (!handle) return (uint32)IO_ERROR;
	 else return handle->cache_size;
}

boolean lilly_io_strm_set_current_stream_offset(const opaque_ptr stream_handle,const uint64 stream_offset,const boolean write_mode)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (!handle) return FALSE;

	 handle->error_code = ERROR_SUCCESS;

	 handle->current_offset = stream_offset;

	 if ((write_mode) || (stream_offset >= (uint64)handle->cache_size))
	 {
	   handle->current_offset = lilly_io_file_seek(handle->io_handle,stream_offset,lilly_soFromBeginning);
	 }

	 if ((int64)handle->current_offset < 0)
	 {
	   handle->error_code = IO_ERROR;
	   return FALSE;
	 }

     return TRUE;
}

uint64 lilly_io_strm_get_current_stream_offset(const opaque_ptr stream_handle)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (!handle) return IO_ERROR;

	 return handle->current_offset;
}

puchar lilly_io_strm_get_stream_buffer(const opaque_ptr stream_handle,const uint64 stream_offset)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;
  puchar buffer;


	 if (stream_offset >= (uint64)handle->cache_size)
	 {
	   buffer = handle->io_buffer;
	 }
	 else buffer = handle->cache_mem + (unsigned_int)stream_offset;

	 return buffer;
}

void lilly_io_strm_clear_io_buffer(const opaque_ptr stream_handle)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (handle)
	 {
	   avcore_memset(handle->io_buffer,0,handle->io_buffer_size);
	 }

	 return;
}

puchar lilly_io_strm_read_stream(const opaque_ptr stream_handle,const uint64 stream_offset)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;
  puchar buffer;


	 handle->error_code = ERROR_SUCCESS;

	 if ((int64)stream_offset <= 0)
	 {
	   handle->error_code = API_ERROR;
	   return NULL;
	 }

	 buffer = lilly_io_strm_get_stream_buffer(handle,stream_offset);

	 if (stream_offset >= (uint64)handle->cache_size)
	 {
	   if (!lilly_io_strm_read_stream_ex(handle,buffer,handle->io_buffer_size,stream_offset)) return NULL;
	 }
	 else
	 {
	   handle->current_offset = stream_offset + handle->io_buffer_size;
       handle->last_io_size = handle->io_buffer_size;
	 }

	 return buffer;

}

boolean lilly_io_strm_write_stream(const opaque_ptr stream_handle,const puchar data,const uint64 stream_offset)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;
  puchar buffer;


	 if (!handle) return NULL;

	 handle->error_code = ERROR_SUCCESS;

	 if ((!data) || ((int64)stream_offset <= 0))
	 {
	   handle->error_code = API_ERROR;
	   return NULL;
	 }

     buffer = lilly_io_strm_get_stream_buffer(handle,stream_offset);

	 avcore_memcpy(buffer,data,handle->io_buffer_size);

	 return lilly_io_strm_write_stream_ex(handle,data/*handle->io_buffer*/,handle->io_buffer_size,stream_offset);
}

boolean lilly_io_strm_read_stream_ex(const opaque_ptr stream_handle,const puchar data,const unsigned_int data_size,const uint64 stream_offset)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (!handle) return FALSE;

	 if (!lilly_io_strm_set_current_stream_offset(handle,stream_offset,FALSE)) return FALSE;

	 if (!lilly_io_file_read(handle->io_handle,data,data_size))
	 {
	   handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 handle->current_offset = stream_offset + (uint64)data_size;
	 handle->last_io_size = data_size;

	 return TRUE;
}

boolean lilly_io_strm_write_stream_ex(const opaque_ptr stream_handle,const puchar data,const unsigned_int data_size,const uint64 stream_offset)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;


	 if (!handle) return FALSE;

	 handle->error_code = ERROR_SUCCESS;

	 if ((signed_int)handle->io_handle <= 0)
	 {
	   handle->error_code = API_ERROR;
	   return FALSE;
	 }

	 if (!lilly_io_strm_set_current_stream_offset(handle,stream_offset,TRUE)) return FALSE;

	 if (!lilly_io_file_write(handle->io_handle,data,data_size))
	 {
	   handle->error_code = IO_ERROR;
	   return FALSE;
	 }

	 handle->current_offset = stream_offset + (uint64)data_size;
     handle->last_io_size = data_size;

	 return TRUE;
}

unsigned_int lilly_io_strm_get_last_error(const opaque_ptr stream_handle)
{
  p_lilly_io_strm_handle handle = (p_lilly_io_strm_handle)stream_handle;

	 if (!handle) return FATAL_ERROR;
     else return handle->error_code;
}

