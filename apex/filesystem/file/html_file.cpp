#include "framework.h"
#include "html_file.h"


namespace html
{


   file::file()
   {
      
   }


   file::~file()
   {

   }


   const ::text::context * file::textcontext()
   {
      
      return m_ptextcontext;

   }


   void file::print(const ::string & str)
   {

      raw_print(str);

   }


   void file::raw_print(const ::string & str)
   {

      print(str);

   }


#ifndef VARIADIC_TEMPLATE_FORMAT


   void file::printf(string str,...)
   {

      __UNREFERENCED_PARAMETER(str);

      ::exception::throw_interface_only();

   }


   void file::printstr(string str,...)
   {

      __UNREFERENCED_PARAMETER(str);

      ::exception::throw_interface_only();

   }


#else


   void file::trace(void *,const char * psz)
   {

      print(psz);

   }


#endif


   void file::dprint(const char * pcsz)
   {

      __UNREFERENCED_PARAMETER(pcsz);

      ::exception::throw_interface_only();

   }


} // namespace html



