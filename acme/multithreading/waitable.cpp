/**
* \brief	Session independent waitables
* \author	Thomas Hoefer
*/

#include "framework.h"


//matter::matter()
//{
//
//   mutex() = nullptr;
//
//}
//
//matter::matter(const matter & objectSrc)
//{
//
//   UNREFERENCED_PARAMETER(objectSrc);
//
//   mutex() = nullptr;
//
//}
//
//
/////  \brief		destructor
//matter::~matter()
//{
//
//   if(mutex() != nullptr)
//   {
//
//      delete mutex();
//
//      mutex() = nullptr;
//
//   }
//
//}
//
/////  \brief		abstract function to initialize a waiting action without a timeout
//void matter::wait()
//{
//
//   wait(duration::infinite());
//
//}
//
//	///  \brief		abstract function to initialize a waiting action with a timeout
//	///  \lparam		duration time period to wait for item
//	///  \return	waiting action result as sync_result
//sync_result matter::wait(const duration & duration )
//{
//
//
//   if(mutex() == nullptr)
//   {
//
//      ((matter *)this)->mutex() = new ::mutex();
//
//   }
//
//   try
//   {
//      return mutex()->wait(duration);
//   }
//   catch(...)
//   {
//   }
//
//   return sync_result(sync_result::Failure);
//
//}
//
//
//
//
//// forward declaration
////class event_base;
//
///// This class represents a virtual interface for a callback method for WaitableItems in a
///// event_collection.
//
//waitable_callback::~waitable_callback()
//{
//}
//
//	/// called on signalization of a event_base
//	/// \lparam signaling event_base
////	virtual void callback(const event_base& waitItem) = 0;
////};
//
//
/////  \brief		pauses matter for specified time
/////  \lparam		duration sleeping time of matter
///*CLASS_DECL_ACME void sleep(const duration & duration)
//{
//   Sleep((u32)duration.total_milliseconds());
//}*/
//
//CLASS_DECL_ACME void sleep(const duration & duration)
//{
//   ::Sleep(static_cast<u32>(duration.total_milliseconds()));
//}
//
//
//
//
//
//void * matter::get_os_data() const
//{
//
//   if(mutex() == nullptr)
//   {
//
//      ((matter *)this)->mutex() = new ::mutex();
//
//   }
//
//   return mutex();
//
//}
//
//void matter::lock()
//{
//
//   if(!lock(duration::infinite()))
//      if(!lock(duration::infinite()))
//         __throw(::exception::exception("failure to lock matter"));
//
//}
//
//bool matter::lock(const duration & duration)
//{
//
//   if(mutex() == nullptr)
//   {
//
//      ((matter *)this)->mutex() = new ::mutex();
//
//   }
//
//   bool bLocked = false;
//
//   try
//   {
//
//      bLocked = mutex()->lock(duration);
//
//   }
//   catch(...)
//   {
//
//      bLocked = false;
//
//   }
//
//   if(!bLocked)
//      return false;
//
//   return true;
//
//}
//
//
//bool matter::unlock()
//{
//
//   if(mutex() == nullptr)
//      return false;
//
//   bool bUnlocked = false;
//
//   try
//   {
//
//      bUnlocked = mutex()->unlock();
//
//   }
//   catch(...)
//   {
//
//      bUnlocked = false;
//
//   }
//
//   if(!bUnlocked)
//      return false;
//
//   return true;
//
//}
//
//bool matter::unlock(LONG lCount, LPLONG pPrevCount)

//{
//   UNREFERENCED_PARAMETER(lCount);
//   UNREFERENCED_PARAMETER(pPrevCount);

//   return true;
//}
//
//
//bool matter::is_locked() const
//{
//
//   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
//   ASSERT(dynamic_cast < critical_section * > ( const_cast < matter * > (this)) == nullptr);
//
//   single_lock sl(const_cast < matter * > (this));
//
//   bool bWasLocked = !sl.lock(duration::zero());
//
//   if(!bWasLocked)
//      sl.unlock();
//
//   return bWasLocked;
//
//}
//
