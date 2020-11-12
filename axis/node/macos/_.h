#pragma once


string get_error_message(::u32 dwError);


::aura::application *     macos_instantiate_application(::aura::application * pappSystem, const char * pszId);

#define NULL_REF(class) (*((class *) nullptr))

#define MAC_THREAD(pthread) (dynamic_cast < ::mac::thread * > (dynamic_cast < ::thread * >(pthread)))


CLASS_DECL_AXIS void __trace_message(const char * lpszPrefix, ::message::message * pmessage);
CLASS_DECL_AXIS void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);
int_bool mq_peek_message(LPMESSAGE lpMsg,oswindow hWnd,::u32 wMsgFilterMin,::u32 wMsgFilterMax,::u32 wRemoveMsg);
int_bool mq_get_message(LPMESSAGE lpMsg,oswindow hWnd,::u32 wMsgFilterMin,::u32 wMsgFilterMax);
i32 CLASS_DECL_AXIS __mac_main(i32 argc, char * argv[]);



#include "factory_exchange.h"
//#include "thread.h"
//#include "os_context.h"
//
//
//#include "shell.h"
//
//#include "application.h"
//
//
//
//
//
//
//#include "file.h"
//#include "shell.h"
//#include "stdio_file.h"
//
//#include "dir_system.h"
//#include "file_system.h"
//
//#include "dir_context.h"
//#include "file_context.h"





//void ns_app_terminate();
//void ns_create_alias(const char * pszTarget, const char * pszSource);


