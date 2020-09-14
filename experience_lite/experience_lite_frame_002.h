#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame_002 :
               public frame
            {
            public:


               frame_002(::layered * pobjectContext);
               virtual ~frame_002();

               virtual void on_style_change();

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_border eside);
               void GetBorderRect(const RECT & lpcrectClient, LPRECT lprect, e_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point);

               COLORREF get_border_main_body_color();


            };


         } // namespace lite



      


   } // namespace experience















