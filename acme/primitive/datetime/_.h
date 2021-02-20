#pragma once


#include "system_time.h"
#include "result.h"

#include "microsecond_sleep.h"
//namespace datetime
//{
//
//
//   CLASS_DECL_ACME string to_string(::matter * pobject, const ::acme::str_context * pcontext, const ::datetime::result & value);
//
//
//   CLASS_DECL_ACME value span_strtotime(::matter * pobject, const ::acme::str_context * pcontext, const char * psz);
//   CLASS_DECL_ACME value strtotime(::matter * pobject, const ::acme::str_context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);
//
//
//} // namespace datetime


#ifdef WINDOWS


extern "C" CLASS_DECL_ACME time_t timegm(struct tm *tmp);


#endif


extern "C" CLASS_DECL_ACME int c_localtime_offset();


//#include "department.h"


#include "micro_duration.h"



