#include "framework.h"


namespace browser
{


   document::document(::object * pobject) :
      object(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject),
      ::user::document(pobject)
   {

   }


   document::~document()
   {

   }





   void document::assert_valid() const
   {

      ::user::document::assert_valid();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & varFile)
   {

      impact * pview = get_typed_view < impact >();

      if(pview == nullptr)
      {

         return true;

      }

      string strPath = varFile.get_file_path();

      varFile["url"] = strPath.c_str();
      varFile["http_set"]["raw_http"] = true;
      varFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

/*      ::image_pointer pimage = get_image(varFile, true);

/*      if(pimage->is_ok())
      {

         {

            synchronous_lock synchronouslock(pview->mutex());

/*            pview->m_prender->m_pimageImage = pimage;

            pview->m_strImage = strPath;

            pview->m_prender->m_bImageChanged = true;

         }

         {

            synchronous_lock slText(&pview->m_mutexText);

            pview->m_strHelloBrowser = "image:" + pview->m_strImage + "," + pview->m_strHelloBrowser;

         }

      }
      else if(get_typed_view < ::user::plain_edit_view >() != nullptr
              && pcontext->m_papexcontext->file().exists(varFile)
              && (str = pcontext->m_papexcontext->file().as_string(varFile)).has_char())
      {

         get_typed_view < ::user::plain_edit_view >()->_001SetText(str.Left(84),::e_source_user);

      }
      else if(get_typed_view < ::userex::pane_tab_view >() != nullptr)
      {

         get_typed_view < ::userex::pane_tab_view >()->set_current_tab_by_id(MAIN_IMPACT);

      }

      return true;

   }


   i64 document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


} // namespace browser



