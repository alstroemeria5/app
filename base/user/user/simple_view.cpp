#include "framework.h"
#include "base/user/user/_user.h"
#include "simple_view.h"


namespace user
{


   simple_view::simple_view()
   {

   }


   simple_view::~simple_view()
   {
   }


   void simple_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

   }


   void simple_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void simple_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void simple_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }


   void simple_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      for (auto & text : m_texta)
      {

         pgraphics->set(text.m_font);

         pgraphics->set_text_color(text.m_color.get_rgba());

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->text_out(text.m_point.x, text.m_point.y, text.m_strText);

      }


   }


} // namespace user
