#pragma once



namespace uwp
{

   /////////////////////////////////////////////////////////////////////////////
   // STDIO file implementation


   class stdio_file :
      virtual public ::file::text_file
   {
   public:


      FILE* m_pFile;    // stdio FILE
      // m_hFile from apex class is _fileno(m_pStream)



      stdio_file();


      virtual void write_string(const char * lpsz);
      virtual char * read_string(char * lpsz, ::u32 nMax);
      virtual bool read_string(string & rString);

      virtual ~stdio_file();
      void dump(dump_context & dumpcontext) const;
      virtual filesize get_position() const;
      virtual ::status::result open(const ::file::path & lpszFileName,::u32 nOpenFlags);
      virtual memsize read(void * lpBuf, memsize nCount);
      virtual void write(const void * lpBuf, memsize nCount);
      virtual filesize seek(filesize lOff, ::file::e_seek nFrom);
      virtual void Abort();
      virtual void Flush();
      virtual void close();
      virtual filesize get_length() const;

      // Unsupported APIs
      virtual __pointer(::file::file) Duplicate() const;
      virtual void LockRange(filesize dwPos, filesize dwCount);
      virtual void UnlockRange(filesize dwPos, filesize dwCount);


   };


} // namespace uwp




