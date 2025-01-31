#include "framework.h" 
#include "apex/id.h"
#include "apex/networking/sockets/_sockets.h"


#if defined(LINUX) || defined(__APPLE__)

#include <sys/time.h>

#endif

#define HEAVY_HTTP_LOG 0

namespace sockets
{


   http_socket::http_socket() :
      //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      m_bFirst(true),
      m_bHeader(true),
      m_bRequest(false),
      m_bResponse(false),
      m_body_size_left(0),
      m_body_size_downloaded(0),
      m_b_http_1_1(false),
      m_b_keepalive(false),
      m_chunk_size(0),
      m_chunk_state(0)
   {

      m_bOnlyHeaders = false;
      m_bNoClose = false;
      m_request.attr(__id(http_version)) = "HTTP/1.1";
      SetLineProtocol();
      DisableInputBuffer();

   }


   http_socket::~http_socket()
   {

   }


   ::e_status http_socket::on_initialize_object()
   {

      auto estatus = tcp_socket::on_initialize_object();

      if (!estatus)
      {

         return estatus;

      }

      m_request.m_psystem = m_psystem;

      m_response.m_psystem = m_psystem;

      return estatus;

   }


   void http_socket::OnRawData(char * buf, memsize len)
   {

      if (!m_bHeader)
      {

         if (m_b_chunked)
         {

            memsize ptr = 0;

            while (ptr < len)
            {

               switch (m_chunk_state)
               {
               case 4:
                  while (ptr < len && (m_chunk_line.get_length() < 2 || m_chunk_line.Mid(m_chunk_line.get_length() - 2) != "\r\n"))
                     m_chunk_line += buf[ptr++];
                  if (m_chunk_line.get_length() > 1 && m_chunk_line.Mid(m_chunk_line.get_length() - 2) == "\r\n")
                  {
                     OnDataComplete();
                     // prepare for next request(or response)
                     m_b_chunked = false;
                     SetLineProtocol( true );
                     m_bFirst = true;
                     m_bHeader = true;
                     m_body_size_left = 0;
                     m_body_size_downloaded = 0;
                     if (len - ptr > 0)
                     {
                        memory mem;
                        mem.set_size(TCP_BUFSIZE_READ);
                        char * tmp = (char*)mem.get_data();
                        ::memcpy_dup(tmp,buf + ptr,len - ptr);
                        tmp[len - ptr] = 0;
                        on_read( tmp, (int) (len - ptr ));
                        ptr = len;
                     }
                  }
                  break;
               case 0:
                  while (ptr < len && (m_chunk_line.get_length() < 2 || m_chunk_line.Mid(m_chunk_line.get_length() - 2) != "\r\n"))
                     m_chunk_line += buf[ptr++];
                  if (m_chunk_line.get_length() > 1 && m_chunk_line.Mid(m_chunk_line.get_length() - 2) == "\r\n")
                  {
                     m_chunk_line = m_chunk_line.Left(m_chunk_line.get_length() - 2);
                     ::str::parse pa(m_chunk_line, ";");
                     string size_str = pa.getword();
                     m_chunk_size = ::hex::to_u32(size_str);
                     if (!m_chunk_size)
                     {
                        m_chunk_state = 4;
                        m_chunk_line = "";
                     }
                     else
                     {
                        m_chunk_state = 1;
                        m_chunk_line = "";
                     }
                  }
                  break;
               case 1:
               {
                  memsize left = len - ptr;
                  memsize sz = m_chunk_size < left ? m_chunk_size : left;
                  OnData(buf + ptr, sz);
                  m_chunk_size -= sz;
                  ptr += sz;
                  if (!m_chunk_size)
                  {
                     OnEndChunk();
                     m_chunk_state = 2;
                  }
               }
               break;
               case 2: // skip CR
                  ptr++;
                  m_chunk_state = 3;
                  break;
               case 3: // skip LF
                  ptr++;
                  m_chunk_state = 0;
                  break;
               }
            }
         }
         else
         {

            memsize sizeData = m_body_size_left < len ? m_body_size_left : len;

            m_body_size_left -= sizeData;

            m_body_size_downloaded += sizeData;

            OnData(buf, sizeData);

            if (!m_body_size_left)
            {

               OnDataComplete();

               if (!m_b_keepalive)
               {

                  /*
                  request is HTTP/1.0 _or_ HTTP/1.1 and not keep-alive

                  This means we destroy the connection after the response has been delivered,
                  hence no need to reset all internal state variables for a new incoming
                  request.
                  */

               }
               else
               {

                  // prepare for next request(or response)

                  SetLineProtocol(true);

                  m_bFirst = true;

                  m_bHeader = true;

                  m_body_size_left = 0;

                  if (len - sizeData > 0)
                  {

                     on_read(buf + sizeData, (int)(len - sizeData));

                  }

               }

            }

         }

      }

   }


   void http_socket::OnLine(const string & line)
   {

      if (m_bFirst)
      {

#if 0

         INFO(line);

#endif

         m_microsFirstTime = get_micros();

         ::str::parse pa(line);

         string str = pa.getword();
         if (str.get_length() > 4 &&  ::str::begins_ci(str, "http/")) // response
         {
            //m_response.attr(__id(remote_addr)) = GetRemoteAddress().get_display_number();
            m_response.attr(__id(http_version)) = str;
            string strHttpStatusCode = pa.getword();
            m_response.attr(__id(http_status_code)) = strHttpStatusCode;
            m_response.attr(__id(http_status)) = pa.getrest();
            m_bResponse    = true;
            m_bRequest     = false;
         }
         else // request
         {
            str.make_lower();
            //m_request.attr(__id(remote_addr)) = GetRemoteAddress().get_display_number();
            m_request.m_idHttpMethod = str;
            m_request.attr(__id(http_method)) = str;
            m_request.attr(__id(https)) = IsSSL();
            if(IsSSL())
            {
               m_request.attr(__id(http_protocol)) = "https";
            }
            else
            {
               m_request.attr(__id(http_protocol)) = "http";
            }

            string strRequestUri = pa.getword();

            auto psystem = m_psystem;

            auto purl = psystem->url();

            string strScript = purl->object_get_script(strRequestUri);

            string strQuery = purl->object_get_query(strRequestUri);

            m_request.m_strRequestUri = purl->url_decode(strScript) + ::str::has_char(strQuery, "?");
            m_request.attr(__id(request_uri)) = m_request.m_strRequestUri;
            m_request.attr(__id(http_version)) = pa.getword();
            m_b_http_1_1 = ::str::ends(m_request.attr(__id(http_version)).string(), "/1.1");
            m_b_keepalive = m_b_http_1_1;
            m_bRequest     = true;
            m_bResponse    = false;
         }
         m_bFirst = false;
         OnFirst();
         return;
      }

      if (!line.get_length())
      {

         if (m_body_size_left || !m_b_keepalive || m_b_chunked)
         {

            SetLineProtocol(false);

            m_bHeader = false;

         }

         OnHeaderComplete();

         if(!m_body_size_left && !m_b_chunked)
         {

            OnDataComplete();

         }

         return;

      }

      id key;
      string strKey;
      string value;
      strsize iFind = line.find(':');
      if(iFind < 0)
      {
         strKey = line;
      }
      else
      {
         strKey = line.Left(iFind);
         strKey.trim();
         iFind++;
         while(isspace((unsigned char) line[iFind]) && iFind < line.get_length())
         {
            iFind++;
         }
         strsize iLen = line.get_length();
         while(iLen >= iFind && isspace((unsigned char ) line[iLen - 1]))
         {
            iLen--;
         }
         value = line.Mid(iFind, iLen - iFind);
      }

      strKey.make_lower();

      key = strKey;

      OnHeader(key, value);

      if(key == __id(host))
      {

         m_request.m_strHttpHost = value;

         m_request.attr(__id(http_host)) = value;

      }
      else if(key == __id(content_length))
      {

         m_body_size_left = atol(value);

         m_body_size_downloaded = 0;

      }
      else if(key == __id(connection))
      {

         if (m_b_http_1_1)
         {

            if(::str::equals_ci(value,"close"))
            {

               m_b_keepalive = false;

            }
            else
            {

               m_b_keepalive = true;

            }

         }
         else
         {

            if(::str::equals_ci(value, "keep-alive"))
            {

               m_b_keepalive = true;

            }
            else
            {

               m_b_keepalive = false;

            }

         }

      }
      if (::str::equals_ci(key, "transfer-encoding") && ::str::ends_ci(value, "chunked"))
      {
         m_b_chunked = true;
      }
      /* If remote end tells us to keep connection alive, and we're operating
      in http/1.1 mode (not http/1.0 mode), then we mark the socket to be
      retained. */
      if(m_b_keepalive)
      {

         SetRetain();

      }

   }


   bool http_socket::http_filter_response_header(string & strKey, string_array & straValue)
   {
      __UNREFERENCED_PARAMETER(strKey);
      __UNREFERENCED_PARAMETER(straValue);
      return true;
   }


   void http_socket::SendResponse()
   {

      string msg;
      
      string strLine;
      
      strLine = m_response.attr(__id(http_version)).string() + " " + m_response.attr(__id(http_status_code)) + " " + m_response.attr(__id(http_status));

      msg = strLine + "\r\n";
      
      string strHost;
      
      strHost = m_response.header(__id(host));

      if(strHost.has_char())
      {
         
         msg += "Host: " + strHost + "\r\n";
         
         TRACE("Host: %s", strHost.c_str());

      }

      bool bContentLength = m_response.attr(__id(http_status_code)) != 304;

      if(bContentLength)
      {

         if(!m_response.m_propertysetHeader.has_property(__id(content_length)))
         {

            m_response.m_propertysetHeader[__id(content_length)] = response().file()->get_size();

         }

      }
      else
      {

         m_response.m_propertysetHeader.erase_by_name(__id(content_length));

      }

      for(auto & pproperty : m_response.m_propertysetHeader)
      {

         string strKey = pproperty->name();

         string_array & straValue = pproperty->as_stra();

         if (!http_filter_response_header(strKey, straValue))
         {

            continue;

         }

         if (strKey.compare_ci("host") == 0)
         {

            continue;

         }

         for (int j = 0; j < straValue.get_count(); j++)
         {

            string strValue = straValue[j];
            //         strLine = ;
            msg += strKey + ": " + strValue + "\r\n";
            //TRACE("%s: %s", strKey, strValue);
         }
         //TRACE(strTrace + "\n");
      }

      for (auto & pcookie : m_response.cookies())
      {

         msg += "Set-Cookie: " + pcookie->get_cookie_string() + "\r\n";

      }

      msg += "\r\n";

      print( msg );

      if(bContentLength)
      {

         SendResponseBody();

      }

   }

   void http_socket::SendResponseBody()
   {
      if (response().m_strFile.has_char())
      {

         string strFile = response().m_strFile;

         response().m_strFile.Empty();

         file_pointer spfile(e_create, this);

         try
         {

            if (spfile->open(strFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none).failed())
            {

               __throw(::error_io, "http_socket::SendResponseBody(1) file=" + strFile + "\n");

            }

         }
         catch (...)
         {

            __throw(::error_io, "http_socket::SendResponseBody(2) file=" + strFile + "\n");

         }

         __transfer_to_writer(*this, spfile);

      }
      else if(response().file()->get_size() > 0)
      {

         response().file()->seek_to_begin();

         __transfer_to_writer(*this, response().file());

      }

   }




   void http_socket::SendRequest()
   {

      string msg;

      string strLine;

      msg = m_request.attr("http_method").string() + " " + m_request.attr("request_uri").string() + " " + m_request.attr("http_version").string() + "\r\n";

      if (m_request.m_propertysetHeader[__id(host)].string().has_char())
      {

         strLine = "Host: " + m_request.m_propertysetHeader[__id(host)].to_string();

         if(m_iProxyPort > 0 ||
               (m_iConnectPort != 80 && !IsSSL()) || (m_iConnectPort != 443 && IsSSL()))
         {

            strLine += ":";

            strLine += __str(m_iConnectPort);

         }

         msg += strLine + "\r\n";

      }

      for(auto & pproperty : m_request.m_propertysetHeader)
      {

         string strValue = pproperty->string();

         if (pproperty->name() == __id(content_type))
         {

            msg += "Content-Type: " + strValue + "\r\n";

         }
         else
         {

            string strKey = pproperty->name();

            if (strKey.compare_ci("host") == 0)
            {

               continue;

            }

            strValue.trim();

            if (strValue.is_empty())
            {

               continue;

            }

            msg += strKey + ": " + strValue + "\r\n";

         }

      }

      msg += "\r\n";

      print( msg );

   }


   string http_socket::MyUseragent()
   {
      string version = "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:10.0) Gecko/20100101 veriview/10.0";

      //string version = "Mozilla/5.0 (Windows; U; Windows NT 6.0; point_i32-BR; rv:1.9.2.13) Gecko/20101203 Firefox/3.6.13";
      //string version = "C++Sockets/";
#ifdef _VERSION
      version += _VERSION;
#endif
      return version;
   }


   void http_socket::Reset()
   {
      m_bFirst       = true;
      m_bHeader      = true;
      m_bRequest     = false;
      m_bResponse    = false;
      SetLineProtocol(true);
      m_request.clear();
      m_response.clear();
   }




   void http_socket::url_this(string strUrl, string & strProtocol, string & strHost, port_t & port, string & strRequestUri, string & strFile)
   {

      if (!strUrl.eat_before(strProtocol, "://"))
      {

         return;

      }

      if(strProtocol.equals_ci("https") || strProtocol.equals_ci("wss"))
      {

#ifdef HAVE_OPENSSL

         EnableSSL();

#else

#ifndef _UWP


         WARN("url_this",-1,"SSL not available");

#endif

#endif
         port = 443;

      }
      else
      {

         port = 80;

      }

      string strPort;

      strUrl.eat_before_let_separator(strPort, "/", true);

      if (strPort.eat_before(strHost, ":", true))
      {

         port = atoi(strPort);

      }

      strRequestUri = strUrl;

      strUrl.eat_before(strFile, "?", true);

   }


   void http_socket::OnFirst()
   {
   }

   void http_socket::OnHeader(id key, const string & value)
   {



      //http_socket::OnHeader(key, value);
      /*if(key.compare_ci("user-agent") == 0)
      {
         TRACE("  (request)OnHeader %s: %s\n", (const char *) key, (const char *) value);
      }*/
      if(key == __id(cookie))
      {
         m_request.cookies().parse_header(value);
         //m_response.cookies().parse_header(value);
      }
      else
         m_request.header(key) = value;

   }


   void http_socket::OnHeaderComplete()
   {

      if(IsRequest())
      {

         m_request.header(__id(content_length)).as(m_body_size_left);

         m_body_size_downloaded = 0;

      }

      if(IsResponse())
      {

         m_response.header(__id(content_length)).as(m_body_size_left);

         m_body_size_downloaded = 0;

      }

      if(m_bOnlyHeaders)
      {

         SetCloseAndDelete();

      }

   }


   void http_socket::OnData(const char *, memsize)
   {

   }


   void http_socket::OnDataComplete()
   {
   }

   void http_socket::client_to_server(http_socket * psocket)
   {

      //m_ssl             = psocket->m_ssl;
      m_socket          = psocket->m_socket;
      m_bSsl            = psocket->m_bSsl;
      m_bSslServer      = psocket->m_bSslServer;
      m_bEnableSsl      = psocket->m_bEnableSsl;
      m_bConnected      = psocket->m_bConnected;

      SetRemoteHostname(psocket->GetRemoteHostname());

   }

   void http_socket::OnEndChunk()
   {
   }
} // namespace sockets


