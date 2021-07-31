#pragma once



namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO pen :
      virtual public ::draw2d_cairo::object,
      virtual public ::draw2d::pen
   {
   public:


      pen();
      ~pen() override;


      virtual bool create(::draw2d::graphics * pgraphics);
      virtual ::e_status destroy();


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_cairo





