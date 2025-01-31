#include "framework.h"
#include "base/user/user/_user.h"
#include "split_pane.h"


namespace user
{


   const i32 split_layout::m_iMarging = 5;

   split_layout::split_layout()
   {

      m_bSplitBar = true;
      m_bInitialized = true;
      m_iState = stateInitial;
      m_cxBorder = 1;
      m_cyBorder = 1;
      m_iPaneCount = 0;

      m_flagNonClient.erase(non_client_background);
      m_flagNonClient.erase(non_client_focus_rect);

   }


   split_layout::~split_layout()
   {

   }


   void split_layout::install_message_routing(::channel * pchannel)
   {

      place_holder_container::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &split_layout::on_message_create);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &split_layout::on_message_show_window);

   }


   void split_layout::on_message_create(::message::message* pmessage)
   {

      pmessage->previous();

   }


   void split_layout::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //__pointer(::message::show_window) pshowwindow(pmessage);

      //bool bIsWindowVisible = pshowwindow->m_bShow;

      //::count iSplitBarCount = get_split_count();

      //split_pane * pcomponent;

      //__pointer(::user::interaction) puserinteraction;

      //i32 i;

      //for (i = 0; i < iSplitBarCount; i++)
      //{

      //   puserinteraction = m_splitbara.element_at(i);

      //   if (!bIsWindowVisible)
      //   {

      //      puserinteraction->display(e_display_none);

      //   }
      //   else
      //   {

      //      puserinteraction->display(e_display_normal);

      //   }

      //}

      //::rectangle_i32 rectangleClient;

      //for (i = 0; i < get_pane_count(); i++)
      //{

      //   rectangle_i32 & rectPane = m_splitpanecompositea[i]->m_rectangle;

      //   pcomponent = m_splitpanecompositea.element_at(i);

      //   if (pcomponent == nullptr)
      //   {

      //      continue;

      //   }

      //   puserinteraction = pcomponent->m_pplaceholder;

      //   if ( puserinteraction == nullptr)
      //   {

      //      continue;

      //   }

      //   rectangleClient = rectPane;

      //   rectangleClient.deflate(m_cxBorder, m_cyBorder);

      //   if (rectPane.area() <= 0 || !bIsWindowVisible)
      //   {

      //      puserinteraction->display(e_display_none);

      //   }
      //   else
      //   {

      //      puserinteraction->display(e_display_normal);

      //   }

      //}

   }


   bool split_layout::SetPaneCount(::count iPaneCount)
   {

      m_iPaneCount = iPaneCount;

      m_splitpanecompositea.set_size(iPaneCount);

      m_splitbara.set_size(iPaneCount - 1);

      for(::index i = 0; i < m_splitbara.get_count(); i++)
      {

         if(!m_splitbara[i])
         {

            auto estatus = __construct(m_splitbara[i]);

            if (!estatus)
            {

               ::user::split_bar & splitbar = m_splitbara(i);

               splitbar.m_iIndex = i;

               if (splitbar.create_child(this))
               {

                  splitbar.m_dwPosition = 0;

                  splitbar.m_dwPosition = 0;

               }

            }

         }

      }

      for(::index i = 0; i < m_splitpanecompositea.get_count(); i++)
      {

         auto& ppane = m_splitpanecompositea[i];

         if(!ppane)
         {

            auto estatus = __compose_new(ppane);

            if (!estatus)
            {

               return false;

            }

            ppane->m_bFixedSize =  false;

         }

      }

      return true;

   }


   bool split_layout::initialize_split_layout()
   {

#ifdef _DEBUG

      ::count iPaneCount = m_iPaneCount;

#endif

      m_bInitialized = false;

      ASSERT(iPaneCount > 0);

      for(::index i = 0; i < m_splitpanecompositea.get_count(); i++)
      {

         __compose_new(m_splitpanecompositea[i]);

         if(m_splitpanecompositea[i]->m_pplaceholder.is_null())
         {

            m_splitpanecompositea[i]->m_pplaceholder = get_new_place_holder(m_splitpanecompositea[i]->m_rectangleClient);

         }

      }

      m_bInitialized = true;

      return true;

   }


   void split_layout::SetSplitOrientation(enum_orientation eorientationSplit)
   {

      m_eorientationSplit = eorientationSplit;

   }


   void split_layout::RelayChildEvent(index iIndex, const MESSAGE * pMsg)

   {

      if(!m_bInitialized)
         return;

      ::rectangle_i32 splitRect;
      CalcSplitBarRect(iIndex, &splitRect);
      //::point_i32 pointCursor = pMsg->pt;

      if(pMsg->m_id == e_message_left_button_down)
      {

         auto psession = get_session();

         if(psession->is_mouse_button_pressed(::user::e_mouse_left_button))
         {
            ::user::split_bar & splitbar = *m_splitbara.element_at(iIndex);
            splitbar.set_mouse_capture();
            m_iIndex = iIndex;
            m_iState = stateDragging;
         }
      }
      else if(pMsg->m_id == e_message_left_button_up)
      {

         if(m_iState != stateInitial)
         {

            auto psession = get_session();

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            pwindowing->release_mouse_capture();

            m_iState = stateInitial;

         }

      }
      else if(pMsg->m_id == e_message_mouse_move)
      {

//         i32   fwKeys = (i32) pMsg->wParam;        // key flags


         //auto point = _001ScreenToClient(pointCursor);

         //if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iIndex == m_iIndex))
         //{

         //   synchronous_lock synchronouslock(mutex());
         //   //critical_section_lock synchronouslock(&m_mutex);
         //   {
         //      //      TRACE("split_layout::RelayChildEvent LOWORD(pMsg->lParam) %d\n", LOWORD(lpMsg->lParam));

         //      //      TRACE("split_layout::RelayChildEvent HIWORD(pMsg->lParam) %d\n", HIWORD(lpMsg->lParam));




         //      i32 nPos;
         //      bool bMove;
         //      nPos = GetPos(point.x, point.y);
         //      if(m_iIndex <= 0)
         //      {
         //         bMove = nPos > GetMinPos();
         //      }
         //      else
         //      {
         //         bMove = nPos > (i32) m_splitbara[m_iIndex - 1]->m_dwPosition;
         //      }
         //      if(get_pane_count() >= m_iIndex )
         //      {
         //         bMove = bMove && nPos < GetMaxPos();
         //      }
         //      else
         //      {
         //         bMove = bMove && nPos < (i32) m_splitbara[m_iIndex]->m_dwPosition;
         //      }
         //      if(bMove)
         //      {
         //         bMove = nPos != (i32) m_splitbara[m_iIndex]->m_dwPosition;
         //      }
         //      TRACE("split_layout::RelayChildEvent nPos %d\nOldPos", m_splitbara[m_iIndex]->m_dwPosition);
         //      TRACE("split_layout::RelayChildEvent nPos %d\n", nPos);
         //      if(bMove)
         //      {

         //         m_splitbara[m_iIndex]->m_dwPosition = nPos;
         //         m_splitbara[m_iIndex]->m_dRate = 0.0;

         //         set_need_layout();

               //}

         //   }

         //}
         //else
         //{
         //   m_iState = stateInitial;
         //}
      }

   }


   i32 split_layout::GetPos(i32 xPos, i32 yPos)
   {

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return yPos;

      }
      else
      {

         return xPos;

      }

   }


   i32 split_layout::GetMinPos()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleClient.top;

      }
      else
      {

         return rectangleClient.left;

      }

   }


   i32 split_layout::GetMaxPos()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleClient.bottom;

      }
      else
      {

         return rectangleClient.right;

      }

   }


   void split_layout::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      bool bIsWindowVisible = is_this_visible();

      auto rectangleClient = get_client_rect();

      if (rectangleClient.is_empty())
      {

         return;

      }

      i32 iDimension = get_normal_dimension();

      u32 dwPosition;

      double dRate;

      if(iDimension > 0)
      {

         for(i32 i = 0 ; i < m_splitbara.get_count(); i++)
         {

            if (m_splitbara[i]->m_dRate >= 0.0)
            {

               if ((m_splitbara[i]->m_dRate < m_splitbara[i]->m_dMinimumRate
                     || m_splitbara[i]->m_dRate > m_splitbara[i]->m_dMaximumRate)
                     && m_splitbara[i]->m_dwPosition > 0)
               {

                  dwPosition = m_splitbara[i]->m_dwPosition;

                  dRate = (double)dwPosition / (double)iDimension;

                  m_splitbara[i]->m_dRate = dRate;

               }

               if (m_splitbara[i]->m_dRate < m_splitbara[i]->m_dMinimumRate)
               {

                  m_splitbara[i]->m_dRate = m_splitbara[i]->m_dMinimumRate;

               }
               else if (m_splitbara[i]->m_dRate > m_splitbara[i]->m_dMaximumRate)
               {

                  m_splitbara[i]->m_dRate = m_splitbara[i]->m_dMaximumRate;

               }

               m_splitbara[i]->m_dwPosition = minimum(m_splitbara[i]->m_dwMaxPosition, (u32)(m_splitbara[i]->m_dRate * iDimension));

            }
            else
            {

               m_splitbara[i]->m_dwPosition = minimum(m_splitbara[i]->m_dwMaxPosition, (u32)(m_splitbara[i]->m_dwPosition));

            }

         }

      }

      ::rectangle_i32 rectBar;

      i32 i;

      ::count iSplitBarCount = get_split_count();

      if (iSplitBarCount < 0)
      {

         return;

      }

      split_pane * pcomponent;

      __pointer(::user::interaction) puserinteraction;

      //::u32 uBaseFlags = SWP_NOZORDER;
      ::u32 uBaseFlags = 0;

      ::u32 uFlags = uBaseFlags;

      m_splitbara.set_size(iSplitBarCount);


      for(i = 0; i < iSplitBarCount; i++)
      {

         if (!m_splitbara.element_at(i))
         {

            __construct_new(m_splitbara.element_at(i));

         }

         puserinteraction = m_splitbara.element_at(i);

         if (!m_bSplitBar || !is_pane_visible(i) || !bIsWindowVisible || m_splitpanecompositea[i]->m_bFixedSize)
         {

            puserinteraction->hide();

            continue;

         }

         CalcSplitBarRect(i, &rectBar);

         uFlags = uBaseFlags;

         if (bIsWindowVisible)
         {

            puserinteraction->order(e_zorder_top);

            puserinteraction->place(rectBar);

            puserinteraction->display();

         }

      }

      for(i = 0; i < get_pane_count(); i++)
      {

         ::rectangle_i32 & rectPane = m_splitpanecompositea[i]->m_rectangle;

         ::rectangle_i32 & rectangleClient = m_splitpanecompositea[i]->m_rectangleClient;

         CalcPaneRect(i,&rectPane);

         pcomponent = m_splitpanecompositea.element_at(i);

         puserinteraction = pcomponent->m_pplaceholder;

         if (puserinteraction == nullptr)
         {

            continue;

         }

         rectangleClient = rectPane;

         rectangleClient.deflate(m_cxBorder,m_cyBorder);

         puserinteraction->order(e_zorder_top);

         puserinteraction->place(rectangleClient);

         if (puserinteraction->layout().sketch().is_visible())
         {

            puserinteraction->display();

         }
         else
         {

            puserinteraction->hide();

         }

      }

   }


   void split_layout::set_position(index iIndex, i32 nPos)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      if (iIndex < 0 && iIndex >= get_split_count())
      {

         return;

      }

      m_splitbara[iIndex]->m_dwPosition    = nPos;

      m_splitbara[iIndex]->m_dRate         = -1.0; // disable rate evaluation at first

   }


   void split_layout::set_position_rate(index iIndex, double dRate, double dMinimumRate, double dMaximumRate)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      if (iIndex < 0 && iIndex >= get_split_count())
      {

         return;

      }

      m_splitbara[iIndex]->m_dRate         = dRate;
      m_splitbara[iIndex]->m_dMinimumRate  = dMinimumRate;
      m_splitbara[iIndex]->m_dMaximumRate  = dMaximumRate;
      m_splitbara[iIndex]->m_dwPosition    = (u32) -1; // disable position evaluation at first on on_layout

   }


   i32 split_layout::get_position(index iIndex)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      return m_splitbara[iIndex]->m_dwPosition;

   }


   ::count split_layout::get_split_count()
   {

      return get_pane_count() - 1;

   }


   ::count split_layout::get_pane_count()
   {

      return (i32) m_splitpanecompositea.get_count();

   }

   ::count split_layout::get_visible_pane_count()
   {

      if (!m_bInitialized)
      {

         return get_pane_count();

      }

      ::count c = 0;

      for (index i = 0; i < get_pane_count(); i++)
      {

         if (is_pane_visible((int) (i)))
         {

            c++;

         }

      }

      return c;

   }


   bool split_layout::is_pane_visible(int iPane)
   {

      if (iPane < 0)
      {

         return false;

      }

      if (iPane >= m_splitpanecompositea.get_size())
      {

         return false;

      }

      split_pane * ppane = m_splitpanecompositea[iPane];

      if (ppane == nullptr)
      {

         return false;

      }

      __pointer(::user::place_holder) pholder = ppane->m_pplaceholder;

      if (pholder == nullptr)
      {

         return true; // assume future place_holder by default is visible

      }

      auto puserinteractionpointeraChild = pholder->m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return true;

      }

      if (puserinteractionpointeraChild->has_no_interaction())
      {

         return true; // assume future child by default is visible

      }

      if (!puserinteractionpointeraChild->first_interaction()->layout().sketch().is_visible())
      {

         return false;

      }

      return true;

   }


   void split_layout::CalcPaneRect(index iPane, RECTANGLE_I32 * prectangle)

   {

      i32 nMinPos = GetMinPos(iPane);

      i32 nMaxPos = GetMaxPos(iPane);

      CalcPaneRect(nMinPos, nMaxPos, prectangle);


   }

   void split_layout::CalcPaneRect(i32 nMinPos, i32 nMaxPos, RECTANGLE_I32 * prectangle)

   {

      get_client_rect(prectangle);


      if(m_eorientationSplit == e_orientation_horizontal)
      {

         prectangle->top      = nMinPos;


         prectangle->bottom   = nMaxPos;


      }
      else
      {

         prectangle->left   = nMinPos;


         prectangle->right   = nMaxPos;


      }

   }


   i32 split_layout::get_normal_dimension()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleClient.height();

      }
      else
      {

         return rectangleClient.width();

      }

   }


   i32 split_layout::get_ortogonal_dimension()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleClient.width();

      }
      else
      {

         return rectangleClient.height();

      }

   }


   void split_layout::CalcSplitBarRect(index iIndex, RECTANGLE_I32 * prectangle)

   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      if (iIndex >= m_splitbara.get_count())
      {

         return;

      }

      i32 nPos = 0;

      index i = 0;

      while (i <= iIndex)
      {

         if (is_pane_visible((int)(i)))
         {

            nPos = m_splitbara[iIndex]->m_dwPosition;

         }

         i++;

      }


      get_client_rect(prectangle);


      if(m_eorientationSplit == e_orientation_horizontal)
      {

         nPos = maximum(nPos, prectangle->top + m_iMarging / 2);


         nPos = minimum(nPos, prectangle->bottom - m_iMarging / 2);


         prectangle->top      = nPos - m_iMarging / 2;


         prectangle->bottom   = nPos + m_iMarging / 2;


      }
      else
      {

         nPos = maximum(nPos, prectangle->left + m_iMarging / 2);


         nPos = minimum(nPos, prectangle->right - m_iMarging / 2);


         prectangle->left   = nPos - m_iMarging / 2;


         prectangle->right   = nPos + m_iMarging / 2;


      }

   }


   bool split_layout::InsertPaneAt(index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, ::id id)
   {

      //::count iSplitBarCount = get_pane_count();

      //m_splitbara.erase_all();

      //index i;

      //for(i = 0; i < iSplitBarCount; i++)
      //{

         auto  pbar =__create_new<split_bar>();

         m_splitbara.insert_at(iIndex, pbar);

         //::user::split_bar & splitbar = *m_splitbara.element_at(iIndex);

         pbar->m_iIndex = iIndex;

         if (!pbar->create_child(this))
         {

            return false;

         }

      //}

      auto & ppane = m_splitpanecompositea.add_new_at(iIndex);

      auto estatus = __compose_new(ppane);

      if (!estatus)
      {

         return false;

      }

      ppane->m_pplaceholder = place_hold(puserinteraction, ppane->m_rectangleClient);

      if (ppane->m_pplaceholder == nullptr)
      {

         return false;

      }

      ppane->m_id = id.is_empty() ? (::id) iIndex : id;

      ppane->m_bFixedSize = bFixedSize;

      return true;

   }


   bool split_layout::RemovePaneAt(index iIndex)
   {

      synchronous_lock synchronouslock(mutex());

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      m_splitpanecompositea.erase_at(iIndex);

      ::count iSplitBarCount = get_pane_count();

      m_splitbara.erase_all();

      index i;

      for(i = 0; i < iSplitBarCount; i++)
      {

         m_splitbara.add_new(this);

         ::user::split_bar & splitbar = *m_splitbara.element_at(i);

         splitbar.m_iIndex = i;

         if (!splitbar.create_child(this))
         {

            return false;

         }

      }

      return true;

   }


   bool split_layout::SetPane(index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, id id)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      split_pane * pcomponent = m_splitpanecompositea.element_at(iIndex);

      if(pcomponent->m_pplaceholder != nullptr)
      {

         if (!pcomponent->m_pplaceholder->place_hold(puserinteraction))
         {

            return false;

         }

      }
      else
      {

         ::rectangle_i32 rectPane;

         pcomponent->m_pplaceholder->get_client_rect(rectPane);

         pcomponent->m_pplaceholder = place_hold(puserinteraction, rectPane);

         if (pcomponent->m_pplaceholder == nullptr)
         {

            return false;

         }

      }

      pcomponent->m_id = id.is_empty() ? (::id) iIndex : id;

      m_splitpanecompositea[iIndex]->m_bFixedSize = bFixedSize;

      return true;

   }


   void split_layout::SetPaneFixedSize(index iIndex, SIZE_I32 * pSize)
   {

      __UNREFERENCED_PARAMETER(iIndex);

      __UNREFERENCED_PARAMETER(pSize);

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());
      //    m_aFixedSize.element_at(iIndex) = *pSize;

   }


   i32 split_layout::GetMinPos(index iPane)
   {

      if (get_split_count() <= 0 || iPane <= 0)
      {

         return GetMinPos();

      }
      else
      {

         ::rectangle_i32 rectangle;

         CalcSplitBarRect(iPane - 1, rectangle);

         if(m_eorientationSplit == e_orientation_horizontal)
         {

            return rectangle.bottom;

         }
         else
         {

            return rectangle.right;

         }

      }

   }

   i32 split_layout::GetMaxPos(index iPane)
   {

      if (get_split_count() <= 0 || iPane >= get_split_count())
      {

         return GetMaxPos();

      }
      else
      {

         ::rectangle_i32 rectangle;

         CalcSplitBarRect(iPane, rectangle);

         if(m_eorientationSplit == e_orientation_horizontal)
         {

            return rectangle.top;

         }
         else
         {

            return rectangle.left;

         }

      }

   }

   enum_orientation split_layout::GetSplitOrientation()
   {

      return m_eorientationSplit;

   }


//   void split_layout::RelayEventSplitBar(index iSplitBar, const ::id & id, WPARAM wParam, LPARAM lParam)
//   {
//
//      ASSERT(false);
//
//      if(!m_bInitialized)
//         return;
//
//      ::rectangle_i32 splitRect;
//
//      CalcSplitBarRect(iSplitBar, &splitRect);
//
//      if(id == e_message_left_button_down)
//      {
//
//         i32   fwKeys = (i32) wParam;        // key flags
////         i32 xPos = splitRect.left + (i16) LOWORD(lParam);  // horizontal position of cursor
////         i32 yPos = splitRect.top + (i16) HIWORD(lParam);  // vertical position of cursor
//         if((fwKeys & MK_LBUTTON) > 0)
//         {
//            ::user::split_bar * pSplitBar = m_splitbara.element_at(iSplitBar);
//            pSplitBar->SetCapture();
//            m_iIndex = iSplitBar;
//            m_iState = stateDragging;
//         }
//      }
//      else if(id == e_message_left_button_up)
//      {
////         i32   fwKeys = wParam;        // key flags
////         i32 xPos = splitRect.left + (i16) LOWORD(lParam);  // horizontal position of cursor
////         i32 yPos = splitRect.top + (i16) HIWORD(lParam);  // vertical position of cursor
//         if(m_iState != stateInitial)
//         {
//
//            auto psession = get_session();
//
//            auto puser = psession->user();
//
//            auto pwindowing = puser->windowing();
//
//            pwindowing->release_capture();
//
//            m_iState = stateInitial;
//
//         }
//
//      }
//#ifdef WINDOWS_DESKTOP
//      else if(id == e_message_capture_changed)
//      {
//      }
//#endif
//      else if(id == e_message_mouse_move)
//      {
//         i32   fwKeys = (i32) wParam;        // key flags
//         i32 xPos = splitRect.left + (i16) LOWORD(lParam);  // horizontal position of cursor
//         i32 yPos = splitRect.top + (i16) HIWORD(lParam);  // vertical position of cursor
//         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iSplitBar == m_iIndex))
//         {
//            //critical_section_lock lock(&m_mutex);
//
//            synchronous_lock synchronouslock(mutex());
//
//            {
//               TRACE("split_layout::RelayChildEvent LOWORD(lParam) %d\n", LOWORD(lParam));
//               TRACE("split_layout::RelayChildEvent HIWORD(lParam) %d\n", HIWORD(lParam));
//
//
//               i32 nPos;
//               bool bMove;
//               nPos = GetPos(xPos, yPos);
//               if(m_iIndex <= 0)
//               {
//                  bMove = nPos > GetMinPos();
//               }
//               else
//               {
//                  bMove = nPos > (i32) m_splitbara[m_iIndex - 1]->m_dwPosition;
//               }
//               if(get_pane_count() >= m_iIndex )
//               {
//                  bMove = bMove && nPos < GetMaxPos();
//               }
//               else
//               {
//                  bMove = bMove && nPos < (i32) m_splitbara[m_iIndex]->m_dwPosition;
//               }
//               if(bMove)
//               {
//                  bMove = nPos != (i32) m_splitbara[m_iIndex]->m_dwPosition;
//               }
//               if(bMove)
//               {
//
//                  m_splitbara[m_iIndex]->m_dwPosition = nPos;
//                  m_splitbara[m_iIndex]->m_dRate = 0.0;
//
//                  set_need_layout();
//
//               }
//
//            }
//
//         }
//         else
//         {
//
//            m_iState = stateInitial;
//
//         }
//
//      }
//
//   }


   rectangle_i32 & split_layout::get_pane_rect(index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         __throw(error_invalid_argument);

      }

      return m_splitpanecompositea[iPane]->m_rectangleClient;

   }


   __pointer(::user::place_holder) split_layout::get_pane_holder(index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         return nullptr;

      }

      return m_splitpanecompositea[iPane]->m_pplaceholder;

   }


   __pointer(::user::interaction) split_layout::get_pane_window(index iPane)
   {

      __pointer(::user::place_holder) pholder = get_pane_holder(iPane);

      if (pholder == nullptr)
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   id split_layout::get_pane_id(index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         return id();

      }

      auto & ppane = m_splitpanecompositea[iPane];

      return ppane->m_id;

   }


   split_pane * split_layout::get_pane_by_id(::id id)
   {

      for(index iPane = 0; iPane < m_splitpanecompositea.get_count(); iPane++)
      {

         if (m_splitpanecompositea[iPane]->m_id == id)
         {

            return m_splitpanecompositea[iPane].get();

         }

      }

      return nullptr;

   }




   void split_layout::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, e_element_background);

      if (colorBackground.alpha > 0)
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_rectangle(rectangleClient, colorBackground);

      }

   }


   void split_layout::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);


      if (pstyle)
      {

         if (!pstyle->_001OnDrawSplitLayout(pgraphics, this))
         {

            _001OnDrawSplitLayout(pgraphics);

         }

      }

   }


   void split_layout::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics)
   {


   }


} // namespace user



