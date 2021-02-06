#include "framework.h"
//#include "uwp.h"
//#include <process.h>    // for _beginthreadex and _endthreadex
//#include <ddeml.h>  // for MSGF_DDEMGR

namespace uwp
{
   class thread;
} // namespace uwp

bool CLASS_DECL_ACME __internal_pump_message();
LRESULT CLASS_DECL_ACME __internal_process_wnd_proc_exception(::exception::exception*, const MSG* pMsg);
bool __internal_pre_translate_message(MSG* pMsg);
bool __internal_is_idle_message(MSG* pMsg);
//__STATIC void CLASS_DECL_ACME __pre_init_dialog(__pointer(::user::interaction) pWnd, RECTANGLE_I32 * lpRectOld, u32* pdwStyleOld);
//__STATIC void CLASS_DECL_ACME __post_init_dialog(__pointer(::user::interaction) pWnd, const RECT32& rectOld, u32 dwStyleOld);


//__declspec(thread) HHOOK t_hHookOldMsgFilter = nullptr;
//
//
//LRESULT CALLBACK __message_filter_hook(i32 code,WPARAM wParam,LPARAM lParam);


void CLASS_DECL_ACME __init_thread()
{

   //if(t_hHookOldMsgFilter == nullptr)
   //{

   //   t_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,__message_filter_hook,nullptr,::GetCurrentThreadId());

   //}

}


void CLASS_DECL_ACME __term_thread()
{


}


bool __node_init_thread(::thread * pthread)
{

   try
   {

      pthread->::exception::translator::attach();

   }
   catch(...)
   {

      return false;

   }

   return true;

}



bool __node_term_thread(::thread * pthread)
{

   bool bOk1 = false;

   try
   {

      if(pthread != nullptr)
      {

         pthread->::exception::translator::detach();

      }

      bOk1 = true;

   }
   catch(...)
   {

   }

   return bOk1;

}
