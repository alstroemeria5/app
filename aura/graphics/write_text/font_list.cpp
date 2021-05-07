#include "framework.h"
#include "aura/user/_user.h"

#include <math.h>

#define BOX 0
#define BOX_SEL 1
#define BOX_HOVER 2


namespace write_text
{


   font_list_item::font_list_item()
   {

   }


   font_list_item::~font_list_item()
   {

   }


   font_list::font_list()
   {

      m_bUpdatesHooked = false;

      m_bUpdating = false;

      m_iSelUpdateId = -1;

      m_puserinteraction = nullptr;
      m_rectMargin = rectangle_i32(5, 5, 5, 5);
      m_iSel = -1;
      m_iHover = -1;

      defer_create_mutex();

      m_dwaFg.add(argb(255, 80, 80, 80));
      m_dwaFg.add(argb(255, 45, 45, 45));
      m_dwaFg.add(argb(255, 255, 255, 255));

      m_dwaBg.add(argb(0, 0, 0, 0));
      m_dwaBg.add(argb(128, 128, 200, 152));
      m_dwaBg.add(argb(128, 80, 80, 80));

      m_etype = type_single_column;

   }


   font_list::~font_list()
   {


   }


   void font_list::defer_font_enumeration(::subject::subject * psubject)
   {

      try
      {

         synchronous_lock synchronouslock(mutex());

         if (m_pfontenumeration.is_null())
         {

            auto psystem = m_psystem->m_paurasystem;

            auto pdraw2d = psystem->draw2d();

            pdraw2d->write_text()->fonts()->defer_create_font_enumeration(psubject);

            m_pfontenumeration = pdraw2d->write_text()->fonts()->m_pfontenumeration;

         }

      }
      catch (...)
      {

      }

   }


   void font_list::update_font_enumeration(::subject::subject * psubject)
   {

      try
      {

         synchronous_lock synchronouslock(mutex());

         defer_font_enumeration(psubject);

         m_pfontenumeration->update(psubject);

      }
      catch (...)
      {

      }

   }


   void font_list::sync_font_enumeration(::subject::subject * psubject)
   {

      try
      {

         synchronous_lock synchronouslock(mutex());

         defer_font_enumeration(psubject);

         m_pitema = m_pfontenumeration->m_pitema;

      }
      catch (...)
      {

      }

   }


   bool font_list::set_sel_by_name(string str)
   {

      synchronous_lock synchronouslock(mutex());

      index iSel = find_name(str);

      m_iSel = iSel;

      m_strFontFamily = str;

      return m_iSel >= 0;

   }


   void font_list::_001OnDrawWide(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::rectangle_i32 rectClient = pgraphics->m_puserinteraction->get_client_rect();

      rectClient += pgraphics->m_puserinteraction->get_viewport_offset();

      auto plistdata = m_plistdata;

      if (plistdata.is_null())
      {

         //m_puserinteraction->set_need_layout();

         //m_puserinteraction->set_need_redraw();

         return;

      }

      auto cListDataCount = plistdata->get_count();

      for (int i = 0; i < cListDataCount; i++)
      {

         if (i == m_iSel || i == m_iHover)
         {

            continue;

         }

         auto pitem = plistdata->element_at(i);

         if (!pitem)
         {

            continue;

         }

         text_box * pbox = &pitem->m_box[BOX];

         if (!pbox->m_bInit)
         {

            continue;

         }

         if (!pbox->m_rectangle.intersects(rectClient))
         {

            continue;

         }

         if (!pbox->m_bOk)
         {

            pbox->update(this, BOX, pitem->m_strSample);

         }

         pgraphics->draw(pbox->m_rectangle, pbox->m_pimage);

      }

      if (m_iSel >= 0)
      {

         auto pitem = plistdata->element_at(m_iSel);

         if (pitem)
         {

            text_box* pbox = &pitem->m_box[BOX_SEL];

            if (!pbox->m_bInit)
            {

               update_extents(plistdata, pitem, pgraphics, BOX_SEL);

            }

            if (!pbox->m_bOk)
            {

               pbox->update(this, BOX_SEL, pitem->m_strSample);

            }

            pgraphics->draw(pbox->m_rectangle, pbox->m_pimage);

         }

      }

      if (m_iHover >= 0 && m_iHover != m_iSel)
      {

         auto pitem = plistdata->element_at(m_iHover);

         if (pitem)
         {

            text_box* pbox = &pitem->m_box[BOX_HOVER];

            if (!pbox->m_bInit)
            {

               update_extents(plistdata, pitem, pgraphics, BOX_HOVER);

            }

            if (!pbox->m_bOk)
            {

               pbox->update(this, BOX_HOVER, pitem->m_strSample);

            }

            pgraphics->draw(pbox->m_rectangle, pbox->m_pimage);

         }

      }

   }


   void font_list::_001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      auto plistdata = m_plistdata;

      rectangle_i32 rectClient = pgraphics->m_puserinteraction->get_client_rect();

      rectClient += pgraphics->m_puserinteraction->get_viewport_offset();

      __pointer(::aura::session) psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = pwindowing->get_cursor_position();

      pgraphics->m_puserinteraction->_001ScreenToClient(pointCursor);

      pointCursor += pgraphics->m_puserinteraction->get_viewport_offset();

      bool bCheckHover = true;

      bool bIntersected = false;

      for (int i = 0; i < plistdata->get_count(); i++)
      {

         if (plistdata->element_at(i) == nullptr)
         {

            continue;

         }

         int iBox;

         iBox = BOX;

         auto plistdata = m_plistdata;

         text_box * pbox = &plistdata->element_at(i)->m_box[iBox];

         rectangle_i32 rectangle = pbox->m_rectangle;

         rectangle.right = rectangle.left + m_size.cx;

         if (!pbox->m_bOk)
         {

            pbox->update(this, iBox, plistdata->element_at(i)->m_strSample);

         }

         if (!rectClient.intersects(rectangle))
         {

            if (bIntersected)
            {

               break;

            }

            continue;

         }

         if (bCheckHover && rectangle.contains_y(pointCursor.y))
         {

            pgraphics->m_puserinteraction->m_itemHover = __new(::user::item({ ::user::e_element_item, i }));

            m_iHover = i;

            bCheckHover = false;

         }

         bIntersected = true;

         if (i == m_iSel)
         {

            if (!bCheckHover && i == m_iHover)
            {

               pgraphics->fill_rectangle(rectangle, pgraphics->m_puserinteraction->get_color(pgraphics->m_puserstyle, ::user::e_element_background, ::user::e_state_selected | ::user::e_state_hover));

            }
            else
            {

               pgraphics->fill_rectangle(rectangle, pgraphics->m_puserinteraction->get_color(pgraphics->m_puserstyle, ::user::e_element_background, ::user::e_state_selected));

            }

         }
         else if (!bCheckHover && i == m_iHover)
         {

            auto color = pgraphics->m_puserinteraction->get_color(pgraphics->m_puserstyle, ::user::e_element_background, ::user::e_state_hover);

            int iA = color.alpha;

            pgraphics->fill_rectangle(rectangle, color);

         }

         pgraphics->draw(pbox->m_rectangle, pbox->m_pimage);

      }

   }


   void font_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_etype == type_wide)
      {

         _001OnDrawWide(pgraphics);

      }
      else
      {

         _001OnDrawSingleColumn(pgraphics);

      }

   }


   void font_list::update_extents(font_list_data * plistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, index iBox)
   {

      text_box* pbox = &pitem->m_box[iBox];

      synchronous_lock synchronouslock(mutex());

      if (::is_null(pbox))
      {

         return;

      }

      if (!pbox->m_bInit)
      {

         synchronouslock.unlock();

         ::size_f64 s;

         string strText = m_strTextLayout;

         string str = pitem->m_strName;

         pbox->m_pfont.create(this);

         if (str.compare_ci("GOUDY STOUT") == 0)
         {

            output_debug_string("test05");

         }

         pbox->m_pfont->create_pixel_font(str, plistdata->m_iaSize[iBox]);

         pgraphics->set(pbox->m_pfont);

         pbox->m_pfont->m_echarseta = pitem->m_echarseta;

         if (iBox == 0)
         {

            strText = m_strTextLayout;

            if (strText.is_empty() ||
               (pbox->m_pfont->get_char_set(pgraphics) != ::char_set_ansi
                  && pbox->m_pfont->get_char_set(pgraphics) != ::char_set_default))
            {

               strText = ::write_text::font::get_sample_text(pbox->m_pfont->m_echarset);

               if (strText.is_empty())
               {

                  strText = pitem->m_strName;

               }

            }

            if (strText.has_char())
            {

               s = pgraphics->GetTextExtent(strText);

            }

            if (strText.has_char() && s.area() <= 0)
            {

               string strSample;

               int maxarea = 0;

               ::e_char_set echarsetFound = pbox->m_pfont->get_char_set(pgraphics);

               size_i32 sSample;

               if (maxarea <= 0)
               {

                  strSample = m_strTextLayout;

                  if (strSample.has_char())
                  {

                     sSample = pgraphics->GetTextExtent(strSample);

                     if (sSample.area() > maxarea)
                     {

                        maxarea = (int)(sSample.area());

                        strText = strSample;

                        s = sSample;

                     }

                  }

               }

               if (maxarea <= 0)
               {

                  strSample = pitem->m_strName;

                  if (strSample.has_char())
                  {

                     sSample = pgraphics->GetTextExtent(strSample);

                     if (sSample.area() > maxarea)
                     {

                        maxarea = (int)(sSample.area());

                        strText = strSample;

                        s = sSample;

                     }

                  }

               }

               pbox->m_pfont->m_echarset = echarsetFound;

            }

            pitem->m_strSample = strText;

         }
         else
         {

            pbox->m_pfont->m_echarset = pitem->m_box[0].m_pfont->m_echarset;

            s = pgraphics->GetTextExtent(pitem->m_strSample);

         }

         s.cx += m_rectMargin.left + m_rectMargin.right;

         s.cy += m_rectMargin.top + m_rectMargin.bottom;

         pbox->m_size = s;

         pbox->m_bOk = false;

         pbox->m_bInit = true;

      }

   }


   void font_list::set_need_layout()
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->set_need_layout();

      }

      set_need_redraw();

   }


   void font_list::set_need_redraw()
   {
      
      if (::is_null(m_puserinteraction))
      {

         return;

      }

      m_puserinteraction->set_need_redraw();

      m_puserinteraction->post_redraw();

   }


   ::e_status font_list::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   void font_list::on_subject(::subject::subject * psubject)
   {

      if (psubject->m_esubject == e_subject_prepare)
      {

         e_id eid = (e_id)psubject->id().i64();

         if (eid == id_font_extents)
         {

            update_extents();

         }
         else if (eid == id_font_list_layout)
         {

            layout();

         }
         else if (eid == id_font_list_total_size)
         {

            set_need_layout();

         }
         else if (eid == id_font_list_redraw)
         {

            set_need_redraw();

         }

      }

   }


   void font_list::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      e_id eid = (e_id)psubject->id().i64();

      if (eid == id_font_enumeration)
      {

         sync_font_enumeration(psubject);

         if (!m_rectClient.is_empty())
         {

            psubject->set_modified();

         }

      }
      else if (eid == id_font_extents)
      {

         update_extents();

      }
      else if (eid == id_font_list_layout)
      {

         layout();

      }
      else if (eid == id_font_list_total_size)
      {

         set_need_layout();

      }
      else if (eid == id_font_list_redraw)
      {

         set_need_redraw();

      }

   }

   
   void font_list::set_font_list_type(enum_type etype)
   {

      m_etype = etype;

      if (!m_bUpdatesHooked)
      {

         m_bUpdatesHooked = true;

         __pointer(::aura::system) psystem = m_psystem;

         psystem->delivery_for(id_font_enumeration, this, true);

         delivery_for(id_font_extents, this, true);

         delivery_for(id_font_list_layout, this, true);

         delivery_for(id_font_list_total_size, this, true);

      }
      else
      {

         set_modified(id_font_extents);

      }

   }


   font_list::enum_type font_list::get_font_list_type() const
   {

      return m_etype;

   }


   void font_list::update_extents()
   {

      int_array iaSize;

      int iBaseSize;

      auto plistdata = m_plistdata;

      bool bSameSize = false;

      {

         synchronous_lock synchronouslock(mutex());

         if (!m_pitema)
         {

            return;

         }

         if (m_etype != type_single_column && !m_rectClient)
         {

            return;

         }

         //if (m_rectClient.is_empty())
         //{

         //   return;

         //}

         if (m_etype == type_wide)
         {

            int iBaseHeight = maximum(250, m_rectClient.height());

            iBaseHeight = iBaseHeight + 250;

            int iStep = 200;

            int iDiv = 10;

            iBaseSize = ((iBaseHeight / iStep) * iStep) / iDiv;

         }
         else
         {

            iBaseSize = 18;

         }

         if (plistdata.is_set() &&
            plistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId
            && (m_etype == type_single_column ||
               plistdata->m_rectClient == m_rectClient))
         {

            set_modified(id_font_list_layout);

            return;

         }

         if (plistdata.is_set() && iBaseSize == plistdata->m_iBaseSize)
         {

            if (plistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
            {

               set_modified(id_font_list_layout);

               return;

            }

            bSameSize = true;

         }

         if (m_etype == type_wide)
         {

            iaSize.add(iBaseSize * 16 / 40);

            iaSize.add(iBaseSize * 24 / 40);

            iaSize.add(iBaseSize * 32 / 40);

         }
         else
         {

            iaSize.add(18);

         }

         if (plistdata.is_set() && iaSize == plistdata->m_iaSize
            && plistdata->m_iUpdateId == m_pfontenumeration->m_iUpdateId)
         {

            set_modified(id_font_list_layout);

            return;

         }
         else
         {

            bSameSize = false;

         }

      }

      if (plistdata == nullptr)
      {

         plistdata = __create_new < font_list_data >();

         plistdata->m_iSerial = 0;

         m_plistdata = plistdata;

         plistdata->set_size(m_pitema->get_count());

      }
      else
      {

         // Remove absent/erased fonts

         __pointer(font_list_item) pitem;

         {

            synchronous_lock synchronouslock(mutex());

            for (index iItem = 0; iItem < plistdata->get_count(); )
            {

               auto pitem = plistdata->element_at(iItem);

               if (pitem && pitem->m_strName.has_char() && !m_pfontenumeration->has_font_name(pitem->m_strName))
               {

                  plistdata->erase_at(iItem);

               }
               else
               {

                  iItem++;

               }

            }

            // Make room for new fonts

            for (index iItem = 0; iItem < m_pitema->get_count(); iItem++)
            {

               auto pitem = plistdata->element_at(iItem);

               if (pitem && pitem->m_strName.has_char() && pitem->m_strName != m_pitema->ptr_at(iItem)->m_strName)
               {

                  __pointer(font_list_item) pitemNewEmpty;

                  plistdata->insert_at(iItem, pitemNewEmpty);

               }

            }

            ASSERT(plistdata->get_size() == m_pitema->get_count());

            plistdata->m_iSerial++;

         }

         plistdata->m_rectClient = m_rectClient;

         plistdata->m_iUpdateId = m_pfontenumeration->m_iUpdateId;

         plistdata->m_iUpdatedCount = 0;

         plistdata->m_bLayoutStillIntersect = true;

         m_iLayoutSerial = 0;

      }

      plistdata->m_iBaseSize = iBaseSize;

      plistdata->m_iaSize = iaSize;

      auto iFontCount = plistdata->get_count();

      auto pcounter = fork_count(this, plistdata->get_count(), [this, plistdata, bSameSize](index iOrder, index iStart, index iCount, index iScan)
      {

         ::draw2d::graphics_pointer g(e_create);

         g->CreateCompatibleDC(nullptr);

         ::draw2d::graphics_pointer & pgraphics = g;

      restart:

         index iSerial = plistdata->m_iSerial;

         string strText = m_strTextLayout;

         size_i32 s;

         ::rectangle_i32 rectangle;

         __pointer(font_list_item) plistitem;

         __pointer(font_enum_item) penumitem;

         single_lock lock(mutex());

         for (index iItem = iStart; iItem < plistdata->get_count(); iItem += iScan)
         {

            {

               synchronous_lock synchronouslock(mutex());

               if (plistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               if (iItem >= m_pitema->get_count())
               {

                  break;

               }

               plistitem = plistdata->element_at(iItem);

               penumitem = m_pitema->element_at(iItem);

            }

            bool bNew = false;

            if (!penumitem)
            {

               continue;

            }

            if (!plistitem || plistitem->m_strFont.is_empty())
            {

               bNew = true;

               plistitem = __new(font_list_item);

               plistitem->m_iItem = iItem;

               plistitem->m_strFont = penumitem->m_strName;

               plistitem->m_strName = penumitem->m_strName;

               plistitem->m_echarseta = penumitem->m_echarseta;

            }
            else if (plistitem->m_strFont != penumitem->m_mapFileName[0])
            {

               TRACE("what?!?!");

               continue;

            }

            if (bNew || !bSameSize)
            {

               update_extents(plistdata, plistitem, pgraphics, 0);

            }

            {

               synchronous_lock synchronouslock(mutex());

               if (plistdata->m_iSerial != iSerial)
               {

                  goto restart;

               }

               plistdata->element_at(iItem) = plistitem;

               if (!m_bLayoutWideStillIntersect)
               {

                  continue;

               }

            }

         }

      });

      if (pcounter->lock(30_s))
      {

         {

            synchronous_lock synchronouslock(mutex());

            if (plistdata != m_plistdata)
            {

               return;

            }

            set_modified(id_font_list_layout);

         }

         pcounter = fork_count(this, plistdata->get_count(), [this, plistdata](index iOrder, index iStart, index iCount, index iScan)
         {

            auto iSerial = plistdata->m_iSerial;

            ::draw2d::graphics_pointer g(e_create);

            g->CreateCompatibleDC(nullptr);

            ::draw2d::graphics_pointer & pgraphics = g;

            string strText = m_strTextLayout;

            size_i32 s;

            ::rectangle_i32 rectangle;

            for (index i = iStart; i < iCount && ::task_get_run(); i += iScan)
            {

               auto pitem = plistdata->element_at(i);

               for (index iBox = 1; iBox < plistdata->m_iaSize.get_count(); iBox++)
               {

                  if (plistdata->m_iSerial != iSerial)
                  {

                     return;

                  }

                  update_extents(plistdata, pitem, pgraphics, iBox);

               }

            }

         });

         if (pcounter->lock(30_s))
         {

            {

               synchronous_lock synchronouslock(mutex());

               if (plistdata != m_plistdata)
               {

                  return;

               }

               set_modified(id_font_list_layout);

            }

         }

      }

   }


   void font_list::layout()
   {

      synchronous_lock synchronouslock(mutex());

      ::size_i32 sizeTotal;

      if (m_etype == type_wide)
      {

         sizeTotal = layout_wide();

      }
      else
      {

         sizeTotal = layout_single_column();

      }

      if (sizeTotal != m_size)
      {

         m_size = sizeTotal;

         set_modified(id_font_list_total_size);

      }

   }


   ::size_i32 font_list::layout_wide()
   {

      if (::is_null(m_puserinteraction))
      {

         return ::size_i32();

      }

      TRACE("font_list::layout_wide");

      synchronous_lock synchronouslock(mutex());

      ::size_i32 sizeTotal;

      bool bIntersected = false;

      m_bLayoutWideStillIntersect = true;

      string strText = m_strTextLayout;

      size_i32 s;

      int iMargin = 40;

      int w = m_rectClient.width() - iMargin * 2;

      int iPadding = 15;

      int x = iMargin;

      int y = iMargin + iPadding;

      int h = 0;

      int hExtra = 0;

      int nextx;

      sizeTotal.cx = m_rectClient.width();

      rectangle_i32 rectClient = m_puserinteraction->get_client_rect();

      rectClient += m_puserinteraction->get_viewport_offset();

      auto plistdata = m_plistdata;

      if (plistdata.is_null())
      {

         return sizeTotal;

      }

      int iLineStart = 0;

      auto iFontCount = plistdata->get_count();

      for (int i = 0; i < iFontCount; i++)
      {

         font_list_item * pitem = plistdata->element_at(i);

         if (pitem
            && !m_pfontenumeration->has_font_name(pitem->m_strFont)
            && !m_pfontenumeration->has_font_name(pitem->m_strName))
         {

            //plistdata->erase_at(i);

            //iFontCount = plistdata->get_count();

            //i--;

            continue;

         }

         if (pitem == nullptr)
         {

            sizeTotal.cy = y + hExtra;

            return sizeTotal;

         }

         size_i32 & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;

         x += iPadding;

         nextx = x + s.cx + iPadding;

         if (nextx > w )
         {

            int iDen = (i - iLineStart - 1);

            if (iDen >= 1)
            {

               int iInc = (w - x + iPadding * 4) / (i - iLineStart - 1);

               int iOffset = iInc;

               for (int j = iLineStart + 1; j < i; j++)
               {

                  font_list_item * pitem2 = plistdata->element_at(j);

                  auto & rect2 = pitem2->m_box[0].m_rectangle;

                  rect2.offset_x(iOffset);

                  iOffset += iInc;

               }

            }

            iLineStart = i;

            x = iMargin + iPadding;

            nextx = x + s.cx + iPadding;

            y += h + iPadding;

            h = 0;

            hExtra = 0;

         }

         //pgraphics->text_out(x + m_rectMargin.left,y + m_rectMargin.top,strText);

         rectangle.left = x;

         rectangle.top = y;

         rectangle.right = rectangle.left + s.cx;

         rectangle.bottom = rectangle.top + s.cy;

         if (rectangle.intersects(rectClient))
         {

            bIntersected = true;

         }
         else
         {

            if (bIntersected)
            {

               bIntersected = false;

               m_bLayoutWideStillIntersect = false;

            }

         }

         x = nextx;

         h = maximum(h, s.cy);

         hExtra = maximum(hExtra, s.cy);

      }

      for (int i = 0; i < iFontCount; i++)
      {

         font_list_item * pitem = plistdata->element_at(i);

         size_i32 & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;

         for (index j = 1; j < 3; j++)
         {

            auto & size2 = pitem->m_box[j].m_size;
            auto & rect2 = pitem->m_box[j].m_rectangle;

            int dw = (size2.cx - s.cx) / 2;
            int dh = (size2.cy - s.cy) / 2;

            int x = m_rectClient.center_x() - rectangle.center_x();

            if (x > 0)
            {

               x = m_rectClient.center_x() - rectangle.left;

            }
            else
            {

               x = m_rectClient.center_x() - rectangle.right;

            }

            x = x * (m_rectClient.width() + iPadding * 2) / w;

            if (x > 0)
            {
               rect2.left = m_rectClient.center_x() - x;
               rect2.right = rect2.left + size2.cx;
            }
            else
            {
               rect2.right = m_rectClient.center_x()- x;
               rect2.left = rect2.right - size2.cx;
            }
            rect2.top = rectangle.top - dh;
            rect2.bottom = rect2.top + size2.cy;

            hExtra = maximum(hExtra, size2.cy);

         }

      }

      sizeTotal.cy = y + hExtra + 5;

      return sizeTotal;

   }


   ::size_i32 font_list::layout_single_column()
   {

      synchronous_lock synchronouslock(mutex());

      ::size_i32 sizeTotal;

      string strText = m_strTextLayout;

      size_i32 s;

      int h = 0;

      sizeTotal.cx = 0;

      int xSingleColumn = 0;
      int ySingleColumn = 0;

      auto plistdata = m_plistdata;

      for (int i = 0; i < plistdata->get_count(); i++)
      {

         font_list_item * pitem = plistdata->element_at(i);

         if (pitem == nullptr)
         {

            sizeTotal.cy = ySingleColumn;

            return sizeTotal;

         }

         size_i32 & s = pitem->m_box[0].m_size;

         auto & rectangle = pitem->m_box[0].m_rectangle;



         pitem->m_box[0].m_rectangle.left = xSingleColumn;
         pitem->m_box[0].m_rectangle.top = ySingleColumn;
         pitem->m_box[0].m_rectangle.right = xSingleColumn + s.cx;
         pitem->m_box[0].m_rectangle.bottom = ySingleColumn + s.cy;

         sizeTotal.cx = maximum(m_size.cx, pitem->m_box[0].m_rectangle.right + 4);

         ySingleColumn += s.cy;

         h = maximum(h, s.cy);

      }

      sizeTotal.cy = ySingleColumn;

      return sizeTotal;

   }



   ::user::item font_list::hit_test(const ::point_i32& point)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_etype == type_wide)
      {

         return hit_test_wide(point);

      }
      else
      {

         return hit_test_single_column(point);

      }

   }


   ::user::item font_list::hit_test_wide(const ::point_i32 & point)
   {

      synchronous_lock synchronouslock(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return ::user::e_element_none;

      }

      if (m_iHover >= 0)
      {

         if (plistdata->element_at(m_iHover)->m_box[BOX_HOVER].m_rectangle.contains(point))
         {

            return ::user::item(::user::e_element_item, m_iHover);

         }

      }

      for (::index iItem = 0; iItem < plistdata->get_size(); iItem++)
      {

         if (plistdata->element_at(iItem) == nullptr)
         {

            continue;

         }

         if (plistdata->element_at(iItem)->m_box[BOX].m_rectangle.contains(point))
         {

            return ::user::item(::user::e_element_item, iItem);

         }

      }

      return ::user::e_element_none;

   }


   ::user::item font_list::hit_test_single_column(const ::point_i32 & point)
   {

      synchronous_lock synchronouslock(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return ::user::e_element_none;

      }

      for (index iItem = 0; iItem < plistdata->get_size(); iItem++)
      {

         if (plistdata->element_at(iItem) == nullptr)
         {

            continue;

         }

         rectangle_i32 rectangle(plistdata->element_at(iItem)->m_box[BOX].m_rectangle);

         rectangle.right = rectangle.left + m_size.cx;

         if (rectangle.contains(point))
         {

            return { ::user::e_element_item, iItem };

         }

      }

      return ::user::e_element_none;

   }


   bool font_list::get_box_rect(RECTANGLE_I32 * lprect, ::index i)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_etype == type_wide)
      {

         return get_box_rect_wide(lprect, i);

      }
      else
      {

         return get_box_rect_single_column(lprect, i);

      }

   }


   bool font_list::get_box_rect_wide(RECTANGLE_I32 * lprect, ::index i)
   {

      synchronous_lock synchronouslock(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return false;

      }

      if (i < 0 || i >= plistdata->get_size())
      {

         return false;

      }

      if (plistdata->element_at(i) == nullptr)
      {

         return false;

      }

      *lprect = plistdata->element_at(i)->m_box[BOX].m_rectangle;

      return true;

   }


   bool font_list::get_box_rect_single_column(RECTANGLE_I32 * lprect, ::index i)
   {

      synchronous_lock synchronouslock(mutex());

      auto plistdata = m_plistdata;

      if (!plistdata)
      {

         return false;

      }

      if (i < 0 || i >= plistdata->get_size())
      {

         return false;

      }

      if (plistdata->element_at(i) == nullptr)
      {

         return false;

      }

      *lprect = plistdata->element_at(i)->m_box[BOX].m_rectangle;

      lprect->right = lprect->left + m_size.cx;

      return true;

   }


   void font_list::set_client_rect(const RECTANGLE_I32 * lpcrect)
   {

      ::rectangle_i32 rectangle(lpcrect);

      if (rectangle != m_rectClient)
      {

         ::size_i32 sizeOld(m_rectClient.size());

         ::size_i32 sizeNew(rectangle.size());

         m_rectClient = *lpcrect;

         if (sizeOld != sizeNew)
         {

            set_modified(id_font_extents);

         }

      }

   }


   index font_list::find_name(string str)
   {

      synchronous_lock synchronouslock(mutex());

      auto plistdata = m_plistdata;

      if (plistdata.is_null())
      {

         return -1;

      }

      for (index i = 0; i < plistdata->get_size(); i++)
      {

         if (m_pitema->element_at(i) == nullptr)
         {

            continue;

         }

         if(m_pitema->element_at(i)->m_strName.compare_ci(str) == 0)
         {

            return i;

         }

      }

      return -1;


   }


   //void font_list::update()
   //{

   //   m_bUpdating = true;

   //   try
   //   {

   //      //update_font_enumeration();
   //      sync_font_enumeration();



   //      update_extents();

   //   }
   //   catch (...)
   //   {

   //   }

   //   set_need_layout();

   //   //try
   //   //{

   //   //   m_puserinteraction->set_need_layout();

   //   //   m_puserinteraction->set_need_redraw();

   //   //   m_puserinteraction->post_redraw();

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   m_bUpdating = false;

   //}


   bool font_list::is_updating() const
   {

      if (!m_pfontenumeration)
      {

         return true;

      }

      if (m_pfontenumeration->m_bUpdating)
      {

         return true;

      }

      return m_bUpdating;

   }


} // namespace write_text


