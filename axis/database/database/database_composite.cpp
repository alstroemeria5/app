#include "framework.h"


namespace database
{


   composite::composite()
   {


   }

   composite::~composite()
   {

   }


   ::e_status composite::connect(const char* name, const char* host, const char* port, const char* user, const char* pass, const char* sckt, u64 uConnectionFlags)
   {

      return m_pdatabase->connect(name, host, port, user, pass, sckt, uConnectionFlags);

   }



   ::e_status   composite::_connect()
   {

      return m_pdatabase->_connect();

   }

   void composite::disconnect()
   {

      m_pdatabase->disconnect();

   }


   ::e_status   composite::reset()
   {

      return m_pdatabase->reset();

   }


   ::e_status   composite::create()
   {

      return m_pdatabase->create();

   }


   ::e_status   composite::drop()
   {

      return m_pdatabase->drop();

   }



   bool composite::exec(const char* pszQuery)
   {

      return false;

   }


   //::payload composite::query(const char * pszQuery, ::count iMaxRowCount, ::count iMaxColumnCount)
   //{

   //   return query_rows(pszQuery);

   //}


   string composite::escape(const char* psz)
   {

      return psz;

   }


   ::count composite::get_affected_rows_count()
   {

      return -1;

   }


   string composite::error1(const char* pszPrefix)
   {

      return m_pdatabase->error1(pszPrefix);

   }


   void composite::trace_error1(const char* pszPrefix)
   {

      m_pdatabase->trace_error1(pszPrefix);

   }


   ::e_status     composite::init()
   {

      return m_pdatabase->init();

   }


   ::e_status     composite::set_error_code(int iErrorCode)
   {

      return m_pdatabase->set_error_code(iErrorCode);

   }


   string composite::get_error_message()
   {

      return m_pdatabase->get_error_message();

   }


   ::payload composite::get_agent(const char* pszTable, const char* psz, const char* pszUser)
   {

      return ::payload(::e_type_null);

   }


   
   bool composite::query_table_item(::payload& payload, const char* table, const char* item, const char* where)
   {

      return m_pdatabase->query_table_item(payload, table, item, where);

   }

   



   bool composite::query_rows(__pointer(row_array) & prowaray, const char* pszQuery)
   {

      return m_pdatabase->query_rows(prowaray, pszQuery);

   }


   bool composite::query_row(__pointer(row) & prow, const char* pszQuery)
   {

      return m_pdatabase->query_row(prow, pszQuery);

   }


   bool composite::query_items(__pointer(var_array) & pvara, const char* pszQuery)
   {

      return m_pdatabase->query_items(pvara, pszQuery);

   }


   bool composite::query_item(::payload & payload, const char* pszQuery)
   {

      return m_pdatabase->query_item(payload, pszQuery);

   }


   bool composite::memory_query_item(get_memory getmemory, const char* pszQuery)
   {

      return m_pdatabase->memory_query_item(getmemory, pszQuery);

   }

   __pointer(::database::result_set) composite::query_result(const char* pszQuery, ::count iRowCount, ::count iColumnCount)
   {

      return m_pdatabase->query_result(pszQuery, iRowCount, iColumnCount);

   }

   
   ::payload composite::get_insert_id()
   {

      return ::payload();

   }


} // namespace database



