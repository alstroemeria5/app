#include "framework.h"
#include "internal.h"
#include "oswindow_data.h"


#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>


bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);

bool macos1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);

//device_context::device_context()
//:
///*  m_colour(wxColourDisplay())
// , m_ok(true)
// , m_clipping(false)
// , m_isInteractive(0)
// , m_isBBoxValid(false)
// , */ m_logicalOriginX(0), m_logicalOriginY(0)
//, m_deviceOriginX(0), m_deviceOriginY(0)
//, m_logicalScaleX(1.0), m_logicalScaleY(1.0)
//, m_userScaleX(1.0), m_userScaleY(1.0)
//, m_scaleX(1.0), m_scaleY(1.0)
//, m_signX(1), m_signY(1)
//, m_minX(0), m_minY(0), m_maxX(0), m_maxY(0)
//, m_clipX1(0), m_clipY1(0), m_clipX2(0), m_clipY2(0)
///*  , m_logicalFunction(wxCOPY)
// , m_backgroundMode(wxTRANSPARENT)
// , m_mappingMode(wxMM_TEXT)
// , m_pen() */
///* , m_brush()
// , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
// , m_textForegroundColour(*wxBLACK)
// , m_textBackgroundColour(*wxWHITE)
// , m_font()
// #if wxUSE_PALETTE
// , m_palette()
// , m_hasCustomPalette(false)
// #endif // wxUSE_PALETTE */
//{
//    m_cgcontext = nullptr;
//}

//
//
//CGColorRef cg_create_color(COLORREF cr)
//{
//
//   // Create a color and add it as an attribute to the string.
//   CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
//   CGFloat components[] = { colorref_get_r_value(cr) / 255.0,
//                            colorref_get_g_value(cr) / 255.0,
//                            colorref_get_b_value(cr) / 255.0,
//                            colorref_get_a_value(cr) / 255.0
//                          };
//
//   CGColorRef color = CGColorCreate(rgbColorSpace, components);
//
//   CGColorSpaceRelease(rgbColorSpace);
//
//   return color;
//}
//
//
//WINBOOL cg_release_color(CGColorRef colorref)
//{
//   CGColorRelease(colorref);
//   return TRUE;
//}
//



//
//HFONT CreateFontIndirect(const LOGFONT * lf)
//{
//   return nullptr;
//}
//HPEN CreatePen(int iPenStyle, int iWidth, COLORREF crColor)
//{
//   return nullptr;
//}
//HGDIOBJ GetStockObject(int iStockObject)
//{
//   return nullptr;
//}
//WINBOOL SelectObject(HDC hdc, HGDIOBJ hgdiobj)
//{
//   return FALSE;
//}
//WINBOOL Rectangle(HDC hdc, int x1, int y1, int x2, int y2)
//{
//   return FALSE;
//}
//WINBOOL DeleteObject(HGDIOBJ hgdiobj)
//{
//   return FALSE;
//}
//HDC CreateCompatibleDC(HDC hdc)
//{
//   return nullptr;
//}
//HBITMAP WINAPI CreateDIBSection(HDC hdc, int cx, int cy, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset)
//{
//   return nullptr;
//}
//WINBOOL SetBkMode(HDC hdc, int iMode)
//{
//   return FALSE;
//}
//WINBOOL DeleteDC(HDC hdc)
//{
//   return FALSE;
//}
//WINBOOL AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn)
//{
//   return FALSE;
//}
//WINBOOL GetObject(HGDIOBJ hgdiobj, int iSize, void * object)
//{
//   return FALSE;
//}
//WINBOOL GetTextExtentPoint(HDC hdc, const char * pszText, int iSize, SIZE * psize)
//{
//   return FALSE;
//}
//
//

//WINBOOL SetTextColor(HDC hdc, COLORREF crText)
//{
//
//   cg_release_color(hdc->m_cgcolorrefText);
//   hdc->m_cgcolorrefText = cg_create_color(crText);
//   return TRUE;
//}

HBRUSH CreateSolidBrush(COLORREF cr)
{
   return nullptr;
}



//
//
//CTFontDescriptorRef CreateFontDescriptorFromName(CFStringRef iPostScriptName, CGFloat iSize)
//{
//   assert(iPostScriptName != nullptr);
//   return CTFontDescriptorCreateWithNameAndSize(iPostScriptName, iSize);
//}
//
//
//CTFontDescriptorRef CreateFontDescriptorFromFamilyAndTraits(CFStringRef iFamilyName, CTFontSymbolicTraits iTraits, CGFloat iSize)
//{
//
//   CTFontDescriptorRef descriptor = nullptr;
//   CFMutableDictionaryRef attributes;
//   assert(iFamilyName != nullptr);
//
//   // Create a mutable dictionary to hold our attributes.
//   attributes = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
////   __Check(attributes != nullptr);
//
//   if (attributes != nullptr)
//   {
//
//      CFMutableDictionaryRef traits;
//
//      CFNumberRef symTraits;
//
//      // add a family name to our attributes.
//      CFDictionaryAddValue(attributes, kCTFontFamilyNameAttribute, iFamilyName);
//
//      // Create the traits dictionary.
//      symTraits = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &iTraits);
//
//      ASSERT(symTraits != nullptr);
//
//      if (symTraits != nullptr)
//      {
//         // Create a dictionary to hold our traits values.
//         traits = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
////         __Check(traits != nullptr);
//
//         if (traits != nullptr)
//         {
//
//            // add the symbolic traits value to the traits dictionary.
//            CFDictionaryAddValue(traits, kCTFontSymbolicTrait, symTraits);
//
//            // add the traits attribute to our attributes.
//            CFDictionaryAddValue(attributes, kCTFontTraitsAttribute, traits);
//
//            CFRelease(traits);
//
//         }
//
//         CFRelease(symTraits);
//
//      }
//
//      // Create the font descriptor with our attributes and input size.
//      descriptor = CTFontDescriptorCreateWithAttributes(attributes);
//
////      __Check(descriptor != nullptr);
//
//      CFRelease(attributes);
//
//   }
//
//   // Return our font descriptor.
//   return descriptor;
//
//}
//
//
//CTFontRef CreateFont(CTFontDescriptorRef iFontDescriptor, CGFloat iSize)
//{
//
////   __Check(iFontDescriptor != nullptr);
//
//   // Create the font from the font descriptor and input size. Pass
//   // nullptr for the matrix parameter to use the default matrix (identity).
//   return CTFontCreateWithFontDescriptor(iFontDescriptor, iSize, nullptr);
//
//}
//
//
//CTFontRef CreateBoldFont(CTFontRef iFont, Boolean iMakeBold)
//{
//
//   CTFontSymbolicTraits desiredTrait = 0;
//
//   CTFontSymbolicTraits traitMask;
//
//   // If we are trying to make the font bold, set the desired trait
//   // to be bold.
//   if (iMakeBold)
//      desiredTrait = kCTFontBoldTrait;
//
//   // Mask off the bold trait to indicate that it is the only trait
//   // desired to be modified. As CTFontSymbolicTraits is a bit field,
//   // we could choose to change multiple traits if we desired.
//   traitMask = kCTFontBoldTrait;
//
//   // Create a copy of the original font with the masked trait set to the
//   // desired value. If the font family does not have the appropriate style,
//   // this will return nullptr.
//
//   return CTFontCreateCopyWithSymbolicTraits(iFont, 0.0, nullptr, desiredTrait, traitMask);
//
//}
//
//
//CTFontRef CreateFontConvertedToFamily(CTFontRef iFont, CFStringRef iFamily)
//{
//
//   // Create a copy of the original font with the new family. This call
//   // attempts to preserve traits, and may return nullptr if that is not possible.
//   // Pass in 0.0 and nullptr for size and matrix to preserve the values from
//   // the original font.
//   return CTFontCreateCopyWithFamily(iFont, 0.0, nullptr, iFamily);
//
//}

//
//bool TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
//{
//
//   CGContextRef context = hdc->m_cgcontext;
//
//
//   CGContextSetTextMatrix(context, CGAffineTransformIdentity);
//
//
//   // Initialize an attributed string.
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszUtf8, kCFStringEncodingUTF8);
//   CTFontRef      ctfontrefText     = hdc->m_ctfontref;
//   CGColorRef     cgcolorrefText    = hdc->m_cgcolorrefText;
//
//
//
//   // Initialize string, font, and context
//   CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
//   CFTypeRef values[] = { ctfontrefText, cgcolorrefText };
//   CFDictionaryRef attributes = CFDictionaryCreate(
//                      kCFAllocatorDefault, (const void**)&keys,
//                      (const void**)&values, sizeof(keys) / sizeof(keys[0]),
//                      &kCFTypeDictionaryKeyCallBacks,
//                      &kCFTypeDictionaryValueCallBacks);
//
//
////   CFIndex iLen = CFStringGetLength(string);
//
//
//   CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
//
//   CFRelease(attributes);
//
//
//
////   CFAttributedStringSetAttribute(attrString, CFRangeMake(0, iLen), (CFStringRef) , (CFTypeRef) textcolor);
//
//
//  // CFStringGetLength
//
//   CTLineRef line = CTLineCreateWithAttributedString(attrString);
//
//
//
//   // Set text position and draw the line into the graphics context
//
//   CGContextSetTextPosition(context, x, y);
//
//   CTLineDraw(line, context);
//
//   CFRelease(line);
//
//
//   CFRelease(attrString);
//   CFRelease(string);
//
//
//   return TRUE;
//
//
//}
//
//
//
//void FillSolidRect_dup(HDC hdc, const ::rect & rect, COLORREF clr)

//{
//   CGColorRef color = cg_create_color(clr);
//   CGRect rect;
//   rect.origin.x = prect->left;

//   rect.origin.y = prect->top;

//   rect.size.width = prect->right - prect->left;

//   rect.size.height = prect->bottom - prect->top;

//   CGContextFillRect(hdc->m_cgcontext, rect);
//   cg_release_color(color);
//}

HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam);

HFONT CreatePointBoldFont_dup(int nPointSize, const char * pszFaceName, int BOLD, HDC hdc);


//HFONT CreatePointFont_dup(int nPointSize, const char * pszFaceName, HDC hdc)
//
//{
//   return CreatePointBoldFont_dup(nPointSize, pszFaceName, FALSE, hdc);
//
//}
//
//HFONT CreatePointBoldFont_dup(int nPointSize, const char * pszFaceName, int BOLD, HDC hdc)
//
//{
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszFaceName, kCFStringEncodingUTF8);
//
//   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
//   CFRelease(string);
//   return nullptr;
//}
//
//// pLogFont->nHeight is interpreted as PointSize * 10
//HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam)
//
//{
//
//#ifdef WINDOWS
//
//   HDC hDC;
//   if (hdcParam != nullptr)
//   {
//      hDC = hdcParam;
//   }
//   else
//      hDC = ::GetDC(nullptr);
//
//   // convert nPointSize to logical units based on pgraphics
//   LOGFONT logFont = *pLogFont;
//
//   ::point point;
//   // 72 points/inch, 10 decipoints/point
//   point.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
//   point.x = 0;
//   ::DPtoLP(hDC, &point, 1);
//   const point & pointOrg = { 0, 0 };
//   ::DPtoLP(hDC, &pointOrg, 1);
//   logFont.lfHeight = -abs_dup(point.y - pointOrg.y);
//
//   if(hdcParam == nullptr)
//      ReleaseDC(nullptr, hDC);
//
//   return ::CreateFontIndirect(&logFont);
//
//#else
//
//   /*HDC hDC;
//    if (hdcParam != nullptr)
//    {
//    hDC = hdcParam;
//    }
//    else
//    hDC = ::GetDC(nullptr);*/
//
//   return ::CreateFontIndirect(pLogFont);
//
//
//   /*if(hdcParam == nullptr)
//    ReleaseDC(nullptr, hDC);*/
//
//#endif
//
//}
//
//




bool macos_get_file_image(::image * pimage, const char * psz);

CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);


//
//
//bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage)
//{
//
//   CGContextRef cgctx = CreateARGBBitmapContext(inImage, cx, cy);
//
//   if (cgctx == nullptr)
//   {
//
//      return false;
//
//   }
//
//   CGRect rect = {{0,0},{(CGFloat)cx,(CGFloat)cy}};
//
//   CGContextDrawImage(cgctx, rect, inImage);
//
//   void *data = CGBitmapContextGetData (cgctx);
//
//   u8 * pdest = (u8 * ) pcr;
//
//   if (data != nullptr)
//   {
//
//      for(int y = cy - 1; y >= 0; y--)
//      {
//
//         u8 * pline = (u8 *) &((unsigned int*)data)[y * cx];
//
//         ::memcpy_dup(pdest, pline, cx* 4);
//
//         pdest += iScan;
//
//      }
//
//   }
//
//   CGContextRelease(cgctx);
//
//   return data != nullptr;
//
//}
//
//
//CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy)
//{
//
//   CGContextRef    context = nullptr;
//
//   CGColorSpaceRef colorSpace;
//
//   void *          bitmapData;
//
//   int             bitmapByteCount;
//
//   int             bitmapBytesPerRow;
//
//   bitmapBytesPerRow   = (cx * 4);
//
//   bitmapByteCount     = (bitmapBytesPerRow * cy);
//
//   colorSpace = CGColorSpaceCreateDeviceRGB();
//
//   if (colorSpace == nullptr)
//   {
//
//      output_debug_string("CreateARGBBitmapContext: Error allocating color space\n");
//
//      return nullptr;
//
//   }
//
//   //   bitmapData = malloc( bitmapByteCount );
//   //
//   //   if (bitmapData == nullptr)
//   //   {
//   //
//   //      output_debug_string("CreateARGBBitmapContext: Memory not allocated!");
//   //
//   //      CGColorSpaceRelease( colorSpace );
//   //
//   //      return nullptr;
//   //
//   //   }
//   //
//   //   __memset(bitmapData, 0, bitmapByteCount);
//
//   // Create the bitmap context. We want pre-multiplied ARGB, 8-bits
//   // per component. Regardless of what the source image format is
//   // (CMYK, Grayscale, and so on) it will be converted over to the format
//   // specified here by CGBitmapContextCreate.
//   context =
//   CGBitmapContextCreate (
//   nullptr,
//   cx,
//   cy,
//   8,
//   bitmapBytesPerRow,
//   colorSpace,
//   kCGImageAlphaPremultipliedLast);
//
//   //   if (context == nullptr)
//   //   {
//   //
//   //      free (bitmapData);
//   //
//   //      output_debug_string("CreateARGBBitmapContext: Context not created!");
//   //
//   //   }
//
//   CGColorSpaceRelease( colorSpace );
//
//   return context;
//}
//





bool macos_get_file_image(::image * pimage, const char * psz);

CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);


bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);


#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>



// device_context::device_context()
// :
// /*  m_colour(wxColourDisplay())
//  , m_ok(true)
//  , m_clipping(false)
//  , m_isInteractive(0)
//  , m_isBBoxValid(false)
//  , */ m_logicalOriginX(0), m_logicalOriginY(0)
// , m_deviceOriginX(0), m_deviceOriginY(0)
// , m_logicalScaleX(1.0), m_logicalScaleY(1.0)
// , m_userScaleX(1.0), m_userScaleY(1.0)
// , m_scaleX(1.0), m_scaleY(1.0)
// , m_signX(1), m_signY(1)
// , m_minX(0), m_minY(0), m_maxX(0), m_maxY(0)
// , m_clipX1(0), m_clipY1(0), m_clipX2(0), m_clipY2(0)
// /*  , m_logicalFunction(wxCOPY)
//  , m_backgroundMode(wxTRANSPARENT)
//  , m_mappingMode(wxMM_TEXT)
//  , m_pen() */
// /* , m_brush()
//  , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
//  , m_textForegroundColour(*wxBLACK)
//  , m_textBackgroundColour(*wxWHITE)
//  , m_font()
//  #if wxUSE_PALETTE
//  , m_palette()
//  , m_hasCustomPalette(false)
//  #endif // wxUSE_PALETTE */
// {
//     m_cgcontext = nullptr;
// }



//CGColorRef cg_create_color(COLORREF cr)
//{
//
//   // Create a color and add it as an attribute to the string.
//   CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
//   CGFloat components[] = { colorref_get_r_value(cr) / 255.0,
//      colorref_get_g_value(cr) / 255.0,
//      colorref_get_b_value(cr) / 255.0,
//      colorref_get_a_value(cr) / 255.0};
//
//   CGColorRef color = CGColorCreate(rgbColorSpace, components);
//
//   CGColorSpaceRelease(rgbColorSpace);
//
//   return color;
//}


//WINBOOL cg_release_color(CGColorRef colorref)
//{
//   CGColorRelease(colorref);
//   return TRUE;
//}
//


// HDC GetWindowDC(oswindow hwnd)
// {
//    return GetDC(hwnd);
// }

// HDC GetDC(oswindow hwnd)
// {

//     HDC hdc = new device_context;


//     hdc->m_window = hwnd;
//     hdc->m_cgcontext = get_nswindow_cgcontext(hwnd);
// /*    hdc->m_windowPort = GetWindowPort(hwnd);
//     GetPortBounds(hdc->m_windowPort, &hdc->m_portBounds);

//     hdc->m_wasSwapped = QDSwapPort(hdc->m_windowPort, &hwnd->m_savedPort);


//     /* ... QuickDraw Drawing Commands ... */
//     // at windowPort


//   /*  QDBeginCGContext(hdc->m_windowPort, &hdc->m_cgcontext);
//     SyncCGContextOriginWithPort(hdc->m_cgcontext, hdc->m_windowPort);
//     //ClipCGContextToRegion(cgContext, &portBounds, clippingRegion);
//     //DisposeRgn(clippingRegion);
//     //clippingRegion = nullptr;

//     /* ... Quartz Drawing Commands ... */


//     hdc->m_cgcolorrefText = cg_create_color(0);
//     hdc->m_cgcolorrefBk = cg_create_color(RGB(255, 255, 255));

//     return hdc;

// }


// WINBOOL ReleaseDC(oswindow hwnd, HDC hdc)
// {

//    if(hdc == nullptr)
//       return FALSE;

//    /*QDEndCGContext(hdc->m_windowPort, &hdc->m_cgcontext);

//    if(hdc->m_wasSwapped)
//    {
//       QDSwapPort(hdc->m_savedPort, &hdc->m_savedPort);
//    }*/

//    delete hdc;
//    return TRUE;

// }


//WINBOOL get_client_rect(oswindow hwnd, RECT * prect)
//{
//   
//   /*   XWindowAttributes attrs;
//     Fill attribute structure with information about root window */
//   /* if(XGetWindowAttributes(XOpenDisplay(nullptr), hwnd, &attrs) == 0)
//    {
//    return false;
//    }
//    prect->left      = 0;
//
//    prect->top       = 0;
//
//    prect->right     = prect->left    + attrs.width;
//
//    prect->bottom    = prect->top     + attrs.height;*/
//
//   if(!get_window_rect(hwnd, prect))
//   {
//      
//      return FALSE;
//      
//   }
//
//   prect->right   -=  prect->left;
//
//   prect->bottom  -=  prect->top;
//
//   prect->left    =   0;
//
//   prect->top     =   0;
//
//   return TRUE;
//
//}


//
//WINBOOL get_window_rect(oswindow hwnd, RECT * prect)
//
//{
//   /* XWindowAttributes attrs;
//     Fill attribute structure with information about root window */
//   /*   if(XGetWindowAttributes(XOpenDisplay(nullptr), hwnd, &attrs) == 0)
//    {
//    return false;
//    }
//    prect->left      = attrs.x;
//
//    prect->top       = attrs.y;
//
//    prect->right     = prect->left    + attrs.width;
//
//    prect->bottom    = prect->top     + attrs.height;*/
//
//
//   //if(!hwnd->m_bNsWindowRect)
//   {
//
//      get_nswindow_rect(hwnd, &hwnd->m_rectNsWindow);
//
//      // hwnd->m_bNsWindowRect = true;
//
//   }
//
//   *prect = hwnd->m_rectNsWindow;
//
//
//
//   //::copy(prect, hwnd->m_pimpl->m_rectParentClient);
//
//
//   return true;
//
//
//
//}


/*
 int FillRect(HDC hdc, const ::rect & prc, HBRUSH hbr)

 {

 CGRect rect;

 rect.origin.x     = prc->left;

 rect.origin.y     = prc->top;

 rect.size.width   = prc->right - lprc->left;

 rect.size.height  = prc->bottom - lprc->top;


 CGContextSetRGBFillColor(hdc->m_cgcontext, colorref_get_r_value(hbr->lbColor), colorref_get_g_value(hbr->lbColor), colorref_get_b_value(hbr->lbColor), colorref_get_a_value(hbr->lbColor));

 CGContextFillRect(hdc->m_cgcontext, rect);

 return 1;
 }
 */

// HDC BeginPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    HDC hdc = GetDC(hwnd);

//    get_client_rect(hwnd, &ps->rcPaint);

//    return hdc;

// }


// WINBOOL EndPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    return ReleaseDC(hwnd, ps->hdc);

// }







/*int _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
 {
 return 0;
 }*/




// HFONT CreateFontIndirect(const LOGFONT * lf)
// {
//     return nullptr;
// }
// HPEN CreatePen(int iPenStyle, int iWidth, COLORREF crColor)
// {
//     return nullptr;
// }
// HGDIOBJ GetStockObject(int iStockObject)
// {
//     return nullptr;
// }
// WINBOOL SelectObject(HDC hdc, HGDIOBJ hgdiobj)
// {
//     return FALSE;
// }
// WINBOOL Rectangle(HDC hdc, int x1, int y1, int x2, int y2)
// {
//     return FALSE;
// }
// WINBOOL DeleteObject(HGDIOBJ hgdiobj)
// {
//     return FALSE;
// }
// HDC CreateCompatibleDC(HDC hdc)
// {
//     return nullptr;
// }
// HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *pbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset)

// {
//     return nullptr;
// }
// WINBOOL SetBkMode(HDC hdc, int iMode)
// {
//     return FALSE;
// }
// WINBOOL DeleteDC(HDC hdc)
// {
//     return FALSE;
// }
// WINBOOL AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn)
// {
//     return FALSE;
// }
// WINBOOL GetObject(HGDIOBJ hgdiobj, int iSize, void * object)
// {
//     return FALSE;
// }
// WINBOOL GetTextExtentPoint(HDC hdc, const char * pszText, int iSize, SIZE * psize)
// {
//     return FALSE;
// }



// WINBOOL SetTextColor(HDC hdc, COLORREF crText)
// {

//    cg_release_color(hdc->m_cgcolorrefText);
//    hdc->m_cgcolorrefText = cg_create_color(crText);
//    return TRUE;
// }

// HBRUSH CreateSolidBrush(COLORREF cr)
// {
//     return nullptr;
// }




//
//CTFontDescriptorRef CreateFontDescriptorFromName(CFStringRef iPostScriptName, CGFloat iSize)
//{
//   assert(iPostScriptName != nullptr);
//   return CTFontDescriptorCreateWithNameAndSize(iPostScriptName, iSize);
//}
//
//
//CTFontDescriptorRef CreateFontDescriptorFromFamilyAndTraits(CFStringRef iFamilyName, CTFontSymbolicTraits iTraits, CGFloat iSize)
//{
//
//   CTFontDescriptorRef descriptor = nullptr;
//   CFMutableDictionaryRef attributes;
//   assert(iFamilyName != nullptr);
//
//   // Create a mutable dictionary to hold our attributes.
//   attributes = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
//   //   __Check(attributes != nullptr);
//
//   if (attributes != nullptr)
//   {
//
//      CFMutableDictionaryRef traits;
//
//      CFNumberRef symTraits;
//
//      // add a family name to our attributes.
//      CFDictionaryAddValue(attributes, kCTFontFamilyNameAttribute, iFamilyName);
//
//      // Create the traits dictionary.
//      symTraits = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &iTraits);
//
//      (symTraits != nullptr);
//
//      if (symTraits != nullptr)
//      {
//         // Create a dictionary to hold our traits values.
//         traits = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
//         //         __Check(traits != nullptr);
//
//         if (traits != nullptr)
//         {
//
//            // add the symbolic traits value to the traits dictionary.
//            CFDictionaryAddValue(traits, kCTFontSymbolicTrait, symTraits);
//
//            // add the traits attribute to our attributes.
//            CFDictionaryAddValue(attributes, kCTFontTraitsAttribute, traits);
//
//            CFRelease(traits);
//
//         }
//
//         CFRelease(symTraits);
//
//      }
//
//      // Create the font descriptor with our attributes and input size.
//      descriptor = CTFontDescriptorCreateWithAttributes(attributes);
//
//      //      __Check(descriptor != nullptr);
//
//      CFRelease(attributes);
//
//   }
//
//   // Return our font descriptor.
//   return descriptor;
//
//}
//
//
//CTFontRef CreateFont(CTFontDescriptorRef iFontDescriptor, CGFloat iSize)
//{
//
//   //   __Check(iFontDescriptor != nullptr);
//
//   // Create the font from the font descriptor and input size. Pass
//   // nullptr for the matrix parameter to use the default matrix (identity).
//   return CTFontCreateWithFontDescriptor(iFontDescriptor, iSize, nullptr);
//
//}
//
//
//CTFontRef CreateBoldFont(CTFontRef iFont, Boolean iMakeBold)
//{
//
//   CTFontSymbolicTraits desiredTrait = 0;
//
//   CTFontSymbolicTraits traitMask;
//
//   // If we are trying to make the font bold, set the desired trait
//   // to be bold.
//   if (iMakeBold)
//      desiredTrait = kCTFontBoldTrait;
//
//   // Mask off the bold trait to indicate that it is the only trait
//   // desired to be modified. As CTFontSymbolicTraits is a bit field,
//   // we could choose to change multiple traits if we desired.
//   traitMask = kCTFontBoldTrait;
//
//   // Create a copy of the original font with the masked trait set to the
//   // desired value. If the font family does not have the appropriate style,
//   // this will return nullptr.
//
//   return CTFontCreateCopyWithSymbolicTraits(iFont, 0.0, nullptr, desiredTrait, traitMask);
//
//}
//
//
//CTFontRef CreateFontConvertedToFamily(CTFontRef iFont, CFStringRef iFamily)
//{
//
//   // Create a copy of the original font with the new family. This call
//   // attempts to preserve traits, and may return nullptr if that is not possible.
//   // Pass in 0.0 and nullptr for size and matrix to preserve the values from
//   // the original font.
//   return CTFontCreateCopyWithFamily(iFont, 0.0, nullptr, iFamily);
//
//}

// bool TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
// {

//    CGContextRef context = hdc->m_cgcontext;


//    CGContextSetTextMatrix(context, CGAffineTransformIdentity);


//    // Initialize an attributed string.
//    CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszUtf8, kCFStringEncodingUTF8);
//    CTFontRef      ctfontrefText     = hdc->m_ctfontref;
//    CGColorRef     cgcolorrefText    = hdc->m_cgcolorrefText;



//    // Initialize string, font, and context
//    CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
//    CFTypeRef values[] = { ctfontrefText, cgcolorrefText };
//    CFDictionaryRef attributes = CFDictionaryCreate(
//                       kCFAllocatorDefault, (const void**)&keys,
//                       (const void**)&values, sizeof(keys) / sizeof(keys[0]),
//                       &kCFTypeDictionaryKeyCallBacks,
//                       &kCFTypeDictionaryValueCallBacks);


// //   CFIndex iLen = CFStringGetLength(string);


//    CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);

//    CFRelease(attributes);



// //   CFAttributedStringSetAttribute(attrString, CFRangeMake(0, iLen), (CFStringRef) , (CFTypeRef) textcolor);


//   // CFStringGetLength

//    CTLineRef line = CTLineCreateWithAttributedString(attrString);



//    // Set text position and draw the line into the graphics context

//    CGContextSetTextPosition(context, x, y);

//    CTLineDraw(line, context);

//    CFRelease(line);


//    CFRelease(attrString);
//    CFRelease(string);


//    return TRUE;


// }



// void FillSolidRect_dup(HDC hdc, const ::rect & rect, COLORREF clr)

// {
//    CGColorRef color = cg_create_color(clr);
//    CGRect rect;
//    rect.origin.x = prect->left;

//    rect.origin.y = prect->top;

//    rect.size.width = prect->right - prect->left;

//    rect.size.height = prect->bottom - prect->top;

//    CGContextFillRect(hdc->m_cgcontext, rect);
//    cg_release_color(color);
// }

HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam);

HFONT CreatePointBoldFont_dup(int nPointSize, const char * pszFaceName, int BOLD, HDC hdc);


//HFONT CreatePointFont_dup(int nPointSize, const char * pszFaceName, HDC hdc)

//{
//   return CreatePointBoldFont_dup(nPointSize, pszFaceName, FALSE, hdc);

//}
//
//HFONT CreatePointBoldFont_dup(int nPointSize, const char * pszFaceName, int BOLD, HDC hdc)

//{
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszFaceName, kCFStringEncodingUTF8);

//   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
//   CFRelease(string);
//   return nullptr;
//}
//
//// pLogFont->nHeight is interpreted as PointSize * 10
//HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam)

//{
//
//   return ::CreateFontIndirect(pLogFont);

//
//}



bool macos1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{

   static ::mutex * pmutex = nullptr;

   if(pmutex == nullptr)
   {

      pmutex = new ::mutex();

   }

   sync_lock sl(pmutex);


   return mm1_get_file_image(pcr, cx, cy, iScan, psz);


}




bool macos_get_file_image(::image * pimage, const char * psz)
{

   pimage->map();

   if(!macos1_get_file_image(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), psz))
   {

      return false;

   }

   return true;

}









bool os_init_imaging()
{
   
   return true;
   
}


void os_term_imaging()
{
   
}



WINBOOL get_window_rect(oswindow hwnd, RECT * prect)

{
   /* XWindowAttributes attrs;
    Fill attribute structure with information about root window */
   /*   if(XGetWindowAttributes(XOpenDisplay(nullptr), hwnd, &attrs) == 0)
    {
    return false;
    }
    prect->left      = attrs.x;
    
    prect->top       = attrs.y;
    
    prect->right     = prect->left    + attrs.width;
    
    prect->bottom    = prect->top     + attrs.height;*/
   
   
   //if(!hwnd->m_bNsWindowRect)
   {
      
      get_nswindow_rect(hwnd, &hwnd->m_rectNsWindow);
      
      // hwnd->m_bNsWindowRect = true;
      
   }
   
   *prect = hwnd->m_rectNsWindow;
   
   
   
   //::copy(prect, hwnd->m_pimpl->m_rectParentClient);
   
   
   return true;
   
   
   
}





int_bool delete_hcursor(HCURSOR h)
{
   
   return 1;
   
}


double font_similarity(const char * pszSystem, const char * pszUser)
{

   if (::is_null(pszSystem) || ::is_null(pszUser))
   {

      return 0.0;

   }

   if (!stricmp(pszSystem, pszUser))
   {

      return 1.0;

   }

   return 0.0;
   
}


namespace draw2d
{


   string default_font_name()
   {
 
      return "Helvetica";
   
   }


} // namespace draw2d





void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image)
{

   if(image == nullptr)
   {

      return nullptr;

   }

   //https://www.raywenderlich.com/69855/image-processing-in-ios-part-1-raw-bitmap-modification
   // 1.
   width = (int) CGImageGetWidth(image);
   height = (int) CGImageGetHeight(image);

   // 2.
   long bytesPerPixel = 4;
   long bytesPerRow = bytesPerPixel * width;
   long bitsPerComponent = 8;

   UInt32 * pixels;
   pixels = (UInt32 *) calloc(height * width, sizeof(UInt32));
   
   iScan = width * sizeof(UInt32);

   // 3.
   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
   CGContextRef context = CGBitmapContextCreate(pixels, width, height, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);

   // 4.
   CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);

   // 5. Cleanup
   CGColorSpaceRelease(colorSpace);

   CGContextRelease(context);

   return pixels;

}


//HCURSOR imaging::CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot)
//{
//
//   return (HCURSOR) nullptr;
//
//}
//
//


namespace draw2d
{


   void draw2d::enum_draw2d_fonts(::draw2d::font_enum_item_array& itema)
   {


   }


} // namespace draw2d

void * nscursor_system(e_cursor ecursor);
int os_window_set_mouse_cursor(void *, void * p);

namespace aura
{


   HCURSOR application::load_default_cursor(e_cursor ecursor)
   {
      
      return nscursor_system(ecursor);
      
   }

   
   WINBOOL application::window_set_mouse_cursor(oswindow window, HCURSOR hcursor)
   {

      return os_window_set_mouse_cursor(window, hcursor);

   }


} // namespace aura



