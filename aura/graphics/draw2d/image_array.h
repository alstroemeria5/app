#pragma once


class CLASS_DECL_AURA image_array :
   virtual public __pointer_array(::image)
{
public:


   image_array();
   virtual ~image_array();


   virtual bool explode(::object * pobject, ::payload varFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);

   virtual bool explode(::object * pobject, const ::size & size, ::payload varFile, int cols, int rows, bool bCache = true, bool bCreateHelperMaps = false);


};



