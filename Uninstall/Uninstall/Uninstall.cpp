// Uninstall.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Uninstall.h"
#include "Win7Msgbox.h"
#include "fileapi.h"
#include "shellapi.h"
#include <ShObjIdl.h>
#include <ShlGuid.h>
#include <Shlobj.h>//选择文件夹对话框
#define MAX_LOADSTRING 100
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")//用于支持windows视觉样式

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
typedef TCHAR UFileName[FILENAME_MAX];
UFileName UninstData[] = {
    L"Uninst.exe"
};
WCHAR DIRLIST[][MAX_PATH] = { L".\\.MINECRAFT" ,L".\\PCL"};//卸载后删除的目录列表
WCHAR FILELIST[][MAX_PATH] = {L"TARUCRAFT.EXE",L"Plain Craft Launcher 2.EXE",L"Uninstall.exe"};//卸载后删除的文件列表
int Win7AskBox(const wstring& WinTitle, const wstring& MsgMain, const wstring& MsgMore, const int& Icon, const wstring& MsgEx,const BOOL TwoBTN=TRUE)
{//对话框显示函数
    int Selected = -1;

    TASKDIALOGCONFIG AskWin = { sizeof(AskWin) };
    AskWin.hwndParent = GetActiveWindow();
    AskWin.dwFlags = TDF_POSITION_RELATIVE_TO_WINDOW | TDF_ENABLE_HYPERLINKS;
    if(TwoBTN==TRUE){
        AskWin.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON; 
    }
    else
    {
        AskWin.dwCommonButtons = TDCBF_OK_BUTTON;
    }

    AskWin.pszWindowTitle = WinTitle.c_str();

    if (Icon == -1) { AskWin.pszMainIcon = TD_WARNING_ICON; }
    else if (Icon == -2) { AskWin.pszMainIcon = TD_ERROR_ICON; }
    else if (Icon == -3) { AskWin.pszMainIcon = TD_INFORMATION_ICON; }
    else if (Icon == -4) { AskWin.pszMainIcon = TD_SHIELD_ICON; }

    AskWin.pszMainInstruction = MsgMain.c_str();
    AskWin.pszContent = MsgMore.c_str();
    AskWin.pszCollapsedControlText = L"&展开";
    AskWin.pszExpandedControlText = L"&收起";
    AskWin.pszExpandedInformation = MsgEx.c_str();

    if (TaskDialogIndirect(&AskWin, &Selected, NULL, NULL) != S_OK)
    {
        
    }
    else { return Selected; }
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    SetProcessDPIAware();//支持高dpi
    // 初始化全局字符串
    if (Win7AskBox(L"谢崽成旭", L"您确定坚持己见，不相信此程序开发者提出的不希望用户不采纳不相信放弃不打算不卸载TaruCraft客户端的想法？",
        L"亲爱的用户，您好！从无所凭据，便可知过去未来之事的上帝视角来看。您打开了卸载程序，并且正在阅读这段话。您也许会对程序标题的多重否定的绕口令感到费解和困惑。因此，我们不妨从文字的本质功能出发，回归到文学最朴素最本质的核心内涵，并尝试理解这个卸载程序上令人费解的标题。显然，从文字最朴素的功能本质来看。文字存在的最本质的意义在于传递和信息和情感。从这一本质来出发，尝试理解这个在卸载程序上使用复杂的长篇大论，试图以此阻止用户卸载，不识抬举、用心险恶的程序作者试图传递的信息和情感。我们按照由此观点产生的方法论可知。卸载这个程序的重要步骤就是正确操作这个卸载程序。而正确操作这个卸载程序的关键步骤就在于理解这段复杂的长篇废话包含的信息和情感。仅从语文的观点看待这个问题。这个卸载程序中复杂的绕口令不过是多重否定组成的谜语。而破除这个问题的关键在于跳出常规的思维。尝试用逻辑学和数学的观点看待这个问题。从被人们熟知的双重否定表肯定的基本语法出发，从句式中否定含义的词的个数、作者写这段话时的思维、卸载程序的功能按键及含义出发，找到正确操作这个卸载程序的方法。尽管这一过程可能充满了艰难和困苦，但从马克思主义哲学唯物辩证法的发展观点来看，这一过程虽然曲折，但前途是光明的。就如同您作为电脑前的用户，正在走马观花般的阅读这段话，尝试理解这段话所包含的信息和情感，但却发现这段话只不过是一个文字更多、且内容空洞的废话。这种挫折无疑令人失望，但考虑到将这个程序卸载的光明前途，这种挫折似乎也是必须经历的磨练。因此，我作为这个程序的作者，真诚的希望您能从文学的本质中、从马克思哲学的基本观点中、从古代先贤们的智慧中、从语文课堂上日积月累的知识中。找到这段内容空洞、令人反感的废话中所蕴含的核心思想，将这个程序作者不想让用户卸载的阴谋彻底打破。",
        -3, L"人话:你是否保留TaruCraft客户端") == IDYES) {


    }
    else
    {
        if(Win7AskBox(L"谢崽成旭", L"氨醛警告:这个卸载程序没有认真开发！",L"亲爱的用户，您好！我知道您很想卸载这个软件，并且通过了上一关的试炼。对于您通过上一关试炼的方法。或是尝试理解了那一大段废话，或是通过穷举找到了正确的出口，我们暂且不论。但我作为一个连标题栏的“卸载程序”4个大字都能全部打错的作者，毫无疑问是缺乏知识的**。而我这个**，不仅对内存安全的Java、Python等高级语言毫无动心之意。还固执己见的使用C++这种比较底层的编程语言进行开发。 在我这个**使用C++这种高级了但没完全高级的高级语言编程时，难免有意或无意地使用了C++未定义的行为，比如数组越界、野指针。使用这种未定义的行为，显然是不安全的。面对不同计算机，不同开发环境，不同编译器。这些相同的代码也可能产生不同的后果。虽然对于这个已经编译好的程序而言，其行为是固定的。但您面对这个**作者开发的垃圾程序仍然应当保持警惕。因此，点“是”立刻关闭这个程序可能是目前最优的选择。但如果您固执己见，我依然希望您能够认真考虑这个垃圾卸载程序可能潜藏的风险。",-1,L"人话:作者不想让你卸载，点否继续卸载")==IDYES){
            
        }
        else {
            if (Win7AskBox(L"谢崽成旭", L"对不起，作者不想让你卸载 :)", L"用户您好！作为这个程序的开发者，我真心希望你不要卸载这个程序。从微观的视角来看，您试图卸载的这个程序，不过是用电或磁等基本物理现象记录在物理介质上的大量比特。但仔细审视这些比特，我们可以得知，他们是按照一定规律存储在设备上的。相比于其他随机出现的比特，这些数据比特的熵是更低的。而它们的意义正在于此，它们是人类创造出的逆熵，是文明存在的标志。选择卸载这个程序，无疑增大了介质中的熵值，甚至加速了宇宙更快到达热寂的终极终点。因此，我希望您能将宇宙的未来纳入自己考虑的范围，不要卸载这个程序。   ", -2, L"我才不会告诉你，其实点“是”就能真正卸载这个程序") == IDYES) {
                ShellExecute(NULL, _T("open"), L"TASKKILL.EXE", _T("/F /T /IM TARUCRAFT.EXE"), L"", SW_HIDE);
                ShellExecute(NULL, _T("open"), L"TASKKILL.EXE", _T("/F /T /IM Plain Craft Launcher 2.EXE"), L"", SW_HIDE);
                HKEY RegKey;
                RegCreateKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_WOW64_64KEY, NULL, &RegKey, NULL);//打开注册表指定目录获取句柄
                RegDeleteKey(RegKey, L"TaruCraft");//删除特定的注册表键
                wchar_t desk_path[MAX_PATH] = { 0 };
                ::SHGetSpecialFolderPath(NULL, (LPWSTR)desk_path, CSIDL_DESKTOPDIRECTORY, FALSE);
                wcscat_s(desk_path, L"\\TaruCraft客户端.lnk");
                DeleteFile(desk_path);
                for (int i = 0;i < sizeof(FILELIST) / sizeof(FILELIST[0]);++i) {
                    DeleteFile(FILELIST[i]);//删除文件
                    MoveFileEx(FILELIST[i], NULL, MOVEFILE_DELAY_UNTIL_REBOOT);//将文件标记为重启后删除(需要管理员权限，下同)
                }
                for (int i = 0;i < sizeof(DIRLIST) / sizeof(DIRLIST[0]);++i) {
                    SHFILEOPSTRUCT FileOp;
                    FileOp.fFlags = FOF_NOCONFIRMATION;
                    FileOp.hNameMappings = NULL;
                    FileOp.hwnd = NULL;
                    FileOp.lpszProgressTitle = NULL;
                    FileOp.pFrom = DIRLIST[i];
                    FileOp.pTo = NULL;
                    FileOp.wFunc = FO_DELETE;
                    SHFileOperation(&FileOp);//删除文件夹
                    MoveFileEx(DIRLIST[i], NULL, MOVEFILE_DELAY_UNTIL_REBOOT);//将目录标记为重启后删除
                }
                Win7AskBox(L"卸载程序(这几个字终于打对了)", L"需要重启", L"卸载程序执行完毕，但部分文件需要重启后才会被删除。", -1, L"", FALSE);
            }
        }
        
        
    }
    
    return 0;
}
