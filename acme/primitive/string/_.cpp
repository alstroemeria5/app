#include "framework.h"
#include "acme/operating_system.h"






//CLASS_DECL_ACME string __str(const estatus & estatus)
//{
//
//   return __str((::i64) estatus.m_estatus);
//
//}


int debug_string_iterator()
{

   string str = "This is a phrase this is a link http://test.com/test_file?test_parameter=test_value";

   int iLinkLen = 0;

   int iColon = 0;

   for(auto character : str)
   {

      if (wide_char_is_alphabetic(character)
          || character == L'.'
          || character == L'/'
          || character == L'?'
          || character == L'&'
          || (character == L':' && iColon++ == 0))
      {

         iLinkLen++;

      }
      else
      {

         break;

      }

   }

   return iLinkLen;

}