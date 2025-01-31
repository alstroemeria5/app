// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/acme_file.cpp
// 04:38 BRT <3ThomasBorregaardS�rensen
#include "framework.h"
#include "acme/operating_system.h"
#include "acme_dir.h"
#include "acme_file.h"
#include <stdio.h>


void trace_last_error()
{

   output_debug_string("trace_last_error::todo");

}
acme_file::acme_file()
{

}


acme_file::~acme_file()
{

}


::file::path acme_file::executable()
{

   if (m_pathExecutable.is_empty())
   {

      auto pnode = m_psystem->node();

      auto pathModule = pnode->module_path_source();

      m_pathExecutable = pathModule;

   }

   return m_pathExecutable;

}



file_transport acme_file::open(const ::file::path & path, const ::file::e_open & eopen)
{

   auto pfile = m_psystem->__create_new < ::file::file >();

   if(!pfile)
   {

      return pfile;

   }

   auto estatus = pfile->open(path, eopen);

   if(!estatus)
   {

      return estatus;

   }

   return pfile;

}


file_transport acme_file::stdio_open(const char * path, const char * attrs, int iShare)
{

   auto pfile = __create_new < ::stdio_file >();

   if (!pfile)
   {

      return pfile;

   }

   auto estatus = pfile->open(path, attrs, iShare);

   if (!estatus)
   {

      return estatus;

   }

   return pfile;

}


memory acme_file::as_memory(const char * path, strsize iReadAtMostByteCount)
{

   __throw(error_interface_only);

   return ::memory();

}


string acme_file::as_string(const char * path, strsize iReadAtMostByteCount)
{

   string str;

   wstring wstr(path);

   auto pfile = m_psystem->__create_new < stdio_file >();

   auto estatus = pfile->open(path, "r", _SH_DENYNO);

   if(!estatus)
   {

      return "";

   }

   auto uSize = pfile->get_size();
   
   if(iReadAtMostByteCount < 0)
   {
      
      iReadAtMostByteCount = (strsize) uSize;
      
   }
   else
   {
      
      iReadAtMostByteCount = minimum(iReadAtMostByteCount, (strsize)uSize);
      
   }

   char * psz = str.get_string_buffer(iReadAtMostByteCount);

   ::size_t iPos = 0;

   while (iReadAtMostByteCount - iPos > 0)
   {

      auto dwRead = pfile->read(psz + iPos, (size_t)iReadAtMostByteCount - iPos);

      if (dwRead <= 0)
      {

         break;

      }

      iPos += dwRead;

   }

   psz[iPos] = '\0';

   str.release_string_buffer(iReadAtMostByteCount);

   return str;

}


memsize acme_file::as_memory(const char * path, void * p, memsize s)
{

   stdio_file file;

   auto estatus = file.open(path, "r", _SH_DENYNO);

   if(!estatus)
   {

      return 0;

   }

   auto iReadAtMostByteCount = s;

   byte * psz = (byte *) p;

   ::size_t iPos = 0;

   while (iReadAtMostByteCount - iPos > 0)
   {

      auto dwRead = file.read(psz + iPos, (size_t)iReadAtMostByteCount - iPos);

      if (dwRead <= 0)
      {

         break;

      }

      iPos += dwRead;

   }

   return iPos;

}


::e_status acme_file::as_memory(memory_base & memory, const char * path, memsize iReadAtMostByteCount)
{

   memory.set_size(0);

   stdio_file file;

   auto estatus = file.open(path, "r", _SH_DENYNO);

   if (!estatus)
   {

      return estatus;

   }

   auto iSize = file.get_size();

   if (iSize < 0)
   {

      memory.set_size(0);

      return success;

   }

   iReadAtMostByteCount = minimum_non_negative(iReadAtMostByteCount, (::strsize)iSize);

   memory.set_size(iReadAtMostByteCount);

   filesize dwReadTotal = 0;

   while (dwReadTotal < iReadAtMostByteCount)
   {

      auto dwRead = file.read(memory.get_data() + dwReadTotal, (memsize)(iReadAtMostByteCount - dwReadTotal));

      if (dwRead <= 0)
      {

         break;

      }

      dwReadTotal += dwRead;

   }

   memory.set_size((memsize) dwReadTotal);

   return ::success;

}


string acme_file::get_temporary_file_name(const char * lpszName, const char * pszExtension)
{

#ifdef WINDOWS

   WCHAR pPathBuffer[MAX_PATH * 16];

   ::u32 dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);

   if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
   {

      debug_print("GetTempPath failed (%d)\n", ::GetLastError());

      return "";

   }

#else

   char pPathBuffer[MAX_PATH * 16];

   strcpy(pPathBuffer, "/tmp/");

#endif

   ::file::path pathFolder(pPathBuffer);

   for (int i = 0; i < 1000; i++)
   {

      ::file::path path;

      path = pathFolder;

      path /= lpszName;

      path /= __str(i);

      path /= (string(lpszName) + "." + string(pszExtension));

      if (this->exists(path))
      {

         if (this->delete_file(path))
         {

            return ::move(path);

         }

      }
      else
      {

         return ::move(path);

      }

   }

   return "";

}


::e_status acme_file::write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
{

#if OSBIT > 32

   memsize pos = 0;

   ::u32 dw = 0;

   ::u32 dwWrite;

   memsize uiWrittenTotal = 0;

   while (pos < nCount)
   {

      dwWrite = (::u32)minimum(nCount - uiWrittenTotal, 0xffffffffu);

      dw = (::u32)(fwrite(&((u8 *)pdata)[pos], 1, dwWrite, file));


      if (dw != dwWrite)
      {

         uiWrittenTotal += dw;

         if (puiWritten != nullptr)
         {

            *puiWritten = uiWrittenTotal;

         }

         return false;

      }

      uiWrittenTotal += dw;

      if (dw != dwWrite)
      {

         break;

      }

      pos += dw;

   }

   if (puiWritten != nullptr)
   {

      *puiWritten = uiWrittenTotal;

   }

   if (uiWrittenTotal != nCount)
   {

      return error_failed;

   }

   return ::success;

#else

   ::u32 dw = 0;

   dw = ::fwrite(pdata, 1, (size_t)nCount, file);

   int_bool bOk = dw == nCount;

   if (puiWritten != nullptr)
   {

      *puiWritten = dw;

   }

   if (!bOk)
   {

      return error_failed;

   }

   return success;

#endif

}


::e_status acme_file::append_wait(const char * strFile, const block & block, const ::duration & duration)
{

   auto pacmedir = m_pacmedir;

   auto estatus = pacmedir->create(::file_path_folder(strFile));

   if (!estatus)
   {

      return estatus;

   }

   if (!pacmedir->is(::file_path_folder(strFile)))
   {

      return error_path_not_found;

   }

   wstring wstr(strFile);

   FILE * pfile = nullptr;

   auto millisStart = ::millis::now();

   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
      
      pfile = fopen(strFile, "ab");

#else

      pfile = _wfopen(wstr, L"ab");

#endif

      if (pfile != nullptr)
      {

         break;

      }

      if (millisStart.elapsed() > duration)
      {

         return false;

      }

      preempt(500_ms);

   }

   fwrite(block.get_data(), block.get_size(), 1, pfile);

   fclose(pfile);

   return success;

}


::e_status acme_file::append(const char * strFile, const block & block)
{

   return acme_file::append_wait(strFile, block, 0);

}


bool acme_file::exists(const char * path)
{

   __throw(error_interface_only);

   return false;

}


::e_status acme_file::put_contents(const char * path, const char * contents, strsize len)
{

   __throw(error_interface_only);

   return error_interface_only;

}


::e_status acme_file::get_temporary_file_name_template(char * szRet, strsize iBufferSize, const char * lpszName, const char * pszExtension, const char * pszTemplate)
{

   __throw(error_interface_only);

   return error_interface_only;

}


filesize acme_file::get_size(const char * path)
{

   __throw(error_interface_only);

   return -1;

}


filesize acme_file::get_size(FILE * pfile)
{

   return get_size_fd(fileno(pfile));

}


filesize acme_file::get_size_fd(int iFile)
{

   __throw(error_interface_only);

   return -1;

}


bool acme_file::is_true(const char * path)
{

   __throw(error_interface_only);

   return false;

}


::e_status acme_file::set_size(const char * lpszName, filesize size)
{

   __throw(error_interface_only);

   return success;

}


::e_status acme_file::set_size(int iFileDescriptor, filesize size)
{

   __throw(error_interface_only);

   return false;

}


::e_status acme_file::set_size(FILE * pfile, filesize size)
{

   __throw(error_interface_only);

   return false;

}


::e_status acme_file::move(const char * pszNewName, const char * pszOldName)
{

   auto bOk = copy(pszNewName, pszOldName, true);

   if(!bOk)
   {

      return false;

   }

   bool bOkDelete = delete_file(pszOldName);

   if(!bOk)
   {

      output_debug_string("failed to delete file \"" + string(pszOldName) + "\"");

   }

   return bOk;

}


::e_status acme_file::delete_file(const char * pszFileName)
{

   __throw(error_interface_only);

   return false;

}


void replace_char(char * sz, char ch1, char ch2)
{

   while (*sz)
   {

      if (*sz == ch1)
      {

         *sz = ch2;

      }

      sz++;

   }

}


::e_status acme_file::copy(const char * pszDup, const char * pszSrc, bool bOverwrite)
{

   __throw(error_interface_only);

   return error_interface_only;

}


::e_status acme_file::save_stra(const char * lpszName, const string_array & stra)
{

   __throw(error_interface_only);

   return ::success;

}


::e_status acme_file::load_stra(const char * lpszName, string_array & stra, bool bAddEmpty)
{

   __throw(error_interface_only);

   return ::success;

}


::e_status acme_file::put_contents(const char * path, const memory_base & memory)
{

   __throw(error_interface_only);

   return false;

}


::e_status acme_file::put_contents(const char * path, const char * contents)
{

   auto estatus = put_contents(path, contents, ::str::string_safe_length(contents));

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status acme_file::put_block(const char * path, const block & block)
{

   return put_contents(path, (const char *) block.get_data(), block.get_size());

}



::e_status acme_file::as_block(block & block, const char * path)
{

   return as_memory(path, block.get_data(), block.get_size()) == block.get_size();

}


string acme_file::first_line(const char * path)
{

   return line(path, 0);

}


string acme_file::line(const char * path, index iLine)
{

   string str;

#ifdef WINDOWS

   FILE * file = _fsopen(path, "r", _SH_DENYNO);

#else

   FILE * file = fopen(path, "r");

#endif

   if (file == nullptr)
   {

      trace_last_error();

      return "";

   }

   int iChar;

   string strLine;

   int iLastChar = -1;

   while (iLine >= 0)
   {

      iChar = fgetc(file);

      if (iChar == EOF)
      {

         break;

      }

      if (iChar == '\r')
      {

         iLine--;

      }
      else if (iChar == '\n')
      {

         if (iLastChar != '\r')
         {

            iLine--;

         }

      }
      else if (iLine == 0)
      {

         str += (char)iChar;

      }

      iLastChar = iChar;

   }

   return str;

}


string_array acme_file::lines(const char * path)
{

   string_array straLines;

   auto pfile = open(path, ::file::e_open_read);

   if (!pfile)
   {

      return straLines;

   }

   string strLine;

   while (pfile->read_string(strLine))
   {

      straLines.add(strLine);

   }

   return straLines;

}


::e_status acme_file::set_line(const char * pszPath, index iLine, const char * pszLine)
{

   if (iLine < 0)
   {

      return error_index_out_of_bounds;

   }

   string str;

   ::file::path path(pszPath);

   auto estatus = m_pacmedir->create(path.folder());

   if (!estatus)
   {

      return estatus;

   }

   auto pfile = open(path, ::file::e_open_read_write | ::file::e_open_create | ::file::e_open_no_truncate);

   if (!pfile)
   {

      trace_last_error();

      return pfile;

   }

   int iChar;

   string strLine;

   int iLastChar = -1;

   filesize iPosStart = -1;

   filesize iPosEnd = -1;

   while (iLine >= 0)
   {

      iChar = pfile->getc();

      if (iChar == EOF)
      {

         break;

      }

      if (iChar == '\r')
      {

         iLine--;

      }
      else if (iChar == '\n')
      {

         if (iLastChar != '\r')
         {

            iLine--;

         }

      }
      else if (iLine == 0)
      {

         if (iPosStart <= 0)
         {

            iPosStart = pfile->get_position();

         }

      }

      iLastChar = iChar;

   }

   if (iLine > 0)
   {

      while(iLine > 0)
      {

         pfile->put('\n');

         iLine--;

      }

      pfile->write(pszLine);

   }
   else
   {

      iPosEnd = pfile->get_position();

      ::file::path pathTime = path;

      pathTime += ".time";

      {

         auto pfile2 =
            open(
               pathTime, 
               ::file::e_open_write 
               | ::file::e_open_share_exclusive 
               | ::file::e_open_defer_create_directory
               | ::file::e_open_create);

         if (!pfile2)
         {

            return pfile2;

         }

         if (iPosStart > 0)
         {

            memory m;

            pfile->seek_to_begin();

            m.set_size((memsize)iPosStart);

            pfile->read(m.get_data(), (memsize)iPosStart);

            pfile2->write(m.get_data(), (memsize)iPosStart);

         }

         pfile2->write(pszLine);

         auto iEnd = pfile->get_size();

         if (iEnd - iPosEnd > 0)
         {

            memory m;

            pfile->set_position(iPosEnd);

            m.set_size((memsize)(iEnd - iPosEnd));

            pfile->read(m.get_data(), m.get_size());

            pfile2->write(m.get_data(), m.get_size());

         }

      }

      if (!copy(path, pathTime.c_str(), true))
      {

         return error_failed;

      }

      delete_file(pathTime);

   }

   return true;

}


//string acme_file::get_temporary_file_name(const char * lpszName, const char * pszExtension)
//{
//
//#ifdef WINDOWS
//
//   WCHAR pPathBuffer[MAX_PATH * 16];
//
//   ::u32 dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);
//
//   if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
//   {
//
//      debug_print("GetTempPath failed (%d)\n", ::GetLastError());
//
//      return "";
//
//   }
//
//#else
//
//   char pPathBuffer[MAX_PATH * 16];
//
//   strcpy(pPathBuffer, "/tmp/");
//
//#endif
//
//   ::file::path pathFolder(pPathBuffer);
//
//   for (int i = 0; i < 1000; i++)
//   {
//
//      ::file::path path;
//
//      path = pathFolder;
//
//      path /= lpszName;
//
//      path /= __str(i);
//
//      path /= (string(lpszName) + "." + string(pszExtension));
//
//      if (exists(path))
//      {
//
//         if (delete_file(path))
//         {
//
//            return ::move(path);
//
//         }
//
//      }
//      else
//      {
//
//         return ::move(path);
//
//      }
//
//   }
//
//   return "";
//
//}


::e_status acme_file::write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
{

#if OSBIT > 32

   memsize pos = 0;

   ::u32 dw = 0;

   ::u32 dwWrite;

   memsize uiWrittenTotal = 0;

   while (pos < nCount)
   {

      dwWrite = (::u32)minimum(nCount - uiWrittenTotal, 0xffffffffu);

      dw = (::u32)(fwrite(&((u8 *)pdata)[pos], 1, dwWrite, file));

      if (dw != dwWrite)
      {

         uiWrittenTotal += dw;

         if (puiWritten != nullptr)
         {

            *puiWritten = uiWrittenTotal;

         }

         return false;

      }

      uiWrittenTotal += dw;

      if (dw != dwWrite)
      {

         break;

      }

      pos += dw;

   }

   if (puiWritten != nullptr)
   {

      *puiWritten = uiWrittenTotal;

   }

   return uiWrittenTotal == nCount;

#else

   ::u32 dw = 0;

   dw = ::fwrite(pdata, 1, (size_t)nCount, file);

   int_bool bOk = dw == nCount;

   if (puiWritten != nullptr)
   {

      *puiWritten = dw;

   }

   return bOk;

#endif

}


::e_status acme_file::append(const ::string & strFile, const block & block)
{

   return append_wait(strFile, block, 0);

}


::e_status acme_file::append_wait(const ::string & strFile, const block & block, const ::duration & duration)
{

   m_pacmedir->create(::file_path_folder(strFile));

   if (!m_pacmedir->is(::file_path_folder(strFile)))
   {

      return false;

   }

   wstring wstr(strFile);

   FILE * pfile = nullptr;

   auto millisStart = ::millis::now();

   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
      
      pfile = fopen(strFile, "ab");

#else
      
      pfile = _wfopen(wstr, L"ab");

#endif

      if (pfile != nullptr)
      {

         break;

      }

      if (millisStart.elapsed() > duration)
      {

         return false;

      }

      preempt(500_ms);

   }

   fwrite(block.get_data(), block.get_size(), 1, pfile);

   fclose(pfile);

   return ::success;

}



