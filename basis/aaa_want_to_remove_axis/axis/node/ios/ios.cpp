#include "framework.h"


namespace ios
{

   i32 function()
   {
      return 0;
   }


   DWORD GetTempPath(string & str)
   {
      //return ::GetTempPathW(MAX_PATH * 8,wtostring(str,MAX_PATH * 8));
      
      str = "/var/tmp/ca2/";
      
      return str.get_length();
      
   }


} // namespace ios


