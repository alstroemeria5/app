#pragma once


//CLASS_DECL_ACME void main_async_runnable(::context_object * pobjectTask);
//CLASS_DECL_ACME void main_sync_runnable(::context_object * pobjectTask, ::duration durationTimeout = one_minute());


#define new ACME_NEW
//
//
//template < typename PRED >
//class predicate_method :
//   virtual public ::matter
//{
//public:
//
//
//   PRED   m_predicate;
//
//
//   predicate_method(PRED pred) :
//      m_predicate(pred)
//   {
//
//   }
//
//
//   virtual ~predicate_method()
//   {
//
//
//   }
//
//
//   virtual ::e_status run() override
//   {
//
//      m_predicate();
//
//      return ::success;
//
//   }
//
//
//   void receive_response(const ::payload&) override
//   {
//
//      __throw(interface_only_exception());
//
//   }
//
//
//
//};
//



template < typename PRED >
class predicate_handler :
   virtual public ::matter
{
public:


   PRED m_predicate;


   predicate_handler(PRED pred) : m_predicate(pred) { }
   virtual ~predicate_handler() {}
   //method(const ::matter_pointer & pmatter) : matter_pointer(pmatter) { }
   //method(const ::method & method) : matter_pointer(method) { }


   //inline ::e_status operator()() const;

   virtual void operator()(::message::message * pmessage) override
   {

      m_predicate(pmessage);

   }

   //template < typename PRED >
   //void pred(PRED pred);

   //inline method & operator = (const ::method & method) { m_pmatter = method.m_pmatter; return *this; }
   //method & operator = (const ::payload & payload);


};


template < typename PRED >
::promise::handler __handler(PRED pred) {

    return __new(predicate_handler<PRED>(pred));

}



template < typename TYPE >
class CLASS_DECL_ACME typed_handler :
    virtual public ::matter
{
public:

    TYPE * m_p;
    void(TYPE::*m_phandler)(::message::message *);

    typed_handler():
            m_p(nullptr),
            m_phandler(nullptr)
    {

    }


    typed_handler(TYPE * p, void(TYPE::*phandler)(::message::message *)):
            m_p(p),
            m_phandler(phandler)
    {

    }


    virtual void operator()(::message::message * pmessage)
    {

        (m_p->*m_phandler)(pmessage);

    }


};


template < typename TYPE >
::promise::handler __handler(TYPE * p, void(TYPE::*phandler)(::message::message *))
{

    return __new(::typed_handler<TYPE>(p, phandler));

}

//
//
//
//
//::e_status run_task(::matter * pobjectTask);
//
//
//class processor
//{
//public:
//
//   virtual void schedule(::matter * pobjectTask, e_priority epriority = priority_normal) = 0;
//
//};
//
//
//template < typename PRED >
//inline auto schedule(processor * pprocessor, PRED pred, e_priority epriority = priority_normal)
//{
//
//   auto pobjectTask = create_predicate(pred);
//
//   pprocessor->schedule(pobjectTask, epriority);
//
//   return pobjectTask;
//
//}
//
////
////template < typename PRED >
////auto sync_predicate(void (* pfnBranch )(::object * pobjectTask, e_priority), PRED pred, ::duration durationTimeout = one_minute(), e_priority epriority = priority_normal);
//
//
//
//
//
//
//
//
//
////CLASS_DECL_ACME void main_branch(::matter * pobjectTask, e_priority epriority);
//
//
//
//
//
//
//
//
//
//template < typename TYPE >
//inline auto __runnable_method(TYPE * p, void (TYPE:: * pmethod)())
//{
//
//   return __runnable([p, pmethod]
//   {
//
//      (p->*pmethod)();
//
//   });
//
//}
//
//
//
