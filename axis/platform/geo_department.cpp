#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"


namespace geo
{

   department::department()
   {

      m_bInitialLocalityTimeZoneInit = false;

      //m_bInitialCountryTimeZoneInit = false;

   }

   department::~department()
   {


   }


   void department::defer_check_openweather_city_list()
   {

      synchronous_lock synchronouslock(get_openweather_city_mutex());

      if (m_straCityLo.get_size() == m_straCity.get_size()
         && m_straCity.get_size() == m_iaIds.get_size()
         && m_iaIds.get_size() == m_daLon.get_size()
         && m_daLon.get_size() == m_daLat.get_size()
         && m_straCity.get_size() > 1)
      {

         return;

      }

      ::file::path pathFolder = m_psystem->m_pacmedir->system();

      bool bOk = false;

      auto pcontext = m_pcontext->m_pcontext;

      auto& file = pcontext->m_papexcontext->file();

      try
      {

         *file.get_reader(pathFolder / "weather-cit.bin") >> m_straCity;
         *file.get_reader(pathFolder / "weather-cil.bin") >> m_straCityLo;
         *file.get_reader(pathFolder / "weather-ids.bin") >> m_iaIds;
         *file.get_reader(pathFolder / "weather-lon.bin") >> m_daLon;
         *file.get_reader(pathFolder / "weather-lat.bin") >> m_daLat;


         //pcontext->m_papexcontext->file().to_array(m_straCity,          auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->system() / "weather-cit.bin");
         //pcontext->m_papexcontext->file().to_array(m_straCityLo,          auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->system() / "weather-cil.bin");
         //pcontext->m_papexcontext->file().to_array(m_iaIds,          auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->system() / "weather-ids.bin");
         //pcontext->m_papexcontext->file().to_array(m_daLon,          auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->system() / "weather-lon.bin");
         //pcontext->m_papexcontext->file().to_array(m_daLat,          auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->system() / "weather-lat.bin");


         bOk = m_straCityLo.get_size() == m_straCity.get_size()
            && m_straCity.get_size() == m_iaIds.get_size()
            && m_iaIds.get_size() == m_daLon.get_size()
            && m_daLon.get_size() == m_daLat.get_size()
            && m_straCity.get_size() > 1;


      }
      catch (...)
      {

      }

      if (!bOk)
      {

         try
         {

            file.del(pathFolder / "weather-cit.bin");
            file.del(pathFolder / "weather-cil.bin");
            file.del(pathFolder / "weather-ids.bin");
            file.del(pathFolder / "weather-lon.bin");
            file.del(pathFolder / "weather-lat.bin");

            m_straCityLo.erase_all();
            m_straCity.erase_all();
            m_iaIds.erase_all();
            m_daLon.erase_all();
            m_daLat.erase_all();

         }
         catch (...)
         {

         }

      }

      if (m_straCityLo.get_size() == m_straCity.get_size()
         && m_straCity.get_size() == m_iaIds.get_size()
         && m_iaIds.get_size() == m_daLon.get_size()
         && m_daLon.get_size() == m_daLat.get_size()
         && m_straCity.get_size() > 1)
      {
      }
      else
      {

         string str;

         str = file.as_string("https://server.ca2.software/city-list.json");

         if (str.has_char())
         {

            string_array stra;

            stra.add_lines(str);

            for (auto strJson : stra)
            {

               const char* pszJson = strJson;

               //const char * pszJson = "{\"_id\":6322752, \"name\" : \"Curitiba\", \"country\" : \"BR\", \"coord\" : {\"lon\":-49.290821, \"lat\" : -25.50395}}";

               ::payload v;

               v.parse_json(pszJson);

               string strLine = v["name"].string() + ", " + v["country"].string();

               m_straCity.add(strLine);

               m_straCityLo.add(strLine.lowered());

               i64 iId;

               v["_id"].as(iId);

               m_iaIds.add(iId);

               double dLon = v["coord"]["lon"].f64();

               m_daLon.add(dLon);

               double dLat = v["coord"]["lat"].f64();

               m_daLat.add(dLat);

            }

            *file.get_writer(pathFolder / "weather-cit.bin") << m_straCity;
            *file.get_writer(pathFolder / "weather-cil.bin") << m_straCityLo;
            *file.get_writer(pathFolder / "weather-ids.bin") << m_iaIds;
            *file.get_writer(pathFolder / "weather-lon.bin") << m_daLon;
            *file.get_writer(pathFolder / "weather-lat.bin") << m_daLat;

         }

      }

   }


   openweather_city* department::openweather_find_city(string strQuery)
   {

      auto& pcity = m_mapCity[strQuery];

      if (!pcity)
      {

         pcity = __new(openweather_city);

         pcity->m_iIndex = openweather_find_city2(
            strQuery,
            pcity->m_strCit,
            pcity->m_iId,
            pcity->m_dLat,
            pcity->m_dLon);

      }

      return pcity;

   }


   index department::openweather_find_city2(string strQuery, string& strCit, i64& iId, double& dLat, double& dLon)
   {

      string_array stra;

      stra.explode(",", strQuery);

      stra.trim();

      stra.erase_empty();

      if (stra.get_count() <= 0)
      {

         return -1;

      }

      if (stra.get_count() == 1)
      {

         return openweather_find_city2(strQuery, "", strCit, iId, dLat, dLon, true);

      }


      for (index iCount = stra.get_count() - 1; iCount >= 1; iCount--)
      {

         index iIndex = openweather_find_city2(stra.slice(0, iCount).implode(", "), stra.last(), strCit, iId, dLat, dLon, false);

         if (iIndex >= 0)
         {

            return iIndex;

         }

      }

      for (index iCount = stra.get_count() - 1; iCount >= 1; iCount--)
      {

         index iIndex = openweather_find_city2(stra.slice(0, iCount).implode(", "), stra.last(), strCit, iId, dLat, dLon, true);

         if (iIndex >= 0)
         {

            return iIndex;

         }

      }

      return -1;

   }



   index department::openweather_find_city2(string strQ1, string strQ2, string& strCit, i64& iId, double& dLat, double& dLon, bool bPrefix)
   {

      string strQueryLo;

      string strTry;

      string strTry1;

      string strTry2;

      index iFind;

      defer_check_openweather_city_list();

      if (strQ1.compare_ci("Cologne") == 0 && strQ2.compare_ci("DE") == 0)
      {

         strQ1 = "Koeln";

      }
      else if (strQ1.compare_ci("Washington DC") == 0)
      {

         strQ1 = "Washington, D. C.";

      }

      strQueryLo = strQ1 + ", " + strQ2;

      strQueryLo.make_lower();

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strQueryLo);

      }
      else
      {

         iFind = m_straCityLo.find_first(strQueryLo);

      }

      if (iFind >= 0)
      {

         goto found;

      }























      strTry = strQueryLo;

      strTry.replace("'", "");

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strTry);

      }
      else
      {

         iFind = m_straCityLo.find_first(strTry);

      }

      if (iFind >= 0)
      {

         goto found;

      }

































      strTry = strQueryLo;

      strTry.replace("st.", "saint");
      strTry.replace(unitext("são"), "sao");
      strTry.replace(unitext("ž"), "z");
      strTry.replace(unitext("á"), "a");
      strTry.replace(unitext("à"), "a");
      strTry.replace(unitext("ä"), "a");
      strTry.replace(unitext("é"), "e");
      strTry.replace(unitext("è"), "e");
      strTry.replace(unitext("ë"), "e");
      strTry.replace(unitext("í"), "i");
      strTry.replace(unitext("ì"), "i");
      strTry.replace(unitext("ï"), "i");
      strTry.replace(unitext("ó"), "o");
      strTry.replace(unitext("ò"), "o");
      strTry.replace(unitext("ö"), "o");
      strTry.replace(unitext("ú"), "u");
      strTry.replace(unitext("ù"), "u");
      strTry.replace(unitext("ü"), "u");

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strTry);

      }
      else
      {

         iFind = m_straCityLo.find_first(strTry);

      }

      if (iFind >= 0)
      {

         goto found;

      }









      return -1;

   found:

      strCit = m_straCity[iFind];

      iId = m_iaIds[iFind];

      dLat = m_daLat[iFind];

      dLon = m_daLon[iFind];

      return iFind;

   }


   bool department::locality_sunset(openweather_city* pcity, int& iRise, int& iSet)
   {

      if (pcity == nullptr)
      {

         return false;

      }

      const char* pszId =
#include "sensitive/openweather.txt"
         ;

      double dZone = 0.0;

      initial_locality_time_zone(pcity, dZone);

      int iTimeZone = (int)(dZone * 3600.0);

      property_set set;

      string strUrl = "http://api.openweathermap.org/data/2.5/weather?id=" + __str(pcity->m_iId) + "&APPID=" + string(pszId);

      auto psystem = get_system()->m_paxissystem;

      string strGetUrl = "https://ca2.software/api/account/openweather?request=" + psystem->url_encode(strUrl);

      auto pcontext = get_context();

      string str = pcontext->m_papexcontext->http().get(strGetUrl, set);

      synchronous_lock synchronouslock(mutex());

      const char* pszJson = str;

      ::payload v;

      v.parse_json(pszJson);

      ::datetime::zonetime timeSunrise(v["sys"]["sunrise"].i64(), iTimeZone);

      ::datetime::zonetime timeSunset(v["sys"]["sunset"].i64(), iTimeZone);

      iRise = (int)timeSunrise.GetZoneTimeOfDay();

      iSet = (int)timeSunset.GetZoneTimeOfDay();

      string strSunrise(timeSunrise.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      string strSunset(timeSunset.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      output_debug_string("sunrise:" + strSunrise + "\n");

      output_debug_string("sunset:" + strSunset + "\n");

      return true;

   }


   bool  department::locality_sunset(string strCountry, string strLocality, int& iRise, int& iSet)
   {

      auto psystem = get_system()->m_paxissystem;

      auto pcity = psystem->geo().openweather_find_city(strLocality + ", " + strCountry);

      if (pcity == nullptr)
      {

         return false;

      }

      return locality_sunset(pcity, iRise, iSet);


   }


   string department::initial_locality_time_zone(openweather_city* pcity, double& dZone)
   {

      if (pcity == nullptr)
      {

         dZone = 0.0;

         return "utc";

      }

      class ::datetime::department::time_zone timezone;

      ::datetime::time_span spanTimeout(1, 0, 0, 0);

      ::datetime::time now = ::datetime::time::get_current_time();

      ::mutex m(pcity, false, "Global\\ca2_datetime_departament");

      {

         synchronous_lock synchronouslock(&m);

         if (!m_bInitialLocalityTimeZoneInit)
         {

            m_bInitialLocalityTimeZoneInit = true;

            {

               ::file::path path = m_psystem->m_pacmedir->system() / "datetime_departament_cityTimeZone.bin";

               auto pcontext = get_context();

               auto file = pcontext->m_papexcontext->file().friendly_get_file(path, ::file::e_open_binary | ::file::e_open_read);

               if (file.is_set())
               {

                  ::binary_stream reader(file);

                  reader >> m_cityTimeZone;

               }

            }

         }

         if (m_cityTimeZone.lookup((iptr)pcity->m_iId, timezone) && (now - timezone.m_time) < spanTimeout
            && timezone.m_strZone.has_char())
         {

            dZone = timezone.m_dZone;

            return timezone.m_strZone;

         }

      }


      property_set set;

      string strLat = __str(pcity->m_dLat);

      string strLng = __str(pcity->m_dLon);

      string strKey;

#ifdef WINDOWS

      strKey = m_psystem->m_pacmefile->as_string("C:\\sensitive\\sensitive\\seed\\timezonedb.txt");

#else

      strKey = m_psystem->m_pacmefile->as_string("/sensitive/sensitive/seed/timezonedb.txt");

#endif

      auto pcontext = get_context();

      string str = pcontext->m_papexcontext->http().get("http://api.timezonedb.com/?key=" + strKey + "&format=json&lat=" + strLat + "&lng=" + strLng, set);

      if (str.has_char())
      {

         const char* pszJson = str;

         ::payload v;

         try
         {

            v.parse_json(pszJson);

            str = v["abbreviation"].string().lowered();

            dZone = v["gmtOffset"].f64() / 3600.0;

         }
         catch (...)
         {

            str = "utc";

            dZone = 0.0;

         }

      }
      else
      {

         str = "utc";

         dZone = 0.0;

      }

      timezone.m_strZone = str;

      timezone.m_dZone = dZone;

      timezone.m_time = now;

      {

         synchronous_lock synchronouslock(&m);

         m_cityTimeZone[(iptr)pcity->m_iId] = timezone;

         ::file::path path = m_psystem->m_pacmedir->system() / "datetime_departament_cityTimeZone.bin";

         auto file = pcontext->m_papexcontext->file().get_writer(path);

         ::binary_stream writer(file);

         writer << m_cityTimeZone;

      }

      return str;

   }


   string  department::initial_locality_time_zone(string strCountry, string strLocality, double& dZone)
   {

      string str;

      if (strLocality.is_empty())
      {

         str = initial_country_time_zone(strCountry);

         dZone = time_zone(str, strCountry);

         return str;

      }

      string strQ;

      strQ = strLocality;

      if (strCountry.has_char())
      {

         strQ += ", ";

         strQ += strCountry;

      }


      //  i64 iId;

//      double dLat;

      //    double dLon;

      auto psystem = get_system()->m_paxissystem;

      auto pcity = psystem->geo().openweather_find_city(strQ);

      return initial_locality_time_zone(pcity, dZone);

      //      if (pcity != nullptr)
      //      {
      //
      //
      //
      //         property_set set;
      //
      //         string strLat = __str(pcity->m_dLat);
      //
      //         string strLng = __str(pcity->m_dLon);
      //
      //         string strKey;
      //
      //#ifdef WINDOWS
      //
      //         strKey = m_psystem->m_pacmefile->as_string("C:\\sensitive\\sensitive\\seed\\timezonedb.txt");
      //
      //#else
      //
      //         strKey = m_psystem->m_pacmefile->as_string("/sensitive/sensitive/seed/timezonedb.txt");
      //
      //#endif
      //
      //         str = papplication->http_get("http://api.timezonedb.com/?key=" + strKey + "&format=json&lat=" + strLat + "&lng=" + strLng, set);
      //
      //         if (str.has_char())
      //         {
      //
      //            const char * pszJson = str;
      //
      //            ::payload v;
      //
      //            try
      //            {
      //
      //               v.parse_json(pszJson);
      //
      //               str = v["abbreviation"].get_string().lowered();
      //
      //               dZone = v["gmtoffset"].get_double() / 3600.0;
      //
      //            }
      //            catch (...)
      //            {
      //
      //               str = "utc";
      //
      //               dZone = 0.0;
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //            str = "utc";
      //
      //            dZone = 0.0;
      //
      //         }
      //
      //      }
      //      else
      //      {
      //
      //         str = "utc";
      //
      //         dZone = 0.0;
      //
      //      }
      //
      //
      //      timezone.m_strZone = str;
      //
      //      timezone.m_dZone = dZone;
      //
      //      timezone.m_time = now;
      //
      //      {
      //
      //         synchronous_lock synchronouslock(&m);
      //
      //         m_countryLocalityTimeZone[strCountry][strLocality] = timezone;
      //
      //         ::file::path path = m_psystem->m_pacmedir->public_system() / "datetime_departament_m_countryLocalityTimeZone.bin";
      //
      //         auto & file = pcontext->m_papexcontext->file().friendly_get_file(path, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_defer_create_directory);
      //
      //         stream os(file);
      //
      //         ::file::map::write(os, m_countryLocalityTimeZone);
      //
      //      }
      //
      //      return str;

   }

   // remark: initial does mean "official default" is certainly a rough guess
   string  department::initial_country_time_zone(string strCountry)
   {




      if (strCountry == "br")
      {

         return "brt";

      }
      else if (strCountry == "ua")
      {

         return "eest";

      }
      else if (strCountry == "us")
      {

         return "pdt";

      }
      else if (strCountry == "jp")
      {

         return "jst";

      }
      else if (strCountry == "de")
      {

         return "cest";

      }
      else if (strCountry == "fr")
      {

         return "cest";

      }
      else if (strCountry == "point_i32")
      {

         return "west";

      }
      else if (strCountry == "es")
      {

         return "cest";

      }
      else if (strCountry == "it")
      {

         return "cest";

      }
      else if (strCountry == "ar")
      {

         return "art";

      }
      else if (strCountry == "cl")
      {

         return "clst";

      }
      else if (strCountry == "uk")
      {

         return "bst";

      }
      else if (strCountry == "nl")
      {

         return "cest";

      }
      else if (strCountry == "cn")
      {

         return "cst";

      }
      else if (strCountry == "tw")
      {

         return "cst";

      }
      else if (strCountry == "ru")
      {

         return "msk";

      }
      else if (strCountry == "pl")
      {

         return "cest";

      }
      else if (strCountry == "am")
      {

         return "amt";

      }
      else if (strCountry == "dk")
      {

         return "cest";

      }
      else if (strCountry == "se")
      {

         return "cest";

      }
      else if (strCountry == "fi")
      {

         return "eest";

      }
      else if (strCountry == "ua")
      {

         return "eest";

      }
      else if (strCountry == "no")
      {

         return "cest";

      }
      else if (strCountry == "no")
      {

         return "cest";

      }
      else if (strCountry == "be")
      {

         return "cest";

      }
      else if (strCountry == "at")
      {

         return "cest";

      }
      else if (strCountry == "lu")
      {

         return "cest";

      }
      else if (strCountry == "li")
      {

         return "cest";

      }
      else if (strCountry == "ch")
      {

         return "cest";

      }
      else if (strCountry == "au")
      {

         return "aest";

      }
      else if (strCountry == "nz")
      {

         return "nzst";

      }
      else if (strCountry == "kr")
      {

         return "kst";

      }
      else if (strCountry == "ph")
      {

         return "pht";

      }
      else if (strCountry == "my")
      {

         return "myt";

      }
      else if (strCountry == "hk")
      {

         return "hkt";

      }
      else if (strCountry == "vn")
      {

         return "ict";

      }
      else if (strCountry == "in")
      {

         return "ist";

      }
      else if (strCountry == "ca")
      {

         return "adt";

      }
      else if (strCountry == "bg")
      {

         return "eet";

      }
      else
      {

         return "utc";

      }

   }



   string department::utc_offset_string(double dUTCOffset)
   {

      if (dUTCOffset == 1000000.0)
      {

         return "";

      }
      else if (dUTCOffset == 0.0)
      {

         return "UTC";

      }
      else if (utc_offset_invalid(dUTCOffset))
      {

         return "(" + ::str::signed_double(dUTCOffset) + " : invalid UTC?)";

      }
      else
      {

         string strUTCOffset;

         strUTCOffset = "UTC " + ::str::signed_int((int)dUTCOffset);

         double dMod = fmod(fabs(dUTCOffset), 1.0);

         if (dMod > 0.0)
         {

            string strMinutes;

            strMinutes.Format("%02d", (int)(60.0 * dMod));

            strUTCOffset += ":" + strMinutes;

         }

         return strUTCOffset;

      }

   }


   double department::time_zone(string str, string strCountryCode)
   {
      str.make_lower();
      strCountryCode.make_lower();
      double dTimeZoneOffset = 0.0;
      //Московское время (UTC+3)
      if (str == "msk")
      {

         dTimeZoneOffset = 3.0;

      }
      else if (str == "brt")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "cet")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "cest")
      {

         dTimeZoneOffset = 2.0;

      }
      else if (str == "eet")
      {

         dTimeZoneOffset = 2.0;

      }
      else if (str == "eest")
      {

         dTimeZoneOffset = 3.0;

      }
      else if (str == "pdt")
      {

         dTimeZoneOffset = -7.0;

      }
      else if (str == "est")
      {

         dTimeZoneOffset = -5.0;

      }
      else if (str == "edt")
      {

         dTimeZoneOffset = -4.0;

      }
      else if (str == "mst")
      {

         dTimeZoneOffset = -7.0;

      }
      else if (str == "mdt")
      {

         dTimeZoneOffset = -6.0;

      }
      else if (str == "jst")
      {

         dTimeZoneOffset = 9.0;

      }
      else if (str == "west")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "art")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "clst")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "bst")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "cdt")
      {

         dTimeZoneOffset = -5.0;

      }
      else if (str == "cst")
      {

         if (strCountryCode == "cn")
         {

            dTimeZoneOffset = 8.0;

         }
         else
         {

            dTimeZoneOffset = -6.0;

         }

      }
      else if (str == "amt")
      {

         dTimeZoneOffset = 4.0;

      }
      else if (str == "aest")
      {

         dTimeZoneOffset = 10.0;

      }
      else if (str == "nzst")
      {

         dTimeZoneOffset = 12.0;

      }
      else if (str == "kst")
      {

         dTimeZoneOffset = 9.0;

      }
      else if (str == "pht")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "myt")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "hkt")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "ict")
      {

         dTimeZoneOffset = 7.0;

      }
      else if (str == "utc")
      {

         dTimeZoneOffset = 0.0;

      }
      else if (str == "alphatime")
      {

         dTimeZoneOffset = -2.0;

      }
      else if (str == "ist")
      {

         dTimeZoneOffset = 5.5;

      }
      else if (str == "adt")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "brst")
      {

         dTimeZoneOffset = -2.0;

      }
      else if (::mathematics::convert_to_double(dTimeZoneOffset, str))
      {

      }
      else if (strCountryCode == "br")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (!::mathematics::convert_to_double(dTimeZoneOffset, strCountryCode))
      {

         TRACE("(2) ERROR !! Missing timezone offset information for \"%s\" - \"%s\"", str.c_str(), strCountryCode.c_str());

      }

      return dTimeZoneOffset;


   }

  

   bool utc_offset_invalid(double dUTCOffset)
   {

      return dUTCOffset < -12.0 || dUTCOffset > 14.0;  // don't know (is invalid?)

   }


} // namespace geo