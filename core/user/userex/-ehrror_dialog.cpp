#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



namespace userex
{


   error_dialog::error_dialog()
   {

   }


   void error_dialog::Initialize(const ::exception::exception & e)
   {

      m_exception = e;

   }


   bool error_dialog::OnInitDialog()
   {
      //dialog::OnInitDialog();

      /*   linux CStatic * pImage = (CStatic *) get_child_by_id(IDC_STATIC_IMAGE);
      ::user::interaction_impl * pWndText = get_child_by_id(IDC_STATIC_TEXT);
      user::plain_edit * pEditAdvanced = (user::plain_edit *) get_child_by_id(IDC_EDIT_ADVANCED);

      if(m_pexception != nullptr)
      {
      HICON hIcon = ::LoadIcon(nullptr, IDI_EXCLAMATION);
      pImage->SetIcon(hIcon);
      pWndText->set_window_text(m_pexception->GetUserText());
      pEditAdvanced->set_window_text(m_pexception->GetDetailsText());
      }
      // TODO: add extra initialization here*/

      return true;  // return true unless you set the focus to a control
      // EXCEPTION: OCX Property Pages should return false
   }


} // namespace musical_player_lite







