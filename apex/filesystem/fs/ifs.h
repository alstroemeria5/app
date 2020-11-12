#pragma once


// ifs - implementation of file system interface - file.ca2.cc

class CLASS_DECL_APEX ifs :
   virtual public ::fs::data
{
public:


   string         m_strRoot;
   bool           m_bInitialized;
   string         m_strServer;

   class CLASS_DECL_APEX dir_listing :
      public ::file::listing
   {
   public:

      u32          m_uiTimeout;
      u32          m_uiLsTimeout;

   };

   filepathmap(dir_listing)     m_map;

   //file_path_map < u32 >    m_mapdirTimeout;
   //file_path_map < u32 >    m_mapfileTimeout;
   //file_path_map < u32 >    m_maplsTimeout;
   //filepathmap(::file::patha)    m_mapdirFile;
   //filepathmap(::file::patha)    m_mapdirFolder;
   //filepathmap(::file::patha)    m_mapdirFileName;
   //filepathmap(::file::patha)    m_mapdirFolderName;
   //filepathmap(i64_array)      m_mapdirFileSize;
   //filepathmap(i64_array)      m_mapdirFolderSize; // by now, always store item count?
   //filepathmap(bool_array)       m_mapdirFileDir;
   //filepathmap(bool_array)       m_mapdirFolderDir; // by now, always store item count?


   ifs( const char * pszRoot);


   virtual bool has_subdir(const ::file::path & pszPath) override;
   virtual bool fast_has_subdir(const ::file::path  & pszPath) override;
   virtual ::file::listing & ls(::file::listing & listing) override;
   virtual int is_dir(const ::file::path & path) override;
   virtual ::file::listing & root_ones(::file::listing & listing) override;

   //virtual string file_name(const char * pszPath);
   //virtual string dir_path(const char * psz1, const char * psz2);

   virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc) override;

   virtual file_result get_file(const ::file::path & path, ::u32 nOpenFlags) override;

   virtual bool file_exists(const ::file::path & pszPath) override;
   virtual var file_length(const ::file::path & pszPath) override;

   virtual void defer_initialize();

   virtual bool is_zero_latency(const ::file::path & psz) override;

};

