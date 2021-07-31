#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO brush :
      virtual public ::draw2d::brush
   {
   public:



      brush();
      ~brush() override;


      bool create(::draw2d::graphics * pgraphics);
      ::e_status destroy() override;


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_cairo

