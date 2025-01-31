#include "framework.h"
#include "base/user/simple/_simple.h"
//#include "acme/node/operating_system/cross.h"


simple_scroll_bar::simple_scroll_bar() :
   m_penDraw(e_create),
   m_brushDraw(e_create),
   m_rgnA(e_create), // região da primeira seta
   m_rgnB(e_create) // região da segunda seta
{

   //m_brushNull->CreateStockObject(NULL_BRUSH);
   m_flagNonClient.erase(non_client_background);
   // m_flagNonClient.erase(non_client_focus_rect);
   m_bTracking          = false;
   m_scrollinfo.nMin    = 0;
   m_scrollinfo.nMax    = 100;
   m_scrollinfo.nPage   = 10;
   m_scrollinfo.nPos    = 0;


   //m_cr = argb(127,180,80,120);
   //m_colorStrong = argb(150, 150, 150, 150);
   //m_colorBorder = argb(190, 180, 180, 180);
   //m_colorLiteBorder = argb(184,84 + 23,84 + 23,77 + 23);

   //m_colorHover = argb(100,190,180,250);
   //m_colorHoverStrong = argb(130, 190, 180, 250);
   //m_colorHoverBorder = argb(190, 160, 150, 180);
   //m_colorHoverLiteBorder = argb(184,84 + 23 - 23,84 + 23,77 + 23 + 84);

}

simple_scroll_bar::~simple_scroll_bar()
{
}


void simple_scroll_bar::install_message_routing(::channel * pchannel)
{
   ::user::interaction::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_scroll_bar::on_message_create);
   MESSAGE_LINK(e_message_destroy, pchannel, this, &simple_scroll_bar::on_message_destroy);
   MESSAGE_LINK(e_message_show_window, pchannel, this, &simple_scroll_bar::on_message_show_window);
   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &simple_scroll_bar::on_message_mouse_move);
   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &simple_scroll_bar::on_message_left_button_down);
   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &simple_scroll_bar::on_message_left_button_up);
   MESSAGE_LINK(e_message_hscroll, pchannel, this, &simple_scroll_bar::_001OnHScroll);

}


//bool simple_scroll_bar::create_interaction(const ::string & pszClassName, const ::string & pszWindowName, u32 uStyle, ::user::interaction * puiParent, const ::id & id, ::create * pcreate)
//{
//
//   if(!::user::interaction::create_interaction(pszClassName, pszWindowName, uStyle, puiParent, id, pcreate))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


//bool simple_scroll_bar::create_interaction(enum_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::id id)
//{
//
//   if(!::user::scroll_bar::create_interaction(eorientation, uStyle, puiParent, id))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


void simple_scroll_bar::on_message_mouse_move(::message::message * pmessage)
{

   auto pmouse = pmessage->m_pmouse;

   ::point_i32 point;

   _screen_to_client(point, pmouse->m_point);

   if(m_bTracking)
   {

      point -= m_sizeTrackOffset;

      queue_graphics_call([this, point](::draw2d::graphics_pointer & pgraphics)
         {

            SetTrackingPos(point, pgraphics);

            post_scroll_message(e_scroll_command_thumb_track);

         });

      set_need_redraw();

      post_redraw();

      pmouse->m_lresult = 1;

      //pmouse->m_bRet = true;

      auto psession = get_session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

      pmouse->m_pcursor = pcursor;

   }
   else
   {

      auto eelement = hit_test(pmouse);

      if(eelement.is_set())
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

         pmouse->m_pcursor = pcursor;

      }

   }


}


bool simple_scroll_bar::scrollbar_action(const ::user::item & item, ::draw2d::graphics_pointer & pgraphics)
{

   switch(item.m_eelement)
   {
   case ::user::e_element_scrollbar_rectA:
      return scrollbar_lineA(pgraphics);
   case ::user::e_element_scrollbar_rectB:
      return scrollbar_lineB(pgraphics);
   case ::user::e_element_scrollbar_pageA:
      return scrollbar_pageA(item.m_pointClient, pgraphics);
   case ::user::e_element_scrollbar_pageB:
      return scrollbar_pageB(item.m_pointClient, pgraphics);
   default:
      return false;
   }

}

void simple_scroll_bar::on_message_left_button_down(::message::message * pmessage)
{

   auto pmouse = pmessage->m_pmouse;

   m_itemCurrent = hit_test(pmouse);

   if(!m_itemCurrent.is_set())
   {

      pmouse->m_bRet = false;

      return;

   }

   pmouse->m_bRet = true;

   pmouse->m_lresult = 1;

   set_mouse_capture();

   auto psystem = m_psystem->m_paurasystem;

   auto pdraw2d = psystem->draw2d();

   auto pgraphics = pdraw2d->create_memory_graphics();

   if(m_itemCurrent == ::user::e_element_scrollbar_rect)
   {

      m_bTracking = true;

      SetTimer(43212345, 10, nullptr);

      m_pointTrack = m_itemCurrent.m_pointClient;

      GetTrackRect(m_rectTrack, pgraphics);

      m_sizeTrackOffset = m_pointTrack - m_rectTrack.top_left();

   }
   else
   {

      if(scrollbar_action(m_itemCurrent, pgraphics))
      {

         SetTimer((uptr) this,300,nullptr);

      }

   }

}

void simple_scroll_bar::on_message_left_button_up(::message::message * pmessage)
{

   auto pmouse = pmessage->m_pmouse;

   if (!m_itemCurrent)
   {

      return;

   }

   auto psession = get_session();

   auto puser = psession->user();

   auto pwindowing = puser->windowing();

   pwindowing->release_mouse_capture();

   KillTimer(((uptr)this));

   KillTimer(((uptr)this)+1);

   KillTimer(43212345);

   bool bWasTracking = m_bTracking;

   m_bTracking = false;

   if (bWasTracking)
   {

      auto point = _001ScreenToClient(pmouse->m_point);

      point -= m_sizeTrackOffset;

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics();

      SetTrackingPos(point, pgraphics);

      post_scroll_message(e_scroll_command_thumb_position);

      set_need_redraw();
      
      post_redraw();
   
   }
         
   m_itemCurrent = ::user::e_element_none;

   pmouse->m_bRet = true;

}


bool simple_scroll_bar::GetTrackRect(RECTANGLE_I32 * prectangle, ::draw2d::graphics_pointer & pgraphics)
{

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   ::size_i32 sizeTrack;

   GetTrackSize(sizeTrack, pgraphics);

   i32 iPos;

   if (m_bTracking)
   {

      iPos = m_scrollinfo.nTrackPos;

   }
   else
   {

      iPos = m_scrollinfo.nPos;

   }

   auto pstyle = get_style(pgraphics);

   int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   if(m_eorientation == e_orientation_horizontal)
   {

      i32 iWidth = rectangleClient.width() - iScrollBarWidth * 2 - sizeTrack.cx;

      prectangle->top = rectangleClient.top;


      prectangle->bottom = rectangleClient.top + sizeTrack.cy;


      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         prectangle->left = 0;


      }
      else
      {

         prectangle->left = iScrollBarWidth + (iPos - m_scrollinfo.nMin) * iWidth / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);


      }

      prectangle->right = prectangle->left + sizeTrack.cx;


   }
   else if(m_eorientation == e_orientation_vertical)
   {

      i32 iHeight = rectangleClient.height() - iScrollBarWidth * 2 - sizeTrack.cy;

      prectangle->left = rectangleClient.left;

      prectangle->right = prectangle->left + sizeTrack.cx;

      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         prectangle->top = 0;

      }
      else
      {

         prectangle->top = iScrollBarWidth + (iPos - m_scrollinfo.nMin) * iHeight / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);

      }

      prectangle->bottom = prectangle->top + sizeTrack.cy;

   }

   return true;

}


bool simple_scroll_bar::_001GetScrollInfo(::user::scroll_info * psi)
{

   psi->nPage = m_scrollinfo.nPage;
   psi->nPos = m_scrollinfo.nPos ;
   psi->nMin = m_scrollinfo.nMin;
   psi->nMax = m_scrollinfo.nMax;
   psi->nTrackPos = m_scrollinfo.nTrackPos;

   return true;

}


bool simple_scroll_bar::_001SetScrollInfo(::user::scroll_info * psi, bool bRedraw)
{

   m_scrollinfo.nPage = psi->nPage;
   m_scrollinfo.nMin = psi->nMin;
   m_scrollinfo.nMax = psi->nMax;
   m_scrollinfo.nPos = psi->nPos ;
   m_scrollinfo.nTrackPos = psi->nTrackPos;
   
   return true;

}


bool simple_scroll_bar::GetTrackClientRect(RECTANGLE_I32 * prectangle, ::draw2d::graphics_pointer & pgraphics)
{

   auto pstyle = get_style(pgraphics);

   int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   if(m_eorientation == e_orientation_horizontal)
   {
//      i32 iWidth = rectangleClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;
      prectangle->bottom = rectangleClient.bottom;

      prectangle->top = rectangleClient.top;

      prectangle->left = rectangleClient.left + iScrollBarWidth;

      prectangle->right = rectangleClient.right - iScrollBarWidth;

   }
   else if(m_eorientation == e_orientation_vertical)
   {
//      i32 iWidth = rectangleClient.width() - GetSystemMetrics(SM_CYVSCROLL) * 2;
      prectangle->top = rectangleClient.top + iScrollBarWidth;

      prectangle->bottom = rectangleClient.bottom - iScrollBarWidth;

      prectangle->left = rectangleClient.left + 1;

      prectangle->right = rectangleClient.right - 1;

   }

   return true;

}


i32 simple_scroll_bar::GetTrackSize(::size_i32 &size, ::draw2d::graphics_pointer & pgraphics)
{

   auto pstyle = get_style(pgraphics);

   int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   if(m_eorientation == e_orientation_horizontal)
   {

      i32 iWidth = rectangleClient.width() - iScrollBarWidth * 2;

      i32 cx = 0;

      if(iWidth > 0)
      {

         i32 iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cx = 0;

         }
         else
         {

            cx = (m_scrollinfo.nPage  * iWidth) / iRange;

         }

      }

      if (cx < 5)
      {

         cx = 5;

      }

      size.cx = cx;

      size.cy = rectangleClient.height();

   }
   else if(m_eorientation == e_orientation_vertical)
   {

      i32 iHeight = rectangleClient.height() - iScrollBarWidth * 2;

      i32 cy = 0;

      if(iHeight > 0)
      {

         i32 iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cy = 0;

         }
         else
         {

            cy = (m_scrollinfo.nPage  * iHeight) / iRange;

         }

      }

      if (cy < 5)
      {

         cy = 5;

      }

      size.cy = cy;

      size.cx = rectangleClient.width();

   }

   return true;

}


i32 simple_scroll_bar::SetTrackingPos(const ::point_i32 & point, ::draw2d::graphics_pointer & pgraphics)
{

   i32 nPos = 0;

   ::size_i32 sizeTrack;

   GetTrackSize(sizeTrack, pgraphics);

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   auto pstyle = get_style(pgraphics);

   int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   if(m_eorientation == e_orientation_horizontal)
   {

      i32 iWidth = rectangleClient.width() - iScrollBarWidth * 2 - sizeTrack.cx;

      double dRate = (double)(point.x - iScrollBarWidth) / (double)iWidth;

      dRate = minimum(1.0, dRate);

      nPos = (i32)(dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else if(m_eorientation == e_orientation_vertical)
   {

      i32 iHeight = rectangleClient.height() - iScrollBarWidth * 2 - sizeTrack.cy;

      double dRate = (double)(point.y - iScrollBarWidth) / (double) iHeight;

      dRate = minimum(1.0, dRate);

      nPos = (i32) (dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else
   {

      ASSERT(false);

   }

   if (nPos < m_scrollinfo.nMin)
   {

      nPos = m_scrollinfo.nMin;

   }
   else if (nPos > m_scrollinfo.nMax)
   {

      nPos = m_scrollinfo.nMax;

   }

   if(m_bTracking)
   {

      m_scrollinfo.nTrackPos = nPos;

   }
   else
   {

      m_scrollinfo.nPos = nPos;

   }

   return true;

}


void simple_scroll_bar::_001OnHScroll(::message::message * pmessage)
{
   __pointer(::message::scroll) pscroll(pmessage);
   pscroll->m_bRet = false;
}

i32 simple_scroll_bar::_001GetScrollPos()
{
   if(m_bTracking)
      return m_scrollinfo.nTrackPos;
   else
      return m_scrollinfo.nPos;
}



void simple_scroll_bar::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::rectangle_i32 rectangleClient;
   get_client_rect(rectangleClient);
   ::size_i32 size = rectangleClient.size();

   int iArrowForce = 4;
   int iArrowStability = size.get_orthogonal_dimension(m_eorientation) - 2 - 3 * 2;

   auto pstyle = get_style(pgraphics);

   int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   if(m_eorientation == e_orientation_horizontal)
   {

      m_rectA.left   = 0;
      m_rectA.top    = 0;
      m_rectA.right  = minimum(iScrollBarWidth,size.cx / 2);
      m_rectA.bottom = size.cy;

      /*
      m_ptaA[0].x = 0;
      m_ptaA[0].y = size.cy / 2;
      m_ptaA[1].x = minimum(GetSystemMetrics(SM_CXHSCROLL), size.cx / 2);
      m_ptaA[1].y = size.cy - 1;
      m_ptaA[2].x = m_ptaA[1].x;
      m_ptaA[2].y = 1;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;
      */

      m_ptaA[0].x = m_rectA.left + (m_rectA.width() + iArrowForce) / 2;
      m_ptaA[0].y = m_rectA.top + (m_rectA.height() - iArrowStability) / 2;
      m_ptaA[1].x = m_rectA.left + (m_rectA.width() - iArrowForce) / 2;
      m_ptaA[1].y = m_rectA.top + m_rectA.height() / 2;
      m_ptaA[2].x = m_rectA.left + (m_rectA.width() + iArrowForce) / 2;
      m_ptaA[2].y = m_rectA.top + (m_rectA.height() + iArrowStability) / 2;;

      m_rectB.left   = maximum(size.cx - iScrollBarWidth,size.cx / 2);
      m_rectB.top    = 0;
      m_rectB.right  = size.cx;
      m_rectB.bottom = size.cy;

      /*
      m_ptaB[0].x = size.cx;
      m_ptaB[0].y = size.cy / 2;
      m_ptaB[1].x = ;
      m_ptaB[1].y = 1;
      m_ptaB[2].x = m_ptaB[1].x;
      m_ptaB[2].y = size.cy - 1;
      m_ptaB[3].x = m_ptaB[0].x;
      m_ptaB[3].y = m_ptaA[0].y;
      */

      m_ptaB[0].x = m_rectB.left + (m_rectB.width() - iArrowForce) / 2;
      m_ptaB[0].y = m_rectB.top + (m_rectB.height() - iArrowStability) / 2;
      m_ptaB[1].x = m_rectB.left + (m_rectB.width() + iArrowForce) / 2;
      m_ptaB[1].y = m_rectB.top + m_rectB.height() / 2;
      m_ptaB[2].x = m_rectB.left + (m_rectB.width() - iArrowForce) / 2;
      m_ptaB[2].y = m_rectB.top + (m_rectB.height() + iArrowStability) / 2;;

   }
   else if(m_eorientation == e_orientation_vertical)
   {

      m_rectA.left   = 0;
      m_rectA.top    = 0;
      m_rectA.right  = size.cx;
      m_rectA.bottom = minimum(iScrollBarWidth,size.cy / 2);

      /*
      m_ptaA[0].x = size.cx / 2;
      m_ptaA[0].y = 0;
      m_ptaA[1].x = 1;
      m_ptaA[1].y = minimum(GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaA[2].x = size.cx - 1;
      m_ptaA[2].y = m_ptaA[1].y;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;
      */

      m_ptaA[0].x = m_rectA.left + (m_rectA.width() - iArrowStability) / 2;
      m_ptaA[0].y = m_rectA.top + (m_rectA.height() + iArrowForce) / 2;
      m_ptaA[1].x = m_rectA.left + m_rectA.width() / 2;
      m_ptaA[1].y = m_rectA.top +( m_rectA.height() - iArrowForce) / 2;
      m_ptaA[2].x = m_rectA.left + (m_rectA.width() + iArrowStability) / 2;
      m_ptaA[2].y = m_rectA.top + (m_rectA.height() + iArrowForce) / 2;;

      m_rectB.left   = 0;
      m_rectB.top    = maximum(size.cy - iScrollBarWidth,size.cy / 2);
      m_rectB.right  = size.cx;
      m_rectB.bottom = size.cy;

      /*
      m_ptaB[0].x = size.cx / 2;
      m_ptaB[0].y = size.cy;
      m_ptaB[1].x = size.cx - 1;
      m_ptaB[1].y = maximum(size.cy - GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaB[2].x = 1;
      m_ptaB[2].y = m_ptaB[1].y;
      m_ptaB[3].x = m_ptaA[0].x;
      m_ptaB[3].y = m_ptaB[0].y;
      */
      m_ptaB[0].x = m_rectB.left + (m_rectB.width() - iArrowStability) / 2;
      m_ptaB[0].y = m_rectB.top + (m_rectB.height() - iArrowForce) / 2;
      m_ptaB[1].x = m_rectB.left + m_rectB.width() / 2;
      m_ptaB[1].y = m_rectB.top + (m_rectB.height() + iArrowForce) / 2;
      m_ptaB[2].x = m_rectB.left + (m_rectB.width() + iArrowStability) / 2;
      m_ptaB[2].y = m_rectB.top + (m_rectB.height() - iArrowForce) / 2;;
   }
   else
   {
      ASSERT(false);
   }

   m_rgnA->create_rectangle(m_rectA);
   m_rgnB->create_rectangle(m_rectB);


//   psize->m_bRet = false;
}


void simple_scroll_bar::_001OnTimer(::timer * ptimer)
{

   ::user::scroll_bar::_001OnTimer(ptimer);

   auto psession = get_session();

   auto puser = psession->user();

   auto pwindowing = puser->windowing();

   auto pointCursor = pwindowing->get_cursor_position();

   screen_to_client(pointCursor);

   if(ptimer->m_uEvent == (uptr) this)
   {

      KillTimer(ptimer->m_uEvent);

      SetTimer(((uptr) this) + 1,10,nullptr);

   }
   else if(ptimer->m_uEvent == ((uptr) this) + 1)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics();

      if(!scrollbar_action(m_itemCurrent, pgraphics))
      {

         KillTimer(ptimer->m_uEvent);

      }

   }
   //else if (ptimer->m_uEvent == 43212345)
   //{

   //   set_need_redraw();

   //}

}


bool simple_scroll_bar::scrollbar_lineA(::draw2d::graphics_pointer & pgraphics)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos-=3;

   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == e_orientation_horizontal)
   {
      
      post_scroll_message(e_scroll_command_line_left);

   }
   else
   {
      
      post_scroll_message(e_scroll_command_line_up);

   }

   if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_lineB(::draw2d::graphics_pointer & pgraphics)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos+=3;

   if (nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {

      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   }

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == e_orientation_horizontal)
   {
      
      post_scroll_message(e_scroll_command_line_right);

   }
   else
   {
      
      post_scroll_message(e_scroll_command_line_down);

   }

   if (m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
   {

      return false;

   }

   return true;

}


bool simple_scroll_bar::scrollbar_pageA(const ::point_i32 & point, ::draw2d::graphics_pointer & pgraphics)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos-=m_scrollinfo.nPage ;

   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == e_orientation_horizontal)
   {
      
      post_scroll_message(e_scroll_command_page_left);

   }
   else
   {

      post_scroll_message(e_scroll_command_page_up);

   }

   ::rectangle_i32 rectangleClient;

   ::rectangle_i32 rectTrack;

   ::rectangle_i32 rectangle;

   get_client_rect(rectangleClient);

   GetTrackRect(rectTrack, pgraphics);

   GetPageARect(rectangleClient,rectTrack,rectangle, pgraphics);

   if(!rectangle.contains(point))
      return false;

   if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_pageB(const ::point_i32 & point, ::draw2d::graphics_pointer & pgraphics)
{

   i32 nPos = m_scrollinfo.nPos;

   nPos+=m_scrollinfo.nPage ;

   if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == e_orientation_horizontal)
   {

      post_scroll_message(e_scroll_command_page_right);

   }
   else
   {

      post_scroll_message(e_scroll_command_page_down);

   }

   ::rectangle_i32 rectangleClient;

   ::rectangle_i32 rectTrack;

   ::rectangle_i32 rectangle;

   get_client_rect(rectangleClient);

   GetTrackRect(rectTrack, pgraphics);

   GetPageBRect(rectangleClient,rectTrack,rectangle, pgraphics);

   if(!rectangle.contains(point))
      return false;

   if(m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
      return false;

   return true;

}


//void simple_scroll_bar::OnDraw(::image * pimage)
//{
/*    if(GetExStyle() & WS_EX_TRANSPARENT)
{
return;
}

__pointer(::user::interaction) puiParent = get_parent();
i32 nPos = m_scrollinfo.nPos;
nPos+=m_scrollinfo.nPage;
if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
m_scrollinfo.nPos = nPos;

if(m_eorientation == e_orientation_horizontal)
{
puiParent->SendMessage(e_message_hscroll, MAKEWPARAM(e_scroll_command_LINERIGHT, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}
else
{
puiParent->SendMessage(e_message_vscroll, MAKEWPARAM(e_scroll_command_LINEDOWN, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}*/

//}


void simple_scroll_bar::on_message_create(::message::message * pmessage)
{


   __pointer(::message::create) pcreate(pmessage);


   //if (m_puserstyle == nullptr)
   //{

   //   m_puserstyle = get_top_level();

   //}

   //if (m_puserstyle == nullptr)
   //{

   //   m_puserstyle = papplication->userstyle();

   //}

   update_drawing_objects();

   pcreate->m_lresult = 0;



}


void simple_scroll_bar::pre_translate_message(::message::message * pmessage)
{

   __pointer(::user::message) pusermessage(pmessage);

   return ::user::interaction::pre_translate_message(pusermessage);

}


void simple_scroll_bar::UpdateBitmaps()
{

}


bool simple_scroll_bar::GetPageARect(RECTANGLE_I32 * prectClient,RECTANGLE_I32 * prectTrack, RECTANGLE_I32 * prectangle, ::draw2d::graphics_pointer & pgraphics)
{

   auto pstyle = get_style(pgraphics);

   int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   if(m_eorientation == e_orientation_horizontal)
   {

      prectangle->left = prectClient->left + iScrollBarWidth;

      prectangle->top = prectTrack->top;

      prectangle->right = prectTrack->left;

      prectangle->bottom = prectTrack->bottom;

   }
   else if(m_eorientation == e_orientation_vertical)
   {
      prectangle->left = prectTrack->left;

      prectangle->top = prectClient->top + iScrollBarWidth;

      prectangle->right = prectTrack->right;

      prectangle->bottom = prectTrack->top;

   }

   return true;

}


bool simple_scroll_bar::GetPageBRect(RECTANGLE_I32 * prectClient,RECTANGLE_I32 * prectTrack, RECTANGLE_I32 * prectangle, ::draw2d::graphics_pointer & pgraphics)
{

   auto pstyle = get_style(pgraphics);

   int iScrollBarWidth = get_int(pstyle, ::user::e_int_scroll_bar_width);

   if(m_eorientation == e_orientation_horizontal)
   {

      prectangle->left = prectTrack->right;

      prectangle->top = prectTrack->top;

      prectangle->right = prectClient->right - iScrollBarWidth;

      prectangle->bottom = prectTrack->bottom;

   }
   else if(m_eorientation == e_orientation_vertical)
   {
      prectangle->left = prectTrack->left;

      prectangle->top = prectTrack->bottom;

      prectangle->right = prectTrack->right;

      prectangle->bottom = prectClient->bottom - iScrollBarWidth;

   }

   return true;

}



i32 simple_scroll_bar::_001SetScrollPos(i32 iPos)
{
   m_scrollinfo.nPos = iPos ;
   if(m_scrollinfo.nPos < m_scrollinfo.nMin)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMin;
   }
   else if(m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
   }
   //set_need_redraw();
   return true;
}


//LRESULT simple_scroll_bar::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
//{
//   __UNREFERENCED_PARAMETER(wParam);
//   __UNREFERENCED_PARAMETER(lParam);
//   update_drawing_objects();
//   //set_need_redraw();
//
//   return true;
//}

void simple_scroll_bar::update_drawing_objects()
{

}


class trw:
   virtual public ::user::interaction
{
public:

   ::point_i32 point1;
   ::point_i32 point2;


   trw()
   {

      //auto pusersystem = __new(::user::system (WS_EX_LAYERED, nullptr, "", WS_VISIBLE));

      //if(create_window_ex(pusersystem))
      if(create_host())
      {

         TRACE("created trw");

      }

      best_monitor(nullptr,nullptr,true);

   }

   virtual ~trw()
   {

   }


   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      pgraphics->move_to(point1);
      pgraphics->line_to(point2);
   }
};


// Important:
//
// The default _001OnClip implemenstation clips the current window
// to all ascending windows client area intersection.
// The client area of a window excludes its children scroll bars
// region.
// For the scroll bar, this algorithm would clip scroll bar child
// window from its drawing.
// This overload for this scroll bar overcomes this issue.
void simple_scroll_bar::_001OnClip(::draw2d::graphics_pointer & pgraphics)
{

   try
   {

      //::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      //bool bFirst = true;
      //
      //if (pdrawcontext != nullptr)
      //{

      //   ::rectangle_i32 rectangleClient;

      //   rectangleClient = pdrawcontext->m_rectangleWindow;

      //   screen_to_client(rectangleClient);

      //   rectangleClient.bottom++;
      //   rectangleClient.right++;

      //   rectClip = rectangleClient;

      //   bFirst = false;

      //}
      
      if(!m_pshapeaClip)
      {
         
         __construct_new(m_pshapeaClip);

         ::user::interaction * pinteraction = this;

         ::rectangle_i32 rectFocus;

         index i = 0;

         while (pinteraction != nullptr)
         {

            if (i == 1)
            {

               pinteraction->::user::interaction::get_client_rect(rectFocus);

            }
            else
            {

               pinteraction->get_client_rect(rectFocus);

            }

            pinteraction->client_to_screen(rectFocus);

            screen_to_client(rectFocus);
            
            m_pshapeaClip->add_item(__new(rectangle_shape(rectFocus)));

            m_pshapeaClip->add_item(__new(intersect_clip_shape()));

            i++;

            pinteraction = pinteraction->get_parent();

         }
         
      }
      
      pgraphics->reset_clip();

      pgraphics->m_pointAddShapeTranslate.Null();

      pgraphics->add_shapes(*m_pshapeaClip);

   }
   catch (...)
   {

      throw ::exception::exception("no more a window");

   }

}


void simple_scroll_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   //::user::style_context style(this);

   auto pstyle = get_style(pgraphics);

   if(pstyle)
   {

      if (pstyle->_001DrawSimpleScrollBar(pgraphics, this))
      {

         return;

      }

      //style.next();

   }

   //style = this;

   if(pstyle)
   {

      if (pstyle->_001DrawScrollBar(pgraphics, this))
      {

         return;

      }

   //   style.next();

   }

   _001OnVerisimpleDraw(pgraphics);

}


void simple_scroll_bar::_001OnVerisimpleDraw(::draw2d::graphics_pointer & pgraphics)
{

   auto pstyle = get_style(pgraphics);

   auto crBackground = get_color(pstyle, ::user::e_element_background);

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   if (crBackground.is_translucent())
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto psession = get_session();

      if (psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing))
      {

         pgraphics->fill_rectangle(rectangleClient, rgb(255, 255, 255));

      }
      else
      {

         pgraphics->fill_rectangle(rectangleClient, argb(255, 240, 240, 240));

      }

   }

   ::rectangle_i32 rectTrack;

   GetTrackRect(rectTrack, pgraphics);

   ::rectangle_i32 rectWindow;

   get_window_rect(rectWindow);

   m_brushDraw->create_solid(scrollbar_color_strong(pstyle, ::user::e_element_scrollbar_rect));

   pgraphics->set(m_brushDraw);

   pgraphics->fill_rectangle(rectTrack);

   //if (m_bTracking || (bool)prop("tracking_on"))
   //{

   //   ::u32 tickFadeIn = 300;

   //   ::u32 tickFadeOut = 300;

   //   byte uchAlpha = maximum(0, minimum(255, prop("tracking_alpha").u32()));

   //   if (m_bTracking)
   //   {

   //      if (!(bool)prop("tracking_on"))
   //      {

   //         prop("tracking_on") = true;

   //         prop("tracking_start") = (u32)(::get_tick() + uchAlpha * tickFadeIn / 255);

   //         prop("tracking_fade_in") = true;

   //         prop("tracking_fade_out") = false;

   //         prop("tracking_type") = __random(1, 2);

   //         if (prop("tracking_simple").i32() == 2)
   //         {

   //            int iDeflate = rectTrack.size().get_normal(m_eorientation);

   //            iDeflate /= 2;

   //            ::rectangle_i32 rectConstraint(m_rectTrack);

   //            rectConstraint.deflate(iDeflate, iDeflate);

   //            constraint(m_pointTrack, rectConstraint);

   //            m_sizeTrackOffset = m_pointTrack - m_rectTrack.top_left();

   //         }

   //      }

   //   }
   //   else
   //   {

   //      if (!(bool)prop("tracking_fade_out"))
   //      {

   //         prop("tracking_fade_in") = false;

   //         prop("tracking_fade_out") = true;

   //         prop("tracking_start") = (u32)(::get_tick() + (255 - uchAlpha) * tickFadeOut / 255);

   //      }

   //   }

   //   const ::point_i32 & point1 = rectTrack.top_left() + m_sizeTrackOffset;

   //   client_to_screen(point1);

   //   ::point_i32 point2;

   //   psession->get_cursor_position(&point2);

   //   client_to_screen(point1);

   //   if ((bool)prop("tracking_fade_in"))
   //   {

   //      ::u32 dwFade = prop("tracking_start").u32().elapsed();

   //      if (dwFade < tickFadeIn)
   //      {

   //         uchAlpha = (byte)minimum(255, maximum(0, (dwFade * 255 / tickFadeIn)));

   //      }
   //      else
   //      {

   //         uchAlpha = 255;

   //         prop("tracking_fade_in") = false;

   //      }

   //   }
   //   else if ((bool)prop("tracking_fade_out"))
   //   {

   //      ::u32 dwFade = prop("tracking_start").u32().elapsed();

   //      if (dwFade < tickFadeOut)
   //      {

   //         uchAlpha = (byte)(255 - minimum(255, maximum(0, (dwFade * 255 / tickFadeOut))));

   //      }
   //      else
   //      {

   //         uchAlpha = 0;

   //         prop("tracking_on") = false;

   //         prop("tracking_fade_out") = false;

   //      }

   //   }
   //   else
   //   {
   //      uchAlpha = 255;
   //   }

   //   ::rectangle_i32 rectMachineThumb;

   //   i32 iType = prop("tracking_type").i32();

   //   if (iType == 1)
   //   {

   //      int iSize = rectTrack.size().get_normal(m_eorientation);

   //      rectMachineThumb.top_left() = rectTrack.top_left() + m_sizeTrackOffset - size_i32(iSize / 2, iSize / 2);

   //      rectMachineThumb.bottom_right() = rectMachineThumb.top_left() + size(iSize, iSize);

   //      ::rectangle_i32 rectIntersect;

   //      rectIntersect.intersect(rectMachineThumb, rectTrack);

   //      i32 iArea = (i32)(maximum(1, rectIntersect.area()));

   //      rectMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

   //      draw_mac_thumb_simple(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

   //   }
   //   else
   //   {

   //      int iSize = rectTrack.size().get_normal(m_eorientation);

   //      rectMachineThumb.top_left() = rectTrack.top_left() + m_sizeTrackOffset - size_i32(iSize / 2, iSize / 2);

   //      rectMachineThumb.set_size(iSize, iSize);

   //      rectMachineThumb.assign_normal(rectTrack, m_eorientation);

   //      draw_mac_thumb_dots(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

   //   }

   //   prop("tracking_alpha") = uchAlpha;

   //}

   ::color32_t color32 = scrollbar_color(pstyle, ::user::e_element_scrollbar_rectA);

   m_brushDraw->create_solid(color32);

   pgraphics->set(m_brushDraw);

   pgraphics->fill_rectangle(m_rectA);

   color32 = scrollbar_color(pstyle, ::user::e_element_scrollbar_rectB);

   m_brushDraw->create_solid(color32);

   pgraphics->set(m_brushDraw);

   pgraphics->fill_rectangle(m_rectB);

   ::rectangle_i32 rectangle;

   if (m_itemCurrent == ::user::e_element_scrollbar_pageA || m_itemHover== ::user::e_element_scrollbar_pageA)
   {

      GetPageARect(rectangleClient, rectTrack, rectangle, pgraphics);

      color32 = scrollbar_color(pstyle, ::user::e_element_scrollbar_pageA);

      m_brushDraw->create_solid(color32);

      pgraphics->set(m_brushDraw);

      pgraphics->fill_rectangle(rectangle);

   }
   else if (m_itemCurrent == ::user::e_element_scrollbar_pageB || m_itemHover== ::user::e_element_scrollbar_pageB)
   {

      GetPageBRect(rectangleClient, rectTrack, rectangle, pgraphics);

      color32 = scrollbar_color(pstyle, ::user::e_element_scrollbar_pageB);

      m_brushDraw->create_solid(color32);

      pgraphics->set(m_brushDraw);

      pgraphics->fill_rectangle(rectangle);

   }

   ::draw2d::pen_pointer penArrow(e_create);

   penArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;

   penArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;

   penArrow->m_elinejoin = ::draw2d::e_line_join_round;

   color32 = scrollbar_draw_color(pstyle, ::user::e_element_scrollbar_rectA);

   penArrow->create_solid(1.0, color32);

   pgraphics->set(penArrow);

   pgraphics->polyline(m_ptaA, 3);

   color32 = scrollbar_draw_color(pstyle, ::user::e_element_scrollbar_rectB);

   penArrow->create_solid(1.0, color32);

   pgraphics->set(penArrow);

   pgraphics->polyline(m_ptaB, 3);

}


void simple_scroll_bar::on_message_show_window(::message::message * pmessage)
{
   __pointer(::message::show_window) pshowwindow(pmessage);
   pshowwindow->m_bRet = false;

   // xxx   TwiOnShowWindow(bShow, nStatus);
}

void simple_scroll_bar::on_message_destroy(::message::message * pmessage)
{
   __UNREFERENCED_PARAMETER(pmessage);
}


void simple_scroll_bar::draw_mac_thumb_simple(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectDrawParam,const ::rectangle_i32 & lpcrectClip,byte uchAlpha)
{

   ::draw2d::savedc dc(pgraphics);

   pgraphics->reset_clip();

   ::rectangle_i32 rectDraw(rectDrawParam);

   rectDraw.deflate(1,1);

   ::draw2d::pen_pointer pen(e_create);

   pen->create_solid(2.0,argb(150 * uchAlpha / 255,108, 108, 100));

   pgraphics->set(pen);

   pgraphics->draw_ellipse(rectDraw);

   ::draw2d::brush_pointer brush(e_create);

   ::rectangle_i32 rectDotto(0,0,5,5);

   brush->create_solid(argb(150 * uchAlpha / 255,108,108,100));

   pgraphics->set(brush);

   rectDotto.Align(e_align_center, rectDraw);

   pgraphics->fill_ellipse(rectDotto);

}



void simple_scroll_bar::draw_mac_thumb_dots(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectDrawParam, const ::rectangle_i32 & lpcrectClip,byte uchAlpha)
{

   ::rectangle_f64 rectDraw(rectDrawParam);

   rectDraw.bottom--;

   rectDraw.right--;

   double iDiv = 10;

   if (m_pimageDots->is_null())
   {

      auto estatus = __construct(m_pimageDots);

      if (!estatus)
      {

         return;

      }

      estatus = m_pimageDots->create({ (int)(rectDraw.width() * iDiv), (int)(rectDraw.height() * iDiv) });

      if (!estatus)
      {

         return;

      }

      m_pimageDots->fill_byte(0);

      if (!m_pimageDots->g())
      {

         return;

      }

      m_pimageDots->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      double iDiv2 = iDiv / 2;

      double iDiv3 = iDiv2 / 2;

      double x = m_pimageDots->width() / (iDiv * 2);

      double iSize = iDiv3;

      for (int i = 0; i <= iDiv2; i++)
      {

         double y = m_pimageDots->height() / (iDiv * 2);

         for (int j = 0; j <= iDiv2; j++)
         {

            iSize = maximum(abs(m_pimageDots->width() / 2 - x), abs(m_pimageDots->width() / 2 - y));

            iSize = (m_pimageDots->width() / 2) - iSize;

            iSize = pow(iSize, 0.55);

            rectangle_f64 r(x - iSize, y - iSize, x + iSize, y + iSize);

            m_pimageDots->g()->fill_rectangle(r, argb(80, 0, 0, 0));

            y += m_pimageDots->height() / (iDiv2 + 1.0);

         }

         x += m_pimageDots->width() / (iDiv2 + 1.0);

      }

   }

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

   auto rectangleTarget = rectDraw;

   auto pointSrc = ::point_f64(iDiv, iDiv);

   auto sizeSrc = m_pimageDots->get_size() - ::size_f64(iDiv * 2, iDiv * 2);

   auto rectangleSource = ::rectangle_f64(pointSrc, sizeSrc);

   image_source imagesource(m_pimageDots, rectangleSource);

   image_drawing_options imagedrawingoptions(rectangleTarget);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);
   
   imagedrawing.opacity(uchAlpha);

   pgraphics->draw(imagedrawing);

}


void simple_scroll_bar::on_hit_test(::user::item & item)
{

   ::rectangle_i32 rectTrack;

   auto psystem = m_psystem->m_paurasystem;

   auto pdraw2d = psystem->draw2d();

   auto pgraphics = pdraw2d->create_memory_graphics();

   GetTrackRect(rectTrack, pgraphics);

   if(rectTrack.contains(item.m_pointClient))
   {

      item = ::user::e_element_scrollbar_rect;

   }
   else
   {

      ::rectangle_i32 rectangle;

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      GetPageARect(rectangleClient, rectTrack, rectangle, pgraphics);

      if (rectangle.contains(item.m_pointClient))
      {

         item = ::user::e_element_scrollbar_pageA;

         return;

      }

      GetPageBRect(rectangleClient, rectTrack, rectangle, pgraphics);

      if (rectangle.contains(item.m_pointClient))
      {

         item = ::user::e_element_scrollbar_pageB;

         return;

      }

      if (m_rectA.contains(item.m_pointClient))
      {

         item = ::user::e_element_scrollbar_rectA;

         return;

      }

      if (m_rectB.contains(item.m_pointClient))
      {

         item = ::user::e_element_scrollbar_rectB;

         return;

      }

      item = ::user::e_element_none;

   }

}


::color::color simple_scroll_bar::scrollbar_color_strong(::user::style * pstyle, ::user::enum_element eelement)
{

   if (m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, ::user::e_element_scrollbar_strong, ::user::e_state_hover);

      return color.is_ok() ? color : argb(130, 190, 180, 250);

   }
   else
   {

      auto color = get_color(pstyle, ::user::e_element_scrollbar_strong);

      return color.is_ok() ? color : argb(150, 150, 150, 150);

   }

}


::color::color simple_scroll_bar::scrollbar_color(::user::style* pstyle, ::user::enum_element eelement)
{

   if(m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, eelement, ::user::e_state_hover);

      return color.is_ok() ? color : argb(100, 190, 180, 250);

   }
   else
   {

      auto color = get_color(pstyle, eelement);

      return color.is_ok() ? color : argb(150, 150, 150, 150);

   }

}


::color::color simple_scroll_bar::scrollbar_border_color(::user::style* pstyle, ::user::enum_element eelement)
{

   if(m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, ::user::e_element_border, ::user::e_state_hover);

      return color.is_ok() ? color : argb(190, 180, 180, 180);

   }
   else
   {

      auto color = get_color(pstyle, ::user::e_element_border);

      return color.is_ok() ? color : argb(190, 160, 160, 160);

   }

}


::color::color simple_scroll_bar::scrollbar_lite_border_color(::user::style* pstyle, ::user::enum_element eelement)
{

   if(m_itemCurrent == eelement || m_itemHover== eelement)
   {

      auto color = get_color(pstyle, ::user::e_element_lite_border, ::user::e_state_hover);

      return color.is_ok() ? color : argb(190, 90, 110, 180);

   }
   else
   {

      auto color = get_color(pstyle, ::user::e_element_lite_border);

      return color.is_ok() ? color : argb(190, 110, 110, 100);

   }

}


::color::color simple_scroll_bar::scrollbar_draw_color(::user::style* pstyle, ::user::enum_element eelement)
{

   if (m_itemCurrent == eelement || m_itemHover == eelement)
   {

      auto color = get_color(pstyle, ::user::e_element_scrollbar_draw, ::user::e_state_hover);

      return color.is_ok() ? color : argb(127, 90, 90, 90);

   }
   else
   {

      auto color = get_color(pstyle, ::user::e_element_scrollbar_draw);

      return color.is_ok() ? color : argb(127, 65, 65, 65);

   }

}



