#pragma once




class CLASS_DECL_ACME semaphore :
   virtual public synchronization_object
{
public:

   string            m_strName;

#if defined(ANDROID)

   ::i32              m_lMaxCount;
   sem_t *           m_psem;

#elif defined(LINUX) || defined(__APPLE__)

   ::i32         m_lMaxCount;
   i32           m_hsync;

#endif

   semaphore(::i32 lInitialCount = 1, ::i32 lMaxCount = 1, const char * pstrName=nullptr ARG_SEC_ATTRS_DEF);
   ~semaphore() override;


#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
//   using matter::lock;
   ::e_status wait(const duration & durationTimeout) override;
#endif

   bool unlock() override;
   bool unlock(::i32 lCount, ::i32 * prevCount = nullptr) override;


};


