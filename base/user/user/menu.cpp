#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/id.h"
#include "aqua/xml.h"
#include "acme/constant/timer.h"
#include "aura/astr.h"
#include "aura/user/menu_command.h"


namespace user
{


   menu::menu()
   {

      m_econtroltype = e_control_type_menu;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      m_bCloseButton = true;

      //m_econtroltype = e_control_type_menu;
      m_bCloseButton = true;

      m_iFlags = 0;
      m_bPositionHint = false;
      //m_itemClose.m_id = "close_menu";
      //m_itemClose.m_pmenu = this;
      m_bAutoDelete = true;
      m_bOwnItem = true;
      m_puserinteractionParent = nullptr;
      m_pchannelNotify = nullptr;
      m_pmenuParent = nullptr;
      m_psubmenu = nullptr;
      m_iHoverSubMenu = -1;
      m_bInline = false;
      m_bMenuOk = false;
      m_pmenuitemSub = nullptr;

   }


   menu::menu(::user::menu_item * pitem)
   {

      m_pmenuitem = pitem;

      m_ewindowflag += e_window_flag_arbitrary_positioning;

      //m_econtroltype = e_control_type_menu;

      m_iFlags = 0;
      m_bPositionHint = false;
      m_iHoverSubMenu = -1;
      m_puserinteractionParent = nullptr;
      m_pchannelNotify = nullptr;
      m_pmenuParent = nullptr;
      m_psubmenu = nullptr;
      m_bAutoDelete = true;
      m_bOwnItem = false;
      m_bInline = false;
      m_bMenuOk = false;

   }


   menu::~menu()
   {

   }


   void menu::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &menu::on_message_destroy);
      MESSAGE_LINK(e_message_non_client_activate, pchannel, this, &menu::_001OnNcActivate);
      MESSAGE_LINK(e_message_non_client_calcsize, pchannel, this, &menu::on_message_non_client_calculate_size);
      MESSAGE_LINK(e_message_enable, pchannel, this, &menu::_001OnEnable);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &menu::on_message_show_window);
      MESSAGE_LINK(e_message_close, pchannel, this, &menu::on_message_close);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &menu::_001OnMouseActivate);
      MESSAGE_LINK(e_message_activate, pchannel, this, &menu::_001OnActivate);
      MESSAGE_LINK(e_message_non_client_create, pchannel, this, &menu::_001OnNcCreate);

   }


   void menu::update_flags(int iFlags)
   {

      m_iFlags = iFlags;

   }


   void menu::update_position(const ::point_i32 & point)
   {

      m_bPositionHint = true;

      m_pointPositionHint = point;

   }


   void menu::hints(int iFlags, const ::point_i32 & point)
   {

      update_flags(iFlags);

      update_position(point);

   }


   bool menu::create_menu(const string_array & straCommand, const string_array & straCommandTitle)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  menu_item  > ();

      }

      return m_pmenuitem->create_menu(straCommand, straCommandTitle);

   }


   void menu::destroy_menu()
   {

//      try
//      {
//
//         interaction_pointer_array uiptra = m_uiptraChild;
//
//         {
//
//            synchronous_lock synchronouslock(mutex_children());
//
//            m_uiptraChild.erase_all();
//
//         }
//
//         for (index i = 0; i < uiptra.get_count(); i++)
//         {
//
//            try
//            {
//
//               uiptra[i]->DestroyWindow();
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//
//
      {

        // synchronous_lock synchronouslock(mutex_children());

         // m_uiptraChild.interactiona().erase_all();

         m_puserinteractionpointeraChild.release();

      }

      m_pmenuitem.release();

   }


   bool menu::add_menu(::xml::node * pnode)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  menu_item  > ();

      }

      if (m_pmenuitem.is_null())
      {

         return false;

      }

      m_bCloseButton = pnode->attribute("close_button").is_empty() ||

                       (bool)pnode->attribute("close_button").is_true();


      m_pmenuitem->m_pmenu = this;

      if (!m_pmenuitem->load_menu(pnode))

      {

         return false;

      }

      return true;

   }


   bool menu::load_xml_menu(const ::payload & varXml)
   {

      m_psystem->m_paquasystem->_xml();

      auto papplication = get_application();

      auto strXml = papplication->as_string(varXml.string());

      if (strXml.is_empty())
      {

         return false;

      }

      auto psystem = get_system()->m_paquasystem;

      auto pxml = psystem->xml();

      auto pdocument = pxml->create_document();

      if (!pdocument->load(strXml))
      {

         if (is_debugger_attached())
         {

            output_error_message("menu::load_xml_string_menu\n\nBad XML document!!");

         }

         return false;

      }

      return add_menu(pdocument->root());

   }


   void menu::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshow(pmessage);

      if (pshow->m_bShow)
      {

         TRACE("menu::on_message_show_window bShow = %d", pshow->m_bShow);

         if (m_puserinteractionParent)
         {

            post_routine(__routine([this]()
            {

               get_window()->set_foreground_window();

               post_routine(__routine([this]()
                  {

                     get_window()->set_active_window();

                     get_window()->bring_to_front();

                     get_window()->set_window_position(e_zorder_top_most, 0, 0, 0, 0, 0);

                  }));

            }));

         }

      }
      else
      {

         TRACE("menu::on_message_show_window bShow = %d", pshow->m_bShow);

      }

   }


   void menu::on_message_destroy(::message::message * pmessage)
   {

      if (m_pmenuParent != nullptr)
      {

         if (m_pmenuParent->m_psubmenu == this)
         {

            m_pmenuParent->m_psubmenu.release();

         }
         else
         {

            ::output_debug_string("parent has other Topic Submenu");

         }

      }

      if (m_psubmenu.is_set())
      {

         m_psubmenu->start_destroying_window();

         m_psubmenu.release();

      }

      if (m_pmenuitem.is_set())
      {

         ::user::interaction * puserinteractionHost = m_pmenuitem->m_puserinteractionHost;

         if (::is_set(puserinteractionHost))
         {

            if (puserinteractionHost->m_menua.erase(this)
                  && m_pmenuitem->m_pmenuitemParent.is_null())
            {

               m_pmenuitem->menu_item_destruct();

            }

         }

      }

      //m_pmenuitem.release();

      m_pchannelNotify.release();

      m_puserinteractionParent.release();

      m_pmenuParent.release();

      m_pitemClose.release();

      m_psubmenu.release();

      m_pmenuitemSub.release();

   }


   ::user::menu_item * menu::GetSubMenu(i32 i)
   {

      return get_menu_item()->m_pmenuitema->element_at(i);

   }


   bool menu::create_menu(::channel* pchannelNotify, ::user::interaction * puiParent)
   {

      if (m_pmenuitem.is_null())
      {

         m_pmenuitem = __create <  menu_item  >();

      }

      m_puserinteractionParent = puiParent;

      m_puserinteractionParent->m_menua.add(this);

      m_pmenuitem->m_puserinteractionHost = m_puserinteractionParent;

      if (::is_null(pchannelNotify))
      {

         pchannelNotify = m_puserinteractionParent;

      }

      m_pchannelNotify = pchannelNotify;

      m_pmaterialCommandHandler = pchannelNotify;

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics();

      if (!is_window())
      {

//         int iStyleEx = 0;
//
//         if (puiParent == nullptr)
//         {
//
////#ifdef WINDOWS_DESKTOP
////
////            iStyleEx = WS_EX_LAYERED | WS_EX_TOOLWINDOW;
////
////#endif
//
//         }

         set_tool_window();

         //auto pusersystem = __new(::user::system (iStyleEx, nullptr, nullptr, 0, nullptr, pcreate));

         //if (!create_window_ex(pusersystem, puiParent))
         if (!create_host())
         {

            return false;

         }

         if (pchannelNotify != nullptr)
         {

            //set_owner(puiNotify);


         }

      }

      //::user::style_context stylecontext;

      if (m_bCloseButton)
      {

         if (m_pitemClose.is_null())
         {

            m_pitemClose = __new(menu_item);

            m_pitemClose->m_id = "close_menu";

            m_pitemClose->m_pmenu = this;

            __pointer(::user::interaction) pinteraction = m_pitemClose->m_puserinteraction;

            pinteraction = create_menu_button(pgraphics, m_pitemClose);

            m_pitemClose->m_puserinteraction = pinteraction;

            //if (!m_pitemClose->m_puserinteraction->create_interaction(this, "close_menu"))
            if (!m_pitemClose->m_puserinteraction->create_child(this))
            {

               return false;

            }

         }

         __pointer(::user::button) pbutton = m_pitemClose->m_puserinteraction;

         if (pbutton)
         {

            pbutton->set_stock_icon(e_stock_icon_close);

         }
         else
         {

            m_pitemClose->m_puserinteraction->set_window_text("x");

         }

      }

      if (!m_pmenuitem->create_buttons(pgraphics, this))
      {

         ASSERT(false);

         return false;

      }

      return true;

   }


   bool menu::create_inline_menu(::channel * pchannelNotify, ::user::interaction * puiParent)
   {

      m_bMenuOk = false;

      m_bInline = true;

      if (!create_menu(pchannelNotify, puiParent))
      {

         return false;

      }

      update_command(m_pmenuitem);

      m_bMenuOk = true;

      //      create_buttons(m_pmenuitem);

      //on_layout(::draw2d::graphics_pointer & pgraphics);

      //auto rectangleClient = puiParent->get_client_rect();

      //place(rectangleClient);

      //display();

      set_need_layout();

      set_need_redraw();

      SetTimer(::e_timer_command_probe, 300, nullptr);

      return true;

   }



   bool menu::track_popup_menu(::channel * pchannelNotify, ::user::interaction * puiParent)
   {

      if (!create_menu(pchannelNotify, puiParent))
      {

         return false;

      }

      if (!m_bPositionHint)
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pointCursor = pwindowing->get_cursor_position();
         
         m_pointPositionHint = pointCursor;

      }

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics();

      m_pointTrack = m_pointPositionHint;

      layout_menu(pgraphics);

      m_bMenuOk = true;

      return true;

   }


   bool menu::contains_menu_item(menu_item * pitem, bool bRecursive) const
   {

      if (m_pmenuitem.is_null())
      {

         return false;

      }

      return m_pmenuitem->contains_menu_item(pitem, bRecursive);

   }


   void menu::layout_menu(::draw2d::graphics_pointer & pgraphics)
   {

      ::point_i32 point = m_pointTrack;

      if (get_parent() != nullptr)
      {

         get_parent()->screen_to_client(m_pointTrack);

      }

      auto pstyle = get_style(pgraphics);

      pgraphics->set(get_font(pstyle));

      auto metrics = pgraphics->get_text_metrics();

      auto dMaxHeight = metrics.get_line_spacing();

      m_dItemHeight = dMaxHeight;

      m_dCheckBoxSize = dMaxHeight;

      m_dHeaderHeight = dMaxHeight;

      __pointer(::user::menu_item) pitem = get_menu_item();

      __pointer(::user::menu_item_ptra) pmenuitema = pitem->m_pmenuitema;

      auto rectMargin = get_margin(pstyle);

      auto rectBorder = get_border(pstyle);

      auto rectPadding = get_padding(pstyle);

      //int iElementPadding = rectPadding.left;

      int x = (int) (rectMargin.left + rectBorder.left + rectPadding.left);

      int y = (int) (rectMargin.top + rectBorder.top + rectPadding.top);

      class calc_size calcsize;

      calcsize.m_pgraphics = pgraphics;

      if (m_bCloseButton)
      {

         m_pitemClose->m_puserinteraction->on_calc_size(&calcsize);

         m_pitemClose->m_rectUi.left = x;
         m_pitemClose->m_rectUi.right = x + calcsize.m_size.cx;
         m_pitemClose->m_rectUi.top = y;
         m_pitemClose->m_rectUi.bottom = y + calcsize.m_size.cy;

         y += calcsize.m_size.cy;

      }

      int yClose = y;

      m_iaColumnWidth.set_size(1);

      m_iaColumnHeight.set_size(1);

      m_iaColumnWidth[0] = calcsize.m_size.cx;

      m_iaColumnHeight[0] = yClose;

      index iColumn = 0;

      for (i32 i = 0; i < pmenuitema->get_size(); i++)
      {

         string strButtonText = pmenuitema->element_at(i)->m_puserinteraction->get_window_text();

         pmenuitema->element_at(i)->m_iColumn = (int) iColumn;

         pmenuitema->element_at(i)->m_puserinteraction->on_calc_size(&calcsize);

         pmenuitema->element_at(i)->m_rectUi.left = x;
         pmenuitema->element_at(i)->m_rectUi.right = x + calcsize.m_size.cx;
         pmenuitema->element_at(i)->m_rectUi.top = y;
         pmenuitema->element_at(i)->m_rectUi.bottom = y + calcsize.m_size.cy;

         y += calcsize.m_size.cy;

         m_iaColumnHeight[0] = y;

         if (calcsize.m_size.cx > m_iaColumnWidth[0])
         {

            m_iaColumnWidth[0] = calcsize.m_size.cx;

         }

         if (pmenuitema->element_at(i)->m_bBreak)
         {

            x += m_iaColumnWidth[0];

            y = yClose;

            iColumn++;

            m_iaColumnWidth.add(0);

            m_iaColumnHeight.add(yClose);

         }

      }

      m_size.cx = (int) (m_iaColumnWidth.get_total()
                  + rectMargin.left + rectMargin.right
                  + rectBorder.left + rectBorder.right
                  + rectPadding.left + rectPadding.right);

      m_size.cy = (int) (m_iaColumnHeight.get_maximum_value()
                  + rectMargin.top + rectMargin.bottom
                  + rectBorder.top + rectBorder.bottom
                  + rectPadding.top + rectPadding.bottom);


      m_size.cx = maximum(m_sizeMinimum.cx, m_size.cx);

      m_size.cy = maximum(m_sizeMinimum.cy, m_size.cy);

      ::count iItemCount = pmenuitema->get_size();

      __pointer(::base::style) pbasestyle = pstyle;

      for (i32 i = 0; i < iItemCount; i++)
      {

         ::user::menu_item * pitem = pmenuitema->element_at(i);

         pmenuitema->element_at(i)->m_rectUi.right = x + m_iaColumnWidth[pitem->m_iColumn];

         pbasestyle->prepare_menu(pgraphics, pitem);

         pitem->m_rectUi.right = maximum(pitem->m_rectUi.right, pitem->m_rectUi.left + m_sizeMinimum.cx);

         pitem->m_puserinteraction->place(pitem->m_rectUi);

         pitem->m_puserinteraction->display();

      }

      if (pbasestyle && m_bCloseButton)
      {

         pbasestyle->prepare_menu(pgraphics, m_pitemClose);

         m_pitemClose->m_puserinteraction->place(m_pitemClose->m_rectUi);

         m_pitemClose->m_puserinteraction->display();

      }

      ::rectangle_i32 rectWindow;

      rectWindow.left = point.x;
      rectWindow.top = point.y;
      rectWindow.right = rectWindow.left + m_size.cx;
      rectWindow.bottom = rectWindow.top + m_size.cy;

      ::rectangle_i32 rectMonitor;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      if (pdisplay->get_best_monitor(rectMonitor, rectWindow) >= 0)
      {

         rectMonitor.deflate(16, 16);

         if (rectWindow.left < rectMonitor.left)
         {

            rectWindow.offset(rectMonitor.left - rectWindow.left, 0);

         }
         else if (rectWindow.right > rectMonitor.right)
         {

            rectWindow.offset(rectMonitor.right - rectWindow.right, 0);

         }

         if (rectWindow.top < rectMonitor.top)
         {

            rectWindow.offset(0, rectMonitor.top - rectWindow.top);

         }
         else if (rectWindow.bottom > rectMonitor.bottom)
         {

            rectWindow.offset(0, rectMonitor.bottom - rectWindow.bottom);

         }

      }

      layout().sketch() = e_zorder_top_most;

      place(rectWindow);

      display(e_display_normal, e_activation_no_activate);

      set_need_redraw();

      post_redraw();

      SetTimer(::e_timer_command_probe, 100, nullptr);

   }


   void menu::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto crBackground = get_color(pstyle, e_element_background);

      if (crBackground.is_translucent())
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      }

      ::user::interaction::_001OnDraw(pgraphics);

   }




   void menu::on_message_left_button_down(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void menu::defer_close()
   {

      ::user::control_event ev;

      ev.m_eevent = ::user::e_event_context_menu_close;

      on_control_event(&ev);

      if (!m_bInline && !ev.m_bRet)
      {

         post_message(e_message_close);

      }

   }


   void menu::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_click)
      {

         if (m_pitemClose.is_set() && pevent->m_puserinteraction == m_pitemClose->m_puserinteraction)
         {

            defer_close();

         }
         else
         {

            __pointer(::user::menu_item) pitem = pevent->m_puserinteraction->m_pmenuitem;

            if (pitem != nullptr && !pitem->m_bPopup)
            {

               if (pevent->m_puserinteraction->m_id.begins(astr.ingSysCommand))
               {

                  auto pchannelNotify = get_notify_channel();

                  if (::is_set(pchannelNotify))
                  {

                     //::message::command command(pevent->m_puserinteraction->m_id);

                     //puiTarget->_001SendCommand(&command);

                     pchannelNotify->command_handler(pevent->m_puserinteraction->m_id);

                  }

               }
               else
               {

                  auto pchannelNotify = m_pchannelNotify;

                  id idCommand = pevent->m_puserinteraction->m_id;

                  idCommand = translate_property_id(idCommand);

                  defer_close();

                  // this may be destroyed by e_message_close above

                  if (::is_set(pchannelNotify))
                  {

                     ::message::command command(idCommand);

                     command.m_actioncontext = pevent->m_actioncontext;

                     pchannelNotify->_001SendCommand(&command);

                     pevent->m_bRet = command.m_bRet;

                  }

               }

            }

         }

      }
//      else if (pevent->m_eevent == ::user::e_event_mouse_enter)
//      {
//
//         if (m_pitemClose.is_set()
//               && pevent->m_puserinteraction != m_pitemClose->m_puserinteraction)
//         {
//
//            if (!m_bInline)
//            {
//
//               if (pevent->m_puserinteraction->m_pmenuitem != m_pmenuitemSub)
//               {
//
//                  {
//
//                     __pointer(::user::menu_item) pitem = pevent->m_puserinteraction->m_pmenuitem;
//
//                     if (pitem)
//                     {
//
//                        if (pitem->m_bPopup)
//                        {
//
//                           if (m_psubmenu != nullptr)
//                           {
//
//                              m_psubmenu->start_destroying_window();
//
//                              m_psubmenu = nullptr;
//
//                              m_pmenuitemSub = nullptr;
//
//                           }
//
//                           m_pmenuitemSub = pitem;
//
//                           m_psubmenu = __new(menu(pitem));
//
//                           m_psubmenu->initialize(this);
//
//                           m_psubmenu->m_pmenuParent = this;
//
//                           ::rectangle_i32 rectangle;
//
//                           pevent->m_puserinteraction->get_window_rect(rectangle);
//
//                           m_psubmenu->update_position(rectangle.top_right());
//
//                           m_psubmenu->track_popup_menu(m_pchannelNotify);
//
//                        }
//                        else
//                        {
//
//                           ::user::control_event ev;
//
//                           ev.m_eevent = ::user::e_event_menu_hover;
//
//                           ev.m_id = pitem->m_id;
//
//                           ::user::interaction * puiTarget = get_target_window();
//
//                           if (puiTarget == nullptr)
//                           {
//
//                              return;
//
//                           }
//
//                           return puiTarget->on_control_event(&ev);
//
//                        }
//
//                     }
//
//                  }
//
//               }
//
//            }
//
//         }
//
//         pevent->m_bRet = true;
//
//         return;
//
//      }
//      else if (pevent->m_eevent == ::user::e_event_mouse_leave)
//      {
//         if (pevent->m_puserinteraction->m_id == m_idTimerMenu)
//         {
//            KillTimer(e_timer_menu);
//            m_idTimerMenu.is_empty();
//         }
//
//         pevent->m_bRet = true;
//
//         return;
//
//      }

      ::user::interaction::on_control_event(pevent);

   }


   void menu::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      __pointer(::user::menu_item) pitemThis = get_menu_item();

      if (pitemThis == nullptr)
      {

         return;

      }

      __pointer(::user::menu_item_ptra) pmenuitema = pitemThis->m_pmenuitema;

      if (ptimer->m_uEvent == e_timer_menu)
      {
         KillTimer(e_timer_menu);
         if (m_idSubMenu.has_char())
         {
            m_psubmenu->send_message(e_message_close);
            m_psubmenu = nullptr;
            m_idSubMenu.is_empty();
         }

         if (m_idTimerMenu.has_char())
         {

            m_idSubMenu = m_idTimerMenu;

            m_psubmenu = __new(menu(pmenuitema->find(m_idTimerMenu)));

            m_psubmenu->initialize(this);

            ::rectangle_i32 rectangle;

            pmenuitema->find(m_idTimerMenu)->m_puserinteraction->get_window_rect(rectangle);

            m_psubmenu->update_position(rectangle.top_right());

            m_psubmenu->track_popup_menu(m_pchannelNotify, this);

         }

         m_idTimerMenu.is_empty();

      }
      else if (ptimer->m_uEvent == ::e_timer_command_probe)
      {

         {

            synchronous_lock synchronouslock(mutex());

            update_command(m_pmenuitem);

         }

         //if(pmenuitema != nullptr)
         //{
         //   ::message::command commandui(this);
         //   commandui.m_pitema          = pmenuitema;
         //   for(i32 i = 0; i < pmenuitema->get_size(); i++)
         //   {
         //
         //      commandui.m_iIndex    = i;
         //      commandui.m_id        = pmenuitema->element_at(i)->m_id;
         //      commandui.m_pOther    = pmenuitema->element_at(i)->m_puserinteraction;
         //
         //      __pointer(::user::interaction) puiTarget = get_target_window();
         //
         //      if(puiTarget != nullptr)
         //      {
         //         /* xxx if(puserinteractionParent->on_command(0,
         //          MAKELONG((i32)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
         //          &commandui, nullptr))
         //          continue;*/
         //         if(puiTarget->_001SendUpdateCmdUi(&commandui))
         //            continue;
         //      }
         //   }
         //}
      }


   }


   void menu::on_message_create(::message::message * pmessage)
   {

      /// descriptor().set_control_type(e_control_type_menu);

      pmessage->previous();

      __UNREFERENCED_PARAMETER(pmessage);

      //create_color(color_background, argb(84 + 77, 185, 184, 177));
      //create_translucency(::user::e_translucency_present;



   }



   //    void menu::_001OnIdleUpdateCmdUI(::message::message * pmessage)
   //    {
   //       __UNREFERENCED_PARAMETER(pmessage);
   //       //      __pointer(::user::message) pusermessage(pmessage);

   //       __pointer(::user::menu_item) pitemThis = get_item();

   //       __pointer(::user::menu_item_ptra) pmenuitema = pitemThis->m_spmenuitema;

   //       if(pmenuitema != nullptr)
   //       {
   //          ::message::command commandui(this);
   //          commandui.m_pitema          = pmenuitema;
   //          for(i32 i = 0; i < pmenuitema->get_size(); i++)
   //          {

   //             commandui.m_iIndex    = i;
   //             commandui.m_id        = pmenuitema->element_at(i)->m_id;
   //             commandui.m_pOther    = pmenuitema->element_at(i)->m_puserinteraction;

   //             __pointer(::user::interaction) puserinteractionParent = m_puiNotify;
   //             if(puserinteractionParent != nullptr)
   //             {
   //                /*
   //                 if(puserinteractionParent->on_command(0,
   //                 MAKELONG((i32)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
   //                 &commandui, nullptr))
   //                 continue;
   //                 */

   //                if(puserinteractionParent->_001SendUpdateCmdUi(&commandui))
   //                   continue;
   //             }

   //          }
   //       }
   //    }


   void menu::_001OnEnable(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }


   void menu::_001OnNcCreate(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      pusermessage->m_bRet = true;

      pusermessage->m_lresult = 1;

   }


   void menu::_001OnNcActivate(::message::message * /*pmessage */)
   {

      //__pointer(::message::nc_activate) pncactivate(pmessage);

//#ifdef WINDOWS_DESKTOP
//
//      if (::IsIconic(get_handle()))
//      {
//
//         pncactivate->m_bRet = false;
//
//      }
//      else
//      {
//
//         pncactivate->m_lresult = false;
//
//         pncactivate->m_bRet = true;
//
//
//      }
//
//#else
//
//      pncactivate->m_lresult = true;
//
//      pncactivate->m_bRet = true;
//
//#endif

   }


   void menu::_001OnActivate(::message::message * pmessage)
   {

      __pointer(::message::activate) pactivate(pmessage);

      pactivate->m_lresult = 0;

      pactivate->m_bRet = true;

   }


   void menu::_001OnMouseActivate(::message::message * pmessage)
   {

      __pointer(::message::mouse_activate) pmouseactivate(pmessage);

      pmouseactivate->m_lresult = e_mouse_activate_no_activate;

      pmouseactivate->m_bRet = true;

   }


   size_i32 menu::get_window_minimum_size()
   {

      return m_sizeMinimum;

   }


   void menu::on_message_non_client_calculate_size(::message::message * pmessage)
   {

      ///__pointer(::user::message) pusermessage(pmessage);

      pmessage->previous();

      return;

      //if (pusermessage->m_wparam == true)
      //{

      //   pusermessage->m_bRet = true;
      //   pusermessage->set_lresult(0);

      //}
      //else
      //{

      //   RECTANGLE_I32 * prectangle = (RECTANGLE_I32 *)pusermessage->m_lparam.m_lparam;

      //   prectangle->left = m_pointTrack.x;

      //   prectangle->top = m_pointTrack.y;

      //   prectangle->right = prectangle->left + maximum(::user::interaction::get_window_minimum_size().cx, m_size.cx);

      //   prectangle->bottom = prectangle->left + maximum(::user::interaction::get_window_minimum_size().cy, m_size.cy);

      //   pusermessage->m_bRet = true;
      //   pusermessage->set_lresult(0);

      //}

   }


   void menu::on_message_close(::message::message * pmessage)
   {

      if (!m_bInline)
      {

         if (m_pmenuParent != nullptr)
         {

            m_pmenuParent->post_message(e_message_close);

         }

         //DestroyWindow();
         set_finish();

      }

      pmessage->m_bRet = true;

   }


   bool menu::pre_create_window(::user::system * pusersystem)
   {

//#ifdef WINDOWS_DESKTOP
//
//      pusersystem->m_createstruct.dwExStyle = WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
//
//      pusersystem->m_createstruct.style &= ~WS_VISIBLE;
//
//#endif

      return true;

   }


   __pointer(::user::menu_item) menu::get_menu_item()
   {

      return m_pmenuitem;

   }


   //__pointer(::user::menu_item) menu::get_menu_item(::user::interaction * pinteraction)
   //{

   //   __pointer(::user::interaction) pbutton = pinteraction;

   //   if (pbutton.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return pbutton->m_pmenuitem;

   //}


   ::channel * menu::get_notify_channel()
   {

      return m_pchannelNotify;

      //auto pchannelNotify = m_pchannelNotify;

      //if (::is_null(pchannelNotify))
      //{

      //   return nullptr;

      //}

      //if (dynamic_cast <::user::frame *> (puiTarget) == nullptr)
      //{

      //   puiTarget = puiTarget->get_parent_frame();

      //}

      //return puiTarget;

   }


   bool menu::has_pending_graphical_update()
   {

      return ::user::interaction::has_pending_graphical_update();

   }



   void menu::update_command(menu_item * pitemParent)
   {

      if (m_pchannelNotify == nullptr)
      {

         return;

      }

      if (pitemParent == nullptr)
      {

         return;

      }

      if (pitemParent->m_pmenuitema == nullptr)
      {

         return;

      }

      auto pmenucommand= __create_new< ::user::menu_command>();

      pmenucommand->m_pitema = pitemParent->m_pmenuitema;

      pmenucommand->m_iCount = pitemParent->m_pmenuitema->get_size();

      for (pmenucommand->m_iIndex = 0; pmenucommand->m_iIndex < pmenucommand->m_iCount; pmenucommand->m_iIndex++)
      {

         __pointer(menu_item) pitem = pitemParent->m_pmenuitema->element_at(pmenucommand->m_iIndex);

         pmenucommand->m_id = pitem->m_id;

         pmenucommand->m_puiOther = pitem->m_puserinteraction;

         if (m_pchannelNotify.is_null())
         {

            return;

         }

         try
         {

            m_pchannelNotify->_001SendCommandProbe(pmenucommand);

         }
         catch (...)
         {

            return;

         }

      }

      for (pmenucommand->m_iIndex = 0; pmenucommand->m_iIndex < pmenucommand->m_iCount; pmenucommand->m_iIndex++)
      {

         __pointer(menu_item) pitem = pitemParent->m_pmenuitema->element_at(pmenucommand->m_iIndex);

         pmenucommand->m_id = pitem->m_id;

         pmenucommand->m_puiOther = pitem->m_puserinteraction;

         if (pitem->m_pmenu != nullptr)
         {

            pitem->m_pmenu->update_command(pitem);

         }

      }
      if (pmenucommand->m_bEnableChanged || pmenucommand->m_bRadioChanged)
      {

         set_need_redraw();

      }

   }


   __pointer(::user::menu_interaction) menu::create_menu_button(::draw2d::graphics_pointer & pgraphics, menu_item * pitem)
   {

      auto pstyle = get_style(pgraphics);

      __pointer(::base::session) psession = get_session();

      auto puser = psession->user();

      auto pinteraction = puser->create_menu_button(pstyle, pitem);

      if (!pinteraction)
      {

         return nullptr;

      }

      auto estatus = pinteraction->initialize(this);

      if (!estatus)
      {

         return nullptr;

      }

      pinteraction->m_pmaterialCommandHandler = this;
      
      pinteraction->add_control_event_handler(this);

      return pinteraction;

   }


   // <3ThomasBorregaardS�rensen__!!
   ::e_status menu::command_handler(const ::id& id)
   {

      if (m_pmaterialCommandHandler)
      {

         defer_close();

         auto estatus = m_pmaterialCommandHandler->command_handler(id);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }

      return ::error_failed;

   }



} // namespace user




