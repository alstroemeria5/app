#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE frame : 
      public simple_frame_window
   {
   public: 


      
      
      __pointer(image_list)               m_pimagelist;
      bool                       m_bTimerOn;


      frame(::layered * pobjectContext);
      virtual ~frame();

      virtual bool pre_create_window(::user::system * pusersystem);

      void ShowControlBars(bool bShow);
      
      
   
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   

      DECL_GEN_SIGNAL(on_message_create);
      void OnTimer(::u32 uEvent);

   };

} // namespace calculator




