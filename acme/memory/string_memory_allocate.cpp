// Created by camilo on 2021-07-23 21:53 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


CLASS_DECL_ACME void* string_memory_allocate(memsize size)
{

   return _memory_allocate(size);

}


CLASS_DECL_ACME void* string_memory_reallocate(void* p, memsize size)
{

   return _memory_reallocate(p, size);

}


CLASS_DECL_ACME void string_memory_free(void* p)
{

   _memory_free(p);

}



CLASS_DECL_ACME memsize string_memory_size(void* p);
{

   return memory_size(p, size);

}


