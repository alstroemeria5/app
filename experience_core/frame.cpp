#include "framework.h"


namespace experience
{


   namespace core
   {


            frame::frame() :
               m_penText1(e_create),
               m_penFace1(e_create),
               m_penHilight1(e_create),
               m_penShadow1(e_create),
               m_penDkShadow1(e_create)
            {

               m_pointWindowIcon.x = 5;

               m_sizeIcon.cx = 32;

               m_sizeIcon.cy = 32;

               m_colorCaptionText = argb(255, 0, 0, 0);

               m_rectangleClient.set(0, 0, 0, 0);

            }


            frame::~frame()
            {

            }


            void frame::on_initialize_experience_frame()
            {

/*               auto estyle = translate_style(m_strStyle);

               set_style(estyle)*/;

            }


            string frame::get_default_user_style() const
            {

               return "TranslucidWarmLiteGray";

            }


            void frame::OnMove(__pointer(::user::interaction) pframewindow)
            {

               __UNREFERENCED_PARAMETER(pframewindow);

            }


            void frame::Glass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectParam)
            {

               auto pframewindow = m_pframewindow;

               auto psystem = m_psystem->m_paurasystem;

               auto imaging = psystem->imaging();

               ::rectangle_i32 rectangleClient(rectParam);

               ::rectangle_i32 rectInflate;

               if(rectangleClient.is_empty())
               {

                  return;

               }


               i32 iInflate = 5; // raio 2 pixels + centro 1 pixel

               rectInflate = rectangleClient;

               rectInflate.inflate(iInflate, iInflate);

               ::rectangle_i32 rectScreen;

               pframewindow->best_monitor(rectScreen);

               ::image_pointer pimage1;

               ::image_pointer pimage2;

               pimage1 = m_pcontext->context_image()->create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});

               pimage2 = m_pcontext->context_image()->create_image({rectangleClient.width() + iInflate * 2,  rectangleClient.height() + iInflate * 2});

               ::rectangle_i32 rectWindow = rectangleClient;

               pframewindow->client_to_screen(rectWindow);

               ::point_i32 pointInflate(iInflate, iInflate);

               auto point = rectangleClient.top_left();

               point -= pointInflate;

               bool b;

               {

                  rectangle_f64 rectangleSource(point, pimage1->get_size());

                  image_source imagesource(pgraphics, rectangleSource);

                  rectangle_f64 rectangleTarget(pimage1->get_size());

                  image_drawing_options imagedrawingoptions(rectangleTarget);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  b = pimage2->g()->draw(imagedrawing);

               }

               b = imaging.blur(pimage2, 2);

               {

                  rectangle_f64 rectangleSource(pointInflate, rectangleClient.size());

                  image_source imagesource(pimage2, rectangleSource);

                  rectangle_f64 rectangleTarget(rectangleClient);

                  image_drawing_options imagedrawingoptions(rectangleTarget);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }

            }


            status < ::color::color > frame::get_border_main_body_color()
            {

               return rgb(63, 150, 106);

            }


            void frame::ColorGlass(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::color::color & color32, byte bAlpha)
            {

               pgraphics->fill_rectangle(rectangle, ::color::color(color32, bAlpha));

            }


            //void frame::set_user_style(::user::enum_style estyle)
            //{

            //   m_pframewindow->m_estyle = estyle;

            //   if (get_control_box().is_null())
            //   {

            //      return;

            //   }

            //   on_style_change();

            //}


            //frame::e_style frame::translate_style(const ::string & pszStyle)
            //{

            //   string strStyle(pszStyle);

            //   if(strStyle == "TranslucidLightBlue")
            //   {

            //      return StyleTranslucidLightBlue;

            //   }
            //   else if (strStyle == "TranslucidLightGreen")
            //   {

            //      return StyleTranslucidLightGreen;

            //   }
            //   else if (strStyle == "TranslucidWarmGray")
            //   {

            //      return StyleTranslucidWarmGray;

            //   }
            //   else if (strStyle == "TranslucidWarmLiteGray")
            //   {

            //      return StyleTranslucidWarmLiteGray;

            //   }
            //   else if(strStyle == "DarkWarmBlue")
            //   {

            //      return StyleDarkWarmBlue;

            //   }
            //   else if(strStyle == "WarmGray")
            //   {

            //      return StyleTranslucidWarmGray;

            //   }
            //   else if(strStyle == "BlueRedPurple")
            //   {

            //      return StyleBlueRedPurple;

            //   }
            //   else if(strStyle == "RedOrange")
            //   {

            //      return StyleRedOrange;

            //   }
            //   else if(strStyle == "LightBlue")
            //   {

            //      return StyleLightBlue;

            //   }
            //   else if (strStyle == "BlackBorder")
            //   {

            //      return StyleBlackBorder;

            //   }
            //   else if (strStyle == "LightGreen")
            //   {

            //      return StyleLightGreen;

            //   }
            //   else if (strStyle == "EveningSun")
            //   {

            //      return StyleEveningSun;

            //   }
            //   else if (strStyle == "BlackPiano")
            //   {

            //      return StyleBlackPiano;

            //   }
            //   else
            //   {

            //      return StyleLightBlue;

            //   }

            //}


            frame::enum_element operator++(frame::enum_element & eelement, i32 i)
            {
               __UNREFERENCED_PARAMETER(i);
               return (frame::enum_element) (*((i32*)&eelement))++;
            }

            bool frame::get_element_rect(RECTANGLE_I32 * lprect, enum_element eelement)
            {
               switch(eelement)
               {
               case ElementTopLeftIcon:
               {

                  auto pdrawicon = m_pframewindow->get_draw_icon();

                  if (m_pframewindow == nullptr || pdrawicon == nullptr)
                  {

                     return false;

                  }

                  lprect->left = m_pointWindowIcon.x;
                  lprect->top = m_pointWindowIcon.y;
                  lprect->right = lprect->left + m_sizeIcon.cx;
                  lprect->bottom = lprect->top + m_sizeIcon.cy;

                  //lprect->right = lprect->left + pdrawicon->get_size().cx;
                  //lprect->bottom = lprect->top + pdrawicon->get_size().cy;

                  return true;

               }

               case ElementMoveGripMinimal:

                  if (m_pframewindow == nullptr || m_pframewindow->layout().design().display() != ::e_display_minimal)
                  {
                   
                     return false;

                  }

                  //lprect->left = m_pointMoveGripMinimal.x + 2;
                  //lprect->top = m_pointMoveGripMinimal.y + 2;
                  lprect->right = lprect->left + m_iCaptionHeight - 4;
                  lprect->bottom = lprect->top + m_iCaptionHeight - 4;

                  return true;

               default:
                  break;
               }
               return false;

            }

   
            e_hittest frame::_001HitTest(const ::point_i32 &point)
            {
               return ::experience::frame::_001HitTest(point);
//               ::rectangle_i32 rectangle;
//               for(enum_element eelement = (enum_element)(ElementNone + 1);
//                     eelement < ElementEnd;
//                     eelement++)
//               {
//                  get_element_rect(rectangle, eelement);
//                  if(rectangle.contains(point))
//                  {
//                     eelementParam = eelement;
//                     return true;
//                  }
//               }
//               return false;
            }


            void frame::set_moveable_border_color(const ::color::color& colorMoveableBorder)
            {
               
               m_colorMoveableBorder = colorMoveableBorder;

               ::color::color color;

               color.set_rgb(colorMoveableBorder);
               color.hls_rate(0.0, 0.5, 0.0);
               m_colorMoveableBorderHilight = color;
               m_colorMoveableBorderHilight.alpha = 255;

               color.set_rgb(colorMoveableBorder);
               color.hls_rate(0.0, -0.3, 0.0);
               m_colorMoveableBorderShadow = color;
               m_colorMoveableBorderShadow.alpha = 255;

               color.set_rgb(colorMoveableBorder);
               color.hls_rate(8.0, -0.8, 0.0);
               m_colorMoveableBorderDkShadow = color;
               m_colorMoveableBorderDkShadow.alpha = 255;

               m_colorCaptionTextBk = m_colorMoveableBorderShadow;

            }


            void frame::set_button_color_schema_001(const ::color::color& colorMoveableBorder)
            {

//               defer_create_user_schema(schema_button);

//               ::color::color crBase = crMoveableBorder;
//
//               color ca;
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_border, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.11, -0.11);
//               create_color(color_background, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.49, -0.49);
//               create_color(color_text_normal, ca.get_rgb() | (0xff << 24));
//
//
//
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.45, 0.11);
//               create_color(color_border_hover, ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, 0.33, 0.0);
//               create_color(color_background_hover,ca.get_rgb() | (0xff << 24));
//
//               ca.set_rgb(crBase);
//               ca.hls_rate(0.0, -0.55, 0.11);
//               create_color(color_text_hover, ca.get_rgb() | (0xff << 24));

            }


            void frame::set_frame_color_system_default_001()
            {

               auto pframewindow = m_pframewindow;

               auto psystem = m_psystem->m_paurasystem;

               auto pdraw2d = psystem->draw2d();

               auto pgraphics = pdraw2d->create_memory_graphics();

               auto pstyle = pframewindow->get_style(pgraphics);

               m_penText1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_text));
               m_penFace1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_background));
               m_penHilight1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_hilite));
               m_penShadow1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_shadow));
               m_penDkShadow1->create_solid(1, pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow));
               m_colorDkShadow = pframewindow->get_color(pstyle, ::user::e_element_button_dark_shadow);
               m_colorFrameBorder = argb(255, 0, 0, 0);

            }


            void frame::on_style_change_001_and_002(::draw2d::graphics_pointer & pgraphics)
            {

               auto pcontrolbox = get_control_box();

               m_minSize = size_i32(144, 48);

               m_minSize.cy = 48;

               if (pcontrolbox)
               {

                  pcontrolbox->set_button_color_system_default_001();

               }

               set_frame_color_system_default_001();

               auto pframewindow = m_pframewindow;

               //auto estyle = pframewindow->m_estyle;

               auto colorBorder = pframewindow->get_moveable_border_color();

               set_moveable_border_color(colorBorder);

               set_button_color_schema_001(m_colorMoveableBorder);

               if(m_pframewindow->m_estyle == ::user::StyleTranslucidWarmGray || m_pframewindow->m_estyle == ::user::StyleDarkWarmBlue)
               {

                  pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

                  m_colorCaptionText = argb(255, 255, 255, 255);

               }
               else if (m_pframewindow->m_estyle == ::user::StyleBlackPiano || m_pframewindow->m_estyle == ::user::StyleBlackBorder)
               {

                  pcontrolbox->m_colorBackground = m_colorCaptionTextBk;

                  m_colorCaptionText = argb(255, 255, 255, 255);

               }

            }


            //::color::color frame::get_style_moveable_border_color(::user::enum_style estyle)
            //{
            //   switch(m_pframewindow->m_estyle)
            //   {
            //   case ::user::StyleLightBlue:
            //   case ::user::StyleTranslucidLightBlue:
            //      return rgb(116, 160, 220);
            //   case ::user::StyleBlackPiano:
            //   case ::user::StyleBlackBorder:
            //      return rgb(0, 0, 0);
            //   case ::user::StyleTranslucidWarmGray:
            //      return argb(255, 190, 184, 177);
            //      break;
            //   case ::user::StyleDarkWarmBlue:
            //      return argb(255,34,54,75);
            //      break;
            //   case ::user::StyleLightGreen:
            //   case ::user::StyleTranslucidLightGreen:
            //      return rgb(116, 220, 160) | 0xff000000;
            //   case ::user::StyleRedOrange:
            //      return rgb(255, 170, 136) | 0xff000000;
            //   case ::user::StyleBlueRedPurple:
            //      return rgb(200, 100, 220) | 0xff000000;
            //   case ::user::StyleEveningSun:
            //      return rgb(255, 210, 100) | 0xff000000;
            //   case ::user::StyleTranslucidWarmLiteGray:
            //      return rgb(239, 230, 219) | 0xff000000;
            //   }


            //   // Light Green/Translucid Light Green
            //   return rgb(116, 220, 160) | 0xff000000;

            //}


            //bool frame::is_translucid_style(e_style estyle)
            //{


            //}


            void frame::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam,enum_border eborder, const ::color::color & colorTopLeft, const ::color::color& colorBottomRight)
            {

               ::rectangle_i32 rectangle(rectParam);

               i32 x = rectangle.left;
               i32 y = rectangle.top;
               i32 cx = rectangle.width();
               i32 cy = rectangle.height();

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::draw2d::pen_pointer pen;

               if(eborder & e_border_top || eborder & e_border_left)
               {

                  pen.create(this);

                  pen->create_solid(1.0, colorTopLeft);

                  pgraphics->set(pen);

               }

               if(eborder & e_border_top)
               {

                  pgraphics->move_to(x,y);

                  pgraphics->line_to(x + cx,y);

               }

               if(eborder & e_border_left)
               {

                  pgraphics->move_to(x,y);

                  pgraphics->line_to(x,y+cy);

               }

               if((eborder & e_border_right || eborder & e_border_bottom) && (pen.is_null() || pen->m_color != colorBottomRight))
               {

                  pen.create(this);

                  pen->create_solid(1.0,colorBottomRight);

                  pgraphics->set(pen);

               }

               if(eborder & e_border_right)
               {

                  pgraphics->move_to(x + cx,y);

                  pgraphics->line_to(x + cx,y + cy);

               }

               if(eborder & e_border_bottom)
               {

                  pgraphics->move_to(x,y + cy);

                  pgraphics->line_to(x + cx,y + cy);

               }

            }


            void frame::_on_style_change(::draw2d::graphics_pointer & pgraphics)
            {


            }


            void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
            {

               //return; // abcxxx


               if (!m_pframewindow->is_frame_experience_enabled())
               {

                  return;

               }

               //auto psession = get_session();

               pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

               auto pframewindow = m_pframewindow;

               if(!pframewindow->layout().is_full_screen() && !pframewindow->layout().is_zoomed() && !pframewindow->layout().is_iconic() && !m_pframewindow->frame_is_transparent() && m_pframewindow->m_bShowControlBox)
               {

                  on_draw_frame(pgraphics);

               }

               if(pframewindow->layout().is_minimal())
               {

                  ::rectangle_i32 rectIcon;

                  if(get_element_rect(rectIcon,ElementTopLeftIcon))
                  {

                     auto pdrawicon = m_pframewindow->get_draw_icon();

                     if(::is_set(pdrawicon))
                     {

                        image_source imagesource(pdrawicon);

                        image_drawing_options imagedrawingoptions(rectIcon);

                        image_drawing imagedrawing(imagedrawingoptions, imagesource);

                        pgraphics->draw(imagedrawing);

                     }

                  }

                  ::rectangle_i32 rectGrip;

                  if(get_element_rect(rectGrip,ElementMoveGripMinimal))
                  {

                     int i = 0;

                     while(i < rectGrip.width() - 5 + 1)
                     {

                        ::rectangle_f64 rectangle(rectGrip.left + i, rectGrip.top, 3, rectGrip.height());

                        pgraphics->draw_inset_3drect(rectangle, argb(110,230,230,230),argb(110,130,130,130));

                        i += 5;

                     }

                  }

               }
               else if(!pframewindow->layout().is_full_screen() && !m_pframewindow->frame_is_transparent())
               {

                  //pgraphics->fill_rectangle(m_rectCaptionTextBk, m_colorCaptionTextBk);
                  pgraphics->fill_rectangle(m_rectCaption, m_colorCaptionTextBk);

                  ::rectangle_i32 rectIcon;

                  auto pframewindow = m_pframewindow;

                  status < ::color::color > crMoveableBorder;

                  status < ::color::color > crMoveableBorderHilight;

                  status < ::color::color > crMoveableBorderShadow;

                  string str;

                  pframewindow->get_window_text(str);

                  if(pframewindow->is_active_window())
                  {

                     crMoveableBorder = m_colorMoveableBorder;

                     crMoveableBorderHilight = m_colorMoveableBorderHilight;

                     crMoveableBorderShadow = m_colorMoveableBorderShadow;

                  }
                  else
                  {

                     auto pstyle = pframewindow->get_style(pgraphics);

                     crMoveableBorder = pframewindow->get_color(pstyle, ::user::e_element_button_background);

                     crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::e_element_button_hilite);

                     crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::e_element_button_shadow);

                  }

                  ::rectangle_i32 rectangle;

                  pframewindow->get_window_rect(rectangle);

                  rectangle -= rectangle.top_left();

                  if(get_element_rect(rectIcon, ElementTopLeftIcon))
                  {

                     auto pdrawicon = m_pframewindow->get_draw_icon();

                     if(is_set(pdrawicon))
                     {

                        pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                        image_source imagesource(pdrawicon);

                        image_drawing_options imagedrawingoptions(rectIcon);

                        image_drawing imagedrawing(imagedrawingoptions, imagesource);

                        pgraphics->draw(imagedrawing);

                     }

                  }

                  string wstrWindowText;

                  pframewindow->get_window_text(wstrWindowText);

                  pgraphics->set_text_color(m_colorCaptionText);

                  pgraphics->set_font(pframewindow, ::user::e_element_window_title);

                  pgraphics->_DrawText(wstrWindowText, m_rectWindowText, { e_align_left, e_align_vertical_center}, e_draw_text_no_prefix);

               }


            }


            void frame::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               __UNREFERENCED_PARAMETER(pgraphics);

            }


   } // namespace core


} // namespace experience



