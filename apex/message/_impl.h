#pragma once


#define MESSAGE_LINK(id, pchannel, preceiver, phandler) \
   pchannel->add_route(preceiver, phandler, id)

#define ON_TYPED_MESSAGE(id, MESSAGE, name) \
   this->get_typed_route < typename ::remove_reference < decltype(*this) >::TYPE, MESSAGE >(id, this) = [this](MESSAGE * p ## name)

#define ON_MESSAGE(id) \
   ON_TYPED_MESSAGE(id, ::message::message, message)

#define ON_WM_SHOWWINDOW \
   ON_TYPED_MESSAGE(WM_SHOWWINDOW, ::message::show_window, showwindow)

#define ON_WM_LBUTTONDOWN \
   ON_TYPED_MESSAGE(e_message_lbutton_down, ::message::mouse, mouse)

#define ON_WM_LBUTTONUP \
   ON_TYPED_MESSAGE(e_message_lbutton_up, ::message::mouse, mouse)

#define ON_WM_MBUTTONDOWN \
   ON_TYPED_MESSAGE(WM_MBUTTONDOWN, ::message::mouse, mouse)

#define ON_WM_MBUTTONUP \
   ON_TYPED_MESSAGE(WM_MBUTTONUP, ::message::mouse, mouse)

#define ON_WM_RBUTTONDOWN \
   ON_TYPED_MESSAGE(e_message_rbutton_down, ::message::mouse, mouse)

#define ON_WM_RBUTTONUP \
   ON_TYPED_MESSAGE(e_message_rbutton_up, ::message::mouse, mouse)

#define ON_WM_MOUSEMOVE \
   ON_TYPED_MESSAGE(e_message_mouse_move, ::message::mouse, mouse)

#define SCAST_MSG(tcast) \
   ::message::tcast * p##tcast = dynamic_cast < ::message::tcast * > (pmessage);



