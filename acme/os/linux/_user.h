#pragma once


// Ubuntu apt-get install libx11-dev
// // Ubuntu apt-get install libx11-dev
// // CentOS yum install libX11-devel
//!!!#include <X11/X.h>
//!!!#include <X11/Xlib.h>
//!!!#include <X11/Xutil.h>
//!!!#include <X11/Xatom.h>
//#include <X11/Xatom.h>
// // Ubuntu apt-get install libcairo2-dev

// sudo apt install libgtk-3-dev
// gtk3-devel
//#include <glib.h>


enum enum_net_wm_state
{

   e_net_wm_state_first,
   e_net_wm_state_above = e_net_wm_state_first,
   e_net_wm_state_below,
   e_net_wm_state_hidden,
   e_net_wm_state_maximized_horz,
   e_net_wm_state_maximized_vert,
   e_net_wm_state_fullscreen,
   e_net_wm_state_skip_taskbar,
   e_net_wm_state_count,

};


//e_net_wm_state net_wm_state(const char * pszText);
//const char * net_wm_state_text(e_net_wm_state estate);


//CLASS_DECL_ACME int xinerama_get_monitor_count();
//CLASS_DECL_ACME int xinerama_get_monitor_rect(index i, RECTANGLE_I32 * prectangle);
//CLASS_DECL_ACME int xinerama_get_screen_size(int& width, int& height);


//int best_xinerama_monitor(::user::interaction * pinteraction, RECTANGLE_I32 * prectRet);
//int best_xinerama_monitor(::user::interaction * pinteraction, const ::rectangle_i32 & rectangle, RECTANGLE_I32 * lprectRet);


//!!!void mapped_net_state_raw(bool add, Display * d, Window w, int iScreen, Atom state1, Atom state2);
//!!!void unmapped_net_state_raw(Display * d, Window w, ...);


#include "cross_win_gdi.h"


//#include "xdisplay.h"


//#include "osdisplay.h"


//#include "oswindow.h"


//#include "window_cairo.h"


//#include "window_xlib.h"


//#include "windowing.h"


#ifdef __cplusplus


//!!!void set_xcolor(XColor & color, color32_t cr);


#endif


//CLASS_DECL_ACME i32 oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_ACME i32 oswindow_find(Display * pdisplay, Window window);
//CLASS_DECL_ACME i32 oswindow_find(Window window);
//CLASS_DECL_ACME oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
////CLASS_DECL_ACME oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = nullptr);
//CLASS_DECL_ACME oswindow_data * oswindow_get(Window window);
//CLASS_DECL_ACME oswindow oswindow_defer_get(Window w);
//CLASS_DECL_ACME bool oswindow_remove(Display * pdisplay, Window window);
//CLASS_DECL_ACME bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);


//#ifndef HWND_MESSAGE
//#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)
//#



//
//
//!!!//class CLASS_DECL_ACME device_context
//{
//public:
//
//
//   ::Display *             m_pdisplay;
//   ::Drawable              m_drawable;
//   ::GC                    m_gc;
//   ::Pixmap                m_pixmap;
//   ::Window                m_window;
//   int                     m_iDepth;
//   int                     m_iScreen;
//
//   point_i32                   m_point;
//   point_i32                   m_pointOffset;
//
//   XFontSet                m_fontset;
//
//   device_context();
//
//
//};
//


//extern GMainContext * gtk_main_context;


//gboolean gdk_callback_run_runnable(gpointer pdata);


#include <stdio.h>


#include <string.h>


//Display * x11_get_display();



