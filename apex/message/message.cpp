#include "framework.h"


namespace message
{


   //message::message(const ::id & id) :
   //{

   //   //common_construct();

   //}


   //message::message(enum_message emessage)
   //{

   //   common_construct(emessage);

   //}


   message::~message()
   {

   }



   //bool message::route_message()
   //{

   //   return m_bRet;

   //}


   bool message::all_previous()
   {

      while (m_iRouteIndex >= 0)
      {

         bool bRet = previous();

         if (bRet)
         {

            break;

         }

      }

      return true;

   }


   bool message::previous() 
   { 

      if (--m_iRouteIndex < 0)
      {

         return false;

      }

      if (m_phandlera->m_pData)
      {

         m_phandlera->m_pData[m_iRouteIndex].m_handler(this);

      }

      return m_bRet; 
   
   }


   void message::set_lresult(lresult lresult)
   {

      m_lresult = lresult;

   }


   //void message::set(oswindow oswindow, ::windowing::window * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam, const ::point_i32 & point)
   void message::set(oswindow oswindow, ::windowing::window* playeredUserPrimitive, const ::id& id, wparam wparam, ::lparam lparam)
   {
      
      //initialize(playeredUserPrimitive);

      m_oswindow = oswindow;

      m_id = id;

      m_wparam = wparam;

      m_lparam = lparam;

   }


} // namespace message



