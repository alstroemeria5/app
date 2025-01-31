#include "framework.h"
#include "core/user/netuser/_netuser.h"
#include "aqua/xml.h"


namespace usernet
{


   network_configuration::network_configuration()
   {

      m_pdocument   = nullptr;
      m_pimpact  = nullptr;

   }


   network_configuration::~network_configuration()
   {
   }


   bool network_configuration::initialize(__pointer(::user::interaction) puiParent)
   {

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      m_pdocument = puser->create_form(this, this, puiParent);

      if(m_pdocument != nullptr)
      {

         m_pimpact = m_pdocument->get_typed_view < ::user::form > ();

         m_pimpact->set_form_callback(this);

         return true;

      }

      return false;

   }


   bool network_configuration::initialize_child(__pointer(::user::interaction) puiParent)
   {

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      puser->create_child_form(this, this, puiParent);

      if(m_pdocument != nullptr)
      {

         m_pimpact = m_pdocument->get_typed_view < ::user::form > ();

         m_pimpact->set_form_callback(this);

         return true;

      }

      return false;

   }


   void network_configuration::on_show()
   {

      auto pcontext = get_context();

      if(!m_pdocument->on_open_document(pcontext->m_papexcontext->dir().matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }

      xml::document doc;

      if(doc.load(pcontext->m_papexcontext->file().as_string(pcontext->m_papexcontext->dir().appdata()/"proxy.xml")))
      {
         
         string strProxy(doc.root()->attribute("server"));

         i32 iProxyPort;

         doc.root()->attribute("port").as(iProxyPort);
         
         auto pinteraction = m_pimpact->get_child_by_name("server");
         
         pinteraction->_001SetText(strProxy, ::action_context(::e_source_data) +  ::e_source_load);

         pinteraction = m_pimpact->get_child_by_name("port");
         
         pinteraction->_001SetText(__str(iProxyPort), ::action_context(::e_source_data) +  ::e_source_load);

      }

   }


   void network_configuration::on_control_event(::user::control_event * pevent)
   {

      auto pcontext = get_context();

      if(pevent->m_eevent == ::user::e_event_click)
      {

         if(pevent->m_puserinteraction->m_id == "submit")
         {

            auto pinteraction = m_pimpact->get_child_by_name("server");

            string strServer;

            pinteraction->_001GetText(strServer);

            if(strServer.get_length() == 0)
            {

               pcontext->m_papexcontext->file().del(pcontext->m_papexcontext->dir().appdata()/ "proxy.xml");

            }
            else
            {

               xml::document doc;

               doc.root()->set_name("proxy");

               doc.root()->set_attribute("server", strServer);

               pinteraction = m_pimpact->get_child_by_name("port");

               string strPort;

               pinteraction->_001GetText(strPort);

               doc.root()->set_attribute("port", strPort);

               pcontext->m_papexcontext->file().put_contents(pcontext->m_papexcontext->dir().appdata()/"proxy.xml", doc.get_xml());

            }

         }

      }

   }


} // namespace usernet


