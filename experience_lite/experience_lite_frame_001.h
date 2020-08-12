#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame_001 :
               public frame
            {
            public:


               frame_001(::object * pobject);
               virtual ~frame_001();

               virtual void on_style_change();

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_border eside);
               void GetBorderRect(const RECT & lpcrectClient, LPRECT lprect, e_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point);


            };


         } // namespace lite



      


   } // namespace experience









