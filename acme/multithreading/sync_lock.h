#pragma once


class CLASS_DECL_ACME sync_lock :
   public initial_single_lock
{
public:


   explicit sync_lock(sync * pobject) :
      initial_single_lock(pobject)
   {


   }


   sync_lock(matter * pobject) :
      initial_single_lock(pobject == nullptr ? nullptr : pobject->mutex())
   {

   }


};





