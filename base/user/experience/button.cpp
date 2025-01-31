#include "framework.h"
#include "base/user/experience/_experience.h"


namespace experience
{


   button::button()
   {

   }


   button::~button()
   {

   }


   void button::install_message_routing(::channel* pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      if(m_ebutton == e_button_dock)
      {

         auto pdockmanager = m_pcontrolbox->m_pframewindow->m_pdockmanager.get();

         MESSAGE_LINK(e_message_left_button_down   , pchannel, pdockmanager, &::experience::dock_manager::dock_button_on_message_left_button_down  );
         MESSAGE_LINK(e_message_mouse_move         , pchannel, pdockmanager, &::experience::dock_manager::dock_button_on_message_mouse_move        );
         MESSAGE_LINK(e_message_left_button_up     , pchannel, pdockmanager, &::experience::dock_manager::dock_button_on_message_left_button_up    );

      }

   }


   void button::UpdateWndRgn()
   {

   }


   void button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {
      
#ifdef MACOS

      // clip
      //return;

#endif

      //return;

      try
      {

         if (string(type_name()).contains_ci("control_box"))
         {

            output_debug_string("control_box");

         }

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

            index i = 0;

            while (pinteraction != nullptr)
            {

               pinteraction->get_client_rect(rectFocus);

               pinteraction->client_to_host(rectFocus);

               host_to_client(rectFocus);

               m_pshapeaClip->add_item(__new(rectangle_shape(rectFocus)));
               
               m_pshapeaClip->add_item(__new(intersect_clip_shape));

               i++;

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


   void button::on_hit_test(::user::item & item)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pregion.is_null() || !m_pregion->contains(item.m_pointHitTest))
      {

         if(m_bMouseHoverOnCapture)
         {

            if(has_mouse_capture())
            {

               item = ::user::e_element_non_client;

               return;

            }

         }
         else if(m_ebutton == e_button_dock)
         {

            if(m_pcontrolbox->m_pframewindow->dock_manager()->window_is_docking())
            {

               item = ::user::e_element_non_client;

               return;

            }

         }

      }

      ::user::button::on_hit_test(item);

   }



   bool button::keyboard_focus_is_focusable() const
   {

      return false;

   }


} // namespace experience



