#pragma once


namespace experience
{


   class CLASS_DECL_BASE frame :
      virtual public ::object
   {
   public:


      enum enum_element
      {

         ElementNone,
         ElementTopLeftIcon,
         ElementMoveGripMinimal,
         ElementEnd,

      };


      ::color                                m_colorFrameBorder;
      ::color                                m_colorMoveableBorderHilight;
      ::color                                m_colorMoveableBorderDkShadow;
      ::color                                m_colorCaptionTextBk;
      ::color                                m_colorActiveCaptionTextBk;
      ::color                                m_colorCaptionText;

      bool                                 m_bHollow;
      string                               m_strLibrary;
      string                               m_strName;
      ::rect                               m_rectCaption;
      ::rect                               m_rectCaptionTextBk;
      ::rect                               m_rectWindowText;
      int                                 m_iControlBoxPosition;
      //::rect                               m_rectControlBoxFullScreen;
      //::rect                               m_rectControlBoxZoomed;
      //::rect                               m_rectControlBoxNormal;
      point                                m_pointWindowIcon;
      point                                m_pointMoveGripMinimal;

      ::color                             m_colorMoveableBorder;
      ::color                             m_colorMoveableBorderShadow;


      ::experience::experience *           m_pexperience;
      ::experience::frame_window *         m_pframewindow;

      __composite(control_box)             m_pcontrolbox;

      i32                                  m_iCaptionHeight;

      ::rect                               m_rectControlBoxMargin;


      ::rect                               m_rectMarginFullScreen;
      ::rect                               m_rectMarginZoomed;
      ::rect                               m_rectMarginNormal;
      ::rect                               m_rectMarginDock;


      ::rect                               m_rectClient;
      ::rect                               m_rectWindow;
      int                                  m_iControlBoxRight;
      bool                                 m_bFirstLayoutDone;
      bool                                 m_bControlBoxAlignRight;
      bool                                 m_bInitialControlBoxPosition;



      frame();
      virtual ~frame();






      virtual int adjust_client_height(int iHeight);
      virtual int adjust_client_width(int iWidth);

      //virtual void set_style(const char * pszStyle);
      virtual void on_initialize_experience_frame();
      virtual void on_initialize_appearance();

      virtual void on_defer_display();

      //virtual void update_dock_grip_border_and_display();
      virtual void sync_dock_grip_border();

      //virtual void update_drawing_objects();
      virtual void update_window_client_rect();
      //virtual void update_window_region(const ::rect & rectWindow);

      //virtual void update_window();
      //virtual void update_window_style();

      virtual void defer_frame_placement_snapping();


      virtual string get_default_user_style() const;


      virtual void set_moveable_border_color(const ::color & color);




      virtual bool get_window_client_rect(RECT32 * prect);

      virtual bool get_draw_client_rect(RECT32 * prect);


      //virtual void calc_window_client_rect(RECT32 * prect, const rect & lprectWindow);


      virtual bool get_element_rect(RECT32 * prect, enum_element eelement);


      virtual void get_parent_rect(RECT32 * prect);

      virtual rect get_control_box_margin_rect();
      virtual rect get_margin_rect();
      virtual i32 get_caption_height();
      virtual i32 calc_caption_height();
      virtual i32 calc_caption_height(edisplay edisplay);

      virtual void title_bar_layout();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();

      //virtual i32 calc_control_box_left(bool bLayout);

      virtual __pointer(control_box) get_control_box();


      virtual void OnMove(__pointer(::user::interaction) pframewindow);


      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual void on_style_change();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual size GetMinSize();

      virtual void OnActivate();
      virtual void OnNcCalcSize(RECT32 * prect);

      //virtual void _001OnBeforeSize(const ::rect & rectWindow);

      virtual e_hittest _001HitTest(const ::point & point);


      virtual color32_t get_border_main_body_color();

      virtual bool _001OnLButtonDown(::message::mouse * pmouse);
      virtual bool _001OnLButtonUp(::message::mouse * pmouse);
      virtual bool _001OnMouseMove(::message::mouse * pmouse);
      virtual bool _001OnNcLButtonDown(::message::mouse * pmouse);
      virtual bool _001OnNcLButtonUp(::message::mouse * pmouse);
      virtual bool _001OnNcMouseMove(::message::mouse * pmouse);
      virtual bool _001OnNcHitTest(const ::point & point, LRESULT & nHitTest);
      virtual bool _001OnTimer(::u32 uEvent);
      //virtual bool _001OnSize(::u32 nType, i32 cx, i32 cy);
      //virtual bool _001OnMove(i32 x, i32 y);
      virtual bool _001OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult);



      virtual void frame_on_attach();
      virtual void frame_on_detach();

      virtual bool is_control_box_moveable();

      virtual void GetFrameRect(rect * prect);



      //virtual void nextstyle(::user::style_context * pcontext) override;


   };



} // namespace experience



