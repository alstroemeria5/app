#include "framework.h"
#include "application.h"


namespace message
{


   application::application(e_application eapplication)
   {

      m_id = ::message::type_application;
      m_eapplication = eapplication;
      m_bOk = true;

   }


} // namespace message




