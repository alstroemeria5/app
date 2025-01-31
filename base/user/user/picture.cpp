#include "framework.h"
#include "base/user/user/_user.h"
#include <math.h>


property & operator << (property & property, const RECTANGLE_F64 & rectangle)
{

   property["left"] = rectangle.left;
   property["top"] = rectangle.top;
   property["right"] = rectangle.right;
   property["bottom"] = rectangle.bottom;

   return property;

}

property & operator >> (property & property, RECTANGLE_F64 & rectangle)
{

   property["left"].as(rectangle.left);
   rectangle.top = property["top"].f64();
   rectangle.right = property["right"].f64();
   rectangle.bottom = property["bottom"].f64();

   return property;

}



namespace user
{


   picture::picture()
   {

      set(e_object_default_io_exchange);

      reset_cursor_rect();

   }


   //picture::picture()
   //{

   //   m_eobject += object_default_io_exchange;

   //   reset_cursor_rect();

   //}


   picture::~picture()
   {

      enable_picture(false);

   }


   bool picture::is_picture_enabled() const
   {

      return m_ppictureimpl;

   }


   picture::picture_impl::picture_impl()
   {

      set(e_object_default_io_exchange);

      m_dZoom = 1.0;
      m_pointDrag2.x = 0.0;
      m_pointDrag2.y = 0.0;


      m_bOutline = false;
      m_iOutlineWidth = 7;
      m_hlsOutline.m_dH = 0.0;
      m_hlsOutline.m_dL = 0.0;
      m_hlsOutline.m_dS = 0.0;

      m_bGlowDropShadow = false;
      m_iGlowDropShadowOffset = 12;
      m_iGlowDropShadowBlur = 4;
      m_hlsGlowDropShadow.m_dH = 0.0;
      m_hlsGlowDropShadow.m_dL = 0.0;
      m_hlsGlowDropShadow.m_dS = 0.0;

      m_iBlur = 0;
      m_bGrayscale = false;
      m_bInvert = false;
      m_iOpacity = 100;
      m_iSaturation = 100;

   }


   bool picture::enable_picture(bool bEnable)
   {

      if (bEnable)
      {

         __compose_new(m_ppictureimpl);

      }
      else
      {

         __release(m_ppictureimpl);

      }

      return is_equivalent(bEnable, m_ppictureimpl);

   }


   void picture::on_hit_test(::user::item & item)
   {

      ASSERT(is_picture_enabled());

      //_rtransform_point(point);

      if (m_ppictureimpl->m_rectangle.contains(item.m_pointHitTest))
      {

         item = 0;

         return;

      }

      item = -1;

   }


   point_f64 picture::_transform(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      _transform_point(point);

      return point;

   }


   point_f64 picture::_transform_drawing(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      _transform_point_drawing(point);

      return point;

   }


   void picture::_transform_point(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectangle.center());

      m.transform(point);

   }


   void picture::_transform_point_drawing(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectDrawing.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectDrawing.center());

      m.transform(point);

   }

   point_f64 picture::_rtransform(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      _rtransform_point(point);

      return point;

   }


   point_f64 picture::_rtransform_drawing(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      _rtransform_point_drawing(point);

      return point;

   }


   void picture::_rtransform_point(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectangle.center());

      m.transform(point);

   }


   void picture::_rtransform_point_drawing(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectDrawing.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectDrawing.center());

      m.transform(point);

   }


   point_f64 picture::drag_transform(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      drag_transform_point(point);

      return point;

   }


   point_f64 picture::drag_transform_drawing(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      drag_transform_point_drawing(point);

      return point;

   }


   void picture::drag_transform_point(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.scale(m_ppictureimpl->m_dZoom, m_ppictureimpl->m_dZoom);

      m.translate(m_ppictureimpl->m_rectangle.center());

      m.transform(point);

   }


   void picture::drag_transform_point_drawing(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectDrawing.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.scale(m_ppictureimpl->m_dZoom, m_ppictureimpl->m_dZoom);

      m.translate(m_ppictureimpl->m_rectDrawing.center());

      m.transform(point);

   }

   point_f64 picture::drag_rtransform(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      drag_rtransform_point(point);

      return point;

   }


   point_f64 picture::drag_rtransform_drawing(const point_f64 & pointParam) const
   {

      point_f64 point(pointParam);

      drag_rtransform_point_drawing(point);

      return point;

   }


   void picture::drag_rtransform_point(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      double dZoom = m_ppictureimpl->m_dZoom;

      m.scale(1.0 / dZoom, 1.0 / dZoom);

      m.transform(point);

   }



   void picture::set_drag_point(const ::point_f64 & point)
   {

      auto size = get_size();

      m_ppictureimpl->m_pointDrag2.x = point.x * size.cx/m_ppictureimpl->m_rectangle.width();

      m_ppictureimpl->m_pointDrag2.y = point.y * size.cy / m_ppictureimpl->m_rectangle.height();

   }

   ::point_f64 picture::get_drag_point()
   {

      ::point_f64 point;

      auto size = get_size();

      point.x = m_ppictureimpl->m_pointDrag2.x *m_ppictureimpl->m_rectangle.width() / size.cx;

      point.y = m_ppictureimpl->m_pointDrag2.y *m_ppictureimpl->m_rectangle.height() / size.cy;

      return point;

   }


   void picture::drag_rtransform_point_drawing(point_f64 & point) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::draw2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectDrawing.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      m.scale(1.0 / m_ppictureimpl->m_dZoom, 1.0 / m_ppictureimpl->m_dZoom);

      //m.translate(m_ppictureimpl->m_rectDrawing.center());

      m.transform(point);

   }


   void picture::update_placement()
   {

   }


   void picture::update_drawing_rect(::size_f64 sizePage, ::size_f64 sizeClient)
   {

      ASSERT(is_picture_enabled());

      if (sizeClient.area() <= 0)
      {

         m_ppictureimpl->m_rectDrawing = m_ppictureimpl->m_rectangle;

      }
      else
      {

         m_ppictureimpl->m_rectDrawing.left = m_ppictureimpl->m_rectangle.left * sizePage.cx / sizeClient.cx;
         m_ppictureimpl->m_rectDrawing.right = m_ppictureimpl->m_rectangle.right * sizePage.cx / sizeClient.cx;
         m_ppictureimpl->m_rectDrawing.top = m_ppictureimpl->m_rectangle.top * sizePage.cy / sizeClient.cy;
         m_ppictureimpl->m_rectDrawing.bottom = m_ppictureimpl->m_rectangle.bottom * sizePage.cy / sizeClient.cy;

      }

   }


   void picture::update_screen_rect(::size_f64 sizePage, ::size_f64 sizeClient)
   {

      ASSERT(is_picture_enabled());

      if (sizePage.area() <= 0)
      {

         m_ppictureimpl->m_rectangle = m_ppictureimpl->m_rectDrawing;

      }
      else
      {

         m_ppictureimpl->m_rectangle.left = m_ppictureimpl->m_rectDrawing.left * sizeClient.cx / sizePage.cx;
         m_ppictureimpl->m_rectangle.right = m_ppictureimpl->m_rectDrawing.right * sizeClient.cx / sizePage.cx;
         m_ppictureimpl->m_rectangle.top = m_ppictureimpl->m_rectDrawing.top * sizeClient.cy / sizePage.cy;
         m_ppictureimpl->m_rectangle.bottom = m_ppictureimpl->m_rectDrawing.bottom * sizeClient.cy / sizePage.cy;

      }

   }

   void picture::update_region()
   {

      if (m_ppictureimpl->m_rectRegion == m_ppictureimpl->m_rectangle
            && m_ppictureimpl->m_rectRegionDrawing == m_ppictureimpl->m_rectDrawing)
      {

         return;

      }



      ASSERT(is_picture_enabled());

      m_ppictureimpl->m_polygonDrawing.set_size(4);

      m_ppictureimpl->m_polygonDrawing[0] = _transform_drawing(m_ppictureimpl->m_rectDrawing.top_left());
      m_ppictureimpl->m_polygonDrawing[1] = _transform_drawing(m_ppictureimpl->m_rectDrawing.top_right());
      m_ppictureimpl->m_polygonDrawing[2] = _transform_drawing(m_ppictureimpl->m_rectDrawing.bottom_right());
      m_ppictureimpl->m_polygonDrawing[3] = _transform_drawing(m_ppictureimpl->m_rectDrawing.bottom_left());

      m_ppictureimpl->m_polygonDrawing.m_bDirty = true;

      m_ppictureimpl->m_polygon.set_size(4);

      m_ppictureimpl->m_polygon[0] = _transform(m_ppictureimpl->m_rectangle.top_left());
      m_ppictureimpl->m_polygon[1] = _transform(m_ppictureimpl->m_rectangle.top_right());
      m_ppictureimpl->m_polygon[2] = _transform(m_ppictureimpl->m_rectangle.bottom_right());
      m_ppictureimpl->m_polygon[3] = _transform(m_ppictureimpl->m_rectangle.bottom_left());

      m_ppictureimpl->m_polygon.m_bDirty = true;

      m_ppictureimpl->m_rectRegion = m_ppictureimpl->m_rectangle;
      m_ppictureimpl->m_rectRegionDrawing = m_ppictureimpl->m_rectDrawing;

   }


   ::draw2d::region_pointer picture::get_region() const
   {

      if (m_ppictureimpl->m_region.is_null())
      {

         ((picture*)this)->update_region();

      }

      return m_ppictureimpl->m_region;

   }


   bool picture::intersects(const ::rectangle_f64 & rectParam) const
   {

      rectangle_f64 rectangle(rectParam);

      polygon_f64 polygon_i32;

      polygon_i32.set_size(4);

      polygon_i32[0] = rectangle.top_left();
      polygon_i32[1] = rectangle.top_right();
      polygon_i32[2] = rectangle.bottom_right();
      polygon_i32[3] = rectangle.bottom_left();

      polygon_i32.m_bDirty = false;

      polygon_i32.m_bDirtyBoundingRect = false;

      polygon_i32.m_rectBounding = rectangle;

      if (m_ppictureimpl->m_polygon.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return polygon_i32.overlaps(m_ppictureimpl->m_polygon);

   }


   rectangle_f64 picture::drawing_bounds() const
   {

      rectangle_f64 rectangle(0.0, 0.0, 0.0, 0.0);

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      if (m_ppictureimpl->m_polygonDrawing.get_size() > 0)
      {

         rectangle.left = rectangle.right = m_ppictureimpl->m_polygonDrawing[0].x;

         rectangle.top = rectangle.bottom = m_ppictureimpl->m_polygonDrawing[0].y;

         for (index i = 1; i < m_ppictureimpl->m_polygonDrawing.get_size(); i++)
         {

            if (m_ppictureimpl->m_polygonDrawing[i].x < rectangle.left)
            {

               rectangle.left = m_ppictureimpl->m_polygonDrawing[i].x;

            }
            else if (m_ppictureimpl->m_polygonDrawing[i].x > rectangle.right)
            {

               rectangle.right = m_ppictureimpl->m_polygonDrawing[i].x;

            }

            if (m_ppictureimpl->m_polygonDrawing[i].y < rectangle.top)
            {

               rectangle.top = m_ppictureimpl->m_polygonDrawing[i].y;

            }
            else if (m_ppictureimpl->m_polygonDrawing[i].y > rectangle.bottom)
            {

               rectangle.bottom = m_ppictureimpl->m_polygonDrawing[i].y;

            }

         }

      }

      return rectangle;

   }

   point_f64_array & picture::drawing_polygon() const
   {

      rectangle_f64 rectangle(0.0, 0.0, 0.0, 0.0);

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return m_ppictureimpl->m_polygonDrawing;

   }


   bool picture::intersects_drawing(const polygon_f64 & polygon_i32) const
   {

      ASSERT(is_picture_enabled());

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return polygon_i32.overlaps( m_ppictureimpl->m_polygonDrawing);

   }


   bool picture::intersects_drawing(const ::rectangle_f64 & rectParam) const
   {

      ASSERT(is_picture_enabled());

      polygon_f64 polygon_i32;

      polygon_i32.set_rect(rectParam);

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return polygon_i32.overlaps(m_ppictureimpl->m_polygonDrawing);

   }


   bool picture::is_valid()
   {

      return true;

   }


   ::size_f64 picture::get_size()
   {

      return ::size_f64(128, 128);

   }


   ::size_f64 picture::get_request_size()
   {

      return get_size();

   }


   bool picture::set_text_editable(bool bEditable)
   {

      return false;

   }


   bool picture::is_text_editable() const
   {

      return false;

   }


   bool picture::is_text_editor() const
   {

      return false;

   }


   void picture::reset_cursor_rect()
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      m_ppictureimpl->m_rectCursor.set(0, 0, -1, -1);

   }


   bool picture::is_dragging()
   {

      if (!is_valid())
      {

         return false;

      }

      if (!m_ppictureimpl->m_bDrag)
      {

         return false;

      }

      return true;

   }


   //int picture::on_hit_test_cursor(point_f64 point)
   //{

   //   if (!is_valid())
   //   {

   //      return -1;

   //   }

   //   _rtransform_point(point);

   //   if(m_ppictureimpl->m_rectangle.contains(point))
   //   {

   //      return 0;

   //   }

   //   return -1;

   //}


   ::image_pointer picture::defer_draw_drop_shadow_phase1(rectangle_i32 & rectDropShadow, ::draw2d::fastblur & blurDropShadow, ::image_pointer & pimageDropShadow, ::image_pointer pimage)
   {

      if (m_ppictureimpl->m_bGlowDropShadow)
      {

         double dBlur = (double)m_ppictureimpl->m_iGlowDropShadowBlur * (double)pimage->width() / (double)rectDropShadow.width();

         int iBlur = (int) ceil(dBlur);

         ::rectangle_i32 rectDib(pimage->get_size());

         int iShift = iBlur * 2;

         rectDib.inflate(iShift, iShift);

         pimageDropShadow = m_pcontext->context_image()->create_image(rectDib.size());

         if (pimageDropShadow)
         {

            rectDropShadow.inflate(m_ppictureimpl->m_iGlowDropShadowBlur, m_ppictureimpl->m_iGlowDropShadowBlur);

            pimageDropShadow->fill(0);

            image_source imagesource(pimage);

            image_drawing_options imagedrawingoptions(pimage->rectangle({ iShift, iShift }));

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pimageDropShadow->g()->draw(imagedrawing);

            pimageDropShadow->paint_rgb(m_ppictureimpl->m_hlsGlowDropShadow);

            blurDropShadow.blur(pimageDropShadow, iBlur);

         }

      }

      return pimage;

   }

   void picture::defer_draw_drop_shadow_phase2(::draw2d::graphics_pointer & pgraphics, const rectangle_i32 & rectangle, ::draw2d::fastblur & pblurDropShadow, ::image_pointer & pimageDropShadow)
   {

      if (m_ppictureimpl->m_bGlowDropShadow)
      {

         ::rectangle_i32 rectDropShadow(rectangle);

         rectDropShadow.offset(m_ppictureimpl->m_iGlowDropShadowOffset, m_ppictureimpl->m_iGlowDropShadowOffset);

         image_source imagesource(pimageDropShadow);

         image_drawing_options imagedrawingoptions(rectDropShadow);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }


   void picture::draw_impl(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void picture::hit_test(::user::item & item, const ::point_i32 & point)
   {

      item.m_pointScreen = point;

      item.m_pointClient = _rtransform(item.m_pointScreen);

      item.m_pointHitTest = item.m_pointClient;

      on_hit_test(item);

   }



   ::rectangle_f64 picture::get_rect_for_picture2()
   {

      auto size = m_ppictureimpl->m_rectDrawing.size() / 2.0;

      auto pointDrag = get_drag_point();

      size = ::size_f64(pointDrag.x * m_ppictureimpl->m_rectDrawing.width(),
         pointDrag.y * m_ppictureimpl->m_rectDrawing.height()) - size;

      rectangle_f64 rectangle(__pointd(size), ::size_f64(m_ppictureimpl->m_rectDrawing.size()));

      return rectangle;

   }


   void picture::draw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!_000OnBeforeDraw(pgraphics))
      {

         return;

      }

      ::draw2d::savedc savedc(pgraphics);

      ::draw2d::matrix mRot;

      ::rectangle_f64 rectClip(m_ppictureimpl->m_rectDrawing);

      ::polygon_f64 polygon_i32;

      polygon_i32.set_size(4);

      polygon_i32[0] = _transform_drawing(rectClip.top_left());
      polygon_i32[1] = _transform_drawing(rectClip.top_right());
      polygon_i32[2] = _transform_drawing(rectClip.bottom_right());
      polygon_i32[3] = _transform_drawing(rectClip.bottom_left());

      pgraphics->intersect_clip(polygon_i32);

      mRot.append(::draw2d::matrix::rotation(m_ppictureimpl->m_dRotate));

      ::draw2d::matrix mG;

      pgraphics->get_viewport_scale(mG);

      pgraphics->prepend(mRot);

      pgraphics->prepend(::draw2d::matrix::scaling(m_ppictureimpl->m_dZoom, m_ppictureimpl->m_dZoom));

      pgraphics->prepend(::draw2d::matrix::translation(
         -m_ppictureimpl->m_rectangle.width() / 2,
         -m_ppictureimpl->m_rectangle.height() / 2));

      auto pointDrag = get_drag_point();

      pgraphics->prepend(::draw2d::matrix::translation(
         pointDrag.x,
         pointDrag.y));

      ::draw2d::matrix mTrans;

      auto pointD = m_ppictureimpl->m_rectDrawing.center();

      mG.transform(pointD);

      mTrans.append(::draw2d::matrix::translation(pointD));

      pgraphics->append(mTrans);

      draw_impl(pgraphics);


   }




   void picture::move_to(point_f64 point, ::size_f64 sizePage, ::size_f64 sizeClient, const ::rectangle_f64 & rectMargin)
   {

      m_ppictureimpl->m_rectangle.move_to(point);

      update_region();

      m_ppictureimpl->m_rectangle._001Constraint(rectMargin, m_ppictureimpl->m_rectBounding);

      update_drawing_rect(sizePage, sizeClient);

      update_region();

      update_placement();

   }



   void picture::picture_impl::exchange(::stream & stream)
   {

      __EXCHANGE(rectangle);
      __EXCHANGE(rectDrawing);
      __EXCHANGE(rectCursor);
      __EXCHANGE(bDrag);
      __EXCHANGE(dRotate);
      __EXCHANGE(rectBounding);
      __EXCHANGE(polygon);
      __EXCHANGE(polygonDrawing);
      __EXCHANGE(ptaCursor);
      __EXCHANGE(dZoom);
      __EXCHANGE(pointDrag2);


      __EXCHANGE(bOutline);
      __EXCHANGE(iOutlineWidth);
      __EXCHANGE(hlsOutline);

      __EXCHANGE(bGlowDropShadow);
      __EXCHANGE(iGlowDropShadowOffset);
      __EXCHANGE(iGlowDropShadowBlur);
      __EXCHANGE(hlsGlowDropShadow);

      __EXCHANGE(iBlur);
      __EXCHANGE(bGrayscale);
      __EXCHANGE(bInvert);
      __EXCHANGE(iOpacity);
      __EXCHANGE(iSaturation);


   }


   picture::picture_impl::~picture_impl()
   {


   }


   void picture::exchange(::stream & stream)
   {

      if (stream.is_version(FIRST_VERSION))
      {

         bool bEnable = false;

         if (stream.is_storing())
         {

            bEnable = m_ppictureimpl != nullptr;

         }

         stream.exchange(id(), bEnable);

         if (!stream.is_storing())
         {

            enable_picture(bEnable);

         }

         if (bEnable)
         {

            m_ppictureimpl->exchange(stream);

         }

      }

   }


} // namespace user



