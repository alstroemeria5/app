//
//  apple_time.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/17.
//

#include "framework.h"
#include "acme/platform/static_setup.h"



//#include <mach/clock.h>
//#include <mach/mach.h>
#include <mach/mach_time.h>

//extern clock_serv_t g_cclock;

namespace acme
{
extern double g_machtime_conversion_factor;
} // namespace acme
void ns_Sleep(unsigned int uiMillis);


CLASS_DECL_ACME ::i64 _get_nanos()
{
   
   return mach_absolute_time() * ::acme::g_machtime_conversion_factor;
   
   //   mach_timespec_t mts;
   //
   //   clock_get_time(g_cclock, &mts);
   //
   //   return ((u64) mts.tv_sec * (u64)1000 * (u64)1000 * (u64)1000 )+ ((u64) mts.tv_nsec);
   
}