#include "framework.h"
#include "_uwp.h"
#include <io.h>


int_bool file_exists(const char * path1)
{

   u32 dwFileAttributes = windows_get_file_attributes(path1);

   if(dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      return FALSE;

   return true;

}



int_bool file_put_contents_dup(const char * path,const char * contents,count len)
{

   dir::mk(dir::name(path));

   wstring wstr(path);

   HANDLE hfile = create_file(path,GENERIC_WRITE,0,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);

   if(hfile == INVALID_HANDLE_VALUE)
      return FALSE;

   count dwWrite;

   if(len < 0)
      dwWrite = ansi_length(contents);
   else
      dwWrite = len;

   DWORD dwWritten = 0;

   int_bool bOk = WriteFile(hfile,contents,(u32)dwWrite,&dwWritten,nullptr) != FALSE;

   CloseHandle(hfile);

   return dwWrite == dwWritten && bOk != FALSE;


}


filesize file_length_dup(const char * path)
{

   HANDLE hfile = create_file(path,GENERIC_READ,0,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);

   if(hfile == INVALID_HANDLE_VALUE)
      return 0;

   u64 ui = fsize_dup(hfile);

   CloseHandle(hfile);

   return ui;

}







int_bool file_is_equal_path_dup(const char * psz1,const char * psz2)
{
   return file_is_equal_path(psz1,psz2);
//   const i32 iBufSize = MAX_PATH * 8;
//   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);
//   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);
//   int iCmp = pwsz1.compare_ci(pwsz2);
///*   unichar * pwszFile1;
//   unichar * pwszFile2;
//   unichar * pwszPath1 = new unichar[iBufSize];
//   unichar * pwszPath2 = new unichar[iBufSize];
//   i32 iCmp = -1;
//   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
//   {
//      if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
//      {
//         string p1 = ::str::international::unicode_to_utf8(pwszPath1);
//         string p2 = ::str::international::unicode_to_utf8(pwszPath2);
//         iCmp = ansi_compare_ci(p1,p2);
//      }
//   }
//   delete pwszPath1;
//   delete pwszPath2;*/
//   return iCmp == 0;

}





























//
//
//string file_get_mozilla_firefox_plugin_container_path()
//{
//
//   string strPath;
//   HKEY hkeyMozillaFirefox;
//
//   if(::RegOpenKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Mozilla\\Mozilla Firefox",&hkeyMozillaFirefox) != ERROR_SUCCESS)
//      return "";
//   {
//
//      DWORD dwType;
//      DWORD dwData;
//      dwData = 0;
//      if(::WinRegGetValueW(hkeyMozillaFirefox,nullptr,L"CurrentVersion",RRF_RT_REG_SZ,&dwType,nullptr,&dwData) != ERROR_SUCCESS)
//      {
//         goto ret1;
//      }
//
//      wstring wstrVersion;
//      wstrVersion.alloc(dwData);
//      if(::WinRegGetValueW(hkeyMozillaFirefox,nullptr,L"CurrentVersion",RRF_RT_REG_SZ,&dwType,wstrVersion,&dwData) != ERROR_SUCCESS)
//      {
//         goto ret1;
//      }
//      wstrVersion.release_string_buffer();
//
//      wstring wstrMainSubKey = wstrVersion + L"\\Main";
//      dwData = 0;
//
//      if(::WinRegGetValueW(hkeyMozillaFirefox,wstrMainSubKey,L"Install Directory",RRF_RT_REG_SZ,&dwType,nullptr,&dwData) != ERROR_SUCCESS)
//      {
//         goto ret1;
//      }
//
//      wstring wstrDir;
//      wstrDir.alloc(dwData);
//      if(::WinRegGetValueW(hkeyMozillaFirefox,wstrMainSubKey,L"Install Directory",RRF_RT_REG_SZ,&dwType,wstrDir,&dwData) != ERROR_SUCCESS)
//      {
//         goto ret1;
//      }
//      wstrDir.release_string_buffer();
//
//      string strDir;
//
//      strDir = ::str::international::unicode_to_utf8(wstrDir);
//
//      strPath = dir::path(strDir,"plugin-container.exe");
//   }
//
//ret1:
//   ::RegCloseKey(hkeyMozillaFirefox);
//   return strPath;
//
//}
//
//
//


//
//string get_sys_temp_path()
//{
//
//   unichar  wsz[MAX_PATH * 4];
//
//   wsz[GetTempPathW(sizeof(wsz) / sizeof(wsz[0]),wsz)] = L'\0';
//
//   return string(wsz);
//
//}
//


//string file_as_string(const char * path)
//{
//
//   string str;
//
//   HANDLE hfile = ::create_file(path,GENERIC_READ,0,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
//
//   if(hfile == INVALID_HANDLE_VALUE)
//      return "";
//
//   DWORD dwSizeHigh;
//
//   DWORD dwSize = ::GetFileSize(hfile,&dwSizeHigh);
//
//   LPSTR lpsz = str.get_string_buffer(dwSize);
//
//   DWORD dwRead;
//
//   ::ReadFile(hfile,lpsz,dwSize,&dwRead,nullptr);
//
//   lpsz[dwSize] = '\0';
//
//   str.release_string_buffer(dwSize);
//
//   ::CloseHandle(hfile);
//
//   return str;
//
//
//}

//
//
//bool file_as_memory(memory_base & memory,const char * path)
//{
//
//   memory.set_size(0);
//
//   HANDLE hfile = ::create_file(path,GENERIC_READ,0,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
//
//   if(hfile == INVALID_HANDLE_VALUE)
//      return false;
//
//   u64 uiSize = fsize_dup(hfile);
//
//   if(uiSize > ((::count) - 1))
//   {
//
//      ::CloseHandle(hfile);
//
//      return false;
//
//   }
//
//   memory.set_size((::count) uiSize);
//
//   DWORD dwRead;
//
//   ::ReadFile(hfile,memory.get_data(),(u32)memory.get_size(),&dwRead,nullptr);
//
//   ::CloseHandle(hfile);
//
//   return true;
//
//}

//
//
//string file_module_path_dup()
//{
//
//   char path[MAX_PATH * 4];
//
//   if(!GetModuleFileName(nullptr,path,sizeof(path)))
//      return "";
//
//   return path;
//
//}



//void file_read_n_number_dup(HANDLE hfile,::md5::md5 * pctx,i32 & iNumber)
//{
//
//   string str;
//
//   char ch;
//
//   DWORD dwRead;
//
//   while(ReadFile(hfile,&ch,1,&dwRead,nullptr) && dwRead == 1)
//   {
//      if(ch >= '0' && ch <= '9')
//         str += ch;
//      else
//         break;
//      if(pctx != nullptr)
//      {
//         pctx->update(&ch,1);
//      }
//   }
//   if(ch != 'n')
//      return;
//   if(pctx != nullptr)
//   {
//      pctx->update(&ch,1);
//   }
//   iNumber = ansi_to_i32(str);
//}
//
//void file_read_gen_string_dup(HANDLE hfile,::md5::md5 * pctx,string & str)
//{
//   i32 iLen;
//   file_read_n_number_dup(hfile,pctx,iLen);
//   LPSTR lpsz = (LPSTR)memory_alloc(iLen + 1);
//   DWORD dwRead;
//   ReadFile(hfile,lpsz,iLen,&dwRead,nullptr);
//   if(pctx != nullptr)
//   {
//      pctx->update(lpsz,iLen);
//   }
//   lpsz[iLen] = '\0';
//   str = lpsz;
//   memory_free_dbg(lpsz,0);
//}


string file_module_path_dup()
{

   return "/ca2/stage";

}



//
//bool PrintModules(string & strImage,u32 processID,const char * pszDll)
//{
//
//   HANDLE hProcess;
//
//   DWORD cbNeeded;
//
//   u32 ui;
//
//   hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,processID);
//
//   if(nullptr == hProcess)
//      return false;
//
//   const i32 iMaxModuleCount = 1024;
//
//   HMODULE * hMods = new HMODULE[iMaxModuleCount];
//
//   const i32 iImageSize = MAX_PATH * 8;
//
//   char * szImage = (char *)memory_alloc(iImageSize);
//
//   GetModuleFileNameEx(hProcess,nullptr,szImage,iImageSize);
//
//   strImage = szImage;
//
//   memory_free_dbg(szImage,0);
//
//   bool bFound = false;
//
//   if(EnumProcessModules(hProcess,hMods,sizeof(HMODULE) * iMaxModuleCount,&cbNeeded))
//   {
//
//      for(ui = 0; ui < (cbNeeded / sizeof(HMODULE)); ui++)
//      {
//
//         TCHAR szModName[MAX_PATH];
//
//         // Get the full path to the module's file.
//
//         if(GetModuleFileNameEx(hProcess,hMods[ui],szModName,sizeof(szModName) / sizeof(TCHAR)))
//         {
//
//            if(!ansi_compare_ci(szModName,pszDll))
//            {
//
//               bFound = true;
//
//               break;
//
//            }
//
//         }
//
//      }
//
//   }
//
//   delete hMods;
//
//   CloseHandle(hProcess);
//
//   return bFound;
//
//}
//
//void dll_processes(u32_array & dwa,string_array & straProcesses,const char * pszDll)
//{
//   // Get the list of process identifiers.
//
//   DWORD * aProcesses = new DWORD[1024 * 8];
//
//   DWORD cbNeeded,cProcesses;
//
//   u32 ui;
//
//   if(!EnumProcesses(aProcesses,124 * 8 * sizeof(DWORD),&cbNeeded))
//   {
//      delete aProcesses;
//      return;
//   }
//
//   // Calculate how many process identifiers were returned.
//
//   cProcesses = cbNeeded / sizeof(DWORD);
//
//   // Print the name of the modules for each process.
//
//   string strImage;
//
//   for(ui = 0; ui < cProcesses; ui++)
//   {
//
//      if(PrintModules(strImage,aProcesses[ui],pszDll))
//      {
//
//         straProcesses.add(strImage); // there may processes with different pids but same image
//         dwa.add(aProcesses[ui]);
//
//      }
//
//   }
//
//   delete aProcesses;
//
//}
//
//



// #define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
// struct PROCESS_INFO_t
// {
//    string csProcess;
//    u32 dwImageListIndex;
// };


// #if !defined(LINUX) && !defined(MACOS) && !defined(_UWP) && !defined(ANDROID)

// //#include <Tlhelp32.h>
// //#include <Psapi.h>


// // void EnumerateLoadedModules(string& csPath,OF_CALLBACK CallBackProc,uptr pUserContext);
// // void EnumerateOpenedFiles(string& csPath,OF_CALLBACK CallBackProc,uptr pUserContext,HANDLE hDriver,GetFinalPathNameByHandleDef pGetFinalPathNameByHandle);

// // const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
// // const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
// // const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

// // #define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
// // #define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")


// // // This Function install the driver and starts it
// // HANDLE OnlyGetDrv()
// // {


// //    HMODULE hModule = GetModuleHandle(_T("acme.dll"));
// //    if(!hModule)
// //    {
// //       output_debug_string(L"GetModuleHandle(_T(\"acme.dll\")); failed");
// //       return 0;
// //    }
// //    string csFilePath;
// //    LPTSTR lpPath = csFilePath.GetBuffer(MAX_PATH);
// //    GetModuleFileName(hModule,lpPath,MAX_PATH);
// //    PathRemoveFileSpec(lpPath);
// //    csFilePath.ReleaseBuffer();
// //    if(IsWow64())
// //    {
// //       csFilePath += DRIVER_FILE_NAME_64;
// //    }
// //    else
// //    {
// //       csFilePath += DRIVER_FILE_NAME_32;
// //    }

// //    if(!PathFileExists(csFilePath))
// //    {
// //       message_box(nullptr,"Cannot find driver " + csFilePath,"Cannot find driver " + csFilePath,MB_OK);
// //       return 0;
// //    }



// //    // Delete the temp file...
// //    //DeleteFile( csPath );
// //    HANDLE hFile = CreateFile(DRV_DOS_NAME,GENERIC_READ | GENERIC_WRITE,
// //                              FILE_SHARE_READ | FILE_SHARE_WRITE,0,
// //                              OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
// //    return hFile;

// // }


// // extern "C" CLASS_DECL_ACME void GetOpenedFiles(LPCWSTR lpPath,OF_TYPE Filter,OF_CALLBACK CallBackProc,uptr pUserContext)
// // {
// //    string csPath = lpPath;
// //    csPath.make_lower();
// //    EnableTokenPrivilege(SE_DEBUG_NAME);
// //    if(Filter& MODULES_ONLY)
// //    {
// //       EnumerateLoadedModules(csPath,CallBackProc,pUserContext);
// //    }

// //    if(Filter& FILES_ONLY)
// //    {


// //       // Extract the driver from the resource and install it.
// //       //HANDLE hDriver = ExtractAndInstallDrv();
// //       //HANDLE hDriver = OnlyGetDrv();
// //       HANDLE hDriver = nullptr;
// //       GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = 0;
// //       if(!hDriver)
// //       {
// //          pGetFinalPathNameByHandle = (GetFinalPathNameByHandleDef)GetProcAddress(GetModuleHandle(_T("kernel32.dll")),"GetFinalPathNameByHandleW");
// //       }
// //       // Now walk all handles
// //       EnumerateOpenedFiles(csPath,CallBackProc,pUserContext,hDriver,pGetFinalPathNameByHandle);
// //       //if( hDriver )
// //       {
// //          // Time to wind up
// //          //StopAndUninstallDrv( hDriver );
// //       }
// //    }
// // }

// // #ifndef _UWP

// // typedef struct _SYSTEM_HANDLE_INFORMATION
// // {
// //    u32         dwCount;
// //    SYSTEM_HANDLE Handles[1];
// // } SYSTEM_HANDLE_INFORMATION,*PSYSTEM_HANDLE_INFORMATION,**PPSYSTEM_HANDLE_INFORMATION;

// // typedef enum _SYSTEM_INFORMATION_CLASS
// // {
// //    SystemHandleInformation = 0X10,
// // } SYSTEM_INFORMATION_CLASS;

// // #endif

// // typedef NTSTATUS(WINAPI *PNtQuerySystemInformation)
// // (IN	SYSTEM_INFORMATION_CLASS SystemInformationClass,
// //  OUT	PVOID					 SystemInformation,
// //  IN	ULONG					 SystemInformationLength,
// //  OUT	PULONG					 ReturnLength OPTIONAL);

// // UINT g_CurrentIndex = 0;
// // struct THREAD_PARAMS
// // {
// //    PSYSTEM_HANDLE_INFORMATION pSysHandleInformation;
// //    GetFinalPathNameByHandleDef pGetFinalPathNameByHandle;
// //    LPWSTR lpPath;
// //    i32 nFileType;
// //    HANDLE hStartEvent;
// //    HANDLE hFinishedEvent;
// //    bool bStatus;
// // };

// // u32 ThreadProc(void * lParam)
// // {
// //    THREAD_PARAMS* pThreadParam = (THREAD_PARAMS*)lParam;

// //    FILE_NAME_INFO * pinfo = (FILE_NAME_INFO *)new BYTE[MAX_PATH * 8];

// //    GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = pThreadParam->pGetFinalPathNameByHandle;
// //    for(g_CurrentIndex; g_CurrentIndex < pThreadParam->pSysHandleInformation->dwCount;)
// //    {

// //       WaitForSingleObject(pThreadParam->hStartEvent,INFINITE);
// //       ResetEvent(pThreadParam->hStartEvent);
// //       pThreadParam->bStatus = false;
// //       SYSTEM_HANDLE& sh = pThreadParam->pSysHandleInformation->Handles[g_CurrentIndex];
// //       g_CurrentIndex++;
// //       HANDLE hDup = (HANDLE)sh.wValue;
// //       HANDLE hProcess = OpenProcess(PROCESS_DUP_HANDLE,FALSE,sh.dwProcessId);
// //       if(hProcess)
// //       {
// //          bool b = DuplicateHandle(hProcess,(HANDLE)sh.wValue,GetCurrentProcess(),&hDup,0,FALSE,DUPLICATE_SAME_ACCESS) != FALSE;
// //          if(!b)
// //          {
// //             hDup = (HANDLE)sh.wValue;
// //          }
// //          CloseHandle(hProcess);
// //       }
// //       //u32 dwRet = pGetFinalPathNameByHandle( hDup, pThreadParam->lpPath, MAX_PATH, 0 );
// //       //u32 dwRet = GetFileInformationByHandleEx(hDup, FileNameInfo, pinfo, MAX_PATH * 8);
// //       u32 dwRet = GetFinalPathNameByHandleW(hDup,pThreadParam->lpPath,MAX_PATH,0);
// //       //wcsncpy(pThreadParam->lpPath, pinfo->FileName, pinfo->FileNameLength);
// //       if(hDup && (hDup != (HANDLE)sh.wValue))
// //       {
// //          CloseHandle(hDup);
// //       }
// //       if(dwRet)
// //       {
// //          pThreadParam->bStatus = true;
// //       }
// //       SetEvent(pThreadParam->hFinishedEvent);

// //    }
// //    delete[](BYTE *) pinfo;
// //    return 0;
// // }

// // void EnumerateOpenedFiles(string& csPath,OF_CALLBACK CallBackProc,uptr pUserContext,HANDLE hDriver,
// //                           GetFinalPathNameByHandleDef pGetFinalPathNameByHandle)
// // {
// //    i32 nFileType;

// //    if(is_windows_vista_or_greater())
// //    {
// //       nFileType = VISTA_FILETYPE;
// //    }
// //    else
// //    {
// //       nFileType = XP_FILETYPE;
// //    }

// //    LPCTSTR lpPath = csPath;
// //    string csShortName;
// //    GetShortPathName(csPath,csShortName.GetBuffer(MAX_PATH),MAX_PATH);
// //    csShortName.ReleaseBuffer();
// //    csShortName.make_lower();
// //    bool bShortPath = false;
// //    LPCTSTR lpShortPath = csShortName;
// //    if(csShortName != csPath && FALSE == csShortName.is_empty())
// //    {
// //       bShortPath = true;
// //    }

// //    HMODULE hModule = GetModuleHandle(_T("ntdll.dll"));
// //    PNtQuerySystemInformation NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress(hModule,"NtQuerySystemInformation");
// //    if(0 == NtQuerySystemInformation)
// //    {
// //       output_debug_string(L"Getting proc of NtQuerySystemInformation failed");
// //       return;
// //    }

// //    // Get the list of all handles in the file_system
// //    PSYSTEM_HANDLE_INFORMATION pSysHandleInformation = new SYSTEM_HANDLE_INFORMATION;
// //    u32 size = sizeof(SYSTEM_HANDLE_INFORMATION);
// //    DWORD needed = 0;
// //    NTSTATUS status = NtQuerySystemInformation(SystemHandleInformation,pSysHandleInformation,size,&needed);
// //    if(!NT_SUCCESS(status))
// //    {
// //       if(0 == needed)
// //       {
// //          return;// some other error
// //       }
// //       // The previously supplied buffer wasn't enough.
// //       delete pSysHandleInformation;
// //       size = needed + 1024;
// //       pSysHandleInformation = (PSYSTEM_HANDLE_INFORMATION)new BYTE[size];
// //       status = NtQuerySystemInformation(SystemHandleInformation,pSysHandleInformation,size,&needed);
// //       if(!NT_SUCCESS(status))
// //       {
// //          // some other error so quit.
// //          delete pSysHandleInformation;
// //          return;
// //       }
// //    }

// //    if(pGetFinalPathNameByHandle)// there is no driver, we have do it ugly way
// //    {
// //       g_CurrentIndex = 0;
// //       //		TCHAR tcFileName[MAX_PATH+1];
// //       THREAD_PARAMS ThreadParams;
// //       wstring wstrFileName;

// //       wstrFileName.alloc(MAX_PATH * 8);
// //       ThreadParams.lpPath = wstrFileName;
// //       ThreadParams.nFileType = nFileType;
// //       ThreadParams.pGetFinalPathNameByHandle = pGetFinalPathNameByHandle;
// //       ThreadParams.pSysHandleInformation = pSysHandleInformation;
// //       ThreadParams.hStartEvent = ::CreateEvent(0,TRUE,FALSE,0);
// //       ThreadParams.hFinishedEvent = ::CreateEvent(0,TRUE,FALSE,0);
// //       HANDLE ThreadHandle = 0;
// //       while(g_CurrentIndex < pSysHandleInformation->dwCount)
// //       {
// //          if(!ThreadHandle)
// //          {
// //             ThreadHandle = create_thread(ThreadProc,&ThreadParams);
// //          }
// //          ResetEvent(ThreadParams.hFinishedEvent);
// //          SetEvent(ThreadParams.hStartEvent);
// //          if(WAIT_TIMEOUT == WaitForSingleObject(ThreadParams.hFinishedEvent,100))
// //          {
// //             string csError;
// //             csError.Format("Query hang for handle %d",(i32)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue);
// //             output_debug_string(csError);
// //             TerminateThread(ThreadHandle,0);
// //             CloseHandle(ThreadHandle);
// //             ThreadHandle = 0;
// //             continue;
// //          }
// //          if(!ThreadParams.bStatus)
// //          {
// //             continue;
// //          }
// //          i32 nCmpStart = 4;
// //          string csFileName(::str::international::unicode_to_utf8(&ThreadParams.lpPath[nCmpStart]));
// //          csFileName.make_lower();
// //          if(csFileName.find("vs11_dp_ctp") >= 0)
// //          {
// //             continue;
// //          }
// //          else if(0 != _tcsncmp(lpPath,csFileName,csPath.get_length()))
// //          {
// //             continue;
// //          }
// //          OF_INFO_t stOFInfo;
// //          stOFInfo.dwPID = pSysHandleInformation->Handles[g_CurrentIndex - 1].dwProcessId;
// //          wstring wstrCallback;
// //          wstrCallback = ::str::international::utf8_to_unicode(csFileName);
// //          stOFInfo.lpFile = wstrCallback;
// //          stOFInfo.hFile  = (HANDLE)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue;
// //          CallBackProc(stOFInfo,pUserContext);
// //       }
// //       if(ThreadHandle)
// //       {
// //          if(WAIT_TIMEOUT == WaitForSingleObject(ThreadHandle,1000))
// //          {
// //             TerminateThread(ThreadHandle,0);
// //          }
// //          CloseHandle(ThreadHandle);
// //       }
// //       CloseHandle(ThreadParams.hStartEvent);
// //       CloseHandle(ThreadParams.hFinishedEvent);
// //       return;
// //    }

// //    // Walk through the handle list
// //    for(u32 i = 0; i < pSysHandleInformation->dwCount; i++)
// //    {
// //       SYSTEM_HANDLE& sh = pSysHandleInformation->Handles[i];
// //       if(sh.bObjectType != nFileType)// Under windows XP file handle is of type 28
// //       {
// //          continue;
// //       }

// //       string csFileName;
// //       string csDir;
// //       if(hDriver)
// //       {
// //          HANDLE_INFO stHandle = {0};
// //          ADDRESS_INFO stAddress;
// //          stAddress.pAddress = sh.pAddress;
// //          DWORD dwReturn = 0;
// //          bool bSuccess = DeviceIoControl(hDriver,IOCTL_LISTDRV_BUFFERED_IO,&stAddress,sizeof(ADDRESS_INFO),&stHandle,sizeof(HANDLE_INFO),&dwReturn,nullptr) != FALSE;


// //          if(bSuccess && stHandle.tcFileName[0] != 0 &&
// //                stHandle.uType != FILE_DEVICE_SOUND &&
// //                stHandle.uType != FILE_DEVICE_NAMED_PIPE)
// //          {

// //             if(stHandle.uType != FILE_DEVICE_NETWORK_FILE_SYSTEM)
// //             {
// //                // Get the drive name from the dos device name
// //                if(!GetDrive((LPCTSTR)stHandle.tcDeviceName,csFileName,true))
// //                {
// //                   output_debug_string(L"GetDrive failed");
// //                }
// //                csFileName += (LPCTSTR)stHandle.tcFileName;
// //             }
// //             else
// //             {
// //                csFileName = _T("\\");
// //                csFileName += (LPCTSTR)stHandle.tcFileName;
// //             }
// //          }
// //          else
// //          {
// //             continue;
// //          }
// //       }
// //       else
// //       {
// //          return;
// //       }


// //       csFileName.make_lower();
// //       // Check whether the file belongs to the specified folder
// //       // 		if( -1 == csFileName.Find( csPath ))
// //       // 		{
// //       // 			if( bShortPath )
// //       // 			{
// //       // 				// Some times the file name may be in i16 path form.
// //       // 				if( -1 == csFileName.Find( csShortName ))
// //       // 				{
// //       // 					continue;
// //       // 				}
// //       // 			}
// //       // 			else
// //       // 			{
// //       // 				continue;
// //       // 			}
// //       // 		}

// //       if(0 != _tcsncmp(lpPath,csFileName,csPath.get_length()))
// //       {
// //          if(bShortPath)
// //          {
// //             // Some times the file name may be in i16 path form.
// //             if(0 != _tcsncmp(lpShortPath,csFileName,csShortName.get_length()))
// //             {
// //                continue;
// //             }
// //          }
// //          else
// //          {
// //             continue;
// //          }
// //       }
// //       OF_INFO_t stOFInfo;
// //       stOFInfo.dwPID = sh.dwProcessId;
// //       wstring wstrCallback;
// //       wstrCallback = ::str::international::utf8_to_unicode(csFileName);
// //       stOFInfo.lpFile = wstrCallback;
// //       stOFInfo.hFile  = (HANDLE)sh.wValue;
// //       CallBackProc(stOFInfo,pUserContext);
// //    }
// //    delete pSysHandleInformation;

// // }


// // void EnumerateLoadedModules(string& csPath,OF_CALLBACK CallBackProc,uptr pUserContext)
// // {
// //    string csShortName;
// //    GetShortPathName(csPath,csShortName.GetBuffer(MAX_PATH),MAX_PATH);
// //    csShortName.ReleaseBuffer();
// //    csShortName.make_lower();
// //    bool bShortPath = false;
// //    if(csShortName != csPath && FALSE == csShortName.is_empty())
// //    {
// //       bShortPath = true;
// //    }

// //    u32 dwsize = 300;
// //    PDWORD pDwId = (PDWORD)new BYTE[dwsize];
// //    DWORD dwReturned = dwsize;
// //    // Enum all the process first
// //    while(1)
// //    {
// //       EnumProcesses(pDwId,dwsize,&dwReturned);
// //       if(dwsize > dwReturned)
// //       {
// //          break;
// //       }
// //       delete pDwId;
// //       dwsize += 50;
// //       pDwId = (PDWORD)new BYTE[dwsize];
// //    }
// //    i32 nCount = dwReturned / sizeof(u32);
// //    i32 nItemCount = -1;
// //    // Enumerate modules of the above process
// //    for(i32 nIdx = 0; nIdx < nCount; nIdx++)
// //    {
// //       if(0 != pDwId[nIdx])
// //       {
// //          HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
// //          MODULEENTRY32 me32;
// //          // Take a snapshot of all modules in the specified process.
// //          hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pDwId[nIdx]);
// //          if(hModuleSnap == INVALID_HANDLE_VALUE)
// //          {
// //             continue;
// //          }
// //          me32.dwSize = sizeof(MODULEENTRY32);
// //          if(!Module32First(hModuleSnap,&me32))
// //          {
// //             CloseHandle(hModuleSnap);
// //             continue;
// //          }
// //          bool bFirst = true;
// //          PROCESS_INFO_t stInfo;
// //          do
// //          {
// //             string csModule;
// //             if(bFirst)
// //             {
// //                // First module is always the exe name
// //                bFirst = false;
// //                if(!PathFileExists(me32.szExePath))
// //                {
// //                   TCHAR tcFileName[MAX_PATH];
// //                   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,TRUE,pDwId[nIdx]);
// //                   if(GetProcessImageFileName(hProcess,tcFileName,MAX_PATH))
// //                   {
// //                      GetDrive(tcFileName,csModule,false);
// //                   }
// //                   CloseHandle(hProcess);
// //                }
// //                else
// //                {
// //                   csModule = me32.szExePath;
// //                }
// //                csModule.make_lower();
// //             }
// //             else
// //             {
// //                csModule = me32.szExePath;
// //                csModule.make_lower();
// //             }
// //             if(-1 == csModule.find(csPath))
// //             {
// //                if(bShortPath)
// //                {
// //                   if(-1 == csModule.find(csShortName))
// //                   {
// //                      continue;
// //                   }
// //                }
// //                else
// //                {
// //                   continue;
// //                }
// //             }
// //             OF_INFO_t stOFInfo;
// //             stOFInfo.dwPID = pDwId[nIdx];
// //             wstring wstrCallback;

// //             wstrCallback = ::str::international::utf8_to_unicode(csModule);

// //             stOFInfo.lpFile = wstrCallback;
// //             CallBackProc(stOFInfo,pUserContext);
// //          }
// //          while(Module32Next(hModuleSnap,&me32));
// //          CloseHandle(hModuleSnap);
// //       }
// //    }

// //    delete pDwId;

// // }



// // #endif // LINUX





int ftruncate(int file,filesize len)
{
   return _chsize_s(file,len);
}





int_bool ensure_file_size_fd(i32 fd,size_t iSize)
{

   if(ftruncate(fd,iSize) == -1)
      return 0;

   return 1;

}


int_bool ensure_file_size(FILE * file,size_t iSize)
{

   return ensure_file_size_fd(fileno(file),iSize);

}


int_bool ensure_file_size_handle(HANDLE h,u64 iSize)
{

   DWORD dwHi;

   DWORD dwLo = GetFileSize(h,&dwHi);

   if(((u64)dwLo | ((u64)dwHi << 32)) != iSize)
   {

      LONG l = (iSize >> 32) & 0xffffffff;

      if(SetFilePointer(h,iSize & 0xffffffff,&l,SEEK_SET) != (DWORD)(iSize & 0xffffffff))
         return false;

      if(l != ((iSize >> 32) & 0xffffffff))
         return false;

      if(!SetEndOfFile(h))
         return false;

   }


   return 1;

}
























//
//
//
//
//int_bool file_set_length(const char * pszName,size_t iSize)
//{
//
//   wstring wstr(pszName);
//
//   HANDLE h = ::CreateFileW(wstr,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
//
//   if(h == INVALID_HANDLE_VALUE)
//      return false;
//
//   if(!ensure_file_size_handle(h,iSize))
//   {
//
//      ::CloseHandle(h);
//
//      return false;
//
//   }
//
//   ::CloseHandle(h);
//
//   return true;
//
//}
//
//
//
//
//
//int_bool file_move(const char * lpszNewName,const char * lpszOldName)
//{
//
//   if(!::MoveFile((LPTSTR)lpszOldName,(LPTSTR)lpszNewName))
//      return FALSE;
//
//   return TRUE;
//
//}

int_bool file_delete(const char * lpszFileName)
{


   if(!::DeleteFile((LPTSTR)lpszFileName))
      return FALSE;

   return TRUE;


}



//
//int_bool file_is_equal_path(const char * psz1,const char * psz2)
//{
//   return file_is_equal_path_dup(psz1,psz2);
//   /*const i32 iBufSize = MAX_PATH * 8;
//   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);
//   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);
//   unichar * pwszFile1;
//   unichar * pwszFile2;
//   unichar * pwszPath1 = new unichar[iBufSize];
//   unichar * pwszPath2 = new unichar[iBufSize];
//   i32 iCmp = -1;
//   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
//   {
//      if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
//      {
//         string p1 = ::str::international::unicode_to_utf8(pwszPath1);
//         string p2 = ::str::international::unicode_to_utf8(pwszPath2);
//         iCmp = ansi_compare_ci(p1,p2);
//      }
//   }
//   delete pwszPath1;
//   delete pwszPath2;
//   return iCmp == 0;
//*/
//}




// file.cpp

// file routine overrides

// 08/20/05 (mv)

#include "framework.h"





/*i32 _fileno(FILE *fp)
{
return (i32)fp;			// FIXME:  This doesn't work under Win64
}

HANDLE _get_osfhandle(i32 i)
{
return (HANDLE)i;		// FIXME:  This doesn't work under Win64
}*/

//FILE *fopen_dup(const char *path,const char *attrs)
//{
//
//
//
//   u32 access,disp;
//   if(ansi_find_char(attrs,'w'))
//   {
//      access = GENERIC_WRITE;
//      disp = CREATE_ALWAYS;
//   }
//   else
//   {
//      access = GENERIC_READ;
//      disp = OPEN_EXISTING;
//   }
//
//   CREATEFILE2_EXTENDED_PARAMETERS ep;
//
//   __memset(&ep,0,sizeof(ep));
//   ep.dwSize = sizeof(ep);
//   ep.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
//
//   wstring wstr(path);
//
//   HANDLE hFile = CreateFile2(wstr,access,0,disp,&ep);
//
//
//   if(hFile == INVALID_HANDLE_VALUE)
//      return 0;
//
//   FILE *file = new FILE;
//   __memset(file,0,sizeof(FILE));
//   file->_base = (char *)hFile;
//
//   if(ansi_find_char(attrs,'t'))
//      file->_flag |= _FILE_TEXT;
//
//   return file;
//
//
//}
//
//
//FILE *_wfopen_dup(const unichar *path,const unichar *attrs)
//{
//
//   u32 access,disp;
//   if(wide_find_char(attrs,L'w'))
//   {
//      access = GENERIC_WRITE;
//      disp = CREATE_ALWAYS;
//   }
//   else
//   {
//      access = GENERIC_READ;
//      disp = OPEN_EXISTING;
//   }
//
//   HANDLE hFile = CreateFile2(path,access,0,disp,nullptr);
//   if(hFile == INVALID_HANDLE_VALUE)
//      return 0;
//
//   FILE *file = new FILE;
//   __memset(file,0,sizeof(FILE));
//   file->_base = (char *)hFile;
//
//   if(wide_find_char(attrs,L't'))
//      file->_flag |= _FILE_TEXT;
//
//   return file;
//
//}
//
//
//i32 fprintf_dup(FILE *fp,const char *s,...)
//{
//   va_list args;
//   va_start(args,s);
//
//   char bfr[1024];
//   i32 len = vsprintf(bfr,s,args);
//
//   va_end(args);
//
//   fwrite_dup(bfr,len + 1,sizeof(char),fp);
//   return len;
//}
//
//
//i32 fclose_dup(FILE *fp)
//{
//
//   ::CloseHandle((HANDLE)((FILE*)fp)->_base);
//   delete fp;
//   return 0;
//
//
//}
//
//i32 feof_dup(FILE *fp)
//{
//
//   return (fp->_flag & _FILE_EOF) ? 1 : 0;
//
//}
//
//i32 fflush_dup(FILE * fp)
//{
//
//   ::FlushFileBuffers((HANDLE)fp->_base);
//   return 0;
//
//}
//
//filesize fseek_dup(FILE *fp,filesize offset,i32 origin)
//{
//
//   u32 meth = FILE_BEGIN;
//   if(origin == SEEK_CUR)
//      meth = FILE_CURRENT;
//   else if(origin == SEEK_END)
//      meth = FILE_END;
//   LONG offsetHigh = (offset >> 32) & 0xffffffffLL;
//   u32 dw = ::SetFilePointer((HANDLE)((FILE*)fp)->_base,offset & 0xffffffff,&offsetHigh,meth);
//   ((FILE*)fp)->_flag &= ~_FILE_EOF;
//   return (u64)dw | (((u64)offsetHigh) << 32);
//
//}
//
//long ftell_dup(FILE *fp)
//{
//
//   return SetFilePointer((HANDLE)((FILE*)fp)->_base,0,0,FILE_CURRENT);
//
//}
//
//size_t fread_dup(void *buffer,size_t size,size_t count,FILE *str)
//{
//
//   if(size*count == 0)
//      return 0;
//   if(feof_dup(str))
//      return 0;
//
//   HANDLE hFile = (HANDLE)((FILE*)str)->_base;
//   i32 textMode = ((FILE*)str)->_flag & _FILE_TEXT;
//
//   memory buf;
//   buf.set_size(size*count);
//   char *src;
//   if(textMode)
//      src = (char*)buf.get_data();
//   else
//      src = (char*)buffer;
//
//   DWORD br;
//   if(!ReadFile(hFile,src,(u32)(size*count),&br,0))
//      ((FILE*)str)->_flag |= _FILE_ERROR;
//   else if(!br)		// nonzero return value and no bytes read = EOF
//      ((FILE*)str)->_flag |= _FILE_EOF;
//
//   if(!br)
//      return 0;
//
//   // Text-mode translation is always ANSI
//   if(textMode)		// text mode: must translate CR -> LF
//   {
//      char *dst = (char*)buffer;
//      for(u32 i = 0; i < br; i++)
//      {
//         if(src[i] != '\r')
//         {
//            *dst++ = src[i];
//            continue;
//         }
//
//         // If next char is LF -> convert CR to LF
//         if(i + 1 < br)
//         {
//            if(src[i + 1] == '\n')
//            {
//               *dst++ = '\n';
//               i++;
//            }
//            else
//               *dst++ = src[i];
//         }
//         else if(br > 1)
//         {
//            // This is the hard part: must peek ahead one byte
//            DWORD br2 = 0;
//            char peekChar = 0;
//            ReadFile(hFile,&peekChar,1,&br2,0);
//            if(!br2)
//               *dst++ = src[i];
//            else if(peekChar == '\n')
//               *dst++ = '\n';
//            else
//            {
//               fseek_dup(str,-1,SEEK_CUR);
//               *dst++ = src[i];
//            }
//         }
//         else
//            *dst++ = src[i];
//      }
//
//      //_ca_free(src, 0);
//   }
//
//   return br / size;
//
//}
//
//size_t fwrite_dup(const void *buffer,size_t size,size_t count,FILE *str)
//{
//
//   DWORD bw = 0,bw2 = 0;
//
//   if(size*count == 0)
//      return 0;
//
//   HANDLE hFile = (HANDLE)((FILE*)str)->_base;
//   i32 textMode = ((FILE*)str)->_flag & _FILE_TEXT;
//
//   if(hFile == nullptr)
//      return 0;
//
//   // Text-mode translation is always ANSI!
//   if(textMode)			// text mode -> translate LF -> CRLF
//   {
//      const char *src = (const char*)buffer;
//      size_t startpos = 0,i = 0;
//      for(i = 0; i < size*count; i++)
//      {
//         if(src[i] != '\n')
//            continue;
//         if(i > 0 && src[i - 1] == '\r')		// don't translate CRLF
//            continue;
//
//         if(i > startpos)
//         {
//            size_t dwWritten = 0;
//            while(i - startpos - dwWritten > 0)
//            {
//               if(!WriteFile(hFile,&src[startpos + dwWritten],(u32)min(1024,i - startpos - dwWritten),&bw2,0))
//                  return 0;
//               bw += bw2;
//               dwWritten += bw2;
//            }
//         }
//
//         const char *crlf = "\r\n";
//         WriteFile(hFile,crlf,2,&bw2,0);
//         bw++;		// one '\n' written
//
//         startpos = i + 1;
//      }
//
//      size_t dwWritten = 0;
//      while(i - startpos - dwWritten > 0)
//      {
//         WriteFile(hFile,&src[startpos + dwWritten],(u32)min(1024,i - startpos - dwWritten),&bw2,0);
//         bw += bw2;
//         dwWritten += bw2;
//      }
//   }
//   else
//   {
//      size_t s = size * count;
//      const char *src = (const char*)buffer;
//      size_t dwWritten = 0;
//      while(s - dwWritten > 0)
//      {
//         WriteFile(hFile,&src[dwWritten],(u32)min(1024,s - dwWritten),&bw2,0);
//         bw += bw2;
//         dwWritten += bw2;
//      }
//   }
//   return bw / size;
//
//}
//
//char *fgets_dup(char *str,i32 n,FILE *s)
//{
//
//   if(feof_dup(s))
//      return 0;
//
//   i32 i;
//   for(i = 0; i < n - 1; i++)
//   {
//      if(!fread_dup(&str[i],1,sizeof(char),s))
//         break;
//      if(str[i] == '\r')
//      {
//         i--;
//         continue;
//      }
//      if(str[i] == '\n')
//      {
//         i++;
//         break;
//      }
//   }
//
//   str[i] = 0;
//   return str;
//
//
//}
//
//unichar *fgetws_dup(unichar *str,i32 n,FILE *s)
//{
//   // Text-mode fgetws converts MBCS->Unicode
//   if(((FILE*)str)->_flag & _FILE_TEXT)
//   {
//      memory buf;
//      buf.set_size(n);
//      char *bfr = (char*)buf.get_data();
//      fgets_dup(bfr,n,s);
//      MultiByteToWideChar(CP_ACP,0,bfr,-1,str,n);
//      return str;
//   }
//
//   // Binary fgetws reads as Unicode
//
//   if(feof_dup(s))
//      return 0;
//
//   i32 i;
//   for(i = 0; i < n - 1; i++)
//   {
//      if(!fread_dup(&str[i],1,sizeof(unichar),s))
//         break;
//      if(str[i] == L'\r')
//      {
//         i--;
//         continue;	// does i++
//      }
//      if(str[i] == L'\n')
//      {
//         i++;
//         break;
//      }
//   }
//
//   str[i] = 0;
//   return str;
//}
//
//i32 fgetc_dup(FILE *s)
//{
//   if(s == 0 || feof_dup(s))
//      return EOF;
//
//   uchar c;
//   fread_dup(&c,1,sizeof(uchar),s);
//
//   return (i32)c;
//}
//
//i32 ungetc_dup(i32 c,FILE *s)
//{
//   if(s == 0)
//      return EOF;
//
//   fseek_dup(s,-1,SEEK_CUR);
//
//   return (i32)c;
//}
//
//wint_t fgetwc_dup(FILE *s)
//{
//   if(s == 0 || feof_dup(s))
//      return (wint_t)EOF;
//
//   // text-mode fgetwc reads and converts MBCS
//   if(((FILE*)s)->_flag & _FILE_TEXT)
//   {
//      char ch = (char)fgetc_dup(s);
//      wint_t wch;
//      MultiByteToWideChar(CP_ACP,0,&ch,1,(LPWSTR)&wch,1);
//      return wch;
//   }
//
//   // binary fgetwc reads unicode
//
//   wint_t c;
//   fread_dup(&c,1,sizeof(wint_t),s);
//
//   return c;
//
//}
//
//wint_t ungetwc_dup(wint_t w,FILE *s)
//{
//   if(s == 0)
//      return EOF;
//
//   fseek_dup(s,-2,SEEK_CUR);
//
//   return (i32)w;
//}
//
//
//i32 ferror_dup(FILE *fp)
//{
//
//   return fp->_flag & _FILE_ERROR;
//
//
//}
//
//u64 fsize_dup(HANDLE h)
//{
//
//   DWORD dwHi;
//
//   DWORD dwLo = ::GetFileSize(h,&dwHi);
//
//   return dwLo | (((DWORD64)dwHi) << 32);
//
//}
//
//
//
//

void ensure_file_size(HANDLE h,i64 iSize)
{

   DWORD dwHi;

   DWORD dwLo = ::GetFileSize(h,&dwHi);

   if(((u64)dwLo | ((i64)dwHi << 32)) != iSize)
   {
      LONG l = (iSize >> 32) & 0xffffffff;
      ::SetFilePointer(h,iSize & 0xffffffff,&l,SEEK_SET);
      SetEndOfFile(h);
   }

}

DWORD WinSetFilePointer(HANDLE h,LONG lMove,PLONG plHi,DWORD dwMeth)
{

   LARGE_INTEGER liMove;

   LARGE_INTEGER liRes;

   liRes.LowPart  = 0;

   liRes.HighPart = 0;

   liMove.LowPart = lMove;

   if(plHi != nullptr)
   {

      liMove.HighPart = *plHi;

   }
   else
   {

      liMove.HighPart = 0;

   }

   if(!SetFilePointerEx(h,liMove,&liRes,dwMeth))
      __throw(::exception::exception("SetFilePointer error"));

   if(plHi != nullptr)
   {

      *plHi = liRes.HighPart;

   }

   return liRes.LowPart;


}

DWORD GetFileSize(HANDLE h,LPDWORD lpdwHi)
{

   FILE_STANDARD_INFO info;

   if(!GetFileInformationByHandleEx(h,FileStandardInfo,&info,sizeof(info)))
      __throw(::exception::exception("GetFileSize Error"));

   if(lpdwHi != nullptr)
   {
      *lpdwHi = info.EndOfFile.HighPart;
   }

   return info.EndOfFile.LowPart;

}


DWORD WinGetFileAttributes(const unichar * psz)
{

   WIN32_FILE_ATTRIBUTE_DATA data;

   zero(&data,sizeof(data));


   if(!::GetFileAttributesExW(psz,GetFileExInfoStandard,&data))
   {
      DWORD dwLastError = ::get_last_error();
      return INVALID_FILE_ATTRIBUTES;
   }

   return data.dwFileAttributes;

}




HANDLE WinFindFirstFileW(const unichar * pwsz,WIN32_FIND_DATAW * pdata)
{

   return FindFirstFileExW(pwsz,FindExInfoStandard,pdata,FindExSearchNameMatch,nullptr,0);

}

HANDLE WinFindFirstFileA(const char * pwsz,WIN32_FIND_DATAA * pdata)
{

   return FindFirstFileExA(pwsz,FindExInfoStandard,pdata,FindExSearchNameMatch,nullptr,0);

}



/*
int_bool WINAPI FileTimeToLocalFileTime(const FILETIME * lpFileTime, LPFILETIME lpLocalFileTime)
{

SYSTEMTIME st;

__memset(&st, 0, sizeof(st));

if(FileTimeToSystemTime(lpFileTime, &st))
return FALSE;

SYSTEMTIME stLocal;

__memset(&stLocal, 0, sizeof(stLocal));

if(!SystemTimeToTzSpecificLocalTime(nullptr, &st, &stLocal))
return FALSE;

if(!SystemTimeToFileTime(&stLocal, lpLocalFileTime))
return FALSE;


return TRUE;


}


*/

HANDLE create_file(const char * lpcszFileName,DWORD dwDesiredAcces,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSA,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)
{

   CREATEFILE2_EXTENDED_PARAMETERS ps;

   __memset(&ps,0,sizeof(ps));

   ps.dwSize                  = sizeof(ps);
   ps.dwFileAttributes        = dwFlagsAndAttributes;
   ps.lpSecurityAttributes    = lpSA;
   ps.hTemplateFile           = hTemplateFile;

   wstring wstr(lpcszFileName);

   return ::CreateFile2(wstr,dwDesiredAcces,dwShareMode,dwCreationDisposition,&ps);

}


int_bool close_handle(HANDLE h)
{

   return ::CloseHandle(h) != FALSE;

}


::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName)
{

   return wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(lpcszDirName)));

}


::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName,DWORD dwDesiredAcces,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSA,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)
{

   /*
   CREATE_ALWAYS
   2
   Creates a new file, always.
   If the specified file exists and is writable, the function overwrites the file, the function succeeds, and last-error code is set to ERROR_ALREADY_EXISTS (183).
   If the specified file does not exist and is a valid path, a new file is created, the function succeeds, and the last-error code is set to zero.
   For more information, see the Remarks section of this topic.

   CREATE_NEW
   1
   Creates a new file, only if it does not already exist.
   If the specified file exists, the function fails and the last-error code is set to ERROR_FILE_EXISTS (80).
   If the specified file does not exist and is a valid path to a writable location, a new file is created.

   OPEN_ALWAYS
   4
   Opens a file, always.
   If the specified file exists, the function succeeds and the last-error code is set to ERROR_ALREADY_EXISTS (183).
   If the specified file does not exist and is a valid path to a writable location, the function creates a file and the last-error code is set to zero.

   OPEN_EXISTING
   3
   Opens a file or device, only if it exists.
   If the specified file or device does not exist, the function fails and the last-error code is set to ERROR_FILE_NOT_FOUND (2).
   For more information about devices, see the Remarks section.

   TRUNCATE_EXISTING
   5
   Opens a file and truncates it so that its size is zero bytes, only if it exists.
   If the specified file does not exist, the function fails and the last-error code is set to ERROR_FILE_NOT_FOUND (2).
   The calling process must open the file with the GENERIC_WRITE bit set as part of the dwDesiredAccess parameter.

   */

   ::Windows::Storage::StorageFile ^ file = nullptr;

   string strPrefix;

   string strRelative;

   ::Windows::Storage::StorageFolder ^ folder = winrt_get_folder(lpcszFileName, strPrefix, strRelative);

   if (folder == nullptr)
   {

      return nullptr;

   }

   if(dwCreationDisposition == CREATE_ALWAYS)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::ReplaceExisting;

      file = wait(folder->CreateFileAsync(strRelative,optionNew));

   }
   else if(dwCreationDisposition == CREATE_NEW)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::FailIfExists;

      file = wait(folder->CreateFileAsync(strRelative,optionNew));

   }
   else if(dwCreationDisposition == OPEN_ALWAYS)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::OpenIfExists;

      file = wait(folder->CreateFileAsync(strRelative,optionNew));

   }
   else if(dwCreationDisposition == OPEN_EXISTING)
   {

      file = wait(folder->GetFileAsync(strRelative));

   }
   else if(dwCreationDisposition == TRUNCATE_EXISTING)
   {

      file = wait(folder->GetFileAsync(strRelative));

      ::Windows::Storage::StorageStreamTransaction ^ transaction = wait(file->OpenTransactedWriteAsync());

      transaction->Stream->Size = 0;

   }

   return file;

}


bool get_file_time(::Windows::Storage::StorageFile ^ file,LPFILETIME lpCreationTime,LPFILETIME lpItemTime,LPFILETIME lpLastWriteTime)
{

   if(lpCreationTime != nullptr)
   {

      *lpCreationTime = (FILETIME &)file->DateCreated;

   }

   if(lpItemTime != nullptr || lpLastWriteTime != nullptr)
   {

      ::Windows::Storage::FileProperties::BasicProperties ^ properties = wait(file->GetBasicPropertiesAsync());

      if(lpItemTime != nullptr)
      {
         *lpItemTime = (FILETIME &)properties->ItemDate;
      }

      if(lpLastWriteTime != nullptr)
      {
         *lpLastWriteTime = (FILETIME &)properties->DateModified;
      }

   }

   return true;

}




::file::path dir::sys_temp()
{

   return ::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path->Begin();

}


//
//int_bool file_exists(const char * path1)
//{
//
//   string str(path1);
//   str.replace("/","\\");
//   wstring wstr(L"\\\\?\\");
//   wstr = wstr + wstring(str);
//   u32 dwFileAttributes = ::windows_get_file_attributes(wstr);
//   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
//      return true;
//   else
//      return false;
//
//}
//


//int_bool file_put_contents_dup(const char * path,const char * contents,::count len)
//{
//
//   dir::mk(dir::name(path));
//
//   wstring wstr(path);
//
//
//
//   HANDLE hfile = ::create_file(path,GENERIC_WRITE,0,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
//   if(hfile == INVALID_HANDLE_VALUE)
//      return false;
//   count dwWrite;
//   if(len < 0)
//      dwWrite = ansi_length(contents);
//   else
//      dwWrite = len;
//   DWORD dwWritten = 0;
//   bool bOk = ::WriteFile(hfile,contents,(u32)dwWrite,&dwWritten,nullptr) != FALSE;
//   ::CloseHandle(hfile);
//   return dwWrite == dwWritten && bOk != FALSE;
//
//}




string file_as_string(const char * path, strsize iReadAtMostByteCount)
{

   string str;

   HANDLE hfile = ::create_file(path,GENERIC_READ,0,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   DWORD dwSizeHigh;

   u32 dwSize = ::GetFileSize(hfile,&dwSizeHigh);

   if (iReadAtMostByteCount < 0)
   {

      dwSize = dwSize + iReadAtMostByteCount + 1;

   }
   else
   {

      dwSize = iReadAtMostByteCount;

   }

   char * psz = str.get_string_buffer(dwSize);

   DWORD dwRead;

   ::ReadFile(hfile,psz,dwSize,&dwRead,nullptr);

   psz[dwSize] = '\0';

   str.release_string_buffer();

   ::CloseHandle(hfile);

   return str;

}


bool file_as_memory(memory_base & memory,const char * path, iptr iReadAtMostByteCount)
{

   memory.set_size(0);

   HANDLE hfile = ::create_file(path,GENERIC_READ,0,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);

   if (hfile == INVALID_HANDLE_VALUE)
   {

      return false;

   }

   DWORD dwSizeHigh;

   ::count  count = ::GetFileSize(hfile,&dwSizeHigh);

   iReadAtMostByteCount = min_non_neg(count, iReadAtMostByteCount);

   memory.set_size(iReadAtMostByteCount);

   DWORD dwRead;

   ::ReadFile(hfile,memory.get_data(),(u32)memory.get_size(),&dwRead,nullptr);

   ::CloseHandle(hfile);

   return true;

}




int_bool file_is_equal_path(const char * psz1,const char * psz2)
{

   return normalize_path(psz1).compare_ci(normalize_path(psz2)) == 0;

}


string file_get_mozilla_firefox_plugin_container_path()
{

   __throw(::exception::exception(" todo "));

   return "";

}




//
//
//
//int ftruncate(int file,filesize len)
//{
//   return _chsize_s(file,len);
//}
//


int_bool file_set_length(const char * pszName,size_t iSize)
{

   int i = open(pszName,0);

   ftruncate(i,iSize);

   ::close(i);

   return true;

}




bool file_copy_dup(const char  * pszNew, const char * pszSrc,bool bOverwrite)
{

   ::Windows::Storage::StorageFolder ^ folder = nullptr;

   try
   {

      folder = get_os_folder(::dir::name(pszNew));

      if(folder == nullptr)
         return false;

   }
   catch(::Exception ^ ex)
   {

      return false;

   }


   ::Windows::Storage::StorageFile ^ fileSrc = nullptr;

   try
   {

      fileSrc = get_os_file(pszSrc,0,0,nullptr,OPEN_EXISTING,0,nullptr);

      if(fileSrc == nullptr)
         return false;

   }
   catch(::Exception ^ ex)
   {

      return false;

   }

   wstring wstrNew(pszNew);

   return ::wait(fileSrc->CopyAsync(folder,wstrNew,bOverwrite ?
                                    ::Windows::Storage::NameCollisionOption::ReplaceExisting :
                                    ::Windows::Storage::NameCollisionOption::FailIfExists)) ? TRUE : FALSE;


}



filesize fsize_dup(HANDLE h)
{

   DWORD dwHi;

   DWORD dwLo = ::GetFileSize(h, &dwHi);

   return dwLo | (((DWORD64) dwHi) << 32);

}


