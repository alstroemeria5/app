#pragma once


class CLASS_DECL_ACME heap_item_array:
   public array < heap_item,heap_item >
{
public:

#ifdef _UWP
   millis m_millisLastCleanup;
#else
   millis m_millisLastCleanup;
#endif

   inline void add_item(void * p,memsize iSize)
   {
#ifdef _UWP
      add(heap_item(point,iSize,GetTickCount64()));
      if(GetTickCount64() > m_millisLastCleanup + 10000)
#else
      add(heap_item(point,iSize,::get_tick()));
      if(::get_tick() > m_millisLastCleanup + 10000)
#endif
      {
         cleanup();
      }
   }

   inline void cleanup()
   {
#ifdef _UWP
      DWORD64 dwLimit = GetTickCount64() - 1000;
#else
      DWORD64 dwLimit= ::millis::now() - 1000;
#endif
      for(i32 i = 0; i < this->get_count();)
      {
         if(dwLimit > m_pData[i].m_dwTickCount)
         {
            erase_at(i);
         }
         else
         {
            i++;
         }
      }
#ifdef _UWP
      m_millisLastCleanup = GetTickCount64();
#else
      m_millisLastCleanup= ::millis::now();
#endif
   }

   inline bool find(void * p,bool bRemove)
   {
      __UNREFERENCED_PARAMETER(bRemove);

      for(i32 mi = 0; mi < this->get_count(); mi++)
      {
         if(m_pData[mi].contains(point))
         {
            erase_at(mi);
            return true;
         }
      }
      return false;
   }


};


