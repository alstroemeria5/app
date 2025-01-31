#pragma once


namespace user
{

   
   class tree;


} // namespace user


namespace filemanager
{


   class CLASS_DECL_CORE data :
      virtual public ::data::data
   {
   public:


      // most changed parameters
      /// ::aura::application *   m_pappOnBehalfOf; use this data app; (through * pobjec parameter)
      /// a filemanager doesn't actually act in behalf of app but of user!
      /// user->>> session
      /// the only current app things are matter resource assets
      /// fix this concept if there are app exclusive file systems.... but,
      /// other file systems can be included in more incluse fs::data
      /// (or just exclusive file systems at fs::data (ftp only file system?)
      __pointer(::create) m_pcreate;
      ::file::path m_filepath;
      bool m_bMakeVisible;
      bool m_bTransparentBackground;
      ::user::interaction * m_puserinteractionParent;
      __pointer(::fs::data)       m_pfsdata;
      callback *                 m_pcallback;
      //bool bMakeVisible = true, bool bTransparentBackground = false, __pointer(::user::interaction) puiParent = nullptr, ::fs::data * pfsdata = nullptr, __pointer(data) pdata = nullptr, callback * pcallback = nullptr
      ::user::multiple_document_template * m_pdocumenttemplate;
      ::write_text::font_pointer                   m_pfont;
      ::user::document *                  m_pdocumentTopic;
      ::filemanager::document *                    m_pdocument;
      string m_strTitle;
      //    callback   *                        m_pfilemanager;
//      callback *                          m_pcallback;
//      bool                                m_bTransparentBackground;
      ::database::key                     m_datakey;
      ::user::place_holder *              m_pholderFileList;
      ::user::tree *                      m_ptreeFileTreeMerge;
      bool                                m_bSetBergedgeTopicFile;
      property_set                        m_setToolbar;
      bool                                m_bEnableRecursiveFolderSelectionList;
      id                                  m_id;
      string                              m_strCopy;
      ::file::path                        m_pathDefault;
      string                              m_strMenuBar;
      string                              m_strDialogBar;
      string                              m_strPopup;
      string                              m_strXmlPopup;
      string                              m_strXmlPopupSubstId;

      string                              m_strFolderPopup;

      id                                  m_idExpandBox;
      id                                  m_idCollapseBox;

      ::database::key                     m_dataidStatic;


      __pointer(file_list_callback)       m_pfilelistcallback;

      string                              m_strLevelUp;
      i32                                 m_iIconSize;
      bool                                m_bListText;
      bool                                m_bListSelection;
      bool                                m_bFileSize;
      bool                                m_bPassBk;
      bool                                m_bIconView;


      data();
      virtual ~data();


      virtual void assert_valid() const override;
      virtual void dump(dump_context& dumpcontext) const override;


      bool is_topic();


      virtual ::e_status initialize_filemanager_data(::object * pobject);

      
      bool open(::application * pappOnBehalfOf = nullptr, ::file::path path = "", const ::action_context & action_context = ::e_source_system);
      
      
      //::filemanager::document * open(::file::path path = "");
      //virtual ::filemanager::document * document();
      

      virtual bool do_prompt_file_name(::payload & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);


      //virtual void defer_update_data_key() override;


      virtual ::id get_local_machine_id();
      virtual string get_last_browse_path(::object * pobject, const ::string & pszDefault = nullptr);
      virtual ::e_status set_last_browse_path(::object * pobject, const ::file::path & path);


   };


} // namespace filemanager




