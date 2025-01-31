#include "framework.h"
#include "aura/user/_user.h"
#include "aura/message.h"
#include "interaction_thread.h"
#include "interaction_prodevian.h"


#ifdef WINDOWS_DESKTOP


int windows_desktop1_main(HINSTANCE hInstance, int       nCmdShow);


void verisimple_message_loop()
{

   MSG msg;

   while (::GetMessage(&msg, nullptr, 0, 0))
   {

      //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      {

         TranslateMessage(&msg);

         DispatchMessage(&msg);

      }

   }

}


#endif


namespace user
{


   thread::thread()
   {

      m_bMessageThread = true;

//#ifdef WINDOWS_DESKTOP
//
//      m_bCreateNativeWindowOnInteractionThread = true;
//
//#else
//
//      m_bCreateNativeWindowOnInteractionThread = false;
//
//#endif


   }

   thread::~thread()
   {

   }


   ::e_status thread::initialize_user_thread(interaction_impl * pimpl)
   {

      auto estatus = initialize(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      m_pimpl = pimpl;

      string strType = ::str::demangle(m_pimpl->m_puserinteraction->type_name());

      m_strDebugType = strType;

      m_bSimpleMessageLoop = false;

      return estatus;

   }


#ifdef _DEBUG


   i64 thread::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::thread::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 thread::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::thread::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 thread::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::thread::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

   HRESULT thread::initialize_tsf_thread()
   {

      HRESULT hr = S_OK;

      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr.CoCreateInstance(CLSID_TF_ThreadMgr, nullptr, CLSCTX_INPROC_SERVER);

      }

      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr.As(m_pthreadmgrex);

      }

      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgrex->ActivateEx(&m_tfClientID, TF_TMAE_UIELEMENTENABLEDONLY);

      }


      // get the keystroke manager interfce
      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr->QueryInterface(IID_ITfKeystrokeMgr, (void **)& m_pkeystrokemgr);

      }

      // get the message pump wrapper interface
      if (SUCCEEDED(hr))
      {

         hr = m_pthreadmgr->QueryInterface(IID_ITfMessagePump, (void **)& m_pmessagepump);

      }


      return hr;

   }

#endif

   ::e_status thread::task_caller_on_init()
   {

      //if (!m_bCreateNativeWindowOnInteractionThread)
      //{

      //   if (!m_pimpl->_native_create_window_ex(*m_pusersystem))
      //   {

      //      //delete m_pusersystem;

      //      m_pusersystem = nullptr;

      //      m_estatus = error_failed;

      //      finish();

      //      return ::error_failed;

      //   }

      //}


      return ::success;

   }


   ::e_status thread::init_thread()
   {

      auto estatus = ::thread::init_thread();

      if (!estatus)
      {

         return estatus;

      }

#ifdef WINDOWS_DESKTOP

      HRESULT hr = CoInitialize(NULL);

#endif

      //set_topic_text("window_thread_" + ::str::demangle(m_pimpl->m_puserinteraction->type_name()) + "> ");

      ::task_set_name(::str::demangle(m_pimpl->m_puserinteraction->type_name()));

#ifdef WINDOWS_DESKTOP

      //attach_thread_input_to_main_thread();

#endif

      if (!m_pimpl->m_puserinteraction->is_system_message_window())
      {

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

         initialize_tsf_thread();

#endif

      }

      //__compose(m_pimpl->m_puserinteraction, m_pimpl->m_puserinteraction->m_pthreadUserInteraction);

      __keep_flag_on(m_pimpl->m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_creating);

      //fork([this]()
      //   {

      //      task_set_name("test");

            //windows_desktop1_main(psystem->m_hinstance, SW_SHOWNORMAL);

      //  });

      //if (m_bCreateNativeWindowOnInteractionThread)
      //{

      __pointer(::aura::session) psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      m_pwindowing = pwindowing;

      estatus = m_pimpl->native_create_host();

      if(!estatus)
      {

         m_pimpl->m_puserinteraction->m_pusersystem->m_routineFailure();

         if (is_debugger_attached())
         {

            output_error_message("Window not created", "Window not created", e_message_box_icon_warning);

         }

         //delete m_pusersystem;

         //m_pusersystem = nullptr;

         m_estatus = error_failed;

         destroy();

         return estatus;

      }

      auto pusersystem = m_pimpl->m_puserinteraction->m_pusersystem;

      if(pusersystem && pusersystem->m_routineSuccess)
      {

         pusersystem->m_routineSuccess();

      }


      //}
      //else
      //{ 
      //
      //   __refer(m_pimpl->m_puserinteraction->m_pthreadUserInteraction, this);

      //   uiptra().add(m_pimpl->m_puserinteraction);

      //}

      //m_himc = ImmGetContext(m_pimpl->get_handle());

      m_oswindow = m_pimpl->m_pwindow->get_oswindow();

      //delete m_pusersystem;

      //m_pusersystem = nullptr;

      return true;

   }




   bool thread::pump_runnable()
   {

      //{

      //   synchronous_lock synchronouslock(mutex());

      //   if (m_messagebasea.has_elements())
      //   {

      //      auto pusermessage = m_messagebasea.first_pointer();

      //      m_messagebasea.erase_at(0);

      //      synchronouslock.unlock();

      //      m_pimpl->m_puserinteraction->message_handler(pusermessage);

      //      return true;

      //   }

      //}

      return ::thread::pump_runnable();

   }


   bool thread::pump_message()
   {

      try
      {

         if (pump_runnable())
         {

            return true;

         }

      }
      catch (...)
      {

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

      }

      try
      {

         auto estatus = get_message(&m_message, nullptr, 0, 0);

         if(estatus == status_quit)
         {

            if (m_strDebugType.contains("filemanager"))
            {

               //INFO("filemanager");

            }

            TRACE(trace_category_appmsg, e_trace_level_information, string(type_name()) + " thread::pump_message - Received e_message_quit.\n");

            ::output_debug_string(string(type_name()) + " thread::pump_message - Received e_message_quit.\n");

            m_nDisablePumpCount++; // application must die
            // Note: prevents calling message loop things in 'exit_thread'
            // will never be decremented
            return false;

         }

         if(m_message.m_id == e_message_left_button_down)
         {

            output_debug_string("test");

         }

         if (m_message.m_id == e_message_quit)
         {

            if (m_pimpl 
               && m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_is_window
               && ::thread::is_finishing())
            {

               m_pimpl->m_puserinteraction->start_destroying_window();

            }

         }

         if(m_message.m_id == e_message_left_button_down)
         {

            ::output_debug_string("::user::thread::LBUTTONDOWN\n");

         }
         else if(m_message.m_id == e_message_left_button_up)
         {

            ::output_debug_string("::user::thread::LBUTTONUP\n");

         }

         if (m_message.m_id != WM_KICKIDLE && m_message.m_id != e_message_quit)
         {

            if (m_message.m_id == e_message_destroy_window)
            {

               if (m_strDebugType.contains("notify_icon"))
               {

                  INFO("notify_icon");

               }
               else if (m_strDebugType.contains("main_frame"))
               {

                  INFO("main_frame");

               }

            }

            if (estatus != status_kick_idle)
            {

               process_message();

            }

         }

         return true;

      }
      catch (const ::exception::exception & e)
      {

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

         if (handle_exception(e))
         {

            return true;

         }

         //// get_application() may be it self, it is ok...
         //if (papplication->final_handle_exception(e))
         //{

         //   return true;

         //}

      }
      catch (...)
      {

         INFO("... exception");

      }

      return false;

   }


   ::e_status thread::process_message()
   {

      try
      {

         MESSAGE & msg = m_message;

         if(msg.m_id == e_message_mouse_move)
         {


         }
         else if(msg.m_id == e_message_left_button_down)
         {

            ::output_debug_string("e_message_left_button_down");

         }
         else if(msg.m_id == e_message_left_button_up)
         {

            ::output_debug_string("e_message_left_button_up");

         }

         auto oswindow = msg.oswindow;

         if(oswindow)
         {

            auto pwindow = m_pwindowing->window(oswindow);

            if (pwindow)
            {

               auto pimpl = pwindow->m_pimpl;

               if (pimpl)
               {

                  auto puserinteraction = pimpl->m_puserinteraction;

                  if (puserinteraction)
                  {

                     if (msg.m_id == ::e_message_redraw)
                     {

                        string strType = ::str::demangle(puserinteraction->type_name());

                        if (strType.contains_ci("filemanager"))
                        {

                           //INFO("filemanager");

                        }

                        puserinteraction->prodevian_redraw(msg.wParam & 1);

                        return true;

                     }

#if !defined(WINDOWS_DESKTOP)

                     else
                     {

                        if(msg.m_id == e_message_left_button_down)
                        {

                           ::output_debug_string("e_message_left_button_down");

                        }
                        else if(msg.m_id == e_message_left_button_up)
                        {

                           ::output_debug_string("e_message_left_button_up");

                        }

                        auto pmessage = puserinteraction->get_message(msg.m_id, msg.wParam, msg.lParam);

                        if (pmessage)
                        {

                           if(pmessage->m_id == e_message_left_button_down)
                           {

                              ::output_debug_string("e_message_left_button_down");

                           }

                           pwindow->message_handler(pmessage);

                           return ::success;

                        }

                     }

#endif

                  }

               }

            }

         }

      }
      catch(...)
      {

      }

      return ::thread::process_message();

   //      MESSAGE & msg = m_message;
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //      if (msg.hwnd != nullptr)
   //      {
   //
   //         ::TranslateMessage(&msg);
   //
   //         ::DispatchMessage(&msg);
   //
   //         return true;
   //
   //      }
   //      else
   //      {
   //
   //         ::TranslateMessage(&msg);
   //
   //         lresult lresult = ::DispatchMessageW(&msg);
   //
   //         return true;
   //
   //      }
   //
   //#endif
   //
   //      return true;

   }



   ::e_status thread::process_message(::message::message * pmessage)
   {

      if(pmessage->m_oswindow)
      {

         return process_user_message(pmessage);

      }
      else
      {

         return process_thread_message(pmessage);

      }

   }


   ::e_status thread::process_user_message(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      if(::is_set(pusermessage))
      {

         auto puserinteraction = pusermessage->userinteraction();

         if (::is_set(puserinteraction))
         {

            ::i64 iMessage = pmessage->m_id;

            //__throw(todo("interaction"));
            //__throw(todo("thread"));

            //short circuit for frequent messages
            if (iMessage == e_message_apply_visual)
            {

               //__throw(todo("interaction"));
               //__throw(todo("thread"));

               if (puserinteraction->m_pimpl2)
               {

                  puserinteraction->m_pimpl2->_001OnApplyVisual(pusermessage);

                  return true;

               }

            }
            else if (iMessage == e_message_update_notify_icon)
            {

               puserinteraction->route_message(pusermessage);

               return true;

            }
            else if (iMessage == e_message_simple_command)
            {

               puserinteraction->m_pimpl2->_001OnApplyVisual(pusermessage);

               return true;

            }

            //if (iMessage > e_message_midi_sequence_event)
            //{

            //   return true;

            //   ::i64 iApp = iMessage - WM_APP;

            //   pusermessage->m_puserinteraction->message_handler(pusermessage);

            //}
            //else
            //{

            //      //return true;
            //   //__throw(todo("interaction"));
            //   //__throw(todo("thread"));

            puserinteraction->message_handler(pusermessage);

            return true;

         }

      }

      return ::thread::process_message(pmessage);

   }


   ::e_status thread::destroy_composites()
   {

      auto estatus = ::channel::destroy_composites();

      return estatus;

   }


   void thread::enumerate_composite(matter_array& a)
   {


   }


   //::e_status thread::set_finish_composites(::property_object * pcontextobjectFinish)
   //{

   //   auto estatus = channel::set_finish_composites(pcontextobjectFinish);

   //   if (estatus == error_pending)
   //   {

   //      return estatus;

   //   }

   //   if (m_pimpl)
   //   {

   //      auto puserinteraction = m_pimpl->m_puserinteraction;

   //      if (puserinteraction)
   //      {

   //         if (!m_pimpl->m_bDestroying)
   //         {

   //            puserinteraction->DestroyWindow();

   //         }

   //      }

   //      return error_pending;

   //   }

   //   if (task_active())
   //   {

   //      set_finish_bit();

   //      post_quit();

   //      return error_pending;

   //   }

   //   return ::success;

   //}


   ::e_status thread::run()
   {

      ASSERT_VALID(this);

      INFO("user::thread::run");

      if (m_strDebugType.contains("main_frame"))
      {

         output_debug_string("xxthread::run from main_frame");

      }

      // get the keystroke manager interfce
      //if (SUCCEEDED(m_pthreadmgr->QueryInterface(IID_ITfKeystrokeMgr, (void**)& m_pKeyMgr)))
      //{
      //   // get the message pump wrapper interface
      //   if (SUCCEEDED(m_pthreadmgr->QueryInterface(IID_ITfMessagePump, (void**)& m_pMsgPump)))
      //   {

      //   }
      //}
      int_bool    fResult = true;

      //while (fResult)
      //{
      //   MSG     msg;
      //   BOOL    fEaten;

         /*
         Get the next message in the queue. fResult receives false if e_message_quit is encountered
         */
         //            }

               //}

                     //if (FAILED(pMsgPump->GetMessage(&msg, NULL, 0, 0, &fResult)))
                     //{
                     //   fResult = false;
                     //}
                     //else if (e_message_key_down == msg.message)
                     //{
                     //   // does an ime want it?
                     //   if (pKeyMgr->TestKeyDown(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten &&
                     //      pKeyMgr->KeyDown(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten)
                     //   {
                     //      continue;
                     //   }
                     //}
                     //else if (e_message_key_up == msg.message)
                     //{
                     //   // does an ime want it?
                     //   if (pKeyMgr->TestKeyUp(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten &&
                     //      pKeyMgr->KeyUp(msg.wParam, msg.lParam, &fEaten) == S_OK && fEaten)
                     //   {
                     //      continue;
                     //   }
                     //}

                     //if (fResult)
                     //{
                     //   TranslateMessage(&msg);
                     //   DispatchMessage(&msg);
                     //}

                     //if (e_message_quit == msg.message)
                     //{
                     //   nReturn = (int)msg.wParam;
                     //}

      if (m_bMessageThread)
      {

         bool bWindowSetFinish = false;

         while (task_get_run())
         {

            if (m_pimpl)
            {

               m_pimpl->process_message();

            }

            if (!pump_message())
            {

               if (m_strDebugType.contains("filemanager"))
               {

                  //INFO("filemanager");

               }

               if (m_strDebugType.contains("main_frame"))
               {

                  output_debug_string("!xxm_bSimpleMessageLoop !xxpump_message xxthread::run from main_frame");

               }

               break;

            }

//            if (m_bSetFinish)
//            {
//
//               if (!bWindowSetFinish)
//               {
//
//                  bWindowSetFinish = true;
//
//                  if (m_pimpl)
//                  {
//
//                     auto puserinteraction = m_pimpl->m_puserinteraction;
//
//                     if (puserinteraction)
//                     {
//
//                        puserinteraction->destroy_window();
//
//                     }
//
//                  }
//
//               }
//
//            }

         }

      }

      //m_pMsgPump->Release();

      //   m_pKeyMgr->Release();

      if (m_strDebugType.contains("main_frame"))
      {

         output_debug_string("ending xxthread::run from main_frame");

      }

      if (m_strDebugType.contains("filemanager"))
      {

         //INFO("filemanager");

      }

      return m_estatus;

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   int thread::_GetMessage(MESSAGE * lpMsg, HWND hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax)
//   {
//
//#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
//
//      while (m_pmessagepump && m_pkeystrokemgr)
//      {
//
//         BOOL fResult = true;
//
//         if (FAILED(m_pmessagepump->GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, &fResult)))
//         {
//
//            return false;
//
//         }
//         else
//         {
//
//            BOOL    fEaten;
//
//            if (e_message_key_down == lpMsg->message)
//            {
//               // does an ime want it?
//               if (m_pkeystrokemgr->TestKeyDown(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten &&
//                  m_pkeystrokemgr->KeyDown(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten)
//               {
//                  continue;
//               }
//            }
//            else if (e_message_key_up == lpMsg->message)
//            {
//               // does an ime want it?
//               if (m_pkeystrokemgr->TestKeyUp(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten &&
//                  m_pkeystrokemgr->KeyUp(lpMsg->wParam, lpMsg->lParam, &fEaten) == S_OK && fEaten)
//               {
//                  continue;
//               }
//            }
//
//         }
//
//         return true;
//
//      }
//
//#endif
//
//      int iRet = ::thread::_GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
//
//      if (iRet <= 0)
//      {
//
//         return iRet;
//
//      }
//
//      return iRet;
//
//      //if (ImmIsUIMessageW(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam))
//      //{
//
//      //   return iRet;
//
//      //}
//
//      //return iRet;
//
//   }
//
//
//#endif


   bool thread::task_get_run() const
   {

//      if (m_pimpl)
//      {
//
//         return true;
//
//      }

      return ::thread::task_get_run();

   }


   void thread::start_window_visual()
   {

      m_evApplyVisual.ResetEvent();

      m_pimpl->m_puserinteraction->post_message(e_message_apply_visual);

   }


   //::e_status thread::destroy()
   //{

   //   return ::thread::destroy();

   //}


   ::e_status thread::destroy()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pimpl)
      {

         if (m_pimpl->m_bDestroyImplOnly)
         {

            m_pimpl->destroy_impl_only();

         }
         else if (m_pimpl->m_puserinteraction)
         {

            m_pimpl->m_puserinteraction->start_destroying_window();

         }

      }
      else
      {

         //string strType = m_puserinteraction->type_name();

         if (m_strDebugType.contains("filemanager"))
         {

            //INFO("filemanager");

         }

         ::thread::destroy();

      }

      return ::success;

   }


   ::e_status thread::set_finish()
   {

      return ::thread::set_finish();

   }


   void thread::term_thread()
   {

      if (m_pimpl && m_pimpl->m_puserinteraction && m_pimpl->m_puserinteraction->m_strName.contains("notify_icon"))
      {
         INFO("notify_icon");
      }

      synchronous_lock synchronouslock(mutex());

      m_pimpl.release();

      //if (m_pthreadmgr)
      //{
      //   m_pthreadmgr->Deactivate();

      //   m_pthreadmgr->Release();
      //   m_pthreadmgr = NULL;
      //}

      ::thread::term_thread();

   }


} // namespace user




