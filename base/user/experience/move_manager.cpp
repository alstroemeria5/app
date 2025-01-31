#include "framework.h"
#include "base/user/experience/_experience.h"


namespace experience
{

   
   move_manager::move_manager()
   {

      m_iConsiderMove = 0;
      m_bMoving = false;
      //SetSWPFlags(0);
      m_eborderMask = e_border_all;

   }


   move_manager::~move_manager()
   {

   }


   ::e_status move_manager::initialize_move_manager(::experience::frame_window* pframewindow)
   {

      auto estatus = ::object::initialize(pframewindow);

      if (!estatus)
      {

         return estatus;

      }

      m_pframewindow = pframewindow;

      return estatus;

   }


   bool move_manager::on_message_left_button_down(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      m_stateBefore = m_pframewindow->layout().sketch();

      auto pointCursor = pmouse->m_point;

      ::rectangle_i32 rectWindow;

      m_pframewindow->get_window_rect(rectWindow);

      m_pointCursorOrigin = pointCursor;

      m_pointWindowOrigin = rectWindow.top_left();

      m_pointMove = m_pointWindowOrigin;

      m_pframewindow->set_mouse_capture();

      m_iConsiderMove = 0;

      m_bMoving = true;

      m_pframewindow->on_start_layout_experience(e_layout_experience_moving);

      pmouse->m_bRet = true;

      return true;

   }


   bool move_manager::on_message_mouse_move(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      ASSERT(pmouse->m_id == e_message_mouse_move || pmouse->m_id == e_message_non_client_mouse_move);

      auto psession = get_session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

      pmouse->m_pcursor = pcursor;

      m_pframewindow->set_mouse_cursor(pcursor);

      if (!window_is_moving())
      {

         return false;

      }

      auto pframewindow = m_pframewindow;

      auto pointMove = m_pointWindowOrigin + (pmouse->m_point - m_pointCursorOrigin);

      if (pframewindow->get_parent() != nullptr)
      {

         pframewindow->screen_to_client(pointMove);

      }

      if (pframewindow->find_i32("ysnap") > 1)
      {

         pointMove.y -= pointMove.y % pframewindow->find_i32("ysnap");

      }

      m_pointMove = pointMove;

      m_iConsiderMove++;

      {

         ::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

         if (::is_docking_appearance(pframewindow->layout().sketch().display()))
         {

            pframewindow->m_pframe->defer_frame_placement_snapping();

         }
         else
         {

            pframewindow->move_to(pointMove.x, pointMove.y);

         }

         pframewindow->set_need_redraw();

      }

      pframewindow->post_redraw();

      pmouse->m_bRet = true;

      return true;

   }


   bool move_manager::on_message_left_button_up(::message::mouse * pmouse)
   {

      if (!m_pframewindow->is_moving_enabled())
      {

         return false;

      }

      if (!window_is_moving())
      {

         return false;

      }

      bool bApply = !is_docking_appearance(m_pframewindow->layout().sketch().display());

      window_stop_moving(bApply, pmouse);

      return true;

   }


   //bool move_manager::on_message_set_cursor(::message::set_cursor * psetcursor)
   //{

   //   if (!m_pframewindow->is_moving_enabled())
   //   {

   //      return false;

   //   }

   //   if (!window_is_moving())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   bool move_manager::window_stop_moving(bool bApply, ::message::mouse * pmouse)
   {

      if (!m_bMoving)
      {

         return false;

      }

      m_bMoving = false;

      __pointer(::base::session) psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      if (!consider_move())
      {

         {

            ::user::lock_sketch_to_design lockSketchToDesign(m_pframewindow);

            m_pframewindow->layout().sketch() = m_stateBefore;

         }

         m_pframewindow->set_need_redraw();

      }
      else if (bApply)
      {

         auto rectRequest = m_pframewindow->screen_rect();

         index iMatchingMonitor = m_pframewindow->good_move(rectRequest, nullptr);

         if (iMatchingMonitor >= 0)
         {

            if (!pmouse)
            {

               pmouse->m_point = -m_pointWindowOrigin + rectRequest.top_left() + m_pointCursorOrigin;

            }

         }

      }

      m_pframewindow->on_end_layout_experience(e_layout_experience_moving);

      return true;

   }


   bool move_manager::set_frame_window(frame_window * pframewindow)
   {

      m_pframewindow = pframewindow;

      return true;

   }


   bool move_manager::window_is_moving()
   {

      return m_bMoving;

   }


   bool move_manager::consider_move()
   {

      return m_iConsiderMove > 10;

   }


   e_border move_manager::GetBorderMask()
   {

      return m_eborderMask;

   }


   void move_manager::SetBorderMask(const e_border & emask)
   {

      m_eborderMask = emask;

   }


   bool move_manager::_001OnTimer(::u32 uEvent)
   {

      return false;

   }


} // namespace experience



