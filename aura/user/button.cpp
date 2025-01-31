#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   button::button()
   {

      user_button_construct();

   }


   button::button(const ::string & pszName, const ::id & id)
   {

      user_button_construct();

      m_strWindowText = pszName;

      m_id = id;

   }


   button::~button()
   {

      ::acme::del(m_pbitmap);

      ::acme::del(m_plist);

      set_button_style(style_none);

   }


   void button::user_button_construct()
   {

      m_bClickDefaultMouseHandling = true;

      m_econtroltype = e_control_type_button;

      m_bMouseHoverOnCapture = true;

      m_estockicon = e_stock_icon_none;

      m_estyle = style_none;

      m_pbitmap = nullptr;

      m_plist = nullptr;

      m_iClick = 0;

      m_bClickDefaultMouseHandling = true;

   }


   ::matter* button::clone() const
   {

      auto pcheckbox = new ::user::button;

      return pcheckbox;

   }


   ::write_text::font_pointer button::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate) const
   {

      if (pstyle)
      {

         if (pstyle->m_pfontButton)
         {

            return pstyle->m_pfontButton;

         }

         if (pstyle->m_pfont)
         {

            return pstyle->m_pfont;

         }

      }

      return nullptr;

   }


   enum_translucency button::get_translucency(style * pstyle) const
   {

      if (pstyle)
      {

         if (pstyle->m_etranslucencyButton != e_translucency_undefined)
         {

            return pstyle->m_etranslucencyButton;

         }

      }

      return e_translucency_undefined;

   }



   void button::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create    , pchannel, this, &button::on_message_create);
      MESSAGE_LINK(e_message_key_down   , pchannel, this, &button::on_message_key_down);

      //install_click_default_mouse_handling(pchannel);
      
   }


   void button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if (m_estyle == style_push)
      {

         _001OnButtonDrawPush(pgraphics);

      }
      else if (m_estyle == style_list)
      {

         _001OnButtonDrawList(pgraphics);

      }
      else if (m_estyle == style_image)
      {

         _001OnButtonDrawBitmap(pgraphics);

      }
      else if (m_estyle == style_image_and_text)
      {

         _001OnButtonDrawImageAndText(pgraphics);

      }
      else
      {

         _001OnButtonDrawNormal(pgraphics);

      }

   }


   ::size_f64 button::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      if (pgraphics.is_null())
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         pgraphics = pdraw2d->create_memory_graphics();

         pgraphics->m_puserinteraction = this;

      }

      pgraphics->set_font(this, ::user::e_element_none);

      string strText(m_strWindowText);

      const ::size_i32 & size = pgraphics->get_text_extent(strText);

      ::write_text::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::size_i32 sizeTotal;

      sizeTotal.cx = (::i32) size.cx;

      sizeTotal.cy = (::i32)tm.get_line_spacing();

      return sizeTotal;

   }


   void button::resize_to_fit(::draw2d::graphics_pointer& pgraphics)
   {

      if (m_estyle == style_simple)
      {

         auto sizeTotal = _001CalculateAdjustedFittingSize(pgraphics);

         set_size(sizeTotal);

      }
      else if (m_estyle == style_image)
      {

         ::size_i32 sizeTotal = m_pbitmap->m_pimage->size();

         set_size(sizeTotal);

      }
      else if (m_estockicon != e_stock_icon_none)
      {

         set_size({24, 24});

      }
      else
      {

         auto sizeTotal = _001CalculateAdjustedFittingSize(pgraphics);

         set_size(sizeTotal);

      }

   }


   void button::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      if (echeck != this->get_echeck())
      {

         check::_001SetCheck(echeck, context);

         set_need_redraw();

         post_redraw();

      }

   }


   void button::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_estyle == style_none)
      {

         set_button_style(style_normal);

      }

      m_propertyCheck = fetch_property(m_id, true);

   }


   void button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient, ::user::e_layout_design);

      auto sizeText = _001CalculateAdjustedFittingSize(pgraphics);

      ::rectangle_i32 rectangle;

      rectangle.left = (::i32)(rectangleClient.left + (rectangleClient.width() - sizeText.cx) / 2);

      rectangle.top = (::i32)(rectangleClient.top + (rectangleClient.height() - sizeText.cy) / 2);

      rectangle.right = (::i32)(rectangle.left + sizeText.cx);

      rectangle.bottom = (::i32)(rectangle.top + sizeText.cy);

      m_rectText = rectangle;

   }


   //bool button::create_interaction(::user::interaction * pinteractionParent, const ::id & id)
   //{

   //   return interaction::create_interaction(pinteractionParent, id);

   //}


   void button::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::color::color crBk;

      if (!is_window_enabled())
      {

         // Disabled Background
         crBk = argb(255, 127, 127, 127);

      }
      else if (is_left_button_pressed() || echeck() == ::check_checked)
      {

         // Pressed Background
         crBk = argb(255, 127, 127, 127);

      }
      else if (m_itemHover.is_set())
      {

         // Hover Background
         crBk = argb(255, 80, 80, 80);

      }
      else
      {

         crBk = argb(255, 255, 255, 255);

      }

      auto pstyle = get_style(pgraphics);

      auto psystem = m_psystem->m_paurasystem;

      if (get_translucency(pstyle) >= e_translucency_present)
      {

         pgraphics->fill_rectangle(rectangleClient, ::color::color(crBk) & 127_opacity);

      }
      else
      {

         pgraphics->fill_rectangle(rectangleClient, crBk);

      }

      ::color::color crBorder;

      if (!is_window_enabled())
      {

         crBorder = argb(255, 127, 127, 127);

      }
      else if (is_left_button_pressed() || echeck() == ::check_checked)
      {

         crBorder = argb(255, 255, 255, 255);

      }
      else if (m_itemHover.is_set())
      {

         crBorder = argb(255, 100, 100, 200);

      }
      else
      {

         crBorder = argb(255, 10, 10, 100);

      }

      //if (_001GetFlag(flag_border))
      {

         pgraphics->draw_inset_rectangle(rectangleClient, crBorder);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectangleClient.left += 3;
      rectangleClient.top += 3;
      ::rectangle_i32 rectText = m_rectText;
      //      string str = ::str::international::utf8_to_unicode(str);
      if (m_pbitmap->m_pimage->is_set())
      {
         if (m_pbitmap->m_pimage->width() > 0 && m_pbitmap->m_pimage->height() > 0)
         {
            ::rectangle_i32 rectDib;
            rectDib = m_rectText;
            rectDib.bottom = minimum(rectText.top + m_pbitmap->m_pimage->width(), rectText.bottom);
            rectDib.right = minimum(rectText.left + m_pbitmap->m_pimage->height(), rectText.right);
            //m_pimage->to(pgraphics, rectDib);

            {

               image_source imagesource(m_pbitmap->m_pimage);

               auto rectangle = rectDib;

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            rectText.left += m_pbitmap->m_pimage->width();

         }

      }

      ::draw2d::brush_pointer brushText(e_create);

      pgraphics->set(brushText);

      string strText(get_window_text());

      pgraphics->set_font(this, ::user::e_element_none);

      pgraphics->draw_text(strText, rectText, e_align_top_left);

   }


   bool button::keyboard_focus_is_focusable() const
   {

      return is_window_enabled() && is_window_visible(::user::e_layout_sketch);

   }


   void button::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_pkey;

      ::user::enum_key iKey = pkey->m_ekey;

      if (iKey == ::user::e_key_return || iKey == ::user::e_key_space)
      {

         ::user::control_event ev;

         ev.m_puserinteraction = this;

         ev.m_eevent = ::user::e_event_click;

         ev.m_actioncontext.m_pmessage = pkey;

         ev.m_actioncontext.add(e_source_user);

         on_control_event(&ev);

         pmessage->m_bRet = ev.m_bRet;

         if (pmessage->m_bRet)
         {

            pkey->m_lresult = 1;

         }

      }

   }


   //::color::color button::get_button_text_color()
   //{

   //   ::color::color crText;

   //   if (!is_window_enabled())
   //   {

   //      crText = argb(255, 0, 0, 0);

   //   }
   //   else if (is_left_button_pressed() || get_echeck() == ::check_checked)
   //   {

   //      crText = argb(255, 0, 0, 0);

   //   }
   //   else if (m_itemHover.is_set())
   //   {

   //      crText = argb(255, 80, 80, 80);

   //   }
   //   else
   //   {

   //      crText = argb(255, 0, 0, 0);

   //   }

   //   return crText;

   //}


   ::color::color button::_001GetButtonBackgroundColor()
   {

      ::color::color crBackground;

      if (!is_window_enabled())
      {

         crBackground = argb(255, 180, 180, 180);

      }
      else if (is_left_button_pressed() || get_echeck() == ::check_checked)
      {

         crBackground = argb(255, 240, 240, 240);

      }
      else if (m_itemHover.is_set())
      {

         crBackground = argb(255, 240, 240, 240);

      }
      else
      {

         crBackground = argb(255, 240, 240, 240);

      }

      return crBackground;

   }


   void button::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      interaction::on_subject(psubject, pcontext);

   }


   void button::_001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, ::user::e_element_background, get_state());

      //::color::color crBackground = _001GetButtonBackgroundColor();

      auto & propertyCheck = m_propertyCheck;

      auto echeck = get_echeck();

      if(echeck == ::check_checked)
      {

         ::rectangle_i32 rectPush(rectangleClient);

         ::color::color colorBack(colorBackground);

         colorBack.hls_rate(0.0, -0.2, 0.0);

         rectPush.deflate(0, 0, 1, 1);

         ::color::color colorTopLeft(colorBack);

         ::color::color colorBottomRight(colorBack);

         colorTopLeft.hls_rate(0.0, -0.65, 0.0);

         colorBottomRight.hls_rate(0.0, 0.75, 0.0);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->draw_inset_3drect(rectPush, colorTopLeft, colorBottomRight);

         rectPush.deflate(1, 1);

         pgraphics->draw_inset_3drect(rectPush, colorTopLeft, colorBottomRight);

         rectPush.deflate(1, 1);

         pgraphics->draw_inset_3drect(rectPush, colorTopLeft, colorBottomRight);

         rectPush.deflate(1, 1, 0, 1);

         pgraphics->fill_rectangle(rectPush, colorBack);

      }
      else
      {

         if (colorBackground.is_translucent())
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->fill_rectangle(rectangleClient, colorBackground);

         }

      }

   }


   void button::_001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, RECTANGLE_I32 * prectText)
   {

      ::rectangle_i32 rectText(prectText);

      if (m_estockicon == e_stock_icon_none)
      {

         string strText;

         get_window_text(strText);

         if (strText.has_char())
         {

            auto pstyle = get_style(pgraphics);

            ::color::color colorText = get_color(pstyle, e_element_text, get_state());

            pgraphics->set_text_color(colorText);

            ::e_align ealign;
            ::e_draw_text edrawtext;

            if (m_estyle == style_image_and_text)
            {

               if (m_ealignText)
               {

                  ealign = m_ealignText;

               }
               else
               {

                  ealign = e_align_top_left;

               }

            }
            else
            {

               if (m_ealignText)
               {

                  ealign = m_ealignText;

               }
               else
               {

                  ealign = e_align_center;

               }
            }

            edrawtext = e_draw_text_single_line;

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw_text(strText, rectText, ealign, edrawtext);

         }

      }
      else
      {

         auto pstyle = get_style(pgraphics);

         ::color::color colorText = get_color(pstyle, e_element_text, get_state());

         pgraphics->set_text_color(colorText);

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(1.0, colorText);

         pgraphics->set(pen);

         ::rectangle_i32 rectIcon(rectText);

         rectIcon.deflate(rectIcon.width() / 16, rectIcon.height() / 16);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

      }

   }


   void button::_001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      pgraphics->set_font(this, ::user::e_element_none);

      ::rectangle_i32 rectMargin(2, 2,2, 2);

      ::rectangle_i32 rectBorder(2, 2, 2, 2);

      rectangleClient.deflate(rectMargin);

      rectangleClient.deflate(rectBorder);

      if(m_estyle != style_stock_icon)
      {

         _001OnButtonDrawBackground(pgraphics);

      }

//      if(m_itemHover)
//      {
//
//         pgraphics->fill_rectangle(::rectangle_i32(0, 0, 20, 20), argb(255, 255, 0, 0));
//
//      }

      ::rectangle_i32 rectPadding(4, 4, 4,4);

      rectangleClient.deflate(rectPadding);

      _001OnButtonDrawTextLayer(pgraphics, rectangleClient);

   }


   void button::_001OnButtonDrawBitmap(::draw2d::graphics_pointer & pgraphics)
   {

      _001OnButtonDrawBackground(pgraphics);

      if (!m_pbitmap->m_pimage)
      {

         return;

      }

      ASSERT(m_pbitmap->m_pimage); // required

      // use the main bitmap for up, the selected bitmap for down
      ::image_pointer pimage = m_pbitmap->m_pimage;

      auto psession = get_session();

      if(echeck() == ::check_checked && ::is_ok(m_pbitmap->m_pimageSel))
         pimage = m_pbitmap->m_pimageSel;
      else if(m_itemHover.is_set() && is_window_enabled() && ::is_ok(m_pbitmap->m_pimageHover))
         pimage = m_pbitmap->m_pimageHover;
      else if(::is_ok(m_pbitmap->m_pimageFocus) && has_keyboard_focus())
         pimage = m_pbitmap->m_pimageFocus;   // third image for focused
      else if(!is_window_enabled() && ::is_ok(m_pbitmap->m_pimageDisabled))
         pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::rectangle_i32 rectMargin(4, 4, 4, 4);

      ::rectangle_i32 rectBorder(2, 2,2 ,2);

      rectangleClient.deflate(rectMargin);

      rectangleClient.deflate(rectBorder);

      ::rectangle_i32 rectPadding(4, 4,4,4);

      rectangleClient.deflate(rectPadding);

      if (pimage->area() > 0 && rectangleClient.area() > 0)
      {

         ::rectangle_i32 rectAspect;

         rectAspect.left = 0;

         rectAspect.top = 0;

         double dW = (double) rectangleClient.width() / (double)pimage->width();

         double dH = (double) rectangleClient.height() / (double) pimage->height();

         double dMin = minimum(minimum(dW, dH), 1.0);

         rectAspect.right = (::i32) (pimage->width() * dMin);

         rectAspect.bottom = (::i32) (pimage->height() * dMin);

         rectAspect.Align(e_align_center, rectangleClient);

         pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         {

            image_source imagesource(pimage, ::rectangle_i32(pimage->get_size()));

            rectangle_f64 rectangle(rectAspect);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void button::_001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics)
   {

      _001OnButtonDrawBackground(pgraphics);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::rectangle_i32 rectPadded(rectangleClient);

      int iPadding = 4;

      rectPadded.deflate(iPadding, iPadding);

      ::rectangle_i32 rectAspect(rectPadded);

      if (m_pbitmap->m_pimage)
      {

         ASSERT(m_pbitmap->m_pimage); // required

         // use the main bitmap for up, the selected bitmap for down
         ::image_pointer pimage = m_pbitmap->m_pimage;

         auto psession = get_session();

         if (echeck() == ::check_checked && ::is_ok(m_pbitmap->m_pimageSel))
            pimage = m_pbitmap->m_pimageSel;
         else if (m_itemHover.is_set() && is_window_enabled() && ::is_ok(m_pbitmap->m_pimageHover))
            pimage = m_pbitmap->m_pimageHover;
         else if (::is_ok(m_pbitmap->m_pimageFocus) && has_keyboard_focus())
           pimage = m_pbitmap->m_pimageFocus;   // third image for focused
         else if (!is_window_enabled() && ::is_ok(m_pbitmap->m_pimageDisabled))
            pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

         if (pimage->area() > 0 && rectangleClient.area() > 0)
         {

            rectAspect.left = 0;

            rectAspect.top = 0;

            double dW = (double)rectPadded.width() / (double)pimage->width();

            double dH = (double)rectPadded.height() / (double)pimage->height();

            double dMin = minimum(minimum(dW, dH), 1.0);

            rectAspect.right = (::i32) (pimage->width() * dMin);

           rectAspect.bottom = (::i32) (pimage->height() * dMin);

            rectAspect.Align(e_align_bottom_left, rectPadded);

            pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            {

               image_source imagesource(pimage, ::rectangle_i32(pimage->get_size()));

               rectangle_f64 rectangle(rectAspect);

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            rectAspect.left = rectAspect.right + iPadding;
            rectAspect.right = rectPadded.right;
            rectAspect.top = rectPadded.top;
            rectAspect.bottom = rectPadded.bottom;

         }

      }

      _001OnButtonDrawTextLayer(pgraphics, rectAspect);

   }


   void button::_001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      auto color = get_color(pstyle, e_element_background);

      status < ::color::color > color32;

      if(echeck() == ::check_checked)
      {

         color.hls_rate(0.0,- 0.2,- 0.3);

      }

      if(m_itemHover.is_set())
      {

         color.hls_rate(0.0,0.2,0.0);

      }

      color32 = color;

      class ::color::color colorExt1TL;
      class ::color::color colorExt2TL;
      class ::color::color colorExt1BR;
      class ::color::color colorExt2BR;

      colorExt1TL.set_rgb(color32);
      colorExt2TL.set_rgb(color32);
      colorExt1BR.set_rgb(color32);
      colorExt2BR.set_rgb(color32);

      if(echeck() == ::check_checked)
      {

         colorExt1TL.hls_rate(0.0,- 0.5,0.0);
         colorExt2TL.hls_rate(0.0,- 0.2,0.0);
         colorExt2BR.hls_rate(0.0,0.2,0.0);
         colorExt1BR.hls_rate(0.0,0.85,0.0);

      }
      else
      {

         colorExt1TL.hls_rate(0.0,0.85,0.0);
         colorExt2TL.hls_rate(0.0,0.2,0.0);
         colorExt2BR.hls_rate(0.0,- 0.2,0.0);
         colorExt1BR.hls_rate(0.0,- 0.5,0.0);

      }

      auto psystem = m_psystem->m_paurasystem;

      ::rectangle_i32 rectangle = rectangleClient;
      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,215,colorExt1BR,215);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,210,colorExt1BR,210);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt2TL,205,colorExt2BR,205);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt2TL,200,colorExt2BR,200);
      rectangle.deflate(1,1,1,1);
      pgraphics->fill_rectangle(rectangle,::color::color(color32,200));
      rectangle.deflate(1,1,1,1);

      i32 x1 = rectangle.left;
      i32 x2 = x1 + rectangle.width() / 3;

      rectangle.left = x1;
      rectangle.right = x2;
      rectangle.bottom = rectangle.top + 5;

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1, colorExt1TL);

      pgraphics->set(pen);

      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,220,colorExt1BR,220);


   }


   void button::set_button_style(e_style estyle)
   {

      if (m_estyle == estyle)
      {

         return;

      }

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void button::on_enter_button_style(e_style estyle)
   {

      if(estyle == style_image || estyle == style_image_and_text)
      {

         m_pbitmap = new bitmap();

      }
      else if(estyle == style_list)
      {

         m_plist = new list();

         //m_plist->m_pimagelistNormal         = nullptr;
         //m_plist->m_pimagelistItemHover      = nullptr;
         //m_plist->m_pimagelistSubItemHover   = nullptr;

      }
      else if(estyle == style_push)
      {

         SetTimer(16384,100,nullptr);

      }


   }


   void button::on_exit_button_style(e_style estyle)
   {

      if(estyle == style_image|| estyle == style_image_and_text)
      {

         ::acme::del(m_pbitmap);

      }
      else if(estyle == style_list)
      {

         ::acme::del(m_plist);

      }
      else if(estyle == style_push)
      {

         KillTimer(16384);

      }

   }


   bool button::LoadBitmaps(::payload payload,::payload varSel,::payload varFocus,::payload varDisabled,::payload varHover)
   {

      if (m_estyle != style_image &&
            m_estyle != style_image_and_text)
      {

         set_button_style(style_image);

      }

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      if(!payload.is_empty())
      {

         m_pbitmap->m_pimage = pcontextimage->get_image(payload);

      }

      if(!varSel.is_empty())
      {

         m_pbitmap->m_pimageSel = pcontextimage->get_image(varSel);

      }


      if(!varFocus.is_empty())
      {

         m_pbitmap->m_pimageFocus = pcontextimage->get_image(varFocus);

      }


      if(!varDisabled.is_empty())
      {
         
         m_pbitmap->m_pimageDisabled = pcontextimage->get_image(varDisabled);

      }


      if(!varHover.is_empty())
      {

         m_pbitmap->m_pimageHover = pcontextimage->get_image(varHover);

      }

      return m_pbitmap->m_pimage->is_set() && m_pbitmap->m_pimage->area() > 0;

   }






   void button::pre_translate_message(::message::message * pmessage)
   {

      // Relay events from this button to the tool tip tool handler
      BaseToolTipRelayEvent(pmessage);

      return ::user::interaction::pre_translate_message(pmessage);

   }


   void button::BaseToolTipGetRect(RECTANGLE_I32 * prectangle)

   {
      // use window client rectangle_i32 as the tool rectangle_i32
      get_client_rect(prectangle);

   }

   i32 button::BaseToolTipGetIndex()
   {
      // use window dialog control id as the index
      return (i32)GetDlgCtrlId();
   }


   void button::_001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics)
   {
      ::rectangle_i32 rectangleClient;
      bool bItemHover;
      bool bSubItemHover;

      ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      if(pdrawcontext != nullptr)
      {

         bItemHover     = pdrawcontext->m_bListItemHover;

         bSubItemHover  = pdrawcontext->m_bListSubItemHover;

      }
      else
      {

         if (get_form() != nullptr)
         {

            return;

         }

         bItemHover     = m_itemHover.is_set();

         bSubItemHover  = bItemHover;

      }

      get_client_rect(rectangleClient);

      ::point_i32 point = rectangleClient.top_left();

      point += ::size_i32(1, 1);

      if(bSubItemHover)
      {
         pgraphics->draw_inset_3drect(
         rectangleClient,
         rgb(255,255,255),
         rgb(155,155,105));

         if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
      }
      else if(bItemHover)
      {
         if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
      }
      else
      {
         if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != nullptr)
         {
            
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            
               m_plist->m_iImageItemHover,
            point,
            0);

         }
         else if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);

         }

      }

   }


   void button::BaseToolTipRelayEvent(class ::message::message *)
   {

   }


   bool button::is_custom_draw()
   {

      return m_estyle == style_list;

   }


   void button::set_stock_icon(enum_stock_icon estockicon)
   {

      m_estockicon = estockicon;

   }


   enum_stock_icon button::get_stock_icon()
   {

      return m_estockicon;

   }


} // namespace user



