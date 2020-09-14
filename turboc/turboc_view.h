#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC view :
      public ::aura::impact
   {
   public:


      enum e_effect
      {

         effect_none,
         effect_crt,

      };


      e_effect                m_eeffect;
      bool                    m_bLite;

      //main_view *             m_pmainview;

      string                  m_strServer;
      ::mutex                   m_mutexWork;
      ::mutex                   m_mutexDraw;
      ::mutex                   m_mutexSwap;
      ::mutex                   m_mutexText;
      ::image_pointer        m_pimageAi1;
      ::image_pointer        m_pimageAi2;

      ::image_pointer        m_pimage1;
      ::image_pointer        m_pimage2;
      bool                    m_bDib1;
      bool                    m_bVoidTransfer;

      string                  m_strImage;
      ::image_pointer        m_pimagePost;
      ::draw2d::fastblur      m_pimageImage;
/*      ::draw2d::fastblur      m_pimage;
      ::image_pointer        m_pimageColor;
      ::image_pointer        m_pimageWork;
      ::image_pointer        m_pimageFast;
      ::image_pointer        m_pimageTemplate;

      ::draw2d::font_pointer       m_font;
      string                  m_strNewHelloMultiverse;
      string                  m_strHelloMultiverse;
      bool                    m_bOkPending;
      tick m_tickLastOk;
      tick                   m_tickAnime;
      bool                    m_bNewLayout;
      tick m_tickLastFast;
      DWORD                   m_tickFastAnime;
      bool                    m_bFast;
      bool                    m_bFirstDone;
      bool                    m_bFastOnEmpty;

      int                     m_cx;
      int                     m_cy;
      int                     m_cxCache1;
      int                     m_cyCache1;

      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;
      bool                    m_bHelloRender;


      double                  m_dMinRadius;
      double                  m_dMaxRadius;

      bool                    m_bAlternate;


      view(::layered * pobjectContext);
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_handling(::message::dispatch * pdispatch);


/*      virtual void _001OnPostProcess(::image * pimage);

/*      virtual void _006OnDraw(::image * pimage);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_update(::aura::impact * pSender, e_update eupdate, object* pHint);

      ::aura::document * get_document();

      virtual void turboc_render();
/*      virtual void turboc_render(::image * pimage);
      virtual void turboc_fast_render(const string & strHelloMultiverse);
      virtual void turboc_draw();
      virtual void full_render();

      static UINT thread_proc_render(void * pparam);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual string get_turboc();

      virtual string get_processed_turboc();

      virtual bool in_anime();


/*      virtual void turboc_render_lite_view(::image * pimage);
/*      virtual void turboc_render_full_view(::image * pimage);

   };


} // namespace turboc





















