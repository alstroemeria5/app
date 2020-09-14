#include "framework.h"
//#include "acme/xml/_.h"


void prop_id_debug(::generic * pobject);


//property::property(property_set * pset) :
//   m_ppropertyset(pset)
//{
//
//
//}


//property::property(const property & property) :
//   m_id(property.m_id),
//   m_var(property)
//{
//
//}


//void property::get_value(var & value)
//{
//
//   value = get_value();
//
//}


//void property::get(var & value)
//{
//
//   value = get_value();
//
//}

//var & property::get()
//{
//   return get_value();
//}
//
//void property::set(const var & var)
//{
//   set_value(var);
//}
//
//void property::unset()
//{
//   unset();
//}

//
//var property::operator + (const char * psz) const
//{
//
//   return get_value() + var(psz);
//
//}
//
//
//var property::operator + (const string & str) const
//{
//
//   return get_value() + var(str);
//
//}
//
//
//
//property & property::operator = (const property & property)
//{
//
//   if(&property != this)
//   {
//
////      m_iIndex = prop.m_iIndex;
//
//      if(m_id.is_empty())
//      {
//
//         output_debug_string("\nHI!! Shouldn't you use a generic find this by use generic and set a breakpoint here!!!\n");
//         m_id = property.m_id;
//
//      }
//
//      m_var = property;
//
//   }
//
//   return *this;
//
//}
//
//
////property::property(::index iIndex)
////{
////
////   m_iIndex = iIndex;
////
////}
////
//
////property::property(const property & property) :
////   m_ppropertyset(property.m_ppropertyset),
////   m_var(property)
////{
////
////   m_id = property.m_id;
////
////}
//
//
////property::property(property_set * pset, const id & id) :
////   m_ppropertyset(pset)
////{
////
////   m_id = id;
////
////   if (m_ppropertyset)
////   {
////
////      m_ppropertyset->find(id, m_var);
////
////   }
////
////}
//
//
////property::property(property_set * pset, const id & id, const var &  var, ::generic * pobject) :
////   m_ppropertyset(pset),
////   m_var(var)
////{
////
////   m_id = id;
////
////   if(::is_set(pobject))
////   {
////
////      ASSERT(m_pointer.is_null());
////
////      m_pointer = pobject;
////
////   }
////
////}
//
//bool property::is_set() const
//{
//   return is_set();
//}
//
//bool property::is_new() const
//{
//   return is_new();
//}
//
//bool property::is_null() const
//{
//   return is_null();
//}
//
//bool property::is_new_or_null() const
//{
//   return is_new_or_null();
//}
//
//bool property::is_empty() const
//{
//   return is_empty();
//}
//
//
//bool property::is_true() const
//{
//
//   return is_true();
//
//}
//
//
//string property::implode(const char * pszGlue) const
//{
//   return implode(pszGlue);
//}
//
//void property::parse_json(const string & str)
//{
//   const char * pszJson = str;
//   parse_json(pszJson, str.get_length());
//}
//
//void property::parse_json(const char * & pszJson, strsize length)
//{
//   parse_json(pszJson, pszJson + length - 1);
//}
//
//void property::parse_json(const char * & pszJson,const char * pszEnd)
//{
//   ::property_parse_json_id(m_id, pszJson, pszEnd);
//   ::property_parse_json_value(m_var,pszJson,pszEnd);
//}
//
//
void property_parse_json_id(id & id, const char *& pszJson, const char * pszEnd)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   char sz[1024];

   char * psz = sz;

   strsize iBuffer = sizeof(sz);

   ::str::consume_quoted_value_ex2(pszJson, pszEnd, &psz, iBuffer);

   id = psz;

   if (iBuffer > sizeof(sz))
   {

      ::memory_free(psz);

   }

}


void property_parse_json_value(::var & var, const char *& pszJson, const char * pszEnd)
{
   ::str::consume_spaces(pszJson, 0, pszEnd);
   ::str::consume(pszJson, ":", 1, pszEnd);
   var.parse_json(pszJson, pszEnd);
}


void property_skip_json_id(const char *& pszJson, const char * pszEnd)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   ::str::skip_quoted_value_ex2(pszJson, pszEnd);

}


void property_skip_json_value(const char *& pszJson, const char * pszEnd)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   ::str::consume(pszJson, ":", 1, pszEnd);

   var_skip_json(pszJson, pszEnd);

}


string & property::get_http_post(string & str) const
{

   str += m_id.str();

   str += "=";

   str += url_encode(get_string());

   return str;

}


//string_array & property::stra()
//{
//   return stra();
//}
//
//int_array & property::inta()
//{
//   return inta();
//}
//
//var_array & property::vara()
//{
//   return vara();
//}
//
//property_set & property::propset()
//{
//   return propset();
//}
//
//const string_array & property::stra() const
//{
//   return stra();
//}
//
//const int_array & property::inta() const
//{
//   return inta();
//}
//
//const var_array & property::vara() const
//{
//   return vara();
//}
//
//const property_set & property::propset() const
//{
//   return propset();
//}
//
//
//bool property::is_false() const
//{
//
//   return m_id.is_empty() && is_false();
//
//}
//
//
//bool property::is_bool_false() const
//{
//
//   return is_bool_false();
//
//}
//
//
//bool property::is_set_false() const
//{
//
//   return is_set_false();
//
//}
//
//
//strsize property::get_length() const
//{
//   return get_length();
//}
//
//void property::get_string(char * psz) const
//{
//   get_string(psz);
//}
//
//var property::element_at(index iIndex) const
//{
//   switch(m_etype)
//   {
//   case ::type_stra:
//      return const_cast<property *>(this)->stra().operator [](iIndex);
//   case ::type_inta:
//      return const_cast<property *>(this)->inta().operator [](iIndex);
//   case ::type_vara:
//      return const_cast<property *>(this)->vara().operator [](iIndex);
//   case ::type_propset:
//      return const_cast<property *>(this)->propset().at(iIndex);
//   default:
//      if(const_cast<property *>(this)->get_count() == 1)
//         return const_cast<property *>(this)->get_value();
//      __throw(::exception::exception("unsuported!!"));
//   }
//}
//
//var property::at(index iIndex) const
//{
//   return this->element_at(iIndex);
//}
//
//
////void property::io(::stream & stream)
////{
////
////   stream(m_id);
////   stream(m_var);
////
////}
//
//
//::count property::get_count() const
//{
//   return get_count();
//}
//
//::count property::array_get_count() const
//{
//   return array_get_count();
//}
//
//bool property::array_contains(const char * psz, index first, index last) const
//{
//   return array_contains(psz, first, last);
//}
//
//bool property::array_contains_ci(const char * psz, index first, index last) const
//{
//   return array_contains_ci(psz, first, last);
//}
//
//
//var property::equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const
//{
//   if(compare_value_ci(pszCompare) == 0)
//   {
//      return varOnEqual;
//   }
//   else
//   {
//      return varOnDifferent;
//   }
//}
//
//var property::equals_ci_get(const char * pszCompare, var varOnEqual) const
//{
//   if(compare_value_ci(pszCompare) == 0)
//   {
//      return varOnEqual;
//   }
//   else
//   {
//      return var();
//   }
//}
//
//
////void property::notify_changed(const ::action_context & context)
////{
////
////   auto pchannel = source_channel();
////
////   if(pchannel)
////   {
////
////      pchannel->send_update((::e_id) m_id.i64(), context);
////
////   }
////
////}
//
//
//::i32 property::compare_value_ci(const char * psz) const
//{
//   return compare_ci(psz);
//}
//
//::comparison::var_strict property::strict_compare() const
//{
//   return ((const var &)((property *) (this))->get_value());
//}
//

::i32 var::str_compare(const property & prop) const
{
   return get_string().compare(prop.get_string());
}

//
//bool property::strict_equal(const property & prop) const
//{
//   return strict_equal(prop);
//}
//
//bool property::strict_equal(const var & var) const
//{
//   return strict_equal(var);
//}
//
//bool property::strict_equal(const char * psz) const
//{
//   return strict_equal(psz);
//}
//
//bool property::strict_equal(const string & str) const
//{
//   return strict_equal(str);
//}
//
//bool property::strict_equal(double d) const
//{
//   return strict_equal(d);
//}
//
//bool property::strict_equal(::i32 i) const
//{
//   return strict_equal(i);
//}
//
//bool property::strict_equal(bool b) const
//{
//   return strict_equal(b);
//}
//
//
//bool property::strict_different(const property & prop) const
//{
//   return strict_different(const_cast < property & > (prop));
//}
//
//bool property::strict_different(const var & var) const
//{
//   return strict_different(var);
//}
//
//bool property::strict_different(const char * psz) const
//{
//   return strict_different(psz);
//}
//
//bool property::strict_different(const string & str) const
//{
//   return strict_different(str);
//}
//
//bool property::strict_different(double d) const
//{
//   return strict_different(d);
//}
//
//bool property::strict_different(::i32 i) const
//{
//   return strict_different(i);
//}
//
//bool property::strict_different(bool b) const
//{
//   return strict_different(b);
//}
//
//
//bool property::operator == (const property & prop) const
//{
//   return get_value() == prop;
//}
//
//bool property::operator == (const var & var) const
//{
//   return get_value() == var;
//}
//
//bool property::operator == (const char * psz) const
//{
//   return get_value() == psz;
//}
//
//bool property::operator == (const string & str) const
//{
//   return get_value() == str;
//}
//
//bool property::operator == (::i32 i) const
//{
//   return get_value() == i;
//}
//
//bool property::operator == (bool b) const
//{
//   return get_value() == b;
//}
//
//
//bool property::operator != (const property & prop) const
//{
//   return get_value() != prop;
//}
//
//bool property::operator != (const var & var) const
//{
//   return get_value() != var;
//}
//
//bool property::operator != (const char * psz) const
//{
//   return get_value() != psz;
//}
//
//bool property::operator != (const string & str) const
//{
//   return get_value() != str;
//}
//
//bool property::operator != (::i32 i) const
//{
//   return get_value() != i;
//}
//
//bool property::operator != (bool b) const
//{
//   return get_value() != b;
//}
//
//var property::explode(const char * pszSeparator, bool bAddEmpty) const
//{
//   return explode(pszSeparator, bAddEmpty);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//bool property::operator < (const property & prop) const
//{
//   return get_value() < prop;
//}
//
//bool property::operator < (const var & var) const
//{
//   return get_value() < var;
//}
//
//bool property::operator < (const char * psz) const
//{
//   return get_value() < psz;
//}
//
//bool property::operator < (const string & str) const
//{
//   return get_value() < str;
//}
//
//bool property::operator < (::i32 i) const
//{
//   return get_value() < i;
//}
//
//bool property::operator < (bool b) const
//{
//   return get_value() < b;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//bool property::operator <= (const property & prop) const
//{
//   return get_value() <= prop;
//}
//
//bool property::operator <= (const var & var) const
//{
//   return get_value() <= var;
//}
//
//bool property::operator <= (const char * psz) const
//{
//   return get_value() <= psz;
//}
//
//bool property::operator <= (const string & str) const
//{
//   return get_value() <= str;
//}
//
//bool property::operator <= (::i32 i) const
//{
//   return get_value() <= i;
//}
//
//bool property::operator <= (bool b) const
//{
//   return get_value() <= b;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//bool property::operator >= (const property & prop) const
//{
//   return get_value() >= prop;
//}
//
//bool property::operator >= (const var & var) const
//{
//   return get_value() >= var;
//}
//
//bool property::operator >= (const char * psz) const
//{
//   return get_value() >= psz;
//}
//
//bool property::operator >= (const string & str) const
//{
//   return get_value() >= str;
//}
//
//bool property::operator >= (::i32 i) const
//{
//   return get_value() >= i;
//}
//
//bool property::operator >= (bool b) const
//{
//   return get_value() >= b;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//bool property::operator > (const property & prop) const
//{
//   return get_value() > prop;
//}
//
//bool property::operator > (const var & var) const
//{
//   return get_value() > var;
//}
//
//bool property::operator > (const char * psz) const
//{
//   return get_value() > psz;
//}
//
//bool property::operator > (const string & str) const
//{
//   return get_value() > str;
//}
//
//bool property::operator > (::i32 i) const
//{
//   return get_value() > i;
//}
//
//bool property::operator > (bool b) const
//{
//   return get_value() > b;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//bool property::operator == (::i64 i) const
//{
//   return var::operator == (i);
//}
//bool property::operator != (::i64 i) const
//{
//   return var::operator != (i);
//}
//bool property::operator < (::i64 i) const
//{
//   return var::operator < (i);
//}
//bool property::operator <= (::i64 i) const
//{
//   return var::operator <= (i);
//}
//bool property::operator >= (::i64 i) const
//{
//   return var::operator >= (i);
//}
//bool property::operator > (::i64 i) const
//{
//   return var::operator > (i);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//var property::operator - (::i32 i) const
//{
//   return get_value() - i;
//}
//
//var property::operator - (::u32 user) const
//{
//   return get_value() - user;
//}
//
//var property::operator - (::i64 i) const
//{
//   return get_value() - i;
//}
//
//var property::operator - (::u64 user) const
//{
//   return get_value() - user;
//}
//
//var property::operator - (double d) const
//{
//   return get_value() - d;
//}
//
//var property::operator - (const var & var) const
//{
//   return get_value() - var;
//}
//
//
//
//
//var property::operator + (::i32 i) const
//{
//   return get_value() + i;
//}
//
//var property::operator + (::u32 user) const
//{
//   return get_value() + user;
//}
//
//var property::operator + (::i64 i) const
//{
//   return get_value() + i;
//}
//
//var property::operator + (::u64 user) const
//{
//   return get_value() + user;
//}
//
//var property::operator + (double d) const
//{
//   return get_value() + d;
//}
//
//var property::operator + (const var & var) const
//{
//   return get_value() + var;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//var property::operator / (::i32 i) const
//{
//   return get_value() / i;
//}
//
//var property::operator / (::u32 user) const
//{
//   return get_value() / user;
//}
//
//var property::operator / (::i64 i) const
//{
//   return get_value() / i;
//}
//
//var property::operator / (::u64 user) const
//{
//   return get_value() / user;
//}
//
//var property::operator / (double d) const
//{
//   return get_value() / d;
//}
//
//var property::operator / (const var & var) const
//{
//   return get_value() / var;
//}
//
//
//
//
//var property::operator * (::i32 i) const
//{
//   return get_value() * i;
//}
//
//var property::operator * (::u32 user) const
//{
//   return get_value() * user;
//}
//
//var property::operator * (::i64 i) const
//{
//   return get_value() * i;
//}
//
//var property::operator * (::u64 user) const
//{
//   return get_value() * user;
//}
//
//var property::operator * (double d) const
//{
//   return get_value() * d;
//}
//
//var property::operator * (const var & var) const
//{
//   return get_value() * var;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//property & property::operator -= (::i32 i)
//{
//   operator=(*this - i);
//   return *this;
//}
//
//property & property::operator -= (::u32 user)
//{
//   operator=(*this - user);
//   return *this;
//}
//
//property & property::operator -= (::i64 i)
//{
//   operator=(*this - i);
//   return *this;
//}
//
//property & property::operator -= (::u64 user)
//{
//   operator=(*this - user);
//   return *this;
//}
//
//property & property::operator -= (double d)
//{
//   operator=(*this - d);
//   return *this;
//}
//
//property & property::operator -= (const var & var)
//{
//   operator=(*this - var);
//   return *this;
//}
//
//property & property::operator -= (const property & prop)
//{
//   operator=(get_value() - prop);
//   return *this;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//property & property::operator += (::i32 i)
//{
//   operator=(*this + i);
//   return *this;
//}
//
//property & property::operator += (::u32 user)
//{
//   operator=(*this + user);
//   return *this;
//}
//
//property & property::operator += (::i64 i)
//{
//   operator=(*this + i);
//   return *this;
//}
//
//property & property::operator += (::u64 user)
//{
//   operator=(*this + user);
//   return *this;
//}
//
//property & property::operator += (double d)
//{
//   operator=(*this + d);
//   return *this;
//}
//
//property & property::operator += (const var & var)
//{
//   operator=(*this + var);
//   return *this;
//}
//
//property & property::operator += (const property & prop)
//{
//   operator=(get_value() + prop);
//   return *this;
//}
//
//property & property::operator += (const char * psz)
//{
//   operator=(*this + psz);
//   return *this;
//}
//
//property & property::operator += (const string & str)
//{
//   operator=(*this + str);
//   return *this;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//property & property::operator /= (::i32 i)
//{
//   operator=(*this / i);
//   return *this;
//}
//
//property & property::operator /= (::u32 user)
//{
//   operator=(*this / user);
//   return *this;
//}
//
//property & property::operator /= (::i64 i)
//{
//   operator=(*this / i);
//   return *this;
//}
//
//property & property::operator /= (::u64 user)
//{
//   operator=(*this / user);
//   return *this;
//}
//
//property & property::operator /= (double d)
//{
//   operator=(*this / d);
//   return *this;
//}
//
//property & property::operator /= (const var & var)
//{
//   operator=(*this / var);
//   return *this;
//}
//
//property & property::operator /= (const property & prop)
//{
//   operator=(get_value() / prop);
//   return *this;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//property & property::operator *= (::i32 i)
//{
//   operator=(*this * i);
//   return *this;
//}
//
//property & property::operator *= (::u32 user)
//{
//   operator=(*this * user);
//   return *this;
//}
//
//property & property::operator *= (::i64 i)
//{
//   operator=(*this * i);
//   return *this;
//}
//
//property & property::operator *= (::u64 user)
//{
//   operator=(*this * user);
//   return *this;
//}
//
//property & property::operator *= (double d)
//{
//   operator=(*this * d);
//   return *this;
//}
//
//property & property::operator *= (const var & var)
//{
//   operator=(*this * var);
//   return *this;
//}
//
//property & property::operator *= (const property & prop)
//{
//   operator=(get_value() * prop);
//   return *this;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////property_ptra::property_ptra(::generic * pobject):
////   ::generic(pobject)
////{
////   set_size(0, 64);
////}
//
//
//
//
////PropertySignalObject::PropertySignalObject()
////{
////}
//
//
//
//





//string property::get_xml(::xml::disp_option * opt /*= &optDefault*/ )
//{
//  //   ::text_stream ostring;
//  //   //ostring << (const char *)m_strName << "='" << (const char *)m_strValue << "' ";
//
//  //   ostring << (const char *)m_strName << L"=" << (CHAR)opt->value_quotation_mark
//  //      << (const char *)(opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue)
//  //      << (CHAR)opt->value_quotation_mark << L" ";
//  //   return ostring.str();
//
//  if(opt == ((::xml::disp_option *) 1))
//  {
//
//     opt = System.xml().m_poptionDefault;
//
//  }
//
//  string str;
//
//  str = name();
//  str += "=";
//  str += opt->m_chQuote;
//  string strValue;
//  if(opt->m_bReferenceValue && opt->m_pentities)
//     strValue = opt->m_pentities->entity_to_ref(get_string());
//  else
//     strValue = get_string();
//
//  strValue.replace("\\", "\\\\"); // should be first
//  strValue.replace("\n", "\\n");
//  strValue.replace("\t", "\\t");
//  strValue.replace("\r", "\\r");
//  strValue.replace("'", "\\'");
//  strValue.replace("\"", "\\\"");
//
//  str += strValue;
//  str += opt->m_chQuote;
//
//  return str;
//}





//
//
//
//void prop_id_debug(::generic * pobject)
//{
//
//   comparable_array < ::id > idaSchema;
//
//   property_set set;
//
//   idaSchema.add(set["prop1"]);
//
//
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//string  operator + (const string & str, const property & prop)
//{
//
//   return str +  (const var &) prop;
//
//}
//
//
string operator + (const char * psz, const property & prop)
{

   return string(psz) + (const var &)prop;

}















//
//
//var  operator - (::i32 i, const property & prop)
//{
//   return i - (const var &)prop;
//}
//
//
//var  operator - (::u32 user, const property & prop)
//{
//   return user - (const var &) prop;
//}
//
//
//var  operator - (::i64 l, const property & prop)
//{
//   return l - (const & var) prop;
//}
//
//
//var  operator - (::u64 ul, const property & prop)
//{
//   return ul - (const & var) prop;
//}
//
//
//var  operator - (double d, const property & prop)
//{
//   return d - (const & var) prop;
//}
//
//
//var  operator - (const var & var, const property & prop)
//{
//   return var - (const & var) prop;
//}


property operator - (const property & prop, const var & var)
{

   auto property = prop;

   property -= var;

   return property;

}



property operator - (const property & prop1, const property & prop2)
{

   auto property = prop1;

   property -= (const var &)prop2;

   return property;

}













//
//
//
//var  operator + (::i32 i, const property & prop)
//{
//   return i + prop;
//}
//
//
//var  operator + (::u32 user, const property & prop)
//{
//   return user + prop;
//}
//
//
//var  operator + (::i64 l, const property & prop)
//{
//   return l + prop;
//}
//
//
//var  operator + (::u64 ul, const property & prop)
//{
//   return ul + prop;
//}
//
//
//var  operator + (double d, const property & prop)
//{
//   return d + prop;
//}
//
//
//var  operator + (const var & var, const property & prop)
//{
//   return var + prop;
//}


property operator + (const property & prop, const var & var)
{

   auto property = prop;

   property += var;

   return property;

}


property operator + (const property & prop1, const property & prop2)
{

   auto property = prop1;

   property += (const var &)prop2;

   return property;

}














//
//
//
//var  operator / (::i32 i, const property & prop)
//{
//   return i / prop;
//}
//
//
//var  operator / (::u32 user, const property & prop)
//{
//   return user / prop;
//}
//
//
//var  operator / (::i64 l, const property & prop)
//{
//   return l / prop;
//}
//
//
//var  operator / (::u64 ul, const property & prop)
//{
//   return ul / prop;
//}
//
//
//var  operator / (double d, const property & prop)
//{
//   return d / prop;
//}
//
//
//var  operator / (const var & var, const property & prop)
//{
//   return var / prop;
//}


property operator / (const property & prop, const var & var)
{

   auto property = prop;

   property /= var;

   return property;

}


property operator / (const property & prop1, const property & prop2)
{

   auto property = prop1;

   property /= (const var &) prop2;

   return property;

}


//
//
//
//
//
//
//
//
//
//
//
//var  operator * (::i32 i, const property & prop)
//{
//   return i * prop;
//}
//
//
//var  operator * (::u32 user, const property & prop)
//{
//   return user * prop;
//}
//
//
//var  operator * (::i64 l, const property & prop)
//{
//   return l * prop;
//}
//
//
//var  operator * (::u64 ul, const property & prop)
//{
//   return ul * prop;
//}
//
//
//var  operator * (double d, const property & prop)
//{
//   return d * prop;
//}
//
//
//var  operator * (const var & var, const property & prop)
//{
//   return var * prop;
//}
//


property operator * (const property & prop, const var & var)
{

   auto property = prop;

   property *= var;

   return property;

}



property operator * (const property & prop1, const property & prop2)
{

   auto property = prop1;

   property *= (const var &) prop2;

   return property;

}



