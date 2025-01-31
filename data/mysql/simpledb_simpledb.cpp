#include "framework.h"
#ifndef _UWP
#include "mysql/mysql.h"
#endif


namespace simpledb
{


   simpledb::simpledb(::object * pobject) :
      ::object(pobject),
      ::acme::department(pobject)
   {

      m_pserver      = nullptr;

   }

   simpledb::~simpledb()
   {

   }

   bool simpledb::InitializeDataCentral()
   {

      if(get_application()->is_system())
      {
      }

      m_pserver = new db_server(get_application());


      m_pserver->add_client(this);

      if(!m_pserver->initialize())
      {
         Platform.userex()->message_box(nullptr, "Could not initialize simpledb.", e_message_box_ok);
         return false;
      }

      return true;
   }

   void simpledb::on_set_locale(const ::string & lpcsz, const ::action_context & context)
   {
      if(context.is_user_source())
      {
         data_set("&data_source=local&locale", lpcsz);
      }
      get_application()->m_psession->on_set_locale(lpcsz, context);
   }

   void simpledb::on_set_schema(const ::string & lpcsz, const ::action_context & context)
   {
      if(context.is_user_source())
      {
         data_set("&data_source=local&schema", lpcsz);
      }
      get_application()->m_psession->on_set_schema(lpcsz,context);
   }

   bool simpledb::FinalizeDataCentral()
   {

      try
      {
         m_pserver->destroy();
      }
      catch(...)
      {
      }

      try
      {
         delete m_pserver;
      }
      catch(...)
      {
      }

      if(get_application()->is_system())
      {

         m_pserver = nullptr;
      }

      return true;
   }

   bool simpledb::init2()
   {

      if(get_application()->m_pcoreapp->m_varTopicQuery["locale"].get_count() > 0)
      {
         string str = get_application()->m_pcoreapp->m_varTopicQuery["locale"].stra()[0];
         get_application()->m_psession->set_locale(str,::e_source_database);
      }

      if(get_application()->m_pcoreapp->m_varTopicQuery["schema"].get_count() > 0)
      {
         string str = get_application()->m_pcoreapp->m_varTopicQuery["schema"].stra()[0];
         get_application()->m_psession->set_schema(str,::e_source_database);
      }

//      if(&AppUser(this) == nullptr)
  //       return false;

      if(!InitializeDataCentral())
      {
         get_application()->m_pcoreapp->message_box(nullptr, "Could not initialize data central");
         return false;
      }

      ::database::client::initialize_data_client(m_pserver);

      if (papplication->m_spdataserver.is_null())
      {

         papplication->m_spdataserver = m_pserver;

      }


//      ::aura::application_request * prequest = psystem->get_application_request();


      get_application()->m_psession->fill_locale_schema(*get_application()->m_psession->textcontext()->m_plocaleschema);


      //if(!get_application()->m_pcoreapp->is_installing() && !get_application()->m_pcoreapp->is_unstalling() && !get_application()->m_pcoreapp->is_system())
      //{

      //   set_keyboard_layout(nullptr, context + ::e_source_sync + ::e_source_system;

      //}


      return true;

   }




   bool simpledb::initialize()
   {



      if(!::database::database::initialize())
         return false;



      return true;


   }


   bool simpledb::destroy()
   {

      try
      {
       //  ::database::database::destroy();
      }
      catch(...)
      {
      }

      try
      {
         FinalizeDataCentral();
      }
      catch(...)
      {
      }


      return true;


   }


   ::database::server * simpledb::get_data_server()
   {

      return m_pserver;

   }


   db_server & simpledb::db()
   {

      return *m_pserver;

   }


   bool simpledb::set_keyboard_layout(const ::string & pszPath, const ::action_context & context)
   {

      return psession->set_keyboard_layout(pszPath, context);

   }


   void simpledb::on_set_keyboard_layout(const ::string & pszPath, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         if(Sess(get_application()).safe_get_user() != nullptr)
         {

            data_set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace simpledb



