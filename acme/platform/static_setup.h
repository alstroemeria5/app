//
//  apex_app.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 18/08/19.
//  Moved from Apex to Acme on 2021-03-20 18:39 <3ThomasBS_
//
#pragma once


class node_data_exchange;


//void apex_set_get_new_application(PFN_NEW_APEX_APPLICATION pnewapplication);


class CLASS_DECL_ACME static_setup 
{
public:


   enum enum_flag
   {

      e_flag_none,
      flag_system = 1,
      flag_session = 2,
      flag_application = 4,
      flag_multimedia = 8,
      flag_library = 16,
      flag_object_user = 32,
      flag_do_not_install = 4096,

   };


   const char *                  m_pszName;
   enum_flag                        m_eflag;
   static_setup*                 m_ppropertysetupNext;


   static static_setup *         s_psetupList;


   static_setup(::static_setup::enum_flag eflag, const char * pszName);


   void construct();


   inline bool should_install() { return !has_flag(flag_do_not_install); }
   bool has_flag(::static_setup::enum_flag eflag) { return ((int)m_eflag & (int)eflag) == (int)eflag; }


   static static_setup* get_last(::static_setup::enum_flag eflag, const char* pszName = nullptr);
   static static_setup* get_first(::static_setup::enum_flag eflag, const char* pszName = nullptr);

   virtual ::matter * create_new_object();
   virtual ::matter* create_new_application();
   virtual ::acme::library* create_new_library();

   virtual ::matter* new_object();
   virtual ::matter* new_application_as_matter();
   virtual ::acme::library* new_library();


};


template < typename LIBRARY >
class static_library_factory :
   public static_setup
{
public:


   virtual ::acme::library* new_library() override { return new LIBRARY; }


   static_library_factory(const char * pszName = "") :
      static_setup(flag_library, pszName)
   {


   }


};


template < typename OBJECT >
class static_object_factory :
   public static_setup
{
public:


   virtual ::matter * new_object() override { return new OBJECT; }


   static_object_factory(::static_setup::enum_flag eflag, const char* pszName = "") :
      static_setup(eflag, pszName)
   {

   }


};


#define __namespace_library_factory(LIBRARY) \
::static_library_factory < library > TOKEN_AT_LINE(g_library_factory)(LIBRARY);
 

#define __namespace_object_factory(OBJECT, EOBJECT) \
::static_object_factory < OBJECT > TOKEN_AT_LINE(g_library_factory)(EOBJECT);


#define __namespace_system_factory(SYSTEM) \
__namespace_object_factory(SYSTEM,:: static_setup::flag_system)


#define __namespace_session_factory(SESSION) \
__namespace_object_factory(SESSION,:: static_setup::flag_session)




