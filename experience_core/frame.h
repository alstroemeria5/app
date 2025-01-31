#pragma once



   namespace experience
   {


         namespace core
         {


            class CLASS_DECL_APP_EXPERIENCE_CORE frame :
               virtual public ::experience::frame
            {
            public:

               //e_style                           m_pframewindow->m_estyle;
               status < ::color::color >    m_colorFrameBorder;
               status < ::color::color >    m_colorMoveableBorderHilight;
               status < ::color::color >    m_colorMoveableBorderDkShadow;
               status < ::color::color >    m_colorCaptionTextBk;
               status < ::color::color >    m_colorCaptionText;
               ::draw2d::pen_pointer               m_penText1;
               ::draw2d::pen_pointer               m_penFace1;
               ::draw2d::pen_pointer               m_penHilight1;
               ::draw2d::pen_pointer               m_penShadow1;
               ::draw2d::pen_pointer               m_penDkShadow1;
               status < ::color::color >    m_colorDkShadow;
               size_i32                            m_minSize;

               ::draw2d::pen_pointer               m_penHollow0;
               ::draw2d::pen_pointer               m_penHollow1;
               ::draw2d::pen_pointer               m_penHollow2;
               ::draw2d::pen_pointer               m_penHollow3;
               ::draw2d::pen_pointer               m_penHollow4;
               ::draw2d::pen_pointer               m_penHollow5;
               ::size_i32                          m_sizeIcon;

               frame();
               virtual ~frame();


               void on_initialize_experience_frame() override;

               string get_default_user_style() const override;

               status < ::color::color > get_border_main_body_color() override;

               void set_moveable_border_color(const ::color::color& colorMoveableBorder) override;

               virtual void set_button_color_schema_001(const ::color::color& colorMoveableBorder);

               virtual void set_frame_color_system_default_001();

               virtual void on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics);

               //virtual ::color::color get_style_moveable_border_color(::user::enum_style estyle);

               void OnMove(__pointer(::user::interaction) pframewindow) override;

               //virtual void set_style(::user::enum_style estyle);

               //virtual enum_style translate_style(const ::string & pszStyle);

               virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

               //virtual void _001OnBeforeMove(const RECTANGLE_I32 & lpcrectWindow);

               //virtual void _001OnBeforeSize(const RECTANGLE_I32 & lpcrectWindow);

               void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

               bool get_element_rect(RECTANGLE_I32 * lprect, enum_element eelement) override;

               //bool _001HitTest(const POINT_I32 &point, enum_element &eelementParam) override;

               e_hittest _001HitTest(const ::point_i32 & point) override;

               virtual void Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               virtual void ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color& color, byte bAlpha);

//               virtual ::user::front_end_schema * get_user_front_end_schema();

               virtual void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight);

               virtual void on_draw_frame(::draw2d::graphics_pointer & pgraphics);


            };


            frame::enum_element operator++(frame::enum_element & eelement, i32 i);


   } // namespace core


} // namespace experience



