#include "framework.h"
#include "axis/user/_user.h"


namespace user
{


   combo_box::combo_box()
   {

      user_combo_box_common_construct();

   }


   void combo_box::user_combo_box_common_construct()
   {

      m_econtroltype          = e_control_type_combo_box;
      m_typeListBox           = __type(::user::list_box);
      m_estyle                = style_simply;
      m_bEdit                 = true;
      m_edatamode             = data_mode_opaque;
      m_bMultiLine            = false;

   }


   combo_box::~combo_box()
   {

      if(m_plistbox.is_set())
      {

         if(m_plistbox->is_window())
         {

            m_plistbox->destroy_window();

         }

      }

   }


   void combo_box::install_message_routing(::channel * pchannel)
   {

      //if(m_bEdit)
      {

         ::user::plain_edit::install_message_routing(pchannel);

      }
      //else
      {

        // ::user::interaction::install_message_routing(pchannel);

      }

      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &combo_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &combo_box::on_message_mouse_leave);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &combo_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &combo_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &combo_box::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_key_down,pchannel,this,&combo_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up,pchannel,this,&combo_box::on_message_key_up);
      //MESSAGE_LINK(e_message_set_focus,pchannel,this,&combo_box::_001OnSetFocus);
      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &combo_box::_001OnKillFocus);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &combo_box::on_message_show_window);
      MESSAGE_LINK(e_message_move, pchannel, this, &combo_box::on_message_move);

   }


   void combo_box::_001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics)
   {

      string strText;

      if (m_bEdit)
      {

         _001GetText(strText);

      }
      else
      {

         _001GetListText(current_item(), strText);

      }

      ::rectangle_i32 rectangleClient;

      layout().get_client_rect(rectangleClient, ::user::e_layout_design);
      //::user::e_::color::color colorText = color_text;

      ::color::color colorText(0, 0, 0, 255);

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::color::color(192,192,192, 255);

      //      }
      //      else
      //      {

      //         colorText = ::color::color(255, 255, 255, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::color::color(80, 80, 80, 255);;

      //      }
      //      else
      //      {

      //         colorText = ::color::color(80, 80, 80, 255);;

      //      }

      //   }

      //}

      //if(!select_text_color(pgraphics, colorText))
      //{

         pgraphics->set_text_color(colorText);

      //}

      ::rectangle_i32 rectText;

      get_element_rect(rectText, e_element_text);

      pgraphics->set_font(this, ::user::e_element_none);

      ::e_align ealign = e_align_left_center;

      pgraphics->draw_text(strText, rectText, ealign);

   }


   enum_input_type combo_box::preferred_input_type() const
   {

      if (m_bEdit)
      {

         return e_input_type_text;

      }
      else
      {

         return e_input_type_list;

      }

   }


   void combo_box::get_simple_drop_down_open_arrow_polygon(point_f64_array& pointa)
   {

      ::rectangle_i32 rectDropDown;

      get_element_rect(rectDropDown, e_element_drop_down);

      i32 cx = rectDropDown.width() / 3;

      i32 cy = cx * 2 / 3;

      ::point_i32 pointCenter = rectDropDown.center();

      pointa.add(pointCenter.x - cx / 2, pointCenter.y - cy / 2);

      pointa.add(pointCenter.x + cx / 2, pointCenter.y - cy / 2);

      pointa.add(pointCenter.x, pointCenter.y + cy / 2);

   }


   void combo_box::_001OnDrawCombo(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::draw2d::brush_pointer br(e_create);

      //if(m_bEdit)
      {

         ::user::plain_edit::_001OnDraw(pgraphics);

      }
//      else
//      {
//
//         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//         _001OnDrawStaticText(pgraphics);
//
//      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectDropDown;

      get_element_rect(rectDropDown, e_element_drop_down);

      ::rectangle_i32 rectDropIn(rectDropDown);

      //::user::e_::color::color colorDropDown = color_button_background_disabled;
      ::color::color colorDropDown = ::color::color(127, 127, 127, 255);

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::color::color(80, 80, 180, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::color::color(100, 100, 200, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::color::color(200, 200, 250, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::color::color(192, 192, 192, 255);

      //      }

      //   }

      //}
      //else
      {

         bool bHasFocus = has_keyboard_focus();

         if(bHasFocus)
         {

            if (m_itemHover.is_set())
            {

               colorDropDown = ::color::color(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::color::color(200, 200, 250, 255);

            }

         }
         else
         {

            if (m_itemHover.is_set())
            {

               colorDropDown = ::color::color(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::color::color(200, 200, 250, 255);

            }

         }

      }

      ::color::color color(colorDropDown);

      color.hls_rate(0.0, 0.5, 0.1);

      br->create_solid(color);

      pgraphics->set(br);

      pgraphics->fill_rectangle(rectDropIn);

      ::draw2d::path_pointer path(e_create);

      point_f64_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      br->create_solid(argb(210, 0, 0, 0));

      pgraphics->set(br);

      pgraphics->fill_polygon(pointa);

   }


   ::write_text::font_pointer combo_box::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate) const
   {

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

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void combo_box::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::plain_edit::_000OnDraw(pgraphics);

   }


   void combo_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

      _001OnDrawCombo(pgraphics);

   }


   void combo_box::_001GetText(string & str) const
   {

      ::user::plain_edit::_001GetText(str);

//      if(m_bEdit)
//      {
//
//         if(!m_itemCurrent.is_set())
//         {
//
//            ::user::plain_edit::_001GetText(str);
//
//         }
//         else
//         {
//
//            _001GetListText(m_itemCurrent, str);
//
//         }
//
//      }
//      else
//      {
//
//         if(!m_itemCurrent.is_set())
//         {
//
//            str = m_strText;
//
//         }
//         else
//         {
//
//            _001GetListText(m_itemCurrent, str);
//
//         }
//
//      }

   }


   void combo_box::_001SetText(const ::string & str, const ::action_context & context)
   {

      //if(m_bEdit)
      //{

         ::user::plain_edit::_001SetText(str, context);

//      }
//      else
//      {
//
//         m_strText = str;
//
//         auto psystem = m_psystem->m_paurasystem;
//
//         auto pdraw2d = psystem->draw2d();
//
//         auto pgraphics = pdraw2d->create_memory_graphics();
//
//         plain_edit_on_after_change_text(pgraphics, context);
//
//      }

   }


   index combo_box::_001GetListCount() const
   {

      return m_plistbox->_001GetListCount();

   }


   bool combo_box::get_element_rect(RECTANGLE_I32 * prectangle, enum_element eelement)

   {

      if(eelement == e_element_text)
      {

         eelement = e_element_combo_edit;

      }

      return interaction::get_element_rect(prectangle, eelement);


   }


   void combo_box::on_hit_test(::user::item & item)
   {

      ::rectangle_i32 rectElement;

      if(get_element_rect(rectElement, e_element_drop_down))
      {

         if (rectElement.contains(item.m_pointHitTest))
         {

            item = e_element_drop_down;

            return;

         }

      }

      auto rectangleClient = get_client_rect(::user::e_layout_sketch);

      if (rectangleClient.contains(item.m_pointHitTest))
      {

         item = e_element_text;

         return;

      }

      item = e_element_none;

   }


   void combo_box::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (!pshowwindow->m_bShow)
      {

         if (m_plistbox.is_set())
         {

            m_plistbox->post_message(e_message_close);

         }

      }

   }


   void combo_box::on_message_move(::message::message * pmessage)
   {

      if (is_drop_down())
      {

         ::rectangle_i32 rectWindow;

         get_window_rect(rectWindow, ::user::e_layout_sketch);

         m_plistbox->on_drop_down(rectWindow, m_sizeFull);

      }

   }


   void combo_box::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_pkey;

      if(pkey->m_ekey == ::user::e_key_down)
      {

         if(!is_drop_down())
         {

            _001ShowDropDown();

         }

      }

   }


   void combo_box::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   bool combo_box::plain_edit_is_enabled()
   {

      return m_bEdit;

   }


   void combo_box::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      pmouse->previous();

      if (is_window_enabled())
      {

         if (!m_bEdit || m_itemHover == e_element_drop_down)
         {

            auto psession = get_session();

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

            pmouse->m_pcursor = pcursor;

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_message_mouse_leave(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      m_itemHover = e_element_none;

      set_need_redraw();

   }


   void combo_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if (is_window_enabled())
      {

         auto eelementHit = hit_test(pmouse);

         if (eelementHit.is_set() && (!m_bEdit || eelementHit == e_element_drop_down))
         {

            millis tickLastVisibilityChangeElapsed;

            if (m_plistbox.is_set())
            {

               tickLastVisibilityChangeElapsed = m_plistbox->m_millisLastVisibilityChange.elapsed();

            }

            if (m_plistbox.is_null() || tickLastVisibilityChangeElapsed > 300_tick)
            {

               _001ToggleDropDown();

            }
            else if (!m_plistbox->layout().sketch().is_screen_visible())
            {

               //output_debug_string("test");

            }

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if (is_window_enabled())
      {

         //auto point = screen_to_client(pmouse->m_point);

         auto eelementHit = hit_test(pmouse);

         if (eelementHit.is_set() && (!m_bEdit || eelementHit == e_element_drop_down))
         {

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_set_keyboard_focus()
   {

   }


   void combo_box::on_kill_keyboard_focus()
   {

      if (m_plistbox != nullptr)
      {

         m_plistbox->post_message(e_message_close);

      }

   }


   void combo_box::_001ToggleDropDown()
   {

      defer_create_list_box();

      if (m_plistbox.is_set())
      {

         _001ShowDropDown(!m_plistbox->is_window_visible(::user::e_layout_sketch));

      }

   }


   void combo_box::_001ShowDropDown(bool bShow)
   {

      if (m_plistbox)
      {

         m_plistbox->m_bPendingKillFocusHiding = false;

      }

      if(bShow)
      {

         m_millisShowComboList.Now();

         defer_create_list_box();

         auto psession = get_session();

         psession->on_show_user_input_popup(m_plistbox);

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics();

         m_plistbox->query_full_size(pgraphics, m_sizeFull);

         ::rectangle_i32 rectWindow;

         get_window_rect(rectWindow, ::user::e_layout_sketch);

         m_plistbox->on_drop_down(rectWindow, m_sizeFull);

      }
      else
      {

         if(m_plistbox.is_set())
         {

            m_plistbox->hide();

            m_plistbox->set_need_redraw();

            m_plistbox->post_redraw();

         }

         set_keyboard_focus();

         set_active_window();

      }

   }


   void combo_box::defer_create_list_box()
   {

      if(!m_plistbox)
      {

         auto plistbox = __id_create < list_box >(m_typeListBox);

         m_plistbox = plistbox;

         if(m_plistbox == nullptr)
         {

            __throw(error_resource);

         }

         m_plistbox->m_pcombo = this;

      }

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient, ::user::e_layout_sketch);

      m_plistbox->m_dItemHeight = minimum(24, rectangleClient.height());

   }


   ::e_status combo_box::set_current_item(const ::user::item & item, const ::action_context & actioncontext)
   {

      auto estatus = ::user::plain_edit::set_current_item(item, actioncontext);

      if(estatus == ::success_none)
      {

         return estatus;

      }

      if(m_plistbox)
      {

         m_plistbox->m_itemCurrent = m_itemCurrent;

      }

      if (!is_window())
      {

         return ::success;

      }

      string strItem;

      _001GetListText(item, strItem);

      _001SetText(strItem, actioncontext);

      return ::success;

   }


   void combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::on_layout(pgraphics);

      }


      /*      ::write_text::font_pointer fontxyz(e_create);

            ::rectangle_i32 rectangleClient;

            get_client_rect(rectangleClient);

            fontxyz->m_dFontSize = rectangleClient.height() * 0.4;
            fontxyz->m_eunitFontSize = ::draw2d::unit_pixel;
            fontxyz->m_bUpdated = false;

            SetFont(fontxyz);*/



   }


   void combo_box::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & actioncontext)
   {

      if(actioncontext.is_user_source())
      {

         string str;

         //if(m_bEdit)
         //{

         // ::user::plain_edit::_001GetText(str);
         ::user::plain_edit::_001GetText(str);

         //      }
         //      else
         //      {
         //
         //         str = m_strText;
         //
         //      }

         auto itemCurrent = _001FindListText(str);

         set_current_item(itemCurrent, actioncontext);

      }

   }


   void combo_box::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      //if(m_bEdit)
      {

         ::user::plain_edit::on_subject(psubject, pcontext);

      }

   }


   //bool combo_box::create_interaction(::user::interaction * puiParent, const ::id & id)
   //{

   //   if (!::user::plain_edit::create_interaction(puiParent, id))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


//#ifdef WINDOWS_DESKTOP
//   //Derived class is responsible for implementing these handlers
//   //for owner/self draw controls (except for the optional DeleteItem)
//   void combo_box::DrawItem(LPDRAWITEMSTRUCT)
//   { ASSERT(false); }
//   void combo_box::MeasureItem(LPMEASUREITEMSTRUCT)
//   { ASSERT(false); }
//   i32 combo_box::CompareItem(LPCOMPAREITEMSTRUCT)
//   { ASSERT(false); return 0; }
//   void combo_box::DeleteItem(LPDELETEITEMSTRUCT)
//   { /* default to nothing */ }
//#endif

//   bool combo_box::OnChildNotify(::user::message * pusermessage)
//   {
//
//#ifdef WINDOWS_DESKTOP
//      switch (pusermessage->m_id)
//      {
//      case WM_DRAWITEM:
//#ifdef WINDOWSEX
//         DrawItem((LPDRAWITEMSTRUCT)pusermessage->m_lparam);
//#else
//         __throw(todo);
//#endif
//         break;
//      case e_message_measure_item:
//#ifdef WINDOWSEX
//         MeasureItem((LPMEASUREITEMSTRUCT)pusermessage->m_lparam);
//#else
//         __throw(todo);
//#endif
//         break;
//      case WM_COMPAREITEM:
//#ifdef WINODWSEX
//         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)pusermessage->m_lparam);
//#else
//         __throw(todo);
//#endif
//         break;
//      case WM_DELETEITEM:
//#ifdef WINODWSEX
//         DeleteItem((LPDELETEITEMSTRUCT)pusermessage->m_lparam);
//#else
//         __throw(todo);
//#endif
//         break;
//      default:
//         return ::user::interaction::OnChildNotify(pusermessage);
//      }
//#endif
//
//      return true;
//   }
//

   void combo_box::GetLBText(index nIndex, string & rString)
   {

      ASSERT(is_window());

      GetLBText(nIndex, rString.get_string_buffer(GetLBTextLen(nIndex)));

      rString.release_string_buffer();

   }


   //::count combo_box::get_count()
   // { ASSERT(is_window()); return (count)send_message( CB_GETCOUNT, 0, 0); }
   //index combo_box::current_item()
   // { ASSERT(is_window()); return (index)send_message( CB_GETCURSEL, 0, 0); }
   //index combo_box::set_current_item(index nSelect)
   // { ASSERT(is_window()); return (index)send_message( CB_SETCURSEL, nSelect, 0); }
   //IA64: Assuming retval of CB_GETEDITSEL won't be expanded
   bool combo_box::GetEditSel(strsize & nStartChar, strsize & nEndChar)
   {
      /*      ASSERT(is_window()); u32 dw = u32(send_message( CB_GETEDITSEL, 0, 0));
            nStartChar = LOWORD(dw);
            nEndChar = LOWORD(dw);*/
      return true;
   }
   bool combo_box::LimitText(strsize nMaxChars)
   {
      //ASSERT(is_window());
      //return send_message( CB_LIMITTEXT, nMaxChars, 0) != false;
      return true;
   }

   bool combo_box::SetEditSel(strsize nStartChar, strsize nEndChar)
   {
      //ASSERT(is_window());
      //return send_message( CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar)) != false;
      return true;
   }

   uptr combo_box::GetItemData(index nIndex)
   {

      //ASSERT(is_window());

      //return send_message( CB_GETITEMDATA, nIndex, 0);
      return 0;

   }

   index combo_box::SetItemData(index nIndex, uptr dwItemData)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETITEMDATA, nIndex, (LPARAM)dwItemData);

      return -1;

   }

   void * combo_box::GetItemDataPtr(index nIndex)
   {

      //ASSERT(is_window()); return (LPVOID)GetItemData(nIndex);

      return nullptr;

   }

   index combo_box::SetItemDataPtr(index nIndex, void * pData)
   {

      //ASSERT(is_window());

      //return SetItemData(nIndex, (uptr)(LPVOID)pData);

      return -1;

   }

   index combo_box::GetLBText(index nIndex, char * pszText)

   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETLBTEXT, nIndex, (LPARAM)pszText);


      return -1;

   }

   strsize combo_box::GetLBTextLen(index nIndex)
   {

      //ASSERT(is_window());

      //return (strsize)send_message( CB_GETLBTEXTLEN, nIndex, 0);

      return -1;

   }


   void combo_box::ShowDropDown(bool bShowIt)
   {

      _001ShowDropDown(bShowIt);

   }


   index combo_box::delete_string(index nIndex)
   {

      auto iIndex = m_plistbox->delete_string(nIndex);

      return iIndex;

   }


   index combo_box::insert_string(index nIndex, const ::string & pszString)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_INSERTSTRING, nIndex, (LPARAM)pszString);


      return -1;

   }


   void combo_box::reset_content()
   {

      m_plistbox->reset_content();

   }


   index combo_box::Dir(index attr, const ::string & pszWildCard)
   {

//      ASSERT(is_window());

//      return (index)send_message( CB_DIR, attr, (LPARAM)pszWildCard);


      return -1;

   }


   void combo_box::clear()
   {

      //ASSERT(is_window());

      //send_message(WM_CLEAR, 0, 0);

   }


   void combo_box__copy()
   {

      //ASSERT(is_window());

      //send_message(WM_COPY, 0, 0);

   }


   void combo_box::Cut()
   {

      //ASSERT(is_window());

      //send_message( WM_CUT, 0, 0);

   }


   void combo_box::Paste()
   {

      //ASSERT(is_window());

      //send_message( WM_PASTE, 0, 0);

   }


   i32 combo_box::SetItemHeight(index nIndex, ::u32 cyItemHeight)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));

      return -1;

   }


   i32 combo_box::GetItemHeight(index nIndex)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_GETITEMHEIGHT, nIndex, 0L);

      return -1;

   }


   index combo_box::FindStringExact(index nIndexStart, const ::string & pszFind)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)pszFind);


      return -1;

   }


   i32 combo_box::SetExtendedUI(bool bExtended)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETEXTENDEDUI, bExtended, 0L);

      return -1;

   }


   bool combo_box::GetExtendedUI()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETEXTENDEDUI, 0, 0L) != 0;

      return false;

   }


   void combo_box::GetDroppedControlRect(RECTANGLE_I32 * prectangle)
   {

      //ASSERT(is_window());

      //send_message( CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)prectangle);


   }


   bool combo_box::GetDroppedState()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETDROPPEDSTATE, 0, 0L) != 0;

      return false;

   }


//   LCID combo_box::GetLocale()
//   {
//
//      //ASSERT(is_window());
//
//      //return (LCID)send_message( CB_GETLOCALE, 0, 0);
//
//      return -1; // everywhere
//
//   }
//
//   LCID combo_box::SetLocale(LCID nNewLocale)
//   {
//
//      //ASSERT(is_window());
//
//      //return (LCID)send_message( CB_SETLOCALE, (WPARAM)nNewLocale, 0);
//
//      return nNewLocale; // set where it is
//
//   }


   index combo_box::GetTopIndex()
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETTOPINDEX, 0, 0);

      return -1;

   }


   index combo_box::SetTopIndex(index nIndex)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETTOPINDEX, nIndex, 0);

      return -1;

   }


   ::count combo_box::InitStorage(::count nItems, ::u32 nBytes)
   {

      //ASSERT(is_window());

      //return (count)send_message( CB_INITSTORAGE, (WPARAM)nItems, nBytes);

      return -1;

   }

   void combo_box::SetHorizontalExtent(::u32 nExtent)
   {

      //ASSERT(is_window());

      //send_message( CB_SETHORIZONTALEXTENT, nExtent, 0);

   }


   ::u32 combo_box::GetHorizontalExtent()
   {

      //ASSERT(is_window());

      //return (::u32)send_message( CB_GETHORIZONTALEXTENT, 0, 0);

      return 0;

   }


   i32 combo_box::SetDroppedWidth(::u32 nWidth)
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_SETDROPPEDWIDTH, nWidth, 0);

      return -1;

   }


   i32 combo_box::GetDroppedWidth()
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_GETDROPPEDWIDTH, 0, 0);

      return -1;

   }


   bool combo_box::_001GetListText(index iSel,string & str) const
   {

      return m_plistbox->_001GetListText(iSel, str);

   }


   index combo_box::_001FindListText(const ::string & str) const
   {

      return m_plistbox->_001FindListText(str);

   }


   index combo_box::add_string(const ::string & pszString,uptr dwItemData)
   {

      synchronous_lock synchronouslock(mutex());

      ASSERT(m_edatamode == data_mode_opaque);

      if (m_edatamode != data_mode_opaque)
      {

         return -1;

      }

      defer_create_list_box();

      return m_plistbox->add_string(pszString, dwItemData);

   }


   index combo_box::add_string(const ::string & pszString, const ::string & strValue)
   {

      ASSERT(m_edatamode == data_mode_string);

      if (m_edatamode != data_mode_string)
      {

         return -1;

      }

      defer_create_list_box();

      auto iIndex = m_plistbox->add_string(pszString, strValue);

      return iIndex;

   }


   bool combo_box::has_action_hover()
   {

      return ::user::plain_edit::m_itemHover.is_set() || is_drop_down();

   }


   bool combo_box::has_text_input()
   {

      return m_bEdit && ::user::plain_edit::has_text_input();

   }


   void combo_box::set_current_item_by_string_value(const ::string & strValue, const ::action_context & actioncontext)
   {

      m_plistbox->set_current_item_by_string_value(strValue, actioncontext);

   }


   void combo_box::set_current_item_by_data(uptr u, const ::action_context & context)
   {

      m_plistbox->set_current_item_by_data(u, context);

   }


   string combo_box::get_current_item_string_value()
   {

      return m_plistbox->get_current_item_string_value();

   }


   bool combo_box::keyboard_focus_is_focusable() const
   {

      return is_window_enabled() && is_window_visible(e_layout_sketch);

   }


   bool combo_box::is_drop_down()
   {

      return m_plistbox != nullptr && m_plistbox->is_window_visible(e_layout_sketch);

   }


   void combo_box::on_message_left_button_double_click(::message::message * pmessage)
   {

      on_message_left_button_down(pmessage);

   }


   void combo_box::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_after_change_cur_sel)
      {

         auto puserinteraction = pevent->m_puserinteraction;

         if(puserinteraction == m_plistbox)
         {

            set_current_item(pevent->m_item, pevent->m_actioncontext);

            _001ShowDropDown(false);

            pevent->Ret();

            set_need_redraw();

            post_redraw();

            keyboard_set_focus_next();

            return;

         }

      }

      ::user::plain_edit::on_control_event(pevent);

   }


} // namespace user



