﻿#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_windows.h"
#endif
#include "aura/message.h"


UINT g_puiaMessageTrace[] =
{
   e_message_move,
   e_message_size,
   e_message_activate,
   e_message_set_focus,
   e_message_kill_focus,
   (UINT)-1
};

CLASS_DECL_APEX string get_message_text(UINT uMessage, bool bWithNumbers);

bool __windows_message_bypass(HWND oswindow, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
{

   if (message == WM_NCCREATE)
   {

      output_debug_string("WM_NCCREATE");

      return false;

   }
   else if (message == e_message_create)
   {

      output_debug_string("e_message_create");

      return false;

   }
   else if (message == e_message_mouse_move)
   {

      output_debug_string("mm.");

      lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      return true;

   }
   else if (message == WM_SETCURSOR)
   {

      output_debug_string("sc.");

      lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      return true;

   }
   else if (message == WM_NCHITTEST)
   {

      output_debug_string("ht.");

      lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      return true;

   }

   return false;

}
extern UINT g_puiaMessageMouseMove[];
extern UINT g_puiaMessageWindowDeactivating[];
extern UINT g_puiaMessageWindowActivating[];
extern UINT f[];
extern UINT g_puiaMessageWindowCreated[];
extern UINT g_puiaMessageInputLanguageChange[];
extern UINT g_puiaMessageTrace[];

#define STATE_WINDOW_CREATION 0
#define STATE_WINDOW_CREATED 1
#define STATE_INPUT_LANGUAGE_CHANGING 2
#define STATE_WINDOW_DEACTIVATING 3
#define STATE_WINDOW_ACTIVATING 4

bool __windows_message_bypass(HWND oswindow, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult, UINT * puia)
{

   for (int i = 0; puia[i] != -1; i++)
   {

      if (message == puia[i])
      {

         //string str;

         //str.Format("\n%s", get_message_text(message, true).c_str());

         //output_debug_string(str);

         lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

         return true;

      }

   }

   return false;

}


namespace windows
{


   bool interaction_impl::__windows_message_bypass(HWND oswindow, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {

      //if (message == e_message_mouse_move)
      //{

      //   //output_debug_string("mm.");

      //   lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      //   return true;

      //}
      //else if (message == WM_SETCURSOR)
      //{

      //   //output_debug_string("sc.");

      //   lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      //   return true;

      //}
      //else if (message == WM_NCHITTEST)
      //{

      //   //output_debug_string("ht.");

      //   lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      //   return true;

      //}

#if 0

      if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageMouseMove))
      {

         return true;

      }


      if (pimpl->m_iState1 == STATE_WINDOW_CREATION)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageTopLevelCreation))
         {

            if (message == WM_PAINT)
            {

               pimpl->m_iState1 = STATE_WINDOW_CREATED;

            }

            return true;

         }


      }
      else if (pimpl->m_iState1 == STATE_WINDOW_CREATED)
      {

         if (message == WM_INPUTLANGCHANGE)
         {

            pimpl->m_iState1 = STATE_INPUT_LANGUAGE_CHANGING;

         }
         else if (message == WM_IME_NOTIFY)
         {

            pimpl->m_iState1 = STATE_INPUT_LANGUAGE_CHANGING;

         }
         else if (message == WM_NCACTIVATE && wparam == 0)
         {

            pimpl->m_iState1 = STATE_WINDOW_DEACTIVATING;

         }
         else
         {

            if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageWindowCreated))
            {

               return true;

            }

         }


      }

      if (pimpl->m_iState1 == STATE_INPUT_LANGUAGE_CHANGING)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageInputLanguageChange))
         {

            return true;

         }
         else if (message == WM_NCACTIVATE && wparam == 0)
         {

            pimpl->m_iState1 = STATE_WINDOW_DEACTIVATING;

         }

      }

      if (pimpl->m_iState1 == STATE_WINDOW_DEACTIVATING)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageWindowDeactivating))
         {

            return true;

         }

         if (message == WM_WINDOWPOSCHANGING)
         {

            pimpl->m_iState1 = STATE_WINDOW_ACTIVATING;

         }


      }

      if (pimpl->m_iState1 == STATE_WINDOW_ACTIVATING)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageWindowActivating))
         {

            if (message == e_message_set_focus)
            {

               pimpl->m_iState1 = STATE_WINDOW_CREATED;

            }

            return true;

         }


      }

#endif

      bool bTrace = false;

      for (int i = 0; g_puiaMessageTrace[i] != -1; i++)
      {

         if (message == g_puiaMessageTrace[i])
         {

            bTrace = true;

            break;

         }

      }

      string str;

      str.Format("%s", get_message_text(message, true).c_str(), wparam, lparam);

      if (message == e_message_activate)
      {

         if (LOWORD(wparam) == WA_ACTIVE)
         {

            str += " WA_ACTIVE";

         }
         else if (LOWORD(wparam) == WA_CLICKACTIVE)
         {

            str += " WA_CLICKACTIVE";

         }
         else if (LOWORD(wparam) == WA_INACTIVE)
         {

            str += " WA_INACTIVE";

         }

         if (HIWORD(wparam))
         {

            str += " minimized_state_active";

         }

      }

      if (bTrace)
      {

         INFO("\n" + str);

      }

      return false;

   }


} // namespace windows



