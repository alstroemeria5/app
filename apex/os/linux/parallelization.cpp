#include "framework.h"
#include "_linux.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/os/ansios/_pthread.h"


#endif


namespace process
{


   CLASS_DECL_APEX bool set_priority(::e_priority epriority)
   {

      i32 iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, epriority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

   }




} // namespace apex




























void __node_init_thread()
{

}

void __node_term_thread()
{

}














bool __os_init_thread()
{

   //__thread_set_data((ithread_t) idthread, ::parallelization::slot_message_queue, 0);

   return true;

}



bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}







//#if OSBIT != 64
//
//::thread_object < _TEB > t_pteb;
//
//struct _TEB * WINAPI NtCurrentTeb(void)
//{
//
//   return t_pteb;
//
//}
//
//#endif




CLASS_DECL_APEX void main_sync_runnable(::context_object * pobjectRunnable, ::duration durationTimeout)
{

   __pointer(context_object) prunnable = pobjectRunnable;

   auto pevent = __new(manual_reset_event);

   auto pnode = Node;

   pnode->node_fork([prunnable, pevent]()
   {

      try
      {

         prunnable->operator()();

      }
      catch(...)
      {

      }

      pevent->SetEvent();

   });

   pevent->wait(durationTimeout);

}


CLASS_DECL_APEX void main_async_runnable(::context_object * prunnableParam)
{

   __pointer(context_object) prunnable = prunnableParam;

   auto pnode = Node;

   pnode->node_fork([prunnable]()
   {

      prunnable->operator()();

   });

}







