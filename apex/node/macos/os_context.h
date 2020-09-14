#pragma once


namespace macos
{


   class CLASS_DECL_APEX os_context :
      virtual public ::os_context
   {
   public:


      os_context();
      virtual ~os_context();


      virtual string get_command_line() override;

      virtual bool reboot() override;

      virtual bool shutdown(bool bPowerOff) override;

      virtual void terminate_processes_by_title(const char * pszName) override;
      //virtual string get_module_path(HMODULE hmodule);

      virtual bool get_pid_by_path(const char * pszName, DWORD & dwPid) override;

      virtual bool get_pid_by_title(const char * pszName, DWORD & dwPid) override;

      virtual void get_all_processes(u32_array & dwa) override;
      virtual ::file::path get_process_path(DWORD dwPid) override;

      virtual var connection_settings_get_auto_detect() override;
      virtual var connection_settings_get_auto_config_url() override;


      virtual bool local_machine_set_run(const char * pszKey, const char * pszCommand);
      virtual bool local_machine_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool defer_register_ca2_plugin_for_mozilla() override;


      virtual bool file_extension_get_open_with_list_keys(string_array & straKey, const char * pszExtension) override;

      virtual bool file_extension_get_open_with_list_commands(string_array & straCommand, const char * pszExtension) override;

      virtual bool file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath) override;

      virtual bool file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam) override;

      virtual bool file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

      virtual bool open_in_ie(const char * pcsz);

      virtual ::estatus create_service() override;

      virtual ::estatus remove_service() override;

      virtual ::estatus start_service() override;

      virtual ::estatus stop_service() override;

      virtual bool resolve_link(::file::path & pathTarget, const string & strSource, string * pstrFolder = nullptr, string * pstrParams = nullptr, ::user::primitive * puiMessageParentOptional = nullptr) override;

      void raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags);

      virtual bool is_remote_session() override;

      virtual void post_to_all_threads(UINT message, WPARAM wParam, LPARAM lParam);

      virtual int get_pid() override;

      virtual bool initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch) override;

      virtual bool get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      virtual bool set_default_browser() override;

      virtual ::file::path get_app_path(const string & strApp) override;

      virtual void on_process_command(::create * pcommand) override;

      virtual bool file_open(::file::path path, string strParams = "", string strFolder = "") override;
      
      virtual ::estatus link_open(string strUrl) override;

      virtual void set_file_status(const char * lpszFileName, const ::file::file_status& status) override;

      virtual bool browse_folder(::user::interaction * puiOwner, property_set &set) override;
      virtual bool browse_file_open(::user::interaction * puiOwner, property_set &set) override;

   };



} // namespace macos



