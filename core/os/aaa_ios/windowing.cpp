//
//  ios_windowing.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#include "framework.h"
#include "oswindow_data.h"


mutex * g_pmutexOsWindowData = nullptr;

//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   if(psystemwindow == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return psystemwindow->m_puserinteraction;
//
//}


oswindow get_window(oswindow window, int iParentHood)
{

   return nullptr;

}


#include "framework.h"
#include "window_impl.h"


oswindow_dataptra * g_poswindowdataptra = nullptr;


int oswindow_find(UIWindow * window)
{

   for(int i = 0; i < g_poswindowdataptra->get_count(); i++)
   {
      if(g_poswindowdataptra->element_at(i)->m_nswindow == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow_get(UIWindow * window)
{

   iptr iFind = oswindow_find(window);

   if(iFind >= 0)
      return g_poswindowdataptra->element_at(iFind);

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_nswindow    = window;

   g_poswindowdataptra->add(pdata);

   return pdata;

}


CLASS_DECL_CORE ::user::interaction_impl * oswindow_get(oswindow oswindow)
{

   if(oswindow == nullptr)
   {

      return nullptr;

   }

   return oswindow->m_pimpl;

}

//oswindow_data::oswindow_data()
//{
//
//   m_nswindow  = nullptr;
//   m_pimpl       = nullptr;
//   m_plongmap  = new int_to_int;
//
//}
//
//
//oswindow_data::oswindow_data(UIWindow * window)
//{
//
//   m_nswindow  = window;
//   m_pimpl       = nullptr;
//   m_plongmap  = new int_to_int;
//
//}
//
//
//oswindow_data::oswindow_data(const oswindow_data & oswindow)
//{
//
//   m_nswindow  = oswindow.m_nswindow;
//   m_pimpl       = oswindow.m_pimpl;
//   m_plongmap  = oswindow.m_plongmap;
//
//}
//
//
//oswindow_data::~oswindow_data()
//{
//
//   delete m_plongmap;
//
//}
//
//
//oswindow_data & oswindow_data::operator = (const oswindow_data & oswindow)
//{
//
//   if(&oswindow != this)
//   {
//
//      m_nswindow  = oswindow.m_nswindow;
//      m_pimpl       = oswindow.m_pimpl;
//      m_plongmap  = oswindow.m_plongmap;
//
//   }
//
//   return *this;
//
//}


bool oswindow_remove(UIWindow * window)
{

   iptr iFind = oswindow_find(window);

   if(iFind < 0)
      return false;

   g_poswindowdataptra->remove_at(iFind);

   return true;

}


//void oswindow_data::set_user_interaction(::user::interaction_impl * pinteraction)
//{
//
//   if(::is_null(*this))
//      __throw(::exception::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));
//
//   m_pimpl = pinteraction;
//
//}
//
//
//::user::interaction_impl * oswindow_data::get_user_interaction_base()
//{
//
//   if(::is_null(*this))
//      return nullptr;
//
//   return m_pimpl;
//
//}
//
//::user::interaction_impl * oswindow_data::get_user_interaction_base() const
//{
//
//   if(::is_null(*this))
//      return nullptr;
//
//   return m_pimpl;
//
//}
//
//::user::interaction_impl * oswindow_data::get_user_interaction()
//{
//
//   if(::is_null(*this))
//      return nullptr;
//
//   if(m_pimpl == nullptr)
//      return nullptr;
//
//   return m_pimpl;
//
//}
//
//::user::interaction_impl * oswindow_data::get_user_interaction() const
//{
//
//   if(::is_null(*this))
//      return nullptr;
//
//   if(m_pimpl == nullptr)
//      return nullptr;
//
//   return m_pimpl;
//
//}
//
//
//oswindow oswindow_data::get_parent()
//{
//
//   if(::is_null(this))
//      return nullptr;
//
//   if(m_pimpl->GetParent() == nullptr)
//      return nullptr;
//
//   return m_pimpl->GetParent()->get_handle();
//
//}
//
//
//oswindow oswindow_data::set_parent(oswindow oswindow)
//{
//
//   if(::is_null(this))
//      return nullptr;
//
//   ::oswindow oswindowOldParent = get_parent();
//
//   //   if(oswindow == nullptr
//   //      || oswindow->m_pimpl == nullptr)
//   //   {
//   //
//   //      m_pimpl->set_parent_base(nullptr);
//   //
//   //   }
//   //   else
//   //   {
//   //
//   //      m_pimpl->set_parent_base(oswindow->m_pimpl);
//   //
//   //   }
//
//   return oswindowOldParent;
//
//}
//
//
//i32 oswindow_data::get_window_long(i32 iIndex)
//{
//
//   if(::is_null(*this))
//      return 0;
//
//   if(m_plongmap == nullptr)
//      return 0;
//
//   return m_plongmap->operator[](iIndex);
//
//}
//
//
//i32 oswindow_data::set_window_long(i32 iIndex, i32 iNewLong)
//{
//
//   if(::is_null(*this))
//      return 0;
//
//   if(m_plongmap == nullptr)
//      return 0;
//
//   i32 iLong = m_plongmap->operator[](iIndex);
//
//   m_plongmap->operator[](iIndex) = iNewLong;
//
//   return iLong;
//
//}


::user::interaction_impl * window_from_handle(oswindow oswindow)
{

   if(oswindow == nullptr)
      return nullptr;

   return oswindow->m_pimpl;

}

static oswindow g_oswindowCapture;


oswindow get_capture()
{

   return g_oswindowCapture;

}


oswindow set_capture(oswindow window)
{

   oswindow windowOld(g_oswindowCapture);

   g_oswindowCapture = window;

   return windowOld;

}


WINBOOL release_capture()
{

   g_oswindowCapture = nullptr;

   return TRUE;

}


oswindow get_focus();

oswindow g_oswindowFocus = nullptr;

oswindow set_focus(oswindow window)
{

   oswindow windowOld = ::get_focus();

   try
   {

      if(windowOld != nullptr)
      {

         if(windowOld->m_pimpl->m_bFocus)
         {
            
            windowOld->m_pimpl->m_puserinteraction->send_message(WM_KILLFOCUS);

         }

      }

   }
   catch(...)
   {
   }

   g_oswindowFocus = window;

   try
   {

      if(window != nullptr)
      {

         if(!window->m_pimpl->m_puserinteraction->m_bFocus)
         {

            window->m_pimpl->m_puserinteraction->send_message(WM_SETFOCUS);

         }

      }

   }
   catch(...)
   {
   }


   return windowOld;

}


oswindow get_focus()
{

   return g_oswindowFocus;

}




static oswindow g_oswindowActive = nullptr;


oswindow get_active_window()
{

   return g_oswindowActive;

}


void deactivate_window(oswindow window)
{

   sync_lock sl(g_poswindowdataptra->mutex());

   if(window == g_oswindowActive)
   {
   
      set_active_window(nullptr);
      
   }

}


oswindow set_active_window(oswindow window)
{

   oswindow windowOld(g_oswindowActive);

   if(window->window() == nullptr)
      return nullptr;

   g_oswindowActive = window;

   return windowOld;

}





WINBOOL ui_SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
   
   main_async([=]()
              {
   
   if(hwnd == nullptr)
      return FALSE;
   if(hwnd->m_pimpl == nullptr)
      return FALSE;
      return  hwnd->m_pimpl->m_puserinteraction->set_window_pos((iptr)hwndInsertAfter, x, y, cx, cy, uFlags) ? TRUE : FALSE;
      
   });
   
   return TRUE;

}



WINBOOL get_window_rect(oswindow hwnd, LPRECT lprect)
{

   if(void_ptr_is_null(hwnd))
      return FALSE;

   if(void_ptr_is_null(lprect))
      return FALSE;

   hwnd->m_pimpl->m_puserinteraction->get_window_rect(lprect);

   return TRUE;

}


WINBOOL SetWindowRect(oswindow hwnd, LPRECT lprect)
{

   if(hwnd == nullptr)
      return FALSE;

   hwnd->m_pimpl->m_puserinteraction->SetPlacement(*lprect);

   return TRUE;

}


WINBOOL EnableWindow(oswindow hwnd, WINBOOL bEnable)
{

   if(hwnd == nullptr)
      return FALSE;

   return TRUE;

}





void defer_dock_application(int_bool bDock)
{

   //   if (bDock)
   //   {
   //
   //      if (!nsapp_activation_policy_is_regular())
   //      {
   //
   //         nsapp_activation_policy_regular();
   //
   //      }
   //
   //   }
   //   else
   //   {
   //
   //      if (!nsapp_activation_policy_is_accessory())
   //      {
   //
   //         nsapp_activation_policy_accessory();
   //
   //      }
   //
   //   }
   //
}


int_bool destroy_window(oswindow window)
{

   UNREFERENCED_PARAMETER(window);

   return true;

}





void mm_init_workspace_rect();

WINBOOL os_init_windowing()
{

//   set_TranslateMessage(&axis_TranslateMessage);
   
//   set_DispatchMessage(&axis_DispatchMessage);
   
   g_pmutexOsWindowData = new ::mutex();
         
   g_poswindowdataptra = new oswindow_dataptra;
   
   mm_init_workspace_rect();
   
   return true;

}


void os_term_windowing()
{

   ::acme::del(g_poswindowdataptra);

   ::acme::del(g_pmutexOsWindowData);

}




// void update_session_cursor(class user::interaction_impl * puiimpl)
// {

//    __pointer(::ios::interaction_impl) pimpl = puiimpl;

//    if (pimpl.is_set())
//    {

//       return;

//    }

//    Sess(puiimpl->get_context_application()).get_cursor_pos(puiimpl->m_pointCursor);

// }


int_bool point_is_window_origin(POINT ptHitTest, oswindow oswindowExclude, int iMargin)
{

   return abs(ptHitTest.x) < iMargin && abs(ptHitTest.y) < iMargin;

}


void defer_term_ui()
{
   
   
   
}


int_bool is_window_occluded(oswindow oswindow)
{

   return false;
   
}
