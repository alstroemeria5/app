#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif

#include "aura/update.h"
#include "aura/user/menu_command.h"


namespace filemanager
{


   file_list::file_list()
   {

      m_bStatic = false;
      m_bFileSize = false;
      m_bShow = false;
      m_bHoverSelect2 = true;

   }


   file_list::~file_list()
   {

   }


   void file_list::install_message_routing(::channel * pchannel)
   {

      impact::install_message_routing(pchannel);

      ::user::form_list::install_message_routing(pchannel);

      ::userfs::list::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_hscroll, pchannel, this, &file_list::_001OnHScroll);
      MESSAGE_LINK(e_message_vscroll, pchannel, this, &file_list::_001OnVScroll);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &file_list::on_message_context_menu);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &file_list::on_message_show_window);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &file_list::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &file_list::_001OnKillFocus);

      connect_command_probe("edit_copy", &file_list::_001OnUpdateEditCopy);
      connect_command("edit_copy", &file_list::_001OnEditCopy);
      connect_command_probe("trash_that_is_not_trash", &file_list::_001OnUpdateTrashThatIsNotTrash);
      connect_command("trash_that_is_not_trash", &file_list::_001OnTrashThatIsNotTrash);
      connect_command_probe("open_with", &file_list::_001OnUpdateOpenWith);
      //connect_command_probe("spafy", &file_list::_001OnUpdateSpafy);
      //connect_command("spafy", &file_list::_001OnSpafy);
      //connect_command_probe("spafy2", &file_list::_001OnUpdateSpafy2);
      //connect_command("spafy2", &file_list::_001OnSpafy2);
      connect_command_probe("file_rename", &file_list::_001OnUpdateFileRename);
      connect_command("file_rename", &file_list::_001OnFileRename);
      connect_command("file_open", &file_list::_001OnFileOpen);

   }


   void file_list::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void file_list::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }



   bool file_list::on_click(const ::user::item & item)
   {

      if (item.m_iSubItem == m_iNameSubItem ||
         ((m_eview == impact_list || m_eview == impact_report)
         && item.m_iSubItem < 0))
      {

         if (!_017OpenSelected(true, ::e_source_user))
         {

            index iStrict = item.item_index();

            auto pitem = fs_list_item(iStrict);

            _017OpenItem(pitem, true, ::e_source_user);

         }

      }

      return ::user::list::on_click(item);

   }


   bool file_list::on_right_click(const ::user::item & item)
   {

      if(item.is_set())
      {

         _017OpenContextMenuSelected(::e_source_user);

      }
      else
      {

         _017OpenContextMenu(::e_source_user);

      }

      return true;

   }


   void file_list::RenameFile(i32 iLine, string &wstrNameNew, const ::action_context & context)
   {

      synchronous_lock synchronouslock(fs_list()->mutex());

      ::file::path filepath = fs_list_item(iLine)->m_filepathFinal;

      ::file::path filepathNew = filepath.folder() / wstrNameNew;

      auto pcontext = get_context();

      pcontext->m_papexcontext->file().rename(filepathNew, filepath);

      browse_sync(context);

   }


   void file_list::on_message_context_menu(::message::message * pmessage)
   {

      __pointer(::message::mouse) pcontextmenu(pmessage);

      synchronous_lock synchronouslock(fs_list()->mutex());

      index iItem;

      auto point = pcontextmenu->m_point;

      ::user::list::screen_to_client(point);

      if (_001HitTest_(point, iItem))
      {

         if (fs_list_item((::index) iItem)->IsFolder())
         {

            _017OpenContextMenuFolder(fs_list_item((::index) iItem), ::e_source_user);

         }
         else
         {

            auto pcontext = m_pcontext;
            
            auto psession = pcontext->m_pcoresession;
            
            auto puser = psession->m_puser->m_pcoreuser;

            puser->track_popup_xml_menu(this, filemanager_data()->m_strXmlPopup, 0, pcontextmenu->m_point);

         }

      }
      else
      {

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         puser->track_popup_xml_menu(this, filemanager_data()->m_strPopup, 0, pcontextmenu->m_point);

      }

   }


   bool file_list::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP



#endif

      return ::user::impact::pre_create_window(pusersystem);

   }


   //void file_list::FileSize()
   //{

   //   if (m_bFileSize)
   //   {

   //      return;

   //   }

   //   m_bFileSize = true;

   //   db_server * pcentral = dynamic_cast <db_server *> (psystem->m_psimpledb->db());

   //   if (pcentral == nullptr)
   //   {

   //      return;

   //   }

   //   DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;

   //   i32 i;

   //   while (::task_get_run())
   //   {

   //      i = 0;

   //      while (i < fs_list()->m_itema.get_count() || is_window_visible())
   //      {

   //         i64 i64Size;

   //         bool bPendingSize;

   //         single_lock lock(get_application()->mutex());

   //         if (!lock.lock(millis(2000)))
   //         {

   //            break;

   //         }

   //         if (i >= fs_list()->m_itema.get_count())
   //         {

   //            i = 0;

   //         }

   //         bPendingSize = false;

   //         try
   //         {

   //            pset->get_fs_size(i64Size, fs_list_item(i)->get_user_path(), bPendingSize);

   //         }
   //         catch (...)
   //         {

   //         }

   //         lock.unlock();

   //         i++;

   //         sleep(23_ms);

   //      }

   //      sleep(100_ms);

   //   }

   //   m_bFileSize = false;

   //}


   void file_list::_001OnTimer(::timer * ptimer)
   {

      ::userfs::list::_001OnTimer(ptimer);

      if (ptimer->m_uEvent == 888888)
      {

         auto psession = get_session();

         if (filemanager_data()->m_bSetBergedgeTopicFile)
         {

            auto patha = get_selected_user_path();

            if (patha.is_empty())
            {

               psession->m_varTopicFile.unset();

            }
            else if (patha.get_count() == 1)
            {

               psession->m_varTopicFile = patha[0];

            }
            else
            {

               psession->m_varTopicFile = (const string_array &) patha;

            }

         }
         else
         {
            KillTimer(888888);
         }
      }

   }


   void file_list::route_command_message(::message::command * pcommand)
   {

      auto itema = get_selected_items();

      if (filemanager_document()->HandleDefaultFileManagerItemCmdMsg(pcommand, itema))
      {

         pcommand->m_bRet = true;

         return;

      }

      ::user::impact::route_command_message(pcommand);

   }


   void file_list::_001OnShellCommand(::message::message * pmessage)
   {
      __pointer(::user::message) pcommand(pmessage);
      m_contextmenu.OnCommand(pcommand->GetId());
   }

   void file_list::_001OnFileManagerItemCommand(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      ::file::item_array itema;

      index iItemRange, iItem;

      ::user::range range;

      _001GetSelection(range);

      for (iItemRange = 0;
            iItemRange < range.get_item_count();
            iItemRange++)
      {

         auto & itemrange = range.ItemAt(iItemRange);

         for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            itema.add(fs_list_item(iItem));

         }

      }

      filemanager_document()->on_file_manager_item_command(__str(pcommand->m_id), itema);

   }


   void file_list::_001OnFileManagerItemUpdate(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      synchronous_lock synchronouslock(fs_list()->mutex());

      ::file::item_array itema;

      index iItemRange, iItem;

      ::user::range range;

      _001GetSelection(range);

      for (iItemRange = 0; iItemRange < range.get_item_count(); iItemRange++)
      {

         auto & itemrange = range.ItemAt(iItemRange);

         for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            itema.add(fs_list_item(iItem));

         }

      }

      filemanager_document()->on_file_manager_item_update(pcommand, itema);

      pmessage->m_bRet = true;

   }


   void file_list::_017OpenContextMenuFolder(__pointer(::file::item)  item, const ::action_context & context)
   {

      string_array straCommand;

      string_array straCommandTitle;

      filemanager_document()->on_file_manager_open_context_menu_folder(item, straCommand, straCommandTitle, context);

      if (straCommand.get_size() > 0)
      {

         auto pmenu = __create_new < ::user::menu >();

         if (pmenu->create_menu(straCommand, straCommandTitle))
         {

            pmenu->track_popup_menu(get_parent_frame());

         }

      }

   }

   void file_list::_017OpenContextMenuFile(const ::file::item_array & itema, const ::action_context & context)
   {

      filemanager_document()->on_file_manager_open_context_menu_file(itema, context);

   }


   void file_list::_017OpenContextMenu(const ::action_context & context)
   {

      filemanager_document()->on_file_manager_open_context_menu(context);

   }


   void file_list::_017OpenFolder(__pointer(::file::item) pitem, const ::action_context & context)
   {

      filemanager_document()->browse(pitem, context);

   }


   void file_list::_017OpenFile(const ::file::item_array & itema, const ::action_context & context)
   {

      filemanager_document()->on_file_manager_open(itema, context);

   }


   void file_list::_001OnFileRename(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      ::user::range range;

      _001GetSelection(range);

      if (range.get_item_count() == 1 && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound())
      {

         index iEditItem = range.ItemAt(0).get_lower_bound();

         ::user::interaction * pinteraction = _001GetControl(iEditItem, m_iNameSubItem);

         _001PlaceControl(pinteraction, iEditItem);

      }

   }


   void file_list::_001OnFileOpen(::message::message* pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      _017OpenSelected(true, ::e_source_user);

   }


   void file_list::_001OnUpdateFileRename(::message::message * pmessage)
   {
      //      __pointer(::message::command) pcommand(pmessage);
      //    pcommand->enable(_001GetSelectedItemCount() == 1);
      //  pmessage->m_bRet = true;

      __pointer(::message::command) pcommand(pmessage);
      ::user::range range;
      _001GetSelection(range);
      pcommand->enable(
      range.get_item_count() == 1
      && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound());
      pmessage->m_bRet = true;

   }


   void file_list::_001OnUpdateEditCopy(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      ::user::range range;

      _001GetSelection(range);

      pcommand->enable(range.get_item_count() > 0);

      pmessage->m_bRet = true;

   }


   void file_list::_001OnEditCopy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto patha = get_selected_final_path();

      auto pwindow = window();

      auto pcopydesk = pwindow->copydesk();

      pcopydesk->set_filea(patha, ::user::copydesk::op_copy);

      pmessage->m_bRet = true;

   }


   void file_list::_001OnUpdateTrashThatIsNotTrash(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      ::user::range range;

      _001GetSelection(range);

      pcommand->enable(range.get_item_count() > 0);

      pmessage->m_bRet = true;

   }


   void file_list::_001OnTrashThatIsNotTrash(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto patha = get_selected_final_path();

      auto pcontext = get_context();

      pcontext->m_papexcontext->file().trash_that_is_not_trash(patha);

      _001Refresh();

      pmessage->m_bRet = true;

   }


   void file_list::_001OnUpdateOpenWith(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      __pointer(::user::menu_command) pmenucommandui(pcommand);

      if (pmenucommandui)
      {

         auto pitema = pmenucommandui->m_pitema;

         auto pmenu = pitema->element_at(pmenucommandui->m_iIndex)->m_pmenu;

         pitema->erase_at(pcommand->m_iIndex);

         index iStartIndex = pcommand->m_iIndex;

         index iIndex = iStartIndex;

         auto patha = get_selected_final_path();

         ::file::path strPath = patha.first();

         string strExt = strPath.final_extension();

         string_array stra;

         auto pcontext = get_context();

         pcontext->m_papexcontext->os().file_extension_get_open_with_list_keys(stra, strExt);

         m_straOpenWith = stra;

         ::count iCount = stra.get_size();

         string str;

         for (i32 i = 0; i < iCount; i++)
         {

            auto pmenuitem = __create_new < ::user::menu_item > ();

            pmenuitem->m_id = "open with" + stra[i];

            if (pmenuitem->m_puserinteraction != nullptr)
            {

               pmenuitem->m_puserinteraction->set_window_text(stra[i]);

            }

            pmenuitem->m_iLevel = pitema->m_pitemParent != nullptr ? pitema->m_pitemParent->m_iLevel + 1 : 0;

            pmenuitem->m_pmenu = pmenu;

            pitema->insert_at(iIndex, pmenuitem);

            iIndex++;

         }

         pcommand->m_iIndex = iStartIndex;

         pcommand->m_iCount += iCount - 1;

         index iNewIndex = iStartIndex + iCount - 1;

         pmenucommandui->m_iIndex = iNewIndex;

         pmenu->set_need_layout();

      }

      pmessage->m_bRet = true;

   }


   void file_list::on_command_probe(::message::command * pcommand)
   {

      i32 iPos = -1;

      for (i32 i = 0; i < m_straOpenWith.get_size(); i++)
      {

         string strId = "open with" + m_straOpenWith[i];

         if (pcommand->m_id.m_psz == strId)
         {

            iPos = i;

            break;

         }

      }

      if (iPos >= 0)
      {

         pcommand->enable(true);

         pcommand->m_bRet = true;

         return;

      }

      ::user::impact::on_command_probe(pcommand);

   }


   void file_list::on_command(::message::command * pcommand)
   {

      if (pcommand->m_id == "1000")
      {

         //      _017OpenSelected(true, ::e_source_user);

         pcommand->m_bRet = true;

         return;

      }

      i32 iPos = -1;

      for (i32 i = 0; i < m_straOpenWith.get_size(); i++)
      {

         string strId = "open with" + m_straOpenWith[i];

         if (pcommand->m_id.m_psz == strId)
         {

            iPos = i;

            break;

         }

      }

      if (iPos >= 0)
      {

         auto patha = get_selected_final_path();

         ::file::path pathUser = patha.first();

         auto pcontext = get_context();

         pcontext->m_papexcontext->os().file_open(pathUser);

         pcommand->m_bRet = true;

         return;

      }

      ::user::impact::on_command(pcommand);

   }


   //void file_list::_001OnUpdateSpafy(::message::message * pmessage)
   //{
   //   __pointer(::message::command) pcommand(pmessage);
   //   ::user::range range;
   //   _001GetSelection(range);
   //   pcommand->enable(range.get_item_count() > 0);
   //   pmessage->m_bRet = true;
   //}


   //void file_list::_001OnSpafy(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //   auto itema = get_selected_items();

   //   string_array stra;

   //   ::file::listing straSub;

   //   string strFileList;
   //   string strFileCheck;
   //   for (i32 i = 0; i < itema.get_size(); i++)
   //   {

   //      if (pcontext->m_papexcontext->dir().is(itema[i]->m_filepathFinal) && strcmp(itema[i]->m_filepathFinal.name(), ".svn"))
   //      {

   //         straSub.rls(itema[i]->m_filepathFinal);

   //         for (i32 j = 0; j < straSub.get_size(); j++)
   //         {
   //            if (!pcontext->m_papexcontext->dir().is(straSub[j]) && straSub[j].find(".svn") < 0)
   //            {
   //               strFileList += straSub[j] + "\n";
   //               strFileCheck += straSub[j] + ",";
   //               strFileCheck += pcontext->m_papexcontext->file().length(straSub[j]).get_string() + ",";
   //               strFileCheck += pcontext->m_papexcontext->file().md5(straSub[j]) + "\n";
   //            }
   //         }
   //      }
   //      else
   //      {
   //         strFileList += itema[i]->m_filepathUser + "\n";
   //         strFileCheck += itema[i]->m_filepathUser + ",";
   //         strFileCheck += pcontext->m_papexcontext->file().length(itema[i]->m_filepathFinal).get_string() + ",";
   //         strFileCheck += pcontext->m_papexcontext->file().md5(itema[i]->m_filepathFinal) + "\n";
   //      }
   //   }

   //   ::datetime::time time = ::datetime::time::get_current_time();

   //   string strTime;

   //   strTime.Format("%04d-%02d-%02d %02d-%02d",
   //                  time.GetYear(),
   //                  time.GetMonth(),
   //                  time.GetDay(),
   //                  time.GetHour(),
   //                  time.GetMinute());

   //   string strBase = filemanager_item()->m_filepathUser / "spafy_";

   //   string strList = strBase + "list_" + strTime + ".txt";
   //   string strCheck = strBase + "check_" + strTime + ".txt";


   //   pcontext->m_papexcontext->file().put_contents(strList, strFileList);
   //   pcontext->m_papexcontext->file().put_contents(strCheck, strFileCheck);

   //}

   //void file_list::_001OnUpdateSpafy2(::message::message * pmessage)
   //{
   //   __pointer(::message::command) pcommand(pmessage);
   //   pcommand->enable(true);
   //   pmessage->m_bRet = true;
   //}


   //void file_list::_001OnSpafy2(::message::message * pmessage)
   //{

   //   synchronous_lock synchronouslock(fs_list()->mutex());

   //   __pointer(::userfs::list_data) pdata = fs_list();
   //
   //   __UNREFERENCED_PARAMETER(pmessage);
   //
   //   string_array stra;
   //
   //   ::file::listing straSub(get_context());

   //   string strFileList;

   //   string strFileCheck;

   //   for (i32 i = 0; i < pdata->m_itema.get_count(); i++)
   //   {

   //      if (fs_data()->is_dir(pdata->item(i)->m_filepathFinal)
   //            && strcmp(pdata->item(i)->m_filepathFinal.name(), ".svn"))
   //      {

   //         straSub.rls(pdata->item(i)->m_filepathFinal);

   //         for (i32 j = 0; j < straSub.get_size(); j++)
   //         {

   //            string strExtension = straSub[j].extension();

   //            if (!pcontext->m_papexcontext->dir().is(straSub[j])
   //                  && (strExtension == "exe" || strExtension == "dll" || strExtension == "dll.manifest"
   //                      || strExtension == "exe.manifest"))
   //            {

   //               strFileList += straSub[j] + "\n";
   //               strFileCheck += straSub[j] + ",";
   //               strFileCheck += pcontext->m_papexcontext->file().length(straSub[j]).get_string() + ",";
   //               strFileCheck += pcontext->m_papexcontext->file().md5(straSub[j]) + "\n";

   //            }

   //         }
   //      }
   //      else
   //      {

   //         string strExtension = pdata->item(i)->m_filepathUser.extension();

   //         if (strExtension == "exe" || strExtension == "dll" || strExtension == "dll.manifest"
   //               || strExtension == "exe.manifest")
   //         {

   //            strFileList += pdata->item(i)->m_filepathUser + "\n";
   //            strFileCheck += pdata->item(i)->m_filepathUser + ",";
   //            strFileCheck += pcontext->m_papexcontext->file().length(pdata->item(i)->m_filepathFinal).get_string() + ",";
   //            strFileCheck += pcontext->m_papexcontext->file().md5(pdata->item(i)->m_filepathFinal) + "\n";

   //         }

   //      }

   //   }

   //   ::datetime::time time = ::datetime::time::get_current_time();

   //   string strTime;

   //   strTime.Format("%04d-%02d-%02d %02d-%02d",
   //                  time.GetYear(),
   //                  time.GetMonth(),
   //                  time.GetDay(),
   //                  time.GetHour(),
   //                  time.GetMinute());

   //   string strBase = filemanager_item()->m_filepathUser / "spafy_";

   //   string strList = strBase + "list_" + strTime + ".txt";

   //   string strCheck = strBase + "check_" + strTime + ".txt";

   //   pcontext->m_papexcontext->file().put_contents(strList, strFileList);

   //   pcontext->m_papexcontext->file().put_contents(strCheck, strFileCheck);

   //}


   void file_list::_001OnAfterSort()
   {

      data_set_DisplayToStrict();

   }


   __pointer(::fs::data) file_list::fs_data()
   {

      return ::userfs::list::fs_data();

   }


   //void file_list::schedule_file_size(const ::string & psz)
   //{

   //   __UNREFERENCED_PARAMETER(psz);

   //   if (!is_window_visible())
   //   {

   //      return;

   //   }

   //}


   void file_list::on_message_show_window(::message::message * pmessage)
   {

      //__pointer(::message::show_window) pshowwindow(pmessage);

      __UNREFERENCED_PARAMETER(pmessage);

   }


   id file_list::data_get_current_list_layout_id()
   {

      return filemanager_item()->m_filepathUser;

   }


   void file_list::browse_sync(const ::action_context & context)
   {

      if (m_bStatic)
      {

         ::userfs::list_item item;

         string_array stra;

         auto papplication = get_application();

         auto pcontext = get_context();

         papplication->data_get(filemanager_data()->m_dataidStatic, stra);

         synchronous_lock lock(fs_list()->mutex());

         fs_list()->m_itema.erase_all();

         for (i32 i = 0; i < stra.get_size(); i++)
         {

            item.m_flags.clear();

            ::file::path pathItem = stra[i];

            if (pcontext->m_papexcontext->dir().is(pathItem))
            {

               item.m_flags.add(::file::e_flag_folder);

            }

            ::file::path strPath = stra[i];

            string strName = strPath.name();

            item.m_filepathUser = strPath;

            item.m_filepathFinal = pcontext->m_papexcontext->defer_process_path(strPath);

            item.m_strName = strName;

            fs_list()->m_itema.add_fs_item(item);

         }

         _001OnUpdateItemCount();

         return;

      }

      if (filemanager_data()->m_bSetBergedgeTopicFile)
      {

         SetTimer(888888, 230, nullptr);

      }

      string_array straStrictOrder;

//      papplication->data_get(data_get_current_sort_id() + "." +  data_get_current_list_layout_id() + ".straStrictOrder", straStrictOrder);

      index_biunique iaDisplayToStrict;

      __pointer(icon_layout) piconlayout;

      __construct_new(piconlayout);

//      papplication->data_get(data_get_current_sort_id() + "." + data_get_current_list_layout_id(), piconlayout);

      iaDisplayToStrict = piconlayout->m_iaDisplayToStrict;

      index_biunique iaDisplayToStrictNew;

      ::userfs::list_item item;

      string strParent = filemanager_path();

      ::file::path pathParentEx = filemanager_item()->get_user_path();

      pathParentEx = filemanager_path();

      i32 iMaxSize;

      iMaxSize = 1000;

      i32 iSize;

      iSize = 0;

      m_pathaStrictOrder.erase_all();

      _001OnUpdateItemCount();

      auto pcontext = get_context();

      {

         synchronization_object * pm = fs_list()->mutex();

         synchronous_lock lock(pm);

         ::file::listing & listingUser = get_document()->m_listingUser2;

         ::file::listing & listingFinal = get_document()->m_listingFinal2;

         auto cItem = listingUser.get_size();

         fs_list()->m_itema.set_size(cItem);

         m_pathaStrictOrder = listingUser;

         for (i32 i = 0; i < cItem; i++)
         {

            auto & spitem = fs_list()->m_itema[i];

            spitem.create_new(this);

            ::file::path pathFinal = listingFinal[i];

            pathFinal = pcontext->m_papexcontext->defer_process_path(pathFinal);

            pathFinal.m_iDir = listingFinal[i].m_iDir;

            if (pathFinal.m_iDir < 0)
            {

               pathFinal.m_iDir = fs_data()->is_dir(pathFinal) ? 1 : 0;

            }

            if (pathFinal.m_iDir == 1)
            {

               spitem->m_flags.add(::file::e_flag_folder);

            }

            spitem->m_filepathUser = listingUser[i];

            spitem->m_filepathFinal = pathFinal;

            spitem->m_strName = listingUser.name(i);

            //if (spitem->m_strName.contains_ci("aaa."))
            //{

            //   output_debug_string("test filemanager file_list");

            //}

         }

      }

      _001OnUpdateItemCount();

      {

         synchronous_lock lock(fs_list()->mutex());

         if (m_eview == impact_icon)
         {
            /*   // primeiro, todos System arquivos que foram removidos
            // ou seja, que existem no array antigo,
            // mas não existe no novo.
            for(index strictOld = 0; strictOld < straStrictOrder.get_count(); strictOld++)
            {
            string str = straStrictOrder[strictOld];
            index find = m_pathaStrictOrder.find_first(str);
            if(find < 0)
            {
            iaDisplayToStrictNew.erase_b(strictOld);
            }
            }*/
            // segundo, reordena conforme a
            // ordem que a listagem de arquivos fornecida pelo
            // sistema operacional pode ser fornecida.
            for (index strictNew = 0; strictNew < m_pathaStrictOrder.get_count(); strictNew++)
            {
               string str = m_pathaStrictOrder[strictNew];
               index strictOld = straStrictOrder.find_first(str);
               if (strictOld >= 0)
               {
                  index iDisplay = iaDisplayToStrict.get_a(strictOld);
                  iaDisplayToStrictNew.set(iDisplay, strictNew);
               }
            }
            // terceiro, adiciona System novos arquivos nos primeiros espaços
            // vazios
            for (index strictNew = 0; strictNew < m_pathaStrictOrder.get_count(); strictNew++)
            {
               string str = m_pathaStrictOrder[strictNew];
               index strictOld = straStrictOrder.find_first(str);
               if (strictOld < 0)
               {
                  iaDisplayToStrictNew.add_b_in_first_free_a(strictNew);
               }
            }
            m_piconlayout->m_iaDisplayToStrict = iaDisplayToStrictNew;
         }
         else
         {
            fs_list()->m_itema.arrange(::fs::arrange_by_name);
         }

      }

      ///      _001CreateImageList();

      //file_size_add_request(true);
      /*   for(i32 i = 0; i < m_itema.get_item_count(); i++)
      {
      pset->m_table.add_request(item(i)->m_strPath);
      }*/
      //if (m_eview == impact_icon)
      //{
         //papplication->data_set(data_get_current_sort_id() + "." + data_get_current_list_layout_id() + ".straStrictOrder", m_pathaStrictOrder);
         //m_piconlayout->m_iaDisplayToStrict = iaDisplayToStrictNew;
         //data_set_DisplayToStrict();
      //}

      _001ClearSelection();

      queue_graphics_call([this](::draw2d::graphics_pointer & pgraphics)
         {

            set_viewport_offset(pgraphics, 0, 0);

         });

      set_need_layout();

      set_need_redraw();

   }


   void file_list::_001InsertColumns()
   {

      if (filemanager_document() == nullptr)
      {

         return;

      }

      auto pcontext = m_pcontext->m_papexcontext;

      if (filemanager_data()->m_bIconView)
      {

         m_eview = impact_icon;

      }

      i32 iCount = 0;

      file_list_callback * pcallback = filemanager_data()->m_pfilelistcallback;

      if (pcallback != nullptr)
      {

         iCount = pcallback->GetActionButtonCount();

      }

      index i;

      for (i = 0; i < iCount; i++)
      {

         index iControl;

         ::id id = 1000 + i;

         {

            auto pinteraction = __create_new <  user::button > ();
            pinteraction->m_bTransparent = true;
            //pinteraction->set_control_type(user::e_control_type_button);
            //pinteraction->m_type = __type(::user::button);
            pinteraction->m_id = id;
            pinteraction->add_function(user::e_control_function_action);
            iControl = _001AddControl(pinteraction);

         }

         {

            auto pcolumn = new_list_column();

            pcolumn->m_iWidth = 18;
            pcolumn->m_iSubItem = i;
            pcolumn->m_id = id;
            pcolumn->m_bCustomDraw = true;
            pcolumn->m_bEditOnSecondClick = true;
            pcolumn->m_pil = pcallback->GetActionButtonImageList(i);

         }

      }

      if (filemanager_data()->m_bListSelection)
      {

         m_iSelectionSubItem = i;
         m_iIconSubItem = m_iSelectionSubItem;
         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = filemanager_data()->m_iIconSize;
         //pcolumn->m_bIcon                = true;
         pcolumn->m_sizeIcon.cx = filemanager_data()->m_iIconSize;
         pcolumn->m_sizeIcon.cy = filemanager_data()->m_iIconSize;
         //pcolumn->m_iControl = -1;
         pcolumn->m_datakey = "FILE_MANAGER_ID_FILE_NAME";
         pcolumn->m_bEditOnSecondClick = false;

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         pcolumn->m_pil = puser->shell()->GetImageList(filemanager_data()->m_iIconSize);
         pcolumn->m_pilHover = puser->shell()->GetImageListHover(filemanager_data()->m_iIconSize);
         pcolumn->m_iSubItem = m_iSelectionSubItem;
         i++;
      }
      else
      {
         m_iSelectionSubItem = -1;
      }

      bool bRenameEdit = false;

      {

         auto pcolumn = new_list_column();

         if (bRenameEdit)
         {

            auto pinteraction = __create_new <  user::plain_edit > ();
            //pinteraction->set_control_type(user::e_control_type_edit_plain_text);
            pinteraction->m_datakey = "FILE_MANAGER_ID_FILE_NAME";
            //pinteraction->m_id = _vms::FILE_MANAGER_ID_FILE_NAME;
            pinteraction->set_data_type(user::e_control_data_type_string);
            pinteraction->add_function(user::e_control_function_vms_data_edit);
            pinteraction->m_type = __type(::user::plain_edit);
            //pinteraction->m_iSubItem = i;
            pinteraction->m_id = 1000 + i;
            index iControl = _001AddControl(pinteraction);
            pcolumn->m_id = pinteraction->m_id;

         }



         m_iNameSubItem = i;
         m_iIconSubItem = m_iNameSubItem;
         pcolumn->m_iSubItem = m_iNameSubItem;
         if (filemanager_data()->m_bListText)
         {
            m_iNameSubItemText = i;
            pcolumn->m_iWidth = 500;
         }
         else
         {
            m_iNameSubItemText = i;
            pcolumn->m_iWidth = filemanager_data()->m_iIconSize;
         }
         fs_list()->m_iNameSubItemText = m_iNameSubItemText;
         //pcolumn->m_bIcon                = true;
         pcolumn->m_sizeIcon.cx = filemanager_data()->m_iIconSize;
         pcolumn->m_sizeIcon.cy = filemanager_data()->m_iIconSize;
         pcolumn->m_text = pcontext->__text("file:Name");
         pcolumn->m_datakey = "FILE_MANAGER_ID_FILE_NAME";
         pcolumn->m_bEditOnSecondClick = true;
         int iIconSize = filemanager_data()->m_iIconSize;

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         pcolumn->m_pil = puser->shell()->GetImageList(iIconSize);

         pcolumn->m_pilHover = puser->shell()->GetImageListHover(iIconSize);

      }

      i++;

      if (filemanager_data()->m_bFileSize)
      {

         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 100;

         pcolumn->m_iSubItem = i;

         m_iSizeSubItem = i;

         fs_list()->m_iSizeSubItem = m_iSizeSubItem;

         pcolumn->m_text = pcontext->__text("file:Size");

         pcolumn->m_sizeIcon.cx = 0;

         pcolumn->m_sizeIcon.cy = 0;

         pcolumn->m_pilHover = nullptr;

         pcolumn->m_pil = nullptr;


      }

   }


   void file_list::_001GetItemText(::user::mesh_item * pitem)
   {

      if (m_bStatic)
      {

         return ::user::list::_001GetItemText(pitem);

      }

      return ::userfs::list::_001GetItemText(pitem);

   }


   void file_list::_001GetItemImage(::user::mesh_item * pitem)
   {

      return ::userfs::list::_001GetItemImage(pitem);

   }



   //void file_list::_001OnMainPostMessage(::message::message * pmessage)
   //{

   //   __pointer(::user::message) pusermessage(pmessage);

   //   switch (pusermessage->m_wparam)
   //   {
   //   case MessageMainPostCreateImageListItemStepSetRedraw:
   //   {
   //      millis tickNow= ::millis::now();
   //      if (tickNow - m_millisLastRedraw > 784)
   //      {
   //         m_millisLastRedraw = tickNow;
   //         set_need_redraw();
   //      }
   //   }
   //   break;
   //   case MessageMainPostCreateImageListItemRedraw:
   //   {
   //      set_need_redraw();
   //   }
   //   break;
   //   }

   //   pusermessage->set_lresult(0);

   //   pusermessage->m_bRet = true;

   //}


   void file_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::form_list::_001OnDraw(pgraphics);

   }


   //void file_list::TakeAnimationSnapshot()
   //{

   //}


   //void file_list::_017OpenSelected(bool bOpenFile, const ::action_context & context)
   //{

   //   ::file::item_array itema;

   //   index iItemRange, iItem;

   //   ::user::range range;

   //   _001GetSelection(range);

   //   for (iItemRange = 0; iItemRange < range.get_item_count(); iItemRange++)
   //   {

   //      auto & itemrange = range.ItemAt(iItemRange);

   //      for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
   //      {

   //         if (iItem < 0)
   //         {

   //            continue;

   //         }

   //         if (iItem >= _001GetItemCount())
   //         {

   //            continue;

   //         }

   //         index iStrict;

   //         if (m_eview == impact_icon)
   //         {

   //            iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);

   //         }
   //         else
   //         {

   //            iStrict = m_meshlayout.m_iaDisplayToStrict[iItem];

   //         }

   //         __pointer(::userfs::list_item) pitem = fs_list_item(iStrict);

   //         if (pitem->IsFolder())
   //         {

   //            _017OpenFolder(pitem, context) + ::e_source_selection;

   //            break;

   //         }
   //         else
   //         {

   //            itema.add(pitem);

   //         }

   //      }

   //   }

   //   if (bOpenFile && itema.get_size() > 0)
   //   {

   //      _017OpenFile(itema, context) + ::e_source_selection;

   //   }

   //   _001ClearSelection();

   //}


   void file_list::_017OpenContextMenuSelected(const ::action_context & context)
   {

      synchronous_lock synchronouslock(fs_list()->mutex());

      ::file::item_array itema;

      index iItemRange, iItem;

      ::user::range range;

      _001GetSelection(range);

      for (iItemRange = 0; iItemRange < range.get_item_count(); iItemRange++)
      {

         auto & itemrange = range.ItemAt(iItemRange);

         for (iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {

            if (iItem < 0)
            {

               continue;

            }

            if (iItem >= fs_list()->m_itema.get_count())
            {

               continue;

            }

            index iStrict = _001DisplayToStrict(iItem);

            if (fs_list_item(iStrict)->IsFolder())
            {

               _017OpenContextMenuFolder(fs_list_item(iStrict), context);

               break;

            }
            else
            {

               itema.add(fs_list_item(iStrict));

            }

         }

      }

      if (itema.get_size() > 0)
      {
         _017OpenContextMenuFile(itema, context);
      }
      else
      {
         _017OpenContextMenu(context);
      }
      _001ClearSelection();
   }


   void file_list::_001OnInitializeForm(::user::interaction * pinteraction)
   {

      ASSERT(pinteraction != nullptr);

      if (pinteraction == nullptr)
      {

         return;

      }

      file_list_callback * pcallback = filemanager_data()->m_pfilelistcallback;

      __pointer(::user::button) pbutton = pinteraction;

      if (pcallback != nullptr && pbutton != nullptr)
      {

         pbutton->set_button_style(::user::button::style_list);

         pcallback->InitializeActionButton(((i32)pinteraction->m_id) - 1000, pbutton);

      }

   }


   void file_list::_001OnButtonAction(::user::interaction * pinteraction)
   {

      file_list_callback * pcallback = filemanager_data()->m_pfilelistcallback;

      if (::is_set(pcallback))
      {

         ::file::item item;

         index iItem = pinteraction->m_iItem;

         index iStrict = _001DisplayToStrict(iItem);

         pcallback->OnButtonAction(pinteraction->m_id, fs_list_item(iStrict));

      }

   }


   //void file_list::GetSelected(::file::item_array &itema)
   //{

   //   synchronous_lock synchronouslock(fs_list()->mutex());

   //   index iItemRange, iItem;
   //   ::user::range range;
   //   _001GetSelection(range);
   //   index_array iaItem;
   //   for (iItemRange = 0;
   //         iItemRange < range.get_item_count();
   //         iItemRange++)
   //   {
   //      auto & itemrange = range.ItemAt(iItemRange);
   //      for (iItem = maximum(0, itemrange.get_lower_bound());
   //            iItem <= itemrange.get_upper_bound();
   //            iItem++)
   //      {

   //         if (iItem < fs_list()->m_itema.get_count() && !iaItem.contains(iItem))
   //         {

   //            iaItem.add(iItem);

   //            index iStrict = _001DisplayToStrict(iItem);

   //            itema.add(fs_list_item(iStrict));

   //         }

   //      }

   //   }

   //}


   void file_list::_001OnVScroll(::message::message * pmessage)
   {

      //__pointer(::message::scroll) pscroll(pmessage);

      //m_iCreateImageListStep = pscroll->m_nPos;

      //m_bRestartCreateImageList = true;

      pmessage->m_bRet = false;

   }


   void file_list::_001OnHScroll(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   ::count file_list::_001GetItemCount()
   {

      return fs_list()->m_itema.get_count();

   }


   bool file_list::add_fs_item(::file::path pathUser, ::file::path pathFinal, string strName)
   {

      synchronous_lock synchronouslock(fs_list()->mutex());

      ::userfs::list_item item;

      item.m_filepathUser = pathUser;

      item.m_filepathFinal = pathFinal;

      item.m_strName = strName;

      auto pcontext = get_context();

      if (pcontext->m_papexcontext->dir().is(pathFinal))
      {

         item.m_flags.add(::file::e_flag_folder);

      }

      fs_list()->m_itema.add_fs_item(item);

      _001OnUpdateItemCount();

      return true;

   }


   __pointer(::image_list) file_list::GetActionButtonImageList(index i)
   {

      if (i == 0)
      {

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         return puser->shell()->GetImageList(filemanager_data()->m_iIconSize);

      }

      return nullptr;

   }


   //void file_list::file_size_add_request(bool bClear)
   //{

   //   __UNREFERENCED_PARAMETER(bClear);

   //   db_server * pcentral = dynamic_cast <db_server *> (psystem->m_psimpledb->db());

   //   if (pcentral == nullptr)
   //   {

   //      return;

   //   }

   //   DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;

   //   single_lock synchronouslock(pset->m_table.mutex(), true);

   //   for (i32 i = 0; i < fs_list()->m_itema.get_count(); i++)
   //   {

   //      //pset->get_cache_fs_size(iSize, item(i)->m_strPath, bPending);

   //   }

   //}


   void file_list::_001InitializeFormPreData()
   {

      ::filemanager::data * pdata = filemanager_data();

      pdata->m_pcallback->on_file_manager_initialize_form_pre_data(pdata, GetDlgCtrlId(), this);

   }


   bool file_list::query_drop(index iDisplayDrop, index iDisplayDrag)
   {

      synchronous_lock synchronouslock(fs_list()->mutex());

      if (iDisplayDrag < 0)
         return false;
      if (iDisplayDrop < 0)
         return false;
      if (iDisplayDrag != iDisplayDrop)
      {

         index iStrict = _001DisplayToStrict(iDisplayDrop);

         if (iStrict <= -1)
         {

            return true; // can drop in is_empty place

         }
         else if (iStrict >= _001GetItemCount())
         {

            return true; // can drop if destination is invalid

         }
         else
         {

            // can drop if destination is folder
            return fs_list_item(iStrict)->IsFolder();

         }

      }

      return false;

   }


   bool file_list::do_drop(index iDisplayDrop, index iDisplayDrag)
   {

      synchronous_lock synchronouslock(fs_list()->mutex());

      index strict = _001DisplayToStrict(iDisplayDrop);

      index strictDrag = _001DisplayToStrict(iDisplayDrag);

      auto pcontext = get_context();

      if (strict >= 0 && fs_list_item(strict)->IsFolder())
      {

         ::file::path strPath = fs_list_item(strictDrag)->m_filepathFinal;

         string strName = strPath.name();

         pcontext->m_papexcontext->file().move(fs_list_item(strict)->m_filepathFinal, strPath);

      }
      else
      {

         ::user::list::do_drop(iDisplayDrop, iDisplayDrag);

      }

      return true;

   }


   //::color::color file_list::get_background_color()
   //{

   //   if (filemanager_data() != nullptr && filemanager_data()->is_topic())
   //   {
   //      return argb(255, 255, 255, 255);
   //      //::color32_t color32;
   //      //if (filemanager_document()->m_emode == document::mode_saving)
   //      //{

   //      //   color32 = argb(255, 255, 210, 180);

   //      //}
   //      //else if (filemanager_document()->m_emode == document::mode_import)
   //      //{

   //      //   color32 = argb(255, 180, 210, 255);

   //      //}
   //      //else if (filemanager_document()->m_emode == document::mode_export)
   //      //{

   //      //   color32 = argb(255, 255, 250, 210);

   //      //}
   //      //else
   //      //{

   //      //   color32 = argb(190, 210, 255, 180);

   //      //}
   //      //return color32;
   //   }
   //   else
   //   {

   //      return argb(255, 255, 255, 255);

   //   }

   //}


   void file_list::_001OnSetFocus(::message::message * pmessage)
   {

      TRACE("filemanager::file_list::_001OnSetFocus");

   }


   void file_list::_001OnKillFocus(::message::message * pmessage)
   {

      TRACE("filemanager::file_list::_001OnKillFocus");

   }


   void file_list::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::filemanager_impact_base::on_subject(psubject, pcontext);

      ::userfs::list::on_subject(psubject, pcontext);

      auto papplication = get_application();

      if (m_bStatic && psubject->id() == id_add_location)
      {

         ::file::patha filepatha;

         filepatha = papplication->data_get(filemanager_data()->m_dataidStatic);

         ::file::path filepath = filemanager_item()->get_user_path();

         filepath.trim();

         if (filepath.has_char() && fs_data()->is_dir(filepath))
         {

            if (filepatha.add_unique(filepath) >= 0)
            {

               string_array stra;

               ::papaya::array::copy(stra, filepatha);

               papplication->data_set(filemanager_data()->m_dataidStatic, stra);

               add_fs_item(filemanager_item()->get_user_path(),
                  filemanager_item()->get_final_path(), filemanager_item()->m_filepathUser.name());

               _001OnUpdateItemCount();

            }

         }

      }
      else if (psubject->id() == id_view_list)
      {

         _001SetView(impact_list);

      }
      else if (psubject->id() == id_view_report)
      {

         _001SetView(impact_report);

      }
      else if (psubject->id() == id_view_icon)
      {

         _001SetView(impact_icon);

      }

      if (psubject->id() == id_initialize)
      {

         if (filemanager_data()->m_bPassBk)
         {

            ::user::list::m_bBackgroundBypass = true;

         }

         _001UpdateColumns();

         _001OnUpdateItemCount();

      }
      else if (!m_bStatic && psubject->id() == id_synchronize_path)
      {

         if (psubject->m_pfileitem->m_filepathUser != filemanager_item()->m_filepathUser)
         {

            return;

         }

         if (filemanager_data()->m_pholderFileList != nullptr)
         {

            {

               synchronous_lock synchronouslock(mutex_draw());

               if (filemanager_data()->m_pholderFileList->m_puserinteractionpointeraChild->has_interaction())
               {

                  filemanager_data()->m_pholderFileList->m_puserinteractionpointeraChild->interaction_at(0)->display(e_display_none);

               }

            }

            filemanager_data()->m_pholderFileList->place_hold(this);

            filemanager_data()->m_pholderFileList->set_need_layout();

         }

         data_get_DisplayToStrict();

         _001OnUpdateItemCount();

      }
      else if (psubject->id() == id_filter)
      {

         if (psubject->payload(id_filter).is_empty())
         {

            FilterClose();

         }
         else
         {

            FilterBegin();

            Filter1(psubject->payload(id_filter).as_string());

         }

      }
      else if (psubject->id() == id_get_active_view_selection)
      {

         if (get_parent_frame()->get_active_view() == (this))
         {

            get_selected_items(*psubject->cast <::file::item_array>(id_selected));

         }

      }
      else if (psubject->id() == id_after_browse)
      {

         if (psubject->payload(id_after_browse) == "filemanager\\replace_name_in_file_system.xhtml")
         {

            //html::matter * pelemental = dynamic_cast < html::matter * > (pupdate->m_pformview->get_html_data()->get_element_by_name("encontrar"));

            //html::impl::input_text * pinput = dynamic_cast < html::impl::input_text * > (pelemental->m_pimpl);

            __pointer(::user::interaction) puserinteractionParent = psubject->m_puserprimitive;

            auto pinteraction = puserinteractionParent->get_child_by_id("encontrar");

            auto pitem = get_first_selected_item();

            if (pitem)
            {

               pinteraction->_001SetText(psubject->payload(id_name), psubject->m_actioncontext);

            }

         }

         if (psubject->id() == id_replace_name)
         {

            if (psubject->payload(id_find).has_char())
            {

               auto pcontext = get_context();

               ::file::path pathFolder = filemanager_item()->get_user_path();

               pcontext->m_papexcontext->file().replace(pathFolder, psubject->payload(id_find), psubject->payload(id_replace));

            }

         }
         else if (psubject->id() == id_new_folder)
         {

            if (psubject->payload(id_folder).has_char())
            {

               ::file::path pathFolder = filemanager_item()->get_user_path() / psubject->payload(id_folder);

               auto pcontext = get_context();

               pcontext->m_papexcontext->dir().mk(pathFolder);

               psubject->m_bRet = true;

            }

         }

      }

   }


} // namespace filemanager



