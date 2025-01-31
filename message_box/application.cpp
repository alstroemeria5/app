#include "framework.h"
#include "aura/update.h"


namespace app_message_box
{


   application::application()
   {

      m_strAppId = "app/message_box";

      m_strAppName = "app/message_box";

      m_strBaseSupportId = "app/message_box";

      m_bLicense = false;

      m_bImaging = false;

      //m_bWriteText = false;

   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {

      if (!::aura::application::init_instance())
      {

         return false;

      }

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

      __compose_new(m_pwindow);

      m_pwindow->display(e_display_normal);

      m_pwindow->create_main_window();

      m_pwindow->set_need_layout();

      m_pwindow->set_need_redraw();

      m_pwindow->post_redraw();

   }


#ifdef _DEBUG


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif

  
} // namespace app_message_box



