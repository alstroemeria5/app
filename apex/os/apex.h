#pragma once

//
//CLASS_DECL_APEX void defer_dock_application(int_bool bDock);
//
//
//CLASS_DECL_APEX WINBOOL IsProcessRunning(DWORD pid);
//


#include "file.h"


#include "thread.h"

#include "cross.h"



/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/


#ifdef cplusplus

inline bool IsDirSep(WCHAR ch);



#endif


#include "time.h"


#if defined(MACOS)

#elif defined(APPLE_IOS)

#elif defined(LINUX)

#elif defined(_UWP)

#define BSD_STYLE_SOCKETS

#elif defined(WINDOWS_DESKTOP)

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(ANDROID)

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(SOLARIS)

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(APPLE_IOS)

#else

#error Not supported operating system

#endif





//CLASS_DECL_APEX void set_command_line_dup(const char * psz);
//
//CLASS_DECL_APEX void get_command_line_dup(char * psz, int iBuffer);





#ifdef __cplusplus

#include "windowing.h"

#endif


#include "graphics.h"


#pragma once


#include "apex/os/binreloc.h"




#ifdef AMD64
#define OS64BIT
#elif defined(__LP64)
#define OS64BIT
#else
#define OS32BIT
#endif











