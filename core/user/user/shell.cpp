#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif
#include "core/user/user/shell.h"
#include "core/node/_node.h"
#include "acme/compress/zip/_.h"
#include "acme/compress/gz.h"
#include "acme/primitive/primitive/atomic.h"


#if defined(RASPBIAN)
#define PLATFORM_NAMESPACE linux
#endif


namespace user
{


   shell::image_key::image_key()
      {

         m_iIcon = 0x80000000;

      }


      shell::image_key::image_key(const image_key & key)
      {

         //m_oswindow = key.m_oswindow;
         m_cr = key.m_cr;
         m_strPath = key.m_strPath;
         m_iIcon = key.m_iIcon;
         m_eattribute = key.m_eattribute;
         m_eicon = key.m_eicon;
         m_strExtension = key.m_strExtension;
         m_strShellThemePrefix = key.m_strShellThemePrefix;

      }


      shell::image_key::image_key(const string & strPath, const string & strShellThemePrefix, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
      {

         if (colorref_get_a_value(crBk) != 255)
         {

            crBk = 0;

         }

         set_path(strPath);

         m_strShellThemePrefix = strShellThemePrefix;

         m_eattribute = eattribute;

         m_eicon = eicon;

         m_iIcon = 0;

         //m_oswindow = m_pimage->get_safe_handle();

         m_cr = crBk;

      }


      shell::image_key::~image_key()
      {


      }


      void shell::image_key::set_path(const string & strPath, bool bSetExtension)
      {

         m_strPath = strPath;

         if (bSetExtension)
         {

            set_extension(strPath);

         }
         else
         {

            m_strExtension.Empty();

         }


      }


      void shell::image_key::set_extension(const string & strPath)
      {

         strsize iFind1 = strPath.rfind('/');

         strsize iFind2 = strPath.rfind('\\');

         strsize iFind = max(iFind1, iFind2) + 1;

         strsize iDot = strPath.find('.', iFind);

         if (iDot < 0)
         {

            m_strExtension.Empty();

         }
         else
         {

            m_strExtension = strPath.Mid(iDot + 1);

         }

      }


      shell::shell()
      {

         m_bPendingUpdate = false;
         m_bMax = false;
         m_iActiveThreadCount = 0;
         m_iMaxThreadCount = 1;

         m_pevNewImageKey = __new(manual_reset_event);

         m_pevNewImageKey->m_eobject += e_object_alertable_wait;

         m_iaSize.add(16);
         m_iaSize.add(24);
         m_iaSize.add(32);
         m_iaSize.add(48);
         m_iaSize.add(256);

         m_imagemap.InitHashTable(16383);

      }


      shell::~shell()
      {
         
      }


      ::estatus shell::initialize(::layered * pobjectContext)
      {

         if (m_bInitialized)
         {

            return ::success;

         }

         auto estatus = ::object::initialize(pobjectContext);

         if (!estatus)
         {

            return estatus;

         }

         sync_lock sl(mutex());

         add_thread();

         do_initialize();

         m_bPendingUpdate = true;
         //on_update_sizes_interest();

         m_bInitialized = true;

         return success;

      }


      void shell::add_thread()
      {

         sync_lock sl(mutex());

         auto pthread  = __new(thread(this));

         add_composite(pthread);

      }


      shell::thread::thread(shell * pshell)
      {

         initialize(pshell);

         __refer(m_pshell, pshell);

         begin();

      }


      shell::thread::~thread()
      {

      }


      ::estatus shell::thread::init_thread()
      {

         m_bSimpleMessageLoop = false;

         if (!::thread::init_thread())
         {

            return false;

         }

#ifdef WINDOWS
         defer_co_initialize_ex(false);
#endif

         return true;

      }

      bool shell::reserve_image(const image_key & imagekey, i32 & iImage)
      {

         sync_lock sl(mutex());

         if (contains_image(imagekey, iImage))
         {

            return false;

         }

         iImage = _reserve_image(imagekey);

         return true;

      }


      int shell::_reserve_image(const image_key & key)
      {

         sync_lock sl(mutex());

         int iImage = -1;

         for (auto iSize : m_iaSize)
         {

            iImage = m_pil[iSize]->reserve_image(iImage);

            iImage = m_pilHover[iSize]->reserve_image(iImage);

         }

         m_imagemap.set_at(key, iImage);

         return iImage;

      }


      bool shell::contains_image(const image_key & imagekey, i32 & iImage)
      {

         sync_lock sl(mutex());

         if (m_imagemap.lookup(imagekey, iImage))
         {

            return true;

         }

         return false;

      }


      void shell::add_size_interest(int_array iaSize)
      {

         sync_lock sl(mutex());

         auto cAddedCount = m_iaSize.add_unique(iaSize);

         if (cAddedCount > 0)
         {

            m_iaSize.sort();

            m_bPendingUpdate = true;

         }

      }


      void shell::set_size_interest(int_array iaSize)
      {

         sync_lock sl(mutex());

         iaSize.sort();

         if(m_iaSize != iaSize)
         {

            m_iaSize = iaSize;

            m_bPendingUpdate = true;

         }

      }


      void shell::on_update_sizes_interest()
      {

         sync_lock sl(mutex());

         m_imagemap.remove_all();

         m_iaSize.sort();

         if (m_iaSize.isEmpty())
         {

            m_iaSize.add(48);

         }

         for (auto iSize : m_iaSize)
         {

            if (m_pil[iSize].is_null())
            {

               m_pil[iSize] = __new(::image_list);
               m_pil[iSize]->create(iSize, iSize, 0, 10, 10);

            }
            else
            {

               m_pil[iSize]->remove_all();

            }

            if (m_pilHover[iSize].is_null())
            {

               m_pilHover[iSize] = __new(::image_list);
               m_pilHover[iSize]->create(iSize, iSize, 0, 10, 10);

            }
            else
            {

               m_pilHover[iSize]->remove_all();

            }

         }

         on_add_default_file_image();

         m_bPendingUpdate = false;

      }


      void shell::get_scheduled_image_key(image_key& imagekey)
      {


         while (thread_get_run())
         {

            {

               m_pevNewImageKey->wait();

               sync_lock sl(mutex());

               if (m_imagekeySchedule.has_elements())
               {

                  imagekey = m_imagekeySchedule[0];

                  m_imagekeySchedule.remove_at(0);

                  return;

               }
               else
               {

                  m_pevNewImageKey->ResetEvent();

               }

            }

         }


      }


      void shell::on_add_default_file_image()
      {

         create_file_icon_image(::dir::bookmark(), file_attribute_directory, icon_normal, "matter://quickaccess.ico");

         create_file_icon_image(::dir::bookmark(), file_attribute_directory, icon_open, "matter://quickaccess.ico");

      }


      void shell::do_initialize()
      {


      }


      ::image_list * shell::GetImageList(int iSize)
      {

         sync_lock sl(mutex());

         if (m_bPendingUpdate)
         {

            on_update_sizes_interest();

         }

         index i = 0;

         for (; i < m_iaSize.get_size(); i++)
         {

            if (iSize <= m_iaSize[i])
            {

               break;

            }

         }

         if (i >= m_iaSize.get_size())
         {

            i = m_iaSize.get_upper_bound();

         }

         if (i < 0)
         {

            return nullptr;

         }

         return m_pil[m_iaSize[i]];

      }


      ::image_list * shell::GetImageListHover(int iSize)
      {

         sync_lock sl(mutex());

         if (m_bPendingUpdate)
         {

            on_update_sizes_interest();

         }

         index i = 0;

         for (; i < m_iaSize.get_size(); i++)
         {

            if (iSize <= m_iaSize[i])
            {

               break;

            }

         }

         if (i >= m_iaSize.get_size())
         {

            i = m_iaSize.get_upper_bound();

         }

         if (i < 0)
         {

            return nullptr;

         }

         return m_pilHover[m_iaSize[i]];

      }


      shell::e_folder shell::get_folder_type(::object * pobject, const widechar * pcszPath)
      {

         string str(pcszPath);

         return get_folder_type(pobject, str);

      }


      shell::e_folder shell::get_folder_type(::object * pobject, const char * pcszPath)
      {

         wstring wstr(pcszPath);

         return get_folder_type(pobject, wstr);

      }


      i32 shell::get_file_image(const string & strPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
      {

         sync_lock sl(mutex());

         image_key imagekey(strPath, m_strShellThemePrefix, eattribute, eicon, crBk);

         return get_file_image(imagekey);

      }


      i32 shell::get_file_extension_image(const string & strExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
      {

         //i32 iImage = 0x80000000;

         if (colorref_get_a_value(crBk) != 255)
         {

            crBk = 0;

         }

         image_key imagekey;

         imagekey.m_strPath = "foo";

         imagekey.m_strShellThemePrefix = m_strShellThemePrefix;

         imagekey.m_strExtension = strExtension;

         imagekey.m_eattribute = eattribute;

         imagekey.m_eicon = eicon;

         imagekey.m_iIcon = 0;

         imagekey.m_cr = crBk;

         return get_file_image(imagekey);

      }


      i32 shell::get_file_image(const image_key & imagekey)
      {

         sync_lock sl(mutex());

         if (m_bPendingUpdate)
         {

            on_update_sizes_interest();

         }

         i32 iImage;

         if (m_imagemap.lookup(imagekey, iImage))
         {

            if (iImage == 0x80000001)
            {

               iImage = 0x80000000;

            }

            return iImage;

         }

         image_key imagekeyStore(imagekey);

         m_imagemap.set_at(imagekeyStore, 0x80000001); // mark as "calculating image"

         return _get_file_image(imagekey);

      }


      i32 shell::_get_file_image(const image_key & imagekey)
      {

         {

            sync_lock sl(mutex());

            m_imagekeySchedule.add(imagekey);

            m_pevNewImageKey->SetEvent();

         }

         //if (m_threadptra.get_count() < m_iMaxThreadCount)
         //{

         //   bool bMax = m_iActiveThreadCount >= m_threadptra.get_count();

         //   if (bMax)
         //   {

         //      if (!m_bMax)
         //      {

         //         m_bMax = true;

         //         m_tickLastMax = ::get_tick();

         //      }
         //      else if (m_tickLastMax.elapsed() > 50)
         //      {

         //         add_thread();

         //      }

         //   }
         //   else
         //   {

         //      m_bMax = false;

         //   }

         //}

         //index iThread = m_iThread;

         //iThread = iThread % m_threadptra.get_size();

         //i32 iImage = m_threadptra[iThread]->_get_file_image(oswindow, imagekey);

         //iThread++;

         //m_iThread = iThread;

         //return iImage;
         return 0x80000000;

      }


      ::estatus shell::thread::run()
      {

         while(thread_get_run())
         {

            image_key imagekey;

            m_pshell->get_scheduled_image_key(imagekey);

            if (!thread_get_run())
            {

               break;

            }

            try
            {

               int iImage = m_pshell->impl_get_file_image(imagekey);

               sync_lock sl(m_pshell->mutex());

               if (iImage & 0x80000000)
               {

                  m_pshell->m_imagemap.remove_key(imagekey);

               }
               else
               {

                  m_pshell->m_imagemap.set_at(imagekey, iImage);

               }

            }
            catch (...)
            {

            }

         }

         return ::success;

      }


      i32 shell::add_icon_path(::file::path path, color32_t crBk, int iImage)
      {

         return -1;

      }


      i32 shell::create_file_icon_image(const string & strPath, e_file_attribute eattribute, e_icon eicon, string strIcoLocation)
      {

         image_key imagekey(strPath, m_strShellThemePrefix, eattribute, eicon);

         i32 iImage;

         if (reserve_image(imagekey, iImage))
         {

            ::file::path path = strIcoLocation;

            add_icon_path(path, imagekey.m_cr, iImage);

         }

         return iImage;

      }



   //int shell::add_hover_image(int iSize, int iImage, color32_t crBk)
   //{

   //   sync_lock sl(m_pilHover[iSize]->mutex());

   //   if (crBk == 0)
   //   {

   //      return m_pilHover[iSize]->pred_add_image([&](auto pimage)
   //         {

   //            System.imaging().color_blend(pimage, RGB(255, 255, 240), 64);

   //         }
   //      , m_pil[iSize], iImage, iImage);

   //   }
   //   else
   //   {

   //      iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);

   //      {

   //         ::image_pointer pimage(this);
   //         pimage->create({ iSize, iSize });
   //         pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

   //         m_pilHover[iSize]->draw(pimage->get_graphics(), iImage, nullptr, 0);
   //         m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
   //         m_pilHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
   //         m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

   //      }

   //      {
   //         ::image_pointer d = m_pilHover[iSize]->m_pimage;
   //         size s = m_pil[iSize]->m_pimage->get_size();
   //         ::image_pointer pimage(this);
   //         pimage->create(d->size());
   //         pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
   //         pimage->get_graphics()->draw(nullptr, d->size(), d->get_graphics());
   //         pimage->get_graphics()->fill_solid_rect_dim(0, 0, d->size().cx, d->size().cy, ARGB(123, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk)));
   //         m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
   //         m_pil[iSize]->m_pimage->g()->draw(d->rect(), pimage->get_graphics());
   //         m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

   //      }

   //      return iImage;

   //   }


   //}

   int shell::add_hover_image(int iSize, int iImage, color32_t crBk)
   {

      sync_lock sl(m_pilHover[iSize]->mutex());

      if (crBk == 0)
      {

         return m_pilHover[iSize]->pred_add_image([&](auto pimage)
            {

               System.imaging().color_blend(pimage, RGB(255, 255, 240), 64);

            }
         , m_pil[iSize], iImage, iImage);

      }
      else
      {

         iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);

         {

            ::image_pointer pimage(this);
            pimage->create({ iSize, iSize });
            pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
            pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

            m_pilHover[iSize]->draw(pgraphics, iImage, nullptr, 0);
            m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
            m_pilHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
            m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

         }

         {
            ::image_pointer d = m_pilHover[iSize]->m_pimage;
            //size s = m_pil[iSize]->m_pimage->get_size();
            ::image_pointer pimage(this);
            pimage->create(d->size());
            pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
            pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
            pimage->get_graphics()->draw(nullptr, d->size(), d->get_graphics());
            pimage->get_graphics()->fill_solid_rect_dim(0, 0, d->size().cx, d->size().cy, ARGB(123, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk)));
            m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
            m_pil[iSize]->m_pimage->g()->draw(d->rect(), pimage->get_graphics());
            m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

         }

         return iImage;

      }


   }


   ::estatus shell::thread::finish(::context_object * pcontextobject)
   {

      return ::thread::finish(pcontextobject);

   }


   ::estatus shell::finish(::context_object * pcontextobject)
   {

      ::object::finish(pcontextobject);

      //task_remove_all();

      return ::success;

   }



} // namespace user


//#ifdef WINDOWS_DESKTOP
//#include "aura/user/user/shell_windows.h"
//#elif defined(MACOS)
//#include "aura/user/user/shell_macos.h"
//#elif defined(APPLE_IOS)
//#include "aura/user/user/shell_ios.h"
//#elif defined(LINUX)
//#include "aura/user/user/shell_linux.h"
//#elif defined(ANDROID)
//#include "aura/user/user/shell_android.h"
//#elif defined(_UWP)
//#include "aura/user/user/shell_uwp.h"
//#else
//#error "Implement here"
//#endif





