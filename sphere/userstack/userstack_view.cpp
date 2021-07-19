#include "framework.h"
#include "acme/const/timer.h"


namespace userstack
{


   view::view(::object * pobject) :
      ::object(pobject),
      m_font(e_create)
   {

      m_font->create_point_font(pnode->font_name(e_font_sans_ex), 8.4);
      m_bDestroy = false;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_i_winactionarea = 4;
      m_i_winactionarea_h = 49;
      m_i_winactionarea_w = 49;
      m_ppaneview = nullptr;

   }


   view::~view()
   {

   }


   void view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::on_message_destroy);
      MESSAGE_LINK(e_message_paint, pchannel, this, &view::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &view::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &view::on_message_context_menu);
      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &view::on_message_set_cursor);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &view::on_message_left_button_up);

//

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::view drawing

   void view::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics


   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // ::view message handlers

   // vmpLightView.cpp : implementation of the ::view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::view


   bool view::pre_create_window(::user::system * pusersystem)
   {

      return ::user::impact::pre_create_window(pusersystem);
   }


   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      UNREFERENCED_PARAMETER(psubject);

   }


   void view::on_message_destroy(::message::message * pmessage)
   {
      ::user::impact::on_message_destroy(pmessage);

   }



   void view::_001OnPaint(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);


   }


   void view:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }

   void view::on_message_create(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;

      SetTimer(888888, 2000, nullptr);

      __pointer(frame) pframe = GetTypedParent < frame > ();

      pframe->m_pview = this;
      pframe->m_pdocument = get_document();


      string strImageDir = pcontext->m_papexcontext->dir().appdata() / "image";
      m_straImagePath.m_pprovider = get_application();
      m_straImagePath.rls(strImageDir);

      for(i32 i = 0; i < m_straImagePath.get_size();)
      {
         if(pcontext->m_papexcontext->dir().is(m_straImagePath[i]))
         {
            m_straImagePath.erase_at(i);
         }
         else
         {
            i++;
         }
      }



      SetTimer(e_timer_backview, 83, nullptr);  // maximum. 12 fps
      SetTimer(21977, 20 * 1000, nullptr);  // maximum. 12 fps

      check_apps();

/*      m_pimageBk = load_matter_image("casweden1.png");


/*      m_pimageV = load_matter_image("wild_mountains_and_valleys-123.png");
/*      m_pimage_veriwell = load_matter_image("veriwell_2008_green_h49.png");
/*      m_pimage_winactionarea = load_matter_image("winactionarea.png");

      if(!psession->m_bShowPlatform)
      {
         return;
      }

      m_ppaneview = (create_view(__type(pane_view), get_document(), this, 102));


   }

   void view::on_message_context_menu(::message::message * pmessage)
   {
//      __pointer(::message::context_menu) pcontextmenu(pmessage);
//      ::point_i32 point = pcontextmenu->GetPoint();

   }

   void view::_001OnTabClick(i32 iTab)
   {
      if(iTab == 1)
      {
         message_box(nullptr, "Playlist");
      }
   }

   void view::on_message_set_cursor(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();

   }

   void view::pre_translate_message(::message::message * pmessage)
   {
      ::user::impact::pre_translate_message(pmessage);
   }


   ::user::document * view::get_document()
   {

      return ::user::impact::get_document();

   }


   void view::_001OnTimer(::timer * ptimer)
   {

      BASE::_001OnTimer(ptimer);

      switch(ptimer->m_uEvent)
      {
      case e_timer_backview:
      {
         //gcom::backview::user_interaction::image_change_post_event(gcom::backview::event_timer);
      }
      break;
      }

      if(ptimer->m_uEvent == 21977)
      {
         check_apps();
      }
      else if(ptimer->m_uEvent == 888888)
      {
         psession->check_topic_file_change();
      }

   }


   void view::GetAreaThumbRect(RECTANGLE_I32 * lprect, i32 iArea)
   {
      
      ::rectangle_i32 rectangleClient = get_client_rect();
      
      if(iArea == m_iV)
      {
         lprect->bottom = rectangleClient.bottom;
         lprect->top = lprect->bottom - m_iVH;
         lprect->left = 1;
         lprect->right = lprect->left + m_iVW;
      }
      else if(iArea == m_i_veriwell)
      {
         lprect->bottom = rectangleClient.bottom;
         lprect->top = lprect->bottom - m_i_veriwell_h;
         lprect->left = 1 + m_iVW + 5;
         lprect->right = lprect->left + m_i_veriwell_w;
      }
      else if(iArea == m_i_winactionarea)
      {
         lprect->bottom = rectangleClient.bottom;
         lprect->top = lprect->bottom - m_i_winactionarea_h;
         lprect->left = 1 + m_iVW + 5 + m_i_veriwell_w + 5;
         lprect->right = lprect->left + m_i_winactionarea_w;
      }
   }


   void view::on_message_left_button_up(::message::message * pmessage)
   {
      __pointer(::message::mouse) pmouse(pmessage);
      pmouse->m_lresult = 1;
      KillTimer(5432180);
      auto point = pmouse->m_point;
      screen_to_client(point);
   }

   void view::check_apps()
   {
      //   if(::IsDebuggerPresent())
      //    return;
      //if(!m_bEnsureApps)
      // return;
#ifdef WINDOWS_DESKTOP
      if(::IsWindow(m_oswindowWinactionarea) &&
            ::IsWindow(m_oswindowCommand) &&
            ::IsWindow(m_oswindowWinutil) &&
            ::IsWindow(m_oswindowBergedge))
      {
         return;
      }
      m_oswindowWinservice1       =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::winservice_1");
      m_oswindowWinactionarea     =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::winactionarea");
      m_oswindowCommand           =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::command");
      m_oswindowWinutil           =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::winutil");
      m_oswindowBergedge          =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::bergedge");
#else
      __throw(todo);
#endif
   }


   void view::on_hit_test(::user::item & item)
   {
      
      ::rectangle_i32 rectArea;
      
      GetAreaThumbRect(rectArea, m_iV);

      if(rectArea.contains(item.m_pointHitTest))
      {
      
         item ={ ::user::e_element_area, m_iV };

         return;
         
      }

      GetAreaThumbRect(rectArea, m_i_veriwell);

      if(rectArea.contains(item.m_pointHitTest))
      {

         item = { ::user::e_element_area, m_i_veriwell };

         return;

      }

      GetAreaThumbRect(rectArea, m_i_winactionarea);

      if(rectArea.contains(item.m_pointHitTest))
      {
         
         item = { ::user::e_element_area, m_i_winactionarea };

         return;

      }
      
      item = ::user::e_element_none;
      
   }


   ::u32 c_cdecl view::ThreadProcShowWindow(LPVOID lpparam)
   {
      UNREFERENCED_PARAMETER(lpparam);
      return 0;
   }


   void view::mt_show_window(oswindow oswindow, i32 iShow)
   {
      UNREFERENCED_PARAMETER(oswindow);
      UNREFERENCED_PARAMETER(iShow);
   }

   /*void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {
      ::rectangle_i32 rectangleClient;
      get_client_rect(rectangleClient);
      if(m_ppaneview != nullptr)
      {
         m_ppaneview->set_window_position(e_zorder_top, rectangleClient.top, rectangleClient.left, rectangleClient.width(), rectangleClient.height(), SWP_SHOWWINDOW);
      }
      else
      {
         user::interaction * pinteraction = get_top_child();
         if(pinteraction != nullptr)
         {
            pinteraction->set_window_position(e_zorder_top, rectangleClient.top, rectangleClient.left, rectangleClient.width(), rectangleClient.height(), SWP_SHOWWINDOW);
         }
      }
      ::user::show < ::user::interaction >::on_layout(pgraphics);
      gcom::backview::user::interaction::on_layout(pgraphics);
   }*/

   void view::_000OnMouse(::message::mouse * pmouse)
   {
      try
      {
         if(!_001IsPointInside(pmouse->m_point))
            return;
      }
      catch(...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      user::interaction * pinteraction = top_child();
      try
      {
         while(pinteraction != nullptr)
         {

            try
            {

               if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
               {

                  try
                  {

                     pinteraction->_000OnMouse(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return;

                     }

                  }
                  catch(...)
                  {

                  }

               }

               pinteraction = pinteraction->under_sibling();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         if(m_pimpl == nullptr)
            return;

         route_message(pmouse);

         if(pmouse->m_lresult != 0)
            return;

      }
      catch(...)
      {
      }
   }


}  // namespace userstack



