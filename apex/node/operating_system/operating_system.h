#pragma once


//CLASS_DECL_APEX void defer_dock_application(int_bool bDock);


//CLASS_DECL_APEX int_bool IsProcessRunning(::u32 pid);



#include "file.h"


#include "thread.h"

#include "cross.h"

//CLASS_DECL_APEX int __c_get_text_length(const char * psz);
//CLASS_DECL_APEX void __c_get_text(char * pszText, int iLen, const char * psz);


/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/


#ifdef cplusplus

inline bool IsDirSep(widechar wch);

#endif

//CLASS_DECL_APEX void set_splash(oswindow oswindow);
//CLASS_DECL_APEX oswindow get_splash(void);

//CLASS_DECL_APEX int get_processor_count(void);
//CLASS_DECL_APEX void writeln(const char * psz);


#include "time.h"







//CLASS_DECL_APEX void set_command_line_dup(const char * psz);

//CLASS_DECL_APEX void get_command_line(char * psz, int iBuffer);





#ifdef __cplusplus

#include "windowing.h"

#endif


#include "graphics.h"


#pragma once


//#include "apex/os/binreloc.h"




#ifdef AMD64
#define OS64BIT
#elif defined(__LP64)
#define OS64BIT
#else
#define OS32BIT
#endif











