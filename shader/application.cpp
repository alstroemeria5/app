#include "framework.h"
#include "aura/update.h"


namespace app_shader
{


   application::application() 
   {

      m_strAppId = "app/shader";

      m_strAppName = "app/shader";

      m_strBaseSupportId = "app/shader";

      m_bLicense = false;

      m_bImaging = false;

      m_bWriteText = false;

   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {

      set_local_data();

      create_factory <::app_shader::main_window >();

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

      __compose(m_pmainwindow, __create_new < ::app_shader::main_window > ());

      rectangle_i32 rectWindow;

      m_pmainwindow->_001InitialFramePosition(rectWindow, { 0.05, 0.05, 0.4, 0.4 });

      //auto pusersystem = __new(::user::system(0, nullptr, "app_app", WS_VISIBLE, rectWindow));

      //m_pmainwindow->create_window_ex(pusersystem);

      m_pmainwindow->create_host();

      m_pmainwindow->display(e_display_normal);

      m_pmainwindow->place(rectWindow);

      m_pmainwindow->set_need_layout();

      m_pmainwindow->set_need_redraw();

      m_pmainwindow->post_redraw();

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


   string application::get_next_shader_path(const string& strPath)
   {

      ::file::listing listing;

      get_shader_listing(listing);

      auto next = listing.get_next(strPath);

      return ::move(next);

   }


   void application::get_shader_listing(::file::listing & listing)
   {

      auto pcontext = m_pcontext->m_papexcontext;

      pcontext->dir().ls_pattern(listing, "dropbox://shader/simple shader/", { "*.frag" });

      listing.sort();

   }


} // namespace app_shader



