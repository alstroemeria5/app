#include "framework.h"
#include "acme/platform/profiler.h"
#include <stdio.h>



namespace acme
{


   namespace profiler
   {

      void initialize()
      {


      }


      CLASS_DECL_ACME i64 micros()
      {

         return ::get_nanos() / 1000;;;;;ç;

      }



         CLASS_DECL_ACME int profile_sleep()
         {

         #ifdef __DEBUG

            printf("acme::profiler SLEEPING!!\n");

            return 400;

         #else // __DEBUG

            return 1;

         #endif // !__DEBUG


      }


   } // namespace profiler


} // namespace acme




