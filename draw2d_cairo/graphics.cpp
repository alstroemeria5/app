#include "framework.h"
#include <math.h>

#ifdef _DEBUG
#include <freetype/freetype.h>
#endif

#define DEBUG_WINDOWS_C_ANDROID_FONTS 0


#define __expand_rgba(color) color.dr(), color.dg(), color.db(), color.da()

// https://www.codeproject.com/Articles/2293/Retrieving-Font-Name-from-TTF-File
// Philip Patrick
// Team Leader Varonis
// Israel Israel


double g_dPi = atan(1.0) * 4.0;


#if defined(LINUX)

#include <fontconfig/fontconfig.h>

#include <pango/pangocairo.h>

::mutex * g_pmutexFc = nullptr;

FcBool g_fcResult;

FcConfig * g_fcConfig;

string_to_string * g_pmapFontPath;

//#elif defined(WINDOWS)
//
//class font_fam_callback
//{
//public:
//
//   string_array                    m_stra;
//   ::write_text::font::csa        m_csa;
//
//};
//
//BOOL CALLBACK EnumFamCallBackW(LPLOGFONTW lplf, LPNEWTEXTMETRICW lpntm, ::u32 dwFontType, LPVOID p)
//{
//
//   font_fam_callback * pc = (font_fam_callback *)p;
//
//   int iType = -1;
//
//   if (dwFontType & RASTER_FONTTYPE)
//   {
//
//      iType = 0;
//
//   }
//   else if (dwFontType & TRUETYPE_FONTTYPE)
//   {
//
//      iType = 1;
//
//   }
//   else
//   {
//
//      iType = 2;
//
//   }
//
//   if (iType == 1)
//   {
//
//      if (pc->m_stra.add_unique(lplf->lfFaceName))
//      {
//
//         if (wcsicmp(lplf->lfFaceName, L"Gulim") == 0)
//         {
//            output_debug_string("Gulim");
//         }
//         pc->m_csa.add(::draw2d::wingdi_get_cs(lplf->lfCharSet));
//
//      }
//
//   }
//
//   //int far * aiFontCount = (int far *) aFontCount;
//
//   //// Record the number of raster, TrueType, and vector
//   //// fonts in the font-count array.
//
//   //if (FontType & RASTER_FONTTYPE)
//   //   aiFontCount[0]++;
//   //else if (FontType & TRUETYPE_FONTTYPE)
//   //   aiFontCount[2]++;
//   //else
//   //   aiFontCount[1]++;
//
//   //if (aiFontCount[0] || aiFontCount[1] || aiFontCount[2])
//   //   return true;
//   //else
//   //   return false;
//
//   //__UNREFERENCED_PARAMETER(lplf);
//   //__UNREFERENCED_PARAMETER(lpntm);
//
//
//   return true;
//
//}


#endif

string_map < i32_map < FT_Face > > * g_pmapFontFace = nullptr;

string_map < cairo_font_face_t * > * g_pmapCairoFontFace = nullptr;

string_to_int * g_pmapFontError = nullptr;

string_to_int * g_pmapFontError2 = nullptr;

extern CLASS_DECL_AURA array < matter * > * g_paAura;



namespace draw2d_cairo
{




FT_Face g_ft = nullptr;
int g_iFtLevel = -1;

graphics::graphics()
{

   m_pthis = this;

   m_bToyQuotedFontSelection = true;
   m_iSaveDC = 0;

#ifdef WINDOWS

   m_psurfaceAttach = nullptr;
   m_hdcAttach = nullptr;

#endif

   m_bPrinting = false;
   m_pdc = nullptr;
   m_ewritetextrendering = ::write_text::e_rendering_anti_alias_grid_fit;


   m_iSaveDCPositiveClip = -1;

   m_nStretchBltMode = ::draw2d::e_interpolation_mode_high_quality_bicubic;

}


void graphics::assert_valid() const
{

    object::assert_valid();

}


void graphics::dump(dump_context & dumpcontext) const
{

    object::dump(dumpcontext);

    dumpcontext << "\n";

}


graphics::~graphics()
{

    _synchronous_lock ml(cairo_mutex());

    if (m_pdc != nullptr)
    {

        cairo_destroy(m_pdc);

        m_pdc = nullptr;

    }

}


//bool graphics::IsPrinting()
//{
//
//    return m_bPrinting;
//
//}


//bool graphics::CreateDC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData)
//{
//
//    __throw(error_not_supported);
//
//}


//bool graphics::CreateIC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData)
//{
//
//    __throw(error_not_supported);
//
//}


   ::e_status graphics::initialize(::object * pobject)
   {

   auto estatus = ::draw2d::graphics::initialize(pobject);

   if(!estatus)
   {

      return estatus;

   }

      auto psystem = m_psystem;

      auto pnode = psystem->node();


      m_pfont.create();


      m_pfont->m_strFontFamilyName = pnode->font_name(e_font_sans);

      m_pfont->m_dFontSize = 12.0;

      return estatus;

   }




bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
{

    _synchronous_lock ml(cairo_mutex());

    if (m_pdc != nullptr)
    {

        cairo_destroy(m_pdc);

        m_pdc = nullptr;

        m_osdata[0] = nullptr;

    }

    if (pgraphics == nullptr)
    {

        cairo_surface_t * psurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);

        if (psurface == nullptr)
        {

            return false;

        }

        m_pdc = cairo_create(psurface);

        cairo_surface_destroy(psurface);

        m_osdata[0] = m_pdc;

        return m_pdc != nullptr;

    }
    else
    {

        cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphics->get_os_data());

        if (cairo_surface_status(psurface) != CAIRO_STATUS_SUCCESS)
        {

            return false;

        }

        cairo_surface_t * psurfaceNew = cairo_surface_create_similar(psurface, cairo_surface_get_content(psurface), 1, 1);

        if (psurfaceNew == nullptr)
        {

            return false;

        }

        m_pdc = cairo_create(psurfaceNew);

        cairo_surface_destroy(psurfaceNew);

        m_osdata[0] = m_pdc;

        return m_pdc != nullptr;

    }

    return true;

}


bool graphics::fill_contains(const point_f64 & point)
{


   return cairo_in_fill(m_pdc, point.x, point.y);

}


::e_status graphics::reset_clip()
{

   cairo_reset_clip(m_pdc);

   return ::success;

}


::e_status graphics::_intersect_clip()
{

   cairo_clip(m_pdc);

   return ::success;

}


::e_status graphics::_add_shape(const ::rectangle_f64 & rectangle)
{

   cairo_rectangle(m_pdc, rectangle.left + m_pointAddShapeTranslate.x, rectangle.top + m_pointAddShapeTranslate.y, rectangle.width(), rectangle.height());

   return ::success;

}


::e_status graphics::_add_shape(const ::ellipse & ellipse)
{

   cairo_keep keep(m_pdc);

   cairo_new_sub_path(m_pdc);

   cairo_translate(m_pdc, (ellipse.left + ellipse.right) / 2.0 + m_pointAddShapeTranslate.x, (ellipse.top + ellipse.bottom) / 2.0 + m_pointAddShapeTranslate.y);

   cairo_scale(m_pdc, (ellipse.right - ellipse.left) / 2.0, (ellipse.bottom - ellipse.top) / 2.0);

   cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

   return ::success;

}


::e_status graphics::_add_shape(const ::polygon_f64 & polygon_i32)
{

    if (polygon_i32.is_empty())
    {

        return ::success;

    }

    cairo_new_sub_path(m_pdc);

    cairo_move_to(m_pdc, polygon_i32[0].x + m_pointAddShapeTranslate.x, polygon_i32[0].y + m_pointAddShapeTranslate.y);

    for (i32 i = 1; i < polygon_i32.get_count(); i++)
    {

        cairo_line_to(m_pdc, polygon_i32[i].x + m_pointAddShapeTranslate.x, polygon_i32[i].y + m_pointAddShapeTranslate.y);

    }

    cairo_close_path(m_pdc);

    return ::success;

}


//i32 graphics::ExcludeUpdateRgn(::user::primitive * pwindow)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


i32 graphics::GetDevicecaps(i32 nIndex)
{

    ::exception::throw_not_implemented();

    return 0;

}


point_f64 graphics::GetBrushOrg()
{

    ::exception::throw_not_implemented();

    return ::point_f64();

}


point_f64 graphics::SetBrushOrg(double x, double y)
{

    ::exception::throw_not_implemented();

    return ::point_i32();

}


point_f64 graphics::SetBrushOrg(const ::point_f64 & point)
{

    ::exception::throw_not_implemented();

    return ::point_f64();

}

//
//i32 graphics::EnumObjects(i32 nObjectType, i32(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


::e_status graphics::set(::draw2d::bitmap* pbitmap)
{

    _synchronous_lock ml(cairo_mutex());

    if (pbitmap == nullptr)
    {

        return ::error_failed;

    }

    if (m_pdc != nullptr)
    {

        cairo_destroy(m_pdc);

        m_pdc = nullptr;

        m_osdata[0] = nullptr;

    }

    m_pdc = cairo_create((cairo_surface_t *)pbitmap->get_os_data());

    set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

    m_pbitmap = pbitmap;

    m_osdata[0] = m_pdc;

    return ::success;

}


//::draw2d_cairo::object* graphics::SelectObject(draw2d_cairo::object* pObject)
//{
//
//    return nullptr;
//
//}


//color32_t graphics::GetNearestColor(color32_t crColor)
//{
//
//    return crColor;
//
//}
//
//
//::u32 graphics::RealizePalette()
//{
//
//    return 0;
//
//}
//
//
//void graphics::UpdateColors()
//{
//
//}
//

//i32 graphics::GetPolyFillMode()
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    cairo_fill_rule_t fillrule = cairo_get_fill_rule(m_pdc);
//
//    if(fillrule == CAIRO_FILL_RULE_WINDING)
//    {
//
//        return ::draw2d::fill_mode_winding;
//
//    }
//
//    return ::draw2d::fill_mode_alternate;
//
//}


//i32 graphics::GetROP2()
//{
//
//    return 0;
//
//}


//i32 graphics::GetStretchBltMode()
//{
//
//    return 0;
//
//}
//
//
//i32 graphics::GetMapMode()
//{
//
//    return 0;
//
//}
//
//
//i32 graphics::GetGraphicsMode()
//{
//
//    return 0;
//
//}


//bool graphics::GetWorldTransform(XFORM* pXform)
//{
//
//    return 0;
//
//}


size_f64 graphics::GetViewportExt()
{

    return ::size_f64(0, 0);

}


point_f64 graphics::GetWindowOrg()
{

    return ::point_f64();

}


size_f64 graphics::GetWindowExt()
{

    return ::size_f64(0, 0);

}


// non-virtual helpers calling virtual mapping functions
point_f64 graphics::SetViewportOrg(const ::point_f64 & point)
{

   return SetViewportOrg(point.x, point.y);

}


size_f64 graphics::SetViewportExt(const ::size_f64 & size_f64)
{

    return ::size_f64(0, 0);

}


point_f64 graphics::SetWindowOrg(const ::point_f64 & point)
{

    return ::point_f64();

}


size_f64 graphics::set_window_ext(const ::size_f64 & size_f64)
{

    return ::size_f64(0, 0);

}


void graphics::DPtoLP(::point_f64 * lpPoints, count nCount)
{

}


void graphics::DPtoLP(::rectangle_f64 * prectangle)
{

}


void graphics::LPtoDP(::point_f64 * lpPoints, count nCount)
{

}


void graphics::LPtoDP(::rectangle_f64 * prectangle)
{

}


bool graphics::fill_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::frame_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush, double nWidth, double nHeight)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::invert_region(::draw2d::region* pRgn)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::paint_region(::draw2d::region* pRgn)
{

    ::exception::throw_not_implemented();

    return false;

}


//bool graphics::PtVisible(double x, double y)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//bool graphics::PtVisible(const ::point_f64 & point)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//bool graphics::RectVisible(const ::rectangle_i32 & rectangle)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


point_f64 graphics::current_position()
{

    return ::draw2d::graphics::current_position();

}


bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

   _synchronous_lock ml(cairo_mutex());

   double centerx = (x2 + x1) / 2.0;

   double centery = (y2 + y1) / 2.0;

   double radiusx = abs(x2 - x1) / 2.0;

   double radiusy = abs(y2 - y1) / 2.0;

   if (radiusx == 0.0 || radiusy == 0.0)
   {

      return false;

   }

   double start = atan2(y3 - centery, x3 - centerx);

   double end = atan2(y4 - centery, x4 - centerx);

   cairo_keep keep(m_pdc);

   cairo_translate(m_pdc, centerx, centery);

   cairo_scale(m_pdc, radiusx, radiusy);

   cairo_arc(m_pdc, 0.0, 0.0, 1.0, start, end);

   return draw();

}


bool graphics::Arc(double x, double y, double w, double h, angle start, angle extends)
{

   _synchronous_lock ml(cairo_mutex());

   double end = start + extends;

   double start_angle = start;

   double end_angle = end;

   cairo_keep keep(m_pdc);

   cairo_translate(m_pdc, x + w / 2.0, y + h / 2.0);

   cairo_scale(m_pdc, w / 2.0, h / 2.0);

   if (extends > 0)
   {

      cairo_arc(m_pdc, 0.0, 0.0, 1.0, start_angle, end_angle);

   }
   else
   {

      cairo_arc_negative(m_pdc, 0.0, 0.0, 1.0, start_angle, end_angle);

   }

   keep.restore();

   return draw();

}


bool graphics::Arc(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
{

    return Arc(
               rectangle.left,
               rectangle.top,
               rectangle.right,
               rectangle.bottom,
               pointStart.x,
               pointStart.y,
               pointEnd.x,
               pointEnd.y);

}


bool graphics::polyline(const ::point_f64* lpPoints, count nCount)
{

    return draw_polygon(lpPoints, nCount);

}


bool graphics::fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush)
{

    _synchronous_lock ml(cairo_mutex());

    if (rectangle.right <= rectangle.left || rectangle.bottom <= rectangle.top)
    {

        return false;

    }

    cairo_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);

    fill(pbrush);

    return true;

}


bool graphics::draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen)
{

    _synchronous_lock ml(cairo_mutex());

    if (rectangle.right <= rectangle.left || rectangle.bottom <= rectangle.top)
    {

        return false;

    }

    cairo_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);

    draw(ppen);

    return true;

}


bool graphics::invert_rectangle(const ::rectangle_f64 & rectangle)
{

    ::exception::throw_not_implemented();

    return false;

}


//bool graphics::DrawIcon(double x, double y, ::draw2d::icon * picon)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//bool graphics::DrawIcon(const ::point_f64 & point, ::draw2d::icon * picon)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//#ifdef WINDOWS_DESKTOP
//
//bool graphics::draw(::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags)
//{
//
//
//    try
//    {
//
//        if (picon == nullptr)
//        {
//
//            return false;
//
//        }
//
//        if (m_pdc == nullptr)
//        {
//
//            return false;
//
//        }
//
//        if (cx <= 0 || cx <= 0)
//        {
//
//            return false;
//
//        }
//
//        bool bOk = false;
//
//        BITMAPINFO info;
//
//        color32_t * pcolorref;
//
//        ZeroMemory(&info, sizeof(BITMAPINFO));
//
//        info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//        info.bmiHeader.biWidth = cx;
//        info.bmiHeader.biHeight = -cy;
//        info.bmiHeader.biPlanes = 1;
//        info.bmiHeader.biBitCount = 32;
//        info.bmiHeader.biCompression = BI_RGB;
//        info.bmiHeader.biSizeImage = cx * cy * 4;
//
//        HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **)&pcolorref, nullptr, 0);
//
//        HDC hdc = ::CreateCompatibleDC(nullptr);
//
//        HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);
//
//        if (::DrawIconEx(hdc, 0, 0, (HICON)picon->m_picon, cx, cy, istepIfAniCur, nullptr, DI_IMAGE | DI_MASK))
//        {
//
//            ::SelectObject(hdc, hbitmapOld);
//
//            try
//            {
//
//                //Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (byte *) pcolorref);
//
//                ::draw2d::bitmap_pointer b(e_create);
//
//                b->CreateBitmap(this, ::size_f64(cx, cy), 1, 32, pcolorref, cx * sizeof(color32_t));
//
//                cairo_surface_t * psurface = (cairo_surface_t *)b->get_os_data();
//
//                if (psurface == nullptr)
//                    return false;
//
//                cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);
//
//                if (ppattern == nullptr)
//                    return false;
//
//                cairo_matrix_t matrix;
//
//                cairo_matrix_t matrixOld;
//
//                cairo_keep keep(m_pdc);
//
//                cairo_translate(m_pdc, x, y);
//
//                cairo_pattern_get_matrix(ppattern, &matrixOld);
//
//                cairo_matrix_init_translate(&matrix, 0, 0);
//
//                cairo_pattern_set_matrix(ppattern, &matrix);
//
//                cairo_rectangle(m_pdc, 0, 0, cx, cy);
//
//                cairo_clip(m_pdc);
//
//                cairo_set_source(m_pdc, ppattern);
//
//                cairo_paint(m_pdc);
//
//                cairo_pattern_set_matrix(ppattern, &matrixOld);
//
//                cairo_pattern_destroy(ppattern);
//
//            }
//            catch (...)
//            {
//            }
//
//        }
//
//        ::DeleteDC(hdc);
//
//        ::DeleteObject(hbitmap);
//
//        return bOk;
//
//    }
//    catch (...)
//    {
//    }
//
//    return false;
//
//}
//
//
//#endif


//bool graphics::DrawState(const ::point_f64 & point, const ::size_f64 & size_f64, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::DrawState(const ::point_f64 & point, const ::size_f64 & size_f64, ::draw2d::bitmap* pBitmap, ::u32 nFlags, ::draw2d::brush* pBrush)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::DrawState(const ::point_f64 & point, const ::size_f64 & size_f64, const ::string & lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, HBRUSH hBrush)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::DrawState(const ::point_f64 & point, const ::size_f64 & size_f64, const ::string & lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, ::draw2d::brush* pBrush)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//bool graphics::DrawEdge(const ::rectangle_i32 & rectangle, ::u32 nEdge, ::u32 nFlags)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::DrawFrameControl(const ::rectangle_i32 & rectangle, ::u32 nType, ::u32 nState)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


bool graphics::Chord(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::Chord(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
{

    ::exception::throw_not_implemented();

    return false;

}


void graphics::DrawFocusRect(const ::rectangle_f64 & rectangle)
{

    ::exception::throw_not_implemented();

}


bool graphics::draw_ellipse(double x1, double y1, double x2, double y2)
{

   _synchronous_lock ml(cairo_mutex());

   double centerx = (x2 + x1) / 2.0;

   double centery = (y2 + y1) / 2.0;

   double radiusx = fabs(x2 - x1) / 2.0;

   double radiusy = fabs(y2 - y1) / 2.0;

   if (radiusx == 0.0 || radiusy == 0.0)
   {

      return false;

   }

   cairo_keep keep(m_pdc);

   cairo_new_sub_path(m_pdc);

   cairo_translate(m_pdc, centerx, centery);

   cairo_scale(m_pdc, radiusx - m_ppen->m_dWidth / 2.0, radiusy - m_ppen->m_dWidth / 2.0);

   cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

   keep.pulse();

   _set(m_ppen);

   cairo_stroke(m_pdc);

   return true;

}


bool graphics::draw_ellipse(const ::rectangle_f64 & rectangle)
{

    return draw_ellipse(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

}


bool graphics::fill_ellipse(double x1, double y1, double x2, double y2)
{

   _synchronous_lock ml(cairo_mutex());

   double centerx = (x2 + x1) / 2.0;

   double centery = (y2 + y1) / 2.0;

   double radiusx = fabs(x2 - x1) / 2.0;

   double radiusy = fabs(y2 - y1) / 2.0;

   if (radiusx == 0.0 || radiusy == 0.0)
   {

      return false;

   }

   cairo_keep keep(m_pdc);

   _fill1();

   cairo_new_sub_path(m_pdc);

   cairo_translate(m_pdc, centerx, centery);

   cairo_scale(m_pdc, radiusx, radiusy);

   //cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * M_PI);
   cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 6.28);

   cairo_fill(m_pdc);

   _fill2();

   return true;

}


bool graphics::fill_ellipse(const ::rectangle_f64 & rectangle)
{

    return fill_ellipse(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

}


bool graphics::Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::Pie(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::fill_polygon(const POINT_F64 * pa, count nCount)
{

    _synchronous_lock ml(cairo_mutex());

    if (nCount <= 0)
    {

        return true;

    }

    cairo_move_to(m_pdc, pa[0].x, pa[0].y);

    for (i32 i = 1; i < nCount; i++)
    {

        cairo_line_to(m_pdc, pa[i].x, pa[i].y);

    }

    fill();

    return true;

}




bool graphics::draw_polygon(const POINT_F64 * pa, count nCount)
{

    _synchronous_lock ml(cairo_mutex());

    if (nCount <= 0)
    {

        return true;

    }

    cairo_move_to(m_pdc, pa[0].x, pa[0].y);

    for (i32 i = 1; i < nCount; i++)
    {

        cairo_line_to(m_pdc, pa[i].x, pa[i].y);

    }

    draw();

    return true;

}


bool graphics::polygon(const POINT_F64 * pa, count nCount)
{

    _synchronous_lock ml(cairo_mutex());

    if (nCount <= 0)
    {

        return true;

    }

    cairo_move_to(m_pdc, pa[0].x, pa[0].y);

    for (i32 i = 1; i < nCount; i++)
    {

        cairo_line_to(m_pdc, pa[i].x, pa[i].y);

    }

    return fill_and_draw();

}



bool graphics::rectangle(const ::rectangle_f64 & rectangle)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_rectangle(m_pdc, rectangle.left, rectangle.top, ::width(rectangle), ::height(rectangle));

    return fill_and_draw();

}


bool graphics::round_rectangle(const ::rectangle_f64 & rectangle, double dRadius)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::_draw_raw(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::image_drawing_options & imagedrawingoptions, const ::point_f64 & pointSrc)
{

   _synchronous_lock ml(cairo_mutex());

   cairo_keep keep(m_pdc);

   try
   {

      if (::is_null(pimage))
      {

         return false;

      }

      auto pgraphicsSrc = pimage->get_graphics();

      if (::is_null(pgraphicsSrc))
      {

         return false;

      }

      if (pgraphicsSrc->get_os_data() == nullptr)
      {

         return false;

      }

      if (rectangleTarget.width() <= 0 || rectangleTarget.height() <= 0)
      {

         return false;

      }

      cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphicsSrc->get_os_data());

      if (psurface == nullptr)
      {

         return false;

      }

      cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

      if (ppattern == nullptr)
      {

         return false;

      }

      cairo_matrix_t matrix;

      cairo_matrix_t matrixOld;

      cairo_translate(m_pdc, rectangleTarget.left, rectangleTarget.top);

      cairo_pattern_get_matrix(ppattern, &matrixOld);

      cairo_matrix_init_translate(&matrix, pointSrc.x, pointSrc.y);

      cairo_pattern_set_matrix(ppattern, &matrix);

      cairo_rectangle(m_pdc, 0, 0, rectangleTarget.width(), rectangleTarget.height());

      cairo_clip(m_pdc);

      cairo_set_source(m_pdc, ppattern);

      if (m_ealphamode == ::draw2d::e_alpha_mode_blend)
      {

         cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);

      }
      else if (m_ealphamode == ::draw2d::e_alpha_mode_set)
      {

         cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);

      }

      auto opacity = imagedrawingoptions.opacity();

      if (m_pregion.is_set() && !m_pregion.cast < region >()->is_simple_positive_region())
      {

         if (opacity.is_translucent())
         {

            m_pregion.cast < region >()->mask_paint_with_alpha(m_pdc, opacity.get_opacity_rate());

         }
         else
         {

            m_pregion.cast < region >()->mask_paint(m_pdc);

         }

      }
      else
      {

         if (opacity.is_translucent())
         {

            cairo_paint_with_alpha(m_pdc, opacity.get_opacity_rate());

         }
         else
         {

            cairo_paint(m_pdc);

         }

      }

      cairo_pattern_set_matrix(ppattern, &matrixOld);

      cairo_pattern_destroy(ppattern);

      return true;

   }
   catch (...)
   {

      return false;

   }

}


bool graphics::_stretch_raw(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::image_drawing_options & imagedrawingoptions, const ::rectangle_f64 & rectangleSource)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_keep keep(m_pdc);

    if (::is_null(pimage))
    {

        return false;

    }

    auto pgraphicsSrc = pimage->get_graphics();

    if (::is_null(pgraphicsSrc))
    {

       return false;

    }

    auto nSrcWidth = rectangleSource.width();

    auto nSrcHeight = rectangleSource.height();

    rectangle_f64 rectFinal = rectangleTarget;

    auto nDstWidth = rectFinal.width();

    auto nDstHeight = rectFinal.height();

    auto xSrc = rectangleSource.left;

    auto ySrc = rectangleSource.top;

    auto xDst = rectFinal.left;

    auto yDst = rectFinal.top;

    if (nSrcWidth <= 0 || nSrcHeight <= 0 || nDstWidth <= 0 || nDstHeight <= 0)
    {

        return false;

    }

    if (pgraphicsSrc == nullptr || pgraphicsSrc->get_os_data() == nullptr)
    {

        return false;

    }

    cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphicsSrc->get_os_data());

    if (psurface == nullptr)
    {

        return false;

    }

    cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

    if (ppattern == nullptr)
    {

        return false;

    }

    cairo_matrix_t matrix;

    cairo_matrix_t matrixOld;

    cairo_pattern_get_matrix(ppattern, &matrixOld);

    cairo_translate(m_pdc, xDst, yDst);

    cairo_matrix_init_translate(&matrix, xSrc, ySrc);

    cairo_matrix_scale(&matrix, (double)nSrcWidth / (double)nDstWidth, (double)nSrcHeight / (double)nDstHeight);

    cairo_pattern_set_matrix(ppattern, &matrix);

    cairo_rectangle(m_pdc, 0, 0, nDstWidth, nDstHeight);

    cairo_clip(m_pdc);

    cairo_set_source(m_pdc, ppattern);

    if (m_nStretchBltMode == 0)
    {

        cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_NEAREST);

    }
    else if (m_nStretchBltMode == ::draw2d::e_interpolation_mode_high_quality_bicubic)
    {

        cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_GOOD);

    }
    else
    {

        cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_FAST);

    }

    auto opacity = imagedrawingoptions.opacity();

    if (m_pregion.is_set() && !m_pregion.cast < region >()->is_simple_positive_region())
    {

       if (opacity.is_translucent())
       {

          m_pregion.cast < region >()->mask_paint_with_alpha(m_pdc, opacity.get_opacity_rate());

       }
       else
       {

          m_pregion.cast < region >()->mask_paint(m_pdc);

       }

    }
    else
    {

       if (opacity.is_translucent())
       {

          cairo_paint_with_alpha(m_pdc, opacity.get_opacity_rate());

       }
       else
       {

          cairo_paint(m_pdc);

       }

    }
    cairo_pattern_set_matrix(ppattern, &matrixOld);

    cairo_pattern_destroy(ppattern);

    return true;

}


::color::color graphics::GetPixel(double x, double y)
{

    ::exception::throw_not_implemented();

    return false;

}


::color::color graphics::GetPixel(const ::point_f64 & point)
{

    ::exception::throw_not_implemented();

    return false;

}


::color::color graphics::SetPixel(double x, double y, const ::color::color & color)
{

    ::exception::throw_not_implemented();

    return false;

}


::color::color graphics::SetPixel(const ::point_f64 & point, const ::color::color & color)
{

    ::exception::throw_not_implemented();

    return false;

}


//bool graphics::FloodFill(double x, double y, const ::color::color & color)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::ExtFloodFill(double x, double y, const ::color::color & color, ::u32 nFillType)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


// true blend
// COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

// double blend
//// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

//
//bool graphics::text_out(double x, double y, const ::string & str)
//{
//
//    return ::draw2d::graphics::text_out(double(x), double(y), str);
//
//}


//bool graphics::ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const ::string & lpszString, strsize nCount, int * lpDxWidths)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//size_f64 graphics::TabbedTextOut(double x, double y, const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin)
//{
//
//    ::exception::throw_not_implemented();
//
//    return ::size_f64(0, 0);
//
//}
//
//
//size_f64 graphics::TabbedTextOut(double x, double y, const ::string & str, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin)
//{
//
//    ::exception::throw_not_implemented();
//
//    return ::size_f64(0, 0);
//
//}
//
//
//size_f64 graphics::GetTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions)
//{
//
//    ::exception::throw_not_implemented();
//
//    return ::size_f64(0, 0);
//
//}
//
//
//size_f64 graphics::GetTabbedTextExtent(const ::string & str, count nTabPositions, int * lpnTabStopPositions)
//{
//
//    ::exception::throw_not_implemented();
//
//    return ::size_f64(0, 0);
//
//}


size_f64 graphics::GetOutputTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions)
{

    ::exception::throw_not_implemented();

    return ::size_f64(0, 0);

}


size_f64 graphics::GetOutputTabbedTextExtent(const ::string & str, count nTabPositions, int * lpnTabStopPositions)
{

    ::exception::throw_not_implemented();

    return ::size_f64(0, 0);

}


//bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, double x, double y, double nWidth, double nHeight)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


::u32 graphics::GetTextAlign()
{

    ::exception::throw_not_implemented();

    return 0;

}


//i32 graphics::GetTextFace(count nCount, char * lpszFacename)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//i32 graphics::GetTextFace(string & rString)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


::e_status graphics::get_text_metrics(::write_text::text_metric * lpMetrics)
{

    _synchronous_lock synchronouslock(cairo_mutex());

    if(m_pfont.is_null())
    {

        return false;

    }

    if(m_pfont->m_dFontWidth <= 0.0)
    {

        return false;

    }

#if defined(USE_PANGO)

    PangoFontDescription * pdesc = (PangoFontDescription *) m_pfont->get_os_data(this);

    if(!pdesc)
    {

        return false;

    }


    PangoFontMap * pfontmap = pango_cairo_font_map_get_default ();

    PangoContext * pcontext = pango_font_map_create_context(pfontmap);

    PangoFont * pfont = pango_font_map_load_font(pfontmap, pcontext, pdesc);

    int iHeight = 0;

    PangoLayout * playout;                            // layout for a paragraph of text

    playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

    pango_layout_set_text(playout, unitext("ÁÚMGgçy"), -1);          // sets the text to be associated with the layout (final arg is length, -1
    // to calculate automatically when passing a nul-terminated string)
    pango_layout_set_font_description(playout, pdesc);            // assign the previous font description to the layout

    pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance
    // have changed, update the pango layout to reflect this
    int width = 0;

    PangoRectangle pos;

    pango_layout_get_pixel_size(playout, &width, &iHeight);

//      iHeight = pango_font_description_get_size(pdesc);
//
//      if(pango_font_description_get_size_is_absolute(pdesc))
//      {
//
//         iHeight /= PANGO_SCALE;
//
//      }
//      else
//      {
//
//         iHeight = iHeight * 1.333333333333333333 / PANGO_SCALE;
//
//      }

    PangoFontMetrics * pfontmetrics = pango_font_get_metrics(pfont, nullptr);

    lpMetrics->m_dAscent = pango_font_metrics_get_ascent(pfontmetrics) / PANGO_SCALE;

    lpMetrics->m_dDescent = pango_font_metrics_get_descent(pfontmetrics) / PANGO_SCALE;

    lpMetrics->m_dHeight = (::i32) iHeight;

    lpMetrics->m_dExternalLeading = (lpMetrics->m_dHeight - (lpMetrics->m_dAscent + lpMetrics->m_dDescent));

    lpMetrics->m_dInternalLeading = (::i32)0;

    pango_font_metrics_unref(pfontmetrics);

    g_object_unref(pcontext);

#else

   _set(m_pfont);

   cairo_font_extents_t fontextents;

   cairo_font_extents(m_pdc, &fontextents);

   lpMetrics->m_dAscent = fontextents.ascent;

   lpMetrics->m_dDescent = fontextents.descent;

   lpMetrics->m_dHeight = fontextents.height;

   lpMetrics->m_dInternalLeading = 0.;

   lpMetrics->m_dExternalLeading = 0.;

   //lpMetrics->m_dInternalLeading = lpMetrics->m_dAscent * 0.2;

   //lpMetrics->m_dExternalLeading = lpMetrics->m_dAscent * 0.2;

#endif

   return true;

}


bool graphics::get_output_text_metrics(::write_text::text_metric * lpMetrics)
{

    ::exception::throw_not_implemented();

    return false;

}


//i32 graphics::GetTextCharacterExtra()
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//u32 graphics::GetFontLanguageInfo()
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//

//size_f64 graphics::GetAspectRatioFilter()
//{
//
//    ::exception::throw_not_implemented();
//
//    return size_f64(0, 0);
//
//}
//
//
//bool graphics::ScrollDC(i32 dx, i32 dy, const ::rectangle_i32 & rectScroll, const ::rectangle_i32 & rectClip, ::draw2d::region* pRgnUpdate, RECTANGLE_I32 * lpRectUpdate)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//// Printer Escape Functions
//i32 graphics::Escape(i32 nEscape, i32 nCount, const ::string & lpszInData, LPVOID lpOutData)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


// graphics 3.1 Specific functions
::u32 graphics::SetBoundsRect(const ::rectangle_f64 & rectBounds, ::u32 flags)
{

    ::exception::throw_not_implemented();

    return 0;

}


::u32 graphics::GetBoundsRect(::rectangle_f64 * rectBounds, ::u32 flags)
{

    ::exception::throw_not_implemented();

    return 0;

}


//u32 graphics::GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
i32 graphics::StartPage()
{

    ::exception::throw_not_implemented();

    return 0;

}


i32 graphics::EndPage()
{

    ::exception::throw_not_implemented();

    return 0;

}


//i32 graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32))
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


i32 graphics::AbortDoc()
{

    ::exception::throw_not_implemented();

    return 0;

}


i32 graphics::EndDoc()
{

    ::exception::throw_not_implemented();

    return 0;

}


//bool graphics::MaskBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//bool graphics::PlgBlt(::point_f64 * lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 nXSrc, i32 nYSrc, double nWidth, double nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
//{
//
//    if (::is_null(m_pdc))
//    {
//
//        return true;
//
//    }
//
//    if(nWidth <= 0 || nHeight <= 0)
//    {
//
//        return false;
//
//    }
//
//
//
////      cairo_matrix_t matrixOld;
////
////      cairo_pattern_get_matrix(ppattern, &matrixOld);
////
////      {
////
////         cairo_matrix_t matrixSrc;
////
////         cairo_matrix_init_translate(&matrixSrc, nXSrc, nYSrc);
////
////         cairo_pattern_set_matrix(ppattern, &matrixSrc);
////
////      }
//
//    //cairo_matrix_scale(&matrixPlg, (double)dDstWidth / (double)dSrcWidth, (double)dDstHeight / (double)dSrcHeight);
//
//    cairo_matrix_t matrixShear;
//
//    double dWidth = nWidth;
//    double dHeight = nHeight;
//    double srcArea = dWidth * dHeight;
//
//    if(nWidth <= 0 || nHeight <= 0)
//    {
//
//        return false;
//
//    }
//
//
//
//    POINT_F64 plg[3];
//
//
//    plg[0].x =lpPoint[0].x;
//    plg[0].y =lpPoint[0].y;
//    plg[1].x =lpPoint[1].x;
//    plg[1].y =lpPoint[1].y;
//    plg[2].x =lpPoint[2].x;
//    plg[2].y =lpPoint[2].y;
//
//
//    /* X components */
////    xf.eM11 = (plg[1].x*(rectangle_i32[2].y - rectangle_i32[0].y) - plg[2].x*(rectangle_i32[1].y - rectangle_i32[0].y) - plg[0].x*(rectangle_i32[2].y - rectangle_i32[1].y)) / det;
////    xf.eM21 = (rectangle_i32[1].x*(plg[2].x - plg[0].x) - rectangle_i32[2].x*(plg[1].x - plg[0].x) - rectangle_i32[0].x*(plg[2].x - plg[1].x)) / det;
////    xf.eDx  = (rectangle_i32[0].x*(rectangle_i32[1].y*plg[2].x - rectangle_i32[2].y*plg[1].x) -
////               rectangle_i32[1].x*(rectangle_i32[0].y*plg[2].x - rectangle_i32[2].y*plg[0].x) +
////               rectangle_i32[2].x*(rectangle_i32[0].y*plg[1].x - rectangle_i32[1].y*plg[0].x)
////               ) / det;
////
////    xf.eM21 = (nSrcx*(plg[2].x - plg[0].x) + nWitdh(plg[2].x - plg[0].x) - nSrcX*(plg[1].x - plg[0].x) - nSrcx*(plg[2].x - plg[1].x)) / det;
////    xf.eM21 = (+ nWitdh(plg[2].x - plg[0].x)  / det;
////    xf.eDx  = (rectangle_i32[0].x*(rectangle_i32[1].y*plg[2].x - rectangle_i32[2].y*plg[1].x) -
////               rectangle_i32[1].x*(nYSrc*plg[2].x - rectangle_i32[2].y*plg[0].x) +
////               rectangle_i32[2].x*(nYSrc*plg[1].x - rectangle_i32[1].y*plg[0].x)
////               ) / det;
////    xf.eDx  = (nXSrc*(rectangle_i32[1].y*plg[2].x - rectangle_i32[2].y*plg[1].x) -
////               rectangle_i32[1].x*(nYSrc*plg[2].x - nYSrc*plg[0].x) +
////               rectangle_i32[2].x*(nYSrc*plg[1].x - nYSrc*plg[0].x)
////               ) / det;
////    xf.eDx  = (nXSrc*(nYSrc*plg[2].x - rectangle_i32[2].y*plg[1].x) -
////               rectangle_i32[1].x*(nYSrc*plg[2].x - nYSrc*plg[0].x) +
////               nXSrc*(nYSrc*plg[1].x - nYSrc*plg[0].x)
////               ) / det;
////    xf.eDx  = (nXSrc*(nYSrc*plg[2].x - (nYSrc + nHeight)*plg[1].x) -
////               (nXSrc + nWidth)*(nYSrc*plg[2].x - nYSrc*plg[0].x) +
////               nXSrc*(nYSrc*plg[1].x - nYSrc*plg[0].x)
////               ) / det;
////    xf.eDx  = (nXSrc*(nYSrc*plg[2].x - (nYSrc + nHeight)*plg[1].x) -
////               (nXSrc + nWidth)*(nYSrc*plg[2].x - nYSrc*plg[0].x) +
////               nXSrc*(nYSrc*plg[1].x - nYSrc*plg[0].x)
////               ) / det;
//    /* Y components */
////    xf.eM12 = (plg[1].y*(rectangle_i32[2].y - rectangle_i32[0].y) - plg[2].y*(rectangle_i32[1].y - rectangle_i32[0].y) - plg[0].y*(rectangle_i32[2].y - rectangle_i32[1].y)) / det;
////    xf.eM22 = (rectangle_i32[1].x*(plg[2].y - plg[0].y) - rectangle_i32[2].x*(plg[1].y - plg[0].y) - rectangle_i32[0].x*(plg[2].y - plg[1].y)) / det;
////    xf.eDy  = (rectangle_i32[0].x*(rectangle_i32[1].y*plg[2].y - rectangle_i32[2].y*plg[1].y) -
////               rectangle_i32[1].x*(rectangle_i32[0].y*plg[2].y - rectangle_i32[2].y*plg[0].y) +
////               rectangle_i32[2].x*(rectangle_i32[0].y*plg[1].y - rectangle_i32[1].y*plg[0].y)
////               ) / det;
////    xf.eM22 = (rectangle_i32[1].x*(plg[2].y - plg[0].y) - rectangle_i32[2].x*(plg[1].y - plg[0].y) - rectangle_i32[0].x*(plg[2].y - plg[1].y)) / det;
////    xf.eM22 = (nXSrc*(plg[2].y - plg[0].y)+nWidth*(plg[2].y - plg[0].y) - nXSrc*(plg[1].y - plg[0].y) - nXSrc*(plg[2].y - plg[1].y)) / det;
////    xf.eM22 = (nWidth*(plg[2].y - plg[0].y) - nXSrc*(plg[1].y ) - nXSrc*(- plg[1].y)) / det;
////    xf.eM22 = (nWidth*(plg[2].y - plg[0].y) ) / det;
//
//
//    POINT_F64 src[3];
//
//
//    src[0].x = nXSrc;
//    src[0].y = nYSrc;
//    src[1].x = nXSrc + nWidth;
//    src[1].y = nYSrc;
//    src[2].x = nXSrc;
//    src[2].y = nYSrc + nHeight;
//
//
//    //double dX = nXSrc;
//    //double dY = nYSrc;
//    double dA = nWidth * nHeight;
//    //double dX2 = nXSrc + nWidth;
//    //double dY2 = nYSrc + nHeight;
//
//
//    matrixShear.xx = (plg[1].x - plg[0].x) / dWidth;
//    matrixShear.xy = (plg[2].x - plg[0].x) / dHeight;
//    matrixShear.x0  = (src[0].x*(src[1].y*plg[2].x - src[2].y*plg[1].x) -
//                       src[1].x*(src[0].y*plg[2].x - src[2].y*plg[0].x) +
//                       src[2].x*(src[0].y*plg[1].x - src[1].y*plg[0].x)
//                      ) / dA;
//    //matrixShear.x0 = plg[0].x;
//    //matrixShear.x0 = 0;
//
//    matrixShear.yx = (plg[1].y - plg[0].y) / dWidth;
//    matrixShear.yy = (plg[2].y - plg[0].y) / dHeight;
////      matrixShear.y0  = (src[0].x*(src[1].y*plg[2].y - src[2].y*plg[1].y) -
////               src[1].x*(src[0].y*plg[2].y - src[2].y*plg[0].y) +
////               src[2].x*(src[0].y*plg[1].y - src[1].y*plg[0].y)
////               ) / dA;
//    matrixShear.y0  = (src[0].x*(src[1].y*plg[2].y - src[2].y*plg[1].y) -
//                       src[1].x*(src[0].y*plg[2].y - src[2].y*plg[0].y) +
//                       src[2].x*(src[0].y*plg[1].y - src[1].y*plg[0].y)
//                      ) / dA;
//
//    if(fabs(matrixShear.xx) <= 0.001)
//    {
//        return false;
//    }
//    if(fabs(matrixShear.yy) <= 0.001)
//    {
//        return false;
//    }
//
////               if(fabs(matrixShear.xx) <=0.001)
////               {
////               matrixShear.xx = papaya::sgn(matrixShear.xx);
////               }
////               if(fabs(matrixShear.yy) <=0.001)
////               {
////               matrixShear.yy = papaya::sgn(matrixShear.yy);
////               }
//
//
//    //matrixShear.y0 = plg[0].y;
//    //matrixShear.y0 = 0;
////
////      cairo_matrix_t matrix;
////
////      cairo_get_matrix(m_pdc, &matrix);
////
////      cairo_matrix_multiply(&matrix, &matrix, &matrixShear);
//
//    _synchronous_lock ml(cairo_mutex());
//
//    cairo_keep keep(m_pdc);
//
//    if (pgraphicsSrc == nullptr || pgraphicsSrc->get_os_data() == nullptr)
//    {
//
//        return false;
//
//    }
//
//    cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphicsSrc->get_os_data());
//
//    if (psurface == nullptr)
//    {
//
//        return false;
//
//    }
//
//    cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);
//
//    if (ppattern == nullptr)
//    {
//
//        return false;
//
//    }
//    cairo_transform(m_pdc, &matrixShear);
//
//    int cxImage = cairo_image_surface_get_width(psurface);
//
//    int cyImage = cairo_image_surface_get_height(psurface);
//
//    if(nXSrc > 0 || nYSrc > 0 || nWidth < cxImage || nHeight < cyImage)
//    {
//
//        cairo_rectangle(m_pdc, nXSrc, nYSrc, dWidth, dHeight);
//
//        cairo_clip(m_pdc);
//
//    }
//
//    cairo_set_source(m_pdc, ppattern);
//
//   if (m_nStretchBltMode == 0)
//   {
//
//      cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_NEAREST);
//
//   }
//   else if (m_nStretchBltMode == e_interpolation_mode_high_quality_bicubic)
//   {
//
//      cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_GOOD);
//
//   }
//   else
//   {
//
//      cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_FAST);
//
//   }
//
//   if (m_pregion.is_set() && !m_pregion.cast < region >()->is_simple_positive_region())
//   {
//
//      m_pregion.cast < region >()->mask(m_pdc);
//
//   }
//   else
//   {
//
//      cairo_paint(m_pdc);
//
//   }
//
//   // cairo_pattern_set_matrix(ppattern, &matrixOld);
//
//   cairo_pattern_destroy(ppattern);
//
//   return true;
//
//}


bool graphics::SetPixelV(double x, double y, const ::color::color & color)
{

   ::exception::throw_not_implemented();

   return false;

}


bool graphics::SetPixelV(const ::point_f64 & point, const ::color::color & color)
{

   ::exception::throw_not_implemented();

   return false;

}


bool graphics::AngleArc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle)
{

   ::exception::throw_not_implemented();

   return false;

}


bool graphics::ArcTo(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
{

   ::exception::throw_not_implemented();

   return false;

}


//i32 graphics::GetArcDirection()
//{
//
//   ::exception::throw_not_implemented();
//
//   return 0;
//
//}


bool graphics::poly_polyline(const ::point_f64* lpPoints, const ::i32 * lpPolyPoints, count nCount)
{

   ::exception::throw_not_implemented();

   return false;

}


//::draw2d::pen * graphics::get_current_pen()
//{
//
//   return m_ppen;
//
//}


//::draw2d::brush * graphics::get_current_brush()
//{
//
//    return m_pbrush;
//
//}


//::draw2d::palette * graphics::get_current_palette()
//{
//
//    return (::draw2d::palette *)nullptr;
//
//}


//::write_text::font * graphics::get_current_font()
//{
//
//    return m_pfont;
//
//}


//::draw2d::bitmap * graphics::get_current_bitmap()
//{
//
//    return m_pbitmap;
//
//}


bool graphics::poly_bezier(const ::point_f64* lpPoints, count nCount)
{

    ::exception::throw_not_implemented();

    return false;

}
//
//
//i32 graphics::DrawEscape(i32 nEscape, i32 nInputSize, const ::string & lpszInputData)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//i32 graphics::Escape(i32 nEscape, i32 nInputSize, const ::string & lpszInputData, i32 nOutputSize, char * lpszOutputData)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float* lpFloatBuffer)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


bool graphics::abort_path()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::begin_path()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::close_figure()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::end_path()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::fill_path()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::flatten_path()
{

    ::exception::throw_not_implemented();

    return false;

}


float graphics::GetMiterLimit()
{

    ::exception::throw_not_implemented();

    return 0.f;

}

//
//i32 graphics::GetPath(::point_f64 * lpPoints, byte * lpTypes, count nCount)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


bool graphics::SetMiterLimit(float fMiterLimit)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::stroke_and_fill_path()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::stroke_path()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::widen_path()
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::draw_path(::draw2d::path * ppath)
{

    _synchronous_lock ml(cairo_mutex());

    if (!_set(ppath))
    {

        return false;

    }

    return draw();

}


bool graphics::fill_path(::draw2d::path * ppath)
{

    _synchronous_lock ml(cairo_mutex());

    if (!_set(ppath))
    {

        return false;

    }

    return fill();

}


bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
{

    _synchronous_lock ml(cairo_mutex());

    if (!_set(ppath))
    {

        return false;

    }

    return draw(ppen);

}


bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
{

    _synchronous_lock ml(cairo_mutex());

    if (!_set(ppath))
    {

        return false;

    }

    return fill(pbrush);

}


// true blend
// COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

// double blend
// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

//// Thank you
//// Jiju George T
//// Web Developer
//// India India
//// Member
//
//bool graphics::_alpha_blend_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dRate)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    cairo_keep keep(m_pdc);
//
//    try
//    {
//
//        if (pgraphicsSrc == nullptr)
//        {
//
//            return false;
//
//        }
//
//        if (rectangleTarget.area() <= 0)
//        {
//
//            return false;
//
//        }
//
//        if (pgraphicsSrc->get_os_data() == nullptr)
//        {
//
//            return false;
//
//        }
//
//        cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphicsSrc->get_os_data());
//
//        if (psurface == nullptr)
//        {
//
//            return false;
//
//        }
//
//        cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);
//
//        if (ppattern == nullptr)
//        {
//
//            return false;
//
//        }
//
//        cairo_matrix_t matrix;
//
//        cairo_matrix_t matrixOld;
//
//        cairo_translate(m_pdc, rectangleTarget.left, rectangleTarget.right);
//
//        cairo_pattern_get_matrix(ppattern, &matrixOld);
//
//        cairo_matrix_init_translate(&matrix, rectangleSource.left, rectangleSource.top);
//
//        cairo_pattern_set_matrix(ppattern, &matrix);
//
//        cairo_rectangle(m_pdc, 0, 0, rectangleTarget.width(), rectangleTarget.height());
//
//        cairo_clip(m_pdc);
//
//        cairo_set_source(m_pdc, ppattern);
//
//        if (m_ealphamode == ::draw2d::e_alpha_mode_blend)
//        {
//
//            cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);
//
//        }
//        else if (m_ealphamode == ::draw2d::e_alpha_mode_set)
//        {
//
//            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
//
//        }
//
//        if (m_pregion.is_set() && !m_pregion.cast < region >()->is_simple_positive_region())
//        {
//
//            m_pregion.cast < region >()->mask(m_pdc);
//
//        }
//        else
//        {
//
//            cairo_paint_with_alpha(m_pdc, dRate);
//
//        }
//
//        cairo_pattern_set_matrix(ppattern, &matrixOld);
//
//        cairo_pattern_destroy(ppattern);
//
//        return true;
//
//    }
//    catch (...)
//    {
//
//        return false;
//
//    }
//
//}


//bool graphics::TransparentBlt(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight, ::u32 crTransparent)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::GradientFill(TRIVERTEX* pVertices, WINULONG nVertices, void * pMesh, WINULONG nMeshElements, u32 dwMode)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//#if (_WIN32_WINNT >= 0x0500)
//
//// Always Inline. Functions only in Win98/Win2K or later
//
//color32_t graphics::GetDCBrushColor()
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//color32_t graphics::SetDCBrushColor(color32_t crColor)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//color32_t graphics::GetDCPenColor()
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//color32_t graphics::SetDCPenColor(color32_t crColor)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//#endif
//
//
//#if (_WIN32_WINNT >= 0x0500)
//
//
//bool graphics::GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//#endif
//
//
//#if (_WIN32_WINNT >= 0x0500)
//
//
//bool graphics::GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE32 LPSIZE32)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//bool graphics::GetTextExtentPointI(LPWORD pgiIn, i32 cgi, LPSIZE32 LPSIZE32)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}
//
//
//#endif
//

/////////////////////////////////////////////////////////////////////////////
// More coordinate transforms (in separate file to avoid transitive refs)


#define HIMETRIC_INCH   2540    // HIMETRIC units per inch


void graphics::DPtoHIMETRIC(::size_f64 * psize)
{

    ::exception::throw_not_implemented();

}


void graphics::HIMETRICtoDP(::size_f64 * psize)
{

    ::exception::throw_not_implemented();

}





/////////////////////////////////////////////////////////////////////////////
// special graphics drawing primitives/helpers


//::draw2d::brush * PASCAL graphics::GetHalftoneBrush(::object * pobject)
//{
//
//    return nullptr;
//
//}


//   void graphics::DrawDragRect(const ::rectangle_i32 & rectangle, const ::size_f64 & size_f64, const ::rectangle_i32 & rectLast, const ::size_f64 & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
//   {
//
//      ::exception::throw_not_implemented();
//
//   }


bool graphics::DeleteDC()
{

    _synchronous_lock ml(cairo_mutex());

    if (m_pdc == nullptr)
    {

        return true;

    }

    cairo_destroy(m_pdc);

    m_pdc = nullptr;

    m_osdata[0] = nullptr;

    return true;

}


//i32 graphics::StartDoc(const ::string & lpszDocName)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


i32 graphics::SaveDC()
{

    _synchronous_lock synchronouslock(cairo_mutex());

    m_iSaveDC++;

    cairo_save(m_pdc);

    return m_iSaveDC;

}


bool graphics::RestoreDC(i32 nSavedDC)
{

    _synchronous_lock synchronouslock(cairo_mutex());

    bool bRestored = false;

    while (m_iSaveDC >= nSavedDC)
    {

        cairo_restore(m_pdc);

        m_iSaveDC--;

        bRestored = true;

    }

    if (m_iSaveDC < m_iSaveDCPositiveClip)
    {

        m_iSaveDCPositiveClip = -1;

    }

    return bRestored;

}


::draw2d::object * graphics::set_stock_object(i32 nIndex)
{

    return nullptr;

}


//::e_status graphics::set(::draw2d::pen* ppen)
//{
//
//   m_ppen = ppen;
//
//   return ::success;
//
//}


//::e_status graphics::set(::draw2d::brush* pbrush)
//{
//
//    m_pbrush = pbrush;
//
//    return ::success;
//
//}


//::e_status graphics::set(::write_text::font* pfont)
//{
//
//    if (!::draw2d::graphics::set(pfont))
//    {
//
//        return ::error_failed;
//
//    }
//
//    return ::success;
//
//}


::e_status graphics::set(::draw2d::region* pregion)
{

    ::exception::throw_not_implemented();

    return false;

}


//::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
//{
//
//    return nullptr;
//
//}
//

//i32 graphics::SetPolyFillMode(i32 nPolyFillMode)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//i32 graphics::SetROP2(i32 nDrawMode)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


bool graphics::set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode)
{

    if(!::draw2d::graphics::set_interpolation_mode(einterpolationmode))
    {

       return false;

    }

    return true;

}


//i32 graphics::SetGraphicsMode(i32 iMode)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


//bool graphics::SetWorldTransform(const XFORM* pXform)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//bool graphics::ModifyWorldTransform(const XFORM* pXform, u32 iMode)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//i32 graphics::SetMapMode(i32 nMapMode)
//{
//
//    return 0;
//
//}


point_f64 graphics::GetViewportOrg()
{

    return ::draw2d::graphics::GetViewportOrg();

}


point_f64 graphics::SetViewportOrg(double x, double y)
{

    return ::draw2d::graphics::SetViewportOrg(x, y);

}


point_f64 graphics::OffsetViewportOrg(double nWidth, double nHeight)
{

    return ::draw2d::graphics::OffsetViewportOrg(nWidth, nHeight);

}


size_f64 graphics::SetViewportExt(double x, double y)
{

    ::exception::throw_not_implemented();

    return ::size_f64(0, 0);

}


size_f64 graphics::ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom)
{

    return ::draw2d::graphics::ScaleViewportExt(xNum, xDenom, yNum, yDenom);

}


point_f64 graphics::SetWindowOrg(double x, double y)
{

    ::exception::throw_not_implemented();

    return ::point_i32();

}


point_f64 graphics::offset_window_org(double nWidth, double nHeight)
{

    ::exception::throw_not_implemented();

    return ::point_f64();

}


size_f64 graphics::set_window_ext(double x, double y)
{

    ::exception::throw_not_implemented();

    return ::size_f64(0, 0);

}


size_f64 graphics::scale_window_ext(double xNum, double xDenom, double yNum, double yDenom)
{

    ::exception::throw_not_implemented();

    return ::size_f64(0, 0);

}


i32 graphics::get_clip_box(::rectangle_f64 * prectangle)
{

    return 0;

}


//i32 graphics::SelectClipRgn(::draw2d::region * pregion)
//{
//
//   _synchronous_lock ml(cairo_mutex());
//
//   if (pregion == nullptr)
//   {
//
//      cairo_reset_clip(m_pdc);
//
//   }
//   else
//   {
//
//      pregion->cast < region >()->clip(m_pdc);
//
//   }
//
//   return 0;
//
//}


//i32 graphics::ExcludeClipRect(double x1, double y1, double x2, double y2)
//{
//
//    //::exception::throw_not_implemented();
//
//    return ::draw2d::graphics::ExcludeClipRect(x1, y1, x2, y2);
//
//}
//

//i32 graphics::ExcludeClipRect(const ::rectangle_i32 & rectangle)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//

//i32 graphics::IntersectClipRect(double x1, double y1, double x2, double y2)
//{
//
//   _synchronous_lock ml(cairo_mutex());
//
//   cairo_rectangle(m_pdc, x1, y1, x2 - x1, y2 - y1);
//
//   cairo_clip(m_pdc);
//
//   return 0;
//
//}


//i32 graphics::IntersectClipRect(const ::rectangle_i32 & rectangle)
//{
//
//   return IntersectClipRect(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
//
//}


//i32 graphics::OffsetClipRgn(double x, double y)
//{
//
//   return ::draw2d::graphics::OffsetClipRgn(x, y);
//
//    //::exception::throw_not_implemented();
//
//    // does cairo automatically offset clip region
//    // according to current transformation?
//
//    //return 0;
//
//}


//i32 graphics::OffsetClipRgn(const ::size_f64 & size_f64)
//{
//
//    //::exception::throw_not_implemented();
//
//    //return 0;
//
//    return ::draw2d::graphics::OffsetClipRgn(size_f64);
//
//}


//bool graphics::move_to(double x, double y)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    cairo_move_to(m_pdc, x, y);
//
//    m_point.x = x;
//
//    m_point.y = y;
//
//    return true;
//
//}


bool graphics::move_to(double x, double y)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_move_to(m_pdc, x, y);

    m_point.x = x;

    m_point.y = y;

    return true;

}


::u32 graphics::SetTextAlign(::u32 nFlags)
{

    return 0;

}


//i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
//u32 graphics::SetMapperFlags(u32 dwFlag)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}
//
//
u32 graphics::GetLayout()
{

    ::exception::throw_not_implemented();

    return 0;

}


u32 graphics::SetLayout(u32 dwSetLayout)
{

    ::exception::throw_not_implemented();

    return 0;

}


//bool graphics::ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
//{
//
//    ::exception::throw_not_implemented();
//
//    return false;
//
//}


//i32 graphics::SetArcDirection(i32 nArcDirection)
//{
//
//    ::exception::throw_not_implemented();
//
//    return 0;
//
//}


bool graphics::polydraw(const ::point_f64* lpPoints, const byte* lpTypes, count nCount)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::polyline_to(const ::point_f64* lpPoints, count nCount)
{

    ::exception::throw_not_implemented();

    return false;

}


bool graphics::poly_bezier_to(const ::point_f64* lpPoints, count nCount)
{

    ::exception::throw_not_implemented();

    return 0;

}


bool graphics::SelectClipPath(i32 nMode)
{

    ::exception::throw_not_implemented();

    return 0;

}


//i32 graphics::SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine)
//{
//
//    return SelectClipRgn(pRgn);
//
//}


void graphics::LPtoDP(::size_f64 * psize)
{

    ::exception::throw_not_implemented();

    return;

}


void graphics::DPtoLP(::size_f64 * psize)
{

    ::exception::throw_not_implemented();

    return;

}


//bool graphics::draw_text(const ::string & lpszString, strsize nCount, const ::rectangle_i32 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
//{
//
//    return draw_text(string(lpszString, nCount), rectangle, nFormat);
//
//}


#if defined(USE_PANGO)


bool graphics::draw_text(const ::string & strParam, const ::rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_keep keep(m_pdc);

    rectangle_f64 rectangle;

    __copy(rectangle, rectParam);

    return internal_draw_text(strParam, rectangle, ealign, edrawtext);

}


bool graphics::internal_draw_text(const block & block, const ::rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
{

    return internal_draw_text_pango(block, rectangle, ealign, edrawtext, &pango_cairo_show_layout);

}


bool graphics::internal_draw_text_pango(const block & block, const ::rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, PFN_PANGO_TEXT pfnPango)
{

    _synchronous_lock ml(cairo_mutex());

    if(m_pfont.is_null())
    {

        return false;

    }

    if(m_pfont->m_dFontSize <= 0.0 || m_pfont->m_dFontWidth <= 0.0)
    {

        return false;

    }

    PangoFontDescription * pdesc = (PangoFontDescription *) m_pfont->get_os_data(this);

    if(!pdesc)
    {

        return false;

    }

    ::draw2d::savedc savedc(this);

    PangoLayout * playout;                            // layout for a paragraph of text

    // drawing will start from).
    playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

    //pango_layout_set_width(playout, width(rectParam));

    //pango_layout_set_height(playout, height(rectParam));

    pango_layout_set_text(playout, (const ::string &)block.m_pdata, block.m_iSize);          // sets the text to be associated with the layout (final arg is length, -1

    pango_layout_set_font_description(playout, pdesc);            // assign the previous font description to the layout

    //pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance

    PangoRectangle rectangle;

    pango_layout_get_pixel_extents (playout, nullptr, &rectangle);

    point_f64 ptRef;

    if(ealign & e_align_bottom)
    {

        cairo_translate(m_pdc, 0, rectParam.bottom - rectangle.height);

        ptRef.y = rectParam.bottom - rectangle.height;

    }
    else if(ealign & e_align_vertical_center)
    {

        cairo_translate(m_pdc, 0, ((rectParam.top + rectParam.bottom) / 2 - (rectangle.height / 2)));

        ptRef.y = ((rectParam.top + rectParam.bottom) / 2 - (rectangle.height / 2));

    }
    else
    {

        cairo_translate(m_pdc, 0, rectParam.top);

        ptRef.y = rectParam.top;

    }

    if(ealign & e_align_right)
    {

        cairo_translate(m_pdc, rectParam.right - rectangle.width, 0);

        ptRef.x = rectParam.right - rectangle.width;

    }
    else if(ealign & e_align_horizontal_center)
    {

        cairo_translate(m_pdc, ((rectParam.left + rectParam.right) / 2) - (rectangle.width/2), 0);

        ptRef.x = ((rectParam.left + rectParam.right) / 2) - (rectangle.width/2);

    }
    else
    {

        cairo_translate(m_pdc, rectParam.left, 0);

        ptRef.x = rectParam.left;

    }

    cairo_scale(m_pdc, m_pfont->m_dFontWidth, 1.0);

   if(m_pbrush.is_set())
   {

      _set(m_pbrush, ptRef.x, ptRef.y);

   }

   pango_layout_context_changed (playout);

   pango_cairo_update_layout(m_pdc, playout);


    // have changed, update the pango layout to reflect this
    (*pfnPango)(m_pdc, playout);                    // draw the pango layout onto the cairo surface

    g_object_unref(playout);                         // free the layout

    return true;

}


#else


bool graphics::draw_text(const ::string & strParam, const ::rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
{

    return internal_draw_text(strParam, rectangle, ealign, edrawtext, &cairo_show_text);

}


bool graphics::internal_draw_text(const ::block & block, const ::rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext, PFN_CAIRO_TEXT ftext)
{

    string str((const char *) block.get_data(), block.get_size());

    str = ::str::q_valid(str);

    if (str.is_empty())
    {

        return false;

    }

    _synchronous_lock ml(cairo_mutex());

    if (m_pfont.is_null())
    {

        return false;

    }

    if (m_pfont->m_dFontWidth <= 0.0)
    {

        return false;

    }

    cairo_keep keep(m_pdc);

    _fill1();

    _set(m_pfont);

    cairo_font_extents_t e;

    cairo_font_extents(m_pdc, &e);

    size_f64 sz = get_text_extent(str);

    double dx;

    double dy;

    if (ealign & e_align_right)
    {

        dx = rectangle.right - rectangle.left - sz.cx;

    }
    else if (ealign & e_align_horizontal_center)
    {

        dx = ((rectangle.right - rectangle.left) - (sz.cx)) / 2.0;

    }
    else
    {

        dx = 0.;

    }

    if (ealign & e_align_bottom)
    {

        dy = rectangle.bottom - rectangle.top - e.ascent;

    }
    else if (ealign & e_align_vertical_center)
    {

        dy = ((rectangle.bottom - rectangle.top) - (e.ascent)) / 2.0;

    }
    else
    {

        dy = 0.;

    }

    if (m_pfont->m_dFontWidth != 1.0)
    {

        cairo_matrix_t m;

        cairo_get_matrix(m_pdc, &m);

        cairo_matrix_scale(&m, m_pfont->m_dFontWidth, 1.0);

        cairo_set_matrix(m_pdc, &m);

    }

    //if (m_pbrush.is_set())
    //{

    //    set_os_color(m_pbrush->m_color);

    //}

    if (edrawtext & e_draw_text_expand_tabs)
    {

        str.replace("\t", "        ");

    }
    else
    {

        str.replace("\t", "");

    }

    if (edrawtext & e_draw_text_single_line)
    {

        str.replace("\n", "");

        str.replace("\rectangle_i32", "");

    }

    string_array stra;

    stra.add_lines(str);

    int i = 0;

    for (auto & strLine : stra)
    {

        cairo_move_to(m_pdc, rectangle.left + dx, rectangle.top + dy + e.ascent + sz.cy * (i) / stra.get_size());

        (*ftext)(m_pdc, strLine);

        cairo_status_t status = cairo_status(m_pdc);

        if (status != CAIRO_STATUS_SUCCESS)
        {

            const char * pszStatus = cairo_status_to_string(status);

            TRACE("cairo error : graphics::draw_text %d %s", status, pszStatus);

        }

        i++;

    }

    _fill2();

    return 1;

}


#endif


bool graphics::draw_text_ex(const ::string & str, const ::rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
{

    ::exception::throw_not_implemented();

    return 0;

}


size_f64 graphics::get_text_extent(const char * lpszString, strsize nCount, strsize iIndex)
{

    size_f64 sz;

    if (!get_text_extent(sz, lpszString, nCount, iIndex))
    {

        return ::size_f64(0.0, 0.0);

    }

    return sz;

}


size_f64 graphics::get_text_extent(const char * lpszString, strsize nCount)
{

    return get_text_extent(lpszString, nCount, -1);

}


size_f64 graphics::get_text_extent(const block & block)
{

    return get_text_extent((const char *) block.get_data(), block.get_size());

}


size_f64 graphics::GetOutputTextExtent(const char * lpszString, strsize nCount)
{

    ::exception::throw_not_implemented();

    return ::size_f64(0, 0);

}


size_f64 graphics::GetOutputTextExtent(const ::string & str)
{

    ::exception::throw_not_implemented();

    return ::size_f64(0, 0);

}


bool graphics::get_text_extent(size_f64 & size, const char * lpszString, strsize nCount, strsize iIndex)
{

   string str(lpszString, minimum_non_negative(iIndex, nCount));

   str = ::str::q_valid(str);

   if(str.is_empty())
   {

      return false;

   }

   _synchronous_lock ml(cairo_mutex());

   if(m_pfont.is_null())
   {

      return false;

   }

   if(m_pfont->m_dFontWidth <= 0.0)
   {

      return false;

   }

   if (iIndex < 0)
   {

      iIndex = (i32)nCount;

   }

   if(str.find('\n') < 0 && str.find('\r') < 0)
   {

#if defined(USE_PANGO)

      PangoFontDescription * pdesc = (PangoFontDescription *) m_pfont->get_os_data(this);

      if(::is_null(pdesc))
      {

         return false;

      }

      PangoLayout * playout;                            // layout for a paragraph of text

      playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

      pango_layout_set_text(playout, lpszString, -1);          // sets the text to be associated with the layout (final arg is length, -1

      // to calculate automatically when passing a nul-terminated string)
      pango_layout_set_font_description(playout, pdesc);            // assign the previous font description to the layout

      pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance

      // have changed, update the pango layout to reflect this
      int width = 0;

      int height = 0;

      PangoRectangle pos;

      pango_layout_index_to_pos(playout, iIndex, &pos);

      pango_layout_get_pixel_size(playout, &width, &height);

      size.cx = (double) pos.x / (double) PANGO_SCALE;

      size.cy = height;

      g_object_unref(playout);                         // free the layout

#else

      _set(m_pfont);

      cairo_text_extents_t textextents;

      cairo_text_extents(m_pdc, str, &textextents);

      cairo_font_extents_t fontextents;

      cairo_font_extents(m_pdc, &fontextents);

      size.cx = textextents.x_advance;

      size.cy = textextents.height;

#endif

      return true;

   }

   string_array straLines;

   straLines.add_lines(str, true);

   size.cx = 0.0;

   size.cy = 0.0;

   for (auto & strLine : straLines)
   {

      size_f64 s0(0.0, 0.0);

      get_text_extent(s0, strLine, str.get_length(), str.get_length());

      size.cx = maximum(size.cx, s0.cx);

      size.cy += s0.cy;

   }

   return true;

}


bool graphics::_GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount, strsize iIndex)
{

    if (iIndex < 0)
    {

        iIndex = (i32)nCount;

    }

    string str(lpszString, minimum(iIndex, nCount));

    str = ::str::q_valid(str);

    if (str.is_empty())
    {

        return false;

    }

    _synchronous_lock ml(cairo_mutex());

    if(m_pfont.is_null())
    {

        return false;

    }

    if(m_pfont->m_dFontWidth <= 0.0)
    {

        return false;

    }

#if defined(USE_PANGO)

    PangoFontDescription * pdesc = (PangoFontDescription *) m_pfont->get_os_data(this);

    if(!pdesc)
    {

        return false;

    }

#endif

    cairo_keep keep(m_pdc);

#if defined(USE_PANGO)

    PangoLayout * playout;                            // layout for a paragraph of text

    playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

    pango_layout_set_text(playout, lpszString, -1);          // sets the text to be associated with the layout (final arg is length, -1
    // to calculate automatically when passing a nul-terminated string)
    pango_layout_set_font_description(playout, pdesc);            // assign the previous font description to the layout

    pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance
    // have changed, update the pango layout to reflect this
    int width = 0;

    int height = 0;

    pango_layout_get_pixel_size (playout, &width, &height);

    g_object_unref(playout);                         // free the layout

    size.cx = width * m_pfont->m_dFontWidth;

    size.cy = height;
#else

    cairo_text_extents_t ex;

    cairo_font_extents_t e;

    if (::str::begins(str, unitext("バーチャルマシン")))
    {

        TRACE("Likely to fail in certain circumstances");

    }

    cairo_font_extents(m_pdc, &e);

    if (!str.has_char())
    {

        size.cx = 0;

        size.cy = e.height;

        return true;

    }

    cairo_text_extents(m_pdc, str, &ex);

    cairo_status_t status = cairo_status(m_pdc);

    if (status != CAIRO_STATUS_SUCCESS)
    {

        const char * pszStatus = cairo_status_to_string(status);

        TRACE("cairo error : graphics::_GetTextExtent %d %s", status, pszStatus);

    }

    size.cx = (::i32)(ex.x_advance * m_pfont->m_dFontWidth);

    size.cy = (::i32)e.height;

#endif

    return true;

}


bool graphics::get_text_extent(size_f64 & size_f64, const char * lpszString, strsize nCount)
{

    return get_text_extent(size_f64, lpszString, nCount, -1);

}


bool graphics::get_text_extent(size_f64 & size_f64, const ::string & str)
{

    return get_text_extent(size_f64, str, str.get_length());

}


bool graphics::fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color)
{

    _synchronous_lock ml(cairo_mutex());

    if (rectangle.right <= rectangle.left || rectangle.bottom <= rectangle.top)
    {

        return false;

    }

    _set_os_color(color);

    cairo_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);

    cairo_fill(m_pdc);

    return true;

}


//bool graphics::fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    if (rectangle.right <= rectangle.left || rectangle.bottom <= rectangle.top)
//    {
//
//        return false;
//
//    }
//
//   _set_os_color(color);
//
//   cairo_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);
//
//   cairo_fill(m_pdc);
//
//   return true;
//
//}


//bool graphics::text_out(double x, double y, const ::string & lpszString, strsize nCount)
//{
//
//    return text_out(x, y, string(lpszString, nCount));
//
//}


::e_status graphics::TextOutRaw(double x, double y, const block & block)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_keep keep(m_pdc);

#if defined(USE_PANGO)

    auto rectangle = ::rectangle_f64(point_f64(x, y), size_f64(65535.0, 65535.0));

    internal_draw_text(block, rectangle, e_align_none);

#else

    ::rectangle_i32 rectangle = rectangle_i32_dimension(
                      ::i32(x),
                      ::i32(y),
                      65535,
                      65535
                  );

    internal_draw_text(block, rectangle, e_null, e_null, &cairo_show_text);

    return true;

#endif

    return true;

}


bool graphics::line_to(double x, double y)
{

    _synchronous_lock ml(cairo_mutex());

    if (!cairo_has_current_point(m_pdc))
    {

        cairo_move_to(m_pdc, m_point.x, m_point.y);

    }

    cairo_line_to(m_pdc, x, y);

    draw();

    m_point.x = x;

    m_point.y = y;

    return true;

}


bool graphics::draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_move_to(m_pdc, x1, y1);

    cairo_line_to(m_pdc, x2, y2);

    draw(ppen);

    m_point.x = x2;

    m_point.y = y2;

    return true;

}


//bool graphics::draw_line(const ::point_f64 & point1, const ::point_f64 & point2, ::draw2d::pen * ppen)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    cairo_move_to(m_pdc, point1.x, point1.y);
//
//    cairo_line_to(m_pdc, point2.x, point2.y);
//
//    draw(ppen);
//
//    m_point = point2;
//
//    return true;
//
//}


bool graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
{

    _synchronous_lock ml(cairo_mutex());

    try
    {

        if (m_pdc == nullptr)
        {

            return false;

        }

        if (ealphamode == ::draw2d::e_alpha_mode_blend)
        {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);

        }
        else if (ealphamode == ::draw2d::e_alpha_mode_set)
        {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);

        }

        ::draw2d::graphics::set_alpha_mode(ealphamode);

        return true;

    }
    catch (...)
    {

    }

    return false;

}


bool graphics::set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint)
{

   return ::draw2d::graphics::set_text_rendering_hint(etextrenderinghint);

}


::e_status graphics::clear_current_point()
{

   cairo_new_sub_path(m_pdc);

   return ::success;

}


bool graphics::attach(void * pdata)
{

    _synchronous_lock ml(cairo_mutex());

    if (m_pdc != nullptr)
    {

        cairo_destroy(m_pdc);

        m_pdc = nullptr;

        m_osdata[0] = m_pdc;

    }

    m_pdc = (cairo_t *)pdata;

    m_osdata[0] = m_pdc;

    return true;

}


void cairo_image_surface_blur(cairo_surface_t* surface, double radius)
{

    _synchronous_lock ml(cairo_mutex());

    // Steve Hanov, 2009
    // Released into the public domain.

    // get width, height
    i32 width = cairo_image_surface_get_width(surface);

    i32 height = cairo_image_surface_get_height(surface);

    unsigned char* dst = (unsigned char*)malloc(width*height * 4);

    unsigned* precalc = (unsigned*)malloc(width*height * sizeof(unsigned));

    unsigned char* src = cairo_image_surface_get_data(surface);

    double mul = 1.f / ((radius * 2)*(radius * 2));

    i32 channel;

    // The number of times to perform the averaging. According to wikipedia,
    // three iterations is good enough to pass for a gaussian.
    const i32 MAX_ITERATIONS = 3;

    i32 iteration;

    ::memcpy_dup(dst, src, width*height * 4);

    for (iteration = 0; iteration < MAX_ITERATIONS; iteration++)
    {

        for (channel = 0; channel < 4; channel++)
        {

            double x, y;

            // precomputation step.
            unsigned char* pix = src;

            unsigned* pre = precalc;

            pix += channel;

            for (y = 0; y < height; y++)
            {

                for (x = 0; x < width; x++)
                {

                    i32 tot = pix[0];

                    if (x > 0) tot += pre[-1];

                    if (y > 0) tot += pre[-width];

                    if (x > 0 && y > 0) tot -= pre[-width - 1];

                    *pre++ = tot;

                    pix += 4;

                }

            }

            // blur step.
            pix = dst + (i32)radius * width * 4 + (i32)radius * 4 + channel;

            for (y = (i32)radius; y < height - radius; y++)
            {

                for (x = (i32)radius; x < width - radius; x++)
                {

                    i32 l = (i32)(x < radius ? 0 : x - radius);

                    i32 t = (i32)(y < radius ? 0 : y - radius);

                    i32 r = (i32)(x + radius >= width ? width - 1 : x + radius);

                    i32 b = (i32)(y + radius >= height ? height - 1 : y + radius);

                    i32 tot = precalc[r + b*width] + precalc[l + t*width] -
                              precalc[l + b*width] - precalc[r + t*width];

                    *pix = (unsigned char)(tot*mul);

                    pix += 4;

                }

                pix += (i32)radius * 2 * 4;

            }

        }

        ::memcpy_dup(src, dst, width*height * 4);

    }

    free(dst);

    free(precalc);

}


bool graphics::blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_pattern_t * ppattern = cairo_get_source(m_pdc);

    if (ppattern == nullptr)
    {

        return false;

    }

    cairo_surface_t * psurfaceSrc = nullptr;

    cairo_pattern_get_surface(ppattern, &psurfaceSrc);

    /*

    cairo_surface_t * psurface = cairo_surface_create_for_rectangle(psurfaceSrc, rectangle.left, rectangle.top, width(rectangle), height(rectangle));

    cairo_image_surface_blur(psurface, dRadius);

    */

    return true;

}


double graphics::get_dpix()
{

    return 72.0;

}


bool graphics::_set(::draw2d::brush * pbrush, double x, double y)
{

   _synchronous_lock ml(cairo_mutex());

   if (pbrush->m_etype == ::draw2d::brush::type_radial_gradient_color)
   {

      cairo_pattern_t * ppattern = cairo_pattern_create_radial(pbrush->m_point.x - x, pbrush->m_point.y - y, 0, pbrush->m_point.x - x, pbrush->m_point.y - y, maximum(pbrush->m_size.cx, pbrush->m_size.cy));

      cairo_pattern_add_color_stop_rgba(ppattern, 0., __expand_rgba(pbrush->m_color1));

      cairo_pattern_add_color_stop_rgba(ppattern, 1., __expand_rgba(pbrush->m_color2));

      cairo_set_source(m_pdc, ppattern);

      cairo_pattern_destroy(ppattern);

   }
   else if (pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
   {

      double x0 = pbrush->m_point1.x - x;

      double y0 = pbrush->m_point1.y - y;

      double x1 = pbrush->m_point2.x - x;

      double y1 = pbrush->m_point2.y - y;

      cairo_pattern_t * ppattern = cairo_pattern_create_linear(x0, y0, x1, y1);

      double dR;

      double dG;

      double dB;

      double dA;

      dR = (double)pbrush->m_color1.dr();

      dG = (double)pbrush->m_color1.dg();

      dB = (double)pbrush->m_color1.db();

      dA = (double)pbrush->m_color1.da();

      cairo_pattern_add_color_stop_rgba(ppattern, 0., dR, dG, dB, dA);

      dR = (double)pbrush->m_color2.dr();

      dG = (double)pbrush->m_color2.dg();

      dB = (double)pbrush->m_color2.db();

      dA = (double)pbrush->m_color2.da();

      cairo_pattern_add_color_stop_rgba(ppattern, 1., dR, dG, dB, dA);

      cairo_set_source(m_pdc, ppattern);

      // cairo_pattern_destroy(ppattern);

   }
   else if (pbrush->m_etype == ::draw2d::brush::type_pattern)
   {

      if(!::is_ok(pbrush->m_pimage))
      {

         return false;

      }

      cairo_surface_t * psurface = cairo_get_target((cairo_t *)pbrush->m_pimage->g()->get_os_data());

      if (psurface == nullptr)
      {

         return false;

      }

      cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

      cairo_status_t status = cairo_pattern_status (ppattern);

      if(status == CAIRO_STATUS_SUCCESS)
      {

         cairo_pattern_set_extend(ppattern, CAIRO_EXTEND_REPEAT);

         cairo_set_source(m_pdc, ppattern);

      }

      cairo_pattern_destroy(ppattern);

      if(status != CAIRO_STATUS_SUCCESS)
      {

         return false;

      }

   }
   else
   {

      double dR = pbrush->m_color.dr();
      double dG = pbrush->m_color.dg();
      double dB = pbrush->m_color.db();
      double dA = pbrush->m_color.da();

      cairo_set_source_rgba(m_pdc, dR, dG, dB, dA);

   }

   return true;

}


bool graphics::_set(::draw2d::pen * ppen)
{

   _synchronous_lock ml(cairo_mutex());

   if (ppen->m_epen == ::draw2d::e_pen_brush)
   {

      _set(ppen->m_pbrush);

   }
   else
   {

      cairo_set_source_rgba(m_pdc, __expand_rgba(ppen->m_color));

   }

   cairo_set_line_width(m_pdc, ppen->m_dWidth);

   return true;

}


#if !defined(USE_PANGO)


bool graphics::_set(::write_text::font * pfontParam)
{

   _synchronous_lock ml(cairo_mutex());

   if (::is_null(pfontParam))
   {

      return false;

   }

   auto pcairodraw2dfont = __font(pfontParam);

   if (::is_null(pcairodraw2dfont))
   {

      return false;

   }

   auto posdata = pfontParam->get_os_data(this);

   if (::is_null(posdata))
   {

      return false;

   }

   if (::is_set(posdata))
   {

      cairo_font_face_t* pfontface = (cairo_font_face_t*)posdata;

      cairo_set_font_face(m_pdc, pfontface);

   }

#ifdef ANDROID

   float fDpi = maximum(::oslocal()->m_fDpiX, ::oslocal()->m_fDpiY);

   float fDensity = ::oslocal()->m_fDensity;

#endif

   if (pfontParam->m_eunitFontSize == ::draw2d::unit_pixel)
   {

#ifdef ANDROID

      cairo_set_font_size(m_pdc, pfontParam->m_dFontSize * fDensity * 0.5);

#else

      cairo_set_font_size(m_pdc, pfontParam->m_dFontSize);

#endif

   }
   else
   {

#ifdef ANDROID

      cairo_set_font_size(m_pdc, pfontParam->m_dFontSize * fDensity * 0.5 * 96.0 / 72.0);

#else

      cairo_set_font_size(m_pdc, pfontParam->m_dFontSize * 96.0 / 72.0);

#endif

   }

   m_pfontDevice = m_pfont;

   return true;

}


#endif


bool graphics::fill_and_draw()
{

   _synchronous_lock ml(cairo_mutex());

   bool bPen = m_ppen->m_epen != ::draw2d::e_pen_null;

   cairo_keep keep(m_pdc);

   if (m_pbrush->m_etype != ::draw2d::brush::e_type_null)
   {

      _set(m_pbrush);

      set_alpha_mode(m_ealphamode);

      if (bPen)
      {

         cairo_fill_preserve(m_pdc);

      }
      else
      {

         cairo_fill(m_pdc);

      }

   }

   keep.pulse();

   if (bPen)
   {

      _set(m_ppen);

      set_alpha_mode(m_ealphamode);

      cairo_stroke(m_pdc);

   }

   return true;

}


bool graphics::fill(::draw2d::brush * pbrush, double xOrg, double yOrg)
{

   _synchronous_lock ml(cairo_mutex());

   if (pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
   {

      return true;

   }

   _fill1(pbrush, xOrg, yOrg);

   cairo_fill(m_pdc);

   _fill2(pbrush, xOrg, yOrg);

   return true;

}


bool graphics::_fill1(::draw2d::brush* pbrush, double xOrg, double yOrg)
{

   if (pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
   {

      return true;

   }

   if (m_pregion.is_set() && !m_pregion.cast < region >()->is_simple_positive_region())
   {

      cairo_set_antialias(m_pdc, CAIRO_ANTIALIAS_BEST);

      cairo_push_group(m_pdc);

      _set(pbrush, xOrg, yOrg);

   }
   else
   {

      _set(pbrush, xOrg, yOrg);

   }

   return true;

}


bool graphics::_fill2(::draw2d::brush* pbrush, double xOrg, double yOrg)
{

   if (pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
   {

      return true;

   }

   if (m_pregion.is_set() && !m_pregion.cast < region >()->is_simple_positive_region())
   {

      cairo_pop_group_to_source(m_pdc);

      m_pregion.cast < region >()->mask_fill(m_pdc);

   }

   return true;

}


bool graphics::fill(double xOrg, double yOrg)
{

   return fill(m_pbrush, xOrg, yOrg);

}


bool graphics::_fill1(double xOrg, double yOrg)
{

   return _fill1(m_pbrush, xOrg, yOrg);

}


bool graphics::_fill2(double xOrg, double yOrg)
{

   return _fill2(m_pbrush, xOrg, yOrg);

}



bool graphics::draw(::draw2d::pen * ppen)
{

    _synchronous_lock ml(cairo_mutex());

    if (ppen == nullptr || ppen->m_epen == ::draw2d::e_pen_null)
    {

        return true;

    }

    cairo_keep keep(m_pdc);

    _set(ppen);

    cairo_stroke(m_pdc);

    return true;

}


bool graphics::_set(::draw2d::path * ppathParam)
{

    if(ppathParam == nullptr)
    {

        return false;

    }

    ::draw2d_cairo::path * ppath = dynamic_cast <::draw2d_cairo::path *> ((::draw2d::path *) ppathParam);

    if(ppath == nullptr)
    {

        return false;

    }

    _synchronous_lock ml(cairo_mutex());

    cairo_keep keep(m_pdc);

    cairo_new_sub_path(m_pdc);

    //if (!m_bOutline)
    {

        if (ppath->m_efillmode == ::draw2d::fill_mode_alternate)
        {

            cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_EVEN_ODD);

        }
        else
        {

            cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_WINDING);

        }

    }

    for (i32 i = 0; i < ppath->m_shapea.get_count(); i++)
    {

        _set(ppath->m_shapea[i]);

    }

    return true;

}


bool graphics::_set(___shape * pshape)
{

   _synchronous_lock ml(cairo_mutex());

   auto eshape = pshape->eshape();

   switch (eshape)
   {
   case ::e_shape_begin_figure:
      return _set(e_shape_begin_figure);
   case ::e_shape_close_figure:
      return _set(e_shape_close_figure);
   case ::e_shape_end_figure:
      return _set(e_shape_end_figure);
   case ::e_shape_arc:
      return _set(pshape->shape < ::arc > ());
   //case ::e_shape_line:
   //   return _set(pshape->shape < ::line > ());
   case ::e_shape_line:
      return _set(pshape->shape < ::line > ());
   //case ::e_shape_lines:
   //   return _set(pshape->shape < ::lines > ());
   case ::e_shape_lines:
      return _set(pshape->shape < ::lines > ());
   //case ::e_shape_rect:
   //   return _set(pshape->shape < ::rectangle_i32 > ());
   case ::e_shape_rectangle:
      return _set(pshape->shape < ::rectangle > ());
   //case ::e_shape_polygon:
   //   return _set(pshape->shape < ::polygon_i32 > ());
   case ::e_shape_polygon:
      return _set(pshape->shape < ::polygon > ());
   case ::e_shape_text_out:
      return _set(pshape->shape < ::write_text::text_out > ());
   case ::e_shape_draw_text:
      return _set(pshape->shape < ::write_text::draw_text > ());
   default:
      throw "unexpected simple os graphics matter type";
   }

   return false;

}


bool graphics::_set(const ::enum_shape & eshape)
{

   _synchronous_lock ml(cairo_mutex());

   if(eshape == e_shape_begin_figure)
   {

      if(cairo_has_current_point(m_pdc))
      {

         cairo_new_sub_path(m_pdc);

      }

      return true;

   }
   else if(eshape == e_shape_close_figure)
   {

      cairo_close_path(m_pdc);

      return true;

   }
   else if(eshape == e_shape_end_figure)
   {

      return true;

   }
   else
   {

      return false;

   }

}


bool graphics::_set(const ::arc & arc)
{

    if (arc.m_sizeRadius.cx <= 0.0000001)
    {

        return 0;

    }

    if (arc.m_sizeRadius.cy <= 0.0000001)
    {

        return 0;

    }

    _synchronous_lock ml(cairo_mutex());

    cairo_keep keep(m_pdc);

    cairo_translate(m_pdc, arc.m_pointCenter.x, arc.m_pointCenter.y);

    cairo_scale(m_pdc, 1.0, arc.m_sizeRadius.cy / arc.m_sizeRadius.cx);

   if(arc.m_angleExt > 0)
   {

      cairo_arc(m_pdc, 0.0, 0.0, arc.m_sizeRadius.cx, arc.m_angleBeg, arc.m_angleEnd2);

   }
   else
   {

      cairo_arc_negative(m_pdc, 0.0, 0.0, arc.m_sizeRadius.cx, arc.m_angleBeg, arc.m_angleEnd2);

   }

   return true;

}


//bool graphics::_set(const ::line & line)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    if (cairo_has_current_point(m_pdc))
//    {
//
//      double x;
//
//      double y;
//
//      cairo_get_current_point (m_pdc, &x, &y);
//
//      if(x != line.m_p1.x || y != line.m_p1.y)
//      {
//
//         cairo_move_to(m_pdc, line.m_p1.x, line.m_p1.y);
//
//      }
//      else
//      {
//
//         cairo_line_to(m_pdc, line.m_p1.x, line.m_p1.y);
//
//      }
//
//    }
//    else
//    {
//
//      cairo_move_to(m_pdc, line.m_p1.x, line.m_p1.y);
//
//    }
//
//    cairo_line_to(m_pdc, line.m_p2.x, line.m_p2.y);
//
//    return true;
//
//}


bool graphics::_set(const ::line & line)
{

    _synchronous_lock ml(cairo_mutex());

    if (cairo_has_current_point(m_pdc))
    {

      double x;

      double y;

      cairo_get_current_point (m_pdc, &x, &y);

      if(x != line.m_p1.x || y != line.m_p1.y)
      {

         cairo_move_to(m_pdc, line.m_p1.x, line.m_p1.y);

      }
      else
      {

         cairo_line_to(m_pdc, line.m_p1.x, line.m_p1.y);

      }

    }
    else
    {

      cairo_move_to(m_pdc, line.m_p1.x, line.m_p1.y);

    }

    cairo_line_to(m_pdc, line.m_p2.x, line.m_p2.y);

    return true;

}


bool graphics::_set(const ::point_i32_array & pointa)
{

   if(pointa.get_count() <= 1)
   {

      return true;

   }

   _synchronous_lock ml(cairo_mutex());

   if (cairo_has_current_point(m_pdc))
   {

      double x;

      double y;

      cairo_get_current_point (m_pdc, &x, &y);

      if(x != pointa[0].x || y != pointa[0].y)
      {

         cairo_move_to(m_pdc, pointa[0].x, pointa[0].y);

      }
      else
      {

         cairo_line_to(m_pdc, pointa[0].x, pointa[0].y);

      }

   }
   else
   {

      cairo_move_to(m_pdc, pointa[0].x, pointa[0].y);

   }

   for(index i = 1; i < pointa.get_count(); i++)
   {

      cairo_line_to(m_pdc, pointa[i].x, pointa[i].y);

   }

   return true;

}


bool graphics::_set(const ::point_f64_array & pointa)
{

   if(pointa.get_count() <= 1)
   {

      return true;

   }

   _synchronous_lock ml(cairo_mutex());

   if (cairo_has_current_point(m_pdc))
   {

      double x;

      double y;

      cairo_get_current_point (m_pdc, &x, &y);

      if(x != pointa[0].x || y != pointa[0].y)
      {

         cairo_move_to(m_pdc, pointa[0].x, pointa[0].y);

      }
      else
      {

         cairo_line_to(m_pdc, pointa[0].x, pointa[0].y);

      }

   }
   else
   {

      cairo_move_to(m_pdc, pointa[0].x, pointa[0].y);

   }

   for(index i = 1; i < pointa.get_count(); i++)
   {

      cairo_line_to(m_pdc, pointa[i].x, pointa[i].y);

   }

   return true;

}


//bool graphics::_set(const lines & lines)
//{
//
//   if(lines.get_count() <= 1)
//   {
//
//      return true;
//
//   }
//
//   _synchronous_lock ml(cairo_mutex());
//
//   cairo_new_sub_path(m_pdc);
//
//   _set((const ::point_i32_array &) lines);
//
//   return true;
//
//}


bool graphics::_set(const lines & lines)
{

   if(lines.get_count() <= 1)
   {

      return true;

   }

   _synchronous_lock ml(cairo_mutex());

   cairo_new_sub_path(m_pdc);

   _set((const ::point_f64_array &) lines);

   return true;

}


//bool graphics::_set(const ::polygon_i32 & polygon_i32)
//{
//
//   if(polygon_i32.get_count() <= 1)
//   {
//
//      return true;
//
//   }
//
//   _synchronous_lock ml(cairo_mutex());
//
//   cairo_new_sub_path(m_pdc);
//
//   _set((const ::point_i32_array &) polygon_i32);
//
//   cairo_close_path(m_pdc);
//
//   return true;
//
//}


bool graphics::_set(const ::polygon_f64 & polygon_i32)
{

   if(polygon_i32.get_count() <= 1)
   {

      return true;

   }

   _synchronous_lock ml(cairo_mutex());

   cairo_new_sub_path(m_pdc);

   _set((const ::point_f64_array &) polygon_i32);

   cairo_close_path(m_pdc);

   return true;

}


//bool graphics::_set(const ::rectangle_i32 & rectangle)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    cairo_rectangle(
//      m_pdc,
//      rectangle.left,
//      rectangle.top,
//      rectangle.width(),
//      rectangle.height());
//
//    return true;
//
//}


bool graphics::_set(const ::rectangle_f64 & rectangle)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_rectangle(
      m_pdc,
      rectangle.left,
      rectangle.top,
      rectangle.width(),
      rectangle.height());

    return true;

}


bool graphics::_set(const ::write_text::text_out & textout)
{

    _synchronous_lock ml(cairo_mutex());

    auto rectangle = ::rectangle_f64(textout.m_point, size_f64(65535.0, 65535.0));

#if defined(USE_PANGO)

    internal_draw_text_pango(textout.m_strText, rectangle, e_align_top_left, e_draw_text_none, &pango_cairo_layout_path);

#else

    internal_draw_text(textout.m_strText, rectangle, e_align_top_left, e_draw_text_none, &cairo_text_path);

#endif

    cairo_status_t status = cairo_status(m_pdc);

    if(status != CAIRO_STATUS_SUCCESS)
    {

        const char * pszStatus = cairo_status_to_string(status);

        TRACE("cairo error : graphics::set(string_path) %d %s", status, pszStatus);

    }

    return true;

}


bool graphics::_set(const ::write_text::draw_text & drawtext)
{

   _synchronous_lock ml(cairo_mutex());

   auto rectangle = drawtext.m_rectangle;

#if defined(USE_PANGO)

   internal_draw_text_pango(drawtext.m_strText, rectangle, e_align_top_left, e_draw_text_none, &pango_cairo_layout_path);

#else

   internal_draw_text(drawtext.m_strText, rectangle, e_align_top_left, e_draw_text_none, &cairo_text_path);

#endif

   cairo_status_t status = cairo_status(m_pdc);

   if(status != CAIRO_STATUS_SUCCESS)
   {

      const char * pszStatus = cairo_status_to_string(status);

      TRACE("cairo error : graphics::set(string_path) %d %s", status, pszStatus);

   }

   return true;

}


//bool graphics::_set(::draw2d_cairo::path::close * pclose)
//{
//
//   return true;
//
//}


//bool graphics::set(const ::draw2d_cairo::path::move & p)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    cairo_move_to(m_pdc, p.m_x + 0.5, p.m_y + 0.5);
//
//    return true;
//
//}



bool graphics::draw()
{

    return draw(m_ppen);

}


void * graphics::detach()
{

    _synchronous_lock ml(cairo_mutex());

    cairo_t * p = m_pdc;

    m_osdata[0] = nullptr;

    m_pdc = nullptr;

    return p;

}


bool graphics::_set_os_color(color32_t color32)
{

    _synchronous_lock ml(cairo_mutex());

    auto r = colorref_get_r_value(color32);

    auto g = colorref_get_g_value(color32);

    auto b = colorref_get_b_value(color32);

    auto a = colorref_get_a_value(color32);

    cairo_set_source_rgba(m_pdc, r / 255.0, g / 255.0, b / 255.0, a / 255.0);

    return true;

}


bool graphics::flush()
{

    _synchronous_lock ml(cairo_mutex());

    cairo_pattern_t * ppattern = cairo_get_source(m_pdc);

    if (ppattern == nullptr)
    {

        return true;

    }

    cairo_surface_t * psurface = nullptr;

    cairo_pattern_get_surface(ppattern, &psurface);

    if (psurface == nullptr)
    {

        return true;

    }

    cairo_surface_flush(psurface);

    return true;

}


//#ifdef WINDOWS
//
//
//bool graphics::attach_hdc(HDC hdc)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    if (m_hdcAttach != nullptr)
//    {
//
//        detach_hdc();
//
//    }
//
//    m_psurfaceAttach = cairo_win32_surface_create(hdc);
//
//    if (m_psurfaceAttach == nullptr)
//    {
//
//        return false;
//
//    }
//
//    m_pdc = cairo_create(m_psurfaceAttach);
//
//    if (m_pdc == nullptr)
//    {
//
//        cairo_surface_destroy(m_psurfaceAttach);
//
//        return false;
//
//    }
//
//    m_hdcAttach = hdc;
//
//    m_osdata[0] = m_pdc;
//
//    return false;
//
//}
//
//HDC graphics::detach_hdc()
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    if (m_hdcAttach == nullptr)
//    {
//
//        return nullptr;
//
//    }
//
//    HDC hdc = m_hdcAttach;
//
//    cairo_surface_destroy(m_psurfaceAttach);
//
//    m_psurfaceAttach = nullptr;
//
//    return hdc;
//
//}
//
//
//#endif // WINDOWS


//#if defined(USE_PANGO)
//
//
//void graphics::enum_fonts(::write_text::font_enumeration_item_array & itema)
//{
//
//    _synchronous_lock ml(cairo_mutex());
//
//    PangoFontMap * pfontmap = pango_cairo_font_map_get_default();
//
//    PangoFontFamily ** families;
//
//    int n_families = 0;
//
//    pango_font_map_list_families(pfontmap, &families, &n_families);
//
//    printf("Total fonts: %d", n_families);
//
//    __pointer(::write_text::font_enumeration_item) item;
//
//    for (int i = 0; i < n_families; i++)
//    {
//
//        item = __new(::write_text::font_enumeration_item);
//
//        PangoFontFamily * pfamily = families[i];
//
//        string strFileName = pango_font_family_get_name(pfamily);
//
//        item->m_mapFileName[0] = strFileName;
//
//        item->m_strName = strFileName;
//
//        itema.add(item);
//
//    }
//
//    g_free(families);
//
//}
//
//
//
//#else
//
////
////void graphics::enum_fonts(::write_text::font_enumeration_item_array & itema)
////{
////
////   __pointer(::write_text::font_enumeration_item) pitem;
////
////#if DEBUG_WINDOWS_C_ANDROID_FONTS
////
////   ::file::listing listing(get_context());
////
////   listing.ls_pattern_file("C:/android_fonts", {"*.ttf"});
////
////   __pointer(ttf_util) putil;
////
////   ::e_status estatus = __construct_new(putil);
////
////   for (auto& path : listing)
////   {
////
////      pitem = __new(::write_text::font_enumeration_item);
////
////      pitem->m_strFile = path;
////
////      string strName = putil->GetFontNameFromFile(path);
////
////      if (strName.is_empty())
////      {
////
////         strName = path.title();
////
////      }
////
////      pitem->m_strName = strName;
////
////      itema.add(pitem);
////
////      g_pmapFontFaceName->set_at(strName, path);
////
////
////   }
////
////
////#elif defined(LINUX)
////
////   _synchronous_lock ml(cairo_mutex());
////
////   FcPattern *    pat;
////
////   FcObjectSet *  os;
////
////   FcFontSet *    fs;
////
////   FcChar8 *      s;
////
////   FcChar8 *      file;
////
////   int            i;
////
////   if (!g_fcResult)
////   {
////
////      g_fcResult = FcInit();
////
////   }
////
////   if (!g_fcConfig)
////   {
////
////      g_fcConfig = FcConfigGetCurrent();
////
////      FcConfigSetRescanInterval(g_fcConfig, 30);
////
////   }
////
////   pat = FcPatternCreate();
////
////   os = FcObjectSetBuild(FC_FAMILY, FC_STYLE, FC_FILE, nullptr);
////
////   fs = FcFontList(g_fcConfig, pat, os);
////
////   printf("Total fonts: %d", fs->nfont);
////
////   for (i = 0; fs && i < fs->nfont; i++)
////   {
////
////      pitem = __new(::write_text::font_enumeration_item);
////
////      FcPattern * font = fs->fonts[i];//FcFontSetFont(fs, i);
////
////      //FcPatternPrint(font);
////
////      s = FcNameUnparse(font);
////
////      string str((const ::string &)s);
////
////      int iFind = str.find(":");
////
////      if (iFind > 0)
////      {
////
////         str = str.Left(iFind);
////
////      }
////
////      if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch)
////      {
////
////         //printf("Filename: %s", file);
////
////         pitem->m_strFile = (const ::string &)file;
////
////      }
////      else
////      {
////
////         pitem->m_strFile = str;
////
////      }
////
////      //printf("Font: %s\n", str.c_str());
////
////      //printf("Font: %s\n", s);
////
////      pitem->m_strName = str;
////
////      pitem->m_ecs = ::write_text::font::cs_default;
////
////      itema.add(pitem);
////
////      free(s);
////
////   }
////
////   if (fs != nullptr)
////   {
////
////      FcFontSetDestroy(fs);
////
////   }
////
////#elif defined(WINDOWS)
////
////
////   ::draw2d::wingdi_enum_fonts(itema, false, true, false);
////
////#elif defined(ANDROID)
////
////   auto psession = get_session();
////
////   itema.add(psession->m_fontenumitema);
////
////#else
////
////    __throw(error_not_implemented);
////
////#endif
////
////}
//
//
//#endif
//
//
//::file::path graphics::get_font_path(const ::string & str, int iWeight, bool bItalic)
//{
//
//#ifdef LINUX
//
//    _synchronous_lock ml(cairo_mutex());
//
//    if (str.find("/") >= 0)
//    {
//
//        return str;
//
//    }
//
//    if (str == "TakaoPGothic")
//    {
//
//        output_debug_string("searching TakaoPGothic");
//
//    }
//
//    string strPath;
//
//    if (!g_pmapFontPath->lookup(str, strPath))
//    {
//
//        string_array straPath;
//
//        string_array stra;
//
//        ::write_text::font_enumeration_item_array itema;
//
//        enum_fonts(itema);
//
//        if (str == "TakaoPGothic")
//        {
//
//            output_debug_string("searching TakaoPGothic");
//
//        }
//
//        int iFind = stra.find_first_ci(str);
//
//        if (iFind >= 0)
//        {
//
//            strPath = straPath[iFind];
//
//        }
//        else
//        {
//
//            iFind = stra.find_first_begins_ci(str + " Regular");
//
//            if (iFind >= 0)
//            {
//
//                strPath = straPath[iFind];
//
//            }
//            else
//            {
//
//                iFind = stra.find_first_begins_ci(str + ",");
//
//                if (iFind >= 0)
//                {
//
//                    strPath = straPath[iFind];
//
//                }
//                else
//                {
//
//                    iFind = stra.find_first_begins_ci(str + " ");
//
//                    if (iFind >= 0)
//                    {
//
//                        strPath = straPath[iFind];
//
//                    }
//                    else
//                    {
//
//                        strPath = str;
//
//                    }
//
//
//                }
//
//            }
//
//        }
//
//        g_pmapFontPath->set_at(str, strPath);
//
//    }
//
//    return strPath;
//
//#else
//
//   return ::draw2d::graphics::get_font_path(str, iWeight, bItalic);
//
//#endif
//
//}


bool graphics::_get(::draw2d::matrix & matrix)
{

    _synchronous_lock ml(cairo_mutex());

    cairo_matrix_t cairomatrix;

    cairo_get_matrix(m_pdc, &cairomatrix);

    __copy(matrix, cairomatrix);

    return true;

}


bool graphics::_set(const ::draw2d::matrix & matrix)
{

    _synchronous_lock ml(cairo_mutex());

    if(m_pdc == nullptr)
    {

        return false;

    }

    cairo_matrix_t cairomatrix;

    __copy(cairomatrix, matrix);

    cairo_set_matrix(m_pdc, &cairomatrix);

    return true;

}


FT_Face graphics::ftface(const ::string & pszFontName, int iWeight, bool bItalic)
{

   _synchronous_lock synchronouslock(cairo_mutex());

   FT_Face ftface = (*g_pmapFontFace)[pszFontName][iWeight *10 + (bItalic ? 1 : 0)];

   if(ftface)
   {

      return ftface;

   }

   ::file::path path = get_font_path(pszFontName, iWeight, bItalic);

   if (path.is_empty())
   {

      path = get_font_path(pszFontName, 400, bItalic);

      if (path.is_empty())
      {

         path = get_font_path(pszFontName, 0, bItalic);

         if (path.is_empty() && bItalic)
         {

            path = get_font_path(pszFontName, iWeight, false);

            if (path.is_empty())
            {

               path = get_font_path(pszFontName, 400, false);

               if (path.is_empty())
               {

                  path = get_font_path(pszFontName, 0, false);

               }

            }

         }

      }

   }

   if(path.has_char())
   {

      auto ftlibrary = __ftlibrary();

      const char* psz = path;

      FT_Error error = FT_New_Face(ftlibrary, psz, 0, &ftface);

      if (error == FT_Err_Unknown_File_Format)
      {

         ftface = nullptr;

      }
      else if (error == FT_Err_Missing_Module)
      {

         ftface = nullptr;

      }
      else if (error)
      {

         ftface = nullptr;

      }
      else
      {

         TRACE("Creating font : %s", pszFontName);

      }

   }

   (*g_pmapFontFace)[pszFontName][iWeight * 10 + (bItalic ? 1 : 0)] = ftface;

   return ftface;

}



} // namespace draw2d_cairo

FT_Library g_ftlibrary = nullptr;

FT_Library __ftlibrary()
{

   if (!g_ftlibrary)
   {

      auto error = FT_Init_FreeType(&g_ftlibrary);

      if (error)
      {

         return nullptr;

      }

   }

   return g_ftlibrary;

}


//bool path::contains(::draw2d::graphics_pointer & pgraphics, const point_f64& point)
//{
//
//   pgraphics->set(this);
//
//   pgraphics->fill_contains(point);
//
//   int iFill = 0;
//
//   for (auto& pmatter : m_shapea)
//   {
//
//      if (pmatter->contains(point))
//      {
//
//         if (m_efillmode == ::draw2d::fill_mode_winding)
//         {
//
//            return true;
//
//         }
//         else
//         {
//
//            iFill++;
//
//         }
//
//      }
//
//   }
//
//   return (iFill % 2) == 1;
//
//}



