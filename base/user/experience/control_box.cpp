#include "framework.h"
#include "base/user/experience/_experience.h"
#include "acme/constant/timer.h"


namespace experience
{


   control_box::control_box() :
      m_brushButtonBack(e_create),
      m_brushButtonBackSel(e_create),
      m_brushButtonBackFocus(e_create),
      m_brushButtonBackDisabled(e_create),
      m_penButtonBack(e_create),
      m_penButtonBackSel(e_create),
      m_penButtonBackFocus(e_create),
      m_penButtonBackDisabled(e_create)
   {

      m_strInteractionTag = "control_box";

      set_control_box_button_id(e_button_close, "frame::ButtonClose");
      set_control_box_button_id(e_button_up, "frame::e_button_up");
      set_control_box_button_id(e_button_down, "frame::e_button_down");
      set_control_box_button_id(e_button_minimize, "frame::e_button_minimize");
      set_control_box_button_id(e_button_maximize, "frame::e_button_maximize");
      set_control_box_button_id(e_button_restore, "frame::e_button_restore");
      set_control_box_button_id(e_button_notify_icon, "frame::e_button_notify_icon");
      set_control_box_button_id(e_button_transparent_frame,"frame::e_button_transparent_frame");
      set_control_box_button_id(e_button_dock,"frame::e_button_dock");
      m_bDrag = false;
      m_iDefaultButtonMargin = 3;

   }


   control_box::~control_box()
   {

   }


   void control_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if (m_pframewindow != nullptr
            && m_pframewindow->m_pframe != nullptr
            && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         m_bDrag = true;

         m_pointDrag = pmouse->m_point;

         screen_to_client(m_pointDrag);

         set_mouse_capture();

         pmouse->m_bRet = true;

      }

   }


   void control_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if (m_pframewindow != nullptr
            && m_pframewindow->m_pframe != nullptr
            && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         ::point_i32 point = pmouse->m_point;

         m_pframewindow->screen_to_client(point);

         drag(point);

         m_bDrag = false;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

         pmouse->m_bRet = true;

      }

   }


   void control_box::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if (m_pframewindow != nullptr
            && m_pframewindow->m_pframe != nullptr
            && m_pframewindow->m_pframe->is_control_box_moveable())
      {

         if (m_bDrag)
         {

            ::point_i32 point = pmouse->m_point;

            m_pframewindow->screen_to_client(point);

            drag(point);

         }

         pmouse->m_bRet = true;

      }

   }


   void control_box::drag(const ::point_i32 & point)
   {

      //int x = point.x - m_pointDrag.x;

      //if (x < 0)
      //{

      //   x = 0;

      //}

      //::rectangle_i32 rectParent;

      //get_parent()->get_client_rect(rectParent);

      //::rectangle_i32 rectangleClient;

      //get_client_rect(rectangleClient);

      //::rectangle_i32 rectWindow;

      //get_window_rect(rectWindow);

      //get_parent()->screen_to_client(rectWindow);

      //m_pframewindow->m_pframe->m_iControlBoxRight = rectParent.right - x - rectWindow.width();

      //m_pframewindow->m_pframe->get_control_box_rect()->move_left_to(x);

      //x = m_pframewindow->m_pframe->calc_control_box_left(true);

      //::point_i32 point(x, rectWindow.top);

      //::point_i32 pointScreen(point);

      //get_parent()->client_to_screen(pointScreen);

      //m_pframewindow->m_pframe->m_iControlBoxRight = rectParent.right - point.x - rectWindow.width();

      //int iControlBoxRight = m_pframewindow->m_pframe->m_iControlBoxRight;

      //m_pframewindow->prop("control_box_right_to_right") = iControlBoxRight;

      //order(e_zorder_top);

      //move_to(point);

   }


   void control_box::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshow(pmessage);

      m_bDrag = false;

      m_bShowAttempt = false;

      if (pshow->m_bShow)
      {

         m_millisShow.Now();

      }
      else
      {

         output_debug_string(".");

      }

   }


   void control_box::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == e_timer_check_hover)
      {

         if (get_top_level()->layout().is_moving())
         {

            //TRACE("experience control_box : top level is moving : ignoring e_message_timer");

            return;

         }
         else if (get_top_level()->layout().is_sizing())
         {

            //TRACE("experience control_box : top level is sizing : ignoring e_message_timer");

            return;

         }

         ::point_i32 pointCursor;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pointCursor = pwindowing->get_cursor_position();

         if (is_window_visible())
         {

            if (m_bDrag)
            {

               m_millisShow.Now();

            }
            else
            {

               if (m_pframewindow != nullptr)
               {

                  if (m_pframewindow->layout().is_full_screen())
                  {

                     ::rectangle_i32 rectWindow;

                     get_window_rect(rectWindow);

                     if (rectWindow.contains(pointCursor))
                     {

                        m_millisShow.Now();

                     }
                     else
                     {

                        if(m_millisShow.elapsed() > 1000)
                        {

                           display(e_display_none);

                        }

                     }

                  }

               }

            }

         }
         else if (m_bShowAttempt)
         {
            //if ((m_millisShowTime.elapsed()) > 284)
            {
               if (m_pframewindow != nullptr)
               {

                  if (m_pframewindow->layout().is_full_screen())
                  {

                     ::rectangle_i32 rectWindow;

                     get_window_rect(rectWindow);

                     rectWindow.left = minimum(rectWindow.left, rectWindow.right);
                     rectWindow.bottom = minimum(rectWindow.top, rectWindow.bottom);


                     if (pointCursor.x >= rectWindow.left && pointCursor.y <= rectWindow.right && pointCursor.y == 0)
                     {

                        order(e_zorder_top);

                        display();

                     }

                     m_bShowAttempt = false;

                  }

               }

            }
         }
         else
         {

            if (m_pframewindow->layout().is_full_screen())
            {

               ::rectangle_i32 rectWindow;

               get_window_rect(rectWindow);

               rectWindow.left = minimum(rectWindow.left, rectWindow.right);
               rectWindow.bottom = minimum(rectWindow.top, rectWindow.bottom);

               ::point_i32 point;

               try
               {

                  point = psession->m_pointCursor;

               }
               catch (...)
               {

               }

               if (point.x >= rectWindow.left && point.x <= rectWindow.right && point.y == 0)
               {

                  m_bShowAttempt = true;

                  m_millisShow.Now();

               }

            }

         }

      }

   }


   void control_box::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      if (!m_fontMarlett)
      {

         m_fontMarlett.create(this);

         m_fontMarlett->create_pixel_font("Marlett", 16.0);

      }

      create_buttons();

   }


   void control_box::install_message_routing(::channel *pframewindow)
   {

      ::user::interaction::install_message_routing(pframewindow);

      MESSAGE_LINK(e_message_show_window, pframewindow, this, &control_box::on_message_show_window);
      MESSAGE_LINK(e_message_create, pframewindow, this, &control_box::on_message_create);
      MESSAGE_LINK(e_message_mouse_move, pframewindow, this, &control_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_left_button_down, pframewindow, this, &control_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pframewindow, this, &control_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_move, pframewindow, this, &control_box::on_message_move);
      MESSAGE_LINK(e_message_size, pframewindow, this, &control_box::on_message_size);

   }


   bool control_box::should_show_button(enum_button ebutton) const
   {

      if (!has_button(ebutton))
      {

         return false;

      }

      if (ebutton == e_button_close)
      {

         return true;

      }
      else if (ebutton == e_button_up)
      {

         return m_pframewindow->updown_get_up_enable();

      }
      else if (ebutton == e_button_down)
      {

         return m_pframewindow->updown_get_down_enable();

      }
      else if (ebutton == e_button_maximize)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return !m_pframewindow->layout().is_zoomed();

      }
      else if (ebutton == e_button_restore)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

         //auto edisplay = m_pframewindow->layout().sketch().display();

         //return is_iconic(edisplay)
            // || is_full_screen(edisplay)
            //|| is_zoomed(edisplay)
            //|| is_docking_appearance(edisplay);

      }
      else if (ebutton == e_button_minimize)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      }
      else if (ebutton == e_button_notify_icon)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return m_pframewindow->window_is_notify_icon_enabled();

      }
      else if (ebutton == e_button_transparent_frame)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      }
      else if (ebutton == e_button_dock)
      {

         if (m_pframewindow->updown_get_up_enable())
         {

            return false;

         }

         return true;

      }

      return false;

   }


   void control_box::_layout_button(enum_button ebutton, ::rectangle_i32& rectangle)
   {

      auto pbutton = get_box_button(ebutton);

      if(should_show_button(ebutton))
      {

         auto sizeButton = get_button_size(ebutton);

         auto rectMargin = get_button_margin(ebutton);

         rectangle.right = rectangle.left - rectMargin.right;
         rectangle.left = rectangle.right - sizeButton.cx;

         if (pbutton)
         {

            rectangle.top = rectMargin.top;
            rectangle.bottom = sizeButton.cy + rectangle.top;

            pbutton->order(e_zorder_top);
            pbutton->place(rectangle);
            pbutton->display();
            pbutton->UpdateWndRgn();

         }

         rectangle.left -= rectMargin.left;

      }
      else
      {

         if (pbutton)
         {

            pbutton->hide();

         }

      }

   }


   void control_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      ::rectangle_i32 rectParent(rectWindow);

      m_pframewindow->screen_to_client(rectParent);

      ::rectangle_i32 rectangle;

      get_window_rect(rectangle);

      m_pframewindow->screen_to_client(rectangle);

      reset_layout(pgraphics);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      int iWidth = rectangleClient.width();


      rectangle.left = iWidth;

      _layout_button(e_button_close, rectangle);

      _layout_button(e_button_up, rectangle);

      _layout_button(e_button_down, rectangle);

      _layout_button(e_button_maximize, rectangle);

      _layout_button(e_button_restore, rectangle);

      _layout_button(e_button_minimize, rectangle);

      _layout_button(e_button_notify_icon, rectangle);

      _layout_button(e_button_transparent_frame, rectangle);

      _layout_button(e_button_dock, rectangle);


   }


   control_box::item * control_box::get_item(enum_button ebutton, bool bCreate)
   {

      auto ppair = m_itemmap.plookup(ebutton);

      if (!ppair)
      {

         return nullptr;

      }

      if (bCreate)
      {

         __defer_construct_new(ppair->m_pitem);

      }

      return ppair->m_pitem;

   }


   bool control_box::create_button(enum_button ebutton)
   {

      auto pitem = get_item(ebutton, true);

      if (!pitem)
      {

         return false;

      }

      auto & pbutton = pitem->m_pbutton;

      auto plibrary = m_pframewindow->m_pframe->m_pexperience->m_plibrary;

      plibrary->__defer_construct(pbutton);

      pbutton->initialize(this);

      pbutton->display(e_display_none);

      pbutton->m_pcontrolbox = this;

      pbutton->m_ebutton = ebutton;

      pbutton->add_control_event_handler(m_pframewindow);

      // if(ebutton == e_button_dock)
      // {

      //    pbutton->m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown = true;

      // }

      if (!pbutton->is_window() && !pbutton->create_child(this))
      {

         return false;

      }

      return true;

   }


   bool control_box::update_control_box_button(enum_button ebutton)
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return false;

      }

      auto pbutton = pitem->m_pbutton;

      if (!pbutton)
      {

         return false;

      }

      pbutton->m_ebutton = ebutton;

      id id = get_control_box_button_id(ebutton);

      pbutton->m_id = id;

      string strTag = get_control_box_button_tag(ebutton);

      pbutton->m_strInteractionTag = strTag;

      string strCaption;

      get_control_box_button_caption(ebutton, strCaption);

      pbutton->set_stock_icon(get_control_box_button_stock_icon(ebutton));

      //pbutton->set_parent(this);

      pbutton->set_window_text(strCaption);

      pbutton->m_pcontrolbox = this;

      return true;

   }


   void control_box::update_control_box_buttons()
   {

      for (auto & ebutton : m_itemmap.keys())
      {

         update_control_box_button(ebutton);

      }

   }



   bool control_box::create_buttons()
   {

      create_button(e_button_close);
      create_button(e_button_up);
      create_button(e_button_down);
      create_button(e_button_minimize);
      create_button(e_button_maximize);
      create_button(e_button_restore);
      create_button(e_button_notify_icon);
      create_button(e_button_transparent_frame);
      create_button(e_button_dock);

      return true;

   }


   bool control_box::get_control_box_button_caption(enum_button ebutton, string &strCaption) const
   {

      bool bOk = true;

      switch (ebutton)
      {
      case e_button_close:
         strCaption = (char)114;
         break;
      case e_button_up:
         strCaption = (char)53;
         break;
      case e_button_down:
         strCaption = (char)54;
         break;
      case e_button_minimize:
         strCaption = (char)48;
         break;
      case e_button_maximize:
         strCaption = (char)49;
         break;
      case e_button_restore:
         strCaption = (char)50;
         break;
      case e_button_notify_icon:
         strCaption = (char)0x69;
         break;
      case e_button_transparent_frame:
         strCaption = (char)' ';
         break;
      case e_button_dock:
         strCaption = (char)0x6E;
         break;

      default:
         bOk = false;
      }

      return bOk;

   }


   enum_stock_icon control_box::get_control_box_button_stock_icon(enum_button ebutton)
   {

      return (enum_stock_icon)((int) ebutton - (int)e_button_begin + (int) e_stock_icon_control_box_begin);

   }


   ::e_status control_box::set_control_box_button_id(enum_button ebutton, id id)
   {

      auto estatus = __defer_construct_new(m_itemmap[ebutton]);

      if (!estatus)
      {

         return estatus;

      }

      m_itemmap[ebutton]->m_id = id;

      m_idmap[id] = ebutton;

      return estatus;

   }


   id control_box::get_control_box_button_id(enum_button ebutton) const
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return ::id();

      }

      return m_itemmap[ebutton]->m_id;

   }


   string control_box::get_control_box_button_tag(enum_button ebutton) const
   {

      switch(ebutton)
      {
         case e_button_close: // stock_icon_close
            return "button_close";
         case e_button_up: // stock_icon_level_up
            return "button_up";
         case e_button_down: // stock_icon_level_down
            return "button_down";
         case e_button_minimize: // stock_icon_iconify
            return "button_minimize";
         case e_button_restore: // stock_icon_restore
            return "button_restore";
         case e_button_maximize: // stock_icon_maximize
            return "button_maximize";
         case e_button_notify_icon: // stock_icon_notify
            return "button_notify_icon";
         case e_button_transparent_frame: // stock_icon_transparent_frame
            return "button_transparent_frame";
         case e_button_dock: // stock_icon_dock
            return "button_dock";
         default:
            break;
      }

      return "(unknown)";

   }


   enum_button control_box::get_control_box_button_type(id id) const
   {

      return m_idmap[id];

   }


   bool control_box::hide_button(enum_button ebutton, bool bHide)
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return false;

      }

      pitem->m_bPresent = !bHide;

      return true;

   }


   bool control_box::has_button(enum_button ebutton) const
   {

      if (m_pframewindow->m_ebuttonaHide.contains(ebutton))
      {

         return false;

      }

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return false;

      }
         
      return pitem->m_bPresent;

   }


   void control_box::reset_layout(::draw2d::graphics_pointer & pgraphics)
   {

      int iDefaultButtonSize = calc_button_size(pgraphics);

      m_sizeButtonDefault = ::size_i32(iDefaultButtonSize,iDefaultButtonSize);


   }


   size_i32 control_box::get_button_size(enum_button ebutton)
   {

      return m_sizeButtonDefault;

   }


   rectangle_i32 control_box::get_button_margin(enum_button ebutton)
   {

      ::rectangle_i32 rectMargin;

      rectMargin.left = 0;
      rectMargin.top = m_iDefaultButtonMargin;
      rectMargin.right = m_iDefaultButtonMargin;
      rectMargin.bottom = m_iDefaultButtonMargin;

      return rectMargin;

   }


   i32 control_box::calc_button_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto dFontHeight = m_fontMarlett->get_height(pgraphics);

      i32 iButtonSize = (::i32) (dFontHeight + m_iDefaultButtonMargin * 3);

      return iButtonSize;

   }


   ::count control_box::get_visible_control_box_button() const
   {

      ::count cVisible = 0;

      for (auto ebutton : m_itemmap.keys())
      {
         
         if (should_show_button(ebutton))
         {

            cVisible++;

         }

      }

      return cVisible++;

   }


   i32 control_box::calc_control_box_width(::draw2d::graphics_pointer & pgraphics)
   {

      m_iDefaultButtonSize = calc_button_size(pgraphics);

      int iWidth = 0;

      for (auto & pitem : m_itemmap.values())
      {

         auto & pbutton = pitem->m_pbutton;

         if (pbutton)
         {

            iWidth += m_iDefaultButtonSize;

            iWidth += m_iDefaultButtonMargin;

         }

      }

      return iWidth;

   }


   __pointer(button) control_box::get_button(enum_button ebutton)
   {

      auto pitem = get_item(ebutton);

      if (!pitem)
      {

         return nullptr;

      }

      return pitem->m_pbutton;

   }


   __pointer(::experience::button) control_box::get_box_button(enum_button ebutton)
   {

      return get_button(ebutton);

   }


   void control_box::set_button_color_system_default_001()
   {

      m_brushButtonBack->create_solid(argb(0, 0, 0, 0));
      m_brushButtonBackSel->create_solid(argb(255, 150, 220, 145));
      m_brushButtonBackFocus->create_solid(argb(255, 150, 220, 145));
      m_brushButtonBackDisabled->create_solid(argb(255, 180, 180, 175));

      m_penButtonBack->create_solid(2, argb(255, 255, 255, 255));
      m_penButtonBackSel->create_solid(2, argb(255, 255, 255, 255));
      m_penButtonBackFocus->create_solid(2, argb(255, 255, 255, 255));
      m_penButtonBackDisabled->create_solid(2, argb(255, 220, 220, 215));

      m_colorButtonFore = argb(255, 255, 255, 255);
      m_colorButtonForeSel = argb(255, 255, 255, 255);
      m_colorButtonForeFocus = argb(255, 255, 255, 255);
      m_colorButtonForeDisabled = argb(255, 220, 220, 215);

   }


   void control_box::on_message_move(::message::message * pmessage)
   {

      ::rectangle_i32 rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      ::rectangle_i32 rectangle;

      get_window_rect(rectangle);

      m_pframewindow->screen_to_client(rectangle);

      m_pframewindow->m_pframe->m_bControlBoxAlignRight = rectangle.center().x > (rectWindow.width() / 2);

//      if (rectangle != *m_pframewindow->m_pframe->get_control_box_rect())
//      {
//
//         *m_pframewindow->m_pframe->get_control_box_rect() = rectangle;
//
//         m_pframewindow->m_millisLastVisualChange.Now();
//
//         //auto pframe = m_pframewindow;
//
//         //if (::is_set(pframe))
//         //{
//
//         //   pframe->defer_save_window_placement();
//
//         //}
//
//      }

   }


   void control_box::on_message_size(::message::message * pmessage)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      output_debug_string("rectangleClient");

   }


   bool control_box::get_font(::write_text::font_pointer & font)
   {

      font = m_fontMarlett;

      return true;

   }


   void control_box::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {
      
#ifdef MACOS
      
      // clip
      //return;
      
#endif

      try
      {

         ::rectangle_i32 rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rectangle_i32 rectangleClient;

         bool bFirst = true;

         if (pdrawcontext != nullptr)
         {

            get_client_rect(rectangleClient);

            rectangleClient.bottom++;
            rectangleClient.right++;

            rectClip = rectangleClient;

            bFirst = false;

         }
         
         if(!m_pshapeaClip)
         {
            
            __construct_new(m_pshapeaClip);

            ::user::interaction * pinteraction = this;

            ::rectangle_i32 rectFocus;

            while (pinteraction != nullptr)
            {

               pinteraction->get_window_rect(rectFocus);

               screen_to_client(rectFocus);

               m_pshapeaClip->add_item(__new(rectangle_shape(rectFocus)));

               m_pshapeaClip->add_item(__new(intersect_clip_shape));

               pinteraction = pinteraction->get_parent();
               
            }

         }
         
         pgraphics->reset_clip();

         pgraphics->add_shapes(*m_pshapeaClip);

      }
      catch (...)
      {

         throw ::exception::exception(error_failed, "no more a u");

      }

   }


} // namespace experience



