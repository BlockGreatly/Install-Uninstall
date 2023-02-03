/*
	Windows 7 Style Message Box for Beginners (Visual Studio ONLY)
	<source file>

	THESE FUNCTIONS ARE UNICODE FRIENDLY.

	WARNING:	Target OS version has been set to Microsoft Windows 7 or higher.
				DO NOT INCLUDE THIS HEADER FOR LEGACY APPLICATIONS.

	Version 1.3
	Created by Yi Ding (Vassile) on April 5, 2014.

	PLEASE CREDIT AUTHOR IN YOUR APPLICATION.
*/

#include "Win7Msgbox.h"

void Win7ErrBox(const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore,
	const int& ErrCode)
{
	wstring MsgTech;
	if (ErrCode == 0) { MsgTech = L"Last known error code: " + to_wstring(GetLastError()); }
	else { MsgTech = L"Last known error code: " + to_wstring(ErrCode); }

	TASKDIALOGCONFIG ErrWin = { sizeof(ErrWin) };
	ErrWin.hwndParent = GetActiveWindow();
	ErrWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS;
	ErrWin.dwCommonButtons = TDCBF_CLOSE_BUTTON;
	ErrWin.pszWindowTitle = WinTitle.c_str();
	ErrWin.pszMainIcon = TD_ERROR_ICON;
	ErrWin.pszMainInstruction = MsgMain.c_str();
	ErrWin.pszContent = MsgMore.c_str();
	ErrWin.pszCollapsedControlText = L"&Show technical information";
	ErrWin.pszExpandedControlText = L"&Hide technical information";
	ErrWin.pszExpandedInformation = MsgTech.c_str();
	TaskDialogIndirect(&ErrWin, NULL, NULL, NULL);

	throw(ErrCode);
}

void Win7MsgBox(const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore,
	const int& Icon, const wstring& MsgEx)
{
	TASKDIALOGCONFIG MsgWin = { sizeof(MsgWin) };
	MsgWin.hwndParent = GetActiveWindow();
	MsgWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS;
	MsgWin.dwCommonButtons = TDCBF_OK_BUTTON;
	MsgWin.pszWindowTitle = WinTitle.c_str();

	if (Icon == -1) { MsgWin.pszMainIcon = TD_WARNING_ICON; }
	else if (Icon == -2) { MsgWin.pszMainIcon = TD_ERROR_ICON; }
	else if (Icon == -3) { MsgWin.pszMainIcon = TD_INFORMATION_ICON; }
	else if (Icon == -4) { MsgWin.pszMainIcon = TD_SHIELD_ICON; }

	MsgWin.pszMainInstruction = MsgMain.c_str();
	MsgWin.pszContent = MsgMore.c_str();
	MsgWin.pszCollapsedControlText = L"&Show more information";
	MsgWin.pszExpandedControlText = L"&Show less information";
	MsgWin.pszExpandedInformation = MsgEx.c_str();

	if (TaskDialogIndirect(&MsgWin, NULL, NULL, NULL) != S_OK)
	{
		Win7ErrBox(L"Internal Function Error",
			L"Unable to display Message Box.",
			L"A program failed to pop up a Message Box. "
			L"Instead, this window was displayed by system to notify user about the last error. "
			L"The original program did not order this Error Box. "
			L"Please contact its software developer for further assistance!");
	};
}

int Win7AskBox(const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore,
	const bool& Retry, const int& Icon, const wstring& MsgEx)
{
	int Selected = -1;

	TASKDIALOGCONFIG AskWin = { sizeof(AskWin) };
	AskWin.hwndParent = GetActiveWindow();
	AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS;

	if (Retry) { AskWin.dwCommonButtons = TDCBF_OK_BUTTON | TDCBF_CANCEL_BUTTON; }
	else { AskWin.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON; }

	AskWin.pszWindowTitle = WinTitle.c_str();

	if (Icon == -1) { AskWin.pszMainIcon = TD_WARNING_ICON; }
	else if (Icon == -2) { AskWin.pszMainIcon = TD_ERROR_ICON; }
	else if (Icon == -3) { AskWin.pszMainIcon = TD_INFORMATION_ICON; }
	else if (Icon == -4) { AskWin.pszMainIcon = TD_SHIELD_ICON; }

	AskWin.pszMainInstruction = MsgMain.c_str();
	AskWin.pszContent = MsgMore.c_str();
	AskWin.pszCollapsedControlText = L"&Show more information";
	AskWin.pszExpandedControlText = L"&Show less information";
	AskWin.pszExpandedInformation = MsgEx.c_str();

	if (TaskDialogIndirect(&AskWin, &Selected, NULL, NULL) != S_OK)
	{
		Win7ErrBox(L"Internal Function Error",
			L"Unable to display Message Box.",
			L"A program failed to pop up a Message Box. "
			L"Instead, this window was displayed by system to notify user about the last error. "
			L"The original program did not order this Error Box. "
			L"Please contact its software developer for further assistance!");
	}
	else { return Selected; }
}

int Win7AskBoxEx(const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore,
	const TASKDIALOG_BUTTON* BtnGroup, const int& BtnCount, const int& BtnDefault,
	const int& Icon, const wstring& MsgEx)
{
	int Selected = 0;

	TASKDIALOGCONFIG AskWin = { sizeof(AskWin) };
	AskWin.hwndParent = GetActiveWindow();
	AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_USE_COMMAND_LINKS;
	AskWin.cButtons = BtnCount;
	AskWin.pButtons = BtnGroup;
	AskWin.nDefaultButton = BtnDefault;
	AskWin.pszWindowTitle = WinTitle.c_str();

	if (Icon == -1) { AskWin.pszMainIcon = TD_WARNING_ICON; }
	else if (Icon == -2) { AskWin.pszMainIcon = TD_ERROR_ICON; }
	else if (Icon == -3) { AskWin.pszMainIcon = TD_INFORMATION_ICON; }
	else if (Icon == -4) { AskWin.pszMainIcon = TD_SHIELD_ICON; }

	AskWin.pszMainInstruction = MsgMain.c_str();
	AskWin.pszContent = MsgMore.c_str();
	AskWin.pszCollapsedControlText = L"&Show more information";
	AskWin.pszExpandedControlText = L"&Show less information";
	AskWin.pszExpandedInformation = MsgEx.c_str();

	if (TaskDialogIndirect(&AskWin, &Selected, NULL, NULL) != S_OK)
	{
		Win7ErrBox(L"Internal Function Error",
			L"Unable to display Message Box.",
			L"A program failed to pop up a Message Box. "
			L"Instead, this window was displayed by system to notify user about the last error. "
			L"The original program did not order this Error Box. "
			L"Please contact its software developer for further assistance!");
	}
	else { return Selected; }
}

int Win7AskBoxR(const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore,
	const TASKDIALOG_BUTTON* BtnGroup, const int& BtnCount, const int& BtnDefault,
	const int& Icon, const wstring& MsgEx)
{
	int Selected = -1;

	TASKDIALOGCONFIG AskWin = { sizeof(AskWin) };
	AskWin.hwndParent = GetActiveWindow();

	if (BtnDefault == 0)
	{
		AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_NO_DEFAULT_RADIO_BUTTON;
	}
	else
	{
		AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS;
		AskWin.nDefaultRadioButton = BtnDefault;
	}

	AskWin.cRadioButtons = BtnCount;
	AskWin.pRadioButtons = BtnGroup;
	AskWin.dwCommonButtons = TDCBF_OK_BUTTON;
	AskWin.pszWindowTitle = WinTitle.c_str();

	if (Icon == -1) { AskWin.pszMainIcon = TD_WARNING_ICON; }
	else if (Icon == -2) { AskWin.pszMainIcon = TD_ERROR_ICON; }
	else if (Icon == -3) { AskWin.pszMainIcon = TD_INFORMATION_ICON; }
	else if (Icon == -4) { AskWin.pszMainIcon = TD_SHIELD_ICON; }

	AskWin.pszMainInstruction = MsgMain.c_str();
	AskWin.pszContent = MsgMore.c_str();
	AskWin.pszCollapsedControlText = L"&Show more information";
	AskWin.pszExpandedControlText = L"&Show less information";
	AskWin.pszExpandedInformation = MsgEx.c_str();

	if (TaskDialogIndirect(&AskWin, NULL, &Selected, NULL) != S_OK)
	{
		Win7ErrBox(L"Internal Function Error",
			L"Unable to display Message Box.",
			L"A program failed to pop up a Message Box. "
			L"Instead, this window was displayed by system to notify user about the last error. "
			L"The original program did not order this Error Box. "
			L"Please contact its software developer for further assistance!");
	}
	else { return Selected; }
}

bool Win7ChkBox(const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore,
	const wstring& ChkText, const bool& ChkDefault,
	const int& Icon, const wstring& MsgEx)
{
	BOOL Checked = ChkDefault;

	TASKDIALOGCONFIG MsgWin = { sizeof(MsgWin) };
	MsgWin.hwndParent = GetActiveWindow();

	if (ChkDefault)
	{
		MsgWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_VERIFICATION_FLAG_CHECKED;
	}
	else { MsgWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS; }

	MsgWin.dwCommonButtons = TDCBF_OK_BUTTON;
	MsgWin.pszWindowTitle = WinTitle.c_str();

	if (Icon == -1) { MsgWin.pszMainIcon = TD_WARNING_ICON; }
	else if (Icon == -2) { MsgWin.pszMainIcon = TD_ERROR_ICON; }
	else if (Icon == -3) { MsgWin.pszMainIcon = TD_INFORMATION_ICON; }
	else if (Icon == -4) { MsgWin.pszMainIcon = TD_SHIELD_ICON; }

	MsgWin.pszMainInstruction = MsgMain.c_str();
	MsgWin.pszContent = MsgMore.c_str();
	MsgWin.pszCollapsedControlText = L"&Show more information";
	MsgWin.pszExpandedControlText = L"&Show less information";
	MsgWin.pszExpandedInformation = MsgEx.c_str();
	MsgWin.pszVerificationText = ChkText.c_str();

	if (TaskDialogIndirect(&MsgWin, NULL, NULL, &Checked) != S_OK)
	{
		Win7ErrBox(L"Internal Function Error",
			L"Unable to display Message Box.",
			L"A program failed to pop up a Message Box. "
			L"Instead, this window was displayed by system to notify user about the last error. "
			L"The original program did not order this Error Box. "
			L"Please contact its software developer for further assistance!");
	}
	else { return Checked; }
}

void Win7ChkBoxEx(int& Selection, bool& Check,
	const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore,
	const TASKDIALOG_BUTTON* BtnGroup, const int& BtnCount, const int& BtnDefault,
	const wstring& ChkText, const bool& ChkDefault,
	const int& Icon, const wstring& MsgEx)
{
	BOOL Checked = ChkDefault;
	Selection = -1;

	TASKDIALOGCONFIG AskWin = { sizeof(AskWin) };
	AskWin.hwndParent = GetActiveWindow();

	if (ChkDefault)
	{
		AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_USE_COMMAND_LINKS | TDF_VERIFICATION_FLAG_CHECKED;
	}
	else { AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_USE_COMMAND_LINKS; }

	AskWin.cButtons = BtnCount;
	AskWin.pButtons = BtnGroup;
	AskWin.nDefaultButton = BtnDefault;
	AskWin.pszWindowTitle = WinTitle.c_str();

	if (Icon == -1) { AskWin.pszMainIcon = TD_WARNING_ICON; }
	else if (Icon == -2) { AskWin.pszMainIcon = TD_ERROR_ICON; }
	else if (Icon == -3) { AskWin.pszMainIcon = TD_INFORMATION_ICON; }
	else if (Icon == -4) { AskWin.pszMainIcon = TD_SHIELD_ICON; }

	AskWin.pszMainInstruction = MsgMain.c_str();
	AskWin.pszContent = MsgMore.c_str();
	AskWin.pszCollapsedControlText = L"&Show more information";
	AskWin.pszExpandedControlText = L"&Show less information";
	AskWin.pszExpandedInformation = MsgEx.c_str();
	AskWin.pszVerificationText = ChkText.c_str();

	if (TaskDialogIndirect(&AskWin, &Selection, NULL, &Checked) != S_OK)
	{
		Win7ErrBox(L"Internal Function Error",
			L"Unable to display Message Box.",
			L"A program failed to pop up a Message Box. "
			L"Instead, this window was displayed by system to notify user about the last error. "
			L"The original program did not order this Error Box. "
			L"Please contact its software developer for further assistance!");
	}
	else { Check = Checked; }
}

void Win7ChkBoxR(int& Selection, bool& Check,
	const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore, const wstring& ChkText,
	const TASKDIALOG_BUTTON* BtnGroup, const int& BtnCount, const int& BtnDefault,
	const bool& ChkDefault, const int& Icon, const wstring& MsgEx)
{
	BOOL Checked = ChkDefault;
	Selection = -1;

	TASKDIALOGCONFIG AskWin = { sizeof(AskWin) };
	AskWin.hwndParent = GetActiveWindow();

	if (ChkDefault && BtnDefault == 0)
	{
		AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_NO_DEFAULT_RADIO_BUTTON | TDF_VERIFICATION_FLAG_CHECKED;
	}
	else if (!ChkDefault && BtnDefault == 0)
	{
		AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_NO_DEFAULT_RADIO_BUTTON;
	}
	else if (ChkDefault && BtnDefault != 0)
	{
		AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS | TDF_VERIFICATION_FLAG_CHECKED;
		AskWin.nDefaultRadioButton = BtnDefault;
	}
	else if (!ChkDefault && BtnDefault != 0)
	{
		AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS;
		AskWin.nDefaultRadioButton = BtnDefault;
	}

	AskWin.cRadioButtons = BtnCount;
	AskWin.pRadioButtons = BtnGroup;
	AskWin.pszWindowTitle = WinTitle.c_str();

	if (Icon == -1) { AskWin.pszMainIcon = TD_WARNING_ICON; }
	else if (Icon == -2) { AskWin.pszMainIcon = TD_ERROR_ICON; }
	else if (Icon == -3) { AskWin.pszMainIcon = TD_INFORMATION_ICON; }
	else if (Icon == -4) { AskWin.pszMainIcon = TD_SHIELD_ICON; }

	AskWin.pszMainInstruction = MsgMain.c_str();
	AskWin.pszContent = MsgMore.c_str();
	AskWin.pszCollapsedControlText = L"&Show more information";
	AskWin.pszExpandedControlText = L"&Show less information";
	AskWin.pszExpandedInformation = MsgEx.c_str();
	AskWin.pszVerificationText = ChkText.c_str();

	if (TaskDialogIndirect(&AskWin, NULL, &Selection, &Checked) != S_OK)
	{
		Win7ErrBox(L"Internal Function Error",
			L"Unable to display Message Box.",
			L"A program failed to pop up a Message Box. "
			L"Instead, this window was displayed by system to notify user about the last error. "
			L"The original program did not order this Error Box. "
			L"Please contact its software developer for further assistance!");
	}
	else { Check = Checked; }
}