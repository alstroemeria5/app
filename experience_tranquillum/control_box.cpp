#include "framework.h"


namespace experience
{


   namespace tranquillum
   {

      
      control_box::control_box()
      {
   
         m_iDefaultButtonMargin = 1;

         m_colorBackground.set(0, 0, 0, 0);

      }


      control_box::~control_box()
      {

      }


      void control_box::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
      {


      }
   

      void control_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if((get_top_level()->frame_is_transparent() && !get_top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
         {

            return;

         }

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         if (rectangleClient.area() <= 0)
            return;

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         ::color::color crBackground;

         if(get_top_level()->frame_is_transparent())
         {

            crBackground = alpha(90,m_colorBackground);

         }
         else
         {

            crBackground = m_colorBackground;

         }

         if (m_colorBackground.non_transparent())
         {

            pgraphics->fill_rectangle(rectangleClient, m_colorBackground);

         }

      }


      void control_box::on_message_show_window(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);

      }
   
   
      void control_box::on_message_create(::message::message * pmessage)
      {
         
         m_fontMarlett.create(this);

         m_fontMarlett->create_point_font("Marlett", 20);
      
      }



   
      void control_box::on_message_left_button_down(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);

      }
   

      void control_box::on_message_left_button_up(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);

         set_need_redraw();

      }


      void control_box::_001OnTimer(::timer * ptimer)
      {

         ::experience::control_box::_001OnTimer(ptimer);

      }


      void control_box::install_message_routing(::channel * pchannel)
      {

         ::experience::control_box::install_message_routing(pchannel);

         MESSAGE_LINK(e_message_show_window, pchannel, this, &control_box::on_message_show_window);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &control_box::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &control_box::on_message_left_button_up);
         MESSAGE_LINK(e_message_create, pchannel, this, &control_box::on_message_create);
      //   MESSAGE_LINK(e_message_size, pchannel, this, &control_box::on_message_size);
      //   //MESSAGE_LINK(e_message_timer, pchannel, this, &control_box::_001OnTimer);

      }


   } // namespace tranquillum


} // namespace experience



