﻿#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA icon :
      virtual public ::object
   {
   public:

      
      void *                        m_picon;
      map < ::size, void * >        m_iconmap;
      bool                          m_bAutoDelete;
      string                        m_strAppTrayIcon;
      ::size                        m_size;
      __pointer(size_image)         m_pimagemap;


      icon();
      virtual ~icon();


      virtual ::e_status     initialize(::layered * pobjectContext) override;


      operator void *();
#ifdef WINDOWS
      operator HICON();
      virtual HICON get_os_data();
#else
      virtual void * get_os_data();
#endif


      virtual ::e_status     attach_os_data(void * picon, bool bTakeOwnership = true);

#ifdef WINDOWS

      virtual ::e_status     attach_os_data(HICON hicon, bool bTakeOwnership = true);

#endif


      bool load_file(string strPath);
      bool load_matter(string strPath);
      bool load_app_tray_icon(string strPath);


      ::size get_size();

      virtual void on_update_icon();

      image_pointer get_image(const ::size & size);
      const image_pointer get_image(const ::size & size) const;

      inline ::draw2d::graphics * g(const ::size & sizeHint) { return get_image(sizeHint)->g(); }
      inline ::sized origin() const { return ::sized(); }
      inline ::sized size(const ::size & sizeHint) { return get_image(sizeHint)->size(sizeHint); }

         
   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public i32_map < icon * >
   {
   public:

   };


} // namespace draw2d


#ifdef WINDOWS_DESKTOP

CLASS_DECL_AURA HICON load_icon(::object * pobject, string_array & straMatter, string strIcon, int cx, int cy);

#endif

