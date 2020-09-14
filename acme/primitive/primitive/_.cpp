#include "framework.h"


extern ::mutex * g_pmutexChildren;

void _debug_debug_string_string()
{

   ::id id("a-ha");

   auto bEndsInHa1 = ::str::ends(id, "ha");
   auto bEndsInHa2 = ::str::ends_ci(id, "Ha");


}

void __assert_valid_object(const ::generic * pOb, const char * pszFileName, i32 nLine)

{

   if (pOb == nullptr)
   {

      if (__assert_failed_line(pszFileName, nLine))

      {

         debug_break();

      }

      return;     // quick escape

   }

   if (!__is_valid_address(pOb, sizeof(generic)))
   {

      ///TRACE(trace_category_appmsg, 0, "ASSERT_VALID fails with illegal pointer.\n");

      if (__assert_failed_line(pszFileName, nLine))

      {

         debug_break();

      }

      return;     // quick escape

   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::generic) == sizeof(void *));
   //   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   {

      //      TRACE(trace_category_appmsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");

      if (__assert_failed_line(pszFileName, nLine))

      {

         debug_break();

      }

      return;     // quick escape

   }

   /*if (!__is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, FALSE))
   {
   TRACE(trace_category_appmsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (__assert_failed_line(pszFileName, nLine))

   debug_break();
   return;     // quick escape
   }*/

   pOb->assert_valid();

}



//CLASS_DECL_ACME void call(::generic * pobjectTask)
//{
//
//   pobjectTask->call();
//
//}
//



CLASS_DECL_ACME void call(__pointer(::generic) pobjectRunnable)
{

   pobjectRunnable->call();

}

