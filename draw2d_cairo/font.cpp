#include "framework.h"
#include "aura/user/_user.h"


namespace draw2d_cairo
{


#ifdef WINDOWS


   class font_fam_c2
   {
   public:

      ENUMLOGFONTW lf;

   };

   int CALLBACK EnumFamCallBack(
   _In_ ENUMLOGFONTW   *lpelf,
   _In_ NEWTEXTMETRICW *lpntm,
   _In_ ::u32         FontType,
   _In_ LPARAM        lParam
   )
   {

      font_fam_c2 * pc2 = (font_fam_c2 *)lParam;

      pc2->lf = *lpelf;

      return true;

   }


#endif


   font::font()
   {

      m_pthis = this;

#if defined(USE_PANGO)

      m_pdesc = nullptr;

#else

      m_bToyQuotedFontSelection = false;

      m_pfont = nullptr;
      m_ft = nullptr;
      m_pfontface = nullptr;
      __zero(m_keyDone);

#endif

   }


   font::~font()
   {

      destroy();

   }


   ::e_status font::destroy_os_data()
   {

//#if defined(USE_PANGO)
//
//      // this structure stores a description of the style of font you'd most like
//      PangoFontDescription* m_pdesc;
//
//#else
//
//      FT_Face                    m_ft;
//      cairo_user_data_key_t      m_keyDone;
//      cairo_scaled_font_t* m_pfont;
//
//#endif
//
//      cairo_font_face_t* m_pfontface;
//      bool                       m_bToyQuotedFontSelection;

#if defined(USE_PANGO)

      if (m_pdesc == nullptr)
      {

         pango_font_description_free(m_pdesc);

      }

#else

      if (::is_set(m_pfontface))
      {

         cairo_font_face_destroy(m_pfontface);

      }

#endif

      return ::success;

   }


   ::e_status font::destroy()
   {

      synchronous_lock ml(cairo_mutex());
//      if(m_pdesc != nullptr)
//      {
// // the fonts are stored and managed by "font cache"
//         cairo_scaled_font_destroy(m_pdesc);
//
//         m_pdesc = nullptr;
//
//      }

//      if(m_pface != nullptr)
//      {
// // the fonts are stored and managed by "font cache"
//         cairo_font_face_destroy(m_pface);
//
//         m_pface = nullptr;
//
//      }

//      if(m_ft != nullptr)
      {

         //FT_Done_Face (m_ft);

         //       m_ft = nullptr;

      }

      destroy_os_data();

      ::write_text::font::destroy();

      return ::success;

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::write_text::font::dump(dumpcontext);

   }


   bool font::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

#if defined(USE_PANGO)

      m_pdesc = pango_font_description_new();

      double dFontScaler = 1.0;

      if(::is_set(pgraphics->m_puserinteraction))
      {

         dFontScaler = pgraphics->m_puserinteraction->font_scaler();

      }
      else
      {

         ::output_debug_string("Warning: No ::user::interaction font scaler!\n");

      }


      pango_font_description_set_family(m_pdesc, m_strFontFamilyName);

      pango_font_description_set_style(m_pdesc, m_bItalic ? PANGO_STYLE_ITALIC : PANGO_STYLE_NORMAL);

      pango_font_description_set_weight(m_pdesc, (PangoWeight)m_iFontWeight);

      if (m_eunitFontSize == ::draw2d::unit_pixel)
      {

         pango_font_description_set_absolute_size(m_pdesc, m_dFontSize * PANGO_SCALE);

      }
      else
      {

         pango_font_description_set_size(m_pdesc, m_dFontSize * PANGO_SCALE);

      }

      m_osdata[0] = m_pdesc;

#elif TOY_FONT_SELECTION

      m_bToyQuotedFontSelection = true;

      toy_font_selection();

#else

      auto pcairographics = __graphics(pgraphics);

      FT_Face ftface = pcairographics->ftface(m_strFontFamilyName, m_iFontWeight, m_bItalic);

      if (!ftface)
      {

         toy_font_selection();

      }
      else
      {

         cairo_font_face_t * pfontface = cairo_ft_font_face_create_for_ft_face(ftface, 0);

         cairo_status_t status = cairo_font_face_status(pfontface);

         m_pfontface = pfontface;

         m_osdata[0] = m_pfontface;

      }

#endif

      return m_osdata[0];

   }


   void font::toy_font_selection()
   {

      cairo_font_slant_t slant = get_cairo_font_slant();

      cairo_font_weight_t weight = get_cairo_font_weight();

      cairo_font_face_t* pfontface = cairo_toy_font_face_create(m_strFontFamilyName, slant, weight);

      cairo_status_t status = cairo_font_face_status(pfontface);

      m_pfontface = pfontface;

      m_osdata[0] = m_pfontface;

      if (pfontface)
      {

         m_bToyQuotedFontSelection = true;

      }

   }


   cairo_font_slant_t font::get_cairo_font_slant()
   {

      if (m_bItalic)
      {

         return CAIRO_FONT_SLANT_ITALIC;

      }
      else
      {

         return CAIRO_FONT_SLANT_NORMAL;

      }

   }


   cairo_font_weight_t font::get_cairo_font_weight()
   {

      if (m_iFontWeight >= 700)
      {

         return CAIRO_FONT_WEIGHT_BOLD;

      }
      else
      {

         return CAIRO_FONT_WEIGHT_NORMAL;

      }

   }



   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pgraphics)
   {

      return ::write_text::font::calculate_character_set(pgraphics);

   }


} // namespace draw2d_cairo



