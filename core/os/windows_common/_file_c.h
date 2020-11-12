#pragma once





CLASS_DECL_CORE ::u32 windows_get_file_attributes(const char* path);
CLASS_DECL_CORE int_bool window_create_directory(const char* pszPath, LPSECURITY_ATTRIBUTES lpSecurityAttributes);








CLASS_DECL_CORE HANDLE create_file(
const char *            pFileName,

::u32                   dwDesiredAccess,
::u32                   dwShareMode,
LPSECURITY_ATTRIBUTES   pSecurityAttributes,

::u32                   dwCreationDisposition,
::u32                   dwFlagsAndAttributes,
HANDLE                  hTemplateFile
);
