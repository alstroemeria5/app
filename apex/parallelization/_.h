#pragma once


#include "common.h"


#ifdef __APPLE__
#include <semaphore.h>
#endif





// LPVOID thread_data_get(thread_data_index dataindex);
// int_bool thread_data_set(thread_data_index dataindex, void* pvalue);


// thread_data_index thread_data_allocate();
// int_bool thread_data_free(thread_data_index dataindex);


//extern thread_local __pointer(property_set) t_ppropertyset;


CLASS_DECL_APEX void main_branch(::matter* pobjectTask, enum_priority epriority);


property_set& _thread_property_set();


property_set & thread_property_set();


#if defined(ANDROID)


//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX // as of 2016-11-26
// not implemented (err=38) on android-19 (POSIX semaphore)
#define MUTEX_NAMED_FD
#undef MUTEX_NAMED_VSEM

#elif defined(__APPLE__)

//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
#undef MUTEX_NAMED_VSEM

#elif defined(LINUX)

//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#undef MUTEX_NAMED_FD
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
//#define MUTEX_NAMED_VSEM // psystem V Semaphore
#undef MUTEX_NAMED_VSEM

#endif



class synchronization_object;
class semaphore;
//class ::mutex;
class event;
class critical_section;
class single_lock;
class multi_lock;


//CLASS_DECL_APEX ::e_status __call(::matter * pobject);



namespace parallelization
{


   namespace array
   {

      template < typename ARRAY >
      __pointer(::object) is_running(ARRAY & array, const char * pszTag)
      {

         for (::index i = 0; i < array.get_size(); i++)
         {

            __pointer(::object) pobject;

            pobject = &__typed(array[i]);

            if (pobject && pobject->is_thread())
            {

               if (pobject->task_get_run())
               {

                  if (pobject->get_tag().compare(pszTag) == 0)
                  {

                     return pobject;

                  }

               }

            }

         }

         return nullptr;

      }


   }


} // namespace parallelization



//CLASS_DECL_APEX bool task_set_name(const char * psz);
//CLASS_DECL_APEX bool task_set_name(htask_t htask, const char* pszName);

// Use instead of PostQuitMessage in OLE server applications
//CLASS_DECL_APEX void __post_quit_message(i32 nExitCode);

typedef ::e_status     (*__THREADPROC)(void *);


//CLASS_DECL_APEX bool do_events();
//CLASS_DECL_APEX bool do_events(const duration & duration);

class tool_task;
class task_tool;
class thread_tools;
//class thread_toolset;
//class predicate_set;
//class replace_thread;

namespace user
{


   class interaction;


} // namespace user

using user_interaction_ptr_array = address_array < ::user::interaction * >;

class thread_startup;


namespace parallelization
{


   //CLASS_DECL_APEX bool set_priority(enum_priority epriority);

   //CLASS_DECL_APEX i32 priority();


   //inline i32 get_priority_none()
   //{

   //   return e_priority_none;

   //}


   //inline i32 get_priority_normal()
   //{

   //   return e_priority_normal;

   //}


} // namespace parallelization


class sync_interface;
class synchronous_lock;


class CLASS_DECL_APEX thread_ptra :
   virtual public __pointer_array(thread)
{
public:


   thread_ptra();
   thread_ptra(const thread_ptra & ptra):__pointer_array(thread)(ptra) {}
   thread_ptra(thread_ptra && ptra) :__pointer_array(thread)(::move(ptra)) {}
   virtual ~thread_ptra();

   virtual ::count get_count_except_current_thread();
   //virtual ::e_status finish(::property_object * pcontextobjectFinish = nullptr) override;
   virtual ::e_status destroy() override;
   virtual void wait(const duration & duration, ::synchronous_lock & synchronouslock);

   thread_ptra & operator = (const thread_ptra & ptra) { __pointer_array(thread)::operator =(ptra); return *this; }
   thread_ptra & operator = (thread_ptra && ptra) { __pointer_array(thread)::operator =(::move(ptra)); return *this; }

};




//#include "predicate_holder.h"

//#include "synchronization_object.h"
//#include "synchronization_array.h"
//#include "semaphore.h"
//#include "::mutex.h"
//#include "event.h"
//#include "set_event_on_exit.h"
//#include "condition.h"
//#include "file_change_event.h"
//#include "socket_event.h"
//#include "critical_section.h"
//#include "single_lock.h"
//#include "retry_single_lock.h"
//#include "initial_single_lock.h"
//#include "synchronous_lock.h"
//#include "multi_lock.h"
//#include "retry_multi_lock.h"

//#include "synch_index_ptr_array.h"
//#include "synch_index_iterator.h"


#ifdef ___ENABLE_INLINES
#define _AFXMT_INLINE inline
#include "_impl.h"
#undef _AFXMT_INLINE
#endif


//#include "manual_reset_event.h"


//#include "sync_task.h"


//#ifdef WINDOWS
//#include <Winsvc.h>
//#endif

//#include "service_status.h"
#include "thread_os.h"


#include "create_thread.h"


//#include "service/pool.h"





//CLASS_DECL_APEX u32 random_processor_index_generator();


//CLASS_DECL_APEX int_bool post_message(::windowing::window * pwindow, const ::id & id, wparam wparam, lparam lparam);




// namespace parallelization
// {


//    CLASS_DECL_APEX void os_tls_init();

//    CLASS_DECL_APEX void os_tls_term();

//    CLASS_DECL_APEX void os_tls_set(void * p);

//    CLASS_DECL_APEX void * os_tls_get();


// } // namespace parallelization


//CLASS_DECL_APEX ::thread* get_task();
//CLASS_DECL_APEX ::thread * get_task(itask_t idthread);
//CLASS_DECL_APEX void set_thread(thread * pthread);




//#ifdef _UWP
//
//#include "apex/os/universal_windows/multithreading_winrt.h"
//
//#endif


string get_task_name(htask_t htask);


// Use instead of PostQuitMessage in OLE server applications
//CLASS_DECL_APEX void __post_quit_message(i32 nExitCode);


#if !defined(_UWP)



inline void main_async(const ::routine & routine, enum_priority epriority = e_priority_normal)
{

   main_branch(routine, epriority);

}


#endif





