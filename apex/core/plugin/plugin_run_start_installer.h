﻿#pragma once


#include "apex/run_start_installer.h"


namespace plugin
{



   class run_start_installer :
      virtual public ::apex::run_start_installer
   {
   public:


      plugin * m_pplugin;


      run_start_installer(::object * pobject, plugin * pplugin);


      virtual void run_start_install(const char * pszStart);

   };


} // namespace plugin


