#include "framework.h"
//#include "aura/platform/app_core.h"

#include <math.h>
#include <dwmapi.h>


#undef new

namespace opengl
{

#include "line1.h"

}


BOOL CALLBACK draw2d_opengl_EnumFamCallBack(LPLOGFONT lplf,LPNEWTEXTMETRIC lpntm,::u32 FontType,LPVOID p);


class draw2d_opengl_enum_fonts
{
public:


   ::write_text::font_enumeration_item_array& m_itema;


   draw2d_opengl_enum_fonts(::write_text::font_enumeration_item_array& itema):
      m_itema(itema)
   {

   }


};


namespace draw2d_opengl
{

   ATOM class_atom = NULL;

   graphics * thread_graphics()
   {

      return ::get_task()->payload("draw2d_opengl::graphics").cast < graphics >();

   }

   void thread_graphics(graphics * pgraphics)
   {

      ::get_task()->payload("draw2d_opengl::graphics") = pgraphics;

   }


   graphics::graphics()
   {

      m_hwnd = nullptr;
      m_hglrc = nullptr;
      m_pointTranslate = ::point_i32();
      m_bPrinting = false;
      m_pimageAlphaBlend = nullptr;
      m_size.set(0, 0);
      m_hdc = nullptr;
      m_hdcGraphics = nullptr;
      m_ewritetextrendering = ::write_text::e_rendering_anti_alias_grid_fit;
      m_dFontFactor = 1.0;

   }


   void graphics::assert_valid() const
   {

      object::assert_valid();

   }


   void graphics::dump(dump_context& dumpcontext) const
   {
      
      object::dump(dumpcontext);

      dumpcontext << "m_hdc = " << (iptr) m_hdc;
      dumpcontext << "\nm_hAttribDC = " << (iptr) m_hdc;
      dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";

   }


   graphics::~graphics()
   {

      opengl_delete_offscreen_buffer();

      DeleteDC();

   }


   bool graphics::IsPrinting() const
   {

      return m_bPrinting;

   }

   bool graphics::CreateDC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void* lpInitData)
   {
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
      return false;
   }


   bool graphics::CreateIC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void* lpInitData)
   {
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
      return false;
   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      return true;

   }


   bool graphics::opengl_create_offscreen_buffer(const ::size_i32 & size)
   {

      if (class_atom == 0) {
         TRACE("MS GDI - RegisterClass failed\n");
         TRACE("last-error code: %d\n", GetLastError());
         return false;
      }

      glewExperimental = GL_TRUE;
      GLenum err = glewInit();
      if (err != GLEW_OK) {
         // Problem: glewInit failed, something is seriously wrong.
         TRACE( "glewInit failed: %s\n",glewGetErrorString(err));
         return false;
      }
      LPCTSTR lpClassName = L"draw2d_opengl_offscreen_buffer_window";
      LPCTSTR lpWindowName = L"draw2d_opengl_offscreen_buffer_window";
      //::u32 dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
      ::u32 dwExStyle = 0;
      ::u32 dwStyle = WS_OVERLAPPEDWINDOW;
      dwStyle |= WS_POPUP;
      //dwStyle |= WS_VISIBLE;
      //dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
      dwStyle &= ~WS_CAPTION;
      //dwStyle = 0;
      dwStyle &= ~WS_THICKFRAME;
      dwStyle &= ~WS_BORDER;
      int x = 0;
      int y = 0;
      int nWidth = size.cx;
      int nHeight = size.cy;
      HWND hWndParent = nullptr;
      HMENU hMenu = nullptr;
      HINSTANCE hInstance = psystem->m_hinstance;
      LPVOID lpParam = nullptr;

      HWND window = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y,  nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

      if (window == nullptr) 
      {
         TRACE("MS GDI - CreateWindow failed\n");
         TRACE("last-error code: %d\n", GetLastError());
         return false;
      }

      // create WGL context, make current

      PIXELFORMATDESCRIPTOR pixformat;
      int chosenformat;
      HDC dev_context = GetDC(window);
      if (dev_context == nullptr) 
      {
         TRACE("MS GDI - GetDC failed\n");
         TRACE("last-error code: %d\n", GetLastError());
         return false;
      }

      ZeroMemory(&pixformat, sizeof(pixformat));
      pixformat.nSize = sizeof(pixformat);
      pixformat.nVersion = 1;
      pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      pixformat.iPixelType = PFD_TYPE_RGBA;
      pixformat.cColorBits = 24;
      pixformat.cAlphaBits = 8;
      pixformat.cDepthBits = 24;
      pixformat.cStencilBits = 8;

      chosenformat = ChoosePixelFormat(dev_context, &pixformat);
      if (chosenformat == 0) 
      {
         TRACE("MS GDI - ChoosePixelFormat failed\n");
         TRACE("last-error code: %d\n", GetLastError());
         return false;
      }

      bool spfok = SetPixelFormat(dev_context, chosenformat, &pixformat);
      if (!spfok) 
      {
         TRACE("MS GDI - SetPixelFormat failed\n");
         TRACE("last-error code: %d\n", GetLastError());
         return false;
      }

      HGLRC gl_render_context = wglCreateContext(dev_context);
      if (gl_render_context == nullptr) 
      {
         TRACE("MS WGL - wglCreateContext failed\n");
         TRACE("last-error code: %d\n", GetLastError());
         ReleaseDC(m_hwnd, m_hdc);
         return false;
      }

      bool mcok = wglMakeCurrent(dev_context, gl_render_context);
      if (!mcok) 
      {
         TRACE("MS WGL - wglMakeCurrent failed\n");
         TRACE("last-error code: %d\n", GetLastError());
         return false;
      }

      m_hwnd = window;
      m_hdc = dev_context;
      m_hglrc = gl_render_context;
      m_size = size;

      return true;

   }


   bool graphics::opengl_delete_offscreen_buffer()
   {

      if (m_hglrc == NULL && m_hdc == NULL && m_hwnd == NULL)
      {

         return true;

      }

      wglMakeCurrent(nullptr, nullptr);
      wglDeleteContext(m_hglrc);
      ::ReleaseDC(m_hwnd, m_hdc);
      ::DestroyWindow(m_hwnd);
      m_size.set(0, 0);
      m_hglrc = NULL;
      m_hwnd = NULL;
      m_hdc = NULL;
      return true;

   }



   i32 graphics::ExcludeUpdateRgn(::user::primitive * pwindow)
   {
      // ASSERT(m_hdc != nullptr);
      //::exception::throw_not_implemented();
      ////return ::ExcludeUpdateRgn(m_hdc, WIN_WINDOW(pwindow)->get_handle());
      return 0;
   }

   i32 graphics::GetDeviceCaps(i32 nIndex) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetDeviceCaps(m_hdc, nIndex);
      return 0;
   }

   point_i32 graphics::GetBrushOrg() const
   {
      // ASSERT(m_hdc != nullptr);
      ::point_i32 point;
      //VERIFY(::GetBrushOrgEx(m_hdc, &point));
      return point;
   }

   point_i32 graphics::SetBrushOrg(i32 x, i32 y)
   {
      // ASSERT(m_hdc != nullptr);
      ::point_i32 point;
      //VERIFY(::SetBrushOrgEx(m_hdc, x, y, &point));
      return point;
   }

   point_i32 graphics::SetBrushOrg(const ::point_i32 & point)
   {
      // ASSERT(m_hdc != nullptr);
      //VERIFY(::SetBrushOrgEx(m_hdc, point.x, point.y, &point));
      return point;
   }

   i32 graphics::EnumObjects(i32 nObjectType, i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::EnumObjects(m_hdc, nObjectType, (GOBJENUMPROC)lpfn, lpData);
      return 0;
   }

   ::draw2d::bitmap * graphics::SelectObject(::draw2d::bitmap * pbitmap)
   {

      if (m_pbitmap == pbitmap)
      {

         return m_pbitmap;

      }

      opengl_delete_offscreen_buffer();

      if (!opengl_create_offscreen_buffer(pbitmap->get_size()))
      {

         return NULL;

      }

      ::opengl::resize(pbitmap->get_size());

      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      m_pbitmap = pbitmap;

      return m_pbitmap;

   }


   ::draw2d::object* graphics::SelectObject(::draw2d::object* pObject)
   {
      /*      // ASSERT(m_hdc != nullptr);
         if(pObject == nullptr)
            return nullptr;
         return SelectGdiObject(get_application(), m_hdc, pObject->get_os_data()); */
      return nullptr;
   }

   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for nullptr handles
   {

      ::u32 uType = GetObjectType(hObject);

      if(uiType == OBJ_BITMAP)
      {

         HBITMAP hbitmap = (HBITMAP) hObject;

         if(m_pbitmap.is_null())
            m_pbitmap.create();

         if(m_pbitmap.is_null())
            return nullptr;

         //(dynamic_cast < ::draw2d_opengl::bitmap * > (m_pbitmap.m_p))->m_pbitmap = new plusplus::Bitmap(hbitmap, nullptr);

         //if(m_pgraphics != nullptr)
         //{

         //   try
         //   {

         //      delete m_pgraphics;

         //   }
         //   catch(...)
         //   {

         //      TRACE("graphics::SelectObject(HGDIOBJ) OBJ_BITMAP : Failed to delete plusplus::Graphics");

         //   }

         //   m_pgraphics = nullptr;

         //}

         //m_pgraphics = new plusplus::Graphics((plusplus::Bitmap *) m_pbitmap->get_os_data());

         //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

         //set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

         return hbitmap;

      }

      //*ASSERT(m_hdc == m_hdc); // ASSERT a simple graphics object
      //return (hObject != nullptr) ? ::SelectObject(m_hdc, hObject) : nullptr; */
      return nullptr;
   }

   color32_t graphics::GetNearestColor(color32_t crColor) const
   {
      //return ::GetNearestColor(m_hdc, crColor);
      return 0;
   }

   ::u32 graphics::RealizePalette()
   {
      //return ::RealizePalette(m_hdc);
      return 0;
   }

   void graphics::UpdateColors()
   {
      //::UpdateColors(m_hdc);
   }

   i32 graphics::GetPolyFillMode() const
   {
      //return ::GetPolyFillMode(m_hdc);
      return 0;
   }

   i32 graphics::GetROP2() const
   {
      //return ::GetROP2(m_hdc);
      return 0;
   }

   i32 graphics::GetStretchBltMode() const
   {
      //return ::GetStretchBltMode(m_hdc);
      return 0;
   }

   i32 graphics::GetMapMode() const
   {
      //return ::GetMapMode(m_hdc);
      return 0;
   }

   i32 graphics::GetGraphicsMode() const
   {
      //return ::GetGraphicsMode(m_hdc);
      return 0;
   }

   bool graphics::GetWorldTransform(XFORM* pXform) const
   {



      //m_pgraphics->GetTransform(((graphics *)this)->m_pm);

      //plusplus::REAL rectangle_i32[6];

      //m_pm->GetElements(rectangle);

      //pXform->eM11 = rectangle_i32[0];
      //pXform->eM12 = rectangle_i32[1];
      //pXform->eM21 = rectangle_i32[2];
      //pXform->eM22 = rectangle_i32[3];

      //pXform->eDx = rectangle_i32[4];
      //pXform->eDy = rectangle_i32[5];


      return true;

   }

   size_i32 graphics::GetViewportExt() const
   {
      ::size_i32 size;
      //::GetViewportExtEx(m_hdc, &size);
      return size;
   }

   point_i32 graphics::GetWindowOrg() const
   {
      ::point_i32 point;
      //::GetWindowOrgEx(m_hdc, &point);
      return point;
   }

   size_i32 graphics::GetWindowExt() const
   {
      ::size_i32 size;
      //::GetWindowExtEx(m_hdc, &size);
      return size;
   }

   // non-virtual helpers calling virtual mapping functions
   point_i32 graphics::SetViewportOrg(const ::point_i32 & point)
   {

      return SetViewportOrg(point.x, point.y);

   }

   size_i32 graphics::SetViewportExt(const ::size_i32 & size)
   {
      return SetViewportExt(size.cx, size.cy);
   }

   point_i32 graphics::SetWindowOrg(const ::point_i32 & point)
   {
      return SetWindowOrg(point.x, point.y);
   }

   size_i32 graphics::set_window_ext(const ::size_i32 & size)
   {
      return set_window_ext(size.cx, size.cy);
   }

   void graphics::DPtoLP(POINT_I32 * lpPoints, count nCount) const
   {
      //::DPtoLP(m_hdc, lpPoints, (int) nCount);
   }

   void graphics::DPtoLP(RECTANGLE_I32 * prectangle) const
   {
      //::DPtoLP(m_hdc, (POINT_I32 *)rectangle, 2);
   }

   void graphics::LPtoDP(POINT_I32 * lpPoints,count nCount) const
   {
      //::LPtoDP(m_hdc, lpPoints, (int)  nCount);
   }

   void graphics::LPtoDP(RECTANGLE_I32 * prectangle) const
   {
      //::LPtoDP(m_hdc, (POINT_I32 *)rectangle, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      //return ::FillRgn(m_hdc, (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;
      return false;

   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight)
   {

      //return ::FrameRgn(m_hdc, (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;
      return false;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::InvertRgn(m_hdc, (HRGN)pRgn->get_os_data()) != false;
      return false;

   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::PaintRgn(m_hdc, (HRGN)pRgn->get_os_data())  != false;

      return ::draw2d::graphics::PaintRgn(pRgn);

   }


   bool graphics::PtVisible(i32 x, i32 y) const
   {

      // ASSERT(m_hdc != nullptr);

      //return ::PtVisible(m_hdc, x, y) != false;
      //return ::draw2d::graphics::PtVisible(x, y);

      return true;

   }


   bool graphics::PtVisible(const ::point_i32 & point) const
   {
   
      // ASSERT(m_hdc != nullptr);   // call virtual
      return PtVisible(point.x, point.y);

   }


   bool graphics::RectVisible(const RECTANGLE_I32 &  rectangle_i32) const
   {

      // ASSERT(m_hdc != nullptr);

      //return ::RectVisible(m_hdc, &rectangle) != false;
      return false;

   }


   //point_i32 graphics::GetCurrentPosition() const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //::point_i32 point(m_po;
   //   //VERIFY(::GetCurrentPositionEx(m_hdc, &point));
   //   //return point;
   //   return ::draw2d::graphics::G;
   //}

   bool graphics::polyline(const POINT_I32* lpPoints,count nCount)
   {

      if(nCount <= 0)
         return true;

      bool bOk1 = false;

      //plusplus::Point * ppoints = new plusplus::Point[nCount];

      //try
      //{

      //   for(i32 i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }

      //   bOk1 = m_pgraphics->DrawLines(gl2d_pen(),ppoints,(::i32) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      return bOk1;
   }


   bool graphics::Arc(i32 x1,i32 y1,i32 x2,i32 y2,i32 x3,i32 y3,i32 x4,i32 y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / pmathematics->get_pi();
      double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / pmathematics->get_pi();
      double sweep      = fabs(end - start);

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return Arc(x1,y1,x2-x1,y2-y1,start,sweep);

   }


   bool graphics::Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / pmathematics->get_pi();
      double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / pmathematics->get_pi();
      double sweep      = fabs(end - start);

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return Arc(x1,y1, x2-x1, y2-y1, start, sweep);

   }


   bool graphics::Arc(i32 x1,i32 y1,i32 w,i32 h,double start, double extends)
   {

      //::plusplus::Rect rectangle_i32(x1,y1,w,h);

      //return m_pgraphics->DrawArc(gl2d_pen(),rectangle,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::Arc(double x1,double y1,double w,double h,double start,double extends)
   {

      //::plusplus::RectF rectangle_f32((plusplus::REAL) x1,(plusplus::REAL) y1,(plusplus::REAL) w,(plusplus::REAL) h);

      //return m_pgraphics->DrawArc(gl2d_pen(),rectangle_f32,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::fill_rectangle(const ::rectangle_i32 & rectangle, ::draw2d::brush* pbrush)
   {

      glBegin(GL_QUADS);

      set(pbrush);

      ::opengl::vertex2f(rectangle);

      glEnd();

      return false;

   }


   void graphics::FrameRect(const RECTANGLE_I32 &  rectParam,::draw2d::brush* pBrush)
   {

      //// ASSERT(m_hdc != nullptr);

      //::FrameRect(m_hdc,&rectParam,(HBRUSH)pBrush->get_os_data());

   }


   void graphics::InvertRect(const RECTANGLE_I32 &  rectParam)
   {

      // ASSERT(m_hdc != nullptr);

      //::InvertRect(m_hdc,&rectParam);

   }


   bool graphics::DrawIcon(i32 x, i32 y, ::draw2d::icon * picon)
   {

      // ASSERT(m_hdc != nullptr);

      if(picon == nullptr)
         return false;

      //return ::DrawIcon(m_hdc, x, y, (HICON) picon->m_picon) != false;

      return false;

   }

   bool graphics::DrawIcon(const ::point_i32 & point, ::draw2d::icon * picon)
   {

      // ASSERT(m_hdc != nullptr);

      if(picon == nullptr)
         return false;

      //return ::DrawIcon(m_hdc, point.x, point.y, (HICON) picon->m_picon) != false;

      return false;

   }

   bool graphics::DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags)
   {

      //try
      //{

      //   if(picon == nullptr)
      //      return false;

      //   if(m_pgraphics == nullptr)
      //      return false;

      //   bool bOk = false;

      //   BITMAPINFO info;
      //   color32_t * pcolorref;

      //   ZeroMemory(&info, sizeof (BITMAPINFO));

      //   info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
      //   info.bmiHeader.biWidth         = cx;
      //   info.bmiHeader.biHeight        = - cy;
      //   info.bmiHeader.biPlanes        = 1;
      //   info.bmiHeader.biBitCount      = 32;
      //   info.bmiHeader.biCompression   = BI_RGB;
      //   info.bmiHeader.biSizeImage     = cx * cy * 4;

      //   HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pcolorref, nullptr, 0);

      //   HDC hdc = ::CreateCompatibleDC(nullptr);

      //   HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

      //   ICONINFO ii;
      //   BITMAPINFO biC;
      //   BITMAPINFO biM;

      //   __zero(biC);
      //   __zero(biM);



      //   if(::GetIconInfo((HICON)picon->m_picon,&ii))
      //   {

      //      ::GetObject(ii.hbmColor,sizeof(biC),(LPVOID)&biC);

      //      ::GetObject(ii.hbmMask,sizeof(biM),(LPVOID)&biM);

      //   }



      //   if(!::DrawIconEx(hdc,0,0,(HICON)picon->m_picon,cx,cy,istepIfAniCur,nullptr,DI_IMAGE | DI_MASK))
      //   {

      //      output_debug_string("nok");
      //   }
      //   else
      //   {

      //      bool bAllZeroAlpha = true;
      //      bool bTheres::u32 = false;

      //      int area = cx * cy;

      //      color32_t * pc = pcolorref;
      //      byte * pA = &((byte *) pcolorref)[3];

      //      for(int i = 0; i < area; i++)
      //      {
      //         if(*pc != 0)
      //         {
      //            bTheres::u32 = true;
      //         }
      //         if(*pA != 0)
      //         {
      //            bAllZeroAlpha = false;
      //            break;
      //         }
      //         pc++;
      //         pA +=4;
      //      }

      //      if(bAllZeroAlpha && bTheres::u32)
      //      {

      //         pc = pcolorref;
      //         pA = &((byte *)pcolorref)[3];

      //         for(int i = 0; i < area; i++)
      //         {
      //            if(*pc != 0)
      //            {
      //               *pA = 255;
      //            }
      //            pc++;
      //            pA +=4;
      //         }
      //      }

      //      ::SelectObject(hdc, hbitmapOld);

      //      try
      //      {

      //         plusplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (byte *) pcolorref);

      //         bOk = m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, plusplus::UnitPixel) == plusplus::Ok;

      //      }
      //      catch(...)
      //      {
      //      }

      //   }

      //   ::DeleteDC(hdc);

      //   ::DeleteObject(hbitmap);

      //   return bOk;

      //}
      //catch(...)
      //{
      //   return false;
      //}

      //return ::DrawIconEx(m_hdc, x, y, picon->m_hicon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags);

      return true;

   }

//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush, nullptr, (LPARAM)hBitmap, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != false;
//      return false;
//
//   }

//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != false;
//
//      return false;
//
//   }
//
//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush, nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != false;
//
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::string & lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::string & lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, HBRUSH hBrush)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush,
//          //               lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(),
//        //                 lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != false;
//      return false;
//
//   }
//

//   bool graphics::DrawEdge(const ::rectangle_i32 & rectParam,::u32 nEdge,::u32 nFlags)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawEdge(m_hdc,(RECTANGLE_I32 *)&rectParam,nEdge,nFlags) != false;
//      return false;
//
//   }
//

//   bool graphics::DrawFrameControl(const ::rectangle_i32 & rectParam,::u32 nType,::u32 nState)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawFrameControl(m_hdc,(RECTANGLE_I32 *) &rectParam,nType,nState) != false;
//      return false;
//
//   }


   bool graphics::Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::Chord(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
      return false;

   }


   bool graphics::Chord(const RECTANGLE_I32 &  rectParam,const ::point_i32 & pointStart,const ::point_i32 & pointEnd)
   {

      // ASSERT(m_hdc != nullptr);
      //return ::Chord(m_hdc,rectParam.left,rectParam.top,
      //               rectParam.right,rectParam.bottom,ptStart.x,ptStart.y,
      //               ptEnd.x, ptEnd.y) != false;

      return false;

   }

   
   void graphics::DrawFocusRect(const RECTANGLE_I32 &  rectParam)
   {
      // ASSERT(m_hdc != nullptr);
      //::DrawFocusRect(m_hdc,&rectParam);

   }


   //bool graphics::DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   //set_smooth_mode(::draw2d::smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(gl2d_pen(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

   //   return true;
   //}


   bool graphics::draw_ellipse(const ::rectangle_f64 &  rectParam)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

      //return (m_pgraphics->DrawEllipse(gl2d_pen(),rectParam.left,rectParam.top,rectParam.right - rectParam.left,rectParam.bottom - rectParam.top)) == plusplus::Status::Ok;

      return true;

   }


   //bool graphics::FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   //set_smooth_mode(::draw2d::smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(gl2d_brush(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

   //   return true;

   //}


   bool graphics::fill_ellipse(const ::rectangle_f64 &  rectParam)
   {

      //set_smooth_mode(::draw2d::smooth_mode_high);

//      return (m_pgraphics->FillEllipse(gl2d_brush(), rectParam.left, rectParam.top, rectParam.right - rectParam.left, rectParam.bottom - rectParam.top)) == plusplus::Status::Ok;

      return true;

   }


   //bool graphics::draw_ellipse(double x1,double y1,double x2,double y2)
   //{

   //   //set_smooth_mode(::draw2d::smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(gl2d_pen(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::draw_ellipse(const ::rectangle_f64 & rectectParam)
   //{

   //   //set_smooth_mode(::draw2d::smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(gl2d_pen(),(plusplus::REAL)rectParam.left,(plusplus::REAL)rectParam.top,
   //   //                                 (plusplus::REAL)(rectParam.right - rectParam.left),
   //   //                                 (plusplus::REAL)(rectParam.bottom - rectParam.top))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::FillEllipse(double x1,double y1,double x2,double y2)
   //{

   //   //set_smooth_mode(::draw2d::smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(gl2d_brush(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::FillEllipse(const ::rectangle_f64 & rectectParam)
   //{

   //   //set_smooth_mode(::draw2d::smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(gl2d_brush(),(plusplus::REAL)rectParam.left,(plusplus::REAL)rectParam.top,
   //   //                                 (plusplus::REAL)(rectParam.right - rectParam.left),
   //   //                                 (plusplus::REAL)(rectParam.bottom - rectParam.top))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   //{
   //
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::Pie(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   return false;

   //}


   //bool graphics::Pie(const RECTANGLE_I32 &  rectParam,const ::point_i32 & pointStart,const ::point_i32 & pointEnd)
   //{

   //   // ASSERT(m_hdc != nullptr);
   //   //return ::Pie(m_hdc, rectParam.left, rectParam.top,
   //   //             rectParam.right, rectParam.bottom, ptStart.x, ptStart.y,
   //   //             ptEnd.x, ptEnd.y) != false;

   //   return false;

   //}


   bool graphics::fill_polygon(const POINT_F64 * lpPoints,count nCount)
   {

      //   if(nCount <= 0)
      //      return true;

      //   bool bOk1 = false;

      //   plusplus::PointF * ppoints = new plusplus::PointF[nCount];

      //   try
      //   {

      //      for(i32 i = 0; i < nCount; i++)
      //      {
      //         ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
      //         ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
      //      }

      //      m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //      set_smooth_mode(::draw2d::smooth_mode_high);


      //      bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (::i32) nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

      //   }
      //   catch(...)
      //   {
      //   }

      //   try
      //   {
      //      delete ppoints;
      //   }
      //   catch(...)
      //   {
      //   }


      //   return bOk1;

      return true;

   }


   bool graphics::fill_polygon(const POINT_I32* lpPoints,count nCount)
   {

      //   if(nCount <= 0)
      //      return true;

      //   bool bOk1 = false;

      //   plusplus::Point * ppoints = new plusplus::Point[nCount];

      //   try
      //   {

      //      for(i32 i = 0; i < nCount; i++)
      //      {
      //         ppoints[i].X = lpPoints[i].x;
      //         ppoints[i].Y = lpPoints[i].y;
      //      }

      //      m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //      bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (::i32)  nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

      //   }
      //   catch(...)
      //   {
      //   }

      //   try
      //   {
      //      delete ppoints;
      //   }
      //   catch(...)
      //   {
      //   }


      //   return bOk1;

      return true;

   }


   bool graphics::draw_polygon(const POINT_I32* lpPoints,count nCount)
   {

      //if (nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //plusplus::Point * ppoints = new plusplus::Point[nCount];

      //try
      //{

      //   for (i32 i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   set_smooth_mode(::draw2d::smooth_mode_high);

      //   bOk1 = m_pgraphics->DrawPolygon(gl2d_pen(), ppoints, (::i32) nCount) == plusplus::Status::Ok;

      //}
      //catch (...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch (...)
      //{
      //}


      //return bOk1;
      return true;

   }


   bool graphics::draw_polygon(const POINT_F64* lpPoints,count nCount)
   {

      //if(nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //plusplus::PointF * ppoints = new plusplus::PointF[nCount];

      //try
      //{

      //   for(i32 i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
      //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   bOk1 = m_pgraphics->DrawPolygon(gl2d_pen(),ppoints,(::i32) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1;

      return true;

   }


   bool graphics::polygon_i32(const POINT_I32* lpPoints,count nCount)
   {

      //if(nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //bool bOk2 = false;

      //plusplus::Point * ppoints = new plusplus::Point[nCount];

      //try
      //{

      //   for(i32 i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x;
      //      ppoints[i].Y = lpPoints[i].y;
      //   }


      //   set_smooth_mode(::draw2d::smooth_mode_high);

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //   bOk1 = m_pgraphics->FillPolygon(gl2d_brush(), ppoints, (::i32) nCount, gl2d_get_fill_mode()) == plusplus::Status::Ok;

      //   bOk2 = m_pgraphics->DrawPolygon(gl2d_pen(), ppoints, (::i32) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1 && bOk2;

      return true;

   }


   bool graphics::poly_polygon(const POINT_I32* lpPoints, const ::i32* lpPolyCounts,count nCount)
   {

      // ASSERT(m_hdc != nullptr);


      //return ::PolyPolygon(m_hdc, lpPoints, (const ::i32 *) lpPolyCounts, (int) nCount) != false;
      return false;

   }


   //bool graphics::Rectangle(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   //plusplus::RectF rectangle_f32((plusplus::REAL) x1, (plusplus::REAL) y1, (plusplus::REAL) (x2 - x1), (plusplus::REAL) (y2 - y1));

   //   //bool bOk1 = m_pgraphics->FillRectangle(gl2d_brush(), rectangle_f32) == plusplus::Status::Ok;

   //   //bool bOk2 = m_pgraphics->DrawRectangle(gl2d_pen(), rectangle_f32) == plusplus::Status::Ok;

   //   //return bOk1 && bOk2;

   //   return true;

   //}


   bool graphics::polygon_i32(const POINT_F64* lpPoints,count nCount)
   {

      //if(nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //bool bOk2 = false;

      //plusplus::PointF * ppoints = new plusplus::PointF[nCount];

      //try
      //{

      //   for(i32 i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x;
      //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y;
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   if(m_ealphamode == ::draw2d::e_alpha_mode_set)
      //   {

      //      set_smooth_mode(::draw2d::smooth_mode_none);

      //   }
      //   else
      //   {

      //      set_smooth_mode(::draw2d::smooth_mode_high);

      //   }


      //   bOk1 = m_pgraphics->FillPolygon(gl2d_brush(),ppoints,(::i32) nCount,gl2d_get_fill_mode()) == plusplus::Status::Ok;

      //   bOk2 = m_pgraphics->DrawPolygon(gl2d_pen(),ppoints,(::i32) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1 && bOk2;

      return true;

   }

   
   bool graphics::rectangle_i32(const ::rectangle_f64 &  rectParam)
   {

      bool bOk1 = fill_rectangle(rectParam);

      bool bOk2 = draw_rectangle(rectParam);

      //return rectangle_i32(rectParam.left, rectParam.top, rectParam.right, rectParam.bottom);

      return bOk1 && bOk2;

   }


   bool graphics::draw_rectangle(const ::rectangle_f64& rectangle, ::draw2d::pen* ppen)
   {

      glLineWidth(ppen->m_dWidth);

      glBegin(GL_LINE_LOOP);
      
      ::opengl::color::color(ppen->m_color);
      
      ::opengl::vertex2f(rectangle);
      
      glEnd();

      return true;

   }


   bool graphics::draw_rectangle(const ::rectangle_f64 & rectangle)
   {

      draw_rectangle(rectangle, m_ppen);

      return true;

   }


   bool graphics::fill_rectangle(const ::rectangle_f64 & rectangle)
   {

      return fill_rectangle(rectangle, m_pbrush);

   }

   
   bool graphics::RoundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3)
   {
   
      //// ASSERT(m_hdc != nullptr);
      //return ::RoundRect(m_hdc, x1, y1, x2, y2, x3, y3) != false;

      return false;

   }


   bool graphics::RoundRect(const RECTANGLE_I32 &  rectParam,const ::point_i32 & point)
   {
      //// ASSERT(m_hdc != nullptr);
      //return ::RoundRect(m_hdc, rectParam.left, rectParam.top,
        //                 rectParam.right, rectParam.bottom, point.x, point.y) != false;

      return false;

   }


   bool graphics::PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight)
   {
      //// ASSERT(m_hdc != nullptr);
      //return ::PatBlt(m_hdc, x, y, nWidth, nHeight, dwRop) != false;

      return false;

   }


   bool graphics::BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc)
   {
//      if (m_pgraphics == nullptr)
//         return false;
//
//      if (::draw2d::graphics::BitBlt(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop))
//         return true;
//
      try
      {

         if(pgraphicsSrc == nullptr)
            return false;

         if (pgraphicsSrc->get_current_bitmap() == nullptr)
            return false;

         if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
            return false;

         __pointer(bitmap) pbitmap = pgraphicsSrc->get_current_bitmap();

         //pbitmap->create_texture(0);

         //glBegin(GL_QUADS);
         //// Front Face
         //glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
         //glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
         //glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
         //glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);


//
//
//         return m_pgraphics->DrawImage(
//                   (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),
//                   x, y, xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y, nWidth, nHeight, plusplus::UnitPixel) == plusplus::Status::Ok;
//
      }
      catch(...)
      {
         return false;
      }
//
//      //return ::BitBlt(m_hdc, x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc);
//
//gdi_fallback:
//
//      HDC hdcDst = get_hdc();
//
//      if(hdcDst == nullptr)
//         return false;
//
//      HDC hdcSrc = GL2D_GRAPHICS(pgraphicsSrc)->get_hdc();
//
//      if(hdcSrc == nullptr)
//      {
//
//         release_hdc(hdcDst);
//
//         return false;
//
//      }
//
//      bool bOk = ::BitBlt(hdcDst, x, y, nWidth, nHeight, hdcSrc, x, y, dwRop) != false;
//
//      GL2D_GRAPHICS(pgraphicsSrc)->release_hdc(hdcSrc);
//
//      release_hdc(hdcDst);
//
//      return bOk;

      return true;

   }


   bool graphics::StretchBltRaw(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   {

      //if(pgraphicsSrc == nullptr)
      //   return false;

      //plusplus::RectF dstRect((plusplus::REAL) xDst, (plusplus::REAL) yDst, (plusplus::REAL) nDstWidth, (plusplus::REAL) nDstHeight);

      //plusplus::RectF srcRect((plusplus::REAL) xSrc, (plusplus::REAL) ySrc, (plusplus::REAL) nSrcWidth, (plusplus::REAL) nSrcHeight);

      //if(pgraphicsSrc == nullptr || pgraphicsSrc->get_current_bitmap() == nullptr)
      //   return false;

      //try
      //{
      //   return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),  dstRect, srcRect, plusplus::UnitPixel) == plusplus::Status::Ok;
      //}
      //catch(...)
      //{

      //}

      //return false;

      ////return ::StretchBlt(m_hdc, x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight);

      return true;

   }


   color32_t graphics::GetPixel(i32 x, i32 y) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetPixel(m_hdc, x, y);
      return 0;

   }


   color32_t graphics::GetPixel(const ::point_i32 & point) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetPixel(m_hdc, point.x, point.y);
      return 0;

   }


   color32_t graphics::SetPixel(i32 x, i32 y, color32_t crColor)
   {
      
      return 0;

   }


   color32_t graphics::SetPixel(const ::point_i32 & point, color32_t crColor)
   {

      fill_solid_rect_coord(point.x,point.y,1,1,crColor);

      return crColor;

   }

   
//   bool graphics::FloodFill(i32 x, i32 y, color32_t crColor)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::FloodFill(m_hdc, x, y, crColor) != false;
//      return 0;
//
//   }
//
//
//   bool graphics::ExtFloodFill(i32 x, i32 y, color32_t crColor, ::u32 nFillType)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::ExtFloodFill(m_hdc, x, y, crColor, nFillType) != false;
//
//      return 0;
//
//   }


   size_i32 graphics::GetTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      // ASSERT(m_hdc != nullptr);

      return nullptr;

   }


   size_i32 graphics::GetTabbedTextExtent(const ::string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      // ASSERT(m_hdc != nullptr);

      return nullptr;

   }


   size_i32 graphics::GetOutputTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTabbedTextExtent(m_hdc, lpszString, (i32) nCount, (int) nTabPositions, lpnTabStopPositions);
      return nullptr;

   }


   size_i32 graphics::GetOutputTabbedTextExtent(const ::string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTabbedTextExtent(m_hdc, str, (i32) str.get_length(), (int) nTabPositions, lpnTabStopPositions);
      return nullptr;

   }


   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount,i32 x, i32 y, i32 nWidth, i32 nHeight)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GrayString(m_hdc, (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != false;
      return false;

   }


   ::u32 graphics::GetTextAlign()
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTextAlign(m_hdc);
      return 0;

   }


   i32 graphics::GetTextFace(count nCount, char * lpszFacename)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTextFace(m_hdc, (int) nCount, lpszFacename);
      return -1;

   }


   i32 graphics::GetTextFace(string & rString)
   {

      // ASSERT(m_hdc != nullptr);

      //i32 nResult = ::GetTextFace(m_hdc, 256, rString.GetBuffer(256));
      //rString.ReleaseBuffer();

      //return nResult;
      return -1;

   }


   bool graphics::get_text_metrics(::write_text::text_metric * lpMetrics)
   {

      if (!set(m_pfont))
      {

         return false;

      }

      __pointer(font) pfont = m_pfont;

      TEXTMETRIC tm;

      GetTextMetrics(pfont->m_hdcFont, &tm);

      lpMetrics->tmAscent = tm.tmAscent;
      lpMetrics->tmHeight = tm.tmHeight;
      lpMetrics->tmDescent = tm.tmDescent;
      //lpMetrics->tmAveCharWidth = tm.tmAveCharWidth;

      //if (m_pgraphics == nullptr)
      //   return false;

      //graphics * pgraphics = ((graphics *)this);

      //if(pgraphics->gl2d_font() == nullptr)
      //   return false;

      //plusplus::Font * pfont = pgraphics->gl2d_font();

      //plusplus::FontFamily family;

      //pfont->GetFamily(&family);

      //::i32 iStyle = pfont->GetStyle();

      //double dHeight = family.GetEmHeight(iStyle);

      //double dSize = pfont->GetSize();

      //double dFontHeight = pfont->GetHeight((plusplus::REAL) pgraphics->get_dpiy());

      //lpMetrics->tmAscent              = (::i32) (dSize * family.GetCellAscent(iStyle) / dHeight);
      //lpMetrics->tmDescent             = (::i32) (dSize * family.GetCellDescent(iStyle) / dHeight);
      //lpMetrics->tmHeight              = (::i32)dFontHeight;

      //double dLineSpacing = maximum(dFontHeight, dSize * family.GetLineSpacing(iStyle) / dHeight);

      //lpMetrics->tmInternalLeading     = (::i32) (lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight);
      //lpMetrics->tmExternalLeading     = (::i32) (dLineSpacing - (lpMetrics->tmAscent + lpMetrics->tmDescent));

      //const plusplus::FontFamily * pfamilyMono = family.GenericMonospace();

      //::plusplus::Font font2(pfamilyMono, pfamilyMono->GetEmHeight(((graphics * )this)->gl2d_font()->GetStyle()));

      //wstring wstr(L"123AWZwmc123AWZwmcpQg");
      //plusplus::RectF rectangle_i32(0.f, 0.f, 1024.f * 1024.f, 1024.f * 1024.f);
      //plusplus::RectF rect2;
      //plusplus::PointF origin(0, 0);

      //m_pgraphics->MeasureString(wstr, (::i32) wstr.get_length(), ((graphics * )this)->gl2d_font(), origin, &rectangle);


      ///*wstr = L"";
      //m_pgraphics->MeasureString(wstr.m_pwsz, -1, (plusplus::Font *) m_font->get_os_data(), origin, &rect2);*/

      //lpMetrics->tmAveCharWidth = (::i32) (rectangle.Width * get_current_font()->m_dFontWidth / (double) wstr.get_length());

      return true;

   }


   bool graphics::get_output_text_metrics(::write_text::text_metric * lpMetrics)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTextMetricsW(m_hdc, lpMetrics) != false;

      //::exception::throw_not_implemented();

      return false;

   }


   i32 graphics::GetTextCharacterExtra()
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetTextCharacterExtra(m_hdc);
      return 0;

   }


   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharWidth(m_hdc, nFirstChar, nLastChar, lpBuffer) != false;

      return false;

   }


   bool graphics::GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharWidth(m_hdc, nFirstChar, nLastChar, lpBuffer) != false;
      return false;

   }


   u32 graphics::GetFontLanguageInfo() const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetFontLanguageInfo(m_hdc);

      return 0;

   }


   u32 graphics::GetCharacterPlacement(const ::string & lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const
   {

      // ASSERT(m_hdc != nullptr);

      // return ::GetCharacterPlacement(m_hdc, lpString, (int)nCount, (int)nMaxExtent, lpResults, dwFlags);
      return false;

   }


   u32 graphics::GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetCharacterPlacement(m_hdc, (const ::string &)str, (i32) str.get_length(), (int) nMaxExtent, lpResults, dwFlags);
      return false;

   }


   size_i32 graphics::GetAspectRatioFilter() const
   {
      // ASSERT(m_hdc != nullptr);
      ::size_i32 size;
      // VERIFY(::GetAspectRatioFilterEx(m_hdc, &size));
      return size;

   }


   bool graphics::ScrollDC(i32 dx, i32 dy,
                           const RECTANGLE_I32 &  lpRectScroll,const RECTANGLE_I32 &  rectClip,
                           ::draw2d::region* pRgnUpdate, RECTANGLE_I32 * lpRectUpdate)
   {
      
      // ASSERT(m_hdc != nullptr);
      //return ::ScrollDC(m_hdc,dx,dy,&rectClip,
        //                &rectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != false;
      return 0;

   }


   // Printer Escape Functions
   i32 graphics::Escape(i32 nEscape, i32 nCount, const ::string & lpszInData, LPVOID lpOutData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::Escape(m_hdc, nEscape, nCount, lpszInData, lpOutData);
      return 0;

   }


   // graphics 3.1 Specific functions
   ::u32 graphics::SetBoundsRect(const RECTANGLE_I32 &  rectBounds, ::u32 flags)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetBoundsRect(m_hdc, &rectBounds, flags);
      return 0;

   }


   ::u32 graphics::GetBoundsRect(RECTANGLE_I32 * rectBounds, ::u32 flags)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetBoundsRect(m_hdc, rectBounds, flags);
      return 0;

   }


   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::ResetDC(m_hdc, lpDevMode) != nullptr;
      return false;

   }


   ::u32 graphics::GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetOutlineTextMetricsW(m_hdc, cbData, lpotm);
      return 0;
   }


   bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharABCWidths(m_hdc, nFirstChar, nLastChar, lpabc) != false;
      return false;

   }


   u32 graphics::GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData,
                                  u32 cbData) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetFontData(m_hdc, dwTable, dwOffset, lpData, cbData);
      return 0;

   }


   i32 graphics::GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetKerningPairs(m_hdc, nPairs, lpkrnpair);
      return 0;

   }


   //u32 graphics::GetGlyphOutline(::u32 nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS lpgm,
   //                                   u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetGlyphOutline(m_hdc, nChar, nFormat,
   //     //                       lpgm, cbBuffer, lpBuffer, lpmat2);
   //   return 0;

   //}


   // ::user::document handling functions
   i32 graphics::StartDoc(LPDOCINFO lpDocInfo)
   {

      ASSERT(m_hdc != nullptr);

      //return ::StartDoc(m_hdc, lpDocInfo);
      return 0;

   }


   i32 graphics::StartPage()
   {

      //ASSERT(m_hdc != nullptr);

      //::StartPage(m_hdc);

      //m_pgraphics = new plusplus::Graphics(m_hdc);

      //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

      return 1;

   }


   i32 graphics::EndPage()
   {

      /* ASSERT(m_hdc != nullptr);

       delete m_pgraphics;

      */
      //return ::EndPage(m_hdc);
      return 0;

   }


   i32 graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32))
   {

      ASSERT(m_hdc != nullptr);

      //return ::SetAbortProc(m_hdc, (ABORTPROC)lpfn);
      return 0;

   }


   i32 graphics::AbortDoc()
   {

      ASSERT(m_hdc != nullptr);

      //return ::AbortDoc(m_hdc);
      return 0;

   }


   i32 graphics::EndDoc()
   {

      ASSERT(m_hdc != nullptr);

      //return ::EndDoc(m_hdc);
      return 0;

   }


//   bool graphics::MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                          i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::MaskBlt(m_hdc, x, y, nWidth, nHeight, GL2D_HDC(pgraphicsSrc),
//        //               xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;
//      return 0;
//
//   }
//
//
//   bool graphics::PlgBlt(POINT_I32 * lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
//                         i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask)
//   {
//
//      /*try
//      {
//
//         if(pgraphicsSrc == nullptr)
//            return false;
//
//         if(pgraphicsSrc->get_current_bitmap() == nullptr)
//            return false;
//
//         if(pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
//            return false;
//
//         plusplus::Point p[3];
//
//         p[0].X = lpPoint[0].x;
//         p[0].Y = lpPoint[0].y;
//         p[1].X = lpPoint[1].x;
//         p[1].Y = lpPoint[1].y;
//         p[2].X = lpPoint[2].x;
//         p[2].Y = lpPoint[2].y;
//
//         return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), p, 3) == plusplus::Status::Ok;
//
//      }
//      catch(...)
//      {
//         return false;
//      }
//      */
//      return true;
//
//   }



   bool graphics::SetPixelV(i32 x, i32 y, color32_t crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetPixelV(m_hdc, x, y, crColor) != false;
      return 0;

   }


   bool graphics::SetPixelV(const ::point_i32 & point, color32_t crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetPixelV(m_hdc, point.x, point.y, crColor) != false;
      return 0;

   }


   bool graphics::AngleArc(i32 x, i32 y, i32 nRadius, float fStartAngle, float fSweepAngle)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::AngleArc(m_hdc, x, y, nRadius, fStartAngle, fSweepAngle) != false;
      return 0;

   }



   bool graphics::ArcTo(const RECTANGLE_I32 &  rectParam,const ::point_i32 & pointStart,const ::point_i32 & pointEnd)
   {
      // ASSERT(m_hdc != nullptr);
      //return ArcTo(rectParam.left, rectParam.top, rectParam.right,
        //           rectParam.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

      return false;

   }


   i32 graphics::GetArcDirection() const
   {
      // ASSERT(m_hdc != nullptr);
      // return ::GetArcDirection(m_hdc);
      return 0;

   }


   bool graphics::poly_polyline(const POINT_I32* lpPoints, const ::i32 * lpPolyPoints, count nCount)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::poly_polyline(m_hdc, lpPoints, (LPDWORD) lpPolyPoints, (::u32) nCount) != false;
      return false;

   }


   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetColorAdjustment(m_hdc, lpColorAdjust) != false;
      return false;

   }


   ::draw2d::pen_pointer graphics::get_current_pen() const
   {

      return m_ppen;

   }

   ::draw2d::brush_pointer graphics::get_current_brush() const
   {

      return m_pbrush;

   }

   ::draw2d::palette_pointer graphics::get_current_palette() const
   {

      return (::draw2d::palette *)nullptr;

   }

   ::write_text::font_pointer graphics::get_current_font() const
   {

      return m_pfont;

   }

   ::draw2d::bitmap_pointer graphics::get_current_bitmap() const
   {

      return m_pbitmap;

   }


   bool graphics::poly_bezier(const POINT_I32* lpPoints, count nCount)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::poly_bezier(m_hdc, lpPoints, (::u32) nCount) != false;
      return false;

   }


   i32 graphics::DrawEscape(i32 nEscape, i32 nInputSize, const ::string & lpszInputData)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::DrawEscape(m_hdc, nEscape, nInputSize, lpszInputData);
      return 0;


   }


   i32 graphics::Escape(__in i32 nEscape, __in i32 nInputSize, __in_bcount(nInputSize) const char * lpszInputData,  __in i32 nOutputSize, __out_bcount(nOutputSize) char * lpszOutputData)
   {
      // ASSERT(m_hdc != nullptr);
      return ::ExtEscape(m_hdc, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
      return 0;

   }


   bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
                                   LPABCFLOAT lpABCF) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharABCWidthsFloat(m_hdc, nFirstChar, nLastChar, lpABCF) != false;
      return false;
   }


   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float* lpFloatBuffer) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharWidthFloat(m_hdc, nFirstChar, nLastChar, lpFloatBuffer) != false;
      return false;

   }


   bool graphics::AbortPath()
   {
      //if(m_ppath != nullptr)
      //{
      //   delete m_ppath;
      //   m_ppath = nullptr;
      //}
      return true;

   }


   bool graphics::BeginPath()
   {

      /*     if(m_ppath != nullptr)
              delete m_ppath;

           m_ppath = new plusplus::GraphicsPath;
      */
//      return m_ppath != nullptr;

      return true;

   }


   bool graphics::CloseFigure()
   {
      //ASSERT(m_ppath != nullptr);
      //return m_ppath->CloseFigure() == plusplus::Status::Ok;
      return true;

   }


   bool graphics::EndPath()
   {

      //if(m_ppath == nullptr)
      //   return false;

      //m_ppathPaint   = m_ppath;
      //m_ppath        = nullptr;

      return true;

   }


   bool graphics::FillPath()
   {

      //return m_pgraphics->FillPath(gl2d_brush(), m_ppath) == plusplus::Status::Ok;
      return true;

   }


   bool graphics::FlattenPath()
   {
//      return m_ppath->Flatten() == plusplus::Status::Ok;
      return true;

   }


   float graphics::GetMiterLimit() const
   {
      // ASSERT(m_hdc != nullptr);
      float fMiterLimit;
      VERIFY(::GetMiterLimit(m_hdc, &fMiterLimit));
      return fMiterLimit;
   }


   i32 graphics::GetPath(POINT_I32 * lpPoints, byte * lpTypes, count nCount) const
   {

      // ASSERT(m_hdc != nullptr);

      return ::GetPath(m_hdc, lpPoints, lpTypes, (int) nCount);

   }


   bool graphics::SetMiterLimit(float fMiterLimit)
   {
      // ASSERT(m_hdc != nullptr);
      return ::SetMiterLimit(m_hdc, fMiterLimit, nullptr) != false;

   }


   bool graphics::StrokeAndFillPath()
   {

      //bool bOk1 = m_pgraphics->FillPath(gl2d_brush(), m_ppathPaint) == plusplus::Status::Ok;

      //bool bOk2 = m_pgraphics->DrawPath(gl2d_pen(), m_ppathPaint) == plusplus::Status::Ok;

      //return bOk1 && bOk2;

      return true;

   }


   bool graphics::StrokePath()
   {

//      return m_pgraphics->DrawPath(gl2d_pen(), m_ppathPaint) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::WidenPath()
   {

      //return m_ppath->Widen(gl2d_pen()) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      //m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeAntiAlias);
      //m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //return m_pgraphics->DrawPath(gl2d_pen(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;
      return true;

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      //return m_pgraphics->DrawPath((::plusplus::Pen *) ppen->get_os_data(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {

      //return m_pgraphics->FillPath(gl2d_brush(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      //return m_pgraphics->FillPath((::plusplus::Brush *) pbrush->get_os_data(),(dynamic_cast < ::draw2d_opengl::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      return true;

   }


   bool graphics::AddMetaFileComment(::u32 nDataSize, const byte* pCommentData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GdiComment(m_hdc, nDataSize, pCommentData) != false;
      return false;

   }


   /*bool CALLBACK metaCallback(
      EmfPlusRecordType recordType,
      u32 flags,
      u32 dataSize,
      const uchar* pStr,
      void* callbackData)
   {
      // Play only EmfPlusRecordTypeFillEllipse records.
      if (recordType == EmfPlusRecordTypeFillEllipse)
      {
      // Explicitly cast callbackData as a metafile pointer, and use it to call
      // the PlayRecord method.
      static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
      }
      return true;
   }

   VOID Example_EnumerateMetafile9(HDC hdc)
   {
      Graphics graphics(hdc);
      // Create a Metafile object from an existing disk metafile.
      Metafile* pMeta = new Metafile(L"SampleMetafile.emf", hdc);
      {
         // Fill a rectangle_i32 and an ellipse in pMeta.
         Graphics metaGraphics(pMeta);
         metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
     metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
      }
      // Enumerate pMeta to the destination rectangle, passing pMeta as the callback data.
      graphics.EnumerateMetafile(
      pMeta,
      Rect(0, 0, 300, 50),
      metaCallback,
      pMeta);
      // Draw pMeta as an pimage->
      graphics.DrawImage(pMeta, Point(0, 150));
      delete pMeta;;
   }*/
   
   
   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const RECTANGLE_I32 &  rectBounds)
   {

      //plusplus::RectF rectangle_i32((plusplus::REAL) rectBounds.left,(plusplus::REAL) rectBounds.top,(plusplus::REAL) width(rectBounds),(plusplus::REAL) height(rectBounds));

      //plusplus::Metafile* pMeta = new plusplus::Metafile(hEnhMF, false);

      ////m_pgraphcis->EnumerateMetafile(pMeta, rectangle, metaCallback, PMETAHEADER);

      //bool bOk = m_pgraphics->DrawImage(pMeta, rectangle) == plusplus::Status::Ok;

      //delete pMeta;

      //return bOk ? true : false;
      //return ::PlayEnhMetaFile(m_hdc, hEnhMF, lpBounds);

      return true;

   }

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

// Thank you
// Jiju George T
// Web Developer
// India India
// Member

   bool graphics::alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate)
   {

//      if (m_pgraphics == nullptr)
//         return false;
//
//      if(m_pimageAlphaBlend->is_set())
//      {
//
//
//         ::rectangle_i32 rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
//
//
//         ::image_pointer pimageWork = nullptr;
//         ::image_pointer pimageWork2 = nullptr;
////         ::image_pointer pimageWork3 = nullptr;
//         ::image_pointer pimageWork4 = nullptr;
//
//
//         ::point_i32 pointSrc(xSrc, ySrc);
//         ::point_i32 ptDest(xDest, yDest);
//         ::size_i32 size(nDestWidth, nDestHeight);
//
//
//
//         ::image_pointer pimage;
//         if(imageWork == nullptr)
//         {
//            pimage->create(this);
//            imageWork = pimage;
//         }
//         if(imageWork == nullptr)
//            return false;
//         if(!imageWork = create_image(size))
//            return false;
//         if(!imageWork.from(::point_i32(), pgraphicsSrc, pointSrc, size))
//            return false;
//
//
//
//
//         ::image_pointer pimage2;
//         if(imageWork2 == nullptr)
//         {
//            pimage2->create(this);
//            imageWork2 = pimage2;
//         }
//
//
//         ::image_pointer pimage4;
//         if(imageWork4 == nullptr)
//         {
//            image4.create(this);
//            imageWork4 = image4;
//         }
//         if(imageWork4 == nullptr)
//            return false;
//         if(!imageWork4 = create_image(size))
//            return false;
//
//
//         imageWork4.Fill(255, 0, 0, 0);
//
//         imageWork4.from(point_i32(maximum(0, m_pointAlphaBlend.x - xDest), maximum(0, m_pointAlphaBlend.y - yDest)),
//                         m_pimageAlphaBlend->get_graphics(), point_i32(maximum(0, xDest - m_pointAlphaBlend.x), maximum(0, yDest - m_pointAlphaBlend.y)), size);
//
//         imageWork.channel_multiply(::color::e_channel_alpha, imageWork4);
//
//
//         keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);
//
//
//         return BitBlt(ptDest.x, ptDest.y, size.cx, size.cy, imageWork.get_graphics(), pointSrc.x, pointSrc.y);
//
//
//      }
//
//
//      float fA = (float) dRate;
//
//      plusplus::ColorMatrix matrix = {
//         1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//         0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//         0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//         0.0f, 0.0f, 0.0f, fA  , 0.0f,
//         0.0f, 0.0f, 0.0f, 0.0f, 1.0f
//      };
//
//      plusplus::ImageAttributes attributes;
//
//      attributes.SetColorMatrix(&matrix, plusplus::ColorMatrixFlagsDefault, plusplus::ColorAdjustTypeBitmap);
//
//      plusplus::RectF dstRect((plusplus::REAL) xDest, (plusplus::REAL) yDest, (plusplus::REAL) nDestWidth, (plusplus::REAL) nDestHeight);
//
//      if(pgraphicsSrc == nullptr)
//         return false;
//
//      if(pgraphicsSrc->get_current_bitmap() == nullptr)
//         return false;
//
//      plusplus::Bitmap * pbitmap = nullptr;
//
//      try
//      {
//
//         pbitmap = (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();
//
//      }
//      catch(...)
//      {
//      }
//
//      if(pbitmap != nullptr)
//      {
//
//         m_pgraphics->DrawImage(pbitmap,dstRect,(plusplus::REAL) xSrc,(plusplus::REAL) ySrc,(plusplus::REAL) nSrcWidth,(plusplus::REAL) nSrcHeight,plusplus::UnitPixel,&attributes);
//
//      }
//
      return true;

   }


   /*bool graphics::alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, BLENDFUNCTION blend)
   {

      ::exception::throw_not_implemented();
      //if(m_hdc == nullptr)
        // return false;


      if(m_pimageAlphaBlend->is_set())
      {


         ::rectangle_i32 rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


         ::image_pointer pimageWork = nullptr;
         ::image_pointer pimageWork2 = nullptr;
   //         ::image_pointer pimageWork3 = nullptr;
         ::image_pointer pimageWork4 = nullptr;


         ::point_i32 pointSrc(xSrc, ySrc);
         ::point_i32 ptDest(xDest, yDest);
         ::size_i32 size(nDestWidth, nDestHeight);



         ::image_pointer pimage;
         if(imageWork == nullptr)
         {
            pimage->create(this);
            imageWork = pimage;
         }
         if(imageWork == nullptr)
            return false;
         if(!imageWork = create_image(size))
            return false;
         if(!imageWork.from(::point_i32(), pgraphicsSrc, pointSrc, size))
            return false;




         ::image_pointer pimage2;
         if(imageWork2 == nullptr)
         {
            pimage2->create(this);
            imageWork2 = pimage2;
         }


         ::image_pointer pimage4;
         if(imageWork4 == nullptr)
         {
            image4.create(this);
            imageWork4 = image4;
         }
         if(imageWork4 == nullptr)
            return false;
         if(!imageWork4 = create_image(size))
            return false;


         imageWork4.Fill(255, 0, 0, 0);

         imageWork4.from(point_i32(maximum(0, m_pointAlphaBlend.x - xDest), maximum(0, m_pointAlphaBlend.y - yDest)),
            m_pimageAlphaBlend->get_graphics(), point_i32(maximum(0, xDest - m_pointAlphaBlend.x), maximum(0, yDest - m_pointAlphaBlend.y)), size);

         imageWork.channel_multiply(::color::e_channel_alpha, imageWork4);


         keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


         return psystem->imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), pointSrc);


      }

      return ::AlphaBlend(m_hdc, xDest, yDest,
         nDestWidth, nDestHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
         nSrcHeight, blend) != false;
   }*/


   bool graphics::TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, ::u32 crTransparent)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::TransparentBlt(m_hdc, xDest, yDest,  nDestWidth, nDestHeight, GL2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,  nSrcHeight, crTransparent) != false;

      return true;

   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, u32 dwMode)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GradientFill(m_hdc, pVertices, nVertices, pMesh, nMeshElements, dwMode) != false;

      return true;

   }

   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //

   // Always Inline. Functions only in Win98/Win2K or later

   inline color32_t graphics::GetDCBrushColor() const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetDCBrushColor(m_hdc);
      return 0;
   }


   inline color32_t graphics::SetDCBrushColor(color32_t crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetDCBrushColor(m_hdc, crColor);
      return 0;

   }


   inline color32_t graphics::GetDCPenColor() const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetDCPenColor(m_hdc);
      return 0;


   }


   inline color32_t graphics::SetDCPenColor(color32_t crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetDCPenColor(m_hdc, crColor);
      return 0;

   }


   inline bool graphics::GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharABCWidthsI(m_hdc, giFirst, cgi, pgi, lpabc) != false;
      return false;

   }


   inline bool graphics::GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharWidthI(m_hdc, giFirst, cgi, pgi, lpBuffer) != false;
      return false;

   }


   //inline bool graphics::GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE32 LPSIZE32) const
   //{
   //   ENSURE(LPSIZE32 != nullptr);
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextExtentExPointI(m_hdc, pgiIn, cgi, nMaxExtent, lpnFit, alpDx, LPSIZE32) != false;
   //   return false;

   //}


   //inline bool graphics::GetTextExtentPointI(LPWORD pgiIn, i32 cgi, LPSIZE32 LPSIZE32) const
   //{
   //   ENSURE(LPSIZE32 != nullptr);
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextExtentPointI(m_hdc, pgiIn, cgi, LPSIZE32) != false;
   //   return false;

   //}


#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE32 LPSIZE32) const
   {
//      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));
//
//      i32 nMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained map mode, map against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         DPtoLP(LPSIZE32);
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         // map against logical inch for non-constrained mapping modes
//         i32 cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_VALID(this);
//            // ASSERT(m_hdc != nullptr);  // no HDC attached or created?
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {
////            cxPerInch = afxData.cxPixelsPerInch;
//            //          cyPerInch = afxData.cyPixelsPerInch;
//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         LPSIZE32->cx = MulDiv(LPSIZE32->cx, HIMETRIC_INCH, cxPerInch);
//         LPSIZE32->cy = MulDiv(LPSIZE32->cy, HIMETRIC_INCH, cyPerInch);
//      }
   }


   void graphics::HIMETRICtoDP(LPSIZE32 LPSIZE32) const
   {
//      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));
//
//      i32 nMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained map mode, map against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         LPtoDP(LPSIZE32);
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         // map against logical inch for non-constrained mapping modes
//         i32 cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_VALID(this);
//            // ASSERT(m_hdc != nullptr);  // no HDC attached or created?
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {
////            cxPerInch = afxData.cxPixelsPerInch;
//            //          cyPerInch = afxData.cyPixelsPerInch;
//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         LPSIZE32->cx = MulDiv(LPSIZE32->cx, cxPerInch, HIMETRIC_INCH);
//         LPSIZE32->cy = MulDiv(LPSIZE32->cy, cyPerInch, HIMETRIC_INCH);
//      }
   }


   void graphics::LPtoHIMETRIC(LPSIZE32 LPSIZE32) const
   {
      //ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));

      //LPtoDP(LPSIZE32);
      //DPtoHIMETRIC(LPSIZE32);
   }


   void graphics::HIMETRICtoLP(LPSIZE32 LPSIZE32) const
   {
      //ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));

      //HIMETRICtoDP(LPSIZE32);
      //DPtoLP(LPSIZE32);

   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* graphics::GetHalftoneBrush(::object * pobject)
   {
      /*      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
            if (gen_HalftoneBrush == nullptr)
            {
               ::u16 grayPattern[8];
               for (i32 i = 0; i < 8; i++)
                  grayPattern[i] = (::u16)(0x5555 << (i & 1));
               HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
               if (grayBitmap != nullptr)
               {
                  gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
                  ::DeleteObject(grayBitmap);
               }
            }
            if (!gen_WingdixTerm)
               gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
            ::aura::UnlockGlobals(CRIT_HALFTONEBRUSH);

      //      return ::draw2d_opengl::brush::from_handle(papp, gen_HalftoneBrush);*/
      return nullptr;
   }

   void graphics::DrawDragRect(const RECTANGLE_I32 &  rectangle, const ::size_i32 & size, const RECTANGLE_I32 &  lpRectLast, const ::size_i32 & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {

      ::exception::throw_not_implemented();

      /*

            ASSERT(__is_valid_address(rectangle, sizeof(RECTANGLE_I32), false));
            ASSERT(lpRectLast == nullptr ||
               __is_valid_address(lpRectLast, sizeof(RECTANGLE_I32), false));

            // first, determine the update region and select it
            ::draw2d::region rgnNew;
            ::draw2d::region rgnOutside, rgnInside;
            rgnOutside.create_rect(rectangle);
            const ::rectangle_i32 & rectangle = *rectangle;
            rectangle.inflate(-size.cx, -size.cy);
            rectangle.intersect(rectangle, rectangle);
            rgnInside.create_rect(rectangle);
            rgnNew.create_rect(0, 0, 0, 0);
            rgnNew.combine(&rgnOutside, &rgnInside, RGN_XOR);

            ::draw2d::brush* pBrushOld = nullptr;
            if (pBrush == nullptr)
            {
               pBrush = graphics::GetHalftoneBrush(this);
            }

            ENSURE(pBrush);

            if (pBrushLast == nullptr)
            {
               pBrushLast = pBrush;
            }

            ::draw2d::region rgnLast, rgnUpdate;
            if (lpRectLast != nullptr)
            {
               // find difference between new region and old region
               rgnLast.create_rect(0, 0, 0, 0);
               rgnOutside.SetRectRgn(lpRectLast);
               rectangle = *lpRectLast;
               rectangle.inflate(-sizeLast.cx, -sizeLast.cy);
               rectangle.intersect(rectangle, lpRectLast);
               rgnInside.SetRectRgn(rectangle);
               rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

               // only diff them if brushes are the same
               if (pBrush->get_os_data() == pBrushLast->get_os_data())
               {
                  rgnUpdate.create_rect(0, 0, 0, 0);
                  rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
               }
            }
            if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != nullptr)
            {
               // brushes are different -- erase old region first
               SelectClipRgn(&rgnLast);
               get_clip_box(&rectangle);
               pBrushOld = SelectObject(pBrushLast);
               PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);
               SelectObject(pBrushOld);
               pBrushOld = nullptr;
            }

            // draw into the update/new region
            SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
            get_clip_box(&rectangle);
            pBrushOld = SelectObject(pBrush);
            PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);

            // cleanup DC
            if (pBrushOld != nullptr)
               SelectObject(pBrushOld);
            SelectClipRgn(nullptr);

      */
   }

   /*void graphics::FillSolidRect(const RECTANGLE_I32 &  rectangle, color32_t clr)
   {
      ::SetBkColor(m_hdc, clr);
      ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, rectangle, nullptr, 0, nullptr);
   }*/

   /*void graphics::fill_rectangle(const rectangle_f64 & rectangle, color32_t clr)
   {
      ::rectangle_i32 rect32;
      __copy(rect32, rectangle);
      FillSolidRect(rect32, clr);
   }
*/

   /*

   void graphics::FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, color32_t clr)
   {
      ::SetBkColor(m_hdc, clr);
      ::rectangle_i32 rectangle(x, y, x + cx, y + cy);
      ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, &rectangle, nullptr, 0, nullptr);
   }

   */

   void graphics::Draw3dRect(const RECTANGLE_I32 &  rectParam,
                             color32_t clrTopLeft, color32_t clrBottomRight)
   {
      Draw3dRect(rectParam.left, rectParam.top, rectParam.right - rectParam.left,
                 rectParam.bottom - rectParam.top, clrTopLeft, clrBottomRight);
   }

   void graphics::Draw3dRect(i32 x, i32 y, i32 cx, i32 cy,
                             color32_t clrTopLeft, color32_t clrBottomRight)
   {
      fill_solid_rect_coord(x, y, cx - 1, 1, clrTopLeft);
      fill_solid_rect_coord(x, y, 1, cy - 1, clrTopLeft);
      fill_solid_rect_coord(x + cx - 1, y, 1, cy, clrBottomRight);
      fill_solid_rect_coord(x, y + cy - 1, cx, 1, clrBottomRight);
   }





   //::draw2d::graphics * ::draw2d_opengl::graphics::from_handle(HDC hDC)
   //{
   //hdc_map* pMap = afxMapHDC(true); //create map if not exist
   //ASSERT(pMap != nullptr);
//      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)pMap->from_handle(hDC);
   //    ASSERT(pgraphics == nullptr || (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->m_hdc == hDC);
   //  return pgraphics;
   // return nullptr;
   //}

   bool graphics::Attach(HDC hdc)
   {

      //if(hdc == nullptr)
      //   return false;

      //if(m_hdc == hdc)
      //{

      //   if(m_pgraphics != nullptr)
      //      return true;

      //}

      //if(hdc != nullptr)
      //{

      //   m_pgraphics = new ::plusplus::Graphics((HDC) hdc);

      //   m_pgraphics->SetPageUnit(plusplus::UnitPixel);

      //   set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      //   m_hdc = (HDC) hdc;

      //}

      //return m_pgraphics != nullptr;

      return true;

      /*ASSERT(m_hdc == nullptr);      // only attach once, detach on destroy
      ASSERT(m_hdc == nullptr);    // only attach to an is_empty DC

      if (hDC == nullptr)
      {
         return false;
      }
      // remember early to avoid leak
      set_handle1(hDC);
      hdc_map* pMap = afxMapHDC(true); // create map if not exist
      ASSERT(pMap != nullptr);
      pMap->set_permanent(m_hdc, this);

      SetAttribDC(m_hdc);     // Default to same as output
      return true;*/
   }

   HDC graphics::Detach()
   {

      //if(m_hdc == nullptr)
      //   return nullptr;

      //if(m_pgraphics == nullptr)
      //   return nullptr;

      //try
      //{

      //   delete m_pgraphics;

      //}
      //catch(...)
      //{

      //   TRACE("graphics::Detach : Failed to delete plusplus::Graphics");

      //}

      //m_pgraphics = nullptr;

      //HDC hdc = m_hdc;
      //m_hdc = nullptr;

      //return hdc;

      return nullptr;

   }


   bool graphics::AttachPrinter(HDC hdc)
   {

      //if (hdc == nullptr)
      //   return false;

      //if (m_hdc == hdc)
      //{

      //   return true;

      //}

      //if (hdc != nullptr)
      //{

      //   m_hdc = (HDC)hdc;

      //}

      //return m_hdc != nullptr;

      return true;

   }


   HDC graphics::DetachPrinter()
   {

      //if (m_hdc == nullptr)
      //   return nullptr;

      //HDC hdc = m_hdc;

      //m_hdc = nullptr;

      //return hdc;

      return nullptr;

   }


   bool graphics::DeleteDC()
   {



      //HDC hdc = Detach();

      //if(hdc != nullptr)
      //{

      //   bool bDeleted = ::DeleteDC(hdc) != false;

      //   if(!bDeleted)
      //   {

      //      TRACE("graphics::DeleteDC : Failed to delete GDI device context");

      //   }

      //}

      //if(m_pgraphics != nullptr)
      //{

      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      TRACE("graphics::DeleteDC : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = nullptr;

      //}

      //if(m_ppath != nullptr)
      //{

      //   try
      //   {

      //      delete m_ppath;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppath = nullptr;

      //}

      //if(m_ppathPaint != nullptr)
      //{

      //   try
      //   {

      //      delete m_ppathPaint;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppathPaint = nullptr;

      //}

      if (m_hdc != nullptr)
      {

         //::ReleaseDC(m_hwnd, m_hdc);

      }

      return true;

   }


   void graphics::SetAttribDC(HDC hDC)  // set the Attribute DC
   {
//      set_handle2(hDC);
   }


   void graphics::SetOutputDC(HDC hDC)  // set the Output DC
   {
#ifdef _DEBUG
      /*      hdc_map* pMap = afxMapHDC();
            if (pMap != nullptr && pMap->lookup_permanent(m_hdc) == this)
            {
               TRACE(trace_category_appmsg, 0, "Cannot set Output hDC on Attached graphics.\n");
               ASSERT(false);
            }*/
#endif
      //    set_handle1(hDC);
   }


   void graphics::ReleaseAttribDC()     // Release the Attribute DC
   {
//      set_handle2(nullptr);
   }


   void graphics::ReleaseOutputDC()     // Release the Output DC
   {
#ifdef _DEBUG
      /*      hdc_map* pMap = afxMapHDC();
            if (pMap != nullptr && pMap->lookup_permanent(m_hdc) == this)
            {
               TRACE(trace_category_appmsg, 0, "Cannot Release Output hDC on Attached graphics.\n");
               ASSERT(false);
            }*/
#endif
      //set_handle1(nullptr);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   i32 graphics::StartDoc(const ::string & lpszDocName)
   {
      //DOCINFO di;
      //__memset(&di, 0, sizeof(DOCINFO));
      //di.cbSize = sizeof(DOCINFO);
      //di.lpszDocName = lpszDocName;
      //return StartDoc(&di);
      return -1;
   }

   i32 graphics::SaveDC()
   {
//      return m_pgraphics->Save();
      return 0;
   }

   bool graphics::RestoreDC(i32 nSavedDC)
   {

      //return m_pgraphics->Restore(nSavedDC) != false;
      return true;

   }

//   ::draw2d::object* graphics::SelectGdiObject(::object * pobject, HDC hDC, HGDIOBJ h)
   // {
//      return ::draw2d_opengl::object::from_handle(papp, ::SelectObject(hDC, h));
   //}


   ::draw2d::object* graphics::SelectStockObject(i32 nIndex)
   {
      /*      HGDIOBJ hObject = ::GetStockObject(nIndex);
            HGDIOBJ hOldObj = nullptr;
            ASSERT(hObject != nullptr);
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, hObject);
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, hObject);
            return ::draw2d_opengl::object::from_handle(get_application(), hOldObj);*/

      return nullptr;

   }


   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* pPen)
   {
      /*HGDIOBJ hOldObj = nullptr;
      if(pPen == nullptr)
         return nullptr;
      if(m_hdc != nullptr && m_hdc != m_hdc)
         hOldObj = ::SelectObject(m_hdc, pPen->get_os_data());
      if(m_hdc != nullptr)
         hOldObj = ::SelectObject(m_hdc, pPen->get_os_data());
      return dynamic_cast < pen * > (::draw2d_opengl::object::from_handle(get_application(), hOldObj));*/
      m_ppen = pPen;
      return m_ppen;

   }


   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pBrush)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pBrush == nullptr)
               return nullptr;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, pBrush->get_os_data());
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, pBrush->get_os_data());
            return dynamic_cast < ::draw2d::brush * > (::draw2d_opengl::object::from_handle(get_application(), hOldObj));*/
      m_pbrush = pBrush;

      return m_pbrush;

   }


   ::write_text::font* graphics::SelectObject(::write_text::font* pfont)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pFont == nullptr)
               return nullptr;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, pFont->get_os_data());
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, pFont->get_os_data());
            return dynamic_cast < ::write_text::font * > (::draw2d_opengl::object::from_handle(get_application(), hOldObj));*/

      /*ASSERT(pFont != nullptr);

      if(pFont == nullptr)
         return nullptr;

      m_fontxyz = *pFont;
      return &m_fontxyz;*/

      if(!set(pfont))
         return nullptr;

      return m_pfont;

   }


   i32 graphics::SelectObject(::draw2d::region* pRgn)
   {
      i32 nRetVal = GDI_ERROR;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = (i32)(iptr)::SelectObject(m_hdc, (HGDIOBJ) pRgn->get_os_data());
      //if(m_hdc != nullptr)
      //   nRetVal = (i32)(iptr)::SelectObject(m_hdc, (HGDIOBJ) pRgn->get_os_data());
      return nRetVal;

   }


   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return nullptr;
//      return dynamic_cast < ::draw2d::palette * > (::draw2d_opengl::object::from_handle(get_application(), ::SelectPalette(m_hdc, (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }


   i32 graphics::SetPolyFillMode(i32 nPolyFillMode)
   {
      i32 nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetPolyFillMode(m_hdc, nPolyFillMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetPolyFillMode(m_hdc, nPolyFillMode);
      return nRetVal;

   }


   i32 graphics::SetROP2(i32 nDrawMode)
   {
      i32 nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetROP2(m_hdc, nDrawMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetROP2(m_hdc, nDrawMode);
      return nRetVal;

   }


   i32 graphics::set_interpolation_mode(i32 nStretchMode)
   {

      //if(m_pgraphics == nullptr)
      //{

      //   return -1;

      //}

      //if(nStretchMode == 0)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeNearestNeighbor);
      //}
      //else if(nStretchMode == e_interpolation_mode_high_quality_bicubic)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);
      //}
      //else
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeLowQuality);
      //}
      //return 1;

      return true;

      /*i32 nRetVal = 0;
      if(m_hdc != nullptr && m_hdc != m_hdc)
         nRetVal = ::set_interpolation_mode(m_hdc, nStretchMode);
      if(m_hdc != nullptr)
         nRetVal = ::set_interpolation_mode(m_hdc, nStretchMode);
      return nRetVal;*/
   }


   i32 graphics::SetGraphicsMode(i32 iMode)
   {
   
      i32 nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //{
      //   nRetVal = ::SetGraphicsMode(m_hdc, iMode);
      //}
      //if(m_hdc != nullptr)
      //{
      //   nRetVal = ::SetGraphicsMode(m_hdc, iMode);
      //}
      return nRetVal;

   }


   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      //plusplus::REAL rectangle_i32[6];

      //rectangle_i32[0] = pXform->eDx;
      //rectangle_i32[1] = pXform->eDy;

      //rectangle_i32[2] = pXform->eM11;
      //rectangle_i32[3] = pXform->eM12;
      //rectangle_i32[4] = pXform->eM21;
      //rectangle_i32[5] = pXform->eM22;

      //plusplus::Matrix m;

      //m.SetElements(rectangle_i32[2],rectangle_i32[3],rectangle_i32[4],rectangle_i32[5],rectangle_i32[0],rectangle_i32[1]);

      //m_pgraphics->SetTransform(&m);

      return true;

   }


   bool graphics::ModifyWorldTransform(const XFORM* pXform,u32 iMode)
   {
      bool nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //{
      //   nRetVal = ::ModifyWorldTransform(m_hdc, pXform, iMode) != false;
      //}
      //if(m_hdc != nullptr)
      //{
      //   nRetVal = ::ModifyWorldTransform(m_hdc, pXform, iMode) != false;
      //}
      return nRetVal;

   }


   i32 graphics::SetMapMode(i32 nMapMode)
   {
      i32 nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetMapMode(m_hdc, nMapMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetMapMode(m_hdc, nMapMode);
      return nRetVal;

   }


   //point_i32 graphics::GetViewportOrg() const
   //{

   //   return ::draw2d::graphics::GetViewportOrg();

   //   //::point_i32 point;
   //   //::GetViewportOrgEx(m_hdc, &point);

   //   //if (m_pgraphics == nullptr)
   //   //{

   //   //   return ::point_i32();

   //   //}

   //   //plusplus::Point origin(0, 0);

   //   //m_pgraphics->TransformPoints(
   //   //   plusplus::CoordinateSpacePage,
   //   //   plusplus::CoordinateSpaceWorld,
   //   //   &origin,
   //   //   1);

   //   //return point((i64) origin.X, (i64) origin.Y);

   //   //return m_pointTranslate;

   //}


   bool graphics::_set(const ::draw2d::matrix & matrix)
   {

      thread_select();

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

///      GLdouble m[16];
      
      //glGetDoublev(GL_MODELVIEW_MATRIX, m);

      //glTranslatef(matrix.c1, matrix.c2, 0.f);

      //glGetDoublev(GL_MODELVIEW_MATRIX, m);


      GLdouble m[16];

      m[0] = matrix.a1;
      m[1] = matrix.b1;
      //m[2] = matrix.c1;
      m[2] = 0.0;
      m[3] = 0.0;
      
      m[4] = matrix.a2;
      m[5] = matrix.b2;
      //m[6] = matrix.c2;
      m[6] = 0.0;
      m[7] = 0.0;
      
      m[8] = 0.0;
      m[9] = 0.0;
      m[10] = 1.0;
      m[11] = 0.0;
      
      m[12] = matrix.c1;
      m[13] = matrix.c2;
      m[14] = 0.0;
      m[15] = 1.0;

      glLoadMatrixd((const GLdouble *) m);

      return false;

   }


   point_i32 graphics::SetViewportOrg(i32 x, i32 y)
   {

      return ::draw2d::graphics::SetViewportOrg(x, y);

   }


   point_i32 graphics::OffsetViewportOrg(i32 nWidth, i32 nHeight)
   {

      return ::draw2d::graphics::OffsetViewportOrg(nWidth, nHeight);


   }


   size_i32 graphics::SetViewportExt(i32 x, i32 y)
   {

      return ::draw2d::graphics::SetViewportExt(x, y);

      //size_i32 size(0, 0);
      ////if(m_hdc != nullptr && m_hdc != m_hdc)
      ////   ::SetViewportExtEx(m_hdc, x, y, &size);
      ////if(m_hdc != nullptr)
      ////   ::SetViewportExtEx(m_hdc, x, y, &size);
      //return size;

   }


   size_i32 graphics::ScaleViewportExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom)
   {

      return ::draw2d::graphics::ScaleViewportExt(xNum, xDenom, yNum, yDenom);

      //size_i32 size(0, 0);
      ////if(m_hdc != nullptr && m_hdc != m_hdc)
      ////   ::ScaleViewportExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      ////if(m_hdc != nullptr)
      ////   ::ScaleViewportExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      //return size;
   }

   
   point_i32 graphics::SetWindowOrg(i32 x, i32 y)
   {
      
      ::point_i32 point;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetWindowOrgEx(m_hdc, x, y, &point);
      //if(m_hdc != nullptr)
      //   ::SetWindowOrgEx(m_hdc, x, y, &point);
      return point;

   }

   
   point_i32 graphics::offset_window_org(i32 nWidth, i32 nHeight)
   {
      
      ::point_i32 point;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::OffsetWindowOrgEx(m_hdc, nWidth, nHeight, &point);
      //if(m_hdc != nullptr)
      //   ::OffsetWindowOrgEx(m_hdc, nWidth, nHeight, &point);
      return point;

   }

   
   size_i32 graphics::set_window_ext(i32 x, i32 y)
   {
   
      size_i32 size(0, 0);
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetWindowExtEx(m_hdc, x, y, &size);
      //if(m_hdc != nullptr)
      //   ::SetWindowExtEx(m_hdc, x, y, &size);
      return size;

   }


   size_i32 graphics::scale_window_ext(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom)
   {
   
      size_i32 size(0, 0);
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::ScaleWindowExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      //if(m_hdc != nullptr)
      //   ::ScaleWindowExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      return size;

   }


   i32 graphics::get_clip_box(RECTANGLE_I32 * prectangle) const
   {

      //plusplus::Rect rectangle_i32;

      //m_pgraphics->GetClipBounds(rectangle);

      //rectangle.left = rectangle.X;
      //rectangle.top = rectangle.Y;
      //rectangle.right = rectangle.X + rectangle.Width;
      //rectangle.bottom = rectangle.Y + rectangle.Height;

      return 1;

   }


   i32 graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      //if(pregion == nullptr)
      //{
      //   m_pgraphics->ResetClip();
      //}
      //else
      //{
      //   m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data());
      //}

      return 0;

      /*      i32 nRetVal = ERROR;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               nRetVal = ::SelectClipRgn(m_hdc, pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            if(m_hdc != nullptr)
               nRetVal = ::SelectClipRgn(m_hdc, pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            return nRetVal;*/
   }


   i32 graphics::ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      i32 nRetVal = ERROR;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::ExcludeClipRect(m_hdc, x1, y1, x2, y2);
      //if(m_hdc != nullptr)
      //   nRetVal = ::ExcludeClipRect(m_hdc, x1, y1, x2, y2);

      return nRetVal;

   }


   i32 graphics::ExcludeClipRect(const RECTANGLE_I32 &  rectParam)
   {
      
      i32 nRetVal = ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::ExcludeClipRect(m_hdc, rectParam.left, rectParam.top,
      //                               rectParam.right, rectParam.bottom);
      //if(m_hdc != nullptr)
      //   nRetVal = ::ExcludeClipRect(m_hdc, rectParam.left, rectParam.top,
      //                               rectParam.right, rectParam.bottom);

      return nRetVal;

   }


   i32 graphics::IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
   {
      
      i32 nRetVal = ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::IntersectClipRect(m_hdc, x1, y1, x2, y2);
      //if(m_hdc != nullptr)
      //   nRetVal = ::IntersectClipRect(m_hdc, x1, y1, x2, y2);

      return nRetVal;

   }


   i32 graphics::IntersectClipRect(const RECTANGLE_I32 &  rectBounds)
   {
      
      i32 nRetVal = ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::IntersectClipRect(m_hdc,rectBounds.left,rectBounds.top,rectBounds.right,rectBounds.bottom);
      //if(m_hdc != nullptr)
      //   nRetVal = ::IntersectClipRect(m_hdc,rectBounds.left,rectBounds.top,rectBounds.right,rectBounds.bottom);

      return nRetVal;

   }


   i32 graphics::OffsetClipRgn(i32 x, i32 y)
   {
      
      i32 nRetVal = ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::OffsetClipRgn(m_hdc, x, y);
      //if(m_hdc != nullptr)
      //   nRetVal = ::OffsetClipRgn(m_hdc, x, y);

      return nRetVal;

   }


   i32 graphics::OffsetClipRgn(const ::size_i32 & size)
   {
      
      i32 nRetVal = ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::OffsetClipRgn(m_hdc, size.cx, size.cy);
      //if(m_hdc != nullptr)
      //   nRetVal = ::OffsetClipRgn(m_hdc, size.cx, size.cy);

      return nRetVal;

   }


   ::u32 graphics::SetTextAlign(::u32 nFlags)
   {
      
      ::u32 nRetVal = GDI_ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetTextAlign(m_hdc, nFlags);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetTextAlign(m_hdc, nFlags);

      return nRetVal;

   }


   i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
   {
    
      i32 nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetTextJustification(m_hdc, nBreakExtra, nBreakCount);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetTextJustification(m_hdc, nBreakExtra, nBreakCount);

      return nRetVal;

   }


   i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
   {
      
      // ASSERT(m_hdc != nullptr);

      i32 nRetVal = 0x8000000;
      
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetTextCharacterExtra(m_hdc, nCharExtra);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetTextCharacterExtra(m_hdc, nCharExtra);

      return nRetVal;

   }


   u32 graphics::SetMapperFlags(u32 dwFlag)
   {
      
      // ASSERT(m_hdc != nullptr);

      u32 dwRetVal = GDI_ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   dwRetVal = ::SetMapperFlags(m_hdc, dwFlag);
      //if(m_hdc != nullptr)
      //   dwRetVal = ::SetMapperFlags(m_hdc, dwFlag);

      return dwRetVal;

   }


   typedef u32 (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   typedef u32 (CALLBACK* __GDISETLAYOUTPROC)(HDC, u32);

   u32 graphics::GetLayout() const
   {
      
      HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");

      ASSERT(hInst != nullptr);

      /*      u32 dwGetLayout = LAYOUT_LTR;
            __GDIGETLAYOUTPROC pfn;
            pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
            // if they API is available, just call it. If it is not
            // available, indicate an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(m_hdc);
            else
            {
               dwGetLayout = GDI_ERROR;
               set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
            }*/

      //return dwGetLayout;

      return 0;

   }


   u32 graphics::SetLayout(u32 dwSetLayout)
   {
      /*HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != nullptr);
      u32 dwGetLayout = LAYOUT_LTR;
      __GDISETLAYOUTPROC pfn;
      pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
      // If the API is availalbe, just call it. If it's not available,
      // setting anything other than LAYOUT_LTR is an error.
      if (pfn != nullptr)
         dwGetLayout = (*pfn)(m_hdc, dwSetLayout);
      else if (dwSetLayout != LAYOUT_LTR)
      {
         dwGetLayout = GDI_ERROR;
         set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;*/

      return 0;

   }
   /*
   void window::screen_to_client(RECTANGLE_I32 * prectangle)
   {
   ASSERT(::IsWindow(m_hdc));
   ::screen_to_client(m_hdc, (POINT_I32 *)rectangle_i32);
   ::screen_to_client(m_hdc, ((POINT_I32 *)rectangle_i32)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rectangle_i32::swap_left_right(rectangle);
   }

   void window::client_to_screen(RECTANGLE_I32 * prectangle)
   {
   ASSERT(::IsWindow(m_hdc));
   ::client_to_screen(m_hdc, (POINT_I32 *)rectangle_i32);
   ::client_to_screen(m_hdc, ((POINT_I32 *)rectangle_i32)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rectangle_i32::swap_left_right(rectangle);
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {
      // ASSERT(m_hdc != nullptr);
      bool bResult = false;
      //bool bResult = ::ArcTo(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::point_i32 point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
      //}
      return bResult;
   }

   i32 graphics::SetArcDirection(i32 nArcDirection)
   {
      // ASSERT(m_hdc != nullptr);
      i32 nResult = 0;
      //if (m_hdc != m_hdc)
      //   nResult = ::SetArcDirection(m_hdc, nArcDirection);
      //if (m_hdc != nullptr)
      //   nResult = ::SetArcDirection(m_hdc, nArcDirection);
      return nResult;
   }

   bool graphics::PolyDraw(const POINT_I32* lpPoints, const byte* lpTypes, count nCount)
   {

      // ASSERT(m_hdc != nullptr);

      bool bResult = false;
      //bool bResult = ::PolyDraw(m_hdc, lpPoints, lpTypes, (int) nCount) != false;

      //if (m_hdc != m_hdc)
      //{
      //   ::point_i32 point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
      //}
      return bResult;
   }

   bool graphics::polyline_to(const POINT_I32* lpPoints, count nCount)
   {
      // ASSERT(m_hdc != nullptr);
      bool bResult = false;
      //bool bResult = ::polyline_to(m_hdc, lpPoints, (::u32) nCount) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::point_i32 point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
      //}
      return bResult;
   }

   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {
      // ASSERT(m_hdc != nullptr);
      bool bResult = false;
      //if (m_hdc != m_hdc)
      //   bResult = ::SetColorAdjustment(m_hdc, lpColorAdjust) != false;
      //if (m_hdc != nullptr)
      //   bResult = ::SetColorAdjustment(m_hdc, lpColorAdjust) != false;
      return bResult;
   }

   bool graphics::poly_bezier_to(const POINT_I32* lpPoints, count nCount)
   {
      // ASSERT(m_hdc != nullptr);
      bool bResult = false;      //bool bResult = ::poly_bezier_to(m_hdc, lpPoints, (::u32) nCount) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::point_i32 point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x, point.y, nullptr));
      //}
      return bResult;
   }

   bool graphics::SelectClipPath(i32 nMode)
   {
      // ASSERT(m_hdc != nullptr);

      bool bResult = false;

      //// output DC always holds the current path
      //if (!::SelectClipPath(m_hdc, nMode))
      //   return false;

      //// transfer clipping region into the attribute DC
      //bool bResult = true;
      //if (m_hdc != m_hdc)
      //{
      //   HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
      //   if (::GetClipRgn(m_hdc, hRgn) < 0 || !::SelectClipRgn(m_hdc, hRgn))
      //   {
      //      INFO(trace_category_appmsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
      //      bResult = false;
      //   }
      //   ::DeleteObject(hRgn);
      //}
      return bResult;
   }


   i32 graphics::SelectClipRgn(::draw2d::region* pregion,i32 nMode)
   {

      //if(pregion == nullptr)
      //{

      //   m_pgraphics->ResetClip();

      //}
      //else
      //{

      //   if(nMode == RGN_AND)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(), plusplus::CombineModeIntersect);

      //   }
      //   else if(nMode == RGN_OR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeUnion);

      //   }
      //   else if(nMode == RGN_XOR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeXor);

      //   }
      //   else if(nMode == RGN_COPY)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeReplace);

      //   }
      //   else if(nMode == RGN_DIFF)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeExclude);

      //   }

      //}

      return 0;

   }


   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback

   i32 CALLBACK __enum_meta_file_procedure(HDC hDC,
         HANDLETABLE* pHandleTable, METARECORD* pMetaRec, i32 nHandles, LPARAM lParam)
   {
      return 1;
//      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)lParam;
//      ASSERT_VALID(pgraphics);
//
//      switch (pMetaRec->rdFunction)
//      {
//      // these records have effects different for each graphics derived class
//      case META_SETMAPMODE:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetMapMode((i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETWINDOWEXT:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->set_window_ext(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETWINDOWORG:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetWindowOrg(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETVIEWPORTEXT:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetViewportExt(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETVIEWPORTORG:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SetViewportOrg(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SCALEWINDOWEXT:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->scale_window_ext(
//         (i32)(i16)pMetaRec->rdParm[3], (i32)(i16)pMetaRec->rdParm[2],
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SCALEVIEWPORTEXT:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->ScaleViewportExt(
//         (i32)(i16)pMetaRec->rdParm[3], (i32)(i16)pMetaRec->rdParm[2],
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_OFFSETVIEWPORTORG:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->OffsetViewportOrg(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SAVEDC:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SaveDC();
//         break;
//      case META_RESTOREDC:
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->RestoreDC((i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETBKCOLOR:
//      {
//         ::draw2d::brush_pointer brush(e_create);
//         
//         brush->create_solid(*(UNALIGNED color32_t*)& pMetaRec->rdParm[0]);
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(brush);
//      }
//      break;
//      case META_SETTEXTCOLOR:
//      {
//         ::draw2d::brush_pointer brush((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->create_new, this, *(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
//         (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(brush);
//      }
//      break;
//
//      // need to watch out for SelectObject(HFONT), for custom font mapping
//      case META_SELECTOBJECT:
//      {
//         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
//         ::u32 nObjType = GetObjectType(hObject);
//         if (nObjType == 0)
//         {
//            // object type is unknown, determine if it is a font
//            HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
//            HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->m_hdc, hStockFont);
//            HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->m_hdc, hObject);
//            if (hObjOld == hStockFont)
//            {
//               // got the stock object back, so must be selecting a font
//               __throw(error_not_implemented);
////                  (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(::draw2d_opengl::font::from_handle(pgraphics->get_application(), (HFONT)hObject));
//               break;  // don't play the default record
//            }
//            else
//            {
//               // didn't get the stock object back, so restore everything
//               ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->m_hdc, hFontOld);
//               ::SelectObject((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->m_hdc, hObjOld);
//            }
//            // and fall through to PlayMetaFileRecord...
//         }
//         else if (nObjType == OBJ_FONT)
//         {
//            // play back as graphics::SelectObject(::write_text::font*)
////               (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->SelectObject(::draw2d_opengl::font::from_handle(pgraphics->get_application(), (HFONT)hObject));
//            __throw(error_not_implemented);
//            break;  // don't play the default record
//         }
//      }
//      // fall through...
//
//      default:
//         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
//         break;
//      }
//
//      return 1;
   }


   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {
      //if (::GetDeviceCaps(m_hdc, TECHNOLOGY) == DT_METAFILE)
      //{
      //   // playing metafile in metafile, just use aura windows API
      //   return ::PlayMetaFile(m_hdc, hMF) != false;
      //}

      //// for special playback, lParam == pgraphics
      //return ::EnumMetaFile(m_hdc, hMF, __enum_meta_file_procedure, (LPARAM)this) != false;
      return false;

   }


   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   
   void graphics::LPtoDP(LPSIZE32 LPSIZE32) const
   {

      //ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));

      //size_i32 sizeWinExt = GetWindowExt();
      //size_i32 sizeVpExt = GetViewportExt();
      //LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
      //LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));

   }


   void graphics::DPtoLP(LPSIZE32 LPSIZE32) const
   {

      //ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));

      //size_i32 sizeWinExt = GetWindowExt();
      //size_i32 sizeVpExt = GetViewportExt();
      //LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
      //LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));

   }


   bool graphics::draw_text(const ::string & str,const ::rectangle_i32 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      ::rectangle_f64 rectangle;

      __copy(rectangle,&rectParam);

      return draw_text(str, rectangle, ealign, edrawtext);

   }


   bool graphics::draw_text(const ::string & str, const ::rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      //try
      //{

      //   if(m_pgraphics == nullptr)
      //      return false;

      //   /*

      //   switch(m_ewritetextrendering)
      //   {
      //   case ::write_text::e_rendering_anti_alias:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);
      //      break;
      //   case ::write_text::e_rendering_anti_alias_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAliasGridFit);
      //      break;
      //   case ::write_text::e_rendering_single_bit_per_pixel:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintSingleBitPerPixel);
      //      break;
      //   case ::write_text::e_rendering_clear_type_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintClearTypeGridFit);
      //      break;
      //   }

      //   */
      //   m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //   m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);


      //}
      //catch(...)
      //{
      //}



      //plusplus::StringFormat format(plusplus::StringFormat::GenericTypographic());


      //format.SetFormatFlags(format.GetFormatFlags()
      //                      | plusplus::StringFormatFlagsNoClip | plusplus::StringFormatFlagsMeasureTrailingSpaces
      //                      | plusplus::StringFormatFlagsLineLimit);

      //if(nFormat & e_align_left)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & e_align_right)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & e_align_horizontal_center)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}

      //if(nFormat & e_align_bottom)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & e_align_top)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & e_align_vertical_center)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}

      //plusplus::REAL stops[] = {16,32,48, 64,80,96,112,128};

      //format.SetTabStops(0,8,stops);

      ////m_dFontSize             = fontSrc.m_dFontSize;

      //plusplus::Matrix m;
      //m_pgraphics->GetTransform(&m);
      //plusplus::Matrix * pmNew = m.Clone();
      //try
      //{


      //   pmNew->Translate((plusplus::REAL) rectParam.left,(plusplus::REAL) rectParam.top);
      //   pmNew->Scale((plusplus::REAL) m_pfont->m_dFontWidth,(plusplus::REAL) 1.0,plusplus::MatrixOrderAppend);

      //   plusplus::RectF rectangle_f32(0,0,(plusplus::REAL) ((rectParam.right - rectParam.left) * m_pfont->m_dFontWidth),(plusplus::REAL) (rectParam.bottom - rectParam.top));

      //   m_pgraphics->SetTransform(pmNew);

      //   m_pgraphics->DrawString(::str::international::utf8_to_unicode(str),-1,gl2d_font(),rectangle_f32,&format,gl2d_brush());
      //}
      //catch(...)
      //{
      //}

      //m_pgraphics->SetTransform(&m);

      //delete pmNew;

      return 1;

   }


   bool graphics::draw_text_ex(const ::string & str, const ::rectangle_i32 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   {

      // ASSERT(m_hdc != nullptr);

      // these flags would modify the string
      //ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      //ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      //return ::DrawTextExW(m_hdc,const_cast<wchar_t *>((const wchar_t *)wstr),(i32)wcslen(wstr),(RECTANGLE_I32 *) &rectParam,nFormat,lpDTParams);
      
      return false;

   }




   bool graphics::draw_text_ex(const ::string & str,const ::rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   {

      return ::draw2d::graphics::draw_text_ex(str,rectParam,ealign, edrawtext,lpDTParams);

   }


   size_f64 graphics::get_text_extent(const ::string & lpszString, strsize nCount, strsize iIndex)
   {

      if(lpszString == nullptr || *lpszString == '\0')
         return size_i32(0, 0);

      if(nCount < 0)
         nCount = strlen(lpszString);

      if(iIndex > nCount)
         return size_i32(0, 0);

      if(iIndex < 0)
         return size_i32(0, 0);

      return size_i32(0, 0);

      wstring wstr = ::str::international::utf8_to_unicode(lpszString, nCount);

      strsize iRange = 0;
      strsize i = 0;
      strsize iLen;
      const char * psz = lpszString;
      while(i < iIndex)
      {
         iLen = ::str::get_utf8_char(psz).length();
         iRange++;
         i += iLen;
         psz = ::str::utf8_inc(psz);
         if(psz == nullptr)
            break;
         if(*psz == '\0')
            break;
      }

      set(m_pfont);

      __pointer(font) pfont = m_pfont;

      SIZE_I32 s = { 0 };

      ::GetTextExtentPointW(pfont->m_hdcFont, wstr, wstr.get_length(), &s);

      return s;

   }


   size_f64 graphics::get_text_extent(const ::string & lpszString, strsize nCount)
   {

      ::size_f64 size;

      if (!get_text_extent(size, lpszString, nCount, 0))
         return ::size_i32(0, 0);

      return ::size_i32(size.cx, size.cy);

   }


   size_f64 graphics::get_text_extent(const ::string & str)
   {

      ::size_f64 size;

      if(!get_text_extent(size, str, (i32) str.get_length(), 0))
         return ::size_i32(0, 0);

      return ::size_i32((long) size.cx, (long) size.cy);

   }


   size_i32 graphics::GetOutputTextExtent(const ::string & lpszString, strsize nCount)
   {
      // ASSERT(m_hdc != nullptr);
      ::size_i32 size;
      //string str(lpszString, nCount);
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      //VERIFY(::GetTextExtentPoint32W(m_hdc, wstr, (i32)wstr.get_length(), &size));
      return size;

   }


   size_i32 graphics::GetOutputTextExtent(const ::string & str)
   {

      // ASSERT(m_hdc != nullptr);

      ::size_i32 size;

      wstring wstr = ::str::international::utf8_to_unicode(str);

      //::GetTextExtentPoint32W(m_hdc, wstr, (i32)wstr.get_length(), &size);

      return size;

   }


   bool graphics::get_text_extent(size_f64 & size, const ::string & lpszString, strsize nCount, strsize iIndex)
   {

      //// ASSERT(m_hdc != nullptr);

      set(m_pfont);

      __pointer(font) pfont = m_pfont;

      ::size_i32 s;

      wstring wstr = ::str::international::utf8_to_unicode(string(&lpszString[iIndex], nCount));

      //if (!::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (i32)wstr.get_length(), &s))
//         return false;

      //// FreeType
      //FT_Library ft;
      //// All functions return a value different than 0 whenever an error occurred
      //if (FT_Init_FreeType(&ft))
      //   std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

      //// Load font as face
      //FT_Face face;
      //if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
      //   std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

      //// Set size_i32 to load glyphs as
      //FT_Set_Pixel_Sizes(face, 0, 48);

      //// Disable byte-alignment restriction
      //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      //// Load first 128 characters of ASCII set
      //for (GLubyte c = 0; c < 128; c++)
      //{
      //   // Load character glyph 
      //   if (FT_Load_Char(face, c, FT_LOAD_RENDER))
      //   {
      //      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      //      continue;
      //   }
      //   // Generate texture
      //   GLuint texture;
      //   glGenTextures(1, &texture);
      //   glBindTexture(GL_TEXTURE_2D, texture);
      //   glTexImage2D(
      //      GL_TEXTURE_2D,
      //      0,
      //      GL_RED,
      //      face->glyph->bitmap.width,
      //      face->glyph->bitmap.rows,
      //      0,
      //      GL_RED,
      //      GL_UNSIGNED_BYTE,
      //      face->glyph->bitmap.buffer
      //   );
      //   // Set texture options
      //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      //   // Now store character for later use
      //   Character character = {
      //       texture,
      //       glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      //       glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      //       face->glyph->advance.x
      //   };
      //   Characters.insert(std::pair<GLchar, Character>(c, character));
      //}
      //glBindTexture(GL_TEXTURE_2D, 0);
      //// Destroy FreeType once we're finished
      //FT_Done_Face(face);
      //FT_Done_FreeType(ft);

      size.cx = s.cx;

      size.cy = s.cy;

      return true;

   }


   bool graphics::get_text_extent(size_f64 & size, const ::string & lpszString, strsize nCount)
   {

      //// ASSERT(m_hdc != nullptr);

      set(m_pfont);

      __pointer(font) pfont = m_pfont;

      ::size_i32 s;

      wstring wstr = ::str::international::utf8_to_unicode(lpszString, nCount);

      //if (!::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (i32)wstr.get_length(), &s))
        // return false;

      size.cx = s.cx;

      size.cy = s.cy;

      return true;

   }


   bool graphics::get_text_extent(size_f64 & size, const ::string & str)
   {

      //// ASSERT(m_hdc != nullptr);

      set(m_pfont);

      __pointer(font) pfont = m_pfont;

      ::size_i32 s;

      wstring wstr = ::str::international::utf8_to_unicode(str);

      //if (::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (i32)wstr.get_length(), &s))
        // return false;

      size.cx = s.cx;

      size.cy = s.cy;

      return true;

   }


   void graphics::fill_rectangle(const rectangle_f64& rectangle, color32_t color32)
   {

      try
      {

         if (m_pbitmap.is_set())
         {


            ::size_i32 s = m_pbitmap.cast < bitmap>()->m_sizeOut;

            if (s.area() <= 0)
            {

               return;

            }

         }

         glBegin(GL_QUADS);

         ::opengl::color::color(color32);

         ::opengl::vertex2f(rectangle);

         glEnd();

      }
      catch(...)
      {
         
      }

   }


   bool graphics::draw_line(const point_i32& point1, const point_i32& point2, ::draw2d::pen * ppen)
   {

      ::opengl::line(point1.x, point1.y, point2.x, point2.y, ppen->m_dWidth,
         ppen->m_color.m_iR/255.f, ppen->m_color.m_iG / 255.f, ppen->m_color.m_iB / 255.f,
         ppen->m_color.m_iA / 255.f, 0.f, 0.f, true);

      /*glLineWidth(ppen->m_dWidth);

      glBegin(GL_LINES);

      ::opengl::color::color(ppen->m_color);

      glVertex2f(point1.x, point1.y);
      glVertex2f(point2.x, point2.y);

      glEnd();*/

      m_point.x = point2.x;
      m_point.y = point2.y;

      return true;

   }

   
   bool graphics::line_to(const ::point_f64& point)
   {

      glLineWidth(m_ppen->m_dWidth);

      glBegin(GL_LINES);

      ::opengl::color::color(m_ppen->m_color);

      glVertex2f(m_point.x, m_point.y);
      glVertex2f(point.x, point.y);

      glEnd();

      m_point.x = point.x;
      m_point.y = point.y;

      return true;

   }


   bool graphics::text_out(double x, double y, const ::string & lpszString, strsize nCount)
   {

      if (m_pfont.is_null())
      {

         return false;

      }

      if (::draw2d::graphics::text_out(x, y, lpszString, nCount))
      {

         return true;

      }

      return true;

      set(m_pfont);

      __pointer(font) pfont = m_pfont;

      int length = 0;

      for (unsigned int loop = 0; loop < (strlen(lpszString)); loop++)	// Loop To Find Text Length
      {

         length += pfont->m_gmf[lpszString[loop]].gmfCellIncX;			// Increase Length By Each Characters Width

      }

      glTranslatef(x, y, 0.0f);					// Center Our Text On The Screen

      glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
      glListBase(pfont->m_baseFont);									// Sets The Base Character to 0
      glCallLists((GLsizei) strlen(lpszString), GL_UNSIGNED_BYTE, lpszString);	// Draws The Display List Text
      glPopAttrib();										// Pops The Display List Bits      }

      glTranslatef(-x, -y, 0.0f);					// Center Our Text On The Screen

      return true;

   }


   ::e_status graphics::set(::draw2d::region* pregion)
   {

      return ::success;

   }


   ::e_status graphics::set(::draw2d::pen * ppen)
   {

      //glLineWidth(ppen->m_dWidth);

      ::opengl::color::color(ppen->m_color);

      return ::success;

   }



   ::e_status graphics::set(::draw2d::brush * pbrush)
   {

      ::opengl::color::color(pbrush->m_color);
      
      return ::success;

   }



   ::e_status graphics::set(::write_text::font * pfont)
   {

      if (::is_null(pfont))
      {

         return ::error_failed;

      }

      pfont->get_os_data(this);

      return ::success;

   }


   ::e_status graphics::set(::draw2d::bitmap* pbitmap)
   {

      return ::success;

   }


   ::draw2d::object* graphics::set_stock_object(i32 nIndex)
   {

      return nullptr;

   }


   bool graphics::set_smooth_mode(::draw2d::e_smooth_mode esmoothmode)
   {

      //if(m_esmoothmode == esmoothmode)
      //   return;

      //::draw2d::graphics::set_smooth_mode(esmoothmode);

      //try
      //{

      //   if(m_pgraphics == nullptr)
      //      return;

      //   if(m_esmoothmode == ::draw2d::smooth_mode_none)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeNone);

      //   }
      //   else if(m_esmoothmode == ::draw2d::smooth_mode_antialias)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighSpeed);

      //   }
      //   else if(m_esmoothmode == ::draw2d::smooth_mode_high)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighQuality);

      //   }

      //}
      //catch(...)
      //{
      return true;
      //}

   }


   bool graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {

      try
      {

         //if(m_pgraphics == nullptr)
         //   return;

         ::draw2d::graphics::set_alpha_mode(ealphamode);
         if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         }
         else if(m_ealphamode == ::draw2d::e_alpha_mode_set)
         {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);
         }

      }
      catch(...)
      {
         return false;

      }

      return true;

   }


   bool graphics::set_text_rendering_hint(::write_text::enum_rendering etextrendering)
   {
      
      m_ewritetextrendering = etextrendering;

      return true;

   }


//   void * graphics::get_os_data() const
//   {
//
////      return (void *) m_pgraphics;
//
//      if (!m_hglrc)
//      {
//         return (void *) (iptr)1;
//      }
//
//      return m_hglrc;
//
//   }


   //void graphics::fill_rectangle(const rectangle_f64& rectangle, color32_t color32)
   //{



   //}

//   void * graphics::get_os_data_ex(int i) const
//   {
//
//      if(i == 1)
//      {
////         return m_pgraphics->GetHDC();
//      }
//      else
//      {
//         return ::draw2d::graphics::get_os_data(i);
//      }
//
//      return nullptr;
//
//   }


//   void graphics::release_os_data_ex(int i,void * p)
//   {
//      if(i == 1)
//      {
////         m_pgraphics->ReleaseHDC((HDC)p);
//      }
//      else
//      {
//
//         //::draw2d::graphics::release_os_data(i, p);
//
//      }
//
//   }


   /*HDC graphics::get_handle() const
   {

      return m_hdc;

   }


   HDC graphics::m_hdc const
   {

      return get_handle();

   }


   HDC graphics::m_hdc const
   {
      return get_handle();
   }
*/

   bool graphics::attach(void * pdata)
   {

      //if(m_pgraphics != nullptr)
      //{

      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      TRACE("graphics::attach : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = nullptr;

      //}

      //m_pgraphics = (plusplus::Graphics *) pdata;

      return false;

   }


   void * graphics::detach()
   {

      //plusplus::Graphics * pgraphics = m_pgraphics;

      //m_pgraphics = nullptr;

      //m_hdc = nullptr;

      //return pgraphics;

      return nullptr;

   }

   //plusplus::Font * graphics::gl2d_font()
   //{
   //   if(m_pfont.is_null())
   //   {
   //      m_pfont.create(this);
   //      if(m_pfont.is_set())
   //      {
   //         m_pfont->m_powner = this;
   //      }
   //   }
   //   if(m_pfont.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Font *) m_pfont->get_os_data();
   //}

   //plusplus::Brush * graphics::gl2d_brush()
   //{
   //   if(m_pbrush.is_null())
   //   {
   //      m_pbrush.create(this);
   //      if(m_pbrush.is_set())
   //      {
   //         m_pbrush->m_powner = this;
   //      }
   //   }
   //   if(m_pbrush.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Brush *) m_pbrush->get_os_data();
   //}

   //plusplus::Pen * graphics::gl2d_pen()
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   if(m_ppen.is_null())
   //   {
   //      m_ppen.create(this);
   //      if(m_ppen.is_set())
   //      {
   //         m_ppen->m_powner = this;
   //      }
   //   }
   //   if(m_ppen.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Pen *) m_ppen->get_os_data();
   //}

   //plusplus::FillMode graphics::gl2d_get_fill_mode()
   //{
   //   return plusplus::FillModeWinding;
   //}

   bool graphics::blur(bool bExpand,double dRadius,const ::rectangle_i32 & rectParam)
   {

      //   // Commented Out for Running in cosan machine running Windows 2008

      //   //if(m_pbitmap.is_null() || m_pbitmap->get_os_data() == nullptr)
      //   //   return false;

      //   //plusplus::BlurParams myBlurParams;

      //   //myBlurParams.expandEdge    = bExpand ? 1 : 0;
      //   //myBlurParams.radius        = (float) dRadius;

      //   //plusplus::Blur myBlur;
      //   //myBlur.SetParameters(&myBlurParams);

      //   //

      //   //plusplus::Matrix m;
      //   //m_pgraphics->GetTransform(&m);

      //   //plusplus::PointF points[2];

      //   //points[0].X    = (plusplus::REAL) rectParam.left;
      //   //points[0].Y    = (plusplus::REAL) rectParam.top;
      //   //points[1].X    = (plusplus::REAL) rectParam.right;
      //   //points[1].Y    = (plusplus::REAL) rectParam.bottom;

      //   //m.TransformPoints(points, 2);

      //   ////plusplus::RectF rectangle_f32(points[0].X, points[0].Y, points[1].X - points[0].X, points[1].Y - points[0].Y);

      //   //RECTANGLE_I32 rectangle_i32;

      //   //rectangle.left      = (::i32) points[0].X;
      //   //rectangle.top       = (::i32) points[0].Y;
      //   //rectangle.right     = (::i32) points[1].X;
      //   //rectangle.bottom    = (::i32) points[1].Y;

      //   //plusplus::Bitmap * pbitmap = ((plusplus::Bitmap *) m_pbitmap->get_os_data());

      //   //pbitmap->ApplyEffect(&myBlur, &rectangle);

      //   return true;

      return true;
   }


   double graphics::get_dpix() const
   {

      //if (m_pgraphics == nullptr)
      //   return 96.0;

      //return m_pgraphics->GetDpiX();

      return 96.0;

   }


   double graphics::get_dpiy() const
   {

      //if (m_pgraphics == nullptr)
      //   return 96.0;

      //return m_pgraphics->GetDpiY();

      return 96.0;

   }


   bool graphics::flush()
   {

      synchronous_lock synchronouslock(mutex());

//      m_pgraphics->Flush();

      return true;

   }


   bool graphics::sync_flush()
   {

      synchronous_lock synchronouslock(mutex());

      //m_pgraphics->Flush(plusplus::FlushIntentionSync);

      return true;

   }

   HDC graphics::get_hdc()
   {

      if(m_hdc != nullptr)
         return m_hdc;

      ////if(m_pgraphics == nullptr)
      //   return nullptr;

      //return m_pgraphics->GetHDC();

      return nullptr;

   }

   void graphics::release_hdc(HDC hdc)
   {

      if(m_hdc != nullptr)
         return;

      //m_pgraphics->ReleaseHDC(hdc);

   }


   void graphics::enum_fonts(::write_text::font_enumeration_item_array& itema)
   {

      return;

      synchronous_lock synchronouslock(mutex());

      draw2d_opengl_enum_fonts fonts(itema);

      //HDC hdc = ::CreateCompatibleDC(nullptr);

      //::EnumFontFamilies(hdc,(LPCTSTR)nullptr,(FONTENUMPROC)draw2d_opengl_EnumFamCallBack,(LPARAM)&fonts);

      //::DeleteDC(hdc);

      // straPath = stra;

   }


   bool graphics::prefer_mapped_image_on_mix()
   {

      return true;

   }



   bool graphics::CreateWindowDC(oswindow wnd)
   {

      // http://stackoverflow.com/questions/4052940/how-to-make-an-opengl-rendering-context-with-transparent-background
      //

      //PIXELFORMATDESCRIPTOR pfd =
      //{
      //   sizeof(PIXELFORMATDESCRIPTOR),
      //   1,                                // Version Number
      //   PFD_DRAW_TO_WINDOW |         // Format Must Support Window
      //   PFD_SUPPORT_OPENGL |         // Format Must Support OpenGL
      //   PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
      //   PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
      //   PFD_TYPE_RGBA,                    // Request An RGBA Format
      //   32,                               // Select Our Color Depth
      //   0, 0, 0, 0, 0, 0,                 // Color Bits Ignored
      //   8,                                // An Alpha Buffer
      //   0,                                // Shift Bit Ignored
      //   0,                                // No Accumulation Buffer
      //   0, 0, 0, 0,                       // Accumulation Bits Ignored
      //   24,                               // 16Bit Z-Buffer (Depth Buffer)
      //   8,                                // Some Stencil Buffer
      //   0,                                // No Auxiliary Buffer
      //   PFD_MAIN_PLANE,                   // Main Drawing Layer
      //   0,                                // Reserved
      //   0, 0, 0                           // Layer Masks Ignored
      //};


      //DWM_BLURBEHIND bb = { 0 };
      ////HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      ////bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      //bb.dwFlags = DWM_BB_ENABLE;
      ////bb.hRgnBlur = hRgn;
      //bb.fEnable = true;
      //DwmEnableBlurBehindWindow(wnd, &bb);


      //m_hdc = GetDC(wnd);
      //int PixelFormat = ChoosePixelFormat(m_hdc, &pfd);
      //if (PixelFormat == 0)
      //{
      //   ASSERT(0);
      //   return false;
      //}

      //BOOL bResult = SetPixelFormat(m_hdc, PixelFormat, &pfd);
      //if (bResult == false)
      //{
      //   ASSERT(0);
      //   return false;
      //}

      //m_hglrc = wglCreateContext(m_hdc);
      //if (!m_hglrc)
      //{
      //   ASSERT(0);
      //   return false;
      //}

//      return true;
      return false;

   }


   //oswindow graphics::get_window_handle() const
   //{

   //   if (::is_null(m_puserinteraction))
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteraction->get_handle();

   //}


   bool graphics::is_valid_update_window_thread()
   {

      //return ::GetCurrentThreadId() == psystem->get_twf()->m_uiThread;
      return ::GetCurrentThreadId() == ::GetWindowThreadProcessId(m_hwnd, NULL);

   }


   void graphics::on_begin_draw(oswindow wnd, const ::size_i32 & sz)
   {

      thread_select();

      ::opengl::resize(sz);

      m_z = 0.f;

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   }


   void graphics::on_end_draw(oswindow wnd)
   {

      //glFlush();

      //SwapBuffers(m_hdc);

   }


   void graphics::thread_select()
   {

      if (thread_graphics() == this)
      {

         return;
      }

      wglMakeCurrent(m_hdc, m_hglrc);

      thread_graphics(this);

   }


} // namespace draw2d_opengl





BOOL CALLBACK draw2d_opengl_EnumFamCallBack(LPLOGFONT lplf,LPNEWTEXTMETRIC lpntm,::u32 FontType,LPVOID p)
{

   draw2d_opengl_enum_fonts * pfonts = (draw2d_opengl_enum_fonts *) p;

   if(FontType & RASTER_FONTTYPE)
   {

   }
   else if(FontType & TRUETYPE_FONTTYPE)
   {

      pfonts->m_itema.add(__new(::write_text::font_enumeration_item(lplf->lfFaceName)));

   }
   else
   {

   }

   return true;

}





namespace opengl
{


   void resize(const ::size_i32& size)
   {

      //double d = 200.0 / 72.0;

      double d = 1.0;

      glViewport(0, 0, size.cx * d, size.cy * d);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      //glOrtho(0, size.cx * d, size.cy * d, 0.0f, 000.0f, 1000.0f);
      //glOrtho(0, size.cx * d, size.cy * d, 0.0f, 000.0f, 1000.0f);
      ////glOrtho(0, size.cx * d, 0.0f, size.cy * d, 000.0f, 1000.0f);
      //glOrtho(0, size.cx, size.cy, 0.0f, -1000.0f, 1000.0f);
      glOrtho(0, size.cx, 0.f, size.cy, -1000.0f, 1000.0f);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   }

   //https://community.khronos.org/t/draw-an-arc-in-opengl/57994/2
   inline void draw_arc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments)
   {
      float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

      float tangetial_factor = tanf(theta);

      float radial_factor = cosf(theta);


      float x = r * cosf(start_angle);//we now start at the start angle
      float y = r * sinf(start_angle);

      glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
      for (int ii = 0; ii < num_segments; ii++)
      {
         glVertex2f(x + cx, y + cy);

         float tx = -y;
         float ty = x;

         x += tx * tangetial_factor;
         y += ty * tangetial_factor;

         x *= radial_factor;
         y *= radial_factor;
      }
      glEnd();
   }


} // namespace opengl



