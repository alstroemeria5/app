// Extracted from device_lock, Changed and Organized by camilo on 2021-09-04 05:46 BRT <3ThomasBS__!!
#pragma once

//#error
//
//#ifdef _UWP
//
//#include "acme/node/operating_system/windows_common/comptr.h"
//#include <d2d1_1.h>
//
//#endif
//


namespace draw2d
{
//
//
//   class CLASS_DECL_AURA device_lock
//   {
//   public:
//
////#ifdef _UWP
////
////      comptr < ID2D1Multithread > m_D2DMultithread;
////
////#endif
//
//      class ::system * m_psystem;
//
//      device_lock(::user::interaction * pinteraction);
//      ~device_lock();
//
//
//   };


   class CLASS_DECL_AURA lock :
      public synchronous_lock
   {
   public:

      static ::mutex * g_pmutex;

      lock() :
         synchronous_lock(g_pmutex)
      {

      }

      virtual ~lock()
      {

      }

   };


} // namespace draw2d

