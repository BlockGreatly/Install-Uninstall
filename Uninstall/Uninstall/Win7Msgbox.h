#pragma once
/*
	Windows 7 Style Message Box for Beginners (Visual Studio ONLY)
	<header>

	THESE FUNCTIONS ARE UNICODE FRIENDLY.

	WARNING:	Target OS version has been set to Microsoft Windows 7 or higher.
				DO NOT INCLUDE THIS HEADER FOR LEGACY APPLICATIONS.

	Version 1.3
	Created by Yi Ding (Vassile) on April 5, 2014.

	PLEASE CREDIT AUTHOR IN YOUR APPLICATION.
*/

#pragma comment ( linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"" )
#pragma comment ( lib, "comctl32.lib" )

#ifndef WIN7_STYLE_MESSAGE_BOX_HEADER
#define WIN7_STYLE_MESSAGE_BOX_HEADER

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#define NTDDI_VERSION	NTDDI_WIN7
#define _WIN32_WINNT	_WIN32_WINNT_WIN7

#define WIN32_LEAN_AND_MEAN

#include <string>
#include <windows.h>
#include <commctrl.h>

using std::wstring; using std::to_wstring;

#define WARNING7	-1
#define ERROR7		-2
#define INFO7		-3
#define SECURITY7	-4

#endif // Win7_Style_Message_Box_HEADER