#pragma once


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::bred::session
   {
   public:


      session();
      virtual ~session();


      inline ::core::system* get_system() const;
      inline ::core::user* user() const;


      void common_construct();


      virtual ::e_status initialize(::context_object * pcontextobject) override;


      inline ::core::user* user();


   };


} // namespace core




