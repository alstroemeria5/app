#include "framework.h"
#include "aura/math/calculator/calculator.h"






namespace prompt
{


   primary_view::primary_view(::object * pobject) :
      ::object(pobject),
      ::user::plain_edit(pobject)
   {

      m_iCompromised = 0;

      connect_command_probe("edit_copy", &primary_view::_001OnUpdateEditCopy);
      connect_command("edit_copy", &primary_view::_001OnEditCopy);
      connect_command_probe("edit_paste", &primary_view::_001OnUpdateEditPaste);
      connect_command("edit_paste", &primary_view::_001OnEditPaste);

   }


   void primary_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(psubject);

   }


   void primary_view::install_message_routing(::channel * pchannel)
   {

      BASE::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &primary_view::on_message_context_menu);

   }


   void primary_view::_001OnAfterChangeText(const ::action_context & context)
   {
      string str;

      _001GetText(str);
      strsize iFind;
      strsize iFind2;

      if((iFind = str.reverse_find('\n')) >= 0)
      {
         iFind2 = str.reverse_find('\n', iFind - 1);
         iFind2++;
         if(iFind > iFind2 && iFind2 >= m_iCompromised)
         {
            string strLine = str.Mid(iFind2, iFind - iFind2 - 1);
            if(strLine.has_char())
            {
               bool bOk = false;
               string strNewLine;
               try
               {

                  ::calculator::parser parser(this);

                  ::calculator::matter * pmatter = parser.parse(strLine);

                  string strValue;

                  strValue.Format("%f", pmatter->get_value().to_string().c_str());

                  string strNewText = str + pmatter->get_expression() + " = " + strValue  + "\n";

                  strNewText.replace("\r\n", "\n");

                  _001SetText(strNewText, ::e_source_sync);

                  str = strNewText;

                  m_iCompromised = m_ptree->m_iSelBeg = m_ptree->m_iSelEnd = strNewText.get_length();

                  bOk = true;

               }
               catch(const ::string & psz)
               {

                  TRACE("error %s", psz);

                  bOk = false;

               }

               try
               {
                  if(!bOk)
                  {

                     string_array stra;

                     if(cregexp_util::match(stra, strLine, "(.+)\\s*segundos", true, 2) == 1)
                     {

                        calculator::parser parser(this);

                        calculator::matter * pmatter = parser.parse(stra[1]);

                        string strValue;

                        strValue.Format("%f", pmatter->get_value().to_string().c_str());

                        string strMinFrac;

                        strMinFrac.Format("%f", pmatter->get_value().mod() / 60.0);

                        string strMin;

                        strMin.Format("%d", ((i32)pmatter->get_value().mod() / 60));

                        string strMinSec;

                        strMinSec.Format("%f", fmod(pmatter->get_value().mod(), 60.0));

                        string strNewText = str + pmatter->get_expression() + " segundos = " + strValue  + " segundos = " + strMinFrac + " minutos = " + strMin + " minutos e " + strMinSec + " segundos\n";

                        strNewText.replace("\r\n", "\n");

                        _001SetText(strNewText, ::e_source_sync);

                        str = strNewText;

                        m_iCompromised = m_ptree->m_iSelBeg = m_ptree->m_iSelEnd = strNewText.get_length();

                        bOk = true;

                     }
                     else if(cregexp_util::match(stra, strLine, "(.+)\\s*dias", true, 2) == 1)
                     {

                        calculator::parser parser(this);

                        calculator::matter * pmatter = parser.parse(stra[1]);

                        string strValue;

                        strValue.Format("%f", pmatter->get_value().to_string().c_str());

                        string strMinFrac;

                        strMinFrac.Format("%f", pmatter->get_value().mod() / 60.0);

                        string strMin;

                        strMin.Format("%d", ((i32)pmatter->get_value().mod() / 60));

                        string strMinSec;

                        strMinSec.Format("%f", fmod(pmatter->get_value().mod(), 60.0));

                        string strNewText = str + pmatter->get_expression() + " segundos = " + strValue  + " segundos = " + strMinFrac + " minutos = " + strMin + " minutos e " + strMinSec + " segundos\n";

                        strNewText.replace("\r\n", "\n");

                        _001SetText(strNewText, ::e_source_sync);

                        str = strNewText;

                        m_iCompromised = m_ptree->m_iSelBeg = m_ptree->m_iSelEnd = strNewText.get_length();

                        papplication->send_simple_command("winactionareaview::show_calendar(\""+ __str((i32) pmatter->get_value().mod()) +"\")", (void *) get_wnd()->get_os_data());

                        bOk = true;

                     }

                  }

               }
               catch(const ::string & psz)
               {

                  TRACE("error %s", psz);

                  bOk = false;

               }

               if(!bOk)
               {

#ifdef WINDOWS_DESKTOP

                  if(::ShellExecuteW(
                        nullptr,
                        nullptr,
                        ::str::international::utf8_to_unicode(strLine),
                        nullptr,
                        nullptr,
                        e_display_normal))
                  {
                     string strNewText = str + "executing " + strLine  + "...";
                     strNewText.replace("\r\n", "\n");
                     _001SetText(strNewText, context + ::e_source_sync + ::e_source_system);
                     m_iCompromised = m_ptree->m_iSelBeg = m_ptree->m_iSelEnd = strNewText.get_length();
                  }

#else

                  __throw(todo);

#endif

               }
            }
         }


      }
   }

   void primary_view::_001OnUpdateEditCopy(::message::message * pmessage)
   {
      __pointer(::message::command) pcommand(pmessage);
      pcommand->enable(true);
   }

   void primary_view::_001OnEditCopy(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      clipboard_copy();
   }

   void primary_view::_001OnUpdateEditPaste(::message::message * pmessage)
   {
      __pointer(::message::command) pcommand(pmessage);
      pcommand->enable(true);
   }


   void primary_view::_001OnEditPaste(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      clipboard_paste();
   }


   void primary_view::on_message_context_menu(::message::message * pmessage)
   {

      __pointer(::message::context_menu) pcontextmenu(pmessage);

      track_popup_xml_menu("matter://command/popup_primary_verbing.xml", 0, pcontextmenu->GetPoint());

   }


} // namespace prompt


