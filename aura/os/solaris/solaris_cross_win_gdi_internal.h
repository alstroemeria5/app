#pragma once





struct CLASS_DECL_AURA gdi_object
{


   enum e_type
   {
      type_undefined,
      type_pen,
      ::draw2d::e_pen_brush,
      type_bitmap,
      type_font,
   };

   enum e_type      m_etype;

/*   gdi_object(e_type etype = type_undefined) :
      m_etype(etype)
   {
   }*/

};



struct tag_WINDOW
{

   Window   m_window;

};

class CLASS_DECL_AURA device_context
{
public:


   Display *   m_display;
   Drawable    m_d;
   GC          m_gc;
   oswindow        m_hwnd;


   device_context();


};



struct tagEXTLOGPEN :
   public gdi_object
{
    DWORD       elpPenStyle;
    DWORD       elpWidth;
    UINT        elpBrushStyle;
    COLORREF    elpColor;
    ulong_ptr   elpHatch;
    DWORD       elpNumEntries;
    DWORD       elpStyleEntry[1];
};


struct tagEXTLOGBRUSH :
   public gdi_object
{
	UINT        lbStyle;
	COLORREF    lbColor;
	ulong_ptr   lbHatch;
};



struct tagLOGRGN :
   public gdi_object
{
	UINT        m_uiSize;
	byte *      m_puchData;
};




struct  tagFONTA :
   public gdi_object,
   public tagLOGFONTA
{

};




