#include "framework.h"


#ifdef WINDOWS_DESKTOP

///  \brief		constructor with passed path to file
///  \lparam		path the file to watch
///  \lparam		watchsubtree if true, the function monitors the directory tree
///				rooted at the specified directory, if it is false,
///				it monitors only the specified directory
///  \lparam		filter filter conditions that satisfy a change notification wait
///				can take values described by enum filter
file_change_event::file_change_event(::matter * pobject, const char * path, bool watchsubtree, u32 filter) :
   sync(::FindFirstChangeNotificationW(::str::international::utf8_to_unicode(path), watchsubtree, filter))
{
   if (hsync() == nullptr)
      __throw(runtime_error("file_change_event: failed to create event"));
}

///  \brief		destructor
file_change_event::~file_change_event()
{
}


bool file_change_event::lock(const duration & durationTimeout)
{
   u32 dwRet = ::WaitForSingleObject(hsync(), durationTimeout.lock_duration());
   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return true;
   else
      return false;
}

bool file_change_event::unlock()
{
   next();
   return true;
}

///  \brief		waits for an file notification forever
sync_result file_change_event::wait ()
{

   if (::WaitForSingleObject(hsync(), U32_INFINITE_TIMEOUT) != WAIT_OBJECT_0)
   {

      return sync_result(sync_result::result_error);

   }

   return sync_result(sync_result::result_event0);

}


///  \brief		waits for an file notification for a specified time
///  \lparam		duration time period to wait for an file notification
///  \return	waiting action result as sync_result
sync_result file_change_event::wait (const duration & duration)
{

   return sync_result((u32) ::WaitForSingleObject(hsync(),duration.lock_duration()));

}


///  \brief		requests that the operating system signal a change
///				notification handle the next time it detects an appropriate
///				change
bool file_change_event::next ()
{
   return ::FindNextChangeNotification(hsync()) != FALSE;

}

///  \brief		stops change notification handle monitoring
void file_change_event::close ()
{
   ::FindCloseChangeNotification(hsync());
}




#endif


