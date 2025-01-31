#pragma once


namespace database
{


   class dataset;
   class transaction;


   class CLASS_DECL_AXIS database :
      virtual public ::object
   {
   public:

      friend class transaction;


      database();
      ~database() override;


   protected:

      virtual void start_transaction();
      virtual void commit_transaction();
      virtual void rollback_transaction();
   

   public:
      //virtual __pointer(class dataset) dataset() = 0;

      virtual bool isActive() = 0;


      virtual ::e_status     init() = 0;
      virtual e_connection connection_status() = 0;
      virtual ::e_status     set_error_code(int iErrorCode) = 0;
      virtual string get_error_message() = 0;
      virtual void * get_handle() = 0;


      virtual ::e_status     connect(
      const ::string & name,
      const ::string & host = nullptr,
      const ::string & port = nullptr,
      const ::string & user = nullptr,
      const ::string & pass = nullptr,
      const ::string & sckt = nullptr,
      u64 uConnectionFlags = 0) = 0;

      virtual ::e_status     _connect() = 0;

      virtual void disconnect();
      virtual ::e_status     reset() = 0;
      virtual ::e_status     create() = 0;
      virtual ::e_status     drop() = 0;

      //virtual string escape(const ::string & psz);

      virtual  __pointer(class transaction) transaction();

      virtual ::count get_affected_rows_count() = 0;

      virtual bool in_transaction() = 0;


      virtual bool exec(const ::string & pszQuery) = 0;


      virtual __pointer(result_set) query_result(const ::string & pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) = 0;
      virtual __pointer(result_set)  query(const ::string & pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);


      //virtual ::payload query(const ::string & pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      virtual ::payload query_table_item(const ::string & table, const ::string & item, const ::string & where, const ::payload & payload = ::payload());
      virtual __pointer(row_array) query_rows(const ::string & pszQuery);
      virtual __pointer(row) query_row(const ::string & pszQuery);
      virtual __pointer(payload_array) query_items(const ::string & pszQuery);
      virtual ::payload query_item(const ::string & pszQuery, const ::payload & payloadDefault = ::payload());
      //virtual bool query_blob(get_memory getmemory, const ::string & pszQuery);


      virtual bool query_table_item(::payload& payload, const ::string & table, const ::string & item, const ::string & where);


      virtual bool query_rows(__pointer(row_array)& rows, const ::string & pszQuery);
      virtual bool query_row(__pointer(row)& rows, const ::string & pszQuery);
      virtual bool query_items(__pointer(payload_array)& items, const ::string & pszQuery);
      virtual bool query_item(::payload& item, const ::string & pszQuery);
      virtual bool query_blob(get_memory getmemory, const ::string & pszQuery);



      virtual ::payload get_agent(const ::string & pszTable, const ::string & psz, const ::string & pszUser) = 0;


      virtual string escape(const ::string & psz) = 0;

      virtual string add_error_message(const ::string& strErrorMessage);


      virtual string error1(const ::string & strPrefix = nullptr) = 0;
      virtual void trace_error1(const ::string & strPrefix = nullptr) = 0;

      virtual ::payload get_insert_id() = 0;

      virtual ::e_status set_id_blob(string strKey, ::block block);
      virtual ::e_status get_id_blob(string strKey, ::get_memory getmemory);



   };


} // namespace database



