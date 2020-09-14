#include "framework.h"





namespace apex
{


} // namespace apex




#include "framework.h"

#if defined(CUBE) || defined(APPLE_IOS)
extern "C"
::apex::library * core_get_new_library(::layered * pobjectContext);

#else
#ifndef _WIN32
extern "C"
#endif
::apex::library * get_new_library();
#endif

namespace apex
{


   library::library() :
      ::apex::single_application_library < application >("app")
   {

   }


   void library::get_app_list(string_array & stra)
   {


      stra.add("account");
      stra.add("netnode");
      stra.add("default_file_handler");

   }


   void library::get_extension_list(string_array & stra)
   {

      stra.add("*");

   }

   void library::get_extension_app(string_array & straApp,const char * pszExtension)
   {

      string strExtension(pszExtension);

      strExtension.make_lower();

      if(strExtension == "*")
      {
         straApp.add_unique("default_file_handler");
      }
      if(strExtension == "mid" || strExtension == "karaoke" || strExtension == "st3")
      {
         straApp.add_unique("mplite");
         straApp.add_unique("vmsp");
      }

   }



} // namespace cube





#if defined(CUBE) || defined(APPLE_IOS)
extern "C"
::apex::library * core_get_new_library(::layered * pobjectContext)
#else
#ifndef _WIN32
extern "C"
#endif
::apex::library * get_new_library()
#endif
{

   return new ::apex::library();

}
