#include "framework.h"
#include "axis/user/_user.h"
#include "acme/constant/timer.h"


void scroll_x(RECT32 * prect, double dRateX, const ::rectangle & rectangle)
{

   ::i32 w = ::width(prect);

   prect->left = (::i32) (rectangle.left + (rectangle.width() - w) * dRateX);

   prect->right = prect->left + w;

}


namespace user
{


   check_box::check_box(e_style estyle)
   {

      m_millisAnimationPeriod = 300_ms;

      m_estyle = estyle;

   }


   check_box::~check_box()
   {

   }


   void check_box::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      if(echeck != ::check_unchecked && echeck != ::check_checked && echeck != ::check_tristate)
      {

         // default value when setting a value that does not match the ones above

         echeck = ::check_checked;

      }

      if(this->echeck() != echeck)
      {

         check::_001SetCheck(echeck, context);

         ::user::control_event ev;

         ev.m_puserinteraction = this;

         ev.m_id = m_id;

         ev.m_eevent = ::user::e_event_set_check;

         ev.m_actioncontext = context;

         route_control_event(&ev);

         set_need_redraw();

         post_redraw();

      }

   }


   void check_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_estyle == style_toggle_switch)
      {

         _001OnDrawToggleSwitch(pgraphics);

      }
      else if (m_estyle == style_red_green_circle)
      {

         _001OnDrawRedGreenCircle(pgraphics);

      }
      else
      {

         _001OnDrawNormal(pgraphics);

      }

   }


   void check_box::_001OnDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::axis::style) pstyle = get_style(pgraphics);

      if(pstyle)
      {

         if (pstyle->_001DrawCheckBox(pgraphics, this))
         {

            return;

         }

      }

      ::aura::draw_context drawcontext;

      drawcontext.m_bListItemHover = hover_item().is_set();

      __keep(pgraphics->m_pdrawcontext, &drawcontext);

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      int w = rectangleClient.width();

      int h = rectangleClient.height();

      if (w <= 0 || h <= 0)
      {

         return;

      }

      auto echeck = this->echeck();

      ::draw2d::savedc savedc(pgraphics);

      pgraphics->OffsetViewportOrg(rectangleClient.left, rectangleClient.top);

      ::rectangle rectCheckBox;

      ::rectangle rectText;

      {

         int iSize = minimum(15 * w / 15, 15 * h / 15);

         rectCheckBox.left = 0;
         rectCheckBox.top = 0;
         rectCheckBox.right = iSize;
         rectCheckBox.bottom = iSize;

         rectText = rectangleClient;

         rectText.left = rectCheckBox.right + 4;

         if (echeck == ::check_tristate)
         {

            pgraphics->fill_rectangle(rectCheckBox, argb(255, 220, 220, 220));

         }

         if (drawcontext.m_bListItemHover)
         {

            pgraphics->draw_rectangle(rectCheckBox, argb(255, 60, 120, 200));

         }
         else
         {

            pgraphics->draw_rectangle(rectCheckBox, argb(255, 128, 128, 128));

         }

         if (echeck == ::check_tristate || echeck == ::check_checked)
         {

            if (pstyle)
            {

               pstyle->draw_check(echeck, rectCheckBox, pgraphics);

            }

         }

      }

      {

         string strText;

         get_window_text(strText);

         int iDrawParams = e_align_left_center | DT_SINGLELINE;

         pgraphics->set_font(this, ::user::e_element_none);

         color32_t crText;

         if (drawcontext.m_bListItemHover)
         {

            crText = argb(255, 0, 0, 0);

         }
         else
         {

            crText = argb(255, 0, 0, 0);

         }

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(strText, rectText, iDrawParams);

      }

   }


   void check_box::_001OnDrawToggleSwitch(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::axis::style) pstyle = get_style(pgraphics);

      if(pstyle)
      {

         if (pstyle->_001DrawCheckBox(pgraphics, this))
         {

            return;

         }

      }

      ::aura::draw_context drawcontext;

      drawcontext.m_bListItemHover = hover_item().is_set();

      __keep(pgraphics->m_pdrawcontext, &drawcontext);

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      int w = rectangleClient.width();

      int h = rectangleClient.height();

      w--;

      h--;

      if (w % 2 == 0)
      {

         w--;

      }

      if (h % 2 == 0)
      {

         h--;

      }

      if (w <= 0 || h <= 0)
      {

         return;

      }

      //::enum_check echeck = _001GetCheck();

      ::draw2d::savedc savedc(pgraphics);

      if (w > h * 2)
      {

         w = h * 2;

      }
      else
      {

         h = w / 2;

      }

      ::rectangle rectangle(1, 1, w-2, h-2);

      ::rectangle rectEllipse(1, 1, h-2, h-2);

      //double dNow = ::get_millis();

      ::draw2d::path_pointer point(e_create);

      ::rectangle rectL(1, 1, h-2, h-2);

      auto rectR = rectangle_i32_dimension(h-2, 1, h-2, h-2);

      point->add_arc(rectL, -90_degree, -180_degree);

      point->add_line((rectL.left + rectL.right) / 2, rectL.bottom);

      point->add_line((rectR.left + rectR.right) / 2, rectR.bottom);

      point->add_arc(rectR, 90.0, -180.0);

      point->add_line((rectR.left + rectR.right) / 2, rectR.top);

      point->add_line((rectL.left + rectL.right) / 2, rectL.top);

      point->close_figure();

      ::draw2d::pen_pointer point1(e_create);

      ::draw2d::pen_pointer p0(e_create);

      ::draw2d::brush_pointer br1(e_create);

      point1->create_solid(2.0, argb(255, 0, 0, 0));

      p0->create_solid(2.0, argb(255, 90, 150, 255));

      point1->m_ealign = draw2d::pen::e_align_center;

      br1->create_solid(argb(255, 90, 150, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      double dRate = m_millisAnimationStart.period_rate(m_millisAnimationPeriod);

      if (dRate < 1.0)
      {

         bool bComplement;

         if (echeck() == ::check_unchecked)
         {

            bComplement = true;

         }
         else
         {

            bComplement = false;

         }

         color32_t color32 = argb(255, 255, 255, 255);

         ::draw2d::brush_pointer br(e_create);

         m_dPosition = ::sin((::aura::get_system()->math().get_pi() / 2.0) * dRate);

         double dRate = m_dPosition;

         if (bComplement)
         {

            dRate = 1.0 - dRate;

         }

         br1->m_color = (br1->m_color.operator color32_t() & 0xffffff) | ((byte(255.0 * dRate)) << 24);

         br1->set_modified();

         p0->m_color = br1->m_color;

         p0->set_modified();

         pgraphics->set(br1);
         pgraphics->set(p0);

         pgraphics->path(point);

         br->create_solid(argb(255,
                               (byte)((double) colorref_get_r_value(color32) * dRate),
                               (byte)((double) colorref_get_g_value(color32) * dRate),
                               (byte)((double) colorref_get_b_value(color32) * dRate)));

         ::scroll_x(rectEllipse, dRate, rectangle);

         rectEllipse.rate(0.6);

         pgraphics->set(br);

         pgraphics->fill_ellipse(rectEllipse);

         byte bAlphaP1 = (byte) (255.0 * (1.0 - dRate));

         color32_t crP1 = argb(bAlphaP1, 0, 0, 0);

         point1->create_solid(2.0, crP1);

         point1->set_modified();

         pgraphics->set(point1);

         pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

         pgraphics->draw_path(point);


      }
      else
      {

         if (echeck() == ::check_unchecked)
         {

            rectEllipse.Align({e_align_left, e_align_vertical_center}, rectangle);

            rectEllipse.rate(0.6);

            ::draw2d::brush_pointer br(e_create);

            br->create_solid(argb(255, 0, 0, 0));

            pgraphics->set(br);

            pgraphics->fill_ellipse(rectEllipse);

            point1->create_solid(2.0, argb(255, 0, 0, 0));

            pgraphics->set(point1);

            pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

            pgraphics->draw_path(point);


         }
         else
         {

            pgraphics->set(br1);

            pgraphics->set(p0);

            pgraphics->path(point);

            rectEllipse.Align(e_align_right | e_align_vertical_center, rectangle);

            rectEllipse.rate(0.6);

            ::draw2d::brush_pointer br(e_create);

            br->create_solid(argb(255, 255, 255, 255));

            pgraphics->set(br);

            pgraphics->fill_ellipse(rectEllipse);

         }

      }

   }


   void check_box::_001OnDrawRedGreenCircle(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      int iMin = maximum(rectangleClient.min_dim() -1, 1);

      ::rectangle rectCheckBox;
      rectCheckBox.left = 1;
      rectCheckBox.top = 1;
      rectCheckBox.right = iMin + 1;
      rectCheckBox.bottom = iMin + 1;

      color32_t crPen = argb(255, 0, 0, 0);
      color32_t crBrush;

      if (echeck() == ::check_checked)
      {

         crBrush = argb(255, 100, 220, 120);

      }
      else if (echeck() == ::check_unchecked)
      {

         crBrush = argb(255, 220, 220, 100);

      }
      else
      {

         crBrush = argb(255, 128, 128, 128);

      }

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, crPen);

      pgraphics->set(pen);

      ::draw2d::brush_pointer brush(e_create);

      brush->create_solid(crBrush);

      pgraphics->set(brush);

      pgraphics->ellipse(rectCheckBox);
      //   pgraphics->draw3d_rect(rectCheckBox, argb(255, 128, 128, 128), argb(255, 128, 128, 128));
      //   if (m_echeck == check_tristate
      //      || m_echeck == check_checked)
      //   {
      //      ::draw2d::pen_pointer pen(e_create);
      //      pen->create_solid(1, m_echeck == check_checked ? argb(255, 0, 0, 0) : argb(255, 96, 96, 96));
      //      pgraphics->set(pen);
      //      pgraphics->move_to(2, 8);
      //      pgraphics->line_to(6, 12);
      //      pgraphics->line_to(13, 5);
      //      pgraphics->move_to(2, 9);
      //      pgraphics->line_to(6, 13);
      //      pgraphics->line_to(13, 6);
      //   }
      //}
      //pgraphics->OffsetViewportOrg(-rectangleClient.left, -rectangleClient.top);

   }


   void check_box::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == e_timer_check_toggle_animation)
      {

         set_need_redraw();

         post_redraw();

         if (m_millisAnimationStart.elapsed() > m_millisAnimationPeriod)
         {

            KillTimer(ptimer->m_uEvent);

         }

      }
//      else if (ptimer->m_uEvent == e_timer_command_probe)
//      {
//
//         ::user::menu_command command(this);
//
//         command.m_id = m_id;
//
//         command.m_puiOther = this;
//
//         try
//         {
//
//            _001SendCommandProbe(&command);
//
//         }
//         catch(...)
//         {
//         }
//
//      }

      ::user::interaction::_001OnTimer(ptimer);

   }


   void check_box::on_message_key_down(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void check_box::on_message_key_up(::message::message * pmessage)
   {

      auto pkey = pmessage->m_pkey;

      if(pkey->m_ekey == ::user::e_key_space)
      {

         _001ToggleCheck(::e_source_user);

      }

   }


   bool check_box::on_click(const ::user::item & item)
   {

      m_dPosition = 0.0;

      m_millisAnimationStart.Now();

      SetTimer(e_timer_check_toggle_animation, 12);

      _001ToggleCheck(::e_source_user);

      return true;


   }


   void check_box::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      interaction::on_subject(psubject, pcontext);

   }


   void check_box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      install_simple_ui_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &check_box::on_message_create);

   }


   void check_box::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      m_ppropertyCheck = fetch_property(m_id, true);

      add_update_notification(m_ppropertyCheck);

   }


} // namespace user
