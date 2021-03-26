//Created by camilo on 2021-03-26 00:44 BRT <3ThomasBS_
#include "framework.h"
#include "acme/primitive/text/_.h"


namespace acme
{

   
   context::context()
   {

      m_pcontext = nullptr;
      m_papexapplication = nullptr;
      m_paquaapplication = nullptr;
      m_pauraapplication = nullptr;
      m_paxisapplication = nullptr;
      m_pbaseapplication = nullptr;
      m_pbredapplication = nullptr;
      m_pcoreapplication = nullptr;
      m_papexsession = nullptr;
      m_paquasession = nullptr;
      m_paurasession = nullptr;
      m_paxissession = nullptr;
      m_pbasesession = nullptr;
      m_pbredsession = nullptr;
      m_pcoresession = nullptr;
      m_pacmesystem = nullptr;
      m_papexsystem = nullptr;
      m_paquasystem = nullptr;
      m_paurasystem = nullptr;
      m_paxissystem = nullptr;
      m_pbasesystem = nullptr;
      m_pbredsystem = nullptr;
      m_pcoresystem = nullptr;
      
      m_ptexttranslator = new text_translator();

      m_ptexttranslator->m_pcontext = this;

   }


   context::~context()
   {

      ::release(m_ptexttranslator);

   }

   
   void context::translate_text_data(text_data* ptextdata)
   {

      bool bSet = false;

      if (ptextdata->m_id.is_text())
      {

         if (::str::begins(ptextdata->m_id.m_psz, "text://"))
         {

            auto psz = ansi_chr(ptextdata->m_id.m_psz + 7, ':');

            if (psz)
            {

               ptextdata->m_str = psz + 1;

               return;

            }

         }

      }

      ptextdata->m_str = ptextdata->m_id;

   }


   text context::__text(const ::id& id)
   {

      return m_ptexttranslator->create_text_data(id);

   }


} // namespace acme



