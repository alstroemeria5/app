#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC lite_view:
      virtual public impact
   {
   public:


      lite_view(::object * pobject);
      virtual ~lite_view();

      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pHint);

      virtual void turboc_render(::draw2d::graphics * pdcFull);

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

   };


} // namespace turboc












