#include "framework.h"


namespace subject
{


   critical_section manager::s_criticalsection;
   ::set<manager_pointer > manager::s_managerset;
   bool manager::s_bDestroyAll = false;


   //manager::manager()
   //{

   //}


   //manager::~manager()
   //{


   //}


   ::subject::subject * manager::subject(const ::id & id)
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_pmapSubject)
      {

         m_pmapSubject = __new(::id_map<__pointer(::subject::subject)>);

      }

      auto & psubject = m_pmapSubject->operator[](id);

      if(::is_null(psubject))
      {

         psubject = __new(::subject::subject(this, id));

         synchronouslock.unlock();

         start_subject_handling(id);

      }

      return psubject;

   }


   ::subject::subject_pointer manager::fork_subject(const ::id & id)
   {

      auto psubject = this->subject(id);

      return psubject;

   }


   ::subject::subject * manager::start_subject_handling(const ::id &id)
   {

      auto psubject = this->subject(id);

      psubject->defer_create_mutex();

      psubject->m_millisSleep = os_get_system_update_poll_time(id);

      process(psubject);

      //auto pnode = Node;

      auto psystem = m_psystem->m_papexsystem;

      auto pnode = psystem->node();

      if(pnode && pnode->defer_launch_on_node(psubject))
      {

      }
      else if (psubject->should_poll(psubject->poll_time()))
      {

         m_pcontext->branch(psubject);

      }

      return psubject;

   }


   void manager::erase_from_any_source(::matter* pmatter)
   {

//      void matter::erase_from_any_source()
  //    {

         ::subject::manager::__erase(pmatter);

    //  }


   }

   void manager::deliver(const ::id &id)
   {

      auto psubject = subject(id);

      if(psubject)
      {

         psubject->deliver();

      }

   }


   void manager::deliver(const ::id &id, const ::action_context &actioncontext)
   {

      subject(id)->deliver(actioncontext);

   }


   void manager::process_subject(const ::id &id)
   {

      auto psubject = subject(id);

      process(psubject);

   }


   void manager::process_subject(const ::id &id, const ::action_context &actioncontext)
   {

      auto psubject = subject(id);

      psubject->m_actioncontext = actioncontext;

      process(psubject);

   }

   
   void manager::process(::subject::subject * psubject)
   {

      psubject->m_esubject = e_subject_prepare;

      on_subject(psubject);

   }


   void manager::on_subject(::subject::subject * psubject)
   {

      if (psubject->m_esubject == e_subject_prepare)
      {

         //on_subject(psubject);

      }

      if (psubject->m_esubject == e_subject_process)
      {

         //on_subject(psubject);

      }

      if (psubject->m_esubject == e_subject_deliver)
      {

         psubject->deliver();

      }

   }


   void manager::process_subject(const ::id &id, const ::payload & payload)
   {

      auto psubject = subject(id);

      psubject->m_payload = payload;

      process(psubject);

   }


   void manager::set_modified(const ::id &id)
   {

      auto psubject = subject(id);

      if (::is_set(psubject))
      {

         psubject->set_modified();

      }

   }


   void manager::delivery_for(const ::id &id, ::matter *pmatter, bool bForkWhenNotify)
   {

      auto psubject = subject(id);

      if (::is_set(psubject))
      {

         psubject->add(pmatter, bForkWhenNotify);

      }

   }


   void manager::erase_subject(const ::id &id, ::matter *pmatter)
   {

      subject(id)->erase(pmatter);

   }


   //subject_pointer manager::subject(const ::id &id, ::matter *pmatter)
   //{


   //   auto psubject = __new(::subject::subject(id, pmatter));

   //   return psubject;

   //}


//   action_pointer source::subject::subject(const ::id &id, ::matter *pmatter)
//   {
//
//      auto pupdate = update(id);
//
//      auto psubject = ::new_action(pupdate, pmatter);
//
//      return psubject;
//
//   }


   ::e_status manager::finalize()
   {

      property_object::finalize();

      m_pmapSubject.release();

      return ::success;

   }


   void manager::erase(::matter *pmatter)
   {

      synchronous_lock synchronouslock(mutex());

      for (auto &pupdate : m_pmapSubject->values())
      {

         pupdate->m_mattercontext.erase_key(pmatter);

      }

   }


   void manager::__erase(::matter *pmatter)
   {

      critical_section_lock synchronouslock(&s_criticalsection);

      for (auto & manager : s_managerset)
      {

         manager.element()->erase(pmatter);

      }

   }


   void manager::post_destroy_all()
   {

      s_bDestroyAll = true;

   }


} // namespace promise






#include "framework.h"
#include "acme/platform/static_start.h"


namespace subject
{


#undef new


 

   //manager::manager(::subject::manager * pmanager, const ::id & id) :
   //   m_pbacking(pbacking)
   //{

   //   //m_id = id;

   //   m_iUpdateSerial = -1;

   //}


   //manager::~manager()
   //{

   //}


#ifdef DEBUG


   i64 manager::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::property_object::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 manager::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::property_object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 manager::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::property_object::release(OBJ_REF_DBG_ARGS);

   }


#endif







   //void manager::process(const ::action_context & actioncontext)
   //{

   //   ::subject::subject subject(m_id, actioncontext);

   //   m_pbacking->process(&subject);

   //}


   //void manager::process()
   //{

   //   ::subject::subject subject(this);

   //   m_pbacking->process(&subject);

   //}


   //void manager::process(const ::payload & payload)
   //{

   //   ::subject::subject subject(this);

   //   subject.m_var = payload;

   //   m_pbacking->process(&subject);


   //   //for (auto& matterchange : m_matterchange)
   //   //{

   //   //   auto& pmatter = matterchange.m_element1;
   //   //
   //   //   auto& pchange = matterchange.m_element2;

   //   //   ::subject::subject action(this, pchange, pmatter);

   //   //   pchange->apply(&action);

   //   //}

   //}




} // namespace subject


