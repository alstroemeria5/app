#pragma once


class CLASS_DECL_BASE simple_frame_window :
   virtual public ::experience::frame_window
{
public:


   bool                                            m_bDefaultNotifyIcon : 1;
   bool                                            m_bShowTask : 1;
   bool                                            m_bFramePayloadFlags : 1;
   bool                                            m_bProdevianFrame : 1;
   bool                                            m_bFirstShow : 1;
   bool                                            m_bPendingSaveWindowRect : 1;
   bool                                            m_bDefaultCreateToolbar : 1;
   bool                                            m_bTransparentFrameEnable : 1;
   bool                                            m_bCustomFrameBefore : 1;
   __pointer(::user::tool_window)                  m_ptoolwindowFont;
   millis                                          m_millisLastSaveWindowRect;
   millis                                          m_millisLastSaveWindowRectRequest;
   ::image_pointer                                 m_pimageBk;
   ::rectangle_i32                                          m_FullScreenWindowRect;
   draw2d::fastblur                                m_blur;
   ::image_pointer                                 m_pimageBlur;
   ::user::enum_translucency                       m_etranslucencyFrame;
   id_map < __composite(::user::toolbar) >         m_toolbarmap;
   ::image_pointer                                 m_pimageAlpha;
   ::database::key                                 m_datakeyFrame;
   __pointer(::windowing::icon)                    m_piconNotify;
   __pointer(::user::notify_icon)                  m_pnotifyicon;
   ::payload                                       m_varFrame;
   __composite(::task)                             m_ptaskSaveWindowRect;


   simple_frame_window();
   virtual ~simple_frame_window();


   virtual ::e_status initialize(::object * pobject) override;
   
   
   ::user::notify_icon * notify_icon() override;


   virtual ::user::enum_translucency get_translucency(::user::style* pstyle) const override;


   virtual void SaveWindowRectTaskProcedure();


   virtual void defer_save_window_placement() override;

   virtual void _thread_save_window_placement();

   virtual void default_notify_icon_topic();
   virtual bool would_display_notify_icon();


   virtual bool keyboard_focus_is_focusable() const override;

   virtual bool create_bars();
   virtual bool on_create_bars() override;

   virtual void on_visual_applied() override;

   virtual void install_message_routing(::channel * pchannel) override;

   virtual bool on_before_set_parent(__pointer(::user::interaction) pframewindow);
   virtual bool on_set_parent(::user::primitive * puiParent) override;
   virtual void on_after_set_parent() override;

   virtual bool get_client_rect(RECTANGLE_I32 * prectangle);


   virtual bool is_application_main_window();

   bool GetCustomFrame();
   void SetCustomFrame(bool bCustom);
   void SetBorderRect(const ::rectangle_i32 & rectangle) override;
   virtual void GetBorderRect(RECTANGLE_I32 * prectangle) override;

   virtual ::color::color get_border_main_body_color() override;

   void ViewOnActivateFrame(__pointer(::user::impact) pview, ::u32 user, __pointer(::user::interaction) pframe);

   virtual void ToggleFullScreen();
   virtual void WfiOnFullScreen() override;
   virtual void _001OnExitFullScreen() override;
   virtual void show_control_bars(const ::e_display & edisplay = e_display_normal, bool bLeaveFullScreenBarsOnHide = false);

   virtual bool _001OnBeforeAppearance() override;
   virtual ::e_status initialize_frame_window_experience() override;


   virtual void _001OnAfterAppearance() override;

   virtual void WfiToggleShow();

   virtual bool window_is_notify_icon_enabled() override;
   void OnUpdateControlBarMenu(::message::command * pcommand);

   virtual bool WindowDataSaveWindowRect() override;
   virtual bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false) override;


   virtual ::experience::frame * experience_get_frame();

   //virtual bool LoadFrame(const ::string & pszMatter, u32 dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, ::user::interaction * puiParent = nullptr, ::user::system * pusersystem = nullptr) override;

   virtual bool LoadFrame(const ::string & pszMatter, u32 dwDefaultStyle = FWS_ADDTOTITLE, ::user::interaction * puiParent = nullptr, ::user::system * pusersystem = nullptr) override;

   void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

   //virtual bool LoadToolBar(::type sptype,id idToolBar, const ::string & pszToolBar,u32 dwCtrlStyle = TBSTYLE_FLAT,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);

   virtual bool LoadToolBar(::type sptype, id idToolBar, const ::string & pszToolBar, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = CBRS_ALIGN_TOP);

//   template < class TOOLBAR >
  // bool LoadToolBar(id idToolBar, const ::string & pszToolBar,u32 dwCtrlStyle = TBSTYLE_FLAT,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
   template < class TOOLBAR >
   bool LoadToolBar(id idToolBar, const ::string & pszToolBar,u32 dwCtrlStyle = TBSTYLE_FLAT,u32 uStyle = CBRS_ALIGN_TOP);


//   virtual bool LoadToolBar(id idToolBar, const ::string & pszToolBar, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP) override
//   {
//      return LoadToolBar < ::user::toolbar >(idToolBar, pszToolBar, dwCtrlStyle, uStyle);
//   }

   virtual bool LoadToolBar(id idToolBar, const ::string & pszToolBar,u32 dwCtrlStyle = TBSTYLE_FLAT,u32 uStyle = CBRS_ALIGN_TOP) override
   {
      return LoadToolBar < ::user::toolbar >(idToolBar,pszToolBar,dwCtrlStyle,uStyle);
   }


   virtual void InitialFramePosition(bool bForceRestore = false) override;
   virtual void on_frame_position();

   __pointer(::user::interaction) WindowDataGetWnd();
   virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
   virtual void on_reposition() override;
   virtual void ActivateFrame(::e_display edisplay = e_display_undefined) override;
   virtual bool on_create_client(::user::system * pusersystem) override;

   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void pre_translate_message(::message::message * pmessage) override;

   virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void draw_frame_and_control_box_over(::draw2d::graphics_pointer & pgraphics);

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void draw_frame(::draw2d::graphics_pointer & pgraphics);


   virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


   ::e_status command_handler(const ::id & id) override;


   virtual bool _001CanEnterScreenSaver() override;

   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(_001OnDdeInitiate);
   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   DECLARE_MESSAGE_HANDLER(on_message_move);
   DECLARE_MESSAGE_HANDLER(on_message_size);
   DECLARE_MESSAGE_HANDLER(on_message_close);
   DECLARE_MESSAGE_HANDLER(on_message_show_window);
   DECLARE_MESSAGE_HANDLER(_001OnViewFullScreen);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateViewFullScreen);
   DECLARE_MESSAGE_HANDLER(_001OnToggleCustomFrame);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateToggleCustomFrame);
   DECLARE_MESSAGE_HANDLER(_001OnToggleTransparentFrame);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateToggleTransparentFrame);
   DECLARE_MESSAGE_HANDLER(_001OnGetMinMaxInfo);
   DECLARE_MESSAGE_HANDLER(on_message_app_exit);
   DECLARE_MESSAGE_HANDLER(_001OnNotifyIconTopic);
   DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
   DECLARE_MESSAGE_HANDLER(_001OnActivate);
   DECLARE_MESSAGE_HANDLER(_001OnActivateApp);
   DECLARE_MESSAGE_HANDLER(on_message_display_change);
   DECLARE_MESSAGE_HANDLER(_001OnTaskbarCreated);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateNotifyIcon);
   DECLARE_MESSAGE_HANDLER(_001OnKey);
   DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);


   virtual void _000OnMouseLeave(::message::message* pmessage) override;

   virtual bool updown_get_up_enable() override;
   virtual bool updown_get_down_enable() override;


   virtual class mini_dock_frame_window* CreateFloatingFrame(u32 uStyle);
   //virtual void NotifyFloatingWindows(u32 dwFlags) override;


   virtual void design_down() override;
   virtual void design_up() override;


   //virtual bool calc_layered() override;


   virtual string get_window_default_matter() override;


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


   void OnHScroll(::u32 nSBCode, ::u32 nPos, ::user::scroll_bar* pScrollBar);
   void OnVScroll(::u32 nSBCode, ::u32 nPos, ::user::scroll_bar* pScrollBar);
   virtual void on_simple_command(::message::simple_command * psimplecommand) override;

//#ifdef WINDOWS_DESKTOP
//   virtual void OnDropFiles(HDROP hDropInfo);
//   virtual bool OnQueryEndSession();
//   virtual void OnEndSession(bool bEnding);
//#endif


   //LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam) override;
   //LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam) override;
   //LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam) override;

   void _001OnQueryEndSession(::message::message * pmessage);

   void on_control_event(::user::control_event * pevent) override;

   virtual void route_command_message(::message::command * pcommand) override;

   virtual void data_on_after_change(::message::message * pmessage);

   virtual void _on_show_window() override;

   virtual void on_after_graphical_update() override;

   virtual void InitialUpdateFrame(::user::document * pDoc,bool bMakeVisible) override;

   virtual void _001OnTimer(::timer * ptimer) override;

   virtual bool frame_is_transparent() override;




   virtual void OnInitialFrameUpdate(bool bMakeVisible) override;

   virtual void OnUpdateToolWindow(bool bVisible);

   virtual void show_task(bool bShow);

   //virtual void defer_set_icon();

   using ::user::frame_window::get_color;

   virtual void on_select_user_style();


   virtual void defer_create_notification_icon();

   virtual void call_notification_area_action(const ::string & pszId);

   //virtual void OnNotifyIconContextMenu(const ::id & idNotifyIcon);
   //virtual void OnNotifyIconLButtonDblClk(const ::id& idNotifyIcon);
   //virtual void OnNotifyIconLButtonDown(const ::id& idNotifyIcon);

   virtual void notification_area_action(const ::string & pszId);

   virtual string notification_area_get_xml_menu();



};



