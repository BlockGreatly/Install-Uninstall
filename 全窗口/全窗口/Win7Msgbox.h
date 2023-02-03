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

void Win7ErrBox(const wstring&, const wstring&, const wstring&, const int& = 0);
/*
	Parameters:
	[IN] Title:		Error Box window title.
	[IN] Abstract:	Short error message.
	[IN] Message:	Detailed error message.

	[IN] Code (optional):
		Windows system error code.
		Default value is 0.
		If not set (or set to 0), error code returned by GetLastError() will be used.
*/

void Win7MsgBox(const wstring&, const wstring&, const wstring&, const int& = -3, const wstring & = L"");
/*
	Parameters:
	[IN] Title:		Message Box window title.
	[IN] Abstract:	Short message.
	[IN] Message:	Detailed message.

	[IN] Notification Level (optional):
		Available values are:
		-1 (WARNING7):	An exclamation-point icon;
		-2 (ERROR7):	A stop-sign icon;
		-3 (INFO7):		An icon consisting of a lowercase letter i in a circle;
		-4 (SECURITY7):	A shield icon.
		0 (iNULL):		No icon.
		Default value is -3 (INFO7).

	[IN] Extended information (optional):
		If set, an expandable handle will show at the bottom with "Show more information" captions.
		User could choose to extend the dialog and see texts provided by this value.
		Developers may use this parameter to display technical contexts.
*/

int Win7AskBox(const wstring&, const wstring&, const wstring&, const bool& = false, const int& = -3, const wstring & = L"");
/*
	Parameters:
	[IN] Title:		Message Box window title.
	[IN] Abstract:	Short message.
	[IN] Message:	Detailed message.

	[IN] Retry Flag (optional):
		By default, this flag is set to FALSE. User will be asked to choose YES / NO.
		Enabling this flag will change available choices to RETRY / CANCEL.
		Return value will be different if set.

	[IN] Notification Level (optional):
		Available values are:
		-1 (WARNING7):	An exclamation-point icon;
		-2 (ERROR7):	A stop-sign icon;
		-3 (INFO7):		An icon consisting of a lowercase letter i in a circle;
		-4 (SECURITY7):	A shield icon.
		0 (NULL):		No icon.
		Default value is -3 (INFO7).

	[IN] Extended information (optional):
		If set, an expandable handle will show at the bottom with "Show more information" captions.
		User could choose to extend the dialog and see texts provided by this value.
		Developers may use this parameter to display technical contexts.


	Return Value:
		6 (IDYES) / 7 (IDNO):		by default
		4 (IDRETRY) / 2 (IDCANCEL):	if Retry Flag is set to TRUE
*/

int Win7AskBoxEx(const wstring&, const wstring&, const wstring&, const TASKDIALOG_BUTTON*, const int&, const int&, const int& = -3, const wstring & = L"");
/*
	Parameters:
	[IN] Title:		Message Box window title.
	[IN] Abstract:	Short message.
	[IN] Message:	Detailed message.

	[IN] Button Array:		An array constructed by TASKDIALOG_BUTTON that includes all buttons.
	[IN] Button Count:		Number of buttons in Button Array.
	[IN] Default Button:	Value (NOT the index) of the default button in Button Array.

	[IN] Notification Level (optional):
		Available values are:
		-1 (WARNING7):	An exclamation-point icon;
		-2 (ERROR7):	A stop-sign icon;
		-3 (INFO7):		An icon consisting of a lowercase letter i in a circle;
		-4 (SECURITY7):	A shield icon.
		0 (NULL):		No icon.
		Default value is -3 (INFO7).

	[IN] Extended information (optional):
		If set, an expandable handle will show at the bottom with "Show more information" captions.
		User could choose to extend the dialog and see texts provided by this value.
		Developers may use this parameter to display technical contexts.


	Return Value:
		Value of user-clicked button. Or -1 if user did not make a choice.
*/

int Win7AskBoxR(const wstring&, const wstring&, const wstring&, const TASKDIALOG_BUTTON*, const int&, const int& = 0, const int& = -3, const wstring & = L"");
/*
	Parameters:
	[IN] Title:		Message Box window title.
	[IN] Abstract:	Short message.
	[IN] Message:	Detailed message.

	[IN] Radio Button Array:	An array constructed by TASKDIALOG_BUTTON that includes all radio buttons.
	[IN] Radio Button Count:	Number of radio buttons in Radio Button Array.

	[IN] Default Radio Button (optional):
		Value (NOT the index) of the default radio button in Radio Button Array.
		If not set, no default radio button will be selected.

	[IN] Notification Level (optional):
		Available values are:
		-1 (WARNING7):	An exclamation-point icon;
		-2 (ERROR7):	A stop-sign icon;
		-3 (INFO7):		An icon consisting of a lowercase letter i in a circle;
		-4 (SECURITY7):	A shield icon.
		0 (NULL):		No icon.
		Default value is -3 (INFO7).

	[IN] Extended information (optional):
		If set, an expandable handle will show at the bottom with "Show more information" captions.
		User could choose to extend the dialog and see texts provided by this value.
		Developers may use this parameter to display technical contexts.


	Return Value:
		Value of user-selected radio button. Or -1 if user did not make a choice.
*/

bool Win7ChkBox(const wstring&, const wstring&, const wstring&, const wstring&, const bool& = false, const int& = -3, const wstring & = L"");
/*
	Parameters:
	[IN] Title:		Message Box window title.
	[IN] Abstract:	Short message.
	[IN] Message:	Detailed message.

	[IN] Checkbox Texts:
		Texts to display near the checkbox.

	[IN] Checkbox Already Checked (optional):
		Set to TRUE if checkbox should be checked by default.
		Default value is FALSE.

	[IN] Notification Level (optional):
		Available values are:
		-1 (WARNING7):	An exclamation-point icon;
		-2 (ERROR7):	A stop-sign icon;
		-3 (INFO7):		An icon consisting of a lowercase letter i in a circle;
		-4 (SECURITY7):	A shield icon.
		0 (NULL):		No icon.
		Default value is -3 (INFO7).

	[IN] Extended information (optional):
		If set, an expandable handle will show at the bottom with "Show more information" captions.
		User could choose to extend the dialog and see texts provided by this value.
		Developers may use this parameter to display technical contexts.


	Return Value:
		TRUE:	if user checked checkbox (or it was checked by default)
		FALSE:	if user unchecked checkbox (or it was unchecked by default)
*/

void Win7ChkBoxEx(int&, bool&,
	const wstring&, const wstring&, const wstring&, const TASKDIALOG_BUTTON*, const int&, const int&, const wstring&, const bool& = false, const int& = -3, const wstring & = L"");
/*
	Parameters:
	[OUT] Clicked Button:	See "Return Values" for details.
	[OUT] Checkbox Status:	See "Return Values" for details.

	[IN] Title:		Message Box window title.
	[IN] Abstract:	Short message.
	[IN] Message:	Detailed message.

	[IN] Button Array:		An array constructed by TASKDIALOG_BUTTON that includes all buttons.
	[IN] Button Count:		Number of buttons in Button Array.
	[IN] Default Button:	Value (NOT the index) of the default button in Button Array.

	[IN] Checkbox Texts:
		Texts to display near the checkbox.

	[IN] Checkbox Already Checked (optional):
		Set to TRUE if checkbox should be checked by default.
		Default value is FALSE.

	[IN] Notification Level (optional):
		Available values are:
		-1 (WARNING7):	An exclamation-point icon;
		-2 (ERROR7):	A stop-sign icon;
		-3 (INFO7):		An icon consisting of a lowercase letter i in a circle;
		-4 (SECURITY7):	A shield icon.
		0 (NULL):		No icon.
		Default value is -3 (INFO7).

	[IN] Extended information (optional):
		If set, an expandable handle will show at the bottom with "Show more information" captions.
		User could choose to extend the dialog and see texts provided by this value.
		Developers may use this parameter to display technical contexts.


	Return Values:
		This function has no return value itself. User feedback will be passed back by reference to the first two parameters.
		Clicked Button:		Value of user-clicked button. Or -1 if user did not make a choice.
		Checkbox Status:	TRUE (checked) / FALSE (unchecked)
*/

void Win7ChkBoxR(int&, bool&,
	const wstring&, const wstring&, const wstring&, const wstring&, const TASKDIALOG_BUTTON*, const int&, const int& = 0, const bool& = false, const int& = -3, const wstring & = L"");
/*
	Parameters:
	[OUT] Clicked Button:	See "Return Values" for details.
	[OUT] Checkbox Status:	See "Return Values" for details.

	[IN] Title:		Message Box window title.
	[IN] Abstract:	Short message.
	[IN] Message:	Detailed message.

	[IN] Checkbox Texts:
		Texts to display near the checkbox.

	[IN] Button Array:		An array constructed by TASKDIALOG_BUTTON that includes all buttons.
	[IN] Button Count:		Number of buttons in Button Array.

	[IN] Default Radio Button (optional):
		Value (NOT the index) of the default radio button in Radio Button Array.
		If not set, no default radio button will be selected.

	[IN] Checkbox Already Checked (optional):
		Set to TRUE if checkbox should be checked by default.
		Default value is FALSE.

	[IN] Notification Level (optional):
		Available values are:
		-1 (WARNING7):	An exclamation-point icon;
		-2 (ERROR7):	A stop-sign icon;
		-3 (INFO7):		An icon consisting of a lowercase letter i in a circle;
		-4 (SECURITY7):	A shield icon.
		0 (NULL):		No icon.
		Default value is -3 (INFO7).

	[IN] Checkbox Already Checked (optional):
		Set to TRUE if checkbox should be checked by default.
		Default value is FALSE.

	[IN] Extended information (optional):
		If set, an expandable handle will show at the bottom with "Show more information" captions.
		User could choose to extend the dialog and see texts provided by this value.
		Developers may use this parameter to display technical contexts.


	Return Values:
		This function has no return value itself. User feedback will be passed back by reference to the first two parameters.
		Selected Button:	Value of user-selected radio button. Or -1 if user did not make a choice.
		Checkbox Status:	TRUE (checked) / FALSE (unchecked)
*/

#endif // Win7_Style_Message_Box_HEADER