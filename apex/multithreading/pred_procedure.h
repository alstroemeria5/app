#pragma once


CLASS_DECL_APEX void main_async_runnable(::generic * pobjectTask);
CLASS_DECL_APEX void main_sync_runnable(::generic * pobjectTask, ::duration durationTimeout = one_minute());
CLASS_DECL_APEX void main_branch(::generic* pobjectTask, e_priority epriority);


::estatus run_task(::generic * pobjectTask);








template < typename PRED >
inline void main_async(PRED pred, e_priority epriority = priority_normal)
{

   async_pred(&main_branch, pred, epriority);

}


template < typename PRED >
inline void main_sync(PRED pred, ::duration durationTimeout = one_minute(), e_priority epriority = priority_normal)
{

   sync_pred(&main_branch, pred, durationTimeout, epriority);

}


