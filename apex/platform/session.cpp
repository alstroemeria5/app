#include "framework.h"
#include "apex/operating_system.h"
#include "acme/id.h"
#include "apex/platform/app_core.h"
#include "acme/platform/static_setup.h"


#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)


namespace PLATFORM_NAMESPACE
{


   CLASS_DECL_APEX ::user::interaction * create_host_window();


} // namespace PLATFORM_NAMESPACE


#endif


#ifdef CUBE
extern "C"
::application * cube_get_app();
#endif

void defer_term_ui();


CLASS_DECL_ACME bool is_verbose();


int_bool point_is_window_origin(POINT_I32 ptHitTest, ::windowing::window * pwindowExclude, int iMargin);

#ifdef _UWP

#include "apex/node/operating_system/universal_windows/_universal_windows.h"

#elif defined(LINUX)

void x11_on_start_session();

#endif


namespace apex
{


   session::session()
   {

      m_papexsession = this;
      ::object::m_pcontext = this;
      m_pcontext = this;

      m_paquasession = nullptr;
      m_paurasession = nullptr;
      m_paxissession = nullptr;
      m_pbasesession = nullptr;
      m_pbredsession = nullptr;
      m_pcoresession = nullptr;
      //m_psession = this;
      m_bSimpleMessageLoop = false;
      m_bMessageThread = true;
      m_iEdge = -1;

      //set_layer(LAYERED_APEX, this);

      //create_factory < ::user::user >();
      create_factory < ::apex::session, ::apex::session >();

      //m_XstrAppId                    = "core_session";
      //m_strAppName                  = "core_session";
      //m_strBaseSupportId            = "core_session";
      //m_strInstallToken             = "core_session";

      //m_puiLastUserInputPopup = nullptr;

      //m_pdocs = create_session_docs();

      //m_bLicense				               = false;

      //m_bLicense           = false;
      //m_eexclusiveinstance = ExclusiveInstanceNone;

   }


   session::~session()
   {

      output_debug_string("apex::session::~session()");

   }


   ::e_status session::initialize(::object * pobject)
   {

      auto estatus = ::thread::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_bIfs                           = true;

      m_bProgrammerMode                = false;

      m_bSystemSynchronizedCursor      = true;

      //set_context_session(this);

      m_pcontext = this;

      auto psystem = get_system()->m_papexsystem;

      if (psystem != nullptr)
      {

         m_bSystemSynchronizedCursor   = psystem->m_bSystemSynchronizedCursor;

      }

      //m_papplicationCurrent                    = nullptr;

      m_bZipIsDir2                     = true;

      m_iEdge                          = 0;

      m_bShowPlatform                  = false;

      m_papplicationCurrent                    = nullptr;

      return ::success;

   }


   void session::install_message_routing(::channel* pchannel)
   {

      ::apex::context::install_message_routing(pchannel);
      
      MESSAGE_LINK(e_message_erase_application, pchannel, this, &session::on_message_erase_application);

   }


   void session::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   {


   }


   string session::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   bool session::is_session() const
   {

      return true;

   }

   
   //void session::enum_display_monitors()
   //{


   //}
   

   //index session::get_main_monitor(RECTANGLE_I32* prectangle)
   //{

   //   return -1;

   //}


   //::count session::get_monitor_count()
   //{

   //   return -1;

   //}

   
   //bool  session::get_monitor_rectangle(index iMonitor, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}

   
   //::count session::get_desk_monitor_count()
   //{

   //   return -1;

   //}


   //bool  session::get_desk_monitor_rect(index iMonitor, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //index session::get_main_workspace(RECTANGLE_I32* prectangle)
   //{

   //   return -1;

   //}


   //::count session::get_workspace_count()
   //{

   //   return -1;

   //}


   //bool  session::get_workspace_rectangle(index iWorkspace, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}

   //
   //::count session::get_desk_workspace_count()
   //{

   //   return -1;

   //}
  
   //
   //bool  session::get_desk_workspace_rect(index iWorkspace, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //bool session::set_main_monitor(index iMonitor)
   //{

   //   return false;

   //}
   

   //bool session::set_main_workspace(index iWorkspace)
   //{

   //   return false;

   //}


   //bool session::workspace_to_monitor(RECTANGLE_I32* prectangle, index iMonitor, index iWorkspace)
   //{

   //   return false;

   //}


   //bool session::monitor_to_workspace(RECTANGLE_I32* prectangle, index iWorkspace, index iMonitor)
   //{

   //   return false;

   //}


   //bool session::workspace_to_monitor(RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //bool session::monitor_to_workspace(RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //void session::get_monitor(rectangle_i32_array& rectaMonitor, rectangle_i32_array& rectaIntersect, const ::rectangle_i32& rectangle)
   //{


   //}


   ::color::color session::get_default_color(u64 u)
   {

      auto psystem = get_system()->m_papexsystem;

      auto pnode = psystem->node();

      if (!pnode)
      {

         return argb(127, 0, 0, 0);

      }

      return pnode->get_default_color(u);

   }






   //size_i32 session::get_window_minimum_size()
   //{

   //   return size_i32(300, 300);

   //}


   ::e_status session::init_thread()
   {

      auto estatus = process_init();

      if (!estatus)
      {

         return estatus;

      }

      estatus = init_session();

      if (!estatus)
      {

         return estatus;

      }

      // // now there is attempt here
      //estatus = defer_initialize_host_window();

      //if(!estatus)
      //{

      //   __throw(::exception::exception(estatus));

      //}


      INFO(".1");

      return true;

      return estatus;

   }


   void session::term_thread()
   {

      try
      {

         term_session();

      }
      catch (...)
      {

      }

      try
      {

         process_term();

      }
      catch(...)
      {

      }

      ::thread::term_thread();

   }


   ::e_status session::process_init()
   {

      INFO("apex::session::process_init");

      //auto estatus = ::apex::context::initialize_context();

      //if (!estatus)
      //{

         //return estatus;

      //}

      auto estatus = __compose_new(m_ptextcontext);

      if (!estatus)
      {

         INFO("acme::str_context Failed to Allocate!!");

         return estatus;

      }

      INFO("acme::str_context Succeeded to Allocate!!");

      INFO("apex::session::process_init success");

      return ::success;

   }


   ::e_status session::init_session()
   {

      auto estatus = init1();

      if (!estatus)
      {

         output_debug_string("\nFailed to init1 the session (::apex::session or ::apex::session derived)");

         return estatus;

      }

      estatus = init2();

      if (!estatus)
      {

         return estatus;

      }

      estatus = init();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void session::term_session()
   {

      try
      {

         term2();

      }
      catch (...)
      {

      }

      try
      {

         term1();

      }
      catch (...)
      {

      }

      try
      {

         term();

      }
      catch (...)
      {

      }



   }


   void session::on_message_erase_application(::message::message* pmessage)
   {

      auto papplication = pmessage->m_lparam.cast <::application>();

      erase_application(papplication);

   }


   void session::term2()
   {

   }


   void session::term1()
   {

   }


   void session::process_term()
   {

      auto psystem = get_system()->m_papexsystem;

      psystem->post_message(e_message_erase_session, m_iEdge);

   }


   bool session::on_get_task_name(string& strTaskName)
   {

      auto psystem = get_system()->m_papexsystem;

      if (psystem->is_console_app())
      {

         return false;

      }

      return ::apex::context::on_get_task_name(strTaskName);

   }


   void session::on_request(::create * pcreate)
   {

      auto psystem = get_system()->m_papexsystem;

      if (pcreate->m_ecommand == command_protocol)
      {

         m_papplicationCurrent->do_request(pcreate);

         return;

      }

      TRACE("::apex::session::on_request(__pointer(::create)) " + string(type_name()));

      INFO("::apex::session::on_request(__pointer(::create)) %s ", __c_str(THIS_FRIENDLY_NAME()));

      string strAppId = pcreate->m_strAppId;

      if (strAppId.has_char())
      {

         INFO("m_strAppId = " + pcreate->m_strAppId);

         auto papp = start_application(pcreate->m_strAppId, pcreate, m_strLocale, m_strSchema);

         if (!papp)
         {

            destroy();

         }

         return;

      }

      INFO("m_strAppId Is Empty!!");

      string strApp = pcreate->m_pcommandline->m_strApp;

      if (strApp == "app/sphere/userstack")
      {

         start_application("app/sphere/userstack", pcreate, m_strLocale, m_strSchema);

      }

      m_varCurrentViewFile = pcreate->m_pcommandline->m_varFile;

      //string strApp;

      //if ((pcreate->m_pcommandline->m_varQuery["app"].array_get_count() > 1
      //      || pcreate->m_pcommandline->m_varQuery["show_platform"] == 1 || m_varTopicQuery["show_platform"] == 1)
      //      && (!(bool)pcreate->m_pcommandline->m_varQuery.has_property("client_only") && !(bool)has_property("client_only"))
      //      && (!pcreate->m_pcommandline->m_varQuery.has_property("client_only") && !has_property("client_only")))
      //{
      //   m_bShowPlatform = true;
      //}

      bool bCreate = true;

      if (pcreate->m_pcommandline->m_strApp.is_empty())
      {

         if (pcreate->has_file())
         {
            
            if (!open_by_file_extension(pcreate))
            {
               
               if (m_papplicationCurrent != nullptr)
               {
                  
                  m_papplicationCurrent->request(pcreate);

               }

            }

         }
         else if (m_bShowPlatform)
         {
            //create_bergedge(pcreate);
            //if(get_document() != nullptr && get_document()->get_typed_view < ::bergedge::impact >() != nullptr)
            //{
            //   __pointer(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::impact >()->get_parent_frame());
            //   if(pframe != nullptr)
            //   {
            //      pframe->display(e_display_normal);
            //      pframe->InitialFramePosition();
            //   }
            //}
         }
         if (pcreate->m_pcommandline->m_varQuery["app"].array_get_count() <= 0)
         {
            bCreate = false;
         }
      }
      if (bCreate)
      {
         if (pcreate->m_pcommandline->m_strApp == "bergedge")
         {
            if (pcreate->m_pcommandline->m_varQuery.has_property("session_start"))
            {
               strApp = pcreate->m_pcommandline->m_varQuery["session_start"];
            }
            else
            {
               strApp = "bergedge";
            }
         }
         else
         {
            strApp = pcreate->m_pcommandline->m_strApp;
         }


         if (pcreate->m_pcommandline->m_varQuery["app"].stra().find_first_ci(strApp) < 0)
         {

            pcreate->m_pcommandline->m_varQuery["app"].stra().insert_at(0, strApp);

         }

         for (i32 i = 0; i < pcreate->m_pcommandline->m_varQuery["app"].stra().get_count(); i++)
         {

            strApp = pcreate->m_pcommandline->m_varQuery["app"].stra()[i];

            if (strApp.is_empty() || strApp == "bergedge")
            {

               return;

            }

            if (strApp == "session")
            {

               continue;

            }

            ::application * papp = application_get(strApp, true, true, pcreate);

            if (papp == nullptr)
            {

               if(psystem->has_property("install")
                     || psystem->has_property("uninstall"))
               {

                  psystem->destroy();

               }
               else
               {

                  //output_error_message("Could not create requested application: \"" + strApp + "\"");
                  output_debug_string("Could not create requested application: \"" + strApp + "\"");

                  ::count c = psystem->payload("app").array_get_count();

                  if (c == 1 && psystem->payload("app").at(0) == strApp)
                  {

                     psystem->destroy();

                  }

               }

               return;

            }

            pcreate->m_pcommandline->m_eventReady.ResetEvent();

            if (strApp != "bergedge")
            {

               if(!papp->on_start_application())
               {

                  TRACE("One or more errors occurred during on_start_application execution.");

               }

               //if (psystem->is_true("install"))
               if (is_true("install"))
               {

                  papp->do_install();

                  psystem->destroy();

               }
               else
               {

                  if (!papp->is_system() && !papp->is_session())
                  {

                     psystem->merge_accumulated_on_open_file(pcreate);

                  }

                  papp->request(pcreate);

               }

               m_papplicationCurrent = papp;

            }

         }

      }

   }


   //__pointer(::user::menu_interaction) session::create_menu_button(::user::style_pointer & pstyle,::user::menu_item * pitem)
   //{

   //   __throw(error_interface_only);

   //   return nullptr;

   //}


   bool session::open_by_file_extension(const ::string & pszPathName, ::create * pcreate)
   {

      auto pcreateNew = __create_new < ::create >();

      pcreateNew->m_pcommandline->m_varFile = pszPathName;

      pcreateNew->m_puserprimitiveParent = pcreate->m_puserprimitiveParent;

      return open_by_file_extension(pcreateNew);

      //return get_application()->platform_open_by_file_extension(m_iEdge, pszPathName, pcreate);

   }


   bool session::open_by_file_extension(::create * pcreate)
   {

      //return get_application()->platform_open_by_file_extension(m_iEdge, pcc);

      string strId;

      string strOriginalPathName(pcreate->m_pcommandline->m_varFile);

      ::file::path strPathName(strOriginalPathName);

      strsize iFind = strPathName.find("?");

      if (iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if (::str::ends_ci(strPathName, ".ca2"))
      {

      }

      auto psystem = m_psystem;

      auto purl = psystem->url();

      string strProtocol = purl->get_protocol(strPathName);

      if (strProtocol == "app")
      {

         strId = purl->get_server(strPathName);

         string str = purl->get_object(strPathName);

         ::str::begins_eat(str, "/");

         pcreate->m_pcommandline->m_varFile = str;

      }
      else
      {

         string strExtension = strPathName.final_extension();

         string_array straApp;

         __throw(todo, "filehandler");

         //psystem->filehandler().get_extension_app(straApp, strExtension);

         //if (straApp.get_count() == 1)
         //{

         //   strId = straApp[0];

         //}
         //else
         //{

         //   strId = "app/sphere/default_file_handler";

         //}

      }

      ::application* papp = application_get(strId, true, true, pcreate);

      if (papp == nullptr)
      {

         return false;

      }

      papp->do_request(pcreate);

      return true;

   }


   void session::on_instantiate_application(::application* papp)
   {

      papp->m_papexsession = this;
      papp->m_papexsystem = m_papexsystem;
      papp->m_pacmenode = m_pacmenode;
      papp->m_papexnode = m_papexnode;

   }


   //::application * session::application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::create * pcreate)
   //{

   //   __pointer(::application) papp;

   //   if (m_applicationa.lookup(pszAppId, papp))
   //   {

   //      return papp;

   //   }
   //   else
   //   {

   //      if (!bCreate)
   //      {

   //         return nullptr;

   //      }

   //      papp = nullptr;

   //      try
   //      {

   //         papp = create_application(pszAppId, bSynch, pcreate);

   //      }
   //      catch (const ::exception::exception & e)
   //      {

   //         // apex::session, axis::session and ::base::session, could get more specialized handling in apex::application (apex::system)
   //         // Thank you Mummi (em Santos, cuidando do Lucinho e ajudando um monte a Carô e o Lúcio e Eu 2019-01-15) !! Thank you God!! <3tbs

   //         handle_exception(e);

   //         //if (!get_system()->on_run_exception(esp))
   //         //{

   //         //   if (!App(this).on_run_exception(esp))
   //         //   {

   //         //      papp = nullptr;

   //         //   }

   //         //}

   //         //papp = nullptr;

   //      }
   //      catch (...)
   //      {

   //         //papp = nullptr;

   //      }

   //      if (!papp)
   //      {

   //         return nullptr;

   //      }

   //      app_add(papp);

   //      return papp;

   //   }

   //}


   bool session::is_licensed(const ::string & pszAppId, bool bInteractive)
   {

      if (has_property("install"))
      {

         return true;

      }

      if (has_property("uninstall"))
      {

         return true;

      }

      return false;

   }


   bool session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
   {

      throw 0;

      return false;

      //return account()->get_auth(pszForm, strUsername, strPassword);

   }


   bool session::is_key_pressed(::user::enum_key ekey)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::enum_key, bool >;

      }

      bool bPressed = false;

      if (ekey == ::user::e_key_shift)
      {

         m_pmapKeyPressed->lookup(::user::e_key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_shift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_command)
      {
         m_pmapKeyPressed->lookup(::user::e_key_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_command, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_control)
      {
         m_pmapKeyPressed->lookup(::user::e_key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_control, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_alt)
      {
         m_pmapKeyPressed->lookup(::user::e_key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_alt, bPressed);
         if (bPressed)
            goto ret;
      }
      else
      {

         m_pmapKeyPressed->lookup(ekey, bPressed);

      }

ret:

      return bPressed;

   }


   void session::set_key_pressed(::user::enum_key ekey, bool bPressed)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::enum_key, bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }


   ::e_status session::init1()
   {

      auto estatus = initialize_context();

      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose_new(m_pfs);

      if (!estatus)
      {

         output_debug_string("\nFailed to __compose_new(m_pfs)");

         m_result.add(estatus);

         return false;

      }

      // __throw(todo("interaction"));
      //if (psystem->m_bUser)
      //{

      //   bool bCreateSessionWindow = defer_create_session_frame_window();

      //   if (!bCreateSessionWindow)
      //   {

      //      WARN("Could not create session window");

      //   }

      //}

      //estatus = __compose_new(m_puserpresence);

      //if (!estatus)
      //{

      //   m_result.add(estatus);

      //   TRACE("Failed to create new User Presence");

      //   return false;

      //}

      if (!m_pifs)
      {

         estatus = __compose(m_pifs, __new(ifs("")));

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create ifs");

         }

      }

      if (!m_premotefs)
      {

         estatus = __compose(m_premotefs, __new(::fs::remote_native("")));

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create remotefs");

         }

      }

      //if (!m_pftpfs)
      //{

      //   auto pftpfs = __new(ftpfs);

      //   auto estatus = pftpfs->initialize_ftpfs(this, "");

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create ftpfs");

      //   }

      //   __compose(m_pftpfs, pftpfs);

      //}

      if (!m_pfsdata)
      {

         auto pset = __create_new<::fs::set>();

         auto plink = __create_new < ::fs::link>();

         plink->fill_os_user();

         pset->m_spafsdata.add(plink.m_p);

         pset->m_spafsdata.add(__create_new < ::fs::native>().m_p);

         estatus = __compose(m_pfsdata, pset);

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create fsdata");

         }


      }

      INFO(".2");


      return true;

   }


   ::e_status session::defer_initialize_host_window(const RECTANGLE_I32 * lpcrect)
   {

      return ::success;

   }


   ::e_status session::init2()
   {

      ::e_status estatus;

      INFO("apex::session::init2 .1");

      auto psystem = get_system()->m_papexsystem;

      if (psystem->m_bUser)
      {

         //if (!m_paccount)
         //{

         //   estatus = __compose_new(m_paccount);

         //   if (!estatus)
         //   {

         //      FATAL("apex::session::init2 Failed to create account department");

         //      return false;

         //   }

         //}

         //if (!m_paccount->init_instance())
         //{

         //   return false;

         //}


      }

      //initialize_bergedge_application_interface();

      //SetRegistryKey("ca2core");

      if (!InitializeLocalDataCentral())
      {

         //output_error_message("Could not initialize Local data central");

         output_debug_string("Could not initialize Local data central");

         return false;

      }

      return true;

   }


   ::e_status session::init()
   {

      ::e_status estatus = ::success;

      __pointer(::fs::set) pfsset = m_pfsdata;

      if (m_bIfs)
      {

         if (m_pfsdata.is_null())
         {

            __compose(m_pfsdata, __new(::fs::set));

         }

         pfsset = m_pfsdata;

         if (pfsset.is_null())
         {

            pfsset->m_spafsdata.add_unique(m_pifs);

            pfsset->m_spafsdata.add_unique(m_premotefs);

         }

         ::file::listing patha;

         m_pfsdata->root_ones(patha);

      }

      return estatus;

   }


   void session::term()
   {

      try
      {

         ::acme::del(m_pmapKeyPressed);

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

   }


   ::u32 session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}


   //bool session::on_create_frame_window()
   //{

   //   return true;

   //}


//   void session::translate_os_key_message(::user::key * pkey)
//   {
//
////      psession->keyboard().translate_os_key_message(pkey);
//
//   }


   void session::pre_translate_message(::message::message * pmessage)
   {

      if (::is_set(m_papplicationCurrent))
      {

         m_papplicationCurrent->pre_translate_message(pmessage);

      }

   }


   // ::user::style* session::get_user_style() const
   // {

   //    return m_puserstyle;

   // }


} // namespace apex








#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace apex
{






   //::e_status session::initialize(::object * pobject)
   //{

   //   auto estatus = ::apex::session::initialize(pobject);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   return estatus;

   //}


   //void session::install_message_routing(::channel* pchannel)
   //{

   //   ::thread::install_message_routing(pchannel);

   ////   //apex::application::install_message_routing(pchannel);
   ////   apex::session::install_message_routing(pchannel);

   //}


   void session::_001OnFileNew()
   {

   }


   void session::launch_app(const ::string & psz)
   {

      __UNREFERENCED_PARAMETER(psz);

   }


   void session::install_app(const ::string & psz)
   {

      __UNREFERENCED_PARAMETER(psz);

   }


   void session::do_request(::create* pcreate)
   {

      request(pcreate);

   }




   //void session::request_topic_file(::payload& varQuery)
   //{

   //   auto psession = get_session();

   //   request_file(psession->m_varTopicFile, varQuery);

   //}


   //void session::request_topic_file()
   //{

   //   auto psession = get_session();

   //   request_file(psession->m_varTopicFile);

   //}


   __pointer(::application) session::get_current_application()
   {

      auto psession = get_session();

      return psession->m_papplicationCurrent;

   }

   bool session::is_remote_session()
   {


      return m_pcontext->m_papexcontext->os().is_remote_session();


   }


   //bool session::is_mouse_button_pressed(::user::enum_mouse emouse)
   //{

   //   if (emouse == ::user::e_mouse_left_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_left_button);
   //   }
   //   else if (emouse == ::user::e_mouse_right_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_right_button);
   //   }
   //   else if (emouse == ::user::e_mouse_middle_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_middle_button);
   //   }
   //   else
   //   {
   //      __throw(::exception::exception("not expected enum_mouse value"));
   //   }


   //}





//
//   bool session::open_file(::filemanager::data* pdata, ::file::item_array& itema)
//   {
//
//      __UNREFERENCED_PARAMETER(pdata);
//
//      if (itema.get_size() > 0)
//      {
//
//         return true;
//
//      }
//
//      return false;
//
//   }








   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = new nature::database(this);

      //if(m_pdatabase == nullptr)
      //{
      //   TRACE("VmpLightApp::init_instance failed to instatiate LightDB\n");
      //   return false;
      //}

      //if(!m_pdatabase->Initialize())
      //{
      //   TRACE("VmpLightApp::init_instance failed to initialize LightDB\n");
      //   return false;
      //}

      return true;

   }


   //void session::check_topic_file_change()
   //{

   //   auto psession = get_session();

   //   if (psession->m_varCurrentViewFile != psession->m_varTopicFile && !psession->m_varTopicFile.is_empty())
   //   {

   //      psession->m_varCurrentViewFile = psession->m_varTopicFile;

   //      request_topic_file();

   //   }

   //}


   //::user::place_holder_ptra session::get_place_holder(__pointer(::user::frame_window) pmainframe, ::create * pcreate)
   //{

   //   __UNREFERENCED_PARAMETER(pcreate);

   //   ::user::place_holder_ptra holderptra;


   //   ::application & app = App(pmainframe->get_application());

   //   string strAppName = app.m_strAppName;

   //   //if(get_document()->get_typed_view < ::bergedge::pane_view >() != nullptr)
   //   //{

   //   //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_current_tab_by_id("app:" + strAppName);

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName)));

   //   //}
   //   //else
   //   //{

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::impact >());

   //   //}

   //   return holderptra;

   //}

   //bool session::place(::user::main_frame* pmainframe, ::create* pcreate)
   //{

   //   //get_place_holder(pmainframe, pcreate).hold(pmainframe);

   //   return true;

   //}





   void session::set_app_title(const ::string & pszAppId, const ::string & pszTitle)
   {

      __pointer(::application) papp;

      if (m_applicationa.lookup(pszAppId, papp) && papp)
      {

         //__pointer(::bergedge::pane_view) ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

         //if(ppaneview != nullptr)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

         //   if(ppane != nullptr)
         //   {

         //      ppane->m_istrTitleEx = pszTitle;

         //      ppaneview->on_layout(::draw2d::graphics_pointer & pgraphics);

         //   }

         //}

      }

   }



   __pointer(::apex::session) session::get_session()
   {

      return this;

   }



   //   bool session::is_serviceable() const
   //   {
   //
   //
   ////      return ::session::application::is_serviceable();
   //      return false;
   //
   //
   //   }


      //bool session::on_uninstall()
      //{


      //   bool bOk1 = true;
      //   bool bOk2 = true;

      //   try
      //   {

      //      bOk1 = ::apex::session::on_uninstall();

      //   }
      //   catch(...)
      //   {
      //      bOk1 = false;
      //   }




      //   return bOk1 && bOk2;


      //}


      //::e_status session::os_native_bergedge_start()
      //{

      //   if (!::application::os_native_bergedge_start())
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      //service_base * session::allocate_new_service()
      //{


      //   return ::application::allocate_new_service();


      //}





   //::draw2d::cursor* session::get_default_cursor()
   //{

   //   return pdraw2d->get_cursor(m_ecursorDefault);

   //}


   ::e_status     session::main()
   {

      //return ::apex::session::main();
      return ::thread::main();

   }


   //::apex::session * session::query_bergedge()
   //{

   //   ::apex::session * psession = nullptr;

   //   if(psystem->m_pbergedgemap == nullptr)
   //      return nullptr;

   //   if(!psystem->m_pbergedgemap->lookup(0,psession))
   //   {
   //      return nullptr;
   //   }

   //   return psession;

   //}


   //void session::on_user_logon(::account::user* puser)
   //{

   //   ::apex::session::on_user_logon(puser);

   //}


//   void session::interactive_credentials(::account::credentials* pcredentials)
//   {
//
//
//      //if (!USER)
//      //{
//
//      //   //   //pcredentials->m_puser->m_estatusAuthentication = ::error_credentials_non_interactive;
//
//      //   return;
//
//      //}
//      pcredentials->m_estatus = error_failed;
//
//      manual_reset_event ev;
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      //if (m_pmainpane != nullptr && m_pmainpane == nullptr)
//      //{
//
//      //   try
//      //   {
//
//      //      m_pmainpane->interactive_credentials(pcredentials);
//
//      //   }
//      //   catch (...)
//      //   {
//
//      //   }
//
//      //}
//
//      if (pcredentials->m_estatus == ::success_credentials ||
//         ::failed(pcredentials->m_estatus, STATUS_RANGE_AUTHENTICATION))
//      {
//
//         return;
//
//      }
//
//#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
//      //attach_thread_input_to_main_thread(false);
//#endif
//
//      ::apex::session::interactive_credentials(pcredentials);
//
//      if (pcredentials->m_estatus == ::success_credentials)
//      {
//
//         return;
//
//      }
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      auto puser = pcredentials->m_puser;
//
//      //auto pdialog = ::__create_new<::account::dialog>();
//
//      //pdialog->initialize_account_dialog(pcredentials);
//
//      //pdialog->get_credentials();
//
//      //pdialog->DestroyWindow();
//
//
//   }


   //void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32& rectangle, ::draw2d::brush_pointer& brushText)
   //{

   //   string_array& straTitle = pane.m_straTitle;

   //   pgraphics->set(brushText);

   //   if (straTitle.get_count() <= 1)
   //   {

   //      pgraphics->_DrawText(pane.get_title(), recte_bottom_left, e_draw_text_no_prefix);

   //   }
   //   else
   //   {

   //      ::rectangle_i32 rectText(rectangle);


   //      ::write_text::font_pointer font;
   //      font = pgraphics->get_current_font();
   //      size_i32 sSep = ptab->get_data()->m_sizeSep;
   //      ::rectangle_i32 rectEmp;
   //      for (index i = 0; i < straTitle.get_size(); i++)
   //      {
   //         string str = straTitle[i];
   //         size_i32 s = pane.m_sizeaText[i];
   //         rectText.right = rectText.left + s.cx;
   //         pgraphics->_DrawText(str, rectTexte_bottom_left, e_draw_text_no_prefix);
   //         rectText.left += s.cx;
   //         if (i < straTitle.get_upper_bound())
   //         {
   //            rectText.right = rectText.left + sSep.cx;
   //            rectEmp = rectText;
   //            rectEmp.deflate(1, 1);
   //            ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
   //            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //            if (ptab->m_itemHover == (::user::enum_element)(::user::e_element_split + i))
   //            {
   //               pgraphics->fill_rectangle(rectEmp, argb(128, 150, 184, 255));
   //               pgraphics->set(ptab->get_data()->m_brushTextHover);
   //            }
   //            else
   //            {
   //               //pgraphics->fill_rectangle(rectEmp,argb(128,208,223,233));
   //               pgraphics->set(ptab->get_data()->m_brushText);
   //            }
   //            pgraphics->set(ptab->m_pfontTab);
   //            pgraphics->set_alpha_mode(emode);
   //            pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectText, e_align_center, e_draw_text_no_prefix);
   //            rectText.left += sSep.cx;
   //            pgraphics->set(font);
   //            pgraphics->set(brushText);
   //         }
   //      }

   //   }

   //}


   string_array session::get_user_wallpaper()
   {

      string_array stra;

      //string_array straSource = psession->userex()->get_wallpaper();

      //for (string str : straSource)
      //{

      //   if (::str::begins_eat_ci(str, "file://"))
      //   {

      //      str = purl->url_decode(str);

      //   }

      //   stra.add(str.c_str());

      //}

      return stra;

   }


   ::user::primitive* session::get_user_interaction_host()
   {

      return m_puserprimitiveHost;

   }


   ::user::primitive * session::get_host_primitive()
   {

      return m_puserprimitiveHost;
   
   }


   void session::frame_pre_translate_message(::message::message* pmessage)
   {

//      if (pmessage->m_id == WM_GETTEXT
//         || pmessage->m_id == WM_GETTEXTLENGTH
//         )
//      {
//
//         pmessage->m_uiMessageFlags |= 3; // message considered pre translated
//         pmessage->m_uiMessageFlags |= 16384; //  by early optmization
//
//         return;
//
//      }
      //else if (pmessage->m_id == e_message_mouse_move)
      //{

      //   pmessage->m_uiMessageFlags |= 0; // message considered pre translated
      //   pmessage->m_uiMessageFlags |= 16384; //  by early optmization

      //   return;

      //}

      //try
      //{

      //   __pointer(::user::interaction) pinteraction;

      //   while (get_frame(pinteraction))
      //   {

      //      try
      //      {

      //         if (pinteraction != nullptr)
      //         {

      //            pinteraction->pre_translate_message(pmessage);

      //            if (pmessage->m_bRet)
      //               return;

      //         }

      //      }
      //      catch (const ::exception::exception & e)
      //      {

      //         if (e.is < ::exit_exception>())
      //         {

      //            __rethrow(::move(e));

      //         }

      //      }
      //      catch (...)
      //      {
      //      }

      //   }

      //}
      //catch (const ::exception::exception & e)
      //{

      //   if (e.is < ::exit_exception>())
      //   {

      //      __rethrow(::move(e));

      //   }

      //}
      //catch (...)
      //{

      //   pmessage->m_bRet = true;

      //}

   }



   ::e_status session::destroy()
   {

      ::application_container::m_applicationa.erase_all();

      ::apex::context::destroy();

      return success;

   }

   
   __namespace_session_factory(session);


} // namespace apex



