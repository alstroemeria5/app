﻿#pragma once


#ifdef WINDOWS_DESKTOP


namespace user
{


   class CLASS_DECL_AURA message_window :
      virtual public message_window_listener,
      virtual public ::user::interaction
   {
   public:


      __pointer(message_window_listener)      m_plistener;


      message_window();
      virtual ~message_window();


      virtual bool create_message_window(const ::string & pszName,::user::message_window_listener * plistener = nullptr);

      virtual void message_handler(::user::message * pusermessage);

      virtual void message_window_message_handler(::message::message * pmessage);

      virtual bool message_window_is_initialized();

      virtual bool message_window_set_timer(uptr uId,::u32 dwMillis);

      virtual bool message_window_post_message(const ::id & id, wparam wparam = 0,lparam lparam = 0);

      virtual lresult message_window_send_message(const ::id & id, wparam wparam = 0,lparam lparam = 0);

      virtual bool message_window_del_timer(uptr uId);

      virtual bool message_window_destroy();

      virtual void * message_window_get_os_handle();

   };


   typedef __pointer(message_window) message_window_pointer;


} // namespace aura


#endif




