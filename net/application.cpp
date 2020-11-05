#include "framework.h"
#define NO_IMAGING
#include "aura/application.h"
#include "aura/update.h"


namespace app_net
{


   application::application()
   {

      m_strAppId = "app/app";

      m_strAppName = "app/app";

      m_strBaseSupportId = "app_app";

      m_bLicense = false;

   }


   application::~application()
   {

   }


   ::estatus application::init_instance()
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

      m_pwindow->create_main_window();

      m_pwindow->start_layout();

      m_pwindow->display(display_normal);

      m_pwindow->set_need_layout();

      m_pwindow->set_need_redraw();

      m_pwindow->set_layout_ready();

      m_pwindow->post_redraw();

   }


#ifdef _DEBUG


   int64_t application::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t application::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }


#endif


   __namespace_application_factory("app/net");


} // namespace app_net



