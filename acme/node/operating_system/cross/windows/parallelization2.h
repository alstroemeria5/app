#pragma once


#if !defined(WINDOWS_DESKTOP)


void set_defer_process_x_message(bool (* pfn)(htask_t htask, MESSAGE * pmessage,oswindow oswindow,bool bPeek));


//#ifdef __cplusplus

//#undef synchronization_object
//class synchronization_object;
//
//#ifdef WINDOWS
//using HSYNC = HANDLE;
//#else
//using HSYNC = synchronization_object *;
//#endif

#ifdef _UWP

#pragma warning (disable:4273)

CLASS_DECL_ACME DWORD WINAPI MsgWaitForMultipleObjects(DWORD nCount, const HANDLE * pHandles, BOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask);

CLASS_DECL_ACME DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD nCount, const HANDLE* pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags);

#else

::e_status WaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, int_bool bAlertable);

::e_status WaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout);

::e_status MsgWaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, ::u32 dwWakeMask);

::e_status MsgWaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, ::u32 tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags);

::e_status WaitForSingleObject(HSYNC hsync, ::u32 dwMilliseconds);

::e_status WaitForSingleObjectEx(HSYNC hsync, ::u32 dwMilliseconds, int_bool bAlertable);


//#define STATUS_WAIT_0            ((::u32   ) 0x00000000L)
//#define STATUS_ABANDONED_WAIT_0  ((::u32   ) 0x00000080L)
//#define STATUS_USER_APC          ((::u32   ) 0x000000C0L)
//#define STATUS_TIMEOUT           ((::u32   ) 0x00000102L)
//
//
//#define WAIT_FAILED             ((::u32   ) 0xFFFFFFFFL)
//#define WAIT_OBJECT_0           ((::u32   ) STATUS_WAIT_0 + 0)
//
//
//#define WAIT_ABANDONED          ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)
//#define WAIT_ABANDONED_0        ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)


#endif


#define WAIT_IO_COMPLETION      STATUS_USER_APC


// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


//
//#if !defined(__APPLE__) && !defined(ANDROID)
//
//union semun
//{
//   int val; /* Value for SETVAL */
//   struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
//   unsigned short *array; /* Array for GETALL, SETALL */
//   struct seminfo *__buf; /* Buffer for IPC_INFO
//                                (Linux-specific) */
//};
//
//#endif


#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002
#define MWMO_INPUTAVAILABLE 0x0004


// class thread;
// class message_queue;


// CLASS_DECL_ACME int_bool WINAPI GetMessage(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

// CLASS_DECL_ACME int_bool WINAPI PeekMessage(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);

// CLASS_DECL_ACME int_bool WINAPI PostThreadMessage(itask_t idthread, ::u32 Msg, WPARAM wParam, LPARAM lParam);

// CLASS_DECL_ACME void mq_clear(itask_t htask);


// #ifndef _UWP

// CLASS_DECL_ACME ::u32 WINAPI GetThreadId(htask_t Thread);

// CLASS_DECL_ACME htask_t GetCurrentThread();

// CLASS_DECL_ACME itask_t GetCurrentThreadId();

// #endif


#endif




