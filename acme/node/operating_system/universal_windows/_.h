#pragma once


#include "base_file.h"
#include "parallelization.h"


//#ifdef __cplusplus
//#include "platform-windows_common/windows_commoncomptr.h"
//#endif


//#ifndef _UWP
//
//CLASS_DECL_ACME void WINAPI sleep(::u32 dwMilliseconds);
//
//#endif

/*#define GetAValue(rgb)      (__LOBYTE((rgb)>>24))
#define argb(a, r,g,b)          ((color32_t)(((byte)(r)|((::u16)((byte)(g))<<8))|(((::u32)(byte)(b))<<16)|(((::u32)(byte)(a))<<24)))*/


//CLASS_DECL_ACME int_bool os_initialize();
//CLASS_DECL_ACME int_bool os_finalize();


CLASS_DECL_ACME int_bool main_initialize();
CLASS_DECL_ACME int_bool main_finalize();


CLASS_DECL_ACME void set_main_hthread(htask_t htask);
CLASS_DECL_ACME void set_main_ithread(itask_t itask);


CLASS_DECL_ACME htask_t get_main_hthread();
CLASS_DECL_ACME itask_t get_main_ithread();

//CLASS_DECL_ACME oswindow get_focus();
//CLASS_DECL_ACME oswindow set_focus(oswindow oswindow);

//CLASS_DECL_ACME oswindow get_window(oswindow oswindow, int iWindow);

//CLASS_DECL_ACME void attach_thread_input_to_main_thread(int_bool bAttach);


//CLASS_DECL_ACME ::u32 WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ ::u32 dwMilliseconds );




//CLASS_DECL_ACME char* getenv(const char* name);
//CLASS_DECL_ACME HANDLE WINAPI CreateMutex(_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes, _In_ BOOL bInitialOwner, _In_opt_ const char * lpName  );

//CLASS_DECL_ACME HANDLE WINAPI CreateMutexW(    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,    _In_ BOOL bInitialOwner,    _In_opt_ const widechar * lpName    );



//inline int_bool is_nok(hfile hfile);

//
//inline int_bool is_ok(hfile hfile);
//
//
//CLASS_DECL_ACME void dpi_os_initialize();
//



