//
//  account_credentials.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"


namespace account
{


   authenticator::authenticator(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

   }


   authenticator::~authenticator()
   {

   }


   ::estatus     authenticator::pre_authenticate(credentials * pcredentials)
   {

      return error_pre_authentication;

   }


   ::estatus  authenticator::authenticate(credentials * pcredentials)
   {

      return error_authentication_none;

   }


} // namespace account



