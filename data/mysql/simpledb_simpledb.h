#pragma once


namespace aura
{


   class command_line;


} // namespace aura


class db_server;


namespace simpledb
{


   class CLASS_DECL_AURA simpledb :
      virtual public ::acme::department,
      virtual public ::database::database
   {
   public:


      db_server   *  m_pserver;


      simpledb(::object * pobject);
      virtual ~simpledb();

      virtual bool init2();
      virtual bool initialize();
      virtual bool destroy();

      virtual ::database::server * get_data_server();
      virtual db_server & db();

      virtual void on_set_locale(const ::string & lpcsz, const ::action_context & action_context);
      virtual void on_set_schema(const ::string & lpcsz, const ::action_context & action_context);


      virtual bool InitializeDataCentral();
      virtual bool FinalizeDataCentral();

      virtual bool set_keyboard_layout(const ::string & pszPath, const ::action_context & action_context);
      virtual void on_set_keyboard_layout(const ::string & pszPath, const ::action_context & action_context);

   };


} // namespace simpledb






