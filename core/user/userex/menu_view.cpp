#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



menu_view::menu_view()
{
   
}


void menu_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
{
   ::user::form_view::on_subject(psubject, pcontext);
}


void menu_view::on_control_event(::user::control_event * pevent)
{

   auto papplication = get_application();

   papplication->on_control_event(pevent);

   if(pevent->m_bRet)
   {

      return;

   }

   if(m_pcallback != nullptr)
   {

      m_pcallback->on_control_event(pevent);

   }

   if(get_parent() != nullptr)
   {

      get_parent()->on_control_event(pevent);

      if(pevent->m_bRet)
      {

         return;

      }

   }

}


void menu_view::install_message_routing(::channel * pchannel)
{
   ::user::form::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &menu_view::on_message_create);
//   //MESSAGE_LINK(e_message_timer, pchannel, this, &menu_view::_001OnTimer);
   //MESSAGE_LINK(WM_USER + 123, pchannel, this, &menu_view::_001OnUser123);

}


void menu_view::on_message_create(::message::message * pmessage)
{
   pmessage->previous();
}


void menu_view::_001OnTimer(::timer * ptimer)
{

   ::user::form_view::_001OnTimer(ptimer);;

   if(m_pcallback != nullptr)
   {

      ::user::control_event ev;

      ev.m_eevent = ::user::e_event_timer;

      ev.m_uiEvent = ptimer->m_uEvent;
      
      ev.m_etimer = ptimer->m_etimer;

      ev.m_puserinteraction = this;

      auto papplication = get_application();

      papplication->on_control_event(&ev);

      if(ev.m_bRet)
      {

         return;

      }

      m_pcallback->on_control_event(&ev);

   }

   if(ptimer->m_uEvent == 24)
   {

      KillTimer(24);

      top_level_frame()->EndModalLoop(e_dialog_result_ok);

   }

}


//void menu_view::_001OnUser123(::message::message * pmessage)
//{
//   __pointer(::user::message) pusermessage(pmessage);
//   if(pusermessage->m_wparam == 0x80000001)
//   {
//      get_top_level()->EndModalLoop(e_dialog_result_ok);
//      return;
//   }
//   if(m_pcallback != nullptr)
//   {
//      m_pcallback->OnUser123(pusermessage->m_wparam, pusermessage->m_lparam);
//   }
//}
