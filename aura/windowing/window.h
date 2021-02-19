// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA window :
      virtual public ::channel
   {
   public:


      bool                                         m_bMessageOnlyWindow : 1;


#ifdef WINDOWS
      void *                                       m_posdata;
#endif

      __pointer(::windowing::display)         m_pdisplay;
      __pointer(::user::interaction_impl)     m_pimpl;
      string                                       m_strDebug;
      __pointer(message_queue)                     m_pmessagequeue;
      millis                                       m_millisLastMouseMove;
      __pointer(window)                            m_pwindowParent;
      ::rectangle_i32                              m_rectangle;
      __pointer(windowing)                         m_pwindowing;


      window();
      virtual ~window();


      virtual ::e_status create_window(::user::interaction_impl * pimpl);


      virtual ::e_status set_keyboard_focus();

      virtual ::e_status set_mouse_capture();

      virtual ::e_status set_active_window();



      //virtual oswindow get_os_data() const;

      virtual bool has_mouse_capture() const;
      virtual bool has_keyboard_focus() const;




      virtual ::windowing::display * display();

      oswindow get_oswindow() const { return (::oswindow) get_os_data(); }
      void set_oswindow(oswindow oswindow);


      //void send_client_event(Atom atom, unsigned int numArgs, ...);
      virtual i32 store_name(const char * psz);
      virtual i32 select_input(i32 iInput);
      virtual i32 select_all_input();
      virtual i32 map_window();
      virtual i32 unmap_window(bool bWithdraw);
      virtual void set_wm_class(const char * psz);

      virtual void exit_iconify();

      virtual void full_screen(const::rectangle_i32 & rectangle = nullptr);

      virtual void exit_full_screen();

      virtual void exit_zoomed();

      virtual ::e_status destroy_window();

      virtual ::e_status show_window(const ::e_display & edisplay, const ::e_activation & eactivation);

      virtual void set_user_interaction(::layered * pinteraction);

      virtual void post_nc_destroy();

      virtual bool is_child_of(const window * pwindowAscendantCandidate) const; // or descendant
      
      
      virtual ::windowing::window * get_parent() const;
      virtual oswindow get_parent_oswindow() const;
      virtual ::e_status set_parent(::windowing::window * pwindowNewParent);

      
      virtual ::windowing::window * get_owner() const;
      virtual oswindow get_owner_oswindow() const;
      virtual ::e_status set_owner(::windowing::window * pwindowNewOwner);


      virtual long get_state();
      virtual bool is_iconic();
      virtual bool is_zoomed();
      virtual bool is_window();
      virtual bool is_window_visible();
      
      
//      virtual iptr get_window_long_ptr(i32 nIndex) const;
//      virtual bool set_window_long_ptr(i32 nIndex, iptr l);
//
//      virtual iptr get_style() const;
//      virtual iptr get_ex_style() const;
//
//      virtual bool set_style(iptr nStyle);
//      virtual bool set_ex_style(iptr nExStyle);
//
//      virtual bool modify_style(uptr dwRemove, uptr dwAdd, ::u32 nFlags);
//      virtual bool modify_ex_style(uptr dwRemove, uptr dwAdd, ::u32 nFlags);


      virtual bool _001ClientToScreen(POINT_I32 * ppoint);

      virtual bool _001ScreenToClient(POINT_I32 * ppoint);




      virtual bool set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);
      virtual bool _set_window_pos(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);

      virtual bool is_destroying();

      virtual bool bamf_set_icon();

      //virtual bool set_icon(::image * pimage);

      virtual void activate_top_parent();

      //int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);



      void user_common_construct();

      //virtual bool set_window_position(::user::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags = SWP_SHOWWINDOW);



      //virtual void construct(::windowing::window * pwindow);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      //bool create_message_queue(::user::interaction * pinteraction, const char * lpszName);

      //virtual const MSG* GetCurrentMessage();

      //virtual ::e_status update_graphics_resources();


      //virtual bool __windows_message_bypass(HWND oswindow, ::u32 message, wparam wparam, lparam lparam, lresult & lresult);

      virtual void install_message_routing(::channel * pchannel);


      virtual void message_handler(::message::message * pusermessage);

      //bool operator==(const interaction_impl & wnd) const;
      //bool operator!=(const interaction_impl & wnd) const;

      //virtual u32 GetStyle() const;
      //virtual u32 GetExStyle() const;
      //virtual bool ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0);
      //virtual bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0);

      //virtual ::user::interaction * get_owner();
      //virtual void set_owner(::user::interaction * pOwnerWnd);

      virtual void route_command_message(::message::command * pcommand);

      //void _002OnDraw(::image * pimage);

      virtual void present();

      //virtual void defer_start_prodevian();

      //virtual bool set_icon(::draw2d::icon * picon, bool bSmall);

      virtual void on_visual_applied();

      //virtual void window_apply_visual(const ::user::window_state & windowstate);

      //DECL_GEN_SIGNAL(_001OnDestroy);
      //DECL_GEN_SIGNAL(_001OnCreate);
      //DECL_GEN_SIGNAL(_001OnKillFocus);
      //DECL_GEN_SIGNAL(_001OnPaint);
      //DECL_GEN_SIGNAL(_001OnPrint);
      //DECL_GEN_SIGNAL(_001OnSetFocus);
      //DECL_GEN_SIGNAL(_001OnNcCalcSize);
      //DECL_GEN_SIGNAL(_001OnSetCursor);
      //DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      //DECL_GEN_SIGNAL(_001OnMove);
      //DECL_GEN_SIGNAL(_001OnSize);
      //DECL_GEN_SIGNAL(_001OnShowWindow);
      //DECL_GEN_SIGNAL(_001OnActivate);
      //DECL_GEN_SIGNAL(_001OnDwmNcRenderingChanged);
      //DECL_GEN_SIGNAL(_001OnProdevianSynch);
      //DECL_GEN_SIGNAL(_001OnWindowPosChanging);
      //DECL_GEN_SIGNAL(_001OnWindowPosChanged);
      //DECL_GEN_SIGNAL(_001OnGetMinMaxInfo);
      //DECL_GEN_SIGNAL(_001OnEnable);


      virtual void win_update_graphics();

//#if(WINVER >= 0x0500)
//
//      bool GetWindowInfo(PWINDOWINFO pwi) const;
//      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
//
//#endif   // WINVER >= 0x0500

      //      virtual ::user::interaction * from_os_data(void * pdata);
      //virtual void * get_os_data() const;


      //virtual ::e_status finish(::context_object * pcontextobjectFinish);


      //      virtual ::user::interaction * from_handle(::windowing::window * pwindow);

      // subclassing/unsubclassing functions
      //virtual void pre_subclass_window();
      //bool subclass_window(::windowing::window * pwindow);
      //bool SubclassDlgItem(::u32 nID, ::user::interaction_impl * pParent);
      //oswindow unsubclass_window();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //bool ExecuteDlgInit(const char * pszResourceName);

      //bool ExecuteDlgInit(LPVOID pResource);


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, const char * pszClassName,const char * pszWindowName,u32 dwStyle,const ::rectangle_i32 & rectangle,::user::interaction * pParentWnd,id id, ::create * pcreate = nullptr);


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, __pointer(::user::system) pusersystem, ::user::interaction * puiParent, id id);

      //virtual ::e_status native_create_host();

      //virtual bool destroy_impl_only();
      //virtual bool DestroyWindow();

      //virtual void destroy_window();

      // special pre-creation and interaction_impl rectangle_i32 adjustment hooks
      //virtual bool pre_create_window(::user::system * pusersystem);

      // Advanced: virtual AdjustWindowRect
      //enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      //virtual void CalcWindowRect(RECTANGLE_I32 * pClientRect, ::u32 nAdjustType = adjustBorder);



      // get immediate child with given ID
      //using ::user::interaction_impl::get_child_by_id;
      //void get_child_by_id(id id, oswindow * poswindow_) const;

      //virtual bool _is_window() const;

      //#if(WINVER >= 0x0500)
      //
      //      ::user::interaction_impl * GetAncestor(::u32 gaFlags) const;
      //
      //#endif   // WINVER >= 0x0500

      virtual lresult send_message(const ::id & id, wparam wParam = 0, lparam lParam = nullptr);

      virtual bool post_message(const ::id & id, wparam wParam = 0, lparam lParam = nullptr);


      //bool SendNotifyMessage(::u32 message, wparam wParam, lparam lParam);

      //bool SendChildNotifyLastMsg(lresult* pResult = nullptr);

      //bool DragDetect(const ::point_i32 & point) const;



      // Window Text Functions
      virtual void set_window_text(const char * pszString);

      virtual strsize get_window_text(char * pszStringBuf, strsize nMaxCount);

      virtual void get_window_text(string & rectString);
      virtual strsize get_window_text_length();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      //virtual void on_reposition();
      //virtual void on_show_window();
      //virtual void on_zorder();

      //virtual void clear_need_layout();
      //virtual void clear_need_translation();
      //virtual void clear_show_flags();
      //virtual void clear_need_zorder();


      //virtual bool set_window_position(iptr z, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags = SWP_SHOWWINDOW);


      // Window size_i32 and position Functions
      //virtual bool window_is_iconic();
      //virtual bool window_is_zoomed();
      //i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //i32 GetWindowRgn(HRGN hRgn);

      virtual ::u32 ArrangeIconicWindows();
      //virtual void BringToTop(::e_display edisplay);
      //virtual bool BringWindowToTop();
      //using ::user::interaction_impl::get_window_rect;
      //virtual bool get_window_rect(RECTANGLE_I64 * prectangle);

      //using ::user::interaction_impl::get_client_rect;
      //virtual bool get_client_rect(RECTANGLE_I64 * prectangle);


      virtual void rects_from_os();
      virtual bool window_rect_from_os(RECTANGLE_I32 * prectangle);
      virtual bool client_rect_from_os(RECTANGLE_I32 * prectangle);



      //virtual point_f64 client_screen_top_left();


      //virtual bool GetWindowPlacement(WINDOWPLACEMENT * pwndpl);

      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT * pwndpl);


      //virtual void MapWindowPoints(::user::interaction_impl * pwndTo, POINT_I32 * pPoint, ::u32 nCount);

      //virtual void MapWindowPoints(::user::interaction_impl * pwndTo, RECTANGLE_I32 * prectangle);


      //virtual void Print(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;
      //virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;

      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      virtual bool GetUpdateRect(RECTANGLE_I32 * prectangle, bool bErase = false);

      virtual i32 GetUpdateRgn(::draw2d::region * pRgn, bool bErase = false);
      virtual void Invalidate(bool bErase = true);
      virtual void InvalidateRect(const RECTANGLE_I32 * rectangle, bool bErase = true);

      virtual void InvalidateRgn(::draw2d::region * pRgn, bool bErase = true);
      virtual void ValidateRect(const RECTANGLE_I32 * rectangle_i32);

      virtual void ValidateRgn(::draw2d::region * pRgn);
      //virtual bool display(::e_display edisplay);


      //virtual void sketch_prepare_window_minimize(::e_activation eactivation);
      //virtual void sketch_prepare_window_maximize();
      //virtual void sketch_prepare_window_full_screen(const ::rectangle_i32 & rectHint = nullptr);
      //virtual void sketch_prepare_window_restore(edisplay edisplay);


      //virtual bool _is_window_visible();
      virtual void ShowOwnedPopups(bool bShow = true);

      //virtual __pointer(::draw2d::graphics) GetDCEx(::draw2d::region * prgnClip, u32 flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      //virtual bool RedrawWindow(const ::rectangle_i32 & rectUpdate = nullptr,
        // ::draw2d::region * prgnUpdate = nullptr,
         //::u32 flags = RDW_INVALIDATE | RDW_ERASE);

      virtual bool RedrawWindow(const ::rectangle_i32 & rectUpdate = nullptr,
         ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = 0);/*
         ::u32 flags = RDW_INVALIDATE | RDW_ERASE);*/

      //virtual bool EnableScrollBar(i32 nSBFlags, ::u32 nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(i32 idAni, const LPRECTprcFrom, const LPRECTlprcTo);

      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const rectangle_i32 & prc, ::u32 uFlags);


      //#if(WINVER >= 0x0500)
      //
      //      virtual bool AnimateWindow(millis millis, u32 dwFlags);
      //
      //#endif   // WINVER >= 0x0500
      //
      //#if(_WIN32_WINNT >= 0x0501)
      //
      //      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, ::u32 nFlags) const;
      //
      //#endif   // _WIN32_WINNT >= 0x0501
      //
            // Layered Window

      //#if(_WIN32_WINNT >= 0x0500)
      //
      //      virtual bool SetLayeredWindowAttributes(color32_t crKey, byte bAlpha, u32 dwFlags);
      //      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT_I32 *pptDst, SIZE_I32 *psize,
      //                                       ::draw2d::graphics * pDCSrc, POINT_I32 *pptSrc, color32_t crKey, BLENDFUNCTION *pblend, u32 dwFlags);
      //
      //#endif   // _WIN32_WINNT >= 0x0500

      //#if(_WIN32_WINNT >= 0x0501)
      //
      //      virtual bool GetLayeredWindowAttributes(color32_t *pcrKey, byte *pbAlpha, u32 *pdwFlags) const;
      //
      //#endif   // _WIN32_WINNT >= 0x0501


            // timer Functions
      //      virtual bool SetTimer(uptr uEvent, ::u32 nElapse, PFN_TIMER pfnTimer);
            //    virtual bool KillTimer(uptr uEvent);

            // Window State Functions
      virtual bool is_this_enabled();
      virtual bool enable_window(bool bEnable = true);

      // the active interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();

      // the foreground interaction_impl applies only to top-level windows (frame windows)
      virtual ::e_status set_foreground_window();
      virtual ::user::interaction * get_foreground_window();



      virtual bool SetFocus();


      //virtual bool has_keyboard_focus();
      virtual bool is_active_window() const;

      //virtual ::user::interaction * GetFocus();

      virtual ::user::interaction * get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for new code
      virtual void CloseWindow();
      virtual bool OpenIcon();

      // Dialog-Box Item Functions
      // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      //virtual void CheckDlgButton(i32 nIDButton, ::u32 nCheck);
      //virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton);
      //virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton);
      //virtual i32 DlgDirList(__inout_z TCHAR * pPathSpec, __in i32 nIDListBox,

        // __in i32 nIDStaticPath, __in::u32 nFileType);
      //virtual i32 DlgDirListComboBox(__inout_z TCHAR * pPathSpec, __in i32 nIDComboBox,

        // __in i32 nIDStaticPath, __in::u32 nFileType);
      //virtual bool DlgDirSelect(__out_ecount_z(nSize) TCHAR * pString, __in i32 nSize, __in i32 nIDListBox);

      //virtual bool DlgDirSelectComboBox(__out_ecount_z(nSize) TCHAR * pString, __in i32 nSize, __in i32 nIDComboBox);


      //virtual ::u32 GetChildByIdInt(i32 nID, BOOL * pTrans = nullptr, bool bSigned = true) const;

      //virtual i32 GetChildByIdText(__in i32 nID, __out_ecount_part_z(nMaxCount, return +1) TCHAR * pStr, __in i32 nMaxCount) const;

      //virtual i32 GetChildByIdText(i32 nID, string & rectString) const;
      //virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      //virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      //virtual ::u32 IsDlgButtonChecked(i32 nIDButton) const;
      //virtual lresult SendDlgItemMessage(i32 nID, ::u32 message, wparam wParam = 0, lparam lParam = 0);
      //virtual void SetDlgItemInt(i32 nID, ::u32 nValue, bool bSigned = true);
      //virtual void SetDlgItemText(i32 nID, const char * pszString);


      //virtual bool open_clipboard();
      //virtual bool close_clipboard();


      // Scrolling Functions
      //virtual i32 GetScrollPos(i32 nBar) const;
      //virtual void GetScrollRange(i32 nBar, LPINT pMinPos, LPINT lpMaxPos) const;

      //virtual void ScrollWindow(i32 xAmount, i32 yAmount,
      //   const RECTANGLE_I32 * rectangle = nullptr,

      //   const RECTANGLE_I32 * pClipRect = nullptr);

      //virtual i32 SetScrollPos(i32 nBar, i32 nPos, bool bRedraw = true);
      //virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos,
      //   bool bRedraw = true);
      //virtual void ShowScrollBar(::u32 nBar, bool bShow = true);
      //virtual void EnableScrollBarCtrl(i32 nBar, bool bEnable = true);

      //virtual i32 ScrollWindowEx(i32 dx, i32 dy,
      //   const RECTANGLE_I32 * pRectScroll, const RECTANGLE_I32 * lpRectClip,

      //   ::draw2d::region * prgnUpdate, RECTANGLE_I32 * pRectUpdate, ::u32 flags);

      //virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo,

      //   bool bRedraw = true);
      //virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, ::u32 nMask = SIF_ALL);

      //virtual i32 GetScrollLimit(i32 nBar);

      //#if(WINVER >= 0x0500)
      //
      //      virtual bool GetScrollBarInfo(::i32 idObject, PSCROLLBARINFO psbi) const;
      //
      //#endif   // WINVER >= 0x0500

            // Window Access Functions
      //virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point);
      //virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point, ::u32 nFlags);
      ///      virtual ::user::interaction_impl * FindWindow(const char * pszClassName,const char * pszWindowName);

      //   virtual ::user::interaction_impl * FindWindowEx(::windowing::window * pwindowParent,::windowing::window * pwindowChildAfter,const char * lpszClass,const char * pszWindow);

      //virtual ::point_i64 _client_parent_top_left();
      //virtual ::point_i64 _client_screen_top_left();

      virtual ::windowing::window * get_next_window(::u32 nFlag = 0);
      virtual ::windowing::window * get_top_window() const;

      virtual ::windowing::window * get_window(::u32 nCmd) const;
      virtual ::windowing::window * get_last_active_popup() const;

      //virtual ::user::interaction * set_owner(::user::interaction * pWndNewParent);
      //virtual ::user::interaction * get_owner() const;


      virtual point_i32 GetCaretPos();
      virtual void SetCaretPos(const ::point_i32 & point);
      virtual void HideCaret();
      virtual void ShowCaret();

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = true);

      // icon Functions
      virtual ::e_status set_icon(::windowing::icon * picon);
      virtual __pointer(::windowing::icon) get_icon() const;


      virtual ::e_status set_cursor(::windowing::cursor * pcursor);


      // Context Help Functions
      //virtual bool SetWindowContextHelpId(u32 dwContextHelpId);
      //virtual u32 GetWindowContextHelpId() const;

      // Dialog Data support
      //virtual bool update_data(bool bSaveAndValidate = true);
      // data wnd must be same type as this

      //// Help Command Handlers
      //void OnHelp();          // F1 (uses current action_context)
      //void OnHelpIndex();     // ID_HELP_INDEX
      //void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      //void OnHelpUsing();     // ID_HELP_USING
      //virtual void WinHelp(uptr dwData, ::u32 nCmd = HELP_CONTEXT);
      ////virtual void HtmlHelp(uptr dwData, ::u32 nCmd = 0x000F);
      //virtual void WinHelpInternal(uptr dwData, ::u32 nCmd = HELP_CONTEXT);


      // dialog support
      //void UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler);
      //void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      ////virtual id   RunModalLoop(u32 dwFlags = 0,::object * pliveobject = nullptr);
      //virtual bool ContinueModal();
      //virtual void EndModalLoop(id nResult);
      //virtual void EndAllModalLoops(id nResult);

      // Window-Management message handler member functions
      //virtual bool OnCommand(::message::message * pusermessage);
      //virtual bool OnNotify(::message::message * pusermessage);

      //void OnActivate(::u32 nState, ::user::interaction_impl * pWndOther, bool bMinimized);
      //void OnActivateApp(bool bActive, u32 dwThreadID);
      //lresult OnActivateTopLevel(wparam, lparam);
      //void OnCancelMode();
      //void OnChildActivate();
      //void OnClose();
      //void OnContextMenu(::user::interaction_impl * pwindow, point_i32 pos);
      //bool OnCopyData(::user::interaction_impl * pwindow, COPYDATASTRUCT* pCopyDataStruct);

      //HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction_impl * pwindow, ::u32 nCtlColor);


      //void OnEnable(bool bEnable);
      //void OnEndSession(bool bEnding);
      //void OnEnterIdle(::u32 nWhy, ::user::interaction_impl * pWho);
      //bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //void OnGetMinMaxInfo(MINMAXINFO* pMMI);

      //bool OnHelpInfo(HELPINFO* pHelpInfo);

      //void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //lresult OnMenuChar(::u32 nChar, ::u32 nFlags, ::user::menu* pMenu);
      //void OnMenuSelect(::u32 nItemID, ::u32 nFlags, HMENU hSysMenu);
      //void OnMove(i32 x, i32 y);
      //void OnParentNotify(const ::id & id, lparam lParam);
      //hcursor OnQueryDragIcon();
      //bool OnQueryEndSession();
      //bool OnQueryNewPalette();
      //bool OnQueryOpen();
      //void OnShowWindow(bool bShow, ::u32 nStatus);
      //void OnSize(::u32 nType, i32 cx, i32 cy);
      //void OnTCard(::u32 idAction, u32 dwActionData);

      //void OnChangeUIState(::u32 nAction, ::u32 nUIElement);
      //void OnUpdateUIState(::u32 nAction, ::u32 nUIElement);
      //::u32 OnQueryUIState();

      //// Nonclient-Area message handler member functions
      //bool OnNcActivate(bool bActive);
      //void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* pncsp);

      //bool OnNcCreate(::user::system * pCreateStruct);

      //lresult OnNcHitTest(const ::point_i32 & point);
      //void OnNcLButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcLButtonDown(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcLButtonUp(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMButtonDown(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMButtonUp(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcMouseMove(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcPaint();
      //void OnNcRButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcRButtonDown(::u32 nHitTest, const ::point_i32 & point);
      //void OnNcRButtonUp(::u32 nHitTest, const ::point_i32 & point);

      //// System message handler member functions
      //void OnDropFiles(HDROP hDropInfo);
      //void OnPaletteIsChanging(::user::interaction_impl * pRealizeWnd);
      //void OnSysChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnSysCommand(::u32 nID, lparam lParam);
      //void OnSysDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnSysKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnSysKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnCompacting(::u32 nCpuTime);
      //void OnDevModeChange(__in_z char * pDeviceName);

      //void OnFontChange();
      //void OnPaletteChanged(::user::interaction_impl * pFocusWnd);
      //void OnSpoolerStatus(::u32 nStatus, ::u32 nJobs);
      //void OnSysColorChange();
      //void OnTimeChange();
      //void OnSettingChange(::u32 uFlags, const char * pszSection);

      //void OnWinIniChange(const char * pszSection);


      //// Input message handler member functions
      //void OnChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      ////      void OnHScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      ////    void OnVScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      //void OnKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      //void OnLButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      //void OnLButtonDown(::u32 nFlags, const ::point_i32 & point);
      //void OnLButtonUp(::u32 nFlags, const ::point_i32 & point);
      //void OnMButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      //void OnMButtonDown(::u32 nFlags, const ::point_i32 & point);
      //void OnMButtonUp(::u32 nFlags, const ::point_i32 & point);
      //i32 OnMouseActivate(::user::interaction_impl * pDesktopWnd, ::u32 nHitTest, const ::id & id);
      //void OnMouseMove(::u32 nFlags, const ::point_i32 & point);
      //bool OnMouseWheel(::u32 nFlags, i16 zDelta, const ::point_i32 & point);
      //lresult OnRegisteredMouseWheel(wparam wParam, lparam lParam);
      //void OnRButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      //void OnRButtonDown(::u32 nFlags, const ::point_i32 & point);
      //void OnRButtonUp(::u32 nFlags, const ::point_i32 & point);
      //void OnTimer(uptr uEvent);

      //// Initialization message handler member functions
      //void OnInitMenu(::user::menu* pMenu);
      //void OnInitMenuPopup(::user::menu* pPopupMenu, ::u32 nIndex, bool bSysMenu);

      //// Clipboard message handler member functions
      //void OnAskCbFormatName(__in ::u32 nMaxCount, __out_ecount_z(nMaxCount) char * pszString);

      //void OnChangeCbChain(::windowing::window * pwindow_Remove, ::windowing::window * pwindow_After);
      //void OnDestroyClipboard();
      //void OnDrawClipboard();
      //void OnHScrollClipboard(::user::interaction_impl * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);
      //void OnPaintClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hPaintStruct);
      //void OnRenderAllFormats();
      //void OnRenderFormat(::u32 nFormat);
      //void OnSizeClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hRect);
      //void OnVScrollClipboard(::user::interaction_impl * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);

      //// control message handler member functions
      //i32 OnCompareItem(i32 nIDCtl, LPCOMPAREITEMSTRUCT pCompareItemStruct);

      //void OnDeleteItem(i32 nIDCtl, LPDELETEITEMSTRUCT pDeleteItemStruct);

      //void OnDrawItem(i32 nIDCtl, LPDRAWITEMSTRUCT pDrawItemStruct);

      //::u32 OnGetDlgCode();

      // MDI message handler member functions
      //void OnMDIActivate(bool bActivate,
      //                   ::user::interaction_impl * pActivateWnd, ::user::interaction_impl * pDeactivateWnd);

      // menu loop notification messages
      //void OnEnterMenuLoop(bool bIstrack_popup_menu);
      //void OnExitMenuLoop(bool bIstrack_popup_menu);

      //// Win4 messages
      //void OnStyleChanged(i32 nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnStyleChanging(i32 nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnSizing(::u32 nSide, RECTANGLE_I32 * prectangle);

      //void OnMoving(::u32 nSide, RECTANGLE_I32 * prectangle);

      //void OnCaptureChanged(::user::interaction_impl * pwindow);
      //bool OnDeviceChange(::u32 nEventType, uptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      //virtual WNDPROC * GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
      //virtual void BeginModalState();
      //virtual void EndModalState();

      // for translating Windows messages in Main message pump
      //virtual void pre_translate_message(::message::message * pmessage);


      //virtual void default_message_handler(::message::message * pusermessage);
      //virtual void message_handler(::message::message * pusermessage);


      //virtual bool OnWndMsg(const ::id & id, wparam wParam, lparam lParam, lresult* pResult);

      // for handling default processing
      //lresult Default();
      //virtual void default_window_procedure(::message::message * pmessage);


      //virtual void PostNcDestroy();

      // for notifications from parent
      //virtual bool OnChildNotify(::message::message * pusermessage);
      // return true if parent should not process this message
      //virtual bool ReflectChildNotify(::message::message * pusermessage);
      //virtual bool ReflectMessage(::windowing::window * pwindow_Child, ::message::message * pusermessage);

      // Implementation
      //virtual bool CheckAutoCenter();
      //virtual bool GrayCtlColor(HDC hDC, ::windowing::window * pwindow, ::u32 nCtlColor,
      //                          HBRUSH hbrGray, color32_t clrText);

      //virtual ::e_status set_window_position(::zorder zorder, int x, int y, int cx, int cy, ::u32 uFlags);

      // helper routines for implementation
      //bool HandleFloatingSysCommand(::u32 nID, lparam lParam);
      //bool IsTopParentActive();
      //void ActivateTopParent();
      //virtual void on_final_release();
      ///virtual bool ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags);
      //virtual bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags);
      //virtual void _FilterToolTipMessage(MSG* pMsg,::user::interaction_impl * pwindow);
      //bool _EnableToolTips(bool bEnable, ::u32 nFlag);
      //virtual oswindow get_safe_owner(::::windowing::window * pwindow, ::oswindow * pWndTop);
      //void PrepareForHelp();


      virtual ::e_status set_tool_window(bool bSet);


      friend class frame_window;

      //bool CreateDlg(const char * pszTemplateName, ::user::interaction_impl * pParentWnd);



      //CLASS_DECL_AURA friend lresult CALLBACK __send_message_hook(i32, wparam, lparam);
      //CLASS_DECL_AURA friend lresult CALLBACK __cbt_filter_hook(i32, wparam, lparam);

      // standard message implementation
      //lresult OnNTCtlColor(wparam wParam, lparam lParam);
      //lresult OnDisplayChange(wparam, lparam);
      //lresult OnDragList(wparam, lparam);



      //virtual void get_app_wnda(user::oswindow_array & wnda);

      //virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      //virtual ::i32 get_window_long(i32 nIndex) const;
      //virtual ::i32 set_window_long(i32 nIndex, ::i32 lValue);
      //virtual iptr get_window_long_ptr(i32 nIndex) const;
      //virtual iptr set_window_long_ptr(i32 nIndex, iptr lValue);


      //void _001OnTriggerMouseInside();

      void set_viewport_org(::draw2d::graphics_pointer & pgraphics);


      void on_set_parent(::user::interaction * pinteraction);


      virtual bool get_rect_normal(RECTANGLE_I32 * prectangle);
      //virtual void register_drop_target();
      virtual void show_task(bool bShow);
      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation);


      virtual void non_top_most_upper_window_rects(::rect_array & recta);

      virtual void default_message_handler(::message::message * pmessage);

      virtual void track_mouse_hover();


      virtual void _task_transparent_mouse_event();


      virtual float get_dpi_for_window();


      virtual float point_dpi(float points);

      virtual float y_dpi(float y);
      virtual float x_dpi(float x);

      virtual float dpiy(float y);
      virtual float dpix(float x);


      virtual void update_screen();
      virtual void window_show();


      //virtual void activate_top_parent();

      ///virtual bool is_same_window(const ::windowing::window * pwindow) const;

   };


   //using window_map = map < void *, __pointer(window) >;


} // namespace windowing


inline bool operator == (const ::windowing::window & window1, const ::windowing::window & window2)
{

   return window1.get_oswindow() == window2.get_oswindow();

}

inline bool operator != (const ::windowing::window & window1, const ::windowing::window & window2)
{

   return !operator==(window1, window2);

}


