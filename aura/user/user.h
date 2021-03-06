#pragma once


class keyboard;
class front_end_schema;

//#include "user_window_map.h"
//#include "user_style.h"

namespace core
{

   class user;

} //namespace core


namespace user
{


   class CLASS_DECL_AURA user :
      virtual public ::apex::department
   {
   public:


      ::base::user *                         m_pbaseuser;
      ::core::user *                         m_pcoreuser;
      ::user::primitive *                    m_pmousefocusLButtonDown;
      ::user::primitive *                    m_pmousefocusRButtonDown;
      string_array                           m_straEscape;
      ::user::style_pointer                  m_puserstyle;
      string_map < ::user::style_pointer >   m_mapUserStyle;

      __composite(::html::html)              m_phtml; // defined in upper level

      ::type                                 m_typeHtmlDocument;
      ::type                                 m_typeHtmlView;
      
      __pointer_array(::user::interaction)   m_uiptraToolWindow;

      __pointer(::windowing::windowing)      m_pwindowing;

      ::mutex                                  m_mutexRunnable;
      list < __pointer(::matter) >        m_listRunnable;


      user();
      virtual ~user();


      virtual ::e_status initialize(::layered * pobjectContext) override;


      inline ::windowing::windowing * windowing() { return m_pwindowing; }

      virtual ::user::interaction * interaction(oswindow oswindow);

      virtual ::user::interaction * get_mouse_capture(::thread * pthread);

      virtual ::user::interaction * get_keyboard_focus(::thread * pthread);

      virtual ::user::interaction * get_active_window(::thread * pthread);

      virtual ::e_status set_active_window(::user::interaction *);

      
      virtual ::user::interaction * get_foreground_window();
      virtual ::e_status set_foreground_window(::user::interaction *);


      virtual ::user::style* get_user_style();

      //::user::style * get_user_style();

      //virtual ::e_status create_user_shell();


      virtual ::e_status init1() override;
      virtual ::e_status init2() override;
      virtual ::e_status init() override;


      virtual ::e_status create_windowing();




      inline ::html::html* html() { return m_phtml; } // defined in upper level

      inline ::type get_html_document_type() { return m_typeHtmlDocument; }
      inline ::type get_html_view_type() { return m_typeHtmlView; }



      virtual ::user::primitive * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual void defer_remove_mouse_focus_LButtonDown(::user::primitive * pmousefocus);
      virtual ::user::primitive * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::primitive * pmousefocus);

      virtual bool on_ui_mouse_message(::message::mouse* pmouse);

      virtual void SendMessageToWindows(const ::id & id, wparam wParam, lparam lParam);

      virtual void term() override;

      virtual ::type controltype_to_typeinfo(::user::enum_control_type econtroltype);

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style * pstyle, menu_item * pitem);


      virtual bool runnable_step();



   };




} // namespace user



