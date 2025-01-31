// Create on 2021-03-20 23:59 <3ThomasBS_
#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


class CLASS_DECL_ACME acme_dir :
   virtual public ::matter
{
public:


   ::PLATFORM_NAMESPACE::acme_dir *          m_pplatformdir;
   acme_file *                               m_pacmefile;
   acme_path *                               m_pacmepath;

   ::file::path                              m_pathInstallFolder;
   ::file::path                              m_pathModuleFolder;
   

   acme_dir();
   ~acme_dir() override;


   ::e_status initialize(::object * pobject) override;

   
   virtual ::file::path module_folder();


   virtual ::file::path app(string strPlatform, string strConfiguration);
   virtual ::file::path app_app_admin(string strPlatform, string strConfiguration);
   virtual ::file::path app_app_nest(string strPlatform, string strConfiguration);
   virtual ::file::path app_app(string strPlatform, string strConfiguration);
   virtual ::file::path vcredist(string strPlatform, string strConfiguration);
   virtual ::file::path install_log(string strPlatform, string strConfiguration);


   virtual ::file::path install();
   virtual ::file::path default_install();
   virtual ::file::path beforeca2();
   virtual ::file::path module();
   virtual ::file::path relative(::file::path path);
   virtual ::file::path app_relative();
   virtual ::file::path appdata(); // appdata
   virtual ::file::path archive();
   virtual ::file::path tool();
   virtual ::file::path public_system();
   virtual ::file::path system();
   virtual ::file::path config();
   virtual ::file::path local();
   virtual ::file::path sensitive();
   virtual ::file::path localconfig(); // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
   virtual ::file::path ca2roaming(); // writable root (non-bin, non-exe)
   virtual ::file::path ca2appdata(); // writable root (non-bin, non-exe)
   virtual ::file::path roaming();
   virtual ::file::path program_data();
   virtual ::file::path public_root(); // writable common root (non-bin, non-exe)
   virtual ::file::path bookmark();
   virtual ::file::path home();
   virtual ::file::path pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode);
   virtual ::file::path program_files_x86();
   virtual ::file::path program_files();
   //virtual ::file::path program_data();
   virtual ::file::path stage(string strAppId, string strPlatform, string strConfiguration);
   virtual ::file::path sys_temp();
   virtual ::string dir_root();
   //virtual ::file::path home();
   //virtual ::file::path program_data();
   //virtual ::file::path roaming();
   virtual ::file::path get_memory_map_base_folder_path();
   //virtual ::file::path ca2appdata();
   //virtual ::file::path ca2roaming();
   //virtual ::file::path localconfig();
   virtual string system_short_name();


   //::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   //virtual ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   virtual ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   virtual ::file::path inplace_matter_install(string strAppId, string strPlatform, string strConfiguration);


   virtual void set_path_install_folder(const ::string & pszPath);

   //virtual ::file::path pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode);

   virtual ::file::path machine_event_file_path();

   virtual ::file::path user_appdata_local();
   //virtual ::file::path tool();

   virtual bool is(const char * path1);
   virtual bool _is(const char * path1);
   // From acme/filesystem/file/dir.cpp by camilo 
   // From acme_posix/acme_dir.h
// on 2021-08-09 03:20 BRT
// <3ThomasBorregaardS�rensen!!


   //namespace posix
   //{


   //   class CLASS_DECL_ACME_POSIX acme_dir :
   //      virtual public ::acme_dir
   //   {

   //   public:

   //      acme_dir();
   //      ~acme_dir();

         //virtual string name(const char * path1);


         //virtual ::file::path base_module();

         virtual ::e_status create(const char * path);
         virtual ::e_status _create(const char * path);
         virtual ::e_status create_directory(const char * path);
         virtual ::e_status _create_directory(const char * path);


         virtual void rls(::file::patha & stra, const char * psz);
         virtual void rls_dir(::file::patha & stra, const char * psz);

         virtual void ls(::file::patha & stra, const char * psz);
         virtual void ls_dir(::file::patha & stra, const char * psz);

         virtual void ls_file(::file::patha & stra, const char * psz);

         virtual int make_path(const char * psz);


         /*namespace dir
         {*/


            //virtual string name(const char * pszPath);
            //virtual bool mk(const ::string & strPath);
            //virtual bool _mk(const  char * path); // makes a directory path (all intermediates too)
            //virtual bool is(const char * path);
            //virtual bool _is(const char * path);
            //virtual bool mk(const  char * path); // makes a directory path (all intermediates too)
            //virtual bool mkdir(const  char * path); // only creates if parent dir already exists
            //virtual void ls(::file::patha & patha, const char * path);
            //virtual void ls_dir(::file::patha & patha, const char * path);
            //virtual void ls_file(::file::patha & patha, const char * path);
            //virtual void rls(::file::patha & patha, const char * path);
            //virtual void rls_dir(::file::patha & patha, const char * path);


            //virtual::file::path ca2_module();
            //virtual::file::path base_module();


         //} // namespace dir

            virtual string get_current_directory();



};