#pragma once


class CLASS_DECL_ACME timer_callback :
   virtual public ::context_object
{
public:


   virtual bool on_timer(timer * ptimer);
   virtual bool e_timer_is_ok();


   virtual bool remove_timer(::timer* ptimer);

   virtual ::user::interaction * get_user_interaction();

   
};



