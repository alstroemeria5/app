#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_list_view :
      virtual public ::user::show < ::user::menu_list_window >
   {
   public:


      typedef ::user::show <  ::user::menu_list_window  > BASE;


      menu_list_view();
      virtual ~menu_list_view();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual bool pre_create_window(::user::system * pusersystem) override;

      virtual void route_command_message(::message::command * pcommand) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void post_non_client_destroy() override;


   };


} // namespace user



