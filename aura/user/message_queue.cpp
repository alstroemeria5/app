#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   message_queue::message_queue()
   {

      m_plistener          = nullptr;

   }


   message_queue::~message_queue()
   {

   }


   bool message_queue::create_message_queue(const char * pszName,::user::message_queue_listener * plistener)
   {

      m_plistener = plistener;

      if (!::user::interaction::create_message_queue(pszName))
      {

         return false;

      }

      if (m_plistener)
      {

         m_plistener->install_message_queue_routing(this);

      }

      return true;



   }


   void message_queue::message_handler(::user::message * pusermessage)
   {

      message_queue_message_handler(pusermessage);

      if (pusermessage->m_bRet)
      {

         return;

      }

      ::user::interaction::message_handler(pusermessage);

   }


   void message_queue::message_queue_message_handler(::message::message * pmessage)
   {

      if(m_plistener != nullptr)
      {

         m_plistener->message_queue_message_handler(pmessage);

      }

   }


   bool message_queue::message_queue_is_initialized()
   {

      return is_window();

   }


   bool message_queue::message_queue_set_timer(uptr uId,::u32 dwMillis)
   {

      return SetTimer(uId,dwMillis,nullptr) != false;

   }

   bool message_queue::message_queue_del_timer(uptr uId)
   {

      return KillTimer(uId) != false;

   }

   bool message_queue::message_queue_post_message(const ::id & id,wparam wparam,lparam lparam)
   {

      return post_message(id, wparam, lparam);

   }


   lresult message_queue::message_queue_send_message(const ::id& id,wparam wparam,lparam lparam)
   {

      return send_message(id, wparam, lparam);

   }


   bool message_queue::message_queue_destroy()
   {

      return DestroyWindow() != false;

   }


   void * message_queue::message_queue_get_os_handle()
   {

      return get_os_data();

   }


} // namespace user



