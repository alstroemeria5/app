#pragma once


class CLASS_DECL_ACME future :
   public ::matter_pointer
{
public:
   
   using ::matter_pointer::matter_pointer;


   inline void operator()(const var& var) const;

   inline bool should_run_async() const;


};





//using future = ::matter_pointer;





