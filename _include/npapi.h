/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef npapi_h_
#define npapi_h_

#ifdef __OS2__
#pragma pack(1)
#endif

#include "nptypes.h"

#if defined (__OS2__) || defined (OS2)
# ifndef XP_OS2
#  define XP_OS2 1
# endif /* XP_OS2 */
#endif /* __OS2__ */

#ifdef _WINDOWS
# include <windef.h>
# ifndef XP_WIN
#  define XP_WIN 1
# endif /* XP_WIN */
#endif /* _WINDOWS */

#ifdef XP_MACOSX
#ifdef __LP64__
#define NP_NO_QUICKDRAW
#else
#include <Carbon/Carbon.h>
#endif
#endif

#if defined(XP_UNIX)
# include <stdio.h>
# if defined(MOZ_X11)
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
# endif
#endif

/*----------------------------------------------------------------------*/
/*                        Plugin Version Constants                      */
/*----------------------------------------------------------------------*/

#define NP_VERSION_MAJOR 0
#define NP_VERSION_MINOR 22


/* The OS/2 version of Netscape uses RC_DATA to define the
   mime types, file extensions, etc that are required.
   Use a vertical bar to separate types, end types with \0.
   FileVersion and ProductVersion are 32bit ints, all other
   entries are strings the MUST be terminated wwith a \0.

AN EXAMPLE:

RCDATA NP_INFO_ProductVersion { 1,0,0,1,}

RCDATA NP_INFO_MIMEType    { "video/x-video|",
                             "video/x-flick\0" }
RCDATA NP_INFO_FileExtents { "avi|",
                             "flc\0" }
RCDATA NP_INFO_FileOpenName{ "MMOS2 video player(*.avi)|",
                             "MMOS2 Flc/Fli player(*.flc)\0" }

RCDATA NP_INFO_FileVersion       { 1,0,0,1 }
RCDATA NP_INFO_CompanyName       { "Netscape Communications\0" }
RCDATA NP_INFO_FileDescription   { "NPAVI32 Extension DLL\0"
RCDATA NP_INFO_InternalName      { "NPAVI32\0" )
RCDATA NP_INFO_LegalCopyright    { "Copyright Netscape Communications \251 1996\0"
RCDATA NP_INFO_OriginalFilename  { "NVAPI32.DLL" }
RCDATA NP_INFO_ProductName       { "NPAVI32 Dynamic Link Library\0" }
*/
/* RC_DATA types for version info - required */
#define NP_INFO_ProductVersion      1
#define NP_INFO_MIMEType            2
#define NP_INFO_FileOpenName        3
#define NP_INFO_FileExtents         4
/* RC_DATA types for version info - used if found */
#define NP_INFO_FileDescription     5
#define NP_INFO_ProductName         6
/* RC_DATA types for version info - optional */
#define NP_INFO_CompanyName         7
#define NP_INFO_FileVersion         8
#define NP_INFO_InternalName        9
#define NP_INFO_LegalCopyright      10
#define NP_INFO_OriginalFilename    11

#ifndef RC_INVOKED

/*----------------------------------------------------------------------*/
/*                       Definition of Basic Types                      */
/*----------------------------------------------------------------------*/

typedef unsigned char NPBool;
typedef int16_t       NPError;
typedef int16_t       NPReason;
typedef char*         NPMIMEType;

/*----------------------------------------------------------------------*/
/*                       Structures and definitions                     */
/*----------------------------------------------------------------------*/

#if !defined(__LP64__)
#if defined(XP_MAC) || defined(XP_MACOSX)
#pragma options align=mac68k
#endif
#endif /* __LP64__ */

/*
 *  NPP is a plug-in's opaque instance handle
 */
typedef struct _NPP
{
   void* pdata;      /* plug-in private data */
   void* ndata;      /* netscape private data */
} NPP_t;

typedef NPP_t*  NPP;

typedef struct _NPStream
{
   void*    pdata; /* plug-in private data */
   void*    ndata; /* netscape private data */
   const    char* url;
   ::u32 end;
   ::u32 lastmodified;
   void*    notifyData;
   const    char* headers; /* Response headers from host.
                           * Exists only for >= NPVERS_HAS_RESPONSE_HEADERS.
                           * Used for HTTP only; NULL for non-HTTP.
                           * Available from NPP_NewStream onwards.
                           * Plugin should copy this data before storing it.
                           * Includes HTTP status line and all headers,
                           * preferably verbatim as received from server,
                           * headers formatted as in HTTP ("Header: Value"),
                           * and newlines (\n, NOT \r\n) separating lines.
                           * Terminated by \n\0 (NOT \n\n\0). */
} NPStream;

typedef struct _NPByteRange
{
   int32_t  offset; /* negative offset means from the end */
   ::u32 length;
   struct _NPByteRange* next;
} NPByteRange;

typedef struct _NPSavedData
{
   int32_t len;
   void*   buf;
} NPSavedData;

typedef struct _NPRect
{
   ::u3216_t top;
   ::u3216_t left;
   ::u3216_t bottom;
   ::u3216_t right;
} NPRect;

typedef struct _NPSize
{
   int32_t width;
   int32_t height;
} NPSize;

#ifdef XP_UNIX
/*
 * Unix specific structures and definitions
 */

/*
 * Callback Structures.
 *
 * These are used to pass additional platform specific information.
 */
enum
{
   NP_SETWINDOW = 1,
   NP_PRINT
};

typedef struct
{
   int32_t type;
} NPAnyCallbackStruct;

typedef struct
{
   int32_t      type;
#ifdef MOZ_X11
   Display*     display;
   Visual*      draw2d;
   Colormap     colormap;
   unsigned int depth;
#endif
} NPSetWindowCallbackStruct;

typedef struct
{
   int32_t type;
   FILE* fp;
} NPPrintCallbackStruct;

#endif /* XP_UNIX */

#ifdef XP_MACOSX
typedef enum
{
#ifndef NP_NO_QUICKDRAW
   NPDrawingModelQuickDraw = 0,
#endif
   NPDrawingModelCoreGraphics = 1
} NPDrawingModel;
#endif

/*
 *   The following masks are applied on certain platforms to NPNV and
 *   NPPV selectors that pass around pointers to COM interfaces. Newer
 *   compilers on some platforms may generate vtables that are not
 *   compatible with older compilers. To prevent older plugins from
 *   not understanding a new browser's ABI, these masks change the
 *   values of those selectors on those platforms. To remain backwards
 *   compatible with differenet versions of the browser, plugins can
 *   use these masks to dynamically determine and use the correct C++
 *   ABI that the browser is expecting. This does not apply to Windows
 *   as Microsoft's COM ABI will likely not change.
 */

#define NP_ABI_GCC3_MASK  0x10000000
/*
 *   gcc 3.x generated vtables on UNIX and OSX are incompatible with
 *   previous compilers.
 */
#if (defined(XP_UNIX) && defined(__GNUC__) && (__GNUC__ >= 3))
#define _NP_ABI_MIXIN_FOR_GCC3 NP_ABI_GCC3_MASK
#else
#define _NP_ABI_MIXIN_FOR_GCC3 0
#endif

#ifdef XP_MACOSX
#define NP_ABI_MACHO_MASK 0x01000000
#define _NP_ABI_MIXIN_FOR_MACHO NP_ABI_MACHO_MASK
#else
#define _NP_ABI_MIXIN_FOR_MACHO 0
#endif

#define NP_ABI_MASK (_NP_ABI_MIXIN_FOR_GCC3 | _NP_ABI_MIXIN_FOR_MACHO)

/*
 * List of variable names for which NPP_GetValue shall be implemented
 */
typedef enum
{
   NPPVpluginNameString = 1,
   NPPVpluginDescriptionString,
   NPPVpluginWindowBool,
   NPPVpluginTransparentBool,
   NPPVjavaClass,                /* Not implemented in Mozilla 1.0 */
   NPPVpluginWindowSize,
   NPPVpluginTimerInterval,

   NPPVpluginScriptableInstance = (10 | NP_ABI_MASK),
   NPPVpluginScriptableIID = 11,

   /* Introduced in Mozilla 0.9.9 */
   NPPVjavascriptPushCallerBool = 12,

   /* Introduced in Mozilla 1.0 */
   NPPVpluginKeepLibraryInMemory = 13,
   NPPVpluginNeedsXEmbed         = 14,

   /* Get the NPObject for scripting the plugin. Introduced in Firefox
    * 1.0 (NPAPI minor version 14).
    */
   NPPVpluginScriptableNPObject  = 15,

   /* Get the plugin value (as \0-terminated UTF-8 string data) for
    * form submission if the plugin is part of a form. Use
    * NPN_MemAlloc() to allocate memory for the string data. Introduced
    * in Mozilla 1.8b2 (NPAPI minor version 15).
    */
   NPPVformValue = 16,

   NPPVpluginUrlRequestsDisplayedBool = 17,

   /* Checks if the plugin is interested in receiving the http body of
    * all http requests (including failed ones, http status != 200).
    */
   NPPVpluginWantsAllNetworkStreams = 18

#ifdef XP_MACOSX
                                      /* Used for negotiating drawing models */
   , NPPVpluginDrawingModel = 1000
#endif

#ifdef MOZ_PLATFORM_HILDON
   , NPPVpluginWindowlessLocalBool = 2002
#endif
} NPPVariable;

/*
 * List of variable names for which NPN_GetValue is implemented by Mozilla
 */
typedef enum
{
   NPNVxDisplay = 1,
   NPNVxtAppContext,
   NPNVnetscapeWindow,
   NPNVjavascriptEnabledBool,
   NPNVasdEnabledBool,
   NPNVisOfflineBool,

   /* 10 and over are available on Mozilla builds starting with 0.9.4 */
   NPNVserviceManager = (10 | NP_ABI_MASK),
   NPNVDOMElement     = (11 | NP_ABI_MASK),   /* available in Mozilla 1.2 */
   NPNVDOMWindow      = (12 | NP_ABI_MASK),
   NPNVToolkit        = (13 | NP_ABI_MASK),
   NPNVSupportsXEmbedBool = 14,

   /* Get the NPObject wrapper for the browser window. */
   NPNVWindowNPObject = 15,

   /* Get the NPObject wrapper for the plugins DOM matter. */
   NPNVPluginElementNPObject = 16,

   NPNVSupportsWindowless = 17,

   NPNVprivateModeBool = 18

#ifdef XP_MACOSX
                         /* Used for negotiating drawing models */
   , NPNVpluginDrawingModel = 1000
#ifndef NP_NO_QUICKDRAW
   , NPNVsupportsQuickDrawBool = 2000
#endif
   , NPNVsupportsCoreGraphicsBool = 2001
#endif

#ifdef MOZ_PLATFORM_HILDON
   , NPNVSupportsWindowlessLocal = 2002
#endif

} NPNVariable;

typedef enum
{
   NPNURLVCookie = 501,
   NPNURLVProxy
} NPNURLVariable;

/*
 * The type of Tookkit the widgets use
 */
typedef enum
{
   NPNVGtk12 = 1,
   NPNVGtk2
} NPNToolkitType;

/*
 * The type of a NPWindow - it specifies the type of the data structure
 * returned in the window field.
 */
typedef enum
{
   NPWindowTypeWindow = 1,
   NPWindowTypeDrawable
} NPWindowType;

typedef struct _NPWindow
{
   void* window;  /* Platform specific window handle */
   /* OS/2: x - Position of bottom left corner */
   /* OS/2: y - relative to visible netscape window */
   int32_t  x;      /* Position of top left corner relative */
   int32_t  y;      /* to a netscape page. */
   ::u32 width;  /* Maximum window size_i32 */
   ::u32 height;
   NPRect   clipRect; /* Clipping rectangle_i32 in port coordinates */
   /* Used by MAC only. */
#if defined(XP_UNIX) && !defined(XP_MACOSX)
   void * ws_info; /* Platform-dependent additonal data */
#endif /* XP_UNIX */
   NPWindowType type; /* Is this a window or a drawable? */
} NPWindow;

typedef struct _NPImageExpose
{
/*   char*    data;       /* pimage pointer */
/*   int32_t  stride;     /* Stride of data image pointer */
/*   int32_t  depth;      /* Depth of image pointer */
   int32_t  x;          /* Expose x */
   int32_t  y;          /* Expose y */
   ::u32 width;      /* Expose width */
   ::u32 height;     /* Expose height */
   NPSize   dataSize;   /* Data buffer size_i32 */
   float    translateX; /* translate X matrix value */
   float    translateY; /* translate Y matrix value */
   float    scaleX;     /* scale X matrix value */
   float    scaleY;     /* scale Y matrix value */
} NPImageExpose;

typedef struct _NPFullPrint
{
   NPBool pluginPrinted;/* Set true if plugin handled fullscreen printing */
   NPBool printOne;     /* true if plugin should print one copy to default
                          printer */
   void* platformPrint; /* Platform-specific printing info */
} NPFullPrint;

typedef struct _NPEmbedPrint
{
   NPWindow window;
   void* platformPrint; /* Platform-specific printing info */
} NPEmbedPrint;

typedef struct _NPPrint
{
   ::u3216_t mode;               /* NP_FULL or NP_EMBED */
   union
   {
      NPFullPrint fullPrint;   /* if mode is NP_FULL */
      NPEmbedPrint embedPrint; /* if mode is NP_EMBED */
   } print;
} NPPrint;

#ifdef XP_MACOSX
typedef EventRecord NPEvent;
#elif defined(XP_WIN)
typedef struct _NPEvent
{
   ::u3216_t event;
   ::u32 wParam;
   ::u32 lParam;
} NPEvent;
#elif defined(XP_OS2)
typedef struct _NPEvent
{
   ::u32 event;
   ::u32 wParam;
   ::u32 lParam;
} NPEvent;
#elif defined (XP_UNIX) && defined(MOZ_X11)
typedef XEvent NPEvent;
#else
typedef void*  NPEvent;
#endif /* XP_MACOSX */

#ifdef XP_MACOSX

typedef void* NPRegion;
#ifndef NP_NO_QUICKDRAW
typedef RgnHandle NPQDRegion;
#endif
typedef CGPathRef NPCGRegion;
#elif defined(XP_WIN)
typedef HRGN NPRegion;
#elif defined(XP_UNIX) && defined(MOZ_X11)
typedef Region NPRegion;
#else
typedef void *NPRegion;
#endif

#ifdef XP_MACOSX
typedef struct NP_Port
{
   CGrafPtr port;
   int32_t portx; /* position inside the topmost window */
   int32_t porty;
} NP_Port;

typedef struct NP_CGContext
{
   CGContextRef action_context;
   WindowRef window;
} NP_CGContext;

/* Non-standard event types that can be passed to HandleEvent */
enum NPEventType
{
   NPEventType_GetFocusEvent = (osEvt + 16),
   NPEventType_LoseFocusEvent,
   NPEventType_AdjustCursorEvent,
   NPEventType_MenuCommandEvent,
   NPEventType_ClippingChangedEvent,
   NPEventType_ScrollingBeginsEvent = 1000,
   NPEventType_ScrollingEndsEvent
};

#ifdef OBSOLETE
#define getFocusEvent     (osEvt + 16)
#define loseFocusEvent    (osEvt + 17)
#define adjustCursorEvent (osEvt + 18)
#endif

#endif /* XP_MACOSX */

/*
 * Values for mode passed to NPP_New:
 */
#define NP_EMBED 1
#define NP_FULL  2

/*
 * Values for stream type passed to NPP_NewStream:
 */
#define NP_NORMAL     1
#define NP_SEEK       2
#define NP_ASFILE     3
#define NP_ASFILEONLY 4

#define NP_MAXREADY (((unsigned)(~0)<<1)>>1)

#if !defined(__LP64__)
#if defined(XP_MAC) || defined(XP_MACOSX)
#pragma options align=reset
#endif
#endif /* __LP64__ */

/*----------------------------------------------------------------------*/
/*       Error and Reason Code definitions                              */
/*----------------------------------------------------------------------*/

/*
 * Values of type NPError:
 */
#define NPERR_BASE                         0
#define NPERR_NO_ERROR                    (NPERR_BASE + 0)
#define NPERR_GENERIC_ERROR               (NPERR_BASE + 1)
#define NPERR_INVALID_INSTANCE_ERROR      (NPERR_BASE + 2)
#define NPERR_INVALID_FUNCTABLE_ERROR     (NPERR_BASE + 3)
#define NPERR_MODULE_LOAD_FAILED_ERROR    (NPERR_BASE + 4)
#define NPERR_OUT_OF_MEMORY_ERROR         (NPERR_BASE + 5)
#define NPERR_INVALID_PLUGIN_ERROR        (NPERR_BASE + 6)
#define NPERR_INVALID_PLUGIN_DIR_ERROR    (NPERR_BASE + 7)
#define NPERR_INCOMPATIBLE_VERSION_ERROR  (NPERR_BASE + 8)
#define NPERR_INVALID_PARAM               (NPERR_BASE + 9)
#define NPERR_INVALID_URL                 (NPERR_BASE + 10)
#define NPERR_FILE_NOT_FOUND              (NPERR_BASE + 11)
#define NPERR_NO_DATA                     (NPERR_BASE + 12)
#define NPERR_STREAM_NOT_SEEKABLE         (NPERR_BASE + 13)

/*
 * Values of type NPReason:
 */
#define NPRES_BASE          0
#define NPRES_DONE         (NPRES_BASE + 0)
#define NPRES_NETWORK_ERR  (NPRES_BASE + 1)
#define NPRES_USER_BREAK   (NPRES_BASE + 2)

/*
 * Don't use these obsolete error codes any more.
 */
#define NP_NOERR  NP_NOERR_is_obsolete_use_NPERR_NO_ERROR
#define NP_EINVAL NP_EINVAL_is_obsolete_use_NPERR_GENERIC_ERROR
#define NP_EABORT NP_EABORT_is_obsolete_use_NPRES_USER_BREAK

/*
 * Version feature information
 */
#define NPVERS_HAS_STREAMOUTPUT             8
#define NPVERS_HAS_NOTIFICATION             9
#define NPVERS_HAS_LIVECONNECT              9
#define NPVERS_68K_HAS_LIVECONNECT          11
#define NPVERS_HAS_WINDOWLESS               11
#define NPVERS_HAS_XPCONNECT_SCRIPTING      13
#define NPVERS_HAS_NPRUNTIME_SCRIPTING      14
#define NPVERS_HAS_FORM_VALUES              15
#define NPVERS_HAS_POPUPS_ENABLED_STATE     16
#define NPVERS_HAS_RESPONSE_HEADERS         17
#define NPVERS_HAS_NPOBJECT_ENUM            18
#define NPVERS_HAS_PLUGIN_THREAD_ASYNC_CALL 19
#define NPVERS_HAS_ALL_NETWORK_STREAMS      20
#define NPVERS_HAS_URL_AND_AUTH_INFO        21

/*----------------------------------------------------------------------*/
/*                        Function Prototypes                           */
/*----------------------------------------------------------------------*/

#if defined(__OS2__)
#define NP_LOADDS _System
#else
#define NP_LOADDS
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* NPP_* functions are provided by the plugin and called by the navigator. */

#ifdef XP_UNIX
char* NPP_GetMIMEDescription();
#endif

NPError NP_LOADDS NPP_Initialize();
void    NP_LOADDS NPP_Shutdown();
NPError NP_LOADDS NPP_New(NPMIMEType pluginType, NPP instance,
                          ::u3216_t mode, int16_t argc, char* argn[],
                          char* argv[], NPSavedData* saved);
NPError NP_LOADDS NPP_Destroy(NPP instance, NPSavedData** save);
NPError NP_LOADDS NPP_SetWindow(NPP instance, NPWindow* window);
NPError NP_LOADDS NPP_NewStream(NPP instance, NPMIMEType type,
                                NPStream* stream, NPBool seekable,
                                ::u3216_t* stype);
NPError NP_LOADDS NPP_DestroyStream(NPP instance, NPStream* stream,
                                    NPReason reason);
int32_t NP_LOADDS NPP_WriteReady(NPP instance, NPStream* stream);
int32_t NP_LOADDS NPP_Write(NPP instance, NPStream* stream, int32_t offset,
                            int32_t len, void* buffer);
void    NP_LOADDS NPP_StreamAsFile(NPP instance, NPStream* stream,
                                   const char* fname);
void    NP_LOADDS NPP_Print(NPP instance, NPPrint* platformPrint);
int16_t NP_LOADDS NPP_HandleEvent(NPP instance, void* event);
void    NP_LOADDS NPP_URLNotify(NPP instance, const ::string & url,
                                NPReason reason, void* notifyData);
NPError NP_LOADDS NPP_GetValue(NPP instance, NPPVariable variable, void *value);
NPError NP_LOADDS NPP_SetValue(NPP instance, NPNVariable variable, void *value);

/* NPN_* functions are provided by the navigator and called by the plugin. */
void        NP_LOADDS NPN_Version(int* plugin_major, int* plugin_minor,
                                  int* netscape_major, int* netscape_minor);
NPError     NP_LOADDS NPN_GetURLNotify(NPP instance, const ::string & url,
                                       const char* target, void* notifyData);
NPError     NP_LOADDS NPN_GetURL(NPP instance, const ::string & url,
                                 const char* target);
NPError     NP_LOADDS NPN_PostURLNotify(NPP instance, const ::string & url,
                                        const char* target, ::u32 len,
                                        const char* buf, NPBool file,
                                        void* notifyData);
NPError     NP_LOADDS NPN_PostURL(NPP instance, const ::string & url,
                                  const char* target, ::u32 len,
                                  const char* buf, NPBool file);
NPError     NP_LOADDS NPN_RequestRead(NPStream* stream, NPByteRange* rangeList);
NPError     NP_LOADDS NPN_NewStream(NPP instance, NPMIMEType type,
                                    const char* target, NPStream** stream);
int32_t     NP_LOADDS NPN_Write(NPP instance, NPStream* stream, int32_t len,
                                void* buffer);
NPError     NP_LOADDS NPN_DestroyStream(NPP instance, NPStream* stream,
                                        NPReason reason);
void        NP_LOADDS NPN_Status(NPP instance, const ::string & message);
const char* NP_LOADDS NPN_UserAgent(NPP instance);
void*       NP_LOADDS NPN_MemAlloc(::u32 size_i32);
void        NP_LOADDS NPN_MemFree(void* ptr);
::u32    NP_LOADDS NPN_MemFlush(::u32 size_i32);
void        NP_LOADDS NPN_ReloadPlugins(NPBool reloadPages);
NPError     NP_LOADDS NPN_GetValue(NPP instance, NPNVariable variable,
                                   void *value);
NPError     NP_LOADDS NPN_SetValue(NPP instance, NPPVariable variable,
                                   void *value);
void        NP_LOADDS NPN_InvalidateRect(NPP instance, NPRect *invalidRect);
void        NP_LOADDS NPN_InvalidateRegion(NPP instance,
      NPRegion invalidRegion);
void        NP_LOADDS NPN_ForceRedraw(NPP instance);
void        NP_LOADDS NPN_PushPopupsEnabledState(NPP instance, NPBool enabled);
void        NP_LOADDS NPN_PopPopupsEnabledState(NPP instance);
void        NP_LOADDS NPN_PluginThreadAsyncCall(NPP instance,
      void (*func) (void *),
      void *userData);
NPError     NP_LOADDS NPN_GetValueForURL(NPP instance, NPNURLVariable variable,
      const char *url, char **value,
      ::u32 *len);
NPError     NP_LOADDS NPN_SetValueForURL(NPP instance, NPNURLVariable variable,
      const char *url, const ::string &value,
      ::u32 len);
NPError     NP_LOADDS NPN_GetAuthenticationInfo(NPP instance,
      const char *protocol,
      const char *host, int32_t port,
      const char *scheme,
      const char *realm,
      char **username, ::u32 *ulen,
      char **password,
      ::u32 *plen);

#ifdef __cplusplus
}  /* end extern "C" */
#endif

#endif /* RC_INVOKED */
#ifdef __OS2__
#pragma pack()
#endif

#endif /* npapi_h_ */
