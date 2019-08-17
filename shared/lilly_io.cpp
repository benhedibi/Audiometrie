#include <lilly_io.h>
#include <System.IOUtils.hpp>
#include <system.hpp>


unsigned_int lilly_io_open_file(const puchar path,const t_lilly_io_file_modes file_mode,const t_lilly_io_file_acess file_access)
{
  UnicodeString us((PWCHAR)path);
  TFileStream *fs = NULL;
  TFileMode fmode;
  TFileAccess faccess;

	switch (file_mode)
	{
		 case lilly_io_fmCreateNew : fmode = TFileMode::fmCreateNew;
									 break;

			case lilly_io_fmCreate : fmode = TFileMode::fmCreate;
									 break;

			  case lilly_io_fmOpen : fmode = TFileMode::fmOpen;
									 break;

	  case lilly_io_fmOpenOrCreate : fmode = TFileMode::fmOpenOrCreate;
									 break;

		  case lilly_io_fmTruncate : fmode = TFileMode::fmTruncate;
									 break;

			case lilly_io_fmAppend : fmode = TFileMode::fmAppend;
									 break;

                           default : return NULL;
	}

	switch (file_access)
	{
		   case lilly_io_faRead : faccess = TFileAccess::faRead;
								  break;

		  case lilly_io_faWrite : faccess = TFileAccess::faWrite;
								  break;

	  case lilly_io_faReadWrite : faccess = TFileAccess::faReadWrite;
								  break;

						default : return NULL;

	}
	 //*/

	// fs = TFile::Create(us);
	 // fs = TFile::Open(us,TFileMode::fmOpen);
	 //fmode = (TFileMode)fmCreate;
  try
	{
	  fs = TFile::Open(us,fmode,faccess);
	}

  __finally
	{
	  us.~UnicodeString();
	}

	return (unsigned_int)fs;

}

unsigned_int lilly_io_create_file(const puchar path)
{
  UnicodeString us((PWCHAR)path);
  TFileStream *fs = NULL;

	try
	{
	  try
	  {
		fs = TFile::Create(us);
	  }

	  __except(EXCEPTION_EXECUTE_HANDLER)
	  {
		fs = NULL;
	  }
	}

  __finally
	{
	  us.~UnicodeString();
	}

	return (unsigned_int)fs;
}

void lilly_io_close_file(const unsigned_int file_handle)
{
  TFileStream *fs = (TFileStream *)file_handle;


	if (fs)
	{
      //fs->Free();
	  delete(fs);
	  //fs->~TFileStream();
	}

    return;
}

boolean lilly_io_file_read(const unsigned_int file_handle,const puchar buffer,const unsigned_int buffer_size)
{
  TFileStream *fs = (TFileStream *)file_handle;


	return (fs->Read(buffer,buffer_size) == buffer_size);
}

boolean lilly_io_file_write(const unsigned_int file_handle,const puchar buffer,const unsigned_int buffer_size)
{
  TFileStream *fs = (TFileStream *)file_handle;


    return (fs->Write(buffer,buffer_size) == buffer_size);
}

uint64 lilly_io_file_seek(const unsigned_int file_handle,const uint64 offset,const t_lilly_seek_modes seek_mode)
{
  TFileStream *fs = (TFileStream *)file_handle;

	return fs->Seek(offset,(TSeekOrigin)seek_mode);
}

boolean lilly_io_delete_file(const puchar path)
{
  UnicodeString us((PWCHAR)path);
  boolean result = FALSE;

  try
	{
	  TFile::Delete(us);

	  result = (lilly_io_file_exists(path) == FALSE);
	}

 __finally
   {
	 us.~UnicodeString();
   }

   return result;
}

boolean lilly_io_file_exists(const puchar path)
{
  UnicodeString us((PWCHAR)path);
  boolean result = FALSE;

  try
	{
	  result = (boolean)TFile::Exists(us,false);
	}

  __finally
	{
	  us.~UnicodeString();
	}

	return result;
}

boolean lilly_io_file_copy(const puchar source_path,const puchar destination_path,const boolean fail_if_exist)
{
  UnicodeString us_src((pchar)source_path);
  UnicodeString us_dest((pchar)destination_path);
  boolean result = FALSE;


	try
	{
	  TFile::Copy(us_src,us_dest,(fail_if_exist == false));
	  result = (boolean)TFile::Exists(us_dest,false);
    }

  __finally
	{
	  us_src.~UnicodeString();
      us_dest.~UnicodeString();
	}

	return result;

}

uint64 lilly_io_get_file_size(const puchar path)
{
  uint64 size;
  unsigned_int file_handle;

	file_handle = lilly_io_open_file(path,lilly_io_fmOpen,lilly_io_faRead);

	if ((signed_int)file_handle <= 0) return IO_ERROR;

	TFileStream *fs = (TFileStream *)file_handle;

	size = fs->Size;

	lilly_io_close_file(file_handle);

	return size;

}

uint64 lilly_io_get_file_size_ex(const unsigned_int file_handle)
{

	if ((signed_int)file_handle <= 0) return IO_ERROR;

	TFileStream *fs = (TFileStream *)file_handle;

    return fs->Size;

}
