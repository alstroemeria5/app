﻿#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   operation_list_view::operation_list_view()
   {

      m_millisLastUpdate.Now();

   }

   void operation_list_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::list::install_message_routing(pchannel);
//      //MESSAGE_LINK(e_message_timer,pchannel,this,&operation_list_view::_001OnTimer);
      MESSAGE_LINK(e_message_create,pchannel,this,&operation_list_view::on_message_create);
   }


   void operation_list_view::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   ::count operation_list_view::_001GetItemCount()
   {
      if(get_document() == nullptr)
         return 0;
      return get_document()->m_thread.get_item_count();
   }

   __pointer(operation_document) operation_list_view::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_list_view::_001GetItemText(::user::mesh_item * pitem)
   {
      if(pitem->m_iSubItem == 0)
      {
         pitem->m_strText = get_document()->m_thread.get_item_message((i32)pitem->m_iItem);
         pitem->m_bOk = true;
      }
      else
      {
         double d;
         d = get_document()->m_thread.get_item_progress((i32)pitem->m_iItem);
         pitem->m_strText.Format("%0.1f%%",d * 100.0);
         pitem->m_bOk = true;
      }
   }

   void operation_list_view::_001InsertColumns()
   {
      {
         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 500;
         pcolumn->m_iSubItem = 0;
         pcolumn->m_sizeIcon.cx = 16;
         pcolumn->m_sizeIcon.cy = 16;

      }

      {

         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 500;
         pcolumn->m_iSubItem = 1;
         pcolumn->m_sizeIcon.cx = 16;
         pcolumn->m_sizeIcon.cy = 16;


      }

   }




   void operation_list_view::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      auto estatus = __defer_construct_new(m_puserlistcache);

      m_pmeshcache = m_puserlistcache;

      SetTimer(123,500,nullptr);

   }

   void operation_list_view::_001OnTimer(::timer * ptimer)
   {
      BASE::_001OnTimer(ptimer);
      if(ptimer->m_uEvent == 123)
      {
         /*if(m_millisLastUpdate.elapsed() > 500)
         {
         m_millisLastUpdate= ::millis::now();
         _001OnUpdateItemCount();
         m_cache._001Invalidate();
         }*/
      }

   }


   void operation_list_view::OnFileOperationStep(i32 iOperation,bool bFinal)
   {

      __UNREFERENCED_PARAMETER(iOperation);

      if(bFinal || m_millisLastUpdate.elapsed() > 200)
      {

         m_millisLastUpdate= ::millis::now();

         _001OnUpdateItemCount();

         m_puserlistcache->_001Invalidate(this);

         ::count iItem = 0;

         for(i32 i = 0; i < get_document()->m_thread.m_iOperation; i++)
         {

            iItem += get_document()->m_thread.m_fileoperationa.get_size();

         }

         if(get_document()->m_thread.m_iOperation < get_document()->m_thread.m_fileoperationa.get_size())
         {

            iItem += get_document()->m_thread.m_fileoperationa[get_document()->m_thread.m_iOperation]->m_iFile;

         }

         _001ItemScroll(iItem);

      }

   }


   void operation_list_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      BASE::on_subject(psubject, pcontext);

      if (psubject->id() == INITIAL_UPDATE)
      {

         _001UpdateColumns();

      }

   }


} // namespace filemanager



