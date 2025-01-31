/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * FreeRDP Client Compatibility
 *
 * Copyright 2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <winpr/crt.h>
#include <winpr/cmdline.h>

#include <freerdp/addin.h>
#include <freerdp/settings.h>
#include <freerdp/client/channels.h>

#include <freerdp/locale/keyboard.h>

#include <freerdp/client/cmdline.h>
#include <freerdp/log.h>

#include "compatibility.h"

#define TAG CLIENT_TAG("common.compatibility")

COMMAND_LINE_ARGUMENT_A old_args[] =
{
	{ "0", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "connect to console session" },
	{ "a", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "set color depth in bits, default is 16" },
	{ "c", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "shell working directory" },
	{ "D", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "hide window decorations" },
	{ "T", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "Window title" },
	{ "d", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "domain" },
	{ "f", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "fullscreen mode" },
	{ "g", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "set geometry, using format WxH or X%% or 'workarea', default is 1024x768" },
	{ "h", COMMAND_LINE_VALUE_FLAG | COMMAND_LINE_PRINT_HELP, nullptr, nullptr, nullptr, -1, "help", "print this help" },
	{ "k", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "set keyboard on_layout ID" },
	{ "K", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "do not interfere with window manager bindings" },
	{ "n", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "hostname" },
	{ "o", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "console audio" },
	{ "p", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "password" },
	{ "s", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "set startup-shell" },
	{ "t", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "alternative port number, default is 3389" },
	{ "u", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "username" },
	{ "x", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "performance flags (m[odem], b[roadband] or l[an])" },
	{ "X", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "embed into another window with a given XID." },
	{ "z", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "enable compression" },
	{ "app", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "RemoteApp connection. This implies -g workarea" },
	{ "ext", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "load an extension" },
	{ "no-auth", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disable authentication" },
	{ "authonly", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "authentication only, no UI" },
	{ "from-stdin", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "unspecified username, password, domain and hostname params are prompted" },
	{ "no-fastpath", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disable fast-path" },
	{ "no-motion", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "don't send mouse motion events" },
	{ "gdi", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "graphics rendering (hw, sw)" },
	{ "no-osb", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disable offscreen bitmaps" },
	{ "no-bmp-cache", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disable bitmap cache" },
	{ "plugin", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "load a virtual channel plugin" },
	{ "rfx", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "enable RemoteFX" },
	{ "rfx-mode", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "RemoteFX operational flags (v[ideo], i[mage]), default is video" },
	{ "nsc", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "enable NSCodec (experimental)" },
	{ "disable-wallpaper", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disables wallpaper" },
	{ "composition", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "enable desktop composition" },
	{ "disable-full-window-drag", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disables full window drag" },
	{ "disable-menu-animations", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disables menu animations" },
	{ "disable-theming", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disables theming" },
	{ "no-rdp", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disable Standard RDP encryption" },
	{ "no-tls", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disable TLS encryption" },
	{ "no-nla", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "disable network level authentication" },
	{ "ntlm", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "force NTLM authentication protocol version (1 or 2)" },
	{ "ignore-certificate", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "ignore verification of logon certificate" },
	{ "sec", COMMAND_LINE_VALUE_REQUIRED, nullptr, nullptr, nullptr, -1, nullptr, "force protocol security (rdp, tls or nla)" },
	{ "secure-checksum", COMMAND_LINE_VALUE_FLAG, nullptr, nullptr, nullptr, -1, nullptr, "use salted checksums with Standard RDP encryption" },
	{ "version", COMMAND_LINE_VALUE_FLAG | COMMAND_LINE_PRINT_VERSION, nullptr, nullptr, nullptr, -1, nullptr, "print version information" },
	{ nullptr, 0, nullptr, nullptr, nullptr, -1, nullptr, nullptr }
};

BOOL freerdp_client_old_parse_hostname(char* str, char** ServerHostname, ::u32* ServerPort)
{
	char* p;

	if (str[0] == '[' && (p = strchr(str, ']'))
			&& (p[1] == 0 || (p[1] == ':' && !strchr(p + 2, ':'))))
	{
		/* Either "[...]" or "[...]:..." with at most one : after the brackets */
		if (!(*ServerHostname = _strdup(str + 1)))
			return false;

		if ((p = strchr((char*) *ServerHostname, ']')))
		{
			*p = 0;

			if (p[1] == ':')
				*ServerPort = atoi(p + 2);
		}
	}
	else
	{
		/* Port number is cut off and used if exactly one : in the string */
		if (!(*ServerHostname = _strdup(str)))
			return false;

		if ((p = strchr((char*) *ServerHostname, ':')) && !strchr(p + 1, ':'))
		{
			*p = 0;
			*ServerPort = atoi(p + 1);
		}
	}
	return true;
}

int freerdp_client_old_process_plugin(rdpSettings* settings, ADDIN_ARGV* args)
{
	int args_handled = 0;
	if (strcmp(args->argv[0], "cliprdr") == 0)
	{
		args_handled++;
		settings->RedirectClipboard = true;
		WLog_WARN(TAG,  "--plugin cliprdr -> +clipboard");
	}
	else if (strcmp(args->argv[0], "rdpdr") == 0)
	{
		args_handled++;
		if (args->argc < 2)
			return 1;

		args_handled++;
		if ((strcmp(args->argv[1], "disk") == 0) ||
			(strcmp(args->argv[1], "drive") == 0))
		{
			freerdp_addin_replace_argument(args, "disk", "drive");
			freerdp_client_add_device_channel(settings, args->argc - 1, &args->argv[1]);
		}
		else if (strcmp(args->argv[1], "printer") == 0)
		{
			freerdp_client_add_device_channel(settings, args->argc - 1, &args->argv[1]);
		}
		else if ((strcmp(args->argv[1], "scard") == 0) ||
				(strcmp(args->argv[1], "smartcard") == 0))
		{
			freerdp_addin_replace_argument(args, "scard", "smartcard");
			freerdp_client_add_device_channel(settings, args->argc - 1, &args->argv[1]);
		}
		else if (strcmp(args->argv[1], "serial") == 0)
		{
			freerdp_client_add_device_channel(settings, args->argc - 1, &args->argv[1]);
		}
		else if (strcmp(args->argv[1], "parallel") == 0)
		{
			freerdp_client_add_device_channel(settings, args->argc - 1, &args->argv[1]);
		}
	}
	else if (strcmp(args->argv[0], "drdynvc") == 0)
	{
		args_handled++;
		freerdp_client_add_dynamic_channel(settings, args->argc - 1, &args->argv[1]);
	}
	else if (strcmp(args->argv[0], "rdpsnd") == 0)
	{
		args_handled++;
		if (args->argc < 2)
			return 1;

		args_handled++;
		freerdp_addin_replace_argument_value(args, args->argv[1], "sys", args->argv[1]);
		freerdp_client_add_static_channel(settings, args->argc, args->argv);
	}
	else if (strcmp(args->argv[0], "rail") == 0)
	{
		args_handled++;
		if (args->argc < 2)
			return 1;

		args_handled++;
		if (!(settings->RemoteApplicationProgram = _strdup(args->argv[1])))
			return -1;
	}
	else
	{
		freerdp_client_add_static_channel(settings, args->argc, args->argv);
	}

	return args_handled;
}

int freerdp_client_old_command_line_pre_filter(void* context, int index, int argc, const ::string &* argv)
{
	rdpSettings* settings = (rdpSettings*) context;

	if (index == (argc - 1))
	{
		if (argv[index][0] != '-')
		{
			if ((strcmp(argv[index - 1], "-v") == 0) ||
					(strcmp(argv[index - 1], "/v") == 0))
			{
				return -1;
			}
			if (_stricmp(&(argv[index])[strlen(argv[index])- 4], ".rdp") == 0)
			{
				return -1;
			}

			if (!freerdp_client_old_parse_hostname((char*) argv[index],
					&settings->ServerHostname, &settings->ServerPort))
				return -1;

			return 2;
		}
		else
		{
			return -1;
		}
	}

	if (strcmp("--plugin", argv[index]) == 0)
	{
		int args_handled = 0;
		int length;
		char *a, *p;
		int i, j, t;
		int old_index;
		ADDIN_ARGV* args;

		old_index = index;

		index++;
		t = index;

		if (index == argc)
			return -1;

		args = (ADDIN_ARGV*) malloc(sizeof(ADDIN_ARGV));
		if (!args)
			return -1;
		args->argv = (char**) calloc(argc, sizeof(char*));
		if (!args->argv)
		{
			free(args);
			return -1;
		}
		args->argc = 1;

		if ((index < argc - 1) && strcmp("--data", argv[index + 1]) == 0)
		{
			i = 0;
			index += 2;

			while ((index < argc) && (strcmp("--", argv[index]) != 0))
			{
				args_handled++;
				args->argc = 1;
				if (!(args->argv[0] = _strdup(argv[t])))
				{
					free(args->argv);
					free(args);
					return -1;
				}

				for (j = 0, p = (char*) argv[index]; (j < 4) && (p != nullptr); j++)
				{
					if (*p == '\'')
					{
						a = p + 1;

						p = strchr(p + 1, '\'');

						if (p)
							*p++ = 0;
					}
					else
					{
						a = p;
					}

					if (p != nullptr)
					{
						p = strchr(p, ':');
					}
					if (p != nullptr)
					{
						length = (int) (p - a);
						if (!(args->argv[j + 1] = (char*) malloc(length + 1)))
						{
							for (; j >= 0; --j)
								free(args->argv[j]);

							free(args->argv);
							free(args);
							return -1;
						}
						CopyMemory(args->argv[j + 1], a, length);
						args->argv[j + 1][length] = '\0';
						p++;
					}
					else
					{
						if (!(args->argv[j + 1] = _strdup(a)))
						{
							for (; j >= 0; --j)
								free(args->argv[j]);

							free(args->argv);
							free(args);
							return -1;

						}
					}

					args->argc++;
				}

				if (settings)
				{
					freerdp_client_old_process_plugin(settings, args);
				}

				for (i = 0; i < args->argc; i++)
					free(args->argv[i]);
				__memset(args->argv, 0, argc * sizeof(char*));
				index++;
				i++;
			}
		}
		else
		{
			if (settings)
			{
				if (!(args->argv[0] = _strdup(argv[t])))
				{
					free(args->argv);
					free(args);
					return -1;
				}
				args_handled = freerdp_client_old_process_plugin(settings, args);
				free (args->argv[0]);
			}
		}

		free(args->argv);
		free(args);

		return (index - old_index) + args_handled;
	}

	return 0;
}

int freerdp_client_old_command_line_post_filter(void* context, COMMAND_LINE_ARGUMENT_A* arg)
{
	return 0;
}

int freerdp_detect_old_command_line_syntax(int argc, char** argv, int* count)
{
	int status;
	::u32 flags;
	int detect_status;
	rdpSettings* settings;
	COMMAND_LINE_ARGUMENT_A* arg;

	*count = 0;
	detect_status = 0;
	flags = COMMAND_LINE_SEPARATOR_SPACE;
	flags |= COMMAND_LINE_SIGIL_DASH | COMMAND_LINE_SIGIL_DOUBLE_DASH;
	flags |= COMMAND_LINE_SIGIL_NOT_ESCAPED;

	settings = (rdpSettings*) calloc(1, sizeof(rdpSettings));

	if (!settings)
		return -1;

	CommandLineClearArgumentsA(old_args);

	status = CommandLineParseArgumentsA(argc, (const ::string &*) argv, old_args, flags, settings,
			freerdp_client_old_command_line_pre_filter, nullptr);

	if (status < 0)
	{
		free(settings);
		return status;
	}

	arg = old_args;

	do
	{
		if (!(arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT))
			continue;

		CommandLineSwitchStart(arg)

		CommandLineSwitchCase(arg, "a")
		{
			if ((strcmp(arg->Value, "8") == 0) ||
				(strcmp(arg->Value, "15") == 0) || (strcmp(arg->Value, "16") == 0) ||
				(strcmp(arg->Value, "24") == 0) || (strcmp(arg->Value, "32") == 0))
			{
				detect_status = 1;
			}

		}
		CommandLineSwitchDefault(arg)
		{

		}

		CommandLineSwitchEnd(arg)

		(*count)++;
	}
	while ((arg = CommandLineFindNextArgumentA(arg)) != nullptr);

	if ((status <= COMMAND_LINE_ERROR) && (status >= COMMAND_LINE_ERROR_LAST))
		detect_status = -1;

	if (detect_status == 0)
	{
		if (settings->ServerHostname)
			detect_status = 1;
	}

	free(settings->ServerHostname);
	free(settings);

	return detect_status;
}

int freerdp_client_parse_old_command_line_arguments(int argc, char** argv, rdpSettings* settings)
{
	char* p;
	char* str;
	int status;
	::u32 flags;
	COMMAND_LINE_ARGUMENT_A* arg;

	freerdp_register_addin_provider((FREERDP_LOAD_CHANNEL_ADDIN_ENTRY_FN) freerdp_channels_load_static_addin_entry, 0);

	flags = COMMAND_LINE_SEPARATOR_SPACE;
	flags |= COMMAND_LINE_SIGIL_DASH | COMMAND_LINE_SIGIL_DOUBLE_DASH;
	flags |= COMMAND_LINE_SIGIL_ENABLE_DISABLE;
	flags |= COMMAND_LINE_SIGIL_NOT_ESCAPED;

	status = CommandLineParseArgumentsA(argc, (const ::string &*) argv, old_args, flags, settings,
			freerdp_client_old_command_line_pre_filter, freerdp_client_old_command_line_post_filter);

	if (status == COMMAND_LINE_STATUS_PRINT_VERSION)
	{
		freerdp_client_print_version();
		return COMMAND_LINE_STATUS_PRINT_VERSION;
	}
	else if (status == COMMAND_LINE_STATUS_PRINT)
	{
		return COMMAND_LINE_STATUS_PRINT;
	}
	else if (status < 0)
	{
		if (status != COMMAND_LINE_STATUS_PRINT_HELP)
		{

		}
		freerdp_client_print_command_line_help(argc, argv);
		return COMMAND_LINE_STATUS_PRINT_HELP;
	}

	arg = old_args;

	do
	{
		if (!(arg->Flags & COMMAND_LINE_ARGUMENT_PRESENT))
			continue;

		CommandLineSwitchStart(arg)

		CommandLineSwitchCase(arg, "0")
		{
			settings->ConsoleSession = true;
			WLog_WARN(TAG,  "-0 -> /admin");
		}
		CommandLineSwitchCase(arg, "a")
		{
			settings->ColorDepth = atoi(arg->Value);
			WLog_WARN(TAG,  "-a %s -> /bpp:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "c")
		{
			WLog_WARN(TAG,  "-c %s -> /shell-dir:%s", arg->Value, arg->Value);
			if (!(settings->ShellWorkingDirectory = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
		}
		CommandLineSwitchCase(arg, "D")
		{
			settings->Decorations = false;
			WLog_WARN(TAG,  "-D -> -decorations");
		}
		CommandLineSwitchCase(arg, "T")
		{
			if (!(settings->WindowTitle = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			WLog_WARN(TAG,  "-T %s -> /title:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "d")
		{
			if (!(settings->Domain = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			WLog_WARN(TAG,  "-d %s -> /d:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "f")
		{
			settings->Fullscreen = true;
			WLog_WARN(TAG,  "-f -> /f");
		}
		CommandLineSwitchCase(arg, "g")
		{
			if (!(str = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;

			p = strchr(str, 'x');

			if (p)
			{
				*p = '\0';
				settings->DesktopWidth = atoi(str);
				settings->DesktopHeight = atoi(&p[1]);
			}

			free(str);
			WLog_WARN(TAG,  "-g %s -> /size_i32:%s or /w:%d /h:%d", arg->Value, arg->Value,
					  settings->DesktopWidth, settings->DesktopHeight);
		}
		CommandLineSwitchCase(arg, "k")
		{
			sscanf(arg->Value, "%X", &(settings->KeyboardLayout));
			WLog_WARN(TAG,  "-k %s -> /kbd:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "K")
		{
			settings->GrabKeyboard = false;
			WLog_WARN(TAG,  "-K -> -grab-keyboard");
		}
		CommandLineSwitchCase(arg, "n")
		{
			if (!(settings->ClientHostname = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			WLog_WARN(TAG,  "-n -> /client-hostname:%s", arg->Value);
		}
		CommandLineSwitchCase(arg, "o")
		{
			settings->RemoteConsoleAudio = true;
			WLog_WARN(TAG,  "-o -> /audio-mode:1");
		}
		CommandLineSwitchCase(arg, "p")
		{
			if (!(settings->Password = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			WLog_WARN(TAG,  "-p ****** -> /p:******");
			/* Hide the value from 'ps'. */
			FillMemory(arg->Value, strlen(arg->Value), '*');
		}
		CommandLineSwitchCase(arg, "s")
		{
			if (!(settings->AlternateShell = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			WLog_WARN(TAG,  "-s %s -> /shell:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "t")
		{
			settings->ServerPort = atoi(arg->Value);
			WLog_WARN(TAG,  "-t %s -> /port:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "u")
		{
			if (!(settings->Username = _strdup(arg->Value)))
				return COMMAND_LINE_ERROR_MEMORY;
			WLog_WARN(TAG,  "-u %s -> /u:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "x")
		{
			int type;
			char* pEnd;

			type = strtol(arg->Value, &pEnd, 16);

			if (type == 0)
			{
				type = CONNECTION_TYPE_LAN;

				if (_stricmp(arg->Value, "m") == 0)
					type = CONNECTION_TYPE_MODEM;
				else if (_stricmp(arg->Value, "b") == 0)
					type = CONNECTION_TYPE_BROADBAND_HIGH;
				else if (_stricmp(arg->Value, "l") == 0)
					type = CONNECTION_TYPE_LAN;

				freerdp_set_connection_type(settings, type);
			}
			else
			{
				settings->PerformanceFlags = type;
				freerdp_performance_flags_split(settings);
			}

			WLog_WARN(TAG,  "-x %s -> /network:", arg->Value);

			if (type == CONNECTION_TYPE_MODEM)
				WLog_WARN(TAG,  "modem");
			else if (CONNECTION_TYPE_BROADBAND_HIGH)
				WLog_WARN(TAG,  "broadband");
			else if (CONNECTION_TYPE_LAN)
				WLog_WARN(TAG,  "lan");

			WLog_WARN(TAG,  "");
		}
		CommandLineSwitchCase(arg, "X")
		{
			settings->ParentWindowId = strtol(arg->Value, nullptr, 0);
			WLog_WARN(TAG,  "-X %s -> /parent-window:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "z")
		{
			settings->CompressionEnabled = true;
			WLog_WARN(TAG,  "-z -> /compression");
		}
		CommandLineSwitchCase(arg, "app")
		{
			settings->RemoteApplicationMode = true;
			WLog_WARN(TAG,  "--app -> /app: + program name or alias");
		}
		CommandLineSwitchCase(arg, "ext")
		{

		}
		CommandLineSwitchCase(arg, "no-auth")
		{
			settings->Authentication = false;
			WLog_WARN(TAG,  "--no-auth -> -authentication");
		}
		CommandLineSwitchCase(arg, "authonly")
		{
			settings->AuthenticationOnly = true;
		}
		CommandLineSwitchCase(arg, "from-stdin")
		{
			settings->CredentialsFromStdin = true;
		}
		CommandLineSwitchCase(arg, "no-fastpath")
		{
			settings->FastPathInput = false;
			settings->FastPathOutput = false;
			WLog_WARN(TAG,  "--no-fastpath -> -fast-path");
		}
		CommandLineSwitchCase(arg, "no-motion")
		{
			settings->MouseMotion = false;
			WLog_WARN(TAG,  "--no-motion -> -mouse-motion");
		}
		CommandLineSwitchCase(arg, "gdi")
		{
			if (strcmp(arg->Value, "sw") == 0)
				settings->SoftwareGdi = true;
			else if (strcmp(arg->Value, "hw") == 0)
				settings->SoftwareGdi = false;

			WLog_WARN(TAG,  "--gdi %s -> /gdi:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "no-osb")
		{
			settings->OffscreenSupportLevel = false;
			WLog_WARN(TAG,  "--no-osb -> -offscreen-cache");
		}
		CommandLineSwitchCase(arg, "no-bmp-cache")
		{
			settings->BitmapCacheEnabled = false;
			WLog_WARN(TAG,  "--no-bmp-cache -> -bitmap-cache");
		}
		CommandLineSwitchCase(arg, "plugin")
		{
			WLog_WARN(TAG,  "--plugin -> /a, /vc, /dvc and channel-specific options");
		}
		CommandLineSwitchCase(arg, "rfx")
		{
			settings->RemoteFxCodec = true;
			WLog_WARN(TAG,  "--rfx -> /rfx");
		}
		CommandLineSwitchCase(arg, "rfx-mode")
		{
			if (arg->Value[0] == 'v')
				settings->RemoteFxCodecMode = 0x00;
			else if (arg->Value[0] == 'i')
				settings->RemoteFxCodecMode = 0x02;

			WLog_WARN(TAG,  "--rfx-mode -> /rfx-mode:%s", settings->RemoteFxCodecMode ? "image" : "video");
		}
		CommandLineSwitchCase(arg, "nsc")
		{
			settings->NSCodec = true;
			WLog_WARN(TAG,  "--nsc -> /nsc");
		}
		CommandLineSwitchCase(arg, "disable-wallpaper")
		{
			settings->DisableWallpaper = true;
			WLog_WARN(TAG,  "--disable-wallpaper -> -wallpaper");
		}
		CommandLineSwitchCase(arg, "composition")
		{
			settings->AllowDesktopComposition = true;
			WLog_WARN(TAG,  "--composition -> +composition");
		}
		CommandLineSwitchCase(arg, "disable-full-window-drag")
		{
			settings->DisableFullWindowDrag = true;
			WLog_WARN(TAG,  "--disable-full-window-drag -> -window-drag");
		}
		CommandLineSwitchCase(arg, "disable-menu-animations")
		{
			settings->DisableMenuAnims = true;
			WLog_WARN(TAG,  "--disable-menu-animations -> -menu-anims");
		}
		CommandLineSwitchCase(arg, "disable-theming")
		{
			settings->DisableThemes = true;
			WLog_WARN(TAG,  "--disable-theming -> -themes");
		}
		CommandLineSwitchCase(arg, "ntlm")
		{

		}
		CommandLineSwitchCase(arg, "ignore-certificate")
		{
			settings->IgnoreCertificate = true;
			WLog_WARN(TAG,  "--ignore-certificate -> /cert-ignore");
		}
		CommandLineSwitchCase(arg, "sec")
		{
			if (ansi_count_compare("rdp", arg->Value, 1) == 0) /* Standard RDP */
			{
				settings->RdpSecurity = true;
				settings->TlsSecurity = false;
				settings->NlaSecurity = false;
				settings->UseRdpSecurityLayer = false;
			}
			else if (ansi_count_compare("tls", arg->Value, 1) == 0) /* TLS */
			{
				settings->RdpSecurity = false;
				settings->TlsSecurity = true;
				settings->NlaSecurity = false;
			}
			else if (ansi_count_compare("nla", arg->Value, 1) == 0) /* NLA */
			{
				settings->RdpSecurity = false;
				settings->TlsSecurity = false;
				settings->NlaSecurity = true;
			}

			WLog_WARN(TAG,  "--sec %s -> /sec:%s", arg->Value, arg->Value);
		}
		CommandLineSwitchCase(arg, "no-rdp")
		{
			settings->RdpSecurity = false;
			WLog_WARN(TAG,  "--no-rdp -> -sec-rdp");
		}
		CommandLineSwitchCase(arg, "no-tls")
		{
			settings->TlsSecurity = false;
			WLog_WARN(TAG,  "--no-tls -> -sec-tls");
		}
		CommandLineSwitchCase(arg, "no-nla")
		{
			settings->NlaSecurity = false;
			WLog_WARN(TAG,  "--no-nla -> -sec-nla");
		}
		CommandLineSwitchCase(arg, "secure-checksum")
		{
			settings->SaltedChecksum = true;
		}
		CommandLineSwitchDefault(arg)
		{

		}

		CommandLineSwitchEnd(arg)
	}
	while ((arg = CommandLineFindNextArgumentA(arg)) != nullptr);

	WLog_WARN(TAG,  "%s -> /v:%s", settings->ServerHostname, settings->ServerHostname);

	if (settings->ServerPort != 3389)
		WLog_WARN(TAG,  " /port:%d", settings->ServerPort);

	WLog_WARN(TAG,  "");
	return 1;
}
