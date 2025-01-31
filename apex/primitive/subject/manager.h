#pragma once


namespace subject
{


   class CLASS_DECL_APEX manager :
      virtual public ::object
   {
   public:


      __pointer(::id_map<__pointer(::subject::subject)>)    m_pmapSubject;

      static critical_section                               s_criticalsection;
      // todo implement keyset
      // a hashmap of just the key (but not a value)
      // like std::set?
      static ::set < manager_pointer >                      s_managerset;
      static bool                                           s_bDestroyAll;


      manager();
      virtual ~manager();

#ifdef _DEBUG


      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif

      virtual ::subject::subject * subject(const ::id& id, const ::action_context& actioncontext = ::action_context());

      //::subject::subject_pointer fork_subject(const ::id &id);

      //virtual void process_subject(const ::id & id);
      //virtual void process_subject(const ::id & id, const ::payload & payload);
      //virtual void process_subject(const ::id & id, const ::action_context &actioncontext);

      // <3ThomasBorregaardSørensen handle...!!
      virtual void handle_subject(::subject::subject * psubject);


      //using ::property_object::on_subject;
      //void subject_handler(::subject::subject * psubject) override;
      //virtual void on_subject(::subject::subject * psubject);

      //virtual void deliver(const ::id &id);
      //virtual void deliver(const ::id &id, const ::action_context &actioncontext);

      //virtual void set_modified(const ::id &id);
      //virtual void delivery_for(const ::id &id, ::matter *pmatter, bool bForkWhenNotify = false);
      //virtual void erase_subject(const ::id &id, ::matter *pmatter);
      //static handler_pointer fork_handler(const ::id &id, ::matter *pmatter = nullptr);
      //subject_pointer subject(const ::id &id, ::matter *pmatter = nullptr);

      ::e_status destroy() override;

      //virtual void source_add(::matter* pmatter);
      //virtual void source_erase(::matter* pmatter);

      //void update_add(const ::id& id, ::matter* pmatter);
      //void update_erase(const ::id& id, ::matter* pmatter);

      void erase(::matter *pmatter);

      static void erase_from_any_source(::matter *pmatter);

      //static void __add(const ::id& id, ::matter* pmatter);

      //static void __erase(const ::id& id, ::matter* pmatter);

      static void __erase(::matter *pmatter);

      static void post_destroy_all();


   };


   /*inline ::subject::subject_pointer new_subject(::subject::subject * pmanager) { return __new(::subject::subject(pmanager)); }


   inline ::subject::subject_pointer new_subject(::subject::subject * phandler, ::matter *pmatter)
   {

      return __new(::subject::subject(phandler, pmatter));

   }*/

   
   //using manager_pointer = __pointer(promise::manager);


} // namespace subject



