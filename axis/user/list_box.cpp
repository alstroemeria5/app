#include "framework.h"
#include "axis/user/_user.h"
#include "acme/constant/timer.h"


#define DEBUG_LIST_ITEM_DRAWING 0


namespace user
{


   list_box::list_box()
   {

      user_combo_list_common_construct();

   }


   list_box::~list_box()
   {

   }


   void list_box::user_combo_list_common_construct()
   {

      defer_create_mutex();

      m_bClickDefaultMouseHandling = true;

      m_bTransparent = true;

      m_bHoverDefaultMouseHandling = true;

      m_bPendingKillFocusHiding = false;

      m_ewindowflag += e_window_flag_satellite_window;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      m_bComboList = true;

      m_puiDeactivateTogether = nullptr;

      m_pcombo = nullptr;

      m_iPadding = 2;

      m_iBorder = 0;

      m_iMinListItemCount = 8;

      m_bMovingComboBox = false;

   }


   void list_box::install_message_routing(::channel * pchannel)
   {

      ::user::scroll_base::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &list_box::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &list_box::on_message_destroy);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &list_box::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &list_box::_001OnKillFocus);
      MESSAGE_LINK(e_message_close, pchannel, this, &list_box::on_message_close);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &list_box::_001OnMouseActivate);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &list_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &list_box::on_message_key_up);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, (::user::interaction *)this, &interaction::on_message_left_button_down);
      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &list_box::on_message_middle_button_down);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &list_box::on_message_right_button_down);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &list_box::on_message_show_window);

   }


   void list_box::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      add_control_event_handler(this);

   }


   bool list_box::on_set_owner(::user::primitive * pprimitive)
   {

      auto puserinteractionOwner = pprimitive->get_owner();

      if(puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_window();

         if (puserinteractionHost)
         {

            auto pimpl = puserinteractionHost->m_pimpl.cast<::user::interaction_impl>();

            if (pimpl)
            {

               synchronous_lock synchronouslock(pimpl->mutex());

               pimpl->m_userinteractionaHideOnConfigurationChange.add_unique_interaction(this);

            }

         }

      }

      return true;

   }


   bool list_box::_001GetListText(index iSel, string& str) const
   {

      str.Empty();

      if (iSel < 0)
      {

         return false;

      }

      if (iSel >= m_straList.get_count())
         return false;

      str = m_straList[iSel];

      return true;

   }


   index list_box::_001FindListText(const string& str) const
   {


      //index combo_box::_001FindListText(const ::string & str) const
      //{

      //   ::count ca = _001GetListCount();

      //   string strItem;

      //   for(index i = 0; i < ca; i++)
      //   {

      //      _001GetListText(i,strItem);

      //      if(m_bCaseSensitiveMatch)
      //      {

      //         if(str.compare(strItem) == 0)
      //            return i;

      //      }
      //      else
      //      {

      //         if(str.compare_ci(strItem) == 0)
      //            return i;

      //      }

      //   }

      //   return -1;

      //}

      if (m_bCaseSensitiveMatch)
      {

         return m_straList.find_first(str);

      }
      else
      {

         return m_straList.find_first_ci(str);

      }

   }


   index list_box::_001GetListCount() const
   {

      return m_straList.get_count();

   }


   index list_box::add_string(const ::string & pszString, uptr dwItemData)
   {

      m_straList.add(pszString);

      m_straValue.add(__str(dwItemData));

      return m_straList.get_upper_bound();

   }


   index list_box::add_string(const ::string & pszString, const string& strValue)
   {

      m_straList.add(pszString);

      m_straValue.add(strValue);

      return m_straList.get_upper_bound();

   }


   index list_box::delete_string(index iIndex)
   {

      if (iIndex < 0 || iIndex >= _001GetListCount())
      {

         return -1;

      }

      m_straList.erase_at(iIndex);

      m_straValue.erase_at(iIndex);

      return iIndex;

   }


   index list_box::insert_string(index iIndex, const ::string & pszString)
   {

      if (iIndex < 0)
      {

         return -1;

      }

      m_straList.insert_at(iIndex, pszString);

      m_straValue.insert_at(iIndex, "");

      return iIndex;

   }


   void list_box::reset_content()
   {

      synchronous_lock synchronouslock(mutex());

      m_straList.erase_all();

      m_straValue.erase_all();

      m_itemCurrent = -1;

      m_itemHover = -1;

   }


   void list_box::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_click)
      {

         if(pevent->m_puserinteraction == this)
         {

            if (m_pcombo)
            {

               m_pcombo->set_current_item(pevent->m_item, pevent->m_actioncontext);

               m_pcombo->ShowDropDown(false);

            }
            else
            {

               set_current_item(pevent->m_item, pevent->m_actioncontext);

            }

            return;

         }

      }

   }


   void list_box::on_message_destroy(::message::message * pmessage)
   {

      auto puserinteractionOwner = get_owner();

      if(puserinteractionOwner)
      {

         auto puserinteractionHost = puserinteractionOwner->get_host_window();

         if(puserinteractionHost)
         {

            auto pimpl = puserinteractionHost->m_pimpl.cast<::user::interaction_impl>();

            if (pimpl)
            {

               synchronous_lock synchronouslock(pimpl->mutex());

               pimpl->m_userinteractionaHideOnConfigurationChange.erase_interaction(this);

            }

         }

      }

      pmessage->previous();

   }


   void list_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      //if (m_pcombo == nullptr)
      //{

      //   return;

      //}

      ::rectangle_f64 rectClipBox;

      pgraphics->get_clip_box(&rectClipBox);

      pgraphics->reset_clip();

      _001OnDrawComboList(pgraphics);

   }


   void list_box::_001OnDrawComboList(::draw2d::graphics_pointer & pgraphics)
   {

      ::count iListItemCount = _001GetListCount();

      string strItem;

      ::rectangle_i32 rectangleClient;

      layout().get_client_rect(rectangleClient, ::user::e_layout_design);

      status < ::color::color > colorBackground;

      status < ::color::color > colorText;

      auto pstyle = get_style(pgraphics);

      colorBackground = get_color(pstyle, ::user::e_element_background);

      ::draw2d::brush_pointer brBk(e_create);

      brBk->create_solid(colorBackground);

      pgraphics->set(brBk);

      pgraphics->fill_rectangle(rectangleClient);

      ::rectangle_i32 rectItem;

      rectItem = rectangleClient;

      rectItem.bottom = rectangleClient.top;

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         rectItem.bottom += _001GetItemHeight();

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = pwindowing->get_cursor_position();

      screen_to_client(pointCursor, ::user::e_layout_design);

      pgraphics->set_font(this, ::user::e_element_none);

      auto itemHover = hover_item();

      auto itemCurrent = current_item();

      ::draw2d::brush_pointer br(e_create);

      for (index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectItem.top = rectItem.bottom;

         rectItem.bottom = rectItem.top + _001GetItemHeight();

#if DEBUG_LIST_ITEM_DRAWING

         string strDebug;

#endif

         ::user::e_state estate = ::user::e_state_none;

         if (itemHover == iItem)
         {

#if DEBUG_LIST_ITEM_DRAWING

            strDebug += "hover;";

#endif

            estate += ::user::e_state_hover;

         }

         if (itemCurrent == iItem)
         {

#if DEBUG_LIST_ITEM_DRAWING

            strDebug += "selected;";

#endif

            estate += ::user::e_state_selected;

         }

         colorBackground = get_color(pstyle, ::user::e_element_item_background, estate);

         colorText = get_color(pstyle, ::user::e_element_item_text, estate);

         brBk->create_solid(colorBackground);

         br->create_solid(colorText);

         pgraphics->set(brBk);

         pgraphics->fill_rectangle(rectItem);

         _001GetListText(iItem, strItem);

         pgraphics->set(br);

         auto rectText = rectItem;

         rectText.deflate(m_iPadding);

#if DEBUG_LIST_ITEM_DRAWING


         strItem += strDebug;

#endif

         pgraphics->draw_text(strItem, rectText);

      }

      ::color::color crBorder = argb(255, 0, 0, 0);

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, crBorder);

      pgraphics->set(pen);

      rectangleClient.deflate(0, 0, 1, 1);

      pgraphics->draw_rectangle(rectangleClient);

   }


   ::write_text::font_pointer list_box::get_font(style *pstyle, enum_element eelement, ::user::enum_state estate) const
   {

      if (m_pcombo)
      {

         auto pfont = m_pcombo->get_font(pstyle, eelement, estate);

         if (pfont)
         {

            return pfont;

         }

      }

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void list_box::query_full_size(::draw2d::graphics_pointer& pgraphics, SIZE_I32 * psize)
   {

      synchronous_lock synchronouslock(mutex());

      pgraphics->set_font(this, ::user::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      string strItem;

      ::size_f64 size;

      psize->cx = 0;

      m_dItemHeight = 0.;

      ::count cListCount = _001GetListCount();

      for (index i = 0; i < cListCount; i++)
      {

         _001GetListText(i, strItem);

         size = pgraphics->get_text_extent(strItem);

         size.cx += m_iPadding * 2;

         if (size.cx > psize->cx)
         {

            psize->cx = (::i32)size.cx;

         }

         if (size.cy > m_dItemHeight)
         {

            m_dItemHeight = (::i32)size.cy;

            if (size.cy != 18)
            {

               //output_debug_string("\nCOMBO LIST ITEM HEIGHT != 18\n");

            }

         }

      }

      m_dItemHeight += 4.0;

      int iAddUp = 0;

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      if (m_iMinListItemCount > 0)
      {

         auto iAddUp2 = cListCount - m_iMinListItemCount;

         if (iAddUp2 > 0)
         {

            iAddUp = (decltype(iAddUp))iAddUp2;

         }

      }

      psize->cy = (::i32)(_001GetItemHeight() * (_001GetListCount() + iAddUp));

      psize->cx += m_iBorder * 2;

      //auto rectComboClient = get_client_rect();

      //psize->cx = maximum(psize->cx, rectComboClient.width());
      //psize->cx = maximum(psize->cx, rectComboClient.width());

   }


   void list_box::on_change_combo_sel(index iSel)
   {

   }


   i32 list_box::_001GetItemHeight() const
   {

      return (::i32)(m_dItemHeight + m_iPadding * 2);

   }


   void list_box::_001EnsureVisible(index iItem)
   {

      if (m_pscrollbarVertical != nullptr
         && m_scrolldataVertical.m_bScroll
         && iItem >= 0 && iItem < m_pcombo->_001GetListCount())
      {

         m_pointScroll.y = (::i32) (iItem * _001GetItemHeight());

      }
      else
      {

         m_pointScroll.y = 0;

      }

   }


   void list_box::_001OnTimer(::timer* ptimer)
   {
   
      if (ptimer->m_etimer == e_timer_kill_focus)
      {

         if (m_bPendingKillFocusHiding)
         {
            
            m_bPendingKillFocusHiding = false;

            hide();

            set_need_redraw();

            post_redraw();


         }

         KillTimer(e_timer_kill_focus);

      }

      ::user::scroll_base::_001OnTimer(ptimer);
   
   }


   void list_box::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      query_full_size(pgraphics, m_sizeFull);

   }


   bool list_box::keyboard_focus_is_focusable() const
   {

      return true;

   }


   bool list_box::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      if (is_window_visible(::user::e_layout_sketch))
      {

         display(e_display_hide);

         set_need_redraw();

         post_redraw();

         if (m_pcombo != nullptr && m_pcombo->is_window_visible(::user::e_layout_sketch))
         {

            m_pcombo->set_keyboard_focus();

         }

      }

      return true;

   }


   bool list_box::pre_create_window(::user::system * pusersystem)
   {

//#ifdef WINDOWS_DESKTOP
//
//      if (pusersystem->m_createstruct.style & WS_BORDER)
//      {
//
//         pusersystem->m_createstruct.style &= ~WS_BORDER;
//
//      }
//
//      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOOLWINDOW;
//
//      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOPMOST;
//
//#endif
//
//      pusersystem->m_createstruct.dwExStyle |= WS_EX_LAYERED;
      
      //pusersystem->m_createstruct.dwExStyle |= WS_EX_NOACTIVATE;

      return true;

   }


   void list_box::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

#ifdef WINDOWS

         set_keyboard_focus();

#endif

      }
      else
      {

         output_debug_string("list_box hide");

      }

   }


   void list_box::_001OnKillFocus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         bool bGoingToShow = m_pcombo->m_millisShowComboList.elapsed() < 300_ms;

         if (!bGoingToShow)
         {

            m_millisKillFocus.Now();

            m_bPendingKillFocusHiding = true;

            set_timer(e_timer_kill_focus, 300_ms);

            //__pointer(::message::kill_focus) pkillfocus(pmessage);

            //oswindow oswindowThis = get_safe_handle();

            //oswindow oswindowNew = pkillfocus->m_oswindowNew;

            //if (oswindowThis != oswindowNew && !m_bMovingComboBox)
            //{

            //   if (layout().sketch().is_screen_visible())
            //   {

            //      m_millisLastVisibilityChange.Now();

            //      hide();

            //      set_need_redraw();

            //      post_redraw();

            //      m_pcombo->keyboard_set_focus();

            //      m_pcombo->get_wnd()->SetActiveWindow();

            //   }
            //   else
            //   {

            //      //output_debug_string("A phantom is loosing focus. What a pitty!!");

            //   }

            //}

            //pkillfocus->m_bRet = true;

            //pkillfocus->m_lresult = 0;

         }

      }

   }


   void list_box::_001OnSetFocus(::message::message * pmessage)
   {

      if (m_pcombo)
      {

         m_pcombo->m_itemHover = m_pcombo->m_itemCurrent;

         set_need_redraw();

      }

   }



   void list_box::_001OnActivate(::message::message * pmessage)
   {

      __pointer(::message::activate) pactivate(pmessage);

      __pointer(::user::interaction) pActive = (pactivate->m_eactivate == e_activate_inactive ? pactivate->m_pWndOther : this);

      if (pactivate->m_eactivate == e_activate_inactive)
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pointCursor = pwindowing->get_cursor_position();

         m_pcombo->screen_to_client(pointCursor, ::user::e_layout_sketch);

      }
      else
      {

         set_keyboard_focus();


      }

   }


   void list_box::_001OnMouseActivate(::message::message * pmessage)
   {

      __pointer(::message::mouse_activate) pactivate(pmessage);

      pactivate->m_lresult = e_mouse_activate_no_activate;

      pactivate->m_bRet = true;


   }


   void list_box::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_pkey;

      if (pkey->m_ekey == ::user::e_key_escape)
      {

         m_pcombo->ShowDropDown(false);

      }
      else if (pkey->m_ekey == ::user::e_key_tab)
      {

         m_pcombo->ShowDropDown(false);

         __pointer(::user::primitive) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }


      }
      else if (pkey->m_ekey == ::user::e_key_down)
      {

         m_pcombo->m_itemHover = minimum(m_pcombo->m_itemHover + 1, m_pcombo->_001GetListCount() - 1);

      }
      else if (pkey->m_ekey == ::user::e_key_up)
      {

         m_pcombo->m_itemHover = maximum(m_pcombo->m_itemHover - 1, 0);

      }
      else if (pkey->m_ekey == ::user::e_key_return)
      {

         m_pcombo->set_current_item(m_pcombo->m_itemHover, ::e_source_user);

         m_pcombo->ShowDropDown(false);

         __pointer(::user::primitive) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->set_keyboard_focus();

         }

      }

   }


   void list_box::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void list_box::on_message_middle_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      auto point = pmouse->m_point;

      screen_to_client(point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      if (rectangleClient.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   void list_box::on_message_right_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      auto point = pmouse->m_point;

      screen_to_client(point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      if (rectangleClient.contains(point))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pmessage->m_bRet = true;

   }


   void list_box::on_message_mouse_move(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
      //auto pmouse = pmessage->m_pmouse;

      //pmessage->m_bRet = true;

      //auto point = screen_to_client(pmouse->m_point);

      //auto itemHover = hit_test(pmouse);

      //if (itemHover != m_pcombo->m_itemHover)
      //{

      //   m_pcombo->m_itemHover = itemHover.m_iItem;

      //   set_need_redraw();

      //}

   }


   void list_box::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      display(e_display_none);

      set_need_redraw();

   }


   item list_box::current_item()
   {

      return ::user::interaction::current_item();

   }


   item list_box::hover_item()
   {

      return ::user::interaction::hover_item();

   }


   void list_box::on_hit_test(::user::item & item)
   {

      /*if (m_pcombo == nullptr)
      {

         item = ::user::e_element_none;

         return;

      }*/

      ::count iItemCount = _001GetListCount();

      auto rectangleClient = get_client_rect();

      ::rectangle_i32 rectItem = rectangleClient;

      int iAddUp = 0;

      if (m_pcombo && m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      for (::index iItem = 0; iItem < iItemCount; iItem++)
      {

         rectItem.top = rectangleClient.top + (_001GetItemHeight() * (int) (iAddUp + iItem));

         rectItem.bottom = rectItem.top + _001GetItemHeight();

         if (rectItem.contains(item.m_pointHitTest))
         {

            item  = {::user::e_element_item, iItem };

            return;

         }


      }

      rectItem.top = rectangleClient.top;

      rectItem.bottom = rectItem.top + _001GetItemHeight();

      if (rectItem.contains(item.m_pointHitTest))
      {

         item = e_element_search_edit;

         return;

      }

      item = e_element_none;

   }


   bool list_box::has_pending_graphical_update()
   {

      return m_bNeedRedraw;

   }


   void list_box::on_drop_down(const ::rectangle_i32 & rectWindow, const ::size_i32 & sizeFull)
   {

      {

         lock_sketch_to_design lockSketchToDesign(this);

         ::rectangle_i32 rectMonitor;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         ::index i = pdisplay->get_best_monitor(rectMonitor, rectWindow);

         ::rectangle_i32 rectList;

         rectList.left = rectWindow.left;
         rectList.right = rectWindow.left + maximum(rectWindow.width(), sizeFull.cx);
         rectList.top = rectWindow.bottom;
         rectList.bottom = rectWindow.bottom + sizeFull.cy;

         if (i < 0)
         {

            m_pcombo->get_parent()->get_window_rect(rectMonitor);

         }

         if (rectList.bottom > rectMonitor.bottom - m_iBorder)
         {

            rectList.bottom = rectMonitor.bottom - m_iBorder;

            ::rectangle_i32 rectListOver;

            rectListOver.left = rectList.left;
            rectListOver.right = rectList.right;
            rectListOver.bottom = rectWindow.top;
            rectListOver.top = rectWindow.top - sizeFull.cy;

            if (rectListOver.top < rectMonitor.top + m_iBorder)
            {

               rectListOver.move_to(rectListOver.left, rectMonitor.top);

            }

            rectList = rectListOver;

         }

         if (rectList.right > rectMonitor.right - m_iBorder)
         {

            rectList.offset(rectMonitor.right - (rectList.right - m_iBorder), 0);

         }

         if (rectList.left < rectMonitor.left)
         {

            rectList.move_left_to(0);

         }

         m_pcombo->m_itemHover = current_item();

         if (!m_pcombo->m_itemHover.is_set())
         {

            m_pcombo->m_itemHover = 0;

         }

         _001EnsureVisible(m_pcombo->m_itemHover);

         if (i < 0)
         {

            m_pcombo->get_parent()->screen_to_client(rectList);

         }

         if (!is_window())
         {

            m_puserinteractionOwner = m_pcombo;

            order_top_most();

            set_tool_window();

            m_bTransparent = true;

            display();

            place(::rectangle_i32(rectList).inflate(m_iBorder));

            if (!create_interaction(i >= 0 ? nullptr : m_pcombo->get_parent()))
            {

               m_pcombo->m_plistbox.release();

               __throw(error_resource);

            }

            set_owner(m_pcombo);

         }
         else
         {

            place(::rectangle_i32(rectList).inflate(m_iBorder));

         }

         order_top_most();

         display(e_display_normal);

         set_need_layout();

         set_need_redraw();

      }

      post_redraw();

   }


   ::e_status list_box::set_current_item(const ::user::item & item, const ::action_context & context)
   {

      if(m_pcombo)
      {

         auto estatus = m_pcombo->set_current_item(item, context);

         if(!estatus)
         {

            return estatus;

         }

         return estatus;

      }
      else
      {

         auto estatus = ::user::scroll_base::set_current_item(item, context);

         if(!estatus)
         {

            return estatus;

         }

         return estatus;

      }

   }


   void list_box::set_current_item_by_data(uptr u, const ::action_context& context)
   {

      index iSel = m_straValue.find_first(__str(u));

      if (iSel < 0)
      {

         return;

      }

      set_current_item(iSel, context);

   }


   void list_box::set_current_item_by_string_value(const string& strValue, const ::action_context& context)
   {

      index iSel = m_straValue.find_first(strValue);

      if (iSel < 0)
      {

         return;

      }

      set_current_item(iSel, context);

   }


   string list_box::get_current_item_string_value()
   {

      index iSel = current_item();

      if (iSel < 0)
      {

         return "";

      }

      string str = m_straValue[iSel];

      return str;

   }


   void list_box::_on_show_window()
   {

      ::user::interaction::_on_show_window();

      if (m_pcombo)
      {

         if (is_screen_visible(layout().sketch().display()))
         {

            {

               auto psession = get_session();

               synchronous_lock synchronouslock(psession->mutex());

               auto pinteraction = __create_new < ::user::interaction >();

               auto puser = psession->user();

               puser->m_uiptraToolWindow.add(pinteraction);

            }

            set_keyboard_focus();

         }
         else
         {

            {

               auto psession = get_session();

               synchronous_lock synchronouslock(psession->mutex());

               auto puser = psession->user();

               ::index iFind = puser->m_uiptraToolWindow.predicate_find_first([this](auto& p) {return p.get() == this; });

               if (__found(iFind))
               {

                  puser->m_uiptraToolWindow.erase_at(iFind);

               }

            }

         }

      }

   }


} // namespace user



