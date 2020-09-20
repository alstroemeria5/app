

int main(int argc, char * argv[])
{

   //class apex_apex apex_apex;

   //{

   //   ::apex_main_struct mainstruct;

   //   application_initialize(mainstruct);

   //   {

   //      auto psystem = __new(::apex::system());

   //      psystem->set_main_struct(&mainstruct);

   //      psystem->system_construct(argc, argv);

   //      return apex_run_system(psystem);

   //   }

   //}

   auto psystem = platform_create_system(apple_get_bundle_id());

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::estatus estatus = os_application_system_run(psystem);

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;


}



