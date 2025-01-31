#pragma once


#if defined(LINUX) || defined(__APPLE__)
#include <sys/types.h>
#include <sys/sem.h>
#endif



class CLASS_DECL_ACME event :
   public synchronization_object
{
public:


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   /// Private Mutexes
   bool              m_bManualEvent;
   bool              m_bSignaled;  // meaningful only when m_bManualEvent
   i32               m_iSignalId;  // meaningful only when m_bManualEvent
   void *            m_pcond; // pthread_cond_t
   void *            m_mutex; // pthread_mutex_t;


#endif


#if defined(LINUX) || defined(__APPLE__)

   /// Named Mutexes
   int               m_sem;

#endif


   event(char * sz = nullptr,bool bInitiallyOwn = false, bool bManualReset = false, const char * pszNAme = nullptr ARG_SEC_ATTRS_DEF);

   ~event() override;

   // using event_base::lock;
   bool lock(const duration & durationTimeout = duration::infinite()) override;

   using synchronization_object::unlock;
   bool unlock() override;

   //virtual HSYNC hsync() const;

   bool SetEvent();
   bool set_event() {return SetEvent(); }
   //bool PulseEvent();
   bool ResetEvent();

   /**
   * \brief	Session independent waitables (windows version)
   */

   ///  \brief		waits for an event forever
   ::e_status _wait () override;

   ///  \brief		waits for an event for a specified time
   ///  \lparam		duration time period to wait for an event
   ///  \return	waiting action result as WaitResult
   virtual ::e_status _wait (const duration & duration) override;

   bool is_signaled() const;

};

