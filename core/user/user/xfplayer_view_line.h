#pragma once


#include "xfplayer_view_line_selection.h"


class xfplayer_view_linea;


class CLASS_DECL_CORE xfplayer_view_line  :
   virtual public ::object
{
public:




   enum EAnimate
   {
      AnimateNoAnimate = 0,
      AnimateRHL = 1 // Rotates Horizontally Left
   };


   enum EEffect
   {
      EffectSimple = 0,
      EffectEmbossed = 1
   };


   bool                             m_bColonPrefix;


   XfplayerViewLineSelection        m_selection;
   byte *                           m_lpBitmapData;
   ::draw2d::graphics_extension     m_dcextension;

   index                            m_iLinkHoverIndex;
   index                            m_iIndex;

   string                           m_str;
   string                           m_strPrefix;
   string                           m_strRoot;
   int_array                        m_iaPosition;

   ::rectangle_i32                              m_rectangle;

   i32                              m_iIndent;
   bool                             m_bPendingLayoutUpdate;
   bool                             m_bVisible;
   bool                             m_bAutoSizeX;
   bool                             m_bAutoSizeY;
   i32                              m_iAlign;
   ::user::interaction *            m_oswindow;
   xfplayer_view_linea *              m_pContainer;

   // 08, May 2004 attributes
   ::draw2d::graphics_pointer                m_dc1;
   ::draw2d::bitmap_pointer                  m_bmp1;
   ::write_text::font_pointer                    m_font;
   ::write_text::font_pointer                    m_fontPrefix;
   ::write_text::font_pointer                    m_fontLink;
   ::color::color                         m_cr;
   ::color::color                         m_colorOutline;
   ::rectangle_i32                           m_rectangleClient;
   double                           m_floatRateX;
   //LOGFONTW                          m_logfont;


   // 09, Sept 2004 attributes with change inApril 2010 from dcMain/bmpMain to imageMain
   ::image_pointer                     m_pimageMain;
   bool                             m_bEnhancedEmboss;
   bool                             m_bCacheEmboss;
   string                           m_strCache;

   // Link
   //LOGFONTW                          m_logfontLink;
   string_array                          m_straLink;
   index_array                      m_iaLinkStart;
   index_array                      m_iaLinkEnd;


   double                           m_dXfplayerViewLineBlend;
   i32                              m_nFont;
   ::rectangle_i32                           m_rectInvalidate;
   i32                              m_iAnimateType;
   double                           m_dAnimateProgress;
   double                           m_dAnimateProgressIncrement;
   i32                              m_iTextEffect;
   ::draw2d::pen *                      m_lpPenEmboss;
   ::color::color                         m_colorForeground;
   ::draw2d::pen *                      m_ppenLyricLeft;
   ::draw2d::pen *                      m_ppenLyricRight;
   ::size_i32                             m_sizeLyricMargin;
   ::color::color                         m_colorLyricLeft;
   ::color::color                         m_colorLyricRight;

   xfplayer_view_line();
   //xfplayer_view_line(const xfplayer_view_line & line);
   ~xfplayer_view_line() override;

   virtual ::e_status initialize_xfplayer_view_line(xfplayer_view_linea * pContainer);

   void set_blend(double d);
   ::write_text::font * GetFont();
   bool CalcChar(const ::point_i32 & point, strsize &iChar);
   index GetCharLink(strsize iChar);
   bool GetCharLink(string & str, strsize iChar);
   bool CharHasLink(strsize iChar);
   user::enum_line_hit get_link(string & strUrl, const ::point_i32 & point);
   index GetLinkIndex(index iLine, strsize iChar);
   bool has_link();
   bool is_hover();
   void update_hover(point_i32 & pointCursor);
   void PrepareURLLinks();
   void SetFont(::write_text::font * pfont);

//#ifdef WINDOWS_DESKTOP
//   void GetLogFont(LOGFONTW & lf);
//#endif

   user::enum_line_hit hit_test(const point_i32 &pointCursorParam, strsize &iChar);

   void CalcCharsPositions(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);


   void SetColors(::color32_t color32, ::color::color crOutline);

   void embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   const string & str,

   i32 left,
   i32 top,
   i32 ignore1,
   ::color32_t color32,
   ::color::color crOutline,
   strsize iLen,
   double dBlend);

   void embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   ::image * pimageCache,
   const ::string & str,

   i32 iLeft,
   i32 iTop,
   i32 iWidth,
   ::color32_t color32,
   ::color::color crOutline,
   strsize iLen,
   double dBlend);


   virtual void CacheEmboss(
   ::draw2d::graphics_pointer & pgraphics,
   const ::string & str,
   strsize iLen,
   ::image_pointer & imageCache);

   bool IsVisible();
   void Validate(const ::rectangle_i32 & rectangle = nullptr);
   void Invalidate(const ::rectangle_i32 & rectangle = nullptr);
   //void AddVmsFont(::write_text::font * pfont);
   //i32 GetVmsFontCount();
   void SetPlacement(const ::rectangle_i32 & rectangle);
   i32 SetLyricColors(::color::color crLeft, ::color::color crRight);
   i32 SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight);
   void SetRenderCriticalSection(critical_section *pcs);
   void SetAnimateIncrement(double dIncrement);
   i32 MapToFontEffect(i32 iLineEffect);


   void SetForegroundColor(::color32_t color32);
   void SetEmbossPen(::draw2d::pen * pPen);

   void SetTextEffect(i32 iTextEffect);

   void SetAnimateType(i32 iAnimateType);

   void OnTimerAnimate(::draw2d::graphics_pointer & pgraphics, rectangle_i32_array &   rectaModified);

   void Show(bool bShow = true);
   virtual xfplayer_view_line & operator = (const xfplayer_view_line & src);
   void GetPlacement(RECTANGLE_I32 * prectangle);

   void SetPlaement(const ::rectangle_i32 & rectangle);
   void SetAlign(i32 iAlign);
   static const i32 AlignLeft;
   static const i32 AlignRight;

   void SetAutoSize(bool bAutoSize);



   bool PrepareLine(::draw2d::graphics_pointer & pgraphics, string str, i32 flags, const ::rectangle_i32 & rectangle);


   void add_char(widechar wch, strsize &index);

   void add_char(widechar wch, strsize &index, ::write_text::font * pFont);

   bool _001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::rectangle_i32 & rectangle, rectangle_i32_array & rectaModified, bool bRecalcLayout);

   bool _001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::rectangle_i32 & rectangle, rectangle_i32_array & rectaModified, strsize * count, bool bRecalcLayout, ::color::color crColor, ::draw2d::pen_pointer sppen);


   DECLARE_MESSAGE_HANDLER(OnMouseMove);
   DECLARE_MESSAGE_HANDLER(OnLButtonDown);
   DECLARE_MESSAGE_HANDLER(OnLButtonUp);
   virtual void _001OnTimer(::timer * ptimer);
   DECLARE_MESSAGE_HANDLER(OnSetCursor);

   XfplayerViewLineSelection::enum_state GetSelectionState();
   XfplayerViewLineSelection & GetSelection();
   ::user::interaction * get_interaction();


};



