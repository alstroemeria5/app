#pragma once



class CLASS_DECL_BASE composition_imm_client :
   virtual public imm_client
{
public:



   virtual void get_ime_composition_area(::rect & r);
   virtual bool edit_undo();


};

