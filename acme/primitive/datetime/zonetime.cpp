#include "framework.h"
#if defined(LINUX)
#include <time.h>
#endif


namespace datetime
{


   ::datetime::zonetime zonetime::get_current_time(time_t iZoneOffset) noexcept
   {

      zonetime t;

#ifdef WINDOWS

      t.m_time = ::_time64(nullptr);

#else

      t.m_time = ::time(nullptr);

#endif

      t.m_iZoneOffset = iZoneOffset;

      return t;

   }

zonetime::zonetime() noexcept :
   time(0),
        m_iZoneOffset(0)
   {

   }


zonetime::zonetime(const zonetime & zonetime) noexcept :
   time(zonetime.m_time),
   m_iZoneOffset(zonetime.m_iZoneOffset)
   {


   }


zonetime::zonetime(time_t zonetime, int iZoneOffset) noexcept :
   time(zonetime),
   m_iZoneOffset(iZoneOffset)
   {
   }

   zonetime::zonetime(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, i32 iZoneOffset)
   {
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant


#pragma warning (pop)

      struct tm atm;

      atm.tm_sec = nSec;
      atm.tm_min = nMin;
      atm.tm_hour = nHour;
      atm.tm_mday = nDay;
      atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
      atm.tm_year = nYear - 1900;     // tm_year is 1900 based
      atm.tm_isdst = 0;

#ifdef WINDOWS

      m_time = _mkgmtime64(&atm);

#else

      m_time = timegm(&atm);

#endif

      /*
      Remember that:
      ENSURE( nYear >= 1900 );
      ENSURE( nMonth >= 1 && nMonth <= 12 );
      ENSURE( nDay >= 1 && nDay <= 31 );
      ENSURE( nHour >= 0 && nHour <= 23 );
      ENSURE( nMin >= 0 && nMin <= 59 );
      ENSURE( nSec >= 0 && nSec <= 59 );
      ASSUME(m_time != -1);   */    // indicates an illegal input zonetime
      if (m_time == -1)
      {
         __throw(error_invalid_argument);
      }
   }





   struct tm* zonetime::GetZoneTm(struct tm* ptm) const
   {

      if (ptm != nullptr)
      {


#ifdef WINDOWS

         struct tm tmTemp;

         time_t t = m_time;

         t += m_iZoneOffset;

         errno_t err = _gmtime64_s(&tmTemp, &t);

         if (err != 0)
         {
            return nullptr;    // indicates that m_time was not initialized!
         }

         *ptm = tmTemp;

         return ptm;

#else

         struct tm * ptmTemp;


         time_t t = m_time;

         t += m_iZoneOffset;

         ptmTemp = gmtime(&t);

         // gmtime can return nullptr
         if (ptmTemp == nullptr)
            return nullptr;

         // but don't __throw( exception or generate error...
         // (reason for commenting out below, fat to be erased...)
         //         if(errno != 0)
         //          return nullptr;

         *ptm = *ptmTemp;

         return ptm;

#endif

      }
      else
      {

         return nullptr;

      }


   }


   i32 zonetime::GetZoneYear() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? (ptm->tm_year) + 1900 : 0;
   }

   i32 zonetime::GetZoneMonth() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_mon + 1 : 0;
   }

   i32 zonetime::GetZoneDay() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_mday : 0;
   }

   i32 zonetime::GetZoneHour() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_hour : -1;
   }

   i32 zonetime::GetZoneMinute() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_min : -1;
   }

   i32 zonetime::GetZoneSecond() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_sec : -1;
   }

   i32 zonetime::GetZoneDayOfWeek() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_wday + 1 : 0;
   }


   string zonetime::FormatZone(string & str, const ::string & strFormat) const
   {

      str = strFormat;

      str.replace("%Y", __str(GetZoneYear()));
      str.replace("%m", ::str::zero_padded(__str(GetZoneMonth()), 2));
      str.replace("%d", ::str::zero_padded(__str(GetZoneDay()), 2));
      str.replace("%H", ::str::zero_padded(__str(GetZoneHour()), 2));
      str.replace("%M", ::str::zero_padded(__str(GetZoneMinute()), 2));
      str.replace("%S", ::str::zero_padded(__str(GetZoneSecond()), 2));

      return str;

   }


   time_t zonetime::GetZoneTimeOfDay() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ((ptm->tm_hour * 3600) + (ptm->tm_min * 60) + ptm->tm_sec) : 0;

   }


   i64 zonetime::GetZoneDaySig() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

   }


   string zonetime::FormatZone(const ::string & strFormat)
   {
   
      string str;
   
      FormatZone(str, strFormat);
   
      return str;

   }


} // namespace datetime


#ifdef __DEBUG


dump_context & operator <<(dump_context & dumpcontext, ::datetime::zonetime zonetime)
{
   char psz[32];
   psz[0] = '\0';

   //   time_t tmp = zonetime.get_time();
   //   errno_t err = _ctime64_s(psz, sizeof(psz), &tmp);

   errno_t err = 0;

   if ((err != 0) || (psz[0] == '\0') || (zonetime.get_time() == 0))
   {
      dumpcontext << "::datetime::zonetime(invalid #" << (iptr)zonetime.get_time() << ")";

      return dumpcontext;
   }

   // format it
   dumpcontext << "::datetime::zonetime(\"" << psz << "\")";

   return dumpcontext;
}

#endif
