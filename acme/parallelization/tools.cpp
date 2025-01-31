#include "framework.h"


task_tool::task_tool()
{

   defer_create_mutex();

}


task_tool::~task_tool()
{

}


task_group::task_group(::matter * pmatter, ::enum_priority epriority)
{

   defer_create_mutex();

   //auto estatus = initialize(pmatter);

   //if (!estatus)
   //{

   //   __throw(estatus);

   //}

   m_epriority                      = epriority;
   m_cCount                         = 0;
   m_cIteration                     = 0;
   m_cSpan                          = 0;

   int cOrder = get_current_process_affinity_order();

   auto iPreviousSize = m_taska.get_size();

   m_taska.set_size(cOrder);

   for(index iThread = iPreviousSize; iThread < cOrder ; iThread++)
   {

      auto & ptooltask = m_taska[iThread];

      ptooltask = __create_new < ::tool_task >();

      ptooltask->initialize_tool_task(this);

      m_synchronizationa.add(ptooltask->m_pevReady);

      ptooltask->m_iThread = iThread;

      ptooltask->m_uThreadAffinityMask = translate_processor_affinity((int) (ptooltask->m_iThread));

      if (epriority == ::e_priority_none)
      {

         ptooltask->branch(::e_priority_highest);

      }
      else
      {

         ptooltask->branch(epriority);

      }

   }

}


task_group::~task_group()
{


}


bool task_group::prepare(::enum_task_op etaskop, ::count cIteration)
{

   synchronous_lock synchronouslock(mutex());

   for (auto & ptask : m_taska)
   {

      ptask->reset();

   }

   if (etaskop == ::e_task_op_predicate || etaskop == ::e_task_op_fork_count)
   {

      m_cCount = 0;

   }
   else
   {

      m_cCount = minimum(m_taska.get_count(), cIteration);

   }

   m_etaskop = etaskop;

   m_cIteration = cIteration;

   m_cSpan = maximum(1, cIteration / get_count());

   return true;

}


//bool task_groupet::add_tool(::task_tool * ptool)
//{
//
//   add(ptool);
//
//   ptool->m_ptoolset = this;
//
//   return true;
//
//}


bool task_group::add_predicate(::predicate_holder_base * ppred)
{

   synchronous_lock synchronouslock(mutex());

   if ((m_etaskop != ::e_task_op_predicate && m_etaskop != ::e_task_op_fork_count) || is_full())
   {

      return false;

   }

   if (is_full())
   {

      return false;

   }

   m_taska[m_cCount]->set_predicate(ppred);

   m_cCount++;

   return true;

}


::e_status task_group::set_ready_to_start()
{

   synchronous_lock synchronouslock(mutex());

   if (m_cCount <= 0)
   {

      return false;

   }

   m_cSpan = m_cIteration / m_cCount;

   ::count cSuccess = 0;

   ::count cFailed = 0;

   for (index i = 0; i < m_cCount; i++)
   {

      auto estatusTask = m_taska[i]->set_ready_to_start();

      if(estatusTask.succeeded())
      {

         cSuccess++;

      }
      else
      {

         cFailed++;

      }

   }

   auto estatus = _003CountStatus(cSuccess, cFailed);

   return true;

}


bool task_group::wait()
{

   //synchronous_lock synchronouslock(mutex());

   //if (m_cCount <= 0)
   //{

   //   return false;

   //}

   //multi_lock ml(m_cCount, m_synchronizationa);

   //synchronouslock.unlock();

   return m_synchronizationa.wait(5_s).succeeded();

}


bool task_group::process()
{

   set_ready_to_start();

   wait();

   return true;

}

//bool task_group::select_toolset(task_group * pset)
//{
//
//   m_ptoolset = pset;
//
//   return true;
//
//}











tool_task::tool_task()
{

   defer_create_mutex();


}


::e_status tool_task::initialize_tool_task(::task_group* pgroup)
{

   //auto estatus = initialize(pgroup);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_pgroup = pgroup;

   m_iIndex = 0;
   m_pevStart = __new(manual_reset_event());
   m_pevReady = __new(manual_reset_event());

   //return estatus;

   return ::success;

}


bool tool_task::set_predicate(::predicate_holder_base * ppred)
{

   try
   {

      ppred->m_ptooltask = this;

      m_ppred = ppred;

      return true;

   }
   catch (...)
   {

   }

   return false;

}


::e_status tool_task::run()
{

   try
   {

      while (task_get_run())
      {

         if (!m_pevStart->wait(millis(300)).succeeded())
         {

            continue;

         }

         m_pevStart->ResetEvent();

         if (m_pgroup->m_etaskop == ::e_task_op_predicate || m_pgroup->m_etaskop == ::e_task_op_fork_count)
         {

            m_ppred->run();

         }
         else if (m_pgroup->m_etaskop == ::e_task_op_tool)
         {

            m_pitem->run();

         }

         m_pevReady->SetEvent();

      }

   }
   catch (...)
   {

   }

   m_pevReady->SetEvent();

   return ::success;

}


void tool_task::reset()
{

   m_pevStart->ResetEvent();

   m_pevReady->ResetEvent();

}


::e_status tool_task::set_ready_to_start()
{

   m_pevStart->SetEvent();

   return ::success;

}


//CLASS_DECL_ACME ::task_group * get_task_group(::enum_priority epriority)
//{
//
//   return  ::apex::get_system()->tools(epriority);
//
//}
//
//
//CLASS_DECL_ACME ::task_groupet * get_task_groupet(::enum_task_tool etool)
//{
//
//   return ::apex::get_system()->toolset(etool);
//
//}


task_tool_item::task_tool_item()
{

}


task_tool_item::~task_tool_item()
{

}


::e_status task_tool_item::run()
{

   return ::success;

}


void task_group::select_tool(task_tool* ptool)
{

   m_etaskop = ::e_task_op_tool;

   ptool->m_itema.set_size(m_taska.get_size());

   for (index i = 0; i < task_count(); i++)
   {

      auto & ptask = task_at(i);

      auto & pitem = ptool->item_at(i);

      pitem = ::__id_create < ::task_tool_item > (ptool->m_id);

      pitem->m_ptask = ptask;

      pitem->m_ptool = ptool;

      ptask->m_pitem = pitem;

      ptask->m_ptool = ptool;

      ptask->m_pgroup = this;

   }

   m_ptool = ptool;

}


//bool task_groupet::prepare(::count cIteration)
//{
//
//   if (!m_ptasktools->prepare(::task::op_tool, cIteration))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


//predicate_set::predicate_set(::task_group * ptools) :
//   matter(ptools->get_application()),
//   m_ptasktools(ptools)
//{
//
//
//}
//
//bool predicate_set::add_predicate(::predicate_holder_base * ppred)
//{
//
//   ppred->m_ppropertyset = this;
//
//   add(ppred);
//
//   return true;
//
//}
//
//
//
//



