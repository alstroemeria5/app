#ifdef RASPBIAN

#define AXIS_MEMORY_MANAGEMENT true

#else

#define AXIS_MEMORY_MANAGEMENT true

#endif


CLASS_DECL_ACME void simple_debug_print(const char* psz);


namespace HEAP_NAMESPACE
{

#if !AXIS_MEMORY_MANAGEMENT


#include "heap_bare.cpp"


#else


#ifdef LINUX


#include <malloc.h>


#endif


#include "align_byte_count.h"


//#include "acme/platform/static_start.h"


#ifdef MCHECK


#include "heap_mcheck.cpp"


#elif defined(_VLD)


#include "heap_vld.cpp"


#elif defined(__MCRTDBG)


#include "heap_mcrtdbg.cpp"


#elif MEMDLEAK


#include "heap_memdleak.cpp"


#else


#include "inline/heap_std.cpp"


#endif


#endif


   #include "inline/plex.cpp"
   #include "inline/plex_heap.cpp"


   plex_heap_alloc_array* g_pheap = nullptr;


   critical_section* g_pmutexSystemHeap = nullptr;


   void initialize()
   {

      g_pheap = new plex_heap_alloc_array();

   }


   void finalize()
   {

      ::acme::del(g_pheap);

   }

} // namespace HEAP_NAMESPACE



