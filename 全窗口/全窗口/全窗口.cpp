// 全窗口.cpp : 定义应用程序的入口点。
//
#include <stdio.h>
#include "framework.h"
#include "dwmapi.h"
#include <shellapi.h>
#include "全窗口.h"
#include "WindowCompositionAttribute.h"
#include "Win7Msgbox.h"
#include <ShObjIdl.h>
#include <ShlGuid.h>
#define MAX_LOADSTRING 100
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")//用于支持windows视觉样式
#pragma comment(lib,"dwmapi.lib")
#include<Shlobj.h>//选择文件夹对话框
#pragma comment(lib,"Shell32.lib")
#define WM_UNZIP WM_USER+1  //解压文件消息
#define WM_INSTFINSH WM_USER+2//安装完成消息

using namespace std;
// 全局变量:
int ncmd;
HINSTANCE hInst;                                // 当前实例
HMENU hMen;                                     // 右键菜单句柄
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hWndMain;                                  // 主窗口句柄
HWND SticLine, SticTip, SticTip1, SticTip2, LinceAgre, LinceDisAgre,
LinceNextPage,LinceBackPage,LincePageNum;       // 协议控件句柄
HWND ImagBox,FirstPageText;                     //首页图像框
HWND PathText,PathEdit,SelectPath,ErrorInfo;    //安装路径选择页面
HWND InstProce, InstText, InstTip;              //安装进度界面
BOOL InstallProce = TRUE;                       //总安装进度
HWND FinalText;
HWND hWndbuttongo, hWndbuttonexit, hWndbuttonabout, hWndbuttonback;//下方主要功能按钮
TCHAR InstallPath[MAX_PATH] = L"D:\\TaruCraft";                      //默认安装路径
typedef TCHAR FileResList[MAX_PATH];
typedef TCHAR FileResName[FILENAME_MAX];
typedef struct FilesList { //文件资源结构体，成员变量为 资源相对路径 文件名 资源ID
    FileResList filedir;
    FileResName Name;
    DWORD ResID; }fileResLib;
fileResLib files[] = { //文件资源表，成员变量为 资源相对路径 文件名 资源ID
    {L"",L"TaruCraft.exe",IDR_FILES1},{L"",L"Uninstall.exe",IDR_UNINST}
};
typedef struct RegKey {
    WCHAR KeyName[MAX_PATH];
    WCHAR KeyValue[1024];
} RegKeyList;
RegKeyList RegKeyValueList[] = { 
    {L"DisplayName",L"TaruCraft 客户端"},
    {L"Version",L"全球唯一特供版"},
    {L"Publisher",L"塔里木大学方块创作社"},
};
DWORD WinowWide = 750, WindowHight = 500;      // 主窗口宽高
const DWORD BTN_GO = 555, BTN_CAL = 556, BTN_ABOUT = 557,BTN_BACK=558,BTN_AGREE=559,BTN_DISAGREE=560,
BTN_SELECTPATH=561,BTN_NEXTPAGE=562,BTN_BACKPAGE=653;//按钮控件ID
bool DARKMODE = FALSE;                              //深色模式是否启用
static UCHAR Step = 0;                                 // 进行到的步骤
bool Eula = FALSE;
CHAR LinceShowPage = 1;//当前协议展示页
WCHAR LinceMainText[][1000] = { L"隐私政策与服务条款\n省流：我们的安装程序逻辑很简单，基本不涉及以下条款中的任何一条。\n程序介绍：此安装程序仅为由PCL2 + 客户端核心文件打包制成的安装程序，管理员权限的获取仅用于创建桌面快捷方式。\n1.隐私政策\n隐私政策\n本应用尊重并保护所有使用服务用户的个人隐私权。为了给您提供更准确、更有个性化的服务，本应用会按照本隐私权政策的规定使用和披露您的个人信息。但本应用将以高度的勤勉、审慎义务对待这些信息。除本隐私权政策另有规定外，在未征得您事先许可的情况下，本应用不会将这些信息对外披露或向第三方提供。本应用会不时更新本隐私权政策。 您在同意本应用服务使用协议之时，即视为您已经同意本隐私权政策全部内容。本隐私权政策属于本应用服务使用协议不可分割的一部分。"
,L"1. 适用范围\n此安装程序为非联网程序，我们不会获取您的任何信息。\n2. 信息使用\n我们不会使用您的任何信息，因为我们获取不到。\n3. 信息披露\n我们不会披露您的任何信息，因为我们获取不到。\n4. 信息存储和交换\n我们不会存储和交换您的任何信息，因为我们获取不到。\n5. Cookie的使用\n此安装程序为非联网程序，没有Cookie。\n6. 信息安全\n我们获取不到您的信息，故使用此程序安装TaruCraft客户端是安全的。",
L"7.本隐私政策的更改\n除非我们想整个活，否则我们不会更改隐私政策。\n\n2.服务条款\n软件服务及隐私条款\n欢迎您使用软件及服务，以下内容请仔细阅读。\n1、保护用户个人信息是一项基本原则，我们将会采取合理的措施保护用户的个人信息。虽然我们无法获取您的个人信息。\n2、我们将会使用您的以下功能：写入删除程序，修改注册表，创建快捷方式。\n3、此安装程序为组织内部交流程序，仅供学习、娱乐、交流等用途，严禁用于其他商业的或非法的用途，由本程序造成的一切后果，程序开发者及组织内部其它成员概不负责。\n",
L"4、在您使用我们的产品或服务的过程中，我们不会：需要您提供个人信息，如姓名、电子邮件地址、电话号码、联系地址等以及注册或申请服务时需要 的其它类似个人信息。\n5、请您在发现bug之后及时向我们提交。\n6、我们拥有对上述条款的最终解释权。\n7、欢迎加入TaruCraft方块创作社！"};
static HFONT hFont = CreateFont(//创建字体
    24/*高度*/, 0/*宽度*/, 0/*不用管*/, 0/*不用管*/, 400,//设置字体粗细程度一般这个值设为400,11
    FALSE/*不带斜体*/, FALSE/*不带下划线*/, FALSE/*不带删除线*/,
    DEFAULT_CHARSET,  //这里我们使用默认字符集，还有其他以 _CHARSET 结尾的常量可用
    OUT_CHARACTER_PRECIS, //输出精度
    CLIP_CHARACTER_PRECIS,  //剪裁精度
    DEFAULT_QUALITY,  //默认输出质量
    FF_DONTCARE,  //不指定字体族*/
    L"微软雅黑"  //字体名
);

bool ExportToFile(const std::wstring& exportFilePath, const void* pBuffer, DWORD bufferLength)
{//导出文件资源
    if (pBuffer == NULL || bufferLength <= 0)
    {
        return false;
    }
    HANDLE hFile = ::CreateFile(exportFilePath.c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == NULL)
    {
        return false;
    }

    DWORD writetem = -1;
    BOOL ret = ::WriteFile(hFile, pBuffer, bufferLength, &writetem, NULL);
    if (writetem != bufferLength)
    {
        ::CloseHandle(hFile);
        return false;
    }

    ::CloseHandle(hFile);
    return true;
}

HRESULT EnableBlurBehindWindow(HWND hWnd, //窗口句柄
    BOOL bEnable, //启用或禁用
    HRGN hRgn, //模糊窗体中某个区域
    BOOL bTransitionOnMaximized) //最大化时是否启用
{
    DWM_BLURBEHIND blurBehind = { 0 };
    blurBehind.dwFlags = DWM_BB_ENABLE | DWM_BB_TRANSITIONONMAXIMIZED;
    blurBehind.fEnable = bEnable;
    blurBehind.fTransitionOnMaximized = bTransitionOnMaximized;
    if (bEnable && hRgn != NULL)
    {
        blurBehind.dwFlags |= DWM_BB_BLURREGION;
        blurBehind.hRgnBlur = hRgn;
    }
    return DwmEnableBlurBehindWindow(hWnd, &blurBehind);
}

/**
* exportPath:文件路径，
* resourceId:资源ID ：Resource.h中
* 导出资源包转成指定文件
*/
bool ExportRes(const std::wstring& exportPath, DWORD resourceId)
{
    HINSTANCE m_hInstance = hInst;
    // "FILES" 是自定义资源类型，可以自己决定
    HRSRC hrSrc = FindResource(m_hInstance, MAKEINTRESOURCE(resourceId), _T("FILES"));
    if (hrSrc == NULL)
    {
        return false;
    }

    HGLOBAL hGlobalResource = LoadResource(m_hInstance, hrSrc);
    if (hGlobalResource == NULL)
    {
        return false;
    }

    const void* pResourceData = ::LockResource(hGlobalResource);
    if (!pResourceData)
    {
        return false;
    }

    DWORD resLength = SizeofResource(m_hInstance, hrSrc);
    bool ret = ExportToFile(exportPath, pResourceData, resLength);

    FreeResource(hGlobalResource);
    return ret;
}

HRESULT ExtendIntoClientAll(HWND hwnd)// 设置窗口无边框，拓展AERO范围为整个窗口
{
    // Negative margins have special meaning to DwmExtendFrameIntoClientArea.
    // Negative margins create the "sheet of glass" effect, where the client area
    // is rendered as a solid surface with no window border.
    MARGINS margins = { -1 };
    HRESULT hr = S_OK;

    // Extend the frame across the entire window.
    hr = DwmExtendFrameIntoClientArea(hwnd, &margins);
    if (SUCCEEDED(hr))
    {
        // ...
    }
    return hr;
}

void UseAero(HWND hWnd) { //用于支持win11 acrylic效果，不过在低版本windows渲染有问题，已经砍了
    RECT hostWindowRect{};
    HMODULE hUser = GetModuleHandle(TEXT("user32.dll"));
    if (hUser)
    {
        pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
        if (setWindowCompositionAttribute)
        {

            ACCENT_POLICY accent{ ACCENT_ENABLE_BLURBEHIND,0, 0, 0
            };
            // $AABBGGRR
            accent.GradientColor = 0xffffff;
            accent.AccentFlags = 0x00;

            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
            data.cbData = sizeof(accent);
            //setWindowCompositionAttribute(hWnd, &data);
            DWM_SYSTEMBACKDROP_TYPE p = DWMSBT_TRANSIENTWINDOW;//DWMSBT_TABBEDWINDOW;//
            DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &p,sizeof(p));
            UINT c = DWMWCP_ROUND;
            DwmSetWindowAttribute(hWnd, DWMWCP_ROUNDSMALL, &c, sizeof(c));
            
        }
    }
}
void SetDarkMode(HWND hWnd,bool mode) {
    if (mode) {
        BOOL darkmode = TRUE;
        DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkmode, sizeof(darkmode));
    }
    else {
        BOOL darkmode = FALSE;
        DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkmode, sizeof(darkmode));
    }
}

void ShowFirstPage(bool sta = FALSE) {
    if (sta) {
        ImagBox = CreateWindow(TEXT("Static"),L"",WS_CHILD | WS_VISIBLE | SS_ICON ,
            20, 40, WinowWide - 60, 300,hWndMain,(HMENU)2,hInst,NULL);
        HICON hicon = (HICON)LoadImage(hInst,
            MAKEINTRESOURCE(IDI_ABOUT), IMAGE_ICON, 0, 0,
            LR_DEFAULTCOLOR);
        //SendMessage(ImagBox, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hicon);
        FirstPageText = CreateWindow(TEXT("static"), TEXT("欢迎来到TaruCraft客户端安装程序！"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
            20, 40, WinowWide - 60, 30, hWndMain, (HMENU)34, hInst, NULL);
        SendMessage(FirstPageText, WM_SETFONT, (WPARAM)hFont, NULL);
        ShowWindow(ImagBox, ncmd);
        ShowWindow(FirstPageText, ncmd);
        UpdateWindow(ImagBox);
        UpdateWindow(FirstPageText);
        ShowWindow(hWndbuttonback, SW_HIDE);
    }
    else {
        //CloseWindow(ImagBox);//关闭
        ShowWindow(hWndbuttonback, SW_SHOW);
        DestroyWindow(ImagBox);//销毁
        DestroyWindow(FirstPageText);
    }
}

void ShowLinceEula(bool hide=TRUE) {
    if (Step == 1&&hide==TRUE) {
        if (Eula == TRUE) {
            
            DestroyWindow(SticTip1);
            DestroyWindow(LinceAgre);
            SticTip2 = CreateWindow(TEXT("static"), TEXT("您已选择同意用户协议,可以继续"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
                20, 350, 300, 30, hWndMain, (HMENU)17, hInst, NULL);
            LinceDisAgre = CreateWindow(_T("BUTTON"), L"我不同意这个协议", WS_TABSTOP | WS_CHILD,
                WinowWide - (40 + 200), 350, 200, 30, hWndMain, (HMENU)BTN_DISAGREE, hInst, nullptr);
            SendMessage(SticTip2, WM_SETFONT, (WPARAM)hFont, NULL);
            SendMessage(LinceDisAgre, WM_SETFONT, (WPARAM)hFont, NULL);
            ShowWindow(SticTip2, ncmd);
            UpdateWindow(SticTip2);
            ShowWindow(LinceDisAgre, ncmd);
            UpdateWindow(LinceDisAgre);
            ShowWindow(hWndbuttongo, SW_SHOW);
        }
        else {
            ShowWindow(hWndbuttongo, SW_HIDE);
            DestroyWindow(SticTip2);
            DestroyWindow(LinceDisAgre);
            SticTip1 = CreateWindow(TEXT("static"), TEXT("您必须同意用户协议才能继续安装"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
                20, 350, 300, 30, hWndMain, (HMENU)16, hInst, NULL);
            LinceAgre = CreateWindow(_T("BUTTON"), L"我同意这个协议", WS_TABSTOP | WS_CHILD,
                WinowWide - (40 + 200), 350, 200, 30, hWndMain, (HMENU)BTN_AGREE, hInst, nullptr);
            SendMessage(SticTip1, WM_SETFONT, (WPARAM)hFont, NULL);
            SendMessage(LinceAgre, WM_SETFONT, (WPARAM)hFont, NULL);
            ShowWindow(SticTip1, ncmd);
            UpdateWindow(SticTip1);
            ShowWindow(LinceAgre, ncmd);
            UpdateWindow(LinceAgre);
        }
    }
    else {
        ShowWindow(hWndbuttongo, SW_SHOW);
        DestroyWindow(SticTip1);
        DestroyWindow(LinceAgre);
        DestroyWindow(SticTip2);
        DestroyWindow(LinceDisAgre);
    }
}

void ShowLince(bool sta=FALSE) {
    if(sta){
        WCHAR Pagenum[] = L"";
        wsprintf(Pagenum, L"%d", LinceShowPage);
        SticTip = CreateWindow(TEXT("static"), TEXT("以下是用户协议"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
            20, 8, WinowWide - 60, 30, hWndMain, (HMENU)10, hInst, NULL);
        LinceBackPage = CreateWindow(TEXT("BUTTON"), TEXT("上一页"), WS_CHILD | WS_VISIBLE ,
            500, 8, 70, 30, hWndMain, (HMENU)BTN_BACKPAGE, hInst, NULL);
        LincePageNum= CreateWindow(TEXT("static"), Pagenum, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
            570, 8, 30, 30, hWndMain, (HMENU)10, hInst, NULL);
        LinceNextPage = CreateWindow(TEXT("BUTTON") ,TEXT("下一页"), WS_CHILD | WS_VISIBLE,
            600, 8, 70, 30, hWndMain, (HMENU)BTN_NEXTPAGE, hInst, NULL);
        SticLine = CreateWindow(
            TEXT("static"), LinceMainText[LinceShowPage-1], WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT,
            20, 45, WinowWide - 60, 300,hWndMain,(HMENU)22,hInst,NULL);
        SendMessage(SticTip, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(SticLine,WM_SETFONT,(WPARAM)hFont,NULL);
        SendMessage(LinceBackPage, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(LincePageNum, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(LinceNextPage, WM_SETFONT, (WPARAM)hFont, NULL);
        ShowWindow(SticTip, ncmd);
        UpdateWindow(SticTip);
        ShowWindow(SticLine, ncmd);
        UpdateWindow(SticLine);
        ShowWindow(LinceBackPage, ncmd);
        ShowWindow(LincePageNum, ncmd);
        ShowWindow(LinceNextPage, ncmd);
        UpdateWindow(LinceBackPage);
        UpdateWindow(LincePageNum);
        UpdateWindow(LinceNextPage);
        ShowLinceEula();
        ShowWindow(LinceNextPage, SW_SHOW);
        ShowWindow(LinceBackPage, SW_SHOW);
        if (LinceShowPage == 1) {
            ShowWindow(LinceBackPage, SW_HIDE);
            ShowWindow(LinceNextPage, SW_SHOW);
        }else if (LinceShowPage == sizeof(LinceMainText) / sizeof(LinceMainText[0])) {
            ShowWindow(LinceBackPage, SW_SHOW);
            ShowWindow(LinceNextPage, SW_HIDE);
        }
        else {
            ShowWindow(LinceNextPage, SW_SHOW);
            ShowWindow(LinceBackPage, SW_SHOW);
        }
    }
    else {
        //CloseWindow(SticLine);//关闭
        ShowLinceEula(FALSE);
        DestroyWindow(SticTip);
        DestroyWindow(SticLine);//销毁
        DestroyWindow(LinceBackPage);
        DestroyWindow(LincePageNum);
        DestroyWindow(LinceNextPage);
    }
}

void ShowPathSelect(bool sta = FALSE) {
    if (sta) {
        PathText = CreateWindow(TEXT("static"),TEXT("选择你的安装位置"),WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
            20, 40, WinowWide - 60, 30,hWndMain,(HMENU)10,hInst,NULL);
        SendMessage(PathText, WM_SETFONT, (WPARAM)hFont, NULL);
        PathEdit=CreateWindow(_T("EDIT"), InstallPath, WS_TABSTOP | WS_CHILD | WS_BORDER | SS_LEFT | SS_CENTERIMAGE | ES_READONLY,
            20, 80, WinowWide - 60, 30, hWndMain, (HMENU)11, hInst, nullptr);
        SelectPath = CreateWindow(_T("BUTTON"), L"选择文件夹", WS_TABSTOP | WS_CHILD,
            WinowWide - (40 + 200), 120, 200, 30, hWndMain, (HMENU)BTN_SELECTPATH, hInst, nullptr);
        ErrorInfo = CreateWindow(TEXT("static"), TEXT(""), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
            20, 150, WinowWide - 60, 30, hWndMain, (HMENU)10, hInst, NULL);
        SendMessage(PathEdit, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(SelectPath, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(ErrorInfo, WM_SETFONT, (WPARAM)hFont, NULL);
        ShowWindow(PathText, ncmd);
        ShowWindow(PathEdit, ncmd);
        ShowWindow(SelectPath, ncmd);
        ShowWindow(ErrorInfo, ncmd);
        UpdateWindow(SticLine);
        UpdateWindow(PathEdit);
        UpdateWindow(SelectPath);
        UpdateWindow(ErrorInfo);
    }
    else {
        DestroyWindow(PathText);
        DestroyWindow(PathEdit);
        DestroyWindow(SelectPath);
        DestroyWindow(ErrorInfo);
    }
}

void ShowInstProcess(bool sta = FALSE) {
    if (sta) {
        InstText = CreateWindow(TEXT("static"), TEXT("安装进度"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
            20, 40, WinowWide - 60, 30, hWndMain, (HMENU)10, hInst, NULL);
        SendMessage(InstText, WM_SETFONT, (WPARAM)hFont, NULL);
        InstProce = CreateWindowEx(NULL,TEXT("msctls_progress32"), TEXT(" "), WS_CHILD | WS_VISIBLE | SS_ICON ,
            20, 70, WinowWide - 60, 30, hWndMain, (HMENU)18, hInst, NULL);//进度条这鬼东西的类名真他妈坑爹，气死欧类
        SendMessage(InstProce, PBM_SETPOS, (WPARAM)0, NULL);//进度条置零
        InstTip = CreateWindow(TEXT("static"), TEXT("正在释放文件，请勿关闭此程序"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
            20, 100, WinowWide - 60, 30, hWndMain, (HMENU)10, hInst, NULL);
        SendMessage(InstTip, WM_SETFONT, (WPARAM)hFont, NULL);
        ShowWindow(hWndbuttongo, SW_HIDE);
        ShowWindow(hWndbuttonback, SW_HIDE);
        ShowWindow(hWndbuttonexit, SW_HIDE);
        ShowWindow(InstText, ncmd);
        ShowWindow(InstProce, ncmd);
        ShowWindow(InstTip, ncmd);
        UpdateWindow(InstText);
        UpdateWindow(InstProce);
        UpdateWindow(InstTip);
    }
    else {
        DestroyWindow(InstText);
        DestroyWindow(InstProce);
        DestroyWindow(InstTip);
        ShowWindow(hWndbuttongo, SW_SHOW);
        ShowWindow(hWndbuttonback, SW_SHOW);
        ShowWindow(hWndbuttonexit, SW_SHOW);
    }
}

void ShowFinallyPage(bool sta = FALSE) {
    if (sta) {
        FinalText = CreateWindow(TEXT("static"), TEXT("安装完成！"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
            20, 40, WinowWide - 60, 30, hWndMain, (HMENU)34, hInst, NULL);
        SendMessage(FinalText, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hWndbuttongo, WM_SETTEXT, NULL, (LPARAM)L"完成安装");
        ShowWindow(FinalText, ncmd);
        UpdateWindow(FinalText);
        ShowWindow(hWndbuttonback, SW_HIDE);
        ShowWindow(hWndbuttonexit, SW_HIDE);
    }
    else {
        DestroyWindow(FinalText);
        ShowWindow(hWndbuttonback, SW_SHOW);
        ShowWindow(hWndbuttonexit, SW_SHOW);
    }
}

void StepGoto(CHAR Stp) {
    if (Stp > 4 || Stp < 0)Stp = 0,Step=0;
    switch (Stp) {
    case 0: {//第一步
        ShowLince(FALSE);
        ShowPathSelect(FALSE);
        ShowInstProcess(FALSE);
        ShowFinallyPage(FALSE);
        ShowFirstPage(TRUE);
        break;
    }
    case 1: {//第二步
        ShowFirstPage(FALSE);
        ShowPathSelect(FALSE);
        ShowInstProcess(FALSE);
        ShowFinallyPage(FALSE);
        ShowLince(TRUE);
        break;
    }
    case 2: {
        ShowFirstPage(FALSE);
        ShowLince(FALSE);
        ShowInstProcess(FALSE);
        ShowFinallyPage(FALSE);
        ShowPathSelect(TRUE);
        break;
    }
    case 3: {
        ShowFirstPage(FALSE);
        ShowLince(FALSE);
        ShowPathSelect(FALSE);
        ShowFinallyPage(FALSE);
        ShowInstProcess(TRUE);
        break;
    }
    case 4: {
        ShowFirstPage(FALSE);
        ShowLince(FALSE);
        ShowPathSelect(FALSE);
        ShowInstProcess(FALSE);
        ShowFinallyPage(TRUE);
        break;
    }
    default:{
        ShowFirstPage(FALSE);
        ShowLince(FALSE);
        ShowPathSelect(FALSE);
        ShowInstProcess(FALSE);
        ShowFinallyPage(FALSE);
        Step = 0;
        StepGoto(Step);
        break;
    }
    }

}

BOOL MakeDir(WCHAR Path[MAX_PATH]) {//创建多级目录
    unsigned short int count = 0;
    struct _stat s;
    WCHAR TempPath[MAX_PATH] = L"";
    for (count = 0;count < wcslen(Path);++count) {//遍历路径字符串逐级提取目录尝试创建
        if ((Path[count] != L'\\')&&(count != wcslen(Path)-1)) {
            TempPath[count] = Path[count];
        }
        else {
            if (Path[count] != L'\\' && (count == wcslen(Path)-1)) {
                TempPath[count] = Path[count];
                (void)_wmkdir(TempPath);//创建单个目录
            }
            else {
                (void)_wmkdir(TempPath);//创建单个目录
                TempPath[count] = Path[count];
            }
        }
    }
    if (_wstat(Path, &s) == -1) {//判断最终目录是否存在
        return FALSE;
    }else{
        return TRUE;
    }
}

BOOL UnzipFileRes(void) {//释放文件资源
    UINT32 count = 0;
    WCHAR TempPath[MAX_PATH] = L"";
    for (count = 0;count < sizeof(files) / sizeof(files[0]);++count) {//释放文件
        wcscpy_s(TempPath, L"");//清空缓存目录的字符串
        wcscpy_s(TempPath,InstallPath);
        wcscat_s(TempPath, files[count].filedir);//组合相对路径
        if(MakeDir(TempPath) == FALSE) {
            return FALSE;//创建目录,失败返回错误
        }
        wcscat_s(TempPath, L"\\");
        wcscat_s(TempPath, files[count].Name);//组合文件名
        if (ExportRes(TempPath, files[count].ResID) == false) {return FALSE;//解压文件,如果失败返回错误
        }
        SendMessage(InstProce, PBM_SETPOS, (WPARAM)((count + 1) / (sizeof(files) / sizeof(files[0]))*100), NULL);//进度条置零
    }
    return TRUE;
}

BOOL RegInstallInfo(void) {//写入注册表安装信息
    HKEY RegKey;
    RegCreateKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\TaruCraft", 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_WOW64_64KEY, NULL, &RegKey,NULL);
    for (unsigned short int i = 0;i < sizeof(RegKeyValueList) / sizeof(RegKeyValueList[0]);++i) {
        (void)RegSetValueEx(RegKey, RegKeyValueList[i].KeyName, 0, REG_SZ, (byte*)RegKeyValueList[i].KeyValue, sizeof(RegKeyValueList[i].KeyValue));

    }
    /*WCHAR DisplayName[] = L"TaruCraft客户端";
    
    WCHAR Publisher[] = L"塔里木大学方块创作社";
    (void)RegSetValueEx(RegKey, L"Publisher", 0, REG_SZ, (byte*)Publisher, sizeof(Publisher));
    WCHAR Version[] = L"1.0";
    (void)RegSetValueEx(RegKey, L"Version", 0, REG_SZ, (byte*)Version, sizeof(Version));
    (void)RegSetValueEx(RegKey, L"InstallPath", 0, REG_SZ, (byte*)InstallPath, sizeof(InstallPath));*/
    WCHAR UninstallString[MAX_PATH] = L"";
    wcscpy_s(UninstallString, InstallPath);
    wcscat_s(UninstallString, L"\\Uninstall.exe");
    (void)RegSetValueEx(RegKey, L"UninstallString", 0, REG_SZ, (byte*)UninstallString, sizeof(UninstallString));
    wcscat_s(UninstallString, L",2");
    RegSetValueEx(RegKey, L"DisplayIcon", 0, REG_SZ, (byte*)UninstallString, sizeof(UninstallString));
    

    return TRUE;
}
HRESULT CreateLink(LPCWSTR lpszPathObj, LPCWSTR lpszPathLink, LPCWSTR lpszDesc = NULL, LPCWSTR lpszArgs = NULL, LPCWSTR lpszIcon = NULL,CHAR IcoCount=0)
{
    HRESULT hres;
    IShellLink* psl;

    // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
    // has already been called.
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
    DWORD errorCode = ::GetLastError();

    if (SUCCEEDED(hres))
    {
        IPersistFile* ppf;

        // Set the path to the shortcut target and add the description. 
        psl->SetPath(lpszPathObj);
        if (lpszDesc)
        {
            psl->SetDescription(lpszDesc);
        }
        if (lpszIcon)
        {
            psl->SetIconLocation(lpszIcon, IcoCount);//第二个图标
        }
        if (lpszArgs)
        {
            psl->SetArguments(lpszArgs);
        }

        // Query IShellLink for the IPersistFile interface, used for saving the 
        // shortcut in persistent storage. 
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

        if (SUCCEEDED(hres))
        {
            /*
            WCHAR wsz[MAX_PATH];
            // Ensure that the string is Unicode.
            MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH);
            */
            // Save the link by calling IPersistFile::Save. 
            hres = ppf->Save(lpszPathLink, TRUE);
            ppf->Release();
        }
        psl->Release();
    }
    return hres;
}
void tryMkShellLink(LPCWSTR From, LPCWSTR Dir, LPCWSTR Name, LPCWSTR Argv, LPCWSTR Icon,CHAR IcoCount=0)
{
    (void)CoInitialize(0);//初始化com组件,返回值表示是否成功
    CreateLink(From, Dir, Name, Argv, Icon, IcoCount);
    CoUninitialize();
}

int InstthreadProc() {
    InstallProce = TRUE;
    if (UnzipFileRes() == FALSE) { InstallProce = FALSE;}
    if (RegInstallInfo() == FALSE) { InstallProce = FALSE;}
    WCHAR Tmp[MAX_PATH] = L"", Tmp2[MAX_PATH] = L"", Dir[] = L"\\TaruCraft客户端.lnk",
        Name[] = L"TaruCraft客户端", Argv[] = L"";
    wcscpy_s(Tmp, InstallPath);
    wcscat_s(Tmp, L"\\TARUCRAFT.EXE");
    ShellExecute(NULL, _T("open"), Tmp, _T(""), InstallPath, SW_HIDE);
    wcscpy_s(Tmp, L"");
    wcscpy_s(Tmp, InstallPath);
    wcscat_s(Tmp, L"\\Plain Craft Launcher 2.exe");
    wcscpy_s(Tmp2, InstallPath);
    wcscat_s(Tmp2, L"\\Uninstall.exe");
    //CoInitialize(0);
    //MessageBox(NULL, Dir, L"", MB_OK);
    //CreateLink(Tmp, Dir, Name, Argv, Tmp2);
    //CoUninitialize();
    wchar_t desk_path[MAX_PATH] = { 0 },StartMenu[MAX_PATH]=L"";
    ::SHGetSpecialFolderPath(NULL, (LPWSTR)desk_path, CSIDL_DESKTOPDIRECTORY, FALSE);
    ::SHGetSpecialFolderPath(NULL, (LPWSTR)StartMenu, CSIDL_PROGRAMS, FALSE);
    wcscat_s(StartMenu, L"\\TaruCraft客户端");
    wcscat_s(desk_path, Dir);
    tryMkShellLink(Tmp, desk_path, Name, Argv, Tmp2,2);
    (void)_wmkdir(StartMenu);
    wcscat_s(StartMenu, Dir);
    tryMkShellLink(Tmp, StartMenu, Name, Argv, Tmp2,2);
    wcscpy_s(Tmp, L"");
    wcscpy_s(Tmp, InstallPath);
    wcscat_s(Tmp, L"\\Uninstall.exe");
    wcscpy_s(StartMenu, L"");
    ::SHGetSpecialFolderPath(NULL, (LPWSTR)StartMenu, CSIDL_PROGRAMS, FALSE);
    wcscat_s(StartMenu, L"\\TaruCraft客户端\\卸载TaruCraft客户端.lnk");
    tryMkShellLink(Tmp, StartMenu, Name, Argv, Tmp2);
    Sleep(3 * 1000);
    SendMessage(hWndMain, WM_INSTFINSH, NULL, NULL);
    return 0;
}
BOOL StartInst(void) {
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InstthreadProc, NULL, 0, NULL);
    return TRUE;
}
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    //初始化通用控件
    INITCOMMONCONTROLSEX MyControlList = {sizeof(MyControlList),ICC_PROGRESS_CLASS };
    if(InitCommonControlsEx(&MyControlList)==FALSE)Win7MsgBox(L"烷基八氮", L"控件加载失败", L"您必须同意用户协议才能继续安装", -2, L"");
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;
    //__try {
        //SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
        SetProcessDPIAware();//支持高dpi
    //}
    //__finally{
        
    //}
        
    while (1)//主消息循环
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {//如果进程消息队列存在消息则派发给窗口处理函数处理
            if (GetMessage(&msg, nullptr, 0, 0)) {
                if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            else
            {//当消息是WM_QUIT时结束循环
                break;
            }
        }
        else {//无消息时的空闲处理
            //__try {
                //SetProcessDPIAware();//支持高dpi
                //ExtendIntoClientAll(hWndMain);
                UpdateWindow(hWndMain);
            //}
            //__finally{

            //}
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;//MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   ncmd = nCmdShow;
   hMen = LoadMenu(hInst, (LPCWSTR)IDC_MY);
   hMen = GetSubMenu(hMen, 0);
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_DLGFRAME| WS_MINIMIZEBOX| WS_CLIPSIBLINGS,
      CW_USEDEFAULT, 0, WinowWide, WindowHight, nullptr, nullptr, hInstance, nullptr);
   hWndMain = hWnd;
   __try {
       //UseAero(hWnd);
       //ExtendIntoClientAll(hWnd);
       
   }
   __finally {
   
   }
   if (!hWnd)
   {
      return FALSE;
   }
   hWndbuttongo = CreateWindowW(_T("BUTTON"), L"下一步", WS_TABSTOP | WS_CHILD,
       WinowWide-(30+100), WindowHight-30-35-30, 100, 35, hWnd, (HMENU)BTN_GO, hInstance, nullptr);//继续按钮
   hWndbuttonexit = CreateWindowW(_T("BUTTON"), L"放弃安装", WS_TABSTOP | WS_CHILD,
       WinowWide - (30 + 100)*3+40, WindowHight - 30 - 35 - 30, 100, 35, hWnd, (HMENU)BTN_CAL, hInstance, nullptr);//取消按钮
   hWndbuttonabout = CreateWindowW(_T("BUTTON"), L"关于", WS_TABSTOP | WS_CHILD,
       14, WindowHight - 30 - 35 - 30, 100, 35, hWnd, (HMENU)BTN_ABOUT, hInstance, nullptr);//关于按钮
   hWndbuttonback = CreateWindowW(_T("BUTTON"), L"上一步", WS_TABSTOP | WS_CHILD,
       WinowWide - (30 + 100) * 2 + 20, WindowHight - 30 - 35 - 30, 100, 35, hWnd, (HMENU)BTN_BACK, hInstance, nullptr);//上一步按钮
   //ExtendIntoClientAll(hWndbuttonabout);
   SendMessage(hWndbuttongo, WM_SETFONT, (WPARAM)hFont, NULL);
   SendMessage(hWndbuttonexit, WM_SETFONT, (WPARAM)hFont, NULL);
   SendMessage(hWndbuttonabout, WM_SETFONT, (WPARAM)hFont, NULL);
   SendMessage(hWndbuttonback, WM_SETFONT, (WPARAM)hFont, NULL);
   //EnableBlurBehindWindow(hWndbutton1, FALSE, 0, FALSE);
   ShowWindow(hWnd, nCmdShow);
   ShowWindow(hWndbuttongo, nCmdShow);
   UpdateWindow(hWndbuttongo);
   ShowWindow(hWndbuttonexit, nCmdShow);
   UpdateWindow(hWndbuttonexit);
   ShowWindow(hWndbuttonabout, nCmdShow);
   UpdateWindow(hWndbuttonabout);
   ShowWindow(hWndbuttonback, nCmdShow);
   UpdateWindow(hWndbuttonback);
   /* RECT hostWindowRect{};//之前用于给按钮添加图标美化程序的代码，但感觉不需要，于是暂时砍掉
    HICON hicon;
   GetWindowRect(hWndbuttongo, &hostWindowRect);
   hicon = (HICON)LoadImage(hInst,
       MAKEINTRESOURCE(IDI_GO), IMAGE_ICON, 0, 0,
       LR_DEFAULTCOLOR);
   SendMessage(hWndbuttongo, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hicon);

   GetWindowRect(hWndbuttonexit, &hostWindowRect);
   hicon = (HICON)LoadImage(hInst,
       MAKEINTRESOURCE(IDI_EXIT), IMAGE_ICON, 0, 0,
       LR_DEFAULTCOLOR);
   SendMessage(hWndbuttonexit, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hicon);

   GetWindowRect(hWndbuttonabout, &hostWindowRect);
   hicon = (HICON)LoadImage(hInst,
       MAKEINTRESOURCE(IDI_ABOUT), IMAGE_ICON, 0, 0,
       LR_DEFAULTCOLOR);
   SendMessage(hWndbuttonabout, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hicon);*/
   StepGoto(Step);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INSTFINSH: {
        if (InstallProce == TRUE) {
            StepGoto(++Step);
        }
        else {
            StepGoto(--Step);
            SendMessage(ErrorInfo, WM_SETTEXT, NULL, (LPARAM)L"您之前选择的目录无法安装，请重新选择");
        }
    }
        break;
    case WM_UNZIP:
        if (Step < 2) {
            if (Step == 1 && Eula != TRUE) {
                Win7MsgBox(L"烷基八氮", L"无法继续安装", L"您必须同意用户协议才能继续安装", -2, L"");
            }
            else
            {
                StepGoto(++Step);
            }
        }
        else if (Step == 2) {
            if (Eula != TRUE) {
                Win7MsgBox(L"好家伙", L"你居然想不同意用户协议就安装程序", L"别想了", -2, L"");
            }
            else {
                //SendMessage(PathEdit, WM_GETTEXT, 32, (LPARAM)InstallPath);//这个地方有点大坑，从此处取值写入字符串会丢东西！
                StepGoto(++Step);
                StartInst();
            }
        }
        else if (Step == 4) {
            PostMessage(hWnd, WM_DESTROY, NULL, NULL);
        }
        //ExportRes(L"geek.exe", IDR_FILES1);//解压文件
        //ShellExecute(hWnd, _T("open"), _T("geek.exe"), _T(""), NULL, SW_HIDE);
        //PostMessage(hWnd, WM_DESTROY, NULL, NULL);
        
        break;
    case WM_CREATE:
        SetDarkMode(hWnd, DARKMODE);
        PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
        PostMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, NULL);
        //这里的最小化然后还原的迷惑操作是为了修win11使用acrylic效果时标题栏首次显示不正常的奇怪BUG
        //这破BUG就他妈离谱，也不知道微软程序员咋写的代码
        break;
    case WM_SYSCOMMAND:
        switch(wParam){
        case SC_CLOSE:
            if (Win7AskBox(L"退出程序", L"是否要退出本程序", L"此操作会退出并关闭本程序,你是否继续退出此程序?", false, -3) == IDYES) {
                PostMessage(hWnd, WM_DESTROY, NULL, NULL);
            }
            return 0;
        }
        DefWindowProc(hWnd, message, wParam, lParam);
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            /*case IDM_EXIT:
                PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, NULL);
                //DestroyWindow(hWnd);
                break;*/
            /*case IDM_GO:
                PostMessage(hWnd, WM_UNZIP, NULL, NULL);
                break;*/
            case IDM_MIN:
                PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
                break;
            case BTN_GO:
                PostMessage(hWnd, WM_UNZIP, NULL, NULL);
                break;
            case BTN_BACK:
                if(Step>0)
                StepGoto(--Step);
                break;
            case BTN_CAL:
                PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, NULL);
                break;
            case BTN_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case BTN_AGREE:
                Eula = TRUE;
                ShowLinceEula();
                break;
            case BTN_DISAGREE:
                Eula = FALSE;
                ShowLinceEula();
                break;
            case BTN_SELECTPATH:{
                BROWSEINFO bi = { 0 };
                bi.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄
                bi.pszDisplayName = InstallPath;//接收文件夹的缓冲区
                bi.lpszTitle = TEXT("选择一个文件夹");//标题
                bi.ulFlags = BIF_NEWDIALOGSTYLE;
                LPITEMIDLIST idl = SHBrowseForFolder(&bi);
                if (SHGetPathFromIDList(idl, InstallPath)) {
                    if (InstallPath[wcslen(InstallPath) - 1] == L'\\') {
                        wcscat_s(InstallPath, L"TaruCraft");
                    }
                    else {
                        wcscat_s(InstallPath, L"\\TaruCraft");
                    }
                    SendMessage(PathEdit, WM_SETTEXT, NULL, (LPARAM)InstallPath);
                    UpdateWindow(SelectPath);
                }
                else {
                }
                break;}
            case BTN_BACKPAGE: {
                if (LinceShowPage > (sizeof(LinceMainText) / sizeof(LinceMainText[0])) || LinceShowPage < 1) {
                    LinceShowPage = 1;
                    SendMessage(SticLine, WM_SETTEXT, NULL, (LPARAM)LinceMainText[0]);
                    WCHAR Pagenum[] = L"";
                    wsprintf(Pagenum, L"%d", LinceShowPage);
                    SendMessage(LincePageNum, WM_SETTEXT, NULL, (LPARAM)Pagenum);
                }
                else {
                    if(LinceShowPage != 1){
                    --LinceShowPage;
                    WCHAR Pagenum[] = L"";
                    wsprintf(Pagenum, L"%d", LinceShowPage);
                    SendMessage(SticLine, WM_SETTEXT, NULL, (LPARAM)LinceMainText[LinceShowPage-1]);
                    SendMessage(LincePageNum, WM_SETTEXT, NULL, (LPARAM)Pagenum);
                    }
                }
                if (LinceShowPage == 1) {
                    ShowWindow(LinceBackPage, SW_HIDE);
                    ShowWindow(LinceNextPage, SW_SHOW);
                }
                else if (LinceShowPage == sizeof(LinceMainText) / sizeof(LinceMainText[0])) {
                    ShowWindow(LinceBackPage, SW_SHOW);
                    ShowWindow(LinceNextPage, SW_HIDE);
                }
                else {
                    ShowWindow(LinceNextPage, SW_SHOW);
                    ShowWindow(LinceBackPage, SW_SHOW);
                }
                break;
            }
            case BTN_NEXTPAGE: {
                if (LinceShowPage > (sizeof(LinceMainText) / sizeof(LinceMainText[0])) || LinceShowPage < 1) {
                    LinceShowPage = (sizeof(LinceMainText) / sizeof(LinceMainText[0]))-1;
                    SendMessage(SticLine, WM_SETTEXT, NULL, (LPARAM)LinceMainText[(sizeof(LinceMainText) / sizeof(LinceMainText[0])) - 1]);
                    WCHAR Pagenum[] = L"";
                    wsprintf(Pagenum, L"%d", LinceShowPage);
                    SendMessage(LincePageNum, WM_SETTEXT, NULL, (LPARAM)Pagenum);
                }
                else {
                    if (LinceShowPage != (sizeof(LinceMainText) / sizeof(LinceMainText[0]))) {
                        ++LinceShowPage;
                        WCHAR Pagenum[] = L"";
                        wsprintf(Pagenum, L"%d", LinceShowPage);
                        SendMessage(SticLine, WM_SETTEXT, NULL, (LPARAM)LinceMainText[LinceShowPage-1]);
                        SendMessage(LincePageNum, WM_SETTEXT, NULL, (LPARAM)Pagenum);
                    }
                }
                if (LinceShowPage == 1) {
                    ShowWindow(LinceBackPage, SW_HIDE);
                    ShowWindow(LinceNextPage, SW_SHOW);
                }
                else if (LinceShowPage == sizeof(LinceMainText) / sizeof(LinceMainText[0])) {
                    ShowWindow(LinceBackPage, SW_SHOW);
                    ShowWindow(LinceNextPage, SW_HIDE);
                }
                else {
                    ShowWindow(LinceNextPage, SW_SHOW);
                    ShowWindow(LinceBackPage, SW_SHOW);
                }
                break;
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            HICON hicon = (HICON)::LoadImage(
                hInst,
                MAKEINTRESOURCE(IDI_BOTTOM),
                IMAGE_ICON,
                0,
                0,
                LR_DEFAULTCOLOR);
            CHAR i = 0;
            for(;i<6;i++){
            DrawIconEx(hdc, 128*i, WindowHight-110, hicon, 128, 128, 0, NULL, DI_IMAGE);
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
            PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN://鼠标左键按下产生
        PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);//发送鼠标按住标题栏的消息，模拟鼠标按住标题栏，实现拖动
        DefWindowProc(hWnd, message, wParam, lParam);
        break;
    case WM_CTLCOLOREDIT:{
            HDC hdc = (HDC)wParam;
            SetTextColor(hdc, RGB(55, 55, 55));
            SetBkMode(hdc, TRANSPARENT);
            //return (INT_PTR)CreateSolidBrush(NULL_BRUSH);
        break;}
    case WM_RBUTTONUP://右键窗口内部时    
        POINT p;
        GetCursorPos(&p);
        PostMessage(hWnd, WM_COMMAND,
            TrackPopupMenu(hMen, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_VERNEGANIMATION,
                p.x, p.y, 0, hWnd, 0), 0//弹出右键菜单
        );
        DefWindowProc(hWnd, message, wParam, lParam);
        break;
    case WM_CTLCOLORBTN:
        {
        if ((HWND)lParam == GetDlgItem(hWnd, BTN_AGREE) || (HWND)lParam == GetDlgItem(hWnd, BTN_DISAGREE) ||
            (HWND)lParam == GetDlgItem(hWnd, BTN_SELECTPATH)|| (HWND)lParam == GetDlgItem(hWnd, BTN_NEXTPAGE)||
            (HWND)lParam == GetDlgItem(hWnd, BTN_BACKPAGE)) {
            //return (INT_PTR)CreateSolidBrush(NULL_BRUSH);
            }else{
            SetTextColor((HDC)wParam, TRANSPARENT);
            SetBkMode((HDC)wParam, TRANSPARENT);
            return (INT_PTR)CreateSolidBrush(RGB(135, 135, 135));
        }
        }
        break;
    case WM_CTLCOLORSTATIC:{
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(99, 99, 99));
        SetBkColor(hdcStatic, RGB(0x41, 0x96, 0x4F));  //设置字体背景为翠绿色
        SetBkMode(hdcStatic, TRANSPARENT);  //透明背景
        //return (INT_PTR)hBrush; //这里必须返回画刷句柄
        //return (INT_PTR)GetStockObject(NULL_BRUSH);  //无颜色画刷
    }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        //SetDialogBkColor();
        //ExtendIntoClientAll(hDlg);
        SetDarkMode(hDlg, DARKMODE);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
