#pragma once


namespace process
{


   class CLASS_DECL_ACME bidi_pipe:
      virtual public ::matter
   {
   public:


      __pointer(pipe)    m_sppipeIn;
      __pointer(pipe)    m_sppipeOut;


      bidi_pipe();
      virtual ~bidi_pipe();

      virtual bool create(bool bBlock = true,bool bInherit = false);


   };


} // namespace process


































