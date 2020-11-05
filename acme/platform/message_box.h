#pragma once


class CLASS_DECL_ACME message_box
{
public:


   __pointer(::layered)             m_puserprimitive;
   string                           m_strMessage;
   string                           m_strTitle;
   ::emessagebox                    m_emessagebox;
   ::duration                       m_durationTimeout;
   futurevar                        m_future;


   message_box();
   message_box(const var & var);
   virtual ~message_box();


   //::estatus show(::matter* pobject);


};




inline var operator + (var var, const ::enum_message_box& emessagebox)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["flags"] = (::i64) emessagebox;

   return var;

}


template < typename TYPE_CHAR >
inline var operator +(const string_base < TYPE_CHAR >& str, const enum_message_box& e)
{

   return var(str) + e;

}




inline var operator + (const char* psz, const ::enum_message_box& emessagebox)
{

   return var(psz) + emessagebox;

}


CLASS_DECL_ACME ::estatus os_message_box(const char* pszText, const char* pszTitle = nullptr, ::emessagebox emessagebox = message_box_ok, const ::future & future = ::future());



