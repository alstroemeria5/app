#pragma once


namespace axis
{


   class CLASS_DECL_AXIS user :
      virtual public ::user::user
   {
   public:

      
      ::user::style_pointer                           m_pstyle;
      string_map < ::user::style_pointer >            m_mapStyle;


      user();
      virtual ~user();


      virtual ::estatus init() override;
      virtual void term() override;


      virtual ::user::style* get_user_style() override;


   };


} // namespace axis



