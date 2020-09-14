#pragma once


string get_error_message(DWORD dwError);


::aura::application *     macos_instantiate_application(::aura::application * pappSystem, const char * pszId);

CLASS_DECL_AURA void vfxThrowFileException(__pointer(::aura::application) papp, i32 cause, LONG lOsError, const char * lpszFileName = nullptr);

CLASS_DECL_AURA ::file::exception * get_FileException(::object * pobject, const ::estatus & estatus, LONG lOsError, const char * lpszFileName = nullptr);

#define NULL_REF(class) (*((class *) nullptr))

#define MAC_THREAD(pthread) (dynamic_cast < ::mac::thread * > (dynamic_cast < ::thread * >(pthread)))


CLASS_DECL_AURA void __trace_message(const char * lpszPrefix, ::message::message * pmessage);
CLASS_DECL_AURA void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);
WINBOOL mq_peek_message(LPMESSAGE lpMsg,oswindow hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
WINBOOL mq_get_message(LPMESSAGE lpMsg,oswindow hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
i32 CLASS_DECL_AURA __mac_main(i32 argc, char * argv[]);
CLASS_DECL_AURA void vfxThrowFileException(::object * pobject, const ::estatus & estatus, LONG lOsError, const char * lpszFileName = nullptr);



#include "factory_exchange.h"
#include "thread.h"
#include "os_context.h"


//#include "shell.h"

#include "application.h"






#include "file.h"
//#include "shell_macos.h"
#include "stdio_file.h"

#include "dir_system.h"
#include "file_system.h"

#include "dir_context.h"
#include "file_context.h"





//void ns_app_terminate();
void ns_create_alias(const char * pszTarget, const char * pszSource);

