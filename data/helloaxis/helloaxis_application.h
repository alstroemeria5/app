﻿#pragma once



namespace helloaxis
{


   class CLASS_DECL_APP_CORE_HELLOAXIS application :
      virtual public ::axis::application
   {
      public:


         enum enum_type
         {

            type_normal,
            type_mili,

         };

         enum_type                                 m_etype;
         string                                 m_strHelloAxis;
         string                                 m_strHelloAxisDefault;
         string                                 m_strAlternateHelloAxis;
         string                                 m_strAlternateHelloAxisDefault;

         bool                                   m_bAxisChat;

         ::user::document *                     m_pdocMenu;

         ::mutex                                  m_mutexAiFont;
         i32                                m_iErrorAiFont;
         bool                                   m_bLoadAiFont;
         void *                                 m_faceAi; // FT_Face m_faceAi;

         application(::object * pobject);
         virtual ~application();

         virtual ::e_status init_instance() override;
         virtual i32  exit_application() override;

         virtual void on_request(::create * pcreate) override;

         virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
         virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

         void paint(HWND hwnd, HDC hdc);

         void paint(HWND hwnd, ::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloaxis



