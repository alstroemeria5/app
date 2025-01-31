#include "framework.h"
#include "axis/user/_user.h"
#include "acme/constant/timer.h"


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

      install_simple_ui_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_set_focus, pchannel, this, &list_box::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &list_box::_001OnKillFocus);
      MESSAGE_LINK(e_message_close, pchannel, this, &list_box::on_message_close);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &list_box::_001OnMouseActivate);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &list_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up, pchannel, this, &list_box::on_message_key_up);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &list_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_non_client_left_button_down, pchannel, this, &list_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &list_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &list_box::on_message_middle_button_down);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &list_box::on_message_right_button_down);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &list_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &list_box::on_message_show_window);

   }


   void list_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      if (m_pcombo == nullptr)
      {

         return;

      }

      ::rectangle rectClipBox;

      pgraphics->get_clip_box(rectClipBox);

      pgraphics->SelectClipRgn(nullptr);

      _001OnDrawComboList(pgraphics);

   }


   void list_box::_001OnDrawComboList(::draw2d::graphics_pointer & pgraphics)
   {

      ::count iListItemCount = m_pcombo->_001GetListCount();

      string strItem;

      ::rectangle rectangleClient;

      layout().get_client_rect(rectangleClient, ::user::e_layout_design);

      ::draw2d::brush_pointer brBk(e_create);

      brBk->create_solid(argb(230, 255, 255, 255));

      pgraphics->set(brBk);

      pgraphics->fill_rectangle(rectangleClient);

      ::rectangle rectItem;

      //point p = pgraphics->GetViewportOrg();

      rectItem = rectangleClient;

      rectItem.bottom = rectangleClient.top;

      if (m_pcombo->m_bEdit)
      {

         rectItem.bottom += _001GetItemHeight();

      }

      auto pointCursor = psession->get_cursor_position();

      screen_to_client(&pointCursor, ::user::e_layout_design);

      pgraphics->set_font(this, ::user::e_element_none);

      auto itemHover = hover_item();

      index iCurSel = current_item();

      ::draw2d::brush_pointer br(e_create);

      for (index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectItem.top = rectItem.bottom;

         rectItem.bottom = rectItem.top + _001GetItemHeight();

         color32_t crBk;

         color32_t color32;

         string strDebug;

         if (itemHover == iItem)
         {

            strDebug += "hover;";

            if (iItem == iCurSel)
            {

               //crBk = _001GetColor(::user::color_list_item_background_selected_hover);

               //color32 = _001GetColor(::user::color_list_item_text_selected_hover);

               crBk = argb(255, 120, 190, 220);

               color32 = argb(255, 255, 255, 255);

               strDebug += "sel;";

            }
            else
            {

               crBk = argb(255, 235, 245, 255);

               color32 = argb(255, 0, 0, 0);

            }

         }
         else if (iItem == iCurSel)
         {

            strDebug += "sel;";

            crBk = argb(255, 120, 150, 190);

            color32 = argb(255, 255, 255, 255);

         }
         else
         {

            crBk = argb(255, 255, 255, 255);

            color32 = argb(255, 0, 0, 0);

         }

         brBk->create_solid(crBk);

         br->create_solid(color32);

         pgraphics->set(brBk);

         pgraphics->fill_rectangle(rectItem);

         m_pcombo->_001GetListText(iItem, strItem);

         pgraphics->set(br);

         auto rectText = rectItem;

         rectText.deflate(m_iPadding);

#ifdef _DEBUG

         strItem += strDebug;

#endif

         pgraphics->draw_text(strItem, rectText, 0);

      }

      //color32_t crBorder = _001GetColor(::user::color_border);

      color32_t crBorder = argb(255, 0, 0, 0);

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, crBorder);

      pgraphics->set(pen);

      rectangleClient.deflate(0, 0, 1, 1);

      pgraphics->draw_rectangle(rectangleClient);

   }


   ::write_text::font_pointer list_box::get_font(style *pstyle, enum_element eelement, estate estate) const
   {

      if (m_pcombo)
      {

         auto pfont = m_pcombo->get_font(pstyle, eelement, estate);

         if (pfont)
         {

            return pfont;

         }

      }

      //if (pstyle)
      //{

      //   if (pstyle->m_pfontCombo)
      //   {

      //      return pstyle->m_pfontCombo;

      //   }
      //   else if (pstyle->m_pfont)
      //   {

      //      return pstyle->m_pfont;

      //   }

      //}

      //return nullptr;

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void list_box::query_full_size(::draw2d::graphics_pointer& pgraphics, LPSIZE32 psize)
   {

      synchronous_lock synchronouslock(mutex());

      pgraphics->set_font(this, ::user::e_element_none);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      string strItem;

      ::size size;

      psize->cx = 0;

      m_iItemHeight = 0;

      ::count cListCount = m_pcombo->_001GetListCount();

      for (index i = 0; i < cListCount; i++)
      {

         m_pcombo->_001GetListText(i, strItem);

         size = pgraphics->get_text_extent(strItem);

         size.cx += m_iPadding * 2;

         if (size.cx > psize->cx)
         {

            psize->cx = size.cx;

         }

         if (size.cy > m_iItemHeight)
         {

            m_iItemHeight = size.cy;

            if (size.cy != 18)
            {

               //output_debug_string("\nCOMBO LIST ITEM HEIGHT != 18\n");

            }

         }

      }

      m_iItemHeight += 4;

      int iAddUp = 0;

      if (m_pcombo->m_bEdit)
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

      psize->cy = (::i32)(_001GetItemHeight() * (m_pcombo->_001GetListCount() + iAddUp));

      psize->cx += m_iBorder * 2;

      auto rectComboClient = m_pcombo->get_client_rect();

      psize->cx = maximum(psize->cx, rectComboClient.width());

   }


   void list_box::on_change_combo_sel(index iSel)
   {

   }


   i32 list_box::_001GetItemHeight() const
   {

      return m_iItemHeight + m_iPadding * 2;

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

   bool list_box::keyboard_focus_is_focusable()
   {

      return true;

   }


   bool list_box::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      if (is_window_visible(::user::e_layout_sketch))
      {

         display(false);

         set_need_redraw();

         post_redraw();

         if (m_pcombo != nullptr && m_pcombo->is_window_visible(::user::e_layout_sketch))
         {

            m_pcombo->SetFocus();

         }

      }

      return true;

   }


   bool list_box::pre_create_window(::user::system * pusersystem)
   {

      if (pusersystem->m_createstruct.style & WS_BORDER)
      {

         pusersystem->m_createstruct.style &= ~WS_BORDER;

      }

      pusersystem->m_createstruct.dwExStyle |= WS_EX_LAYERED;
      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOOLWINDOW;
      pusersystem->m_createstruct.dwExStyle |= WS_EX_TOPMOST;
      //pusersystem->m_createstruct.dwExStyle |= WS_EX_NOACTIVATE;

      return true;
   }


   void list_box::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

#ifdef WINDOWS

         keyboard_set_focus();

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

      __pointer(::user::interaction) pActive = (pactivate->m_nState == WA_INACTIVE ? pactivate->m_pWndOther : this);

      if (pactivate->m_nState == WA_INACTIVE)
      {

         auto pointCursor = psession->get_cursor_position();

         m_pcombo->screen_to_client(&pointCursor, ::user::e_layout_sketch);

         //if(m_pcombo->hit_test(pointCursor) != e_element_drop_down)
         //{

         //   m_pcombo->_001ShowDropDown(false);

         //}




         //if(pActive != m_puiDeactivateTogether)
         //{

         //   ::experience::frame_window * pset = m_puiDeactivateTogetherSet;

         //   if(pset != nullptr)
         //   {

         //      pset->SetActiveFlag(false);

         //   }

         //}



      }
      else
      {

         psession->set_keyboard_focus(this);


      }

   }


   void list_box::_001OnMouseActivate(::message::message * pmessage)
   {

      __pointer(::message::mouse_activate) pactivate(pmessage);

      pactivate->m_lresult = MA_NOACTIVATE;

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

            pelemental->keyboard_set_focus();

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

            pelemental->keyboard_set_focus();

         }

      }

   }


   void list_box::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void list_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      auto point = screen_to_client(pmouse->m_point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      psession->user()->set_mouse_focus_LButtonDown(this);

      m_itemLButtonDown = -1;

      if (rectangleClient.contains(point))
      {

         m_itemLButtonDown = hit_test(pmouse);

         SetCapture();

      }

      pmessage->m_bRet = true;

   }


   void list_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      auto point = screen_to_client(pmouse->m_point, e_layout_sketch);

      auto rectangleClient = get_client_rect();

      psession->user()->set_mouse_focus_LButtonDown(this);

      ReleaseCapture();

      if (rectangleClient.contains(point))
      {

         auto itemHit = hit_test(pmouse);

         if (itemHit == m_itemLButtonDown)
         {

            if (::is_set(m_pcombo))
            {

               m_pcombo->_001ShowDropDown(false);

            }

            ::user::control_event ev;

            ev.m_puserinteraction = this;

            ev.m_id = m_id;

            ev.m_eevent = ::user::e_event_after_change_cur_sel;

            ev.m_actioncontext = ::e_source_user;

            ev.m_item = itemHit;

            route_control_event(&ev);

         }

      }



      pmouse->m_bRet = true;

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

      return m_pcombo->current_item();

   }


   item list_box::hover_item()
   {

      return ::user::interaction::hover_item();

   }


   void list_box::on_hit_test(::user::item & item)
   {

      if (m_pcombo == nullptr)
      {

         item = ::user::e_element_none;

         return;

      }

      ::count iItemCount = m_pcombo->_001GetListCount();

      auto rectangleClient = get_client_rect();

      ::rectangle rectItem = rectangleClient;

      int iAddUp = 0;

      if (m_pcombo->m_bEdit)
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


   void list_box::on_drop_down(const ::rectangle & rectWindow, const ::size & sizeFull)
   {

      ::rectangle rectMonitor;

      psession->get_best_monitor(rectMonitor, rectWindow);

      ::rectangle rectList;

      rectList.left = rectWindow.left;
      rectList.right = rectWindow.left + maximum(rectWindow.width(), sizeFull.cx);
      rectList.top = rectWindow.bottom;
      rectList.bottom = rectWindow.bottom + sizeFull.cy;

      if (rectList.bottom > rectMonitor.bottom -m_iBorder)
      {

         rectList.bottom = rectMonitor.bottom - m_iBorder;

         ::rectangle rectListOver;

         rectListOver.left = rectWindow.left;
         rectListOver.right = rectWindow.left + sizeFull.cx;
         rectListOver.bottom = rectWindow.top;
         rectListOver.top = rectWindow.top - sizeFull.cy;

         if (rectListOver.top < rectMonitor.top + m_iBorder)
         {

            rectListOver.top = rectMonitor.top + m_iBorder;

            if (rectListOver.height() > rectList.height())
            {

               rectList = rectListOver;

            }

         }

      }

      if (rectList.right > rectMonitor.right - m_iBorder)
      {

         rectList.offset(rectMonitor.right - (rectList.right-m_iBorder), 0);

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

      if (!is_window())
      {

         ::user::system createstruct(0, nullptr, "list_box");

         pusersystem->m_createstruct.set_rect(::rectangle(rectList).inflate(m_iBorder));

         if (!create_window_ex(createstruct))
         {

            m_pcombo->m_plist.release();

            __throw(error_resource);

         }

         SetOwner(m_pcombo);

      }
      else
      {

         place(::rectangle(rectList).inflate(m_iBorder));

      }

      order_top_most();

      display(e_display_normal);

      set_need_redraw();

      set_layout_ready();

      post_redraw();

   }


   void list_box::_on_show_window()
   {

      ::user::interaction::_on_show_window();

      if (is_screen_visible(layout().sketch().display()))
      {

         {

            synchronous_lock synchronouslock(psession->mutex());

            auto & preference = psession->m_uiptraToolWindow.add_new();

            psession->__refer(preference, this);

         }

         keyboard_set_focus();

      }
      else
      {

         {

            synchronous_lock synchronouslock(psession->mutex());

            ::index iFind = psession->m_uiptraToolWindow.predicate_find_first([this](auto& p) {return p.get() == this; });

            if (__found(iFind))
            {

               psession->__release(psession->m_uiptraToolWindow[iFind]);

               psession->m_uiptraToolWindow.erase_at(iFind);

            }

         }

      }

   }



} // namespace user




