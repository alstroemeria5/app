#pragma once



template < typename ITERABLE >
inline ::count __iterable_count(const ITERABLE & iterable);


//#ifdef _UWP
//
//
//template < typename T >
//inline ::count __iterable_count(::winrt::Windows::Foundation::Collections::IVectorView < T > ^ a)
//{
//
//   return a.Size;
//
//}
//
//
//
//
//#endif


class strid_array;


CLASS_DECL_ACME bool safe_destroy_element(matter * pobject);

CLASS_DECL_ACME bool safe_free_memory(void * ptype);







template<class TYPE>
inline void CopyElements(TYPE * pDest, const TYPE * pSrc, ::count nCount);


template<class TYPE>
inline void dump_elements(dump_context & dumpcontext, const TYPE * pElements, ::count nCount);


template<class TYPE, class ARG_TYPE>
bool CompareElements(const TYPE * pElement1, const ARG_TYPE pElement2)
{

   ENSURE(pElement1 != nullptr && pElement2 != nullptr);
   ASSERT(__is_valid_address(pElement1, sizeof(TYPE), false));
   ASSERT(__is_valid_address(pElement2, sizeof(ARG_TYPE), false));

   return *pElement1 == *pElement2;

}


#define _TYPELIB_INDEX_LENGTH 10
#define _QUOTES_SPACE 2


#define forall(set) for(auto item : set)
#define forallref(set) for(auto & item : set)




#include "single.h"

#include "pair.h"


// Range-based for loop support // Thank you PUGIXML
template < typename CONST_ITERATOR >
class const_range
{
public:

   typedef CONST_ITERATOR const_iterator;

   CONST_ITERATOR m_begin;
   CONST_ITERATOR m_end;

   const_range(CONST_ITERATOR b,CONST_ITERATOR e): m_begin(b),m_end(e) {}

   CONST_ITERATOR begin() const { return m_begin; }
   CONST_ITERATOR end() const { return m_end; }


   auto & element_at(::index iIndex)
   {

      CONST_ITERATOR it = begin();

      while(iIndex > 0 && it != end())
      {

         iIndex--;

      }

      if(iIndex != 0)
      {

         __throw(error_invalid_argument);

      }

      return (*it);

   }
};


// Range-based for loop support // Thank you PUGIXML
template < typename ITERATOR >
class range
{
public:


   typedef ITERATOR const_iterator;


   ITERATOR m_begin;
   ITERATOR m_end;

   range(ITERATOR b,ITERATOR e): m_begin(b),m_end(e) { }

   ITERATOR begin() const { return m_begin; }
   ITERATOR end() const { return m_end; }

   auto & element_at(::index iIndex)
   {

      ITERATOR it = begin();

      while(iIndex > 0 && it != end())
      {

         iIndex--;

      }

      if(iIndex != 0)
      {

         __throw(error_invalid_argument);

      }

      return (*it);

   }

};


//#include "comparable_eq_array.h"
//#include "comparable_array.h"
#include "comparable_raw_array.h"
#include "comparable_array.h"


//#include "primitive_array.h"
#include "numeric_array_range.h"
#include "numeric_array.h"

#include "logic_array.h"

#include "list.h"
#include "comparable_eq_list.h"
#include "comparable_list.h"


#include "map_association.h"


#include "set.h"


#include "map.h"


#include "attrib_map.h"
#include "int_map.h"
#include "string_map.h"
#include "strid_map.h"
#include "map_to_smart_pointer.h"
#include "fifo_map.h"
#include "sort_map.h"


#include "sort_array.h"


/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//matter

// Lists
class pointer_list;             // list of void *
class object_list;              // list of matter*

//   // Maps (aka Dictionaries)
//   class CMapWordToOb;         // map from ::u16 to matter*
//   class CMapWordToPtr;        // map from ::u16 to void *
//   class CMapPtrToWord;        // map from void * to ::u16
//   class map_ptr_to_ptr;         // map from void * to void *
//
//   // Special string variants
//   class string_list;          // list of Strings
//   class CMapStringToPtr;      // map from string to void *
//   class CMapStringToOb;       // map from string to matter*
////   class string_to_string;   // map from string to string




#include "string_list.h"


using map_u16_to_ptr = map < ::u16, ::u16, void *, void * >;

using map_ptr_to_u16 = map < void *, void *, ::u16, ::u16 >;

using map_ptr_to_ptr = map < void *, void *, void *, void * >;

using map_word_to_ob = map < ::u16, ::u16, matter *, matter * >;

using map_string_to_ptr = map < string, const string &, void *, void * >;

using map_string_to_ob = map < string, const string &, matter *, matter * >;


#include "string_to_string_map.h"
#include "bit_array.h"
#include "string_array_base.h"


template < typename TYPE >
inline const char * ___type_c_str()
{

   auto pszType = typeid(TYPE).name();

   return pszType;

}



template < typename TYPE >
inline string ___type_str()
{

   string strType = typeid(TYPE).name();

   ::demangle(strType);

   return strType;

}

#define __type_str(TYPE) ::___type_str < TYPE >()

#define __type_c_str(TYPE) ::___type_c_str < TYPE >()


#include "acme/graphics/draw2d/_const.h"


#include "acme/graphics/draw2d/opacity.h"


#include "acme/graphics/draw2d/color.h"


#include "acme/primitive/primitive/payload.h"


#include "payload_array.h"
#include "acme/primitive/primitive/property.h"



//#include "acme/message/_.h"
#include "acme/primitive/primitive/property_set.h"


typedef CLASS_DECL_ACME __pointer_array(u32_array) dword_2darray;
typedef CLASS_DECL_ACME __pointer_array(index_array) index_2darray;


#include "acme/primitive/geometry2d/point_array.h"
#include "acme/primitive/geometry2d/size_array.h"
#include "acme/primitive/geometry2d/rectangle_array.h"


#include "acme/primitive/geometry2d/polygon.h"



#include "acme/primitive/comparison/less.h"


#include "sort.h"

//#include "id_array.h"

#include "bitset.h"

#include "packset.h"

#include "spreadset.h"

#include "deque.h"

#include "queue.h"

#include "priority_queue.h"

class CLASS_DECL_ACME time_array :
   public array < ::datetime::time, ::datetime::time & >
{
};


#include "stringl.h"
//#include "string_sort_array.h"
//#include "string_array.h"

#include "_papaya_array.h"







#include "unique_array.h"

#include "stack.h"

#include "set_element.h"

#include "set.h"

//#include "runnable_array.h"

#include "base_2array.h"


#include "acme/primitive/primitive/property_set_papaya.h"



