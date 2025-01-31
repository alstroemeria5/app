#include "framework.h"
#include "core/user/user/_user.h"


const i32 xfplayer_view_line::AlignLeft = 1;
const i32 xfplayer_view_line::AlignRight = 2;


xfplayer_view_line::xfplayer_view_line()
{

   m_bColonPrefix = false;
   m_pContainer = nullptr;
   m_bEnhancedEmboss = true;
   m_bCacheEmboss = false;
   m_cr = argb(255, 255, 255, 255);
   m_colorOutline = argb(255, 0, 0, 0);
   m_nFont = 0;
   m_lpBitmapData = nullptr;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_rectangle.left = 0;
   m_rectangle.top = 0;
   m_rectangle.right = 0;
   m_rectangle.bottom = 0;
   m_bVisible = false;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_iIndent = 0;
   m_dAnimateProgressIncrement = 1.0;
   m_dXfplayerViewLineBlend = 1.0;
   m_iIndex = 0;

}


::e_status xfplayer_view_line::initialize_xfplayer_view_line(xfplayer_view_linea * pContainer)
{

   auto estatus = initialize(pContainer);
   
   if(!estatus)
   {
      
      return estatus;
      
   }
   
   m_font.create(this);

   m_pContainer = pContainer;
   m_bEnhancedEmboss = true;
   m_bCacheEmboss = false;
   m_nFont = 0;
   m_lpBitmapData = nullptr;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_rectangle.left = 0;
   m_rectangle.top = 0;
   m_rectangle.right = 0;
   m_rectangle.bottom = 0;
   m_bVisible = false;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_dAnimateProgress = 0;
   m_dAnimateProgressIncrement = 1.0;
   m_iIndex = 0;
   
   return estatus;
   
}


//xfplayer_view_line::xfplayer_view_line(const xfplayer_view_line & line)
//{
//
//   initialize((object *) &line);
//   
//   m_font.create(this);
//
//   operator = (line);
//
//}


xfplayer_view_line::~xfplayer_view_line()
{

}


bool xfplayer_view_line::PrepareLine(::draw2d::graphics_pointer & pgraphics, string str, i32 flags, const ::rectangle_i32 & rectangle)
{

   single_lock synchronouslock(m_pContainer->mutex());

   __UNREFERENCED_PARAMETER(flags);

   m_straLink.erase_all();
   m_iaLinkStart.erase_all();
   m_iaLinkEnd.erase_all();

   strsize               iChars;
   strsize               iStr;
   strsize               iStrLen;

   ASSERT(pgraphics != nullptr);

   iStrLen = str.get_length();

   iChars = -1;

   m_str.Empty();

   m_iIndent = 0;

   for (iStr = 0; iStr < iStrLen; iStr++)
   {

      add_char(str[iStr], iChars);

   }

   CalcCharsPositions(pgraphics, rectangle);


   return true;

}


void xfplayer_view_line::add_char(widechar wch, strsize & index)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_str += wch;

   index = m_str.get_length() - 1;

   if (m_iaPosition.get_size() < index + 2)
   {

      m_iaPosition.allocate(m_iaPosition.get_size() + 10);

   }

}


void xfplayer_view_line::add_char(widechar wch, strsize & index, ::write_text::font * pFont)
{

   single_lock synchronouslock(m_pContainer->mutex());

   __UNREFERENCED_PARAMETER(pFont);
   index++;
   if (m_iaPosition.get_size() < index + 2)
   {
      m_iaPosition.allocate(m_iaPosition.get_size() + 10);
   }
   m_str += wch;
   ASSERT(m_str.get_length() - 1 == index);

}


void xfplayer_view_line::GetPlacement(RECTANGLE_I32 * prectangle)

{

   single_lock synchronouslock(m_pContainer->mutex());

   *prectangle = m_rectangle;

}


bool xfplayer_view_line::_001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::rectangle_i32 & rectangle, rectangle_i32_array & rectaModified, bool bRecalcLayout)
{

   single_lock synchronouslock(m_pContainer->mutex());

   string strFinal(m_str);

   double dBlend;

   if (m_dXfplayerViewLineBlend <= 0.0)
      return true;
   if (m_dXfplayerViewLineBlend >= 1.0)
      dBlend = 1.0;
   else
      dBlend = m_dXfplayerViewLineBlend;

   pgraphics->set(m_font);

   //   pgraphics->SetBkMode(TRANSPARENT);

   point_i32 iMargin;
   iMargin.x = 3;
   iMargin.y = 3;

   if (!IsVisible())
   {

      return true;

   }

   if (bRecalcLayout || m_rectangleClient != rectangle)
   {

      m_bCacheEmboss = false;

      CalcCharsPositions(pgraphics, &rectangle);

   }

   ::rectangle_i32 rectTextOut;
   GetPlacement(rectTextOut);

   switch (m_iAnimateType)
   {
   case AnimateNoAnimate:
   {
      if (bDraw)
      {
         strsize iLink = 0;
         strsize iChar = 0;
         while (true)
         {
            pgraphics->set(m_font);
            if (iChar >= strFinal.get_length())
               break;
            if (iLink >= m_iaLinkStart.get_size())
            {
               const ::size_i32 & size = pgraphics->get_text_extent(strFinal.Left(iChar));
               embossed_text_out(pgraphics, strFinal.Mid(iChar), rectTextOut.left + size.cx, rectTextOut.top, 0, m_cr, m_colorOutline, strFinal.get_length() - iChar, dBlend);
               break;
            }
            else if (m_iaLinkStart[iLink] > iChar)
            {
               const ::size_i32 & size = pgraphics->get_text_extent(strFinal.Left(iChar));
               embossed_text_out(pgraphics, strFinal.Mid(iChar), rectTextOut.left + size.cx, rectTextOut.top, 0, m_cr, m_colorOutline, m_iaLinkStart[iLink], dBlend);
            }
            pgraphics->set(m_fontLink);
            const ::size_i32 & size = pgraphics->get_text_extent(strFinal.Left(m_iaLinkStart[iLink]));

            embossed_text_out(pgraphics, strFinal.Mid(m_iaLinkStart[iLink]), rectTextOut.left + size.cx, rectTextOut.top, 0, m_cr, m_colorOutline, m_iaLinkEnd[iLink] - m_iaLinkStart[iLink] + 1, dBlend);
            iChar = m_iaLinkEnd[iLink] + 1;
            iLink++;
         }
         if (GetSelection().m_iCharStartSource >= 0)
         {
            index iStart;
            index iLineStart;
            index iLineEnd;
            strsize iCharStart;
            strsize iCharEnd;
            GetSelection().GetNormalSelection(iLineStart, iCharStart, iLineEnd, iCharEnd);
            if (iLineStart < m_iIndex)
            {
               iStart = 0;
            }
            else if (iLineStart > m_iIndex)
            {
               iStart = m_iaPosition.get_count();
            }
            else
            {
               iStart = iCharStart;
            }
            index iEnd;
            if (iLineEnd < m_iIndex)
            {
               iEnd = -1;
            }
            else if (iLineEnd > m_iIndex)
            {
               iEnd = m_iaPosition.get_upper_bound();
            }
            else
            {
               iEnd = iCharEnd;
            }
            if (iStart < iEnd)
            {
               ::rectangle_i32 rectPlacement;
               GetPlacement(rectPlacement);
               ::rectangle_i32 rectangle = rectPlacement;
               size_i32 size1 = pgraphics->get_text_extent(strFinal.Left(iStart));
               size_i32 size2 = pgraphics->get_text_extent(strFinal.Left(iEnd + 1));
               rectangle.left = rectPlacement.left + size1.cx;
               rectangle.right = rectPlacement.left + size2.cx;
               ::image_pointer pimage;
               if (rectangle.area() > 0)
               {
                  pimage = m_pcontext->context_image()->create_image(rectangle.size());
                  pimage->fill(255, 255, 255, 255);
                  pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
                  pgraphics->flush();

                  //const ::point_i32 & point = pgraphics->GetViewportOrg();
                  //pimage->from(nullptr, pgraphics, point_i32 + rectangle.top_left(), rectangle.size());

                  {

                     image_source imagesource(pgraphics, rectangle);

                     ::rectangle_f64 rectangleTarget(rectangle.size());

                     image_drawing_options imagedrawingoptions(rectangleTarget);

                     image_drawing imagedrawing(imagedrawingoptions, imagesource);

                     pimage->g()->draw(imagedrawing);

                  }

                  //pimage->get_graphics()->fill_rectangle(0, 0, 16, 16, argb(255, 255, 0, 255));
                  pimage->invert();
                  //pimage->fill_channel(0, ::color::e_channel_blue);
                  pimage->fill_channel(255, ::color::e_channel_alpha);

                  {

                     image_source imagesource(pimage);

                     rectangle_f64 rectangleTarget(rectangle);

                     image_drawing_options imagedrawingoptions(rectangleTarget);

                     image_drawing imagedrawing(imagedrawingoptions, imagesource);

                     pgraphics->draw(imagedrawing);

                  }

               }

            }

         }

      }

   }
   break;
   case AnimateRHL:
   {
      i32 iLeft = m_iaPosition.element_at(0);
      i32 iLeftDiff = 0;
      i32 iLastLeftDiff = 0;
      i32 i;
      for (i = 0; i < m_iaPosition.get_size(); i++)
      {
         iLastLeftDiff = iLeftDiff;
         iLeftDiff = m_iaPosition.element_at(i) - iLeft;
         if ((i32)m_dAnimateProgress <= iLeftDiff)
         {
            //i--;
            break;
         }
      }

      ::draw2d::region_pointer prgn(this);

      string strFinal(m_str);
      string strLeft = strFinal.Right(strFinal.get_length() - i);
      i32 iLeftOffset;
      iLeftOffset = iLastLeftDiff - (i32)m_dAnimateProgress;
      ::rectangle_i32 rectTextOut;
      GetPlacement(rectTextOut);
      rectTextOut.left += iLeftOffset;
      if (bDraw)
      {
         embossed_text_out(pgraphics, strLeft, rectTextOut.left, rectTextOut.top,
                         0,
                         m_cr,
                         m_colorOutline,
                         strFinal.get_length(),
                         dBlend);
      }
      i32 iMaxCounter = maximum((i32)m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_rectangle.right - m_rectangle.left);
      i32 iRight = iMaxCounter - (i32)m_dAnimateProgress;
      if (iRight < m_rectangle.right)
      {
         i32 iRightEnd;
         i32 i;
         for (i = 0; i < m_iaPosition.get_size(); i++)
         {
            iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
            if (iRightEnd >= m_rectangle.right)
            {
               break;
            }
         }
         string strRight = strFinal.Left(i);
         rectTextOut.left = iRight;
         if (bDraw)
         {
            embossed_text_out(pgraphics, strRight, rectTextOut.left, rectTextOut.top, 0, m_cr, m_colorOutline, strFinal.get_length(), dBlend);
         }
      }

      if (::is_set(rectaModified))
      {
         ::rectangle_i32 baserect;
         prgn->get_bounding_box(baserect);
         rectaModified.add(baserect);

      }
   }
   break;
   default:
      ASSERT(false);
   }

   return true;

}


bool xfplayer_view_line::_001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::rectangle_i32 & rectangle, rectangle_i32_array & rectaModified, ::count * count, bool bRecalcLayout, ::color::color crColor, ::draw2d::pen_pointer sppen)
{

   single_lock synchronouslock(m_pContainer->mutex());

   ::rectangle_i32 rectPlacement;

   GetPlacement(rectPlacement);

   pgraphics->set(m_font);

   //   pgraphics->SetBkMode(TRANSPARENT);

   point_i32 iMargin;
   {
      iMargin.x = (::i32)(sppen->m_dWidth / 2.0);
      iMargin.y = (::i32)(sppen->m_dWidth / 2.0);
   }

   if (!IsVisible())
   {

      ::rectangle_i32 rectangle(m_rectInvalidate);

      if (!is_null(rectaModified))
      {
         ::rectangle_i32 baserect(rectangle);
         rectaModified.add(baserect);
      }

      Validate(rectangle);

      return true;
   }

   if (bRecalcLayout)
   {

      CalcCharsPositions(pgraphics, &rectangle);

      pgraphics->set(m_font);

   }


   switch (m_iAnimateType)
   {
   case AnimateNoAnimate:
   {
      string strFinal;
      strFinal = m_str;
      pgraphics->set(sppen);

      ::draw2d::brush_pointer brushText(e_create);

      brushText->create_solid(

      crColor);

      pgraphics->set(brushText);

      //pgraphics->set_text_color(crColor);

      ::rectangle_i32 rectTextOut;
      GetPlacement(rectTextOut);
      if (bDraw)
      {
         pgraphics->_DrawText(
         strFinal,
         rectTextOut,
         e_align_bottom_left);
      }
   }
   break;
   case AnimateRHL:
   {
      if (m_iaPosition.get_size() <= 0)
         break;
      //         i32 iLeft = m_iaPosition.element_at(0);
      i32 iLeftDiff = 0;
      //i32 iLastLeftDiff = 0;
      i32 i = 0;
      /*            for(i32 i = 0; i < m_iaPosition.get_size(); i++)
                  {
                      iLastLeftDiff = iLeftDiff;
                      iLeftDiff = m_iaPosition.element_at(i) - iLeft;
                      if(iLeftDiff >= (i32) m_dAnimateProgress)
                      {
                          break;
                      }
                  }*/

      string strFinal(m_str);
      string strLeft = strFinal.Right(strFinal.get_length() - i);
      i32 iLeftOffset;
      iLeftOffset = iLeftDiff - (i32)m_dAnimateProgress;

      pgraphics->set(sppen);
      ::draw2d::brush_pointer brushText(e_create);

      brushText->create_solid(crColor);

      pgraphics->set(brushText);

      pgraphics->set(m_font);
      ::rectangle_i32 rectTextOut;
      GetPlacement(rectTextOut);
      rectTextOut.left += iLeftOffset;
      if (bDraw)
      {
         
         pgraphics->_DrawText(strLeft, rectTextOut, e_align_bottom_left);

      }
      /*           pFont->TextOutEx(
                      pdcForeground,
                    rectTextOut,
                  1.0,
                  rectTextOut.height(),
                    strLeft,
                    m_iaPosition.get_data(),
                      m_iaPosition.get_size(),
                    0,
                      MapToFontEffect(m_iTextEffect));   */
      i32 iSpacing = 100;
      i32 iMaxCounter = maximum(
                            (i32)m_iaPosition.element_at(m_str.get_length())
                            - m_iaPosition.element_at(0) + iSpacing, m_rectangle.right - m_rectangle.left);
      i32 iRight = iMaxCounter - (i32)m_dAnimateProgress;
      if (iRight < m_rectangle.right)
      {
         /*    i32 iRightEnd;
             for(i32 i = 0; i < m_iaPosition.get_size(); i++)
             {
                 iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
                 if(iRightEnd >= m_rectangle.right)
                 {
                     break;
                 }
             }*/
         //string strRight = strFinal.Left(i);
         string strRight = strFinal;
         rectTextOut.left = iRight;
         if (bDraw)
         {

            pgraphics->_DrawText(strRight, rectTextOut, e_align_bottom_left);

         }
         /*               pFont->TextOutEx(
                             pdcForeground,
                           rectTextOut,
                        1.0,
                        rectTextOut.height(),
                           strRight,
                           m_iaPosition.get_data(),
                             m_iaPosition.get_size(),
                           0,
                             MapToFontEffect(m_iTextEffect));   */
      }

   }
   break;
   default:
      ASSERT(false);
   }

   return true;

}



/*void xfplayer_view_line::CalcCharsPositions(
::draw2d::graphics * pdcForeground,
   ref_array <  ::write_text::font > * pFonts,
   const ::rectangle_i32 & rectangle)
{
   m_bCacheEmboss = false;
   //::write_text::font * pFont;
//    ::draw2d::graphics * pdcForeground = m_ptwi->TwiGetDC();
   if(m_str.get_length() <= 0)
      return;
   if(pFonts->get_size() > 0)
   {
      i32 i, nFont, iFontFound, iMaxExtent, iLeft;
      ::size_i32 size;
      ::rectangle_i32 clientRect;
      nFont = 0;
      iFontFound = -1;
      for(nFont = 0; nFont < pFonts->get_size(); nFont++)
      {
         pdcForeground->set(pFonts->get_at(nFont)->GetFont());
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.get_length(),
            &size);
         if((m_iAlign & AlignLeft) > 0)
         {
            if(size.cx + m_rectangle.left <= rectangle.right)

            {
               iFontFound = nFont;
               break;
            }
         }
         else if((m_iAlign & AlignRight) > 0)
         {
            if(m_rectangle.right - size.cx >= 0)
            {
               iFontFound = nFont;
               break;
            }
         }
      }
      if(iFontFound < 0)
      {
         m_nFont = pFonts->get_size() - 1;
      }
      else
      {
         m_nFont = iFontFound;
      }
      pdcForeground->set(pFonts->get_at(m_nFont)->GetFont());
      if(m_iAlign == AlignLeft)
      {
         m_iaPosition[0] = m_rectangle.left + m_iIndent;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx + m_rectangle.left  + m_iIndent;
         }
         if(m_bAutoSizeX)
         {
            m_rectangle.right = m_rectangle.left  + m_iIndent + size.cx;
            }
         if(m_bAutoSizeY)
         {
            m_rectangle.bottom = m_rectangle.top + size.cy;
         }
      }
      else if(m_iAlign == AlignRight)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.get_length(),
            &size);
         iMaxExtent = size.cx;
         iLeft = m_rectangle.right - iMaxExtent;
         m_iaPosition[0] = iLeft;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx + iLeft;
         }
         if(m_bAutoSizeX)
         {
            m_rectangle.left = m_rectangle.right - size.cx;
            }
            if(m_bAutoSizeY)
            {
            m_rectangle.bottom = m_rectangle.top + size.cy;
         }
      }

   }

   else
   {
      i32 i; //, width;
      ::size_i32 size;
         m_iaPosition[0] = m_rectangle.left;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i ,
               &size);
            m_iaPosition[i] = m_rectangle.left + size.cx;
         }
      if(m_bAutoSizeX)
      {
         m_rectangle.right = m_rectangle.left + size.cx;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom = m_rectangle.top + size.cy;
      }
   }
//    m_ptwi->TwiReleaseDC(pdcForeground);

}*/


void xfplayer_view_line::CalcCharsPositions(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)

{

   single_lock synchronouslock(m_pContainer->mutex());

   m_bCacheEmboss = false;

   if (m_str.get_length() <= 0)
   {

      return;

   }

   i32 i;
   ::size_i32 size;
   ::rectangle_i32 rectangleClient(rectangle);

   m_rectangleClient = rectangleClient;
   ::rectangle_i32 rectPlacement;
   GetPlacement(rectPlacement);

   string strMain = m_str;

   m_font->m_dFontWidth = 1.0;

   m_font->set_modified();

   pgraphics->set(m_font);

   size = pgraphics->get_text_extent(strMain);

   if ((size.cx * 1.2) > rectangleClient.width())
   {

      m_floatRateX = (double) rectangleClient.width() / ((double) size.cx * 1.2);

   }
   else
   {

      m_floatRateX = 1.0;

   }

   ::write_text::text_metric tm;

   pgraphics->get_text_metrics(&tm);

   m_font->m_dFontWidth = m_floatRateX;

   m_font->set_modified();

   if (m_straLink.get_size() > 0)
   {
      *m_fontLink = *m_font;
      m_fontLink->set_underline();
   }


   if (m_bColonPrefix)
   {

      m_fontPrefix.create(this);

      *m_fontPrefix = *m_font;

      m_fontPrefix->m_dFontSize *= 0.5;


   }

   m_str.truncate(minimum(100, m_str.length()));

   if (m_bColonPrefix)
   {

      m_strPrefix = m_str.Left(maximum(0, m_str.find(":")));

      m_strRoot = m_str.Mid(maximum(0, m_str.find(":") + 1));

      m_strRoot.trim_left();

      pgraphics->set(m_fontPrefix);

      m_iaPosition[0] = 0;
      for (i = 1; i <= m_strPrefix.get_length(); i++)
      {
         m_dcextension.get_text_extent(
         pgraphics,
         m_strPrefix,
         i,
         size);
         m_iaPosition.add(size.cx);
      }
      int iSize = size.cx;
      m_dcextension.get_text_extent(
      pgraphics,
      " ",
      1,
      size);

      m_iaPosition.add(iSize + size.cx);
      
      pgraphics->set(m_font);

      for (i = 1; i <= m_strRoot.get_length(); i++)
      {

         m_dcextension.get_text_extent(
         pgraphics,
         m_strRoot,
         i,
         size);

         m_iaPosition.add(iSize + size.cx);

      }

   }
   else
   {

      pgraphics->set(m_font);

      m_iaPosition[0] = 0;

      for (i = 1; i <= m_str.get_length(); i++)
      {

         m_dcextension.get_text_extent(
         pgraphics,
         m_str,
         i,
         size);

         m_iaPosition[i] = size.cx;

      }

   }

   /*if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_rectangle.left + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pgraphics->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_rectangle.left + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.right = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom = m_rectangle.top + size.cy;
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         (HDC)pgraphics->get_os_data(),
         m_str,
         m_str.get_length(),
         &size);
      iMaxExtent = size.cx;
      iLeft = m_rectangle.right - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pgraphics->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.left = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom = m_rectangle.top + size.cy;
      }
   }
   pgraphics->set(pfontOld);*/
}

/*void xfplayer_view_line::CalcCharsPositions(
   ::draw2d::graphics *             pdcForeground,
   ::write_text::font *     pFont,
   const rectangle_i32 &           rectangle_i32)

{
   m_bCacheEmboss = false;
   if(m_str.get_length() <= 0)
      return;
    ::write_text::font * pfontOriginal = pdcForeground->get_current_font();
   pdcForeground->set(pFont->GetFont());
   i32 i, iLeft, iRight, iMaxExtent;
   ::size_i32 size;
   ::rectangle_i32 rectangleClient(rectangle);

   m_rectangleClient = rectangleClient;
   ::write_text::font * pfont = pFont;
   ::draw2d::graphics_pointer & pgraphics = pdcForeground;
   ASSERT(pfont != nullptr);
   ::rectangle_i32 rectPlacement;
   GetPlacement(rectPlacement);
   string strMain = m_str;
   GetTextExtentPoint32W(
      (HDC)pgraphics->get_os_data(),
      strMain,
      strMain.get_length(),
      &size);
   pgraphics->set(pfont->GetFont());
   if(size.cx > rectangleClient.width())
   {
      m_floatRateX =
         (float)
         rectangleClient.width()/
         size.cx;
   }
   else
   {
      m_floatRateX = 1.0;
   }

   m_font->delete_object();
   LOGFONTW lf;
   pfont->GetFont()->GetLogFont(&lf);
   pgraphics->set(pfont->GetFont());
   TEXTMETRICW tm;
   pgraphics->GetTextMetrics(&tm);
   lf.lfWidth = (long) (tm.tmAveCharWidth * m_floatRateX - 1);
   m_font->CreateFontIndirect(&lf);





   pgraphics->set(m_font);
   if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_rectangle.left + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_rectangle.left + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.right = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom = m_rectangle.top + size.cy;
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         pdcForeground->get_os_data(),
         m_str,
         m_str.get_length(),
         &size);
      iMaxExtent = size.cx;
      iLeft = m_rectangle.right - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_rectangle.left = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rectangle.bottom = m_rectangle.top + size.cy;
      }
   }
   pdcForeground->set(pfontOriginal);
}*/

void xfplayer_view_line::SetAutoSize(bool bAutoSize)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_bAutoSizeX = bAutoSize;
   m_bAutoSizeY = bAutoSize;
}

void xfplayer_view_line::SetAlign(i32 iAlign)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_iAlign = iAlign;
}

xfplayer_view_line & xfplayer_view_line::operator = (const xfplayer_view_line & src)
{
   m_pContainer = src.m_pContainer;
   m_bAutoSizeX = src.m_bAutoSizeX;
   m_bAutoSizeY = src.m_bAutoSizeY;
   m_str = src.m_str;
   m_iaPosition = src.m_iaPosition;
   m_iAlign = src.m_iAlign;
   m_rectangle.bottom = src.m_rectangle.bottom;
   m_rectangle.left = src.m_rectangle.left;
   m_rectangle.right = src.m_rectangle.right;
   m_rectangle.top = src.m_rectangle.top;
   m_lpBitmapData = src.m_lpBitmapData;
   m_nFont = src.m_nFont;
   m_iAnimateType = src.m_iAnimateType;
   m_iTextEffect = src.m_iTextEffect;
   m_dAnimateProgress = src.m_dAnimateProgress;
   m_dAnimateProgressIncrement = src.m_dAnimateProgressIncrement;
//   m_logfont = src.m_logfont;
   m_font = src.m_font;
   m_bEnhancedEmboss = src.m_bEnhancedEmboss;
   m_bCacheEmboss = false;
   m_dXfplayerViewLineBlend = src.m_dXfplayerViewLineBlend;
   m_iIndex = src.m_iIndex;
   return *this;
}

void xfplayer_view_line::Show(bool bShow)
{

   single_lock synchronouslock(m_pContainer->mutex());

   if (bShow && !m_bVisible)
   {
      m_bVisible = true;
      Invalidate();
      if (m_pContainer != nullptr)
      {
         m_pContainer->OnChildSetVisible(this, m_bVisible);
      }

   }
   else if (!bShow && m_bVisible)
   {
      m_bVisible = false;
      Invalidate();
      if (m_pContainer != nullptr)
      {
         m_pContainer->OnChildSetVisible(this, m_bVisible);
      }
   }
}


void xfplayer_view_line::OnTimerAnimate(::draw2d::graphics_pointer& pgraphics, rectangle_i32_array &  rectaModified)
{

   single_lock synchronouslock(m_pContainer->mutex());

   if (IsVisible())
   {

      switch (m_iAnimateType)
      {
      case AnimateNoAnimate:
         break;
      case AnimateRHL:
      {
         m_dAnimateProgress += m_dAnimateProgressIncrement;
         if (m_iaPosition.get_size() > 0)
         {
            if ((i32)m_dAnimateProgress > maximum(m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_rectangle.right - m_rectangle.left))
               m_dAnimateProgress = 0.0;
            ::rectangle_i32 rectangle;
            GetPlacement(rectangle);
            Invalidate();
            rectaModified.add(rectangle);
            /*to(
                pdcForeground,
                false,
                rectangle, rectaModified,
                false);*/
         }
      }
      break;
      default:
         ASSERT(false);
      }
   }
}

void xfplayer_view_line::SetAnimateType(i32 iAnimateType)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_iAnimateType = iAnimateType;
   m_dAnimateProgress = 0.0;

}

void xfplayer_view_line::SetTextEffect(i32 iTextEffect)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_iTextEffect = iTextEffect;
}

void xfplayer_view_line::SetEmbossPen(::draw2d::pen *pPen)

{

   single_lock synchronouslock(m_pContainer->mutex());

   m_lpPenEmboss = pPen;


}

void xfplayer_view_line::SetForegroundColor(::color32_t color32)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_colorForeground = color32;
}

/*ref_array <  ::write_text::font > * xfplayer_view_line::GetFonts()
{
    return &m_fonts;
}
*/
i32 xfplayer_view_line::MapToFontEffect(i32 iLineEffect)
{

   single_lock synchronouslock(m_pContainer->mutex());

   switch (iLineEffect)
   {
   case EffectSimple:
      return EffectSimple;
   case EffectEmbossed:
      return EffectEmbossed;
   }
   ASSERT(false);
   return -1;
}

void xfplayer_view_line::SetAnimateIncrement(double dIncrement)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_dAnimateProgressIncrement = dIncrement;
}

//void xfplayer_view_line::SetRedrawMode(i32 iMode)
//{
//  m_iRedrawMode = iMode;
//}

//void xfplayer_view_line::SetRenderWindow(::user::interaction_impl * pwindow)
//{
//  m_pRenderWnd = pwindow;
//}

void xfplayer_view_line::SetRenderCriticalSection(critical_section * pcs)
{
   __UNREFERENCED_PARAMETER(pcs);
   //    m_pcsRender =   pcs;
}

i32 xfplayer_view_line::SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_ppenLyricLeft = ppenLeft;
   m_ppenLyricRight = ppenRight;
   return true;
}

i32 xfplayer_view_line::SetLyricColors(::color::color crLeft, ::color::color crRight)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_colorLyricLeft = crLeft;
   m_colorLyricRight = crRight;
   return true;

}


void xfplayer_view_line::SetPlacement(const ::rectangle_i32 & rectangle)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_rectangle = rectangle;

   m_bPendingLayoutUpdate = true;

}


//i32 xfplayer_view_line::GetVmsFontCount()
/*{
   return m_fonts.get_size();
}

void xfplayer_view_line::AddVmsFont(::write_text::font * pfont)
{
   m_fonts.add(pfont);
}*/

void xfplayer_view_line::Invalidate(const rectangle_i32 & rectParam)
{

   single_lock synchronouslock(m_pContainer->mutex());

   ::rectangle_i32 rectPlacement;

   GetPlacement(rectPlacement);

   ::rectangle_i32 rectInvalidate;

   if (is_empty(&rectParam))
   {

      rectInvalidate = rectPlacement;

   }
   else
   {

      rectInvalidate = rectParam;

   }

   m_rectInvalidate.unite(m_rectInvalidate, rectInvalidate);

   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}


void xfplayer_view_line::Validate(const rectangle_i32 & rectParam)
{

   single_lock synchronouslock(m_pContainer->mutex());

   ::rectangle_i32 rectPlacement;

   GetPlacement(rectPlacement);

   ::rectangle_i32 rectValidate;

   if (is_empty(&rectParam))
   {

      rectValidate = rectPlacement;

   }
   else
   {

      rectValidate = rectParam;

   }

   m_rectInvalidate -= rectValidate;

   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}


bool xfplayer_view_line::IsVisible()
{

   single_lock synchronouslock(m_pContainer->mutex());

   return m_bVisible;

}


void xfplayer_view_line::embossed_text_out(::draw2d::graphics_pointer & pgraphics, const ::string & pcsz, i32 iLeft, i32 iTop, i32 iWidth, ::color32_t color32, ::color::color crOutline, strsize iLen, double dBlend)
{

   single_lock synchronouslock(m_pContainer->mutex());

   embossed_text_out(
   pgraphics,
   m_pimageMain,
   pcsz,

   iLeft,
   iTop,
   iWidth,
   color32,
   crOutline,
   iLen,
   dBlend);

}


void xfplayer_view_line::embossed_text_out(::draw2d::graphics_pointer & pgraphics, ::image * pimageCache, const ::string & pcsz, i32 iLeft, i32 iTop, i32 iWidth, ::color32_t color32, ::color::color crOutline, strsize iLen, double dBlend)
{

   single_lock synchronouslock(m_pContainer->mutex());

   __UNREFERENCED_PARAMETER(pimageCache);

   bool bSaveProcessing = !m_bEnhancedEmboss;

   if (bSaveProcessing)
   {

      pgraphics->begin_path();

      pgraphics->text_out(iLeft, iTop, string(pcsz, iLen));


      pgraphics->end_path();

      ::draw2d::pen_pointer pen;

      pen->create_solid(iWidth * 2, crOutline);

      pgraphics->set(pen);

      pgraphics->stroke_path();

      ::draw2d::brush_pointer brushText(e_create);

      brushText->create_solid(color32);

      pgraphics->set(brushText);

      pgraphics->text_out(iLeft, iTop, string(pcsz, iLen));


   }
   else
   {

      if (m_bEnhancedEmboss)
      {

         if (!m_bCacheEmboss || m_strCache != pcsz)

         {

            CacheEmboss(pgraphics, m_str, m_str.get_length(), m_pimageMain);

         }

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::point_i32 point;

      point.x = (::i32) (iLeft - ((maximum(2.0, m_floatRateX * 8.0)) / 2));

      point.y = (::i32) (iTop - ((maximum(2.0, m_floatRateX * 8.0)) / 2));

      {

         image_source imagesource(m_pimageMain);

         rectangle_f64 rectangleTarget(point, m_pimageMain->get_size());

         image_drawing_options imagedrawingoptions(rectangleTarget);

         imagedrawingoptions.opacity(dBlend);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

      if (m_bColonPrefix)
      {

         pgraphics->set(m_fontPrefix);

         ::size_i32 size;

         size = pgraphics->get_text_extent(m_strPrefix);

         auto psystem = m_psystem->m_pcoresystem;

         psystem->imaging().AlphaTextOut(pgraphics, iLeft, iTop + m_rectangle.height() - size.cy, m_strPrefix, (i32)m_strPrefix.get_length(), color32, dBlend);

         pgraphics->set(m_font);

         int iOffset;

         if (m_strPrefix.get_length() <= 0)
         {

            iOffset = 0;

         }
         else
         {

            iOffset = (int) (size.cx + size.cx / m_strPrefix.get_length());

         }

         psystem->imaging().AlphaTextOut(pgraphics, iLeft + iOffset, iTop, m_strRoot, (i32)m_strRoot.get_length(), color32, dBlend);



      }
      else
      {

         pgraphics->set(m_font);

         auto psystem = m_psystem->m_pcoresystem;

         psystem->imaging().AlphaTextOut(pgraphics, iLeft, iTop, pcsz, (i32)iLen, color32, dBlend);


      }


   }


}



void xfplayer_view_line::SetColors(::color32_t color32, ::color::color crOutline)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_cr = color32;
   m_colorOutline = crOutline;
}


//#ifdef WINDOWS_DESKTOP
//
//
//void xfplayer_view_line::GetLogFont(LOGFONTW &lf)
//{
//
//   single_lock synchronouslock(m_pContainer->mutex());
//
//   //lf = m_logfont;
//}
//
//
//#endif


void xfplayer_view_line::CacheEmboss(::draw2d::graphics_pointer & pgraphics, const ::string & pcsz, strsize iLen, ::image_pointer & pimageCache)
{

   single_lock synchronouslock(m_pContainer->mutex());

   if (!m_bEnhancedEmboss)
   {

      return;

   }

   if (m_bCacheEmboss && m_strCache == pcsz)

      return;

   m_strCache = pcsz;

   m_bCacheEmboss = true;

   //TRACE("CLyricViewLine::CacheEmboss: %s\n", pcsz);

   ::size_i32 size;

   pgraphics->set(m_font);

   m_dcextension.get_text_extent(pgraphics, pcsz, iLen, size);

   size.cx += (::i32)(2 * (maximum(2.0, m_floatRateX * 8.0)));
   size.cy += (::i32)(2 * (maximum(2.0, m_floatRateX * 8.0)));


   pimageCache = m_pcontext->context_image()->create_image(size);

   if (!pimageCache)
      return;

   pimageCache->fill(0, 0, 0, 0);

   ::draw2d::graphics_pointer pdcCache = pimageCache->get_graphics();

   pdcCache->set(m_font);

   pdcCache->set_alpha_mode(::draw2d::e_alpha_mode_set);

   pdcCache->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   draw2d::brush_pointer brushText(e_create);

   brushText->create_solid(argb(96, 96, 96, 96));

   pdcCache->set(brushText);

   ::size_i32 s;

   if (m_bColonPrefix)
   {

      pdcCache->set(m_fontPrefix);
      const ::size_i32 & size = pdcCache->get_text_extent(m_strPrefix);
      m_dcextension.text_out(pdcCache, (i32)(i32)((maximum(2.0, m_floatRateX * 4.0)) / 2), (i32)1 * (i32)((maximum(2.0, m_floatRateX * 4.0)) / 2) + m_rectangle.height() - size.cy, m_strPrefix, m_strPrefix.get_length(), s);
      pdcCache->set(m_font);

      int x = (i32) (s.cx + (s.cx / m_strPrefix.get_length()) + (i32)(i32)((maximum(2.0, m_floatRateX * 8.0)) / 2));

      int y = (i32) (1 * (i32)((maximum(2.0, m_floatRateX * 8.0)) / 2));

      m_dcextension.text_out(pdcCache, x, y, m_strRoot, m_strRoot.get_length(), s);

   }
   else
   {

      m_dcextension.text_out(pdcCache, (i32)(i32)((maximum(2.0, m_floatRateX * 8.0)) / 2), (i32)1 * (i32)((maximum(2.0, m_floatRateX * 8.0)) / 2), pcsz, iLen, s);


   }

   auto psystem = m_psystem->m_pcoresystem;

   psystem->imaging().channel_spread_set_color(pdcCache, nullptr, size, pdcCache, nullptr, 0, i32(maximum(1.0, m_floatRateX * 2.0 + 2)), argb(23, 23, 20, 23));

   pdcCache->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   psystem->imaging().channel_alpha_gray_blur(pdcCache, nullptr, size, pdcCache, nullptr, 0, i32(maximum(1.0, m_floatRateX * 2.5)));
   psystem->imaging().channel_alpha_gray_blur(pdcCache, nullptr, size, pdcCache, nullptr, 0, i32(maximum(1.0, m_floatRateX * 2.5)));

   pimageCache->set_rgb(0, 0, 0);

}


void xfplayer_view_line::SetFont(::write_text::font * pfont)
{

   single_lock synchronouslock(m_pContainer->mutex());

   m_font = pfont;

}


void xfplayer_view_line::PrepareURLLinks()
{

   single_lock synchronouslock(m_pContainer->mutex());

   string str;

   auto psystem = m_psystem->m_pcoresystem;

   auto pregex = psystem->create_pcre("/^|\\s|([;\"()]+))(((((http|https)://))|(www\\.))[0-9a-zA-Z./\\-_?=]+)(([;\"()]+)|\\s|$/");

   auto ptopic = pregex->create_topic(m_str);

   auto & rangea = ptopic->get_range_array();

   for(auto & range : rangea)
   {

      m_straLink.add(m_str.Mid(range.begin(), range.count()));
      m_iaLinkStart.add(range.begin());
      m_iaLinkEnd.add(range.upper_bound());

   }


}

bool xfplayer_view_line::CharHasLink(strsize iChar)
{

   single_lock synchronouslock(m_pContainer->mutex());

   return GetCharLink(iChar) > -1;
}

bool xfplayer_view_line::GetCharLink(string & str, strsize iChar)
{

   single_lock synchronouslock(m_pContainer->mutex());

   index iLink = GetCharLink(iChar);
   if (iLink < 0)
      return false;
   str = m_straLink[iLink];
   return true;
}

::user::enum_line_hit xfplayer_view_line::get_link(string & strUrl, const ::point_i32 & pointCursor)
{

   single_lock synchronouslock(m_pContainer->mutex());

   strsize iChar;
   ::user::enum_line_hit etest = hit_test(pointCursor, iChar);
   if (etest == ::user::e_line_hit_link)
   {
      GetCharLink(strUrl, iChar);
   }
   return etest;
}

index xfplayer_view_line::GetCharLink(strsize iChar)
{

   single_lock synchronouslock(m_pContainer->mutex());

   for (index i = 0; i < m_iaLinkStart.get_size(); i++)
   {
      if (iChar >= m_iaLinkStart[i] &&
            iChar <= m_iaLinkEnd[i])
      {
         return i;
      }
   }
   return -1;
}

::user::enum_line_hit xfplayer_view_line::hit_test(const point_i32 &pointCursorParam, strsize &iChar)
{

   single_lock synchronouslock(m_pContainer->mutex());

   bool bInside;
   const ::point_i32 & pointCursor = pointCursorParam;
   ::rectangle_i32 rectPlacement;
   GetPlacement(rectPlacement);
   bInside = rectPlacement.contains(pointCursor) != 0;
   if (!bInside)
   {
      iChar = -1;
      return ::user::e_line_hit_none;
   }
   else
   {
      if (CalcChar(pointCursor, iChar))
      {
         if (CharHasLink(iChar))
         {
            return ::user::e_line_hit_link;
         }
         else
         {
            return ::user::e_line_hit_normal;
         }
      }
      else
      {
         iChar = -1;
         return ::user::e_line_hit_none;
      }
   }

}

bool xfplayer_view_line::CalcChar(const ::point_i32 & point, strsize &iChar)
{

   single_lock synchronouslock(m_pContainer->mutex());

   ::rectangle_i32 rectPlacement;
   GetPlacement(rectPlacement);
   bool bInside = rectPlacement.contains(point) != 0;
   if (!bInside)
      return false;

   int x = point.x - rectPlacement.left;

   for (i32 i = 0; i < m_iaPosition.get_size() - 1; i++)
   {

      int iL = m_iaPosition[i];

      int iR = m_iaPosition[i + 1];

      int iM = (iR + iL) / 2;

      if (x >= iL && x < iM)
      {
         iChar = i;
         return true;
      }
      if (x >= iM && x < iR)
      {
         iChar = i + 1;
         return true;
      }
   }
   return false;
}


void xfplayer_view_line::OnMouseMove(::message::message * pmessage)
{

   single_lock synchronouslock(m_pContainer->mutex());

   auto pmouse = pmessage->m_pmouse;
   strsize iChar;
   if (CalcChar(pmouse->m_point, iChar))
   {

      if (CharHasLink(iChar))
      {

         auto psession = get_session()->m_paurasession;

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pcursor = pwindowing->get_cursor(e_cursor_hand);

         pmouse->m_pcursor = pcursor;

      }

   }
   /*
   lyric_view_line_selection & selection = GetSelection();

   if(selection.GetState() == lyric_view_line_selection::StateTracking)
   {

      bool bInside;
      i32 iToken;
      i32 iChar;
      ::rectangle_i32 rectPlacement;

      GetPlacement(rectPlacement);
      bInside = rectPlacement.contains(point) != 0;

      if(!bInside)
      {
         if(point.y < rectPlacement.top
            || (point.y <= rectPlacement.bottom &&
            point.x < rectPlacement.left))
         {
            selection.SetSelBefore(*this);
            GetWndRender()->Redraw(rectPlacement);
         }
         else
         {
            selection.SetSelAfter(*this);
            GetWndRender()->Redraw(rectPlacement);
         }
         return false;
      }
      else // bInside == true
      {
         u32 fwKeys = user; // key flags
         if(m_tokenaMain.get_size() <= 0)
            return false;
         if(CalcChar(point, iToken, iChar))
         {
            selection.m_item.SetTokenEnd(iToken);
            selection.m_item.SetCharEnd(iChar);
            GetWndRender()->Redraw(rectPlacement);
         }
         else
         {
            if(point.x < m_tokenaMain.element_at(0).get_position())
            {
               selection.SetSelBefore(*this);
            }
            else
            {
               selection.SetSelAfter(*this);
            }
            GetWndRender()->Redraw(rectPlacement);
         }
         return true;
      }
   }
   else
   {
      if(is_hover())
      {
         update_hover(point);
      }
      else
      {
         bool bInside;
         ::rectangle_i32 rectPlacement;

         GetPlacement(rectPlacement);
         bInside = rectPlacement.contains(point);
         if(bInside)
         {
            update_hover(point);
         }
      }

   }*/

   if (GetSelection().OnMouseMove(*this, (::u32)pmouse->m_nFlags, pmouse->m_point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_view_line::OnSetCursor(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   //if(is_hover())
   //{
   //
   //    pmouse->m_ecursor = cursor_hand;
   //
   //    return true;
   //
   //}

}


void xfplayer_view_line::OnLButtonDown(::message::message * pmessage)
{

   single_lock synchronouslock(m_pContainer->mutex());

   auto pmouse = pmessage->m_pmouse;

   if (GetSelection().OnLButtonDown(*this, (::u32)pmouse->m_nFlags, pmouse->m_point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_view_line::OnLButtonUp(::message::message * pmessage)
{

   single_lock synchronouslock(m_pContainer->mutex());

   auto pmouse = pmessage->m_pmouse;

   strsize iChar;

   if (CalcChar(pmouse->m_point, iChar))
   {

      if (CharHasLink(iChar))
      {

         string str;

         str = m_straLink[GetCharLink(iChar)];

         ASSERT(m_oswindow->is_window());

         auto phyperlink = __create_new < ::hyperlink >();

         phyperlink->m_strLink = str;

         phyperlink->run();

      }

   }

   if (GetSelection().OnLButtonUp(*this, (::u32)pmouse->m_nFlags, pmouse->m_point))
   {

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

   }

}


void xfplayer_view_line::_001OnTimer(::timer * ptimer)
{

   __UNREFERENCED_PARAMETER(ptimer);

   //if(GetSelection().OnTimer(*this, user))
   //{
   //
   //    return true;
   //
   //}

}


::write_text::font * xfplayer_view_line::GetFont()
{

   single_lock synchronouslock(m_pContainer->mutex());

   return m_font;

}


void xfplayer_view_line::set_blend(double d)
{

   single_lock synchronouslock(m_pContainer->mutex());

   ASSERT(d >= 0.0);

   ASSERT(d <= 1.0);

   if (d < 0.0 || d > 1.0)
   {

      return;

   }

   m_dXfplayerViewLineBlend = d;

}


void xfplayer_view_line::update_hover(point_i32 &pointCursor)
{

   single_lock synchronouslock(m_pContainer->mutex());

   ::index iLine = m_iIndex;

   strsize iChar;

   ::user::enum_line_hit etest = hit_test(pointCursor, iChar);

   if (etest == ::user::e_line_hit_link)
   {

      if (m_iLinkHoverIndex != GetLinkIndex(iLine, iChar))
      {

         m_iLinkHoverIndex = GetLinkIndex(iLine, iChar);

         ::rectangle_i32 rectangle;

         GetPlacement(rectangle);

         get_interaction()->set_need_redraw();

      }

   }
   else
   {

      if (m_iLinkHoverIndex != -1)
      {

         m_iLinkHoverIndex = -1;

         ::rectangle_i32 rectangle;

         GetPlacement(rectangle);

         get_interaction()->set_need_redraw();

      }

   }

}


bool xfplayer_view_line::is_hover()
{

   if (m_iLinkHoverIndex >= 0)
   {

      return true;

   }
   else
   {

      return false;

   }

}


index xfplayer_view_line::GetLinkIndex(index iLine, strsize iChar)
{

   single_lock synchronouslock(m_pContainer->mutex());

   if (!has_link())
   {

      return -1;

   }

   if (iLine != m_iIndex)
   {

      return -1;

   }

   return GetCharLink(iChar);

}


bool xfplayer_view_line::has_link()
{

   single_lock synchronouslock(m_pContainer->mutex());

   return m_iaLinkStart.get_count() > 0;

}


::user::interaction * xfplayer_view_line::get_interaction()
{

   return m_pContainer->m_pinteraction;

}


inline XfplayerViewLineSelection & xfplayer_view_line::GetSelection()
{

   single_lock synchronouslock(m_pContainer->mutex());

   if (m_pContainer == nullptr)
      return m_selection;
   else
      return m_pContainer->GetSelection();
}
