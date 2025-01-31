#include "framework.h"
#include "apex/message.h"


__pointer(::mutex) channel::s_pmutexChannel;


channel::channel()
{

   channel_common_construct();

}


channel::~channel()
{

   erase_all_routes();

}


void channel::install_message_routing(::channel* pchannel)
{

   ::object::install_message_routing(pchannel);

}




void channel::erase_receiver(::object * preceiver)
{

   synchronous_lock synchronouslock(channel_mutex());

   for (auto & pair : m_handlermap)
   {

      if (pair.element2().is_empty())
      {

         continue;

      }

      pair.element2().predicate_erase([=](auto & item)
      {

         return item.m_preceiver == preceiver;

      });

   }


}


void channel::transfer_receiver(::message::handler_map & handlermap, ::object * preceiver)
{

   synchronous_lock synchronouslock(channel_mutex());

   for (auto & pair : m_handlermap)
   {

      if (pair.element2().is_empty())
      {

         continue;

      }

      pair.element2().predicate_each([&](auto & item)
      {

         if (item.m_preceiver == preceiver)
         {

            auto & routera = handlermap[pair.element1()];

            routera.add(item);

         }

      });

      pair.element2().predicate_erase([&](auto & item)
      {

         return item.m_preceiver == preceiver;

      });

   }

}


void channel::route_message(::message::message * pmessage)
{

   if (::is_null(pmessage)) { ASSERT(false); return; } { synchronous_lock synchronouslock(channel_mutex()); pmessage->m_phandlera = m_handlermap.pget(pmessage->m_id); } if(pmessage->m_phandlera == nullptr || pmessage->m_phandlera->is_empty()) return;

   for(pmessage->m_pchannel = this, pmessage->m_iRouteIndex = pmessage->m_phandlera->get_upper_bound(); pmessage->m_iRouteIndex >= 0; pmessage->m_iRouteIndex--)
   {

      pmessage->m_phandlera->m_pData[pmessage->m_iRouteIndex].m_handler(pmessage); if(pmessage->m_bRet) return;

   }

}


__pointer(::message::message) channel::get_message(MESSAGE * pmessage)
{

   auto pmessagemessage = __new(::message::message);

   pmessagemessage->set(
      pmessage->oswindow, 
      nullptr,
      pmessage->m_id, 
      pmessage->wParam, 
      pmessage->lParam);

   return pmessagemessage;

}


//__pointer(::message::message) channel::get_message(const ::id & id, wparam wparam, lparam lparam, const ::point_i32 & point)
__pointer(::message::message) channel::get_message(const ::id& id, wparam wparam, lparam lparam)
{

   auto pmessagemessage = __new(::message::message);

   pmessagemessage->set(
      nullptr,
      nullptr,
      id,
      wparam,
      lparam);

   return pmessagemessage;

}


//__pointer(::user::message) channel::get_message_base(::windowing::window * pwindow, const ::id & id, wparam wparam, lparam lparam)
//{
//
//   if (id.m_etype != ::id::e_type_message)
//   {
//
//      __throw(error_invalid_argument);
//
//   }
//
//   MESSAGE msg;
//
//   __zero(msg);
//
//   msg.message = (::u32) id.m_emessage;
//   msg.wParam = wparam;
//   msg.lParam = lparam;
//
//   return get_message_base(&msg);
//
//}


//#ifdef LINUX
//
//
//__pointer(::user::message) channel::get_message_base(void * pevent,::user::interaction * puserinteraction)
//{
//
//   __throw(todo);
//
//   return nullptr;
//
//}
//
//
//#endif




void channel::erase_all_routes()
{

   try
   {

      _synchronous_lock synchronouslock(channel_mutex());

      if(m_bNewChannel)
      {

         m_handlermapNew = m_handlermap;

         m_bNewChannel = false;

      }

      m_handlermap.erase_all();

//         for (auto & id_route_array : m_idroute)
//         {
//
//            if (id_route_array.element2().is_null())
//            {
//
//               continue;
//
//            }
//
//            id_route_array.element2()->predicate_each([=](auto & route)
//            {
//
//               try
//               {
//
//                  synchronous_lock synchronouslock(route->m_preceiver->m_pmutexChannel);
//
//                  route->m_preceiver->m_sendera.erase(this);
//
//               }
//               catch (...)
//               {
//
//               }
//
//            });
//
//            id_route_array.element2()->erase_all();
//
//         }
//

   }
   catch (...)
   {

   }

}


void channel::channel_common_construct()
{

   m_bNewChannel = true;

}


::e_status channel::destroy()
{

   if (m_pchannel && m_pchannel != this)
   {

      m_pchannel->destroy();

   }

   m_pchannel.release();

   m_idaHandledCommands.erase_all();

   m_handlermap.erase_all();

   m_handlermapNew.erase_all();

   for (auto& procedurea : m_routinemap.values())
   {

      procedurea.destroy();

      procedurea.erase_all();

   }

   m_routinemap.erase_all();

   ::object::destroy();

   return ::success;

}


::e_status channel::handle(::message::command * pcommand)
{

   return pcommand->handle(this);

}


void channel::BeginWaitCursor()
{

}


void channel::EndWaitCursor()
{

}


void channel::RestoreWaitCursor()
{

}





void channel::_001SendCommand(::message::command * pcommand)
{

   pcommand->m_pchannel = this;

   {

      __scoped_restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command);

      route_command_message(pcommand);

   }

}


void channel::_001SendCommandProbe(::message::command * pcommand)
{

   pcommand->m_pcommandtargetSource = this;

   {

      __scoped_restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command_probe);

      route_command_message(pcommand);

   }

}


void channel::route_command_message(::message::command * pcommand)
{

   on_command_message(pcommand);

}


void channel::on_command_message(::message::command * pcommand)
{

   if (pcommand->is_command())
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

      if (!pcommand->m_bEnableChanged
         && !pcommand->m_bRadioChanged
         && pcommand->m_echeck == check_undefined
         && !pcommand->m_bHasCommandHandler)
      {

         return;

      }

      on_command(pcommand);

   }
   else if (pcommand->m_id.is_command_probe())
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

   }
   else if (pcommand->m_id.is_command())
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

   }
   else
   {

      __throw(error_not_implemented);

   }

}


void channel::on_command(::message::command * pcommand)
{

   {

      __scoped_restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command);

      route_message(pcommand);

   }

}


bool channel::has_command_handler(::message::command * pcommand)
{

   synchronous_lock synchronouslock(channel_mutex());

   __scoped_restore(pcommand->m_id.m_etype);

   pcommand->m_id.set_compounded_type(::id::e_type_command);

   if (m_idaHandledCommands.contains(pcommand->m_id))
   {

      return true;

   }

   auto passoc = m_handlermap.plookup(pcommand->m_id);

   if (::is_null(passoc))
   {

      return false;

   }

   if (passoc->m_element2.is_empty())
   {

      return false;

   }

   if (passoc->element2().is_empty())
   {

      return false;

   }

   return true;

}


void channel::on_command_probe(::message::command * pcommand)
{

   {

      __scoped_restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command_probe);

      route_message(pcommand);

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      pcommand->m_bRet =
         pcommand->m_bEnableChanged
         || pcommand->m_bRadioChanged
         || pcommand->m_echeck != check_undefined;

   }

}


bool channel::_add_handler(const ::id & id, ::object * preceiver, void * phandler, const ::message::handler & handler)
{

    auto & handlera = m_handlermap[id];

    if(preceiver != nullptr || phandler != nullptr)
    {

        for (::index i = 0; i < handlera.get_count(); i++)
        {

            if (handlera.element_at(i).m_preceiver == preceiver
                && handlera.element_at(i).m_pHandler == (void *) phandler)
            {

                return false;

            }

        }

    }

    ::message::handler_item handleritem(preceiver, phandler);

    handleritem.m_handler = handler;

    handlera.add(handleritem);

    return true;

}


::e_status channel::id_notify(const ::id & id, ::matter * pmatter)
{

    auto & routinea = m_routinemap[id];

    routinea.add(pmatter); // pmatter is notified with id

    return ::success;

}


void channel::on_property_changed(property * pproperty, const ::action_context& actioncontext)
{

   auto psubject = subject(pproperty->m_id);

   psubject->m_actioncontext = actioncontext;

   handle_subject(psubject);

   //process_subject(pproperty->m_id, actioncontext);

}


void channel::default_toggle_check_handling(const ::id & id)
{

   auto linkedproperty = fetch_property(id);

   connect_command_predicate(id, [linkedproperty](::message::message * pmessage)
      {

         if (linkedproperty->get_bool())
         {

            *linkedproperty = ::check_unchecked;

         }
         else
         {

            *linkedproperty = ::check_checked;

         }

         linkedproperty.notify_property_changed(pmessage->m_actioncontext);

         pmessage->m_bRet = true;

      });

}










