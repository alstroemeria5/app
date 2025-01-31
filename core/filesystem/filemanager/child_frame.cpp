#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif



namespace filemanager
{


   child_frame::child_frame()
   {

   }


   child_frame::~child_frame()
   {

   }


   void child_frame::install_message_routing(::channel * pchannel)
   {

      simple_child_frame::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_language, pchannel, this, &child_frame::_001OnAppLanguage);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &child_frame::on_message_show_window);
      MESSAGE_LINK(e_message_create, pchannel, this, &child_frame::on_message_create);

   }


   bool child_frame::on_create_bars()
   {

      //auto pdocument = get_active_document();

      //return pdocument->on_create_bars(this);

      return ::simple_frame_window::on_create_bars();

   }


   bool child_frame::DestroyBars()
   {

      return true;

   }


   void child_frame::route_command_message(::message::command * pcommand)
   {

      simple_child_frame::route_command_message(pcommand);

   }


   __pointer(document) child_frame::filemanager_document()
   {

      return  get_active_document();

   }


   void child_frame::on_message_create(::message::message * pmessage)
   {

      if (pmessage->m_bRet)
      {

         return;

      }

//#ifdef WINDOWS_DESKTOP
//
//      m_hMenuDefault = nullptr;
//
//#endif


   }


   void child_frame::_001OnAppLanguage(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   ::file::item_array child_frame::get_selected_items()
   {

      __pointer(file_list) plist = get_active_view();

      if (plist.is_null())
      {

         return ::file::item_array();

      }

      return plist->get_selected_items();

   }


   void child_frame::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


} // namespace filemanager



