#include "framework.h"
//#include "_linux.h"
////#include "acme/platform/app_core.h"
//#include <sys/types.h>
//#include <unistd.h>
//#include <signal.h>
//#undef USE_MISC
//
//#include <sys/wait.h>
//#include <spawn.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include "node.h"
//
//int create_process6(const char * _cmd_line, int * pprocessId);
//
//CLASS_DECL_ACME void dll_processes(u32_array & dwa, string_array & straProcesses, const char * pszDll)
//{
//
//   __UNREFERENCED_PARAMETER(dwa);
//   __UNREFERENCED_PARAMETER(straProcesses);
//   __UNREFERENCED_PARAMETER(pszDll);
//
//}
//
//
//
//
//i32 create_process(const char * pszCommandLine, i32 * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(pszCommandLine);
//
//   address_array < char * > argv;
//
//   for(auto & str : stra)
//   {
//
//      argv.add((char *) str.c_str());
//
//   }
//
//   argv.add(nullptr);
//
//   pid_t pid = 0;
//
//   string strExe = argv[0];
//
//   int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv.get_data(), environ);
//
//   if (status == 0)
//   {
//
//      if(strExe.ends_ci("_app_core_clockverse"))
//      {
//
//         ::output_debug_string("app-core/clockverse");
//
//      }
//
//      if(pprocessId != nullptr)
//      {
//
//         *pprocessId = pid;
//
//      }
//
//      return 1;
//
//   }
//   else
//   {
//
//      if(strExe.ends_ci("_app_core_clockverse"))
//      {
//
//         ::output_debug_string("app-core/clockverse");
//
//      }
//
//      return 0;
//
//   }
//
//}
//
//
//i32 create_process3(const char * _cmd_line, i32 * pprocessId)
//{
//
//   char *   exec_path_name;
//
//   char *	cmd_line;
//
//   char *	cmd_line2;
//
//   cmd_line = strdup(_cmd_line);
//
//   if(cmd_line == nullptr)
//   {
//
//      return 0;
//
//   }
//
//   char *      argv[1024 + 1];
//
//   i32		argc = 0;
//
//   prepare_argc_argv(argc, argv, cmd_line);
//
//   pid_t pid;
//
//   int status;
//
//   status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv, environ);
//
//   free(cmd_line);
//
//   if (status == 0)
//   {
//
//      return 1;
//
//   }
//   else
//   {
//
//      return 0;
//
//   }
//
//}
//
//
//i32 daemonize_process(const char * pszCommandLine, i32 * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(pszCommandLine);
//
//   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));
//
//   int argc = 0;
//
//   for(auto & str : stra)
//   {
//
//      argv[argc] = strdup((char *) str.c_str());
//
//      argc++;
//
//   }
//
//   argv[argc] = nullptr;
//
//   pid_t pid;
//
//   pid = fork();
//
//   if (pid == -1)
//   {
//
//      printf("fork error\n");
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      return 0;
//
//   }
//   else if(pid > 0)
//   {
//
//      return 1;
//
//   }
//
//   daemon(0, 0);
//
////   signal(SIGCHLD, SIG_IGN);
////
////   umask(0);
////
////   int sid = setsid();
////
////   if (sid < 0)
////   {
////
////      exit(EXIT_FAILURE);
////
////   }
////
////    /* Change the current working directory.  This prevents the current
////       directory from being locked; hence not being able to erase it. */
////   if ((chdir("/")) < 0)
////   {
////
////      exit(EXIT_FAILURE);
////
////   }
////
////   /* Redirect standard files to /dev/null */
////   freopen( "/dev/null", "r", stdin);
////   freopen( "/dev/null", "w", stdout);
////   freopen( "/dev/null", "w", stderr);
//
//   int iExitCode = execv(argv[0], argv);
//
//   char ** pargv = argv;
//
//   while(*pargv != nullptr)
//   {
//
//      free(*pargv);
//
//      pargv++;
//
//   }
//
//   free(argv);
//
//   exit(iExitCode);
//
//
//   return 0;
//
//}
//
//
//i32 create_process4(const char * pszCommandLine, i32 * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(pszCommandLine);
//
//   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));
//
//   int argc = 0;
//
//   for(auto & str : stra)
//   {
//
//      argv[argc] = strdup((char *) str.c_str());
//
//      argc++;
//
//   }
//
//   argv[argc] = nullptr;
//
//   if((*pprocessId = fork()) == 0)
//   {
//
//      execv(argv[0], argv);
//
//      int status = 0;
//
//      wait(&status);
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      exit(status);
//
//   }
//   else if(*pprocessId == -1)
//   {
//
//      *pprocessId = 0;
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      return 0;
//
//   }
//
//   return 1;
//
//}
//
//
//CLASS_DECL_ACME ::e_status call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
//{
//
//   string strCmdLine;
//
//   strCmdLine = pszPath;
//
//   if(ansi_length(pszParam) > 0)
//   {
//
//      strCmdLine +=  " ";
//
//      strCmdLine += pszParam;
//
//   }
//
//   i32 processId;
//
//   if(!create_process(strCmdLine, &processId))
//   {
//
//      if(puiPid != nullptr)
//      {
//
//         *puiPid = -1;
//
//      }
//
//      return -1;
//
//   }
//
//   if(puiPid != nullptr)
//   {
//
//      *puiPid = processId;
//
//   }
//
//   return 0;
//
//}
//
//
//CLASS_DECL_ACME ::e_status call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
//{
//
//   string strCmdLine;
//
//   strCmdLine = pszPath;
//
//   if(ansi_length(pszParam) > 0)
//   {
//
//      strCmdLine +=  " ";
//
//      strCmdLine += pszParam;
//
//   }
//
//   i32 processId;
//
//   if(!create_process(strCmdLine, &processId))
//   {
//
//      set["pid"] = processId;
//
//      return -1;
//
//   }
//
//
//   while(true)
//   {
//
//      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
//      {
//
//         break;
//
//      }
//
//      sleep(1_ms);
//
//   }
//
//   set["pid"] = processId;
//
//   return 0;
//
//}
//
//
//string module_path_from_pid(unsigned int iPid)
//{
//
//   struct stat sb;
//
//   int iSize;
//
//   string str;
//
//   str = "/proc/" + __str(iPid) + "/exe";
//
//   memory mem;
//
//   ssize_t s;
//
//   bool iTry;
//
//   if(lstat(str, &sb) == -1)
//   {
//
//retry:
//
//      iSize = 1024 * 4;
//
//      iTry = 1;
//
//      sb.st_size = iSize - 1;
//
//   }
//   else
//   {
//
//      iSize = sb.st_size + 1;
//
//      iTry = 0;
//
//   }
//#if MEMDLEAK
//   mem.m_strTag = "memory://function=module_path_from_pid";
//#endif
//   mem.set_size(iSize);
//
//   s = readlink (str, (char *) mem.get_data(), iSize);
//
//   if(s > sb.st_size)
//   {
//
//      if(iTry <= 0)
//      {
//
//         goto retry;
//
//      }
//      else
//      {
//
//         return "";
//
//      }
//
//   }
//
//   mem.get_data()[s] = '\0';
//
//   return (const char *) mem.get_data();
//
//}
//
//
//int_array module_path_get_pid(const char * pszPath)
//{
//
//   int_array ia;
//
//   ::file::patha stra;
//
//   ::dir::ls_dir(stra, "/proc/");
//
//   for(auto & strPid : stra)
//   {
//
//      int iPid = atoi(strPid.title());
//
//      if(iPid > 0)
//      {
//
//         string strPath =module_path_from_pid(iPid);
//
//         if(strPath	 == pszPath)
//         {
//
//            ia.add(iPid);
//
//         }
//
//      }
//
//   }
//
//   return ia;
//
//}
//
//namespace acme
//{
//
//
//   namespace posix
//   {
//
//
//      id_array node::module_path_get_pid(const char * psz)
//      {
//
//         ::output_debug_string("os/linux_process.cpp app_get_pid (" + string(psz) + ")");
//
//         id_array ia;
//
//         ::file::patha stra;
//
//         ::dir::ls_dir(stra, "/proc/");
//
//         string str(psz);
//
//         str = "app=" + str;
//
//         string strApp(psz);
//
//         strApp.replace("-", "_");
//
//         strApp.replace("/", "_");
//
//         string strApp2;
//
//         strApp2 = "_" + strApp;
//
//         for (auto & strPid : stra)
//         {
//
//            int iPid = atoi(strPid.title());
//
//            if (iPid > 0)
//            {
//
//               //if(iPid == 22912)
//               //{
//               //output_debug_string("22912");
//               //}
//               ::file::path path = module_path_from_pid(iPid);
//
//               if (path.has_char())
//               {
//
//                  //output_debug_string(path + "\n");
//
//               }
//
//               string strTitle = path.title();
//
//               ::str::ends_eat_ci(strTitle, " (deleted)");
//
//               if (strTitle == strApp ||
//                   strTitle == strApp2)
//               {
//
//                  ia.add(iPid);
//
//               } else
//               {
//
//                  string_array straCmdLine = cmdline_from_pid(iPid);
//
//                  string strCmdLine;
//
//                  strCmdLine = straCmdLine.implode(" ");
//
//                  if (straCmdLine.find_first(str) > 0)
//                  {
//
//                     ia.add(iPid);
//
//                  }
//
//               }
//
//            }
//
//         }
//
//         return ia;
//
//      }
//
//
//      string node::command_line_from_pid(unsigned int iPid)
//      {
//
//         string_array stra;
//
//         string str;
//
//         str = "/proc/" + __str(iPid) + "/cmdline";
//
//         memory mem = file_as_memory(str);
//
//         string strArg;
//
//         char ch;
//
//         for (int i = 0; i < mem.get_size(); i++)
//         {
//
//            ch = (char) mem.get_data()[i];
//
//            if (ch == '\0')
//            {
//
//               stra.add(strArg);
//
//               strArg.Empty();
//
//            } else
//            {
//
//               strArg += ch;
//
//            }
//
//
//         }
//
//         if (strArg.has_char())
//         {
//
//            stra.add(strArg);
//
//         }
//
//         return stra;
//
//         /* the easiest case: we are in linux */
////    ssize_t s = readlink (str, path, iSize);
//
//         //  if(s == -1)
//         //{
//         // return "";
//         //}
//
//         //path[s] = '\0';
//
//         //return path;
//
//      }
//
//
//      bool node::is_shared_library_busy(u32 processid, const string_array & stra)
//      {
//
//         return false;
//
//      }
//
//
//      bool node::is_shared_library_busy(const string_array & stra)
//      {
//
//         return false;
//
//      }
//
//
//
//   } // namespace posix
//
//
//} // namespace acme
//
//bool shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout )
//{
//
//   property_set set;
//
//   return call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), e_display_none, durationTimeout, set);
//
//}
//
//
//
//
//
//
//CLASS_DECL_ACME i32 ca2_main();
//
//
//
//int create_process2(const char * pszCommandLine, int * pprocessId)
//{
//
//   string_array stra;
//
//   stra = get_c_args_for_c(pszCommandLine);
//
//   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));
//
//   int argc = 0;
//
//   for(auto & str : stra)
//   {
//
//      argv[argc] = strdup((char *) str.c_str());
//
//      argc++;
//
//   }
//
//   argv[argc] = nullptr;
//
//   pid_t pid = 0;
//
//   if((pid = fork()) == 0) // child
//   {
//
//      int iExitCode = execv(argv[0], argv);
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      exit(iExitCode);
//
//   }
//   else if(pid == -1) // in parent, but error
//   {
//
//      char ** pargv = argv;
//
//      while(*pargv != nullptr)
//      {
//
//         free(*pargv);
//
//         pargv++;
//
//      }
//
//      free(argv);
//
//      return 0;
//
//   }
//
//   if(pprocessId != nullptr)
//   {
//
//      *pprocessId = pid;
//
//   }
//
//   return 1;
//
//}
//
//
//
//
//CLASS_DECL_ACME ::file::path core_app_path(string strApp)
//{
//
//   strApp.replace("-", "_");
//
//   strApp.replace("/", "_");
//
//   return "/xcore/time/x64/basis/" + strApp;
//
//}
//
//


::u32 get_current_process_id()
{

   return getpid();

}


//
//
//
