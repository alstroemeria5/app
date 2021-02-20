#pragma once





inline byte clampAndConvert(double v)
{


   if (v < 0)
      return 0;
   if (v > 255)
      return 255;
   return (byte)(v);


}







typedef struct tagWINRGBQUAD {
   byte    rgbBlue;
   byte    rgbGreen;
   byte    rgbRed;
   byte    rgbReserved;
} WINRGBQUAD, * LPWINRGBQUAD;


#include "_const.h"


#include "_system_color.h"


#include "opacity.h"


#include "color.h"


#include "colorref_array.h"





CLASS_DECL_ACME string os_font_name(enum_font efont);
CLASS_DECL_ACME string os_font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont);
CLASS_DECL_ACME string linux_font_name(enum_linux_distribution elinuxdistribution, enum_font efont);




template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using colorrefmap = map < color32_t, VALUE, typename argument_of < color32_t >::type, ARG_VALUE >;


using colorref_set = isoset < color32_t >;




