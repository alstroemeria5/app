#pragma once


namespace user
{


   class CLASS_DECL_AURA style_base :
      virtual public subject::manager
   {
   public:


      bool        m_bDarkMode;


      style_base();
      ~style_base() override;


      ::e_status on_initialize_object() override; 


      void on_subject(::subject::subject* psubject, ::subject::context* pcontext) override;

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, menu_item * pitem) = 0;
      //virtual bool prepare_menu(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) = 0;
      //virtual bool prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) = 0;
      //virtual void set_style(enum_style estyle);

      //virtual void set_style(const ::string & pszStyle);

      //virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_change_dark_mode();

      bool is_dark_mode() const { return m_bDarkMode; }


      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::frame * pframe);
      virtual bool draw_check(::user::interaction * pinteraction, ::enum_check echeck, const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer & pgraphics);

      virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics);
      //virtual bool on_ui_event(enum_event eevent, e_object eobject, ::user::interaction * pinteraction) = 0;
      //virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,tab * ptab) = 0;
      //virtual bool _001OnDrawMen::u32eraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * ptab) = 0;
      //virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangle,::draw2d::brush_pointer & brushText) = 0;

      //virtual bool _001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab) = 0;
      //virtual bool _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, ::user::check_box * pcheckbox) = 0;
      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar);
      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar);
      virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout);



      virtual enum_control_type get_control_type() const;


      virtual ::color::color get_color(const ::user::interaction* pinteraction, ::user::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) const;
      virtual bool get_int(const ::user::interaction* pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate = ::user::e_state_none) const;
      virtual bool get_double(const ::user::interaction* pinteraction, double & d, ::user::enum_double eint, ::user::enum_state estate = ::user::e_state_none) const;


   };


} // namespace user



