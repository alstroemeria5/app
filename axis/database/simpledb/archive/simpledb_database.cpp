#include "framework.h"


namespace simpledb
{


   database::database(::layered * pobjectContext):
      ::object(pobject)
   {

      defer_create_mutex();

      m_protocol = 0;

   }


   database::~database()
   {

      close();

   }


   bool database::initialize()
   {

      return true;

   }

   bool database::connect(
   const char * pszHost,
   const char * pszUser,
   const char * pszPassword,
   const char * pszDatabase,
   i32 iPort,
   const char * pszSocketName,
   u32 uFlags)
   {
      return false;
   }

   bool database::close()
   {
      return false;

   }

   string database::error1(const char * pszPrefix)
   {
      return "";
   }

   void database::trace_error1(const char * pszPrefix)
   {

      m_strLastError += error1(pszPrefix);

      TRACE("%s", m_strLastError);

   }


   __pointer(result) database::query(const char * pszSql)
   {

      return nullptr;

   }


   ::payload database::query_item(const char * pszSql,::payload varDefault)
   {

      return ::payload(::e_type_null);

   }


   bool database::query_blob(memory_base & memory,const char * pszSql)
   {

      return false;

   }


   ::payload database::query_items(const char * pszSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_row(const char * pszSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_rows(const char * pszSql)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::query_table_item(const char * table,const char * item,const char *where,::payload notfound)
   {

      return ::payload(::e_type_null);

   }


   ::payload database::get_agent(const char * pszTable,const char * psz,const char * pszUser)
   {

      return ::payload(::e_type_null);

   }


   string database::escape(void * p,strsize iLen)
   {

      return "";

   }


   string database::escape(const char * psz)
   {

      return "";

   }


   ::payload database::get_insert_id()
   {

      return -1;

   }


} //   namespace simpledb



