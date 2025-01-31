#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   scroll_bar::scroll_bar()
   {

      m_bParentScrollX = false;
      m_bParentScrollY = false;

      m_scrollinfo.nMin    = 0;
      m_scrollinfo.nMax    = 100;
      m_scrollinfo.nPage   = 10;
      m_scrollinfo.nPos    = 0;

   }


   scroll_bar::~scroll_bar()
   {

   }


   void scroll_bar::post_scroll_message(enum_scroll_command ecommand)
   {

      auto pscroll = __new(::message::scroll);

      pscroll->m_ecommand = ecommand;

      if(m_bTracking)
      {

         pscroll->m_nPos = m_scrollinfo.nTrackPos;

      }
      else
      {

         pscroll->m_nPos = m_scrollinfo.nPos;

      }

      if(m_eorientation == e_orientation_horizontal)
      {

         pscroll->m_id = e_message_hscroll;

      }
      else
      {

         pscroll->m_id = e_message_vscroll;

      }

      __pointer(::user::interaction) puiParent = get_parent();

      puiParent->post(pscroll);

   }


   //bool scroll_bar::create_interaction(enum_orientation eorientation, ::user::interaction * puiParent)
   //{

   //   m_eorientation = eorientation;

   //   return create_interaction(puiParent);

   //}


   point_i32 scroll_bar::get_ascendant_viewport_offset() const
   {

      if (get_parent() == nullptr)
      {

         return nullptr;

      }

      return get_parent()->get_ascendant_viewport_offset();

   }


   point_i32 scroll_bar::get_parent_viewport_offset() const
   {

      return nullptr;

   }


   bool scroll_bar::GetTrackRect(RECTANGLE_I32* prectangle, ::draw2d::graphics_pointer & pgraphics)
   {

      return false;

   }


   ::color::color scroll_bar::scrollbar_color_strong(::user::style* pstyle, ::user::enum_element eelement)
   {

      if (m_itemCurrent == eelement || m_itemHover== eelement)
      {

         return argb(130, 190, 180, 250);

      }
      else
      {

         return argb(150, 150, 150, 150);

      }

   }


   ::color::color scroll_bar::scrollbar_color(::user::style * pstyle, ::user::enum_element eelement)
   {

      if(m_itemCurrent == eelement || m_itemHover== eelement)
      {

         return argb(100, 190, 180, 250);

      }
      else
      {

         return argb(150, 150, 150, 150);

      }

   }


   ::color::color scroll_bar::scrollbar_border_color(::user::style* pstyle, ::user::enum_element eelement)
   {

      if(m_itemCurrent == eelement || m_itemHover== eelement)
      {

         return argb(190, 180, 180, 180);

      }
      else
      {

         return argb(190, 160, 160, 160);

      }

   }


   ::color::color scroll_bar::scrollbar_lite_border_color(::user::style* pstyle, ::user::enum_element eelement)
   {

      if(m_itemCurrent == eelement || m_itemHover== eelement)
      {

         return argb(190, 90, 110, 180);

      }
      else
      {

         return argb(190, 110, 110, 100);

      }

   }


   ::color::color scroll_bar::scrollbar_draw_color(::user::style* pstyle, ::user::enum_element eelement)
   {

      if (m_itemCurrent == eelement || m_itemHover == eelement)
      {

         return argb(127, 90, 90, 90);

      }
      else
      {

         return argb(127, 65, 65, 65);

      }

   }


   void scroll_bar::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {
         
         //return;
         
         
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

         ::user::interaction * pinteraction = this;

         ::rectangle_i32 rectFocus;

         index i = 0;

         while (pinteraction != nullptr)
         {

            if (i != 1)
            {

               pinteraction->get_window_rect(rectangleClient, e_layout_design);

               pinteraction->get_client_rect(rectFocus);

               rectFocus.offset(rectangleClient.top_left());

               screen_to_client(rectFocus, e_layout_design);

               rectFocus.bottom++;
               rectFocus.right++;

               pgraphics->intersect_clip(rectFocus);

            }

            i++;

            pinteraction = pinteraction->get_parent();

         }

      }
      catch (...)
      {

         throw ::exception::exception(error_exception, "no more a window");

      }

   }




} // namespace user









