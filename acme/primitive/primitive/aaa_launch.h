#pragma once


class CLASS_DECL_ACME ___launch :
   virtual public matter
{
public:


   __pointer(::matter)           m_pmatter;

   
   ___launch(::matter * pmatter);
   virtual ~___launch();

#ifdef WINDOWS

   static DWORD WINAPI s_os_thread_proc(void* p);

#else

   static void* s_os_thread_proc(void* p);

#endif

   //virtual ::estatus __thread_procedure() override;


   ::estatus fork(
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0,
      ITHREAD* pithread = nullptr,
      HTHREAD* phthread = nullptr);


};





