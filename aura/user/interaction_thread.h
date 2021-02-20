#pragma once


#include "aura/operating_system.h"


#ifdef WINDOWS_DESKTOP

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#include <msctf.h>
#include "aura/os/windows_common/comptr.h"
#include "windows_tsf/edit_window.h"
#endif
#endif


namespace user
{


   // the thread
   // must be child of an application thread.
   // The window must not be parent of the window thread.
   // The window thread isn't a child worker thread of the window.
   // The window thread is some sort of parent of the window it works upon.
   class CLASS_DECL_AURA thread :
      virtual public ::thread
   {

   public:

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

#ifdef WINDOWS

      comptr < ITfThreadMgr >                      m_pthreadmgr;
      comptr < ITfThreadMgrEx >                    m_pthreadmgrex;
      TfClientId                                   m_tfClientID;
      comptr < ITfKeystrokeMgr >                   m_pkeystrokemgr;
      comptr < ITfMessagePump >                    m_pmessagepump;
      array < comptr < tsf::edit_window > >        m_editwindowa;

#endif

#endif

      __pointer(interaction_impl)            m_pimpl;
      __reference(prodevian)                 m_pprodevian;
      oswindow                               m_oswindow;

      manual_reset_event                     m_evApplyVisual;
      __pointer_array(::message::message)    m_messagebasea;


      //bool                                 m_bCreateNativeWindowOnInteractionThread;

      thread();
      virtual ~thread();


#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 release(OBJ_REF_DBG_PARAMS) override;
#endif


      virtual ::e_status     initialize_user_thread(interaction_impl * pimpl);


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

#ifdef WINDOWS

      virtual HRESULT initialize_tsf_thread();

#endif
#endif
      virtual ::e_status init_thread() override;
      virtual void term_thread() override;

//#ifdef WINDOWS_DESKTOP
//      virtual int _GetMessage(LPMSG lpMsg, HWND hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax) override;
//#endif

      virtual bool pump_message() override;

      virtual bool pump_runnable() override;

      virtual ::e_status process_message() override;

      virtual ::e_status process_message(::message::message * pmessage) override;

      virtual ::e_status process_user_message(::message::message * pmessage);

      virtual ::e_status run() override;

      virtual ::e_status finish(::context_object * pcontextobjectFinish = nullptr) override;

      virtual void finalize() override;

      virtual bool thread_get_run() const override;

      virtual ::e_status set_finish_composites(::context_object * pcontextobjectFinish) override;

      void start_window_visual();

      virtual ::e_status task_caller_on_init() override;


   };


} // namespace user



