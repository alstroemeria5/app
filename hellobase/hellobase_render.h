//
//  hellobase_render.h
//  app_core_hellobase
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#pragma once


namespace hellobase
{


   class CLASS_DECL_APP_HELLO_BASE render :
      virtual public ::helloaxis::render
   {
   public:

      /*
            double                           m_dRenderFps;
            bool                             m_bDib1;

            bool                             m_bAlternate;

            bool                             m_bLite;

            bool                             m_bImageEnable;

            ::mutex                            m_mutexWork;
            ::mutex                            m_mutexDraw;
            ::mutex                            m_mutexSwap;
            ::mutex                            m_mutexDib;
            ::mutex                            m_mutexDib23;

            bool                             m_bNewLayout;
            bool                             m_bHelloRender;
            int                              m_cx;
            int                              m_cy;
            int                              m_cxCache1;
            int                              m_cyCache1;
            int                              m_cxTarget;
            int                              m_cyTarget;

            ::draw2d::fastblur               m_pimageImage;
            ::image_pointer                 m_pimageOut;
            ::image_pointer                 m_pimageA;
            ::image_pointer                 m_pimageB;
            ::image_pointer                 m_pimageWork;
/*            ::draw2d::fastblur               m_pimage;
            ::draw2d::fastblur               m_pimageTint;
            ::image_pointer                 m_pimageTemplate;
            ::image_pointer                 m_pimageTemplate2;

            bool                             m_bVoidTransfer;
            bool                             m_bFirstDone;

            ::draw2d::font_pointer                m_font;

            double                           m_dMinRadius;
            double                           m_dMaxRadius;

            string                           m_strHelloBase;

            ::rect                           m_rectClient;
      */

      ::mutex *                          m_pmutexText;

      view *                           m_pview;


      //tick                            m_tickAnime;
      //tick m_tickLastFast;
      //DWORD                            m_tickFastAnime;
      //::image_pointer                 m_pimageFast;


      //string_array                          m_stra23;
      //string_map < ::image_pointer >    m_mapDib23;
      //bool                             m_b23;
      //u32                         m_uiCurrent23;
      //string                           m_strCurrent23;
      //string                           m_strLast23;
      //bool                             m_bFirst23;
      //DWORD                            m_dw23;

      //array < bilbo >                  m_bilboa;
      //tick m_tickLastOk;


      //bool                             m_bFast;
      //bool                             m_bFastOnEmpty;


      render(::layered * pobjectContext);
      virtual ~render();


      string get_helloaura() { sync_lock slText(m_pmutexText);  string str(m_strHelloBase.c_str()); return str; }


      virtual i32 run();

      virtual bool initialize_render(string strId);


      virtual void full_render() override;
      virtual void helloaura_render() override;
      virtual void helloaura_draw() override;
      virtual void helloaura_render(::draw2d::graphics_pointer & pgraphics) override;
      //virtual void hellobase_render(::draw2d::graphics_pointer & pgraphics);

      virtual void helloaura_render_full_view(::draw2d::graphics_pointer & pgraphics) override;
      virtual void helloaura_render_lite_view(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void defer_update_bilbo() override;

      //::image_pointer & image23(string strDib) override;

      //virtual bool in_anime() override;
      //virtual void helloaura_fast_render(const string & strHelloBase) override;


   };


} // namespace hellobase

