#include "framework.h"


namespace experience
{


   namespace tranquillum
   {

      control_box::control_box()
{
   m_iDefaultButtonMargin = 0;

   m_fontMarlett->create_point_font("Marlett", 24);

}


control_box::~control_box()
{

}


void control_box::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
{


}

void control_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   if(GetTopLevel()->frame_is_transparent() && GetTopLevel() != GetActiveWindow())
   {

      return;

   }

   ::rect rectClient;

   get_client_rect(rectClient);

   if (rectClient.area() <= 0)
      return;

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   COLORREF crBackground;

   if(GetTopLevel()->frame_is_transparent())
   {

      crBackground = ARGB(84,colorref_get_r_value(m_crBackground),colorref_get_g_value(m_crBackground),colorref_get_b_value(m_crBackground));

   }
   else
   {

      crBackground = m_crBackground;

   }

   pgraphics->fill_rect(rectClient, m_crBackground);

}


void control_box::_001OnShowWindow(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}

void control_box::_001OnLButtonDown(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}

void control_box::_001OnLButtonUp(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   set_need_redraw();

}



void control_box::_001OnTimer(::timer * ptimer)
{

   ::experience::control_box::_001OnTimer(ptimer);

}


void control_box::install_message_routing(::channel * pchannel)
{

   ::experience::control_box::install_message_routing(pchannel);

   IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &control_box::_001OnShowWindow);
   IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &control_box::_001OnLButtonDown);
   IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &control_box::_001OnLButtonUp);
//   IGUI_MSG_LINK(WM_SIZE, pchannel, this, &control_box::_001OnSize);
//   //IGUI_MSG_LINK(WM_TIMER, pchannel, this, &control_box::_001OnTimer);

}



         } // namespace tranquillum

   } // namespace experience



