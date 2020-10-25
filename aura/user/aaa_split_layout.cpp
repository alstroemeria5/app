﻿#include "framework.h"


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

      m_flagNonClient.remove(non_client_background);
      m_flagNonClient.remove(non_client_focus_rect);

   }


   split_layout::~split_layout()
   {

   }


   void split_layout::install_message_routing(::channel * pchannel)
   {

      place_holder_container::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &split_layout::_001OnCreate);
      MESSAGE_LINK(WM_SHOWWINDOW, pchannel, this, &split_layout::_001OnShowWindow);

   }


   void split_layout::_001OnCreate(::message::message* pmessage)
   {
      
      pmessage->previous();

   }


   void split_layout::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      //SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      //bool bIsWindowVisible = pshowwindow->m_bShow;

      //::count iSplitBarCount = get_split_count();

      //split_layout::Pane * pcomponent;

      //__pointer(::user::interaction) pwnd;

      //i32 i;

      //for (i = 0; i < iSplitBarCount; i++)
      //{

      //   pwnd = m_splitbara.element_at(i);

      //   if (!bIsWindowVisible)
      //   {

      //      pwnd->display(display_none);

      //   }
      //   else
      //   {

      //      pwnd->display(display_normal);

      //   }

      //}

      //::rect rectClient;

      //for (i = 0; i < get_pane_count(); i++)
      //{

      //   rect & rectPane = m_panea[i]->m_rect;

      //   pcomponent = m_panea.element_at(i);

      //   if (pcomponent == nullptr)
      //   {

      //      continue;

      //   }

      //   pwnd = pcomponent->m_pholder;

      //   if ( pwnd == nullptr)
      //   {

      //      continue;

      //   }

      //   rectClient = rectPane;

      //   rectClient.deflate(m_cxBorder, m_cyBorder);

      //   if (rectPane.area() <= 0 || !bIsWindowVisible)
      //   {

      //      pwnd->display(display_none);

      //   }
      //   else
      //   {

      //      pwnd->display(display_normal);

      //   }

      //}

   }


   bool split_layout::SetPaneCount(::count iPaneCount)
   {

      m_iPaneCount = iPaneCount;

      m_panea.set_size(iPaneCount);

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

               if (splitbar.create_window(this))
               {

                  splitbar.m_dwPosition = 0;

                  splitbar.m_dwPosition = 0;

               }

            }

         }

      }

      for(::index i = 0; i < m_panea.get_count(); i++)
      {

         if(m_panea[i].is_null())
         {

            m_panea[i] = __new(::user::split_layout::Pane);

            m_panea(i).m_bFixedSize =  false;

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

      for(::index i = 0; i < m_panea.get_count(); i++)
      {

         if(m_panea[i]->m_pholder.is_null())
         {

            m_panea[i]->m_pholder = get_new_place_holder(m_panea[i]->m_rectClient);

         }

      }

      m_bInitialized = true;

      return true;

   }


   void split_layout::SetSplitOrientation(e_orientation eorientationSplit)
   {

      m_eorientationSplit = eorientationSplit;

   }


   void split_layout::RelayChildEvent(index iIndex, const MESSAGE * pMsg)

   {

      if(!m_bInitialized)
         return;

      ::rect splitRect;
      CalcSplitBarRect(iIndex, &splitRect);
      ::point pointCursor = pMsg->pt;

      if(pMsg->message == WM_LBUTTONDOWN)

      {

//         i32   fwKeys = (i32) pMsg->wParam;        // key flags

         if(Session.is_mouse_button_pressed(::user::mouse_left_button))
         {
            ::user::split_bar & splitbar = *m_splitbara.element_at(iIndex);
            splitbar.SetCapture();
            m_iIndex = iIndex;
            m_iState = stateDragging;
         }
      }
      else if(pMsg->message == WM_LBUTTONUP)

      {

         if(m_iState != stateInitial)
         {

            Session.ReleaseCapture();

            m_iState = stateInitial;

         }

      }
      else if(pMsg->message == WM_CAPTURECHANGED)

      {

      }
      else if(pMsg->message == e_message_mouse_move)

      {

         i32   fwKeys = (i32) pMsg->wParam;        // key flags


         auto point = pointCursor;

         _001ScreenToClient(&point);

         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iIndex == m_iIndex))
         {

            sync_lock sl(mutex());
            //cslock sl(&m_mutex);
            {
               //      TRACE("split_layout::RelayChildEvent LOWORD(pMsg->lParam) %d\n", LOWORD(lpMsg->lParam));

               //      TRACE("split_layout::RelayChildEvent HIWORD(pMsg->lParam) %d\n", HIWORD(lpMsg->lParam));




               i32 nPos;
               bool bMove;
               nPos = GetPos(point.x, point.y);
               if(m_iIndex <= 0)
               {
                  bMove = nPos > GetMinPos();
               }
               else
               {
                  bMove = nPos > (i32) m_splitbara[m_iIndex - 1]->m_dwPosition;
               }
               if(get_pane_count() >= m_iIndex )
               {
                  bMove = bMove && nPos < GetMaxPos();
               }
               else
               {
                  bMove = bMove && nPos < (i32) m_splitbara[m_iIndex]->m_dwPosition;
               }
               if(bMove)
               {
                  bMove = nPos != (i32) m_splitbara[m_iIndex]->m_dwPosition;
               }
               TRACE("split_layout::RelayChildEvent nPos %d\nOldPos", m_splitbara[m_iIndex]->m_dwPosition);
               TRACE("split_layout::RelayChildEvent nPos %d\n", nPos);
               if(bMove)
               {

                  m_splitbara[m_iIndex]->m_dwPosition = nPos;
                  m_splitbara[m_iIndex]->m_dRate = 0.0;
               
                  set_need_layout();

               }

            }

         }
         else
         {
            m_iState = stateInitial;
         }
      }

   }


   i32 split_layout::GetPos(i32 xPos, i32 yPos)
   {

      if (m_eorientationSplit == orientation_horizontal)
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

      ::rect rectClient;

      get_client_rect(rectClient);

      if (m_eorientationSplit == orientation_horizontal)
      {

         return rectClient.top;

      }
      else
      {

         return rectClient.left;

      }

   }


   i32 split_layout::GetMaxPos()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if (m_eorientationSplit == orientation_horizontal)
      {

         return rectClient.bottom;

      }
      else
      {

         return rectClient.right;

      }

   }


   void split_layout::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      bool bIsWindowVisible = is_this_visible();

      auto rectClient = get_client_rect();

      if (rectClient.is_empty())
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

               m_splitbara[i]->m_dwPosition = min(m_splitbara[i]->m_dwMaxPosition, (u32)(m_splitbara[i]->m_dRate * iDimension));

            }
            else
            {

               m_splitbara[i]->m_dwPosition = min(m_splitbara[i]->m_dwMaxPosition, (u32)(m_splitbara[i]->m_dwPosition));

            }

         }

      }

      ::rect rectBar;

      i32 i;

      ::count iSplitBarCount = get_split_count();

      split_layout::Pane * pcomponent;

      __pointer(::user::interaction) pwnd;

      UINT uiBaseFlags = SWP_NOZORDER;

      UINT uiFlags = uiBaseFlags;

      for(i = 0; i < iSplitBarCount; i++)
      {

         pwnd = m_splitbara.element_at(i);

         if (!m_bSplitBar || !is_pane_visible(i) || !bIsWindowVisible || m_panea[i]->m_bFixedSize)
         {

            pwnd->hide();

            continue;

         }

         CalcSplitBarRect(i, &rectBar);

         uiFlags = uiBaseFlags;


         if (bIsWindowVisible)
         {

            pwnd->order(zorder_top);

            pwnd->place(rectBar);

            pwnd->display();

         }

      }

      for(i = 0; i < get_pane_count(); i++)
      {

         ::rect & rectPane = m_panea[i]->m_rect;

         ::rect & rectClient = m_panea[i]->m_rectClient;

         CalcPaneRect(i,&rectPane);

         pcomponent = m_panea.element_at(i);

         pwnd = pcomponent->m_pholder;

         if (pwnd == nullptr)
         {

            continue;

         }

         rectClient = rectPane;

         rectClient.deflate(m_cxBorder,m_cyBorder);

         pwnd->order(zorder_top);

         pwnd->place(rectClient);

         if (pwnd->is_request_visible())
         {

            pwnd->display();

         }
         else
         {

            pwnd->hide();

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

      return (i32) m_panea.get_count();

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

      if (iPane >= m_panea.get_size())
      {

         return false;

      }

      split_layout::Pane * ppane = m_panea[iPane];

      if (ppane == nullptr)
      {

         return false;

      }

      __pointer(::user::place_holder) pholder = ppane->m_pholder;

      if (pholder == nullptr)
      {

         return true; // assume future place_holder by default is visible

      }

      if (pholder->m_uiptraChild.is_empty())
      {

         return true; // assume future child by default is visible

      }

      if (!pholder->m_uiptraChild[0]->is_request_visible())
      {

         return false;

      }

      return true;

   }


   void split_layout::CalcPaneRect(index iPane, RECT * prect)

   {

      i32 nMinPos = GetMinPos(iPane);

      i32 nMaxPos = GetMaxPos(iPane);

      CalcPaneRect(nMinPos, nMaxPos, prect);


   }

   void split_layout::CalcPaneRect(i32 nMinPos, i32 nMaxPos, RECT * prect)

   {

      get_client_rect(prect);


      if(m_eorientationSplit == orientation_horizontal)
      {

         prect->top      = nMinPos;


         prect->bottom   = nMaxPos;


      }
      else
      {

         prect->left   = nMinPos;


         prect->right   = nMaxPos;


      }

   }


   i32 split_layout::get_normal_dimension()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if(m_eorientationSplit == orientation_horizontal)
      {

         return rectClient.height();

      }
      else
      {

         return rectClient.width();

      }

   }


   i32 split_layout::get_ortogonal_dimension()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if(m_eorientationSplit == orientation_horizontal)
      {

         return rectClient.width();

      }
      else
      {

         return rectClient.height();

      }

   }


   void split_layout::CalcSplitBarRect(index iIndex, RECT * prect)

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


      get_client_rect(prect);


      if(m_eorientationSplit == orientation_horizontal)
      {

         nPos = max(nPos, prect->top + m_iMarging / 2);


         nPos = min(nPos, prect->bottom - m_iMarging / 2);


         prect->top      = nPos - m_iMarging / 2;


         prect->bottom   = nPos + m_iMarging / 2;


      }
      else
      {

         nPos = max(nPos, prect->left + m_iMarging / 2);


         nPos = min(nPos, prect->right - m_iMarging / 2);


         prect->left   = nPos - m_iMarging / 2;


         prect->right   = nPos + m_iMarging / 2;


      }

   }


   bool split_layout::InsertPaneAt(index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, ::id id)
   {

      ::count iSplitBarCount = get_pane_count();

      m_splitbara.remove_all();

      index i;

      for(i = 0; i < iSplitBarCount; i++)
      {

         auto  pbar =__create_new<split_bar>();

         m_splitbara.insert_at(iIndex, pbar);

         ::user::split_bar & splitbar = *m_splitbara.element_at(i);

         splitbar.m_iIndex = i;

         if (!splitbar.create_window(this))
         {

            return false;

         }

      }

      m_panea.insert_at(iIndex, new Pane);

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      split_layout::Pane * pcomponent = m_panea.element_at(iIndex);

      if(pcomponent->m_pholder != nullptr)
      {

         if (!pcomponent->m_pholder->place_hold(puserinteraction))
         {

            return false;

         }

      }
      else
      {

         pcomponent->m_pholder = place_hold(puserinteraction,pcomponent->m_rectClient);

         if (pcomponent->m_pholder == nullptr)
         {

            return false;

         }

      }

      pcomponent->m_id = id.is_empty() ? (::id) iIndex : id;

      m_panea[iIndex]->m_bFixedSize = bFixedSize;

      return true;

   }


   bool split_layout::RemovePaneAt(index iIndex)
   {

      sync_lock sl(mutex());

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      m_panea.remove_at(iIndex);

      ::count iSplitBarCount = get_pane_count();

      m_splitbara.remove_all();

      index i;

      for(i = 0; i < iSplitBarCount; i++)
      {

         m_splitbara.add_new(this);

         ::user::split_bar & splitbar = *m_splitbara.element_at(i);

         splitbar.m_iIndex = i;

         if (!splitbar.create_window(this))
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

      split_layout::Pane * pcomponent = m_panea.element_at(iIndex);

      if(pcomponent->m_pholder != nullptr)
      {

         if (!pcomponent->m_pholder->place_hold(puserinteraction))
         {

            return false;

         }

      }
      else
      {

         ::rect rectPane;

         pcomponent->m_pholder->get_client_rect(rectPane);

         pcomponent->m_pholder = place_hold(puserinteraction, rectPane);

         if (pcomponent->m_pholder == nullptr)
         {

            return false;

         }

      }

      pcomponent->m_id = id.is_empty() ? (::id) iIndex : id;

      m_panea[iIndex]->m_bFixedSize = bFixedSize;

      return true;

   }


   void split_layout::SetPaneFixedSize(index iIndex, SIZE * pSize)
   {

      UNREFERENCED_PARAMETER(iIndex);

      UNREFERENCED_PARAMETER(pSize);

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

         ::rect rect;

         CalcSplitBarRect(iPane - 1, rect);

         if(m_eorientationSplit == orientation_horizontal)
         {

            return rect.bottom;

         }
         else
         {

            return rect.right;

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

         ::rect rect;

         CalcSplitBarRect(iPane, rect);

         if(m_eorientationSplit == orientation_horizontal)
         {

            return rect.top;

         }
         else
         {

            return rect.left;

         }

      }

   }

   e_orientation split_layout::GetSplitOrientation()
   {

      return m_eorientationSplit;

   }


   void split_layout::RelayEventSplitBar(index iSplitBar, const ::id & id, WPARAM wParam, LPARAM lParam)
   {

      ASSERT(FALSE);

      if(!m_bInitialized)
         return;

      ::rect splitRect;

      CalcSplitBarRect(iSplitBar, &splitRect);

      if(emessage == WM_LBUTTONDOWN)
      {

         i32   fwKeys = (i32) wParam;        // key flags
//         i32 xPos = splitRect.left + (i16) LOWORD(lParam);  // horizontal position of cursor
//         i32 yPos = splitRect.top + (i16) HIWORD(lParam);  // vertical position of cursor
         if((fwKeys & MK_LBUTTON) > 0)
         {
            ::user::split_bar * pSplitBar = m_splitbara.element_at(iSplitBar);
            pSplitBar->SetCapture();
            m_iIndex = iSplitBar;
            m_iState = stateDragging;
         }
      }
      else if(emessage == WM_LBUTTONUP)
      {
//         i32   fwKeys = wParam;        // key flags
//         i32 xPos = splitRect.left + (i16) LOWORD(lParam);  // horizontal position of cursor
//         i32 yPos = splitRect.top + (i16) HIWORD(lParam);  // vertical position of cursor
         if(m_iState != stateInitial)
         {
            Session.ReleaseCapture();
            m_iState = stateInitial;
         }
      }
      else if(emessage == WM_CAPTURECHANGED)
      {
      }
      else if(emessage == e_message_mouse_move)
      {
         i32   fwKeys = (i32) wParam;        // key flags
         i32 xPos = splitRect.left + (i16) LOWORD(lParam);  // horizontal position of cursor
         i32 yPos = splitRect.top + (i16) HIWORD(lParam);  // vertical position of cursor
         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iSplitBar == m_iIndex))
         {
            //cslock lock(&m_mutex);
            
            sync_lock sl(mutex());

            {
               TRACE("split_layout::RelayChildEvent LOWORD(lParam) %d\n", LOWORD(lParam));
               TRACE("split_layout::RelayChildEvent HIWORD(lParam) %d\n", HIWORD(lParam));


               i32 nPos;
               bool bMove;
               nPos = GetPos(xPos, yPos);
               if(m_iIndex <= 0)
               {
                  bMove = nPos > GetMinPos();
               }
               else
               {
                  bMove = nPos > (i32) m_splitbara[m_iIndex - 1]->m_dwPosition;
               }
               if(get_pane_count() >= m_iIndex )
               {
                  bMove = bMove && nPos < GetMaxPos();
               }
               else
               {
                  bMove = bMove && nPos < (i32) m_splitbara[m_iIndex]->m_dwPosition;
               }
               if(bMove)
               {
                  bMove = nPos != (i32) m_splitbara[m_iIndex]->m_dwPosition;
               }
               if(bMove)
               {

                  m_splitbara[m_iIndex]->m_dwPosition = nPos;
                  m_splitbara[m_iIndex]->m_dRate = 0.0;
                  
                  set_need_layout();

               }
               
            }

         }
         else
         {

            m_iState = stateInitial;

         }

      }

   }


   rect & split_layout::get_pane_rect(index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         __throw(invalid_argument_exception());

      }

      return m_panea[iPane]->m_rectClient;

   }


   __pointer(::user::place_holder) split_layout::get_pane_holder(index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         return nullptr;

      }

      return m_panea[iPane]->m_pholder;

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

      Pane & pane = m_panea(iPane);

      return pane.m_id;

   }


   index split_layout::get_pane_by_id(::id id)
   {

      for(index iPane = 0; iPane < m_panea.get_count(); iPane++)
      {

         if (m_panea[iPane]->m_id == id)
         {

            return iPane;

         }

      }

      return -1;

   }


   split_layout::Pane::Pane()
   {

      m_pholder = nullptr;

      m_rect.Null();

      m_rectClient.Null();

      m_sizeFixed = ::size(0, 0);

   }


   void split_layout::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, element_background);

      if (colorBackground.m_iA > 0)
      {

         ::rect rectClient;

         get_client_rect(rectClient);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->fill_rect(rectClient, colorBackground);

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



