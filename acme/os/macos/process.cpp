//
//  process.cpp
//  acme
//
//  Created by Camilo Sasuke on 2021-05-13 18:25 BRT <3ThomasBorregaardSørensen_!!
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <spawn.h>
#include <mach-o/dyld.h>


::file::path macos_app_path(::acme_dir * pacmedir, string strApp)
{

   ::file::path path = pacmedir->home() / "Library/papplication Support/ca2/mypath" / (strApp + ".txt");

   return file_as_string(path);

}

extern char ** environ;

string_array get_c_args_for_c(const char * psz);

string transform_to_c_arg(const char * psz);

int create_process2(const char * _cmd_line, int * pprocessId);

i32 create_process(const char * pszCommandLine, i32 * pprocessId)
{

   string_array stra;
   
   stra = get_c_args_for_c(pszCommandLine);

   char * argv[1024 + 1];

   int argc = 0;

   for(auto & str : stra)
   {

      argv[argc] = (char *) str.c_str();

      argc++;

   }

   argv[argc] = nullptr;

   pid_t pid = 0;

   int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv, environ);

   int iError = errno;

   char * pszError = strerror(iError);

   if (status == 0)
   {

      if(pprocessId != nullptr)
      {

         *pprocessId = pid;

      }

      return 1;

   }
   else
   {

      return 0;

   }

}



int create_process2(const char * _cmd_line, int * pprocessId)
{
   char *   exec_path_name;
   char *   cmd_line;

   cmd_line = (char *) memory_alloc(strlen(_cmd_line ) + 1 );

   if(cmd_line == nullptr)
      return 0;

   ansi_copy(cmd_line, _cmd_line);

   if((*pprocessId = fork()) == 0)
   {
      // child
      const char      *pArg, *pPtr;
      const char      *argv[1024 + 1];
      int       argc;
      exec_path_name = cmd_line;
      if( ( pArg = ansi_find_char_reverse( exec_path_name, '/' ) ) != nullptr )
         pArg++;
      else
         pArg = exec_path_name;
      argv[0] = pArg;
      argc = 1;

      if( cmd_line != nullptr && *cmd_line != '\0' )
      {
         pArg = strtok_r(cmd_line, " ", (char **) &pPtr);
         while( pArg != nullptr )
         {
            argv[argc] = pArg;
            argc++;
            if( argc >= 1024 )
               break;
            pArg = strtok_r(nullptr, " ", (char **) &pPtr);
         }
      }
      argv[argc] = nullptr;

      execv(exec_path_name, (char * const *) argv);
      free(cmd_line);
      exit( -1 );
   }
   else if(*pprocessId == -1)
   {
      // in parent, but error
      *pprocessId = 0;
      free(cmd_line);
      return 0;
   }
   // in parent, success
   return 1;
}


CLASS_DECL_ACME ::e_status call_async(
const char * pszPath,
const char * pszParam,
const char * pszDir,
::e_display edisplay,
bool bPrivileged,
unsigned int * puiPid)
{

   string strCmdLine;

   strCmdLine = pszPath;

   if(ansi_length(pszParam) > 0)
   {

      strCmdLine +=  " ";

      strCmdLine += pszParam;

   }

   int processId;

   chdir(pszDir);

   if(!create_process(strCmdLine, &processId))
   {

      return -1;

   }

   if(puiPid != nullptr)
   {

      *puiPid = processId;

   }

   return 0;

}


CLASS_DECL_ACME ::e_status call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
{

   string strCmdLine;

   strCmdLine = pszPath;

   if(ansi_length(pszParam) > 0)
   {

      strCmdLine +=  " ";
      
      strCmdLine += pszParam;
      
   }

   int processId;

   if(!create_process(strCmdLine, &processId))
   {
      
      return -1;

   }

   set["pid"] = processId;

   while(true)
   {

      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         break;

      sleep(1_ms);

   }

   return 0;

}












bool shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout )
{
   
   property_set set;

   return call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), e_display_none, durationTimeout, set);

}

string apple_app_module_path()
{

   string str;

   char * psz = str.get_string_buffer(1024);


   u32 size = 1024;

   if(_NSGetExecutablePath(psz, &size) == 0)

   {

      str.release_string_buffer();

   }
   else
   {

      psz = str.get_string_buffer(size);


      if(_NSGetExecutablePath(psz, &size) == 0)

      {

         str.release_string_buffer();

      }
      else
      {

         return "";

      }

   }


   return str;

}

CLASS_DECL_ACME bool is_shared_library_busy(u32 processid, const string_array & stra)
{

   return false;

}


CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra)
{

   return false;

}

void os_term_application()
{
//
//   ns_app_terminate();
//
}


CLASS_DECL_ACME ::file::path core_app_path(string strApp)
{

   ::file::path path = getenv("HOME");

   path /= "Library/papplication Support/ca2/mypath" / strApp;

   path += ".txt";

   return file_as_string(path);

}


::u32 get_current_process_id()
{

    return getpid();

}



