#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO region :
      virtual public ::draw2d::region
   {
   public:


      cairo_t *               m_pdc;
      cairo_surface_t *       m_psurface;
      ::rect                  m_rectBoundingBoxInternal;


      region();
      virtual ~region();


      virtual bool create(::draw2d::graphics * pgraphics);
      virtual void destroy();


      bool mask(cairo_t * pdc);
      bool _mask(cairo_t * pdc);
      bool mask_rect(cairo_t * pdc);
      bool mask_oval(cairo_t * pdc);
      bool mask_polygon(cairo_t * pdc);
      bool mask_poly_polygon(cairo_t * pdc);
      bool mask_combine(cairo_t * pdc);

      bool clip(cairo_t * pdc);
      bool clip_rect(cairo_t * pdc);
      bool clip_oval(cairo_t * pdc);
      bool clip_polygon(cairo_t * pdc);

      bool is_simple_positive_region();


   };


} // namespace draw2d_cairo


