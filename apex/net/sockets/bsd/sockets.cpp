#include "framework.h"
#include "apex/net/sockets/_sockets.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/os/ansios/_pthread.h"


#endif

namespace net
{

   extern class address_department * g_paddressdepartment;

}

namespace sockets
{


   sockets::sockets()
   {

      ::net::g_paddressdepartment = new class ::net::address_department;

      m_psslinit = nullptr;

      //m_pajpaxissocketinit    = nullptr;

   }


   sockets::~sockets()
   {

      ::acme::del(::net::g_paddressdepartment);
      ::acme::del(m_psslinit);

      //::acme::del(m_pajpaxissocketinit);

   }


   ::e_status sockets::initialize(::object * pobject)
   {

      auto estatus = sockets_base::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      generate_random_bytes(m_baTicketKey, sizeof(m_baTicketKey));

      m_psslinit = __create_new < ::sockets::SSLInitializer >();

      estatus = __construct_new(m_pnet);

      if(!estatus || !m_pnet)
      {

         m_iErrorCode = -1986;

         return error_failed;

      }

      if (!m_pnet->initialize(this))
      {

         return error_failed;

      }

      //if (!::apex::department::initialize())
      //{

      //   return error_failed;

      //}


#ifdef WINDOWS
      m_pportforward.create();
#endif


      //m_pajpaxissocketinit = new AjpBaseSocket::Initializer;

      m_countHttpPostBoundary = 0;

      return ::success;

   }

   
   ::e_status sockets::finalize()
   {

      sockets_base::finalize();

      bool bOk = true;

      if (m_pnet)
      {

         try
         {

            if (!m_pnet->gudo_set())
            {

               m_iErrorCode = -87;

            }

         }
         catch (...)
         {

            m_iErrorCode = -87;

         }

      }

#ifdef WINDOWS

      try
      {

         if(m_pportforward.is_set())
         {

            m_pportforward.release();

         }

      }
      catch(...)
      {

         bOk = false;

      }

      try
      {
         
         m_pportforward.release();

      }
      catch(...)
      {

      }

#endif

      if (m_pnet)
      {

         try
         {

            m_pnet->finalize();

         }
         catch (...)
         {

            m_iErrorCode = -87;

         }

         try
         {

            m_pnet.release();

         }
         catch (...)
         {

            m_iErrorCode = -86;

         }

      }

      ///::acme::del(m_pajpaxissocketinit);

      return ::success;

   }


   ::sockets::net & sockets::net()
   {

      return *m_pnet;

   }
   

} // namespace karaoke





/* Resolve DNS host entry. */
string ip_reverse(string str)
{

#if defined(_UWP) || defined(LINUX) || defined(ANDROID) || defined(__APPLE__)

   return c_gethostbyname(str);

#else

   hostent * pent = gethostbyname(str);

   if (pent == nullptr)
   {

      return "";

   }

   return pent->h_name;

#endif

}




#if defined(_UWP)


#include <openssl/ssl.h>


extern "C"
CLASS_DECL_APEX const SSL_METHOD * TLS_client_method()
{

   return TLSv1_2_client_method();

}


extern "C"
CLASS_DECL_APEX const SSL_METHOD * TLS_server_method()
{

   return TLSv1_2_server_method();

}


#endif



