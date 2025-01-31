//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once


#include "acme/node/operating_system/_.h"


//CLASS_DECL_APEX string get_command_line();

#if defined(MACOS)

#include "apex/node/operating_system/ansi/_.h"
#include "apex/node/operating_system/apple/_.h"
#include "apex/node/operating_system/macos/_.h"

#elif defined(APPLE_IOS)

#include "apex/os/ansios/_.h"
#include "apex/os/apple/_.h"
#include "apex/os/ios/_.h"

#elif defined(LINUX)

#include "apex/node/operating_system/ansi/_.h"
#include "apex/node/operating_system/posix/_.h"
#include "apex/node/operating_system/linux/_.h"

#elif defined(_UWP)

#include "apex/node/operating_system/ansi/_.h"
#include "apex/node/operating_system/windows_common/_.h"
#include "apex/node/operating_system/universal_windows/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "apex/node/operating_system/ansi/_.h"
#include "apex/node/operating_system/windows_common/_.h"
#include "apex/node/operating_system/windows/_.h"

#elif defined(ANDROID)

#include "apex/os/ansios/_.h"
#include "apex/os/android/_.h"

#elif defined(SOLARIS)

#include "apex/os/ansios/_.h"
#include "apex/os/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif

template < typename PRED >
inline bool predicate_Sleep(int iTime, PRED pred);


//void adapt_font_name(string & str);


//namespace str
//{
//
//   string CLASS_DECL_APEX get_window_text_timeout(::windowing::window * pwindow, millis tickTimeout = 1000);
//
//} // namespace str


//
//
////__pointer(pcre_context) pcre_context::create_context(int iSizeData)
////{
////
////   return __new(pcre_context_impl( iSizeData));
////
////}
//////
////
////__pointer(regex) pcre_regex::compile(::object* pobject, const string& str)
////{
////
////   __pointer(pcre_context_impl) pcreContextImpl = pcre_context::create_context(pobject, 0);
////
////   auto putil = __new(pcre_util_impl(pcreContextImpl));
////
////   putil->compile(str);
////
////   return putil;
////
////}
////
////
////__pointer(pcre_code) pcre_code::compile(pcre_context* m_pcreContext, const string& str)
////{
////
////   __pointer(pcre_context_impl) pimpl = m_pcreContext;
////
////   auto pcode = __new(pcre_code_impl(pimpl));
////
////   pcode->compile(str);
////
////   return pcode;
////
////}
////
////
////namespace axis
////{
////
////
////   __pointer(regex) system::create_pcre(const string& str)
////   {
////
////      return pcre_regex::compile(this, str);
////
////   }
////
////   __pointer(regex_context) system::create_pcre_context(int iCount)
////   {
////
////      return pcre_context::create_context(this, iCount);
////   }
////
////
////   int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)
////   {
////
////      throw_todo();
////
////      return -1;
////
////   }
////
////
////} // namespace axis
////
////
////
////namespace axis
////{
////
////
////}
////
////
////CLASS_DECL_APEX void defer_dock_application(int_bool bDock);


//CLASS_DECL_APEX string get_current_login_name();


//#if defined(WINDOWS)
//
//
//CLASS_DECL_APEX _locale_t get_c_locale();
//
//
//#else
//
//
//CLASS_DECL_APEX locale_t get_c_locale();
//
//#endif



