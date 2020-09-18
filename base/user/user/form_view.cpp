#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aura/update.h"
#include "acme/const/id.h"


namespace user
{


   form_view::form_view()
   {

   }


   form_view::~form_view()
   {

   }


   void form_view::update(::update * pupdate)
   {

      ::user::impact::update(pupdate);

      if (pupdate->m_id == id_browse)
      {

         if (!pupdate->value(id_form).is_empty())
         {

            if (get_document()->on_open_document(pupdate->value(id_form)))
            {

               m_strPath = pupdate->value(id_form);

            }

         }

      }
      else if (pupdate->m_id == id_get_form_view)
      {

         pupdate->value(id_form) = this;

      }

      if(m_pcallback != nullptr)
      {

         pupdate->value(id_form) = this;

         m_pcallback->call_update(pupdate);

      }

   }


   bool form_view::Navigate(const char * pszUrl)
   {

      UNREFERENCED_PARAMETER(pszUrl);

      return false;

   }


   ::estatus form_view::open_document(const var & varFile)
   {

      System.defer_create_html();

      __pointer(::user::form) pformOld;

      if (m_pform != this)
      {

         pformOld = m_pform;

      }

      string strHtml;

      ::file::path pathHtml;

      bool bHtml = System.m_phtml->defer_get_html(strHtml, pathHtml, this, varFile);

      bool bOk = true;

      if(bHtml)
      {

         bOk = false;

         m_pform = create_view(Session.user()->get_html_view_type());

         if(m_pform)
         {

            m_pform->set_parent_form(this);

            m_pform->set_form_callback(m_pcallback);

            if (strHtml.has_char())
            {

               if (m_pform->open_html(strHtml))
               {

                  bOk = true;

               }

            }
            else if (m_pform->open_document(pathHtml))
            {

               bOk = true;

            }
            else
            {

               m_pform->DestroyWindow();

               m_pform.release();

            }

         }

      }
      else
      {

         m_pform.release();

      }

      if(pformOld)
      {

         __pointer(::user::form_view) pview = pformOld;

         if (pview)
         {

            get_document()->remove_view(pview);

         }

         pformOld->DestroyWindow();

         pformOld.release();

      }

      if (bOk)
      {

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

      return bOk;

   }


   ::estatus form_view::open_html(const string & str)
   {

      sync_lock sl(mutex());

      auto pformOld = m_pform;

      ::estatus     estatus = error_failed;

      //__pointer(::user::form_view) pformChild = create_view(Session.userex()->get_html_view_type());
      //
      //if(pformChild)
      //{
      //
      //   pformChild->set_form_callback(pformOld->get_form_callback());
      //
      //   if(pformChild->open_html(str))
      //   {
      //
      //      try
      //      {
      //
      //         if(pformOld)
      //         {
      //
      //            pformOld->hide();
      //
      //            pformOld->DestroyWindow();
      //
      //            pformOld.release();
      //
      //         }
      //
      //      }
      //      catch (...)
      //      {
      //
      //      }
      //
      //      m_pform = pformChild;
      //
      //      set_need_layout();

      //      set_need_redraw();

      //      post_redraw();

      //      estatus = success;
      //
      //   }
      //   else
      //   {
      //
      //      pformChild->DestroyWindow();
      //
      //      pformChild.release();
      //
      //   }
      //
      //}

      return estatus;

   }


   void form_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      BASE_VIEW::on_layout(pgraphics);

      if (m_pform)
      {

         auto rectClient = get_client_rect();

         m_pform->place(rectClient);

         m_pform->display();

         m_pform->set_reposition();

         m_pform->set_need_layout();

         m_pform->set_need_redraw();

      }

   }


   void form_view::soft_reload()
   {

      if(m_pform)
      {

         m_pform->soft_reload();

      }

   }


   void form_view::on_control_event(::user::control_event * pevent)
   {

      form_window::on_control_event(pevent);

      if (pevent->m_eevent == ::user::event_form_initialize && pevent->m_puie == this)
      {

         if (get_document())
         {

            call_sync(get_document()->m_mapRunnablea["load"]);

         }

      }

   }


   void form_view::set_need_load_form_data()
   {

      if (m_pform)
      {

         m_pform->set_need_load_form_data();

      }
      else
      {

         ::user::form_window::set_need_load_form_data();

      }

   }


} // namespace user



