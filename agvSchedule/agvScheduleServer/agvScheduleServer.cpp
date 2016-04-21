
// agvScheduleServer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "agvScheduleServer.h"
#include "MainFrm.h"

#include "agvScheduleServerDoc.h"
#include "agvScheduleServerView.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CagvScheduleServerApp

BEGIN_MESSAGE_MAP(CagvScheduleServerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CagvScheduleServerApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CagvScheduleServerApp 构造

CagvScheduleServerApp::CagvScheduleServerApp()
{
	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("agvScheduleServer.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CagvScheduleServerApp 对象

CagvScheduleServerApp theApp;


// CagvScheduleServerApp 初始化

BOOL CagvScheduleServerApp::InitInstance()
{
	if (!AfxOleInit()) { return FALSE; }

	struct Msg_E1
	{
		const BYTE head[3] = { 0x21, 0x15, 0x41 };
		const BYTE type[2] = { 0x45, 0x31 };
		BYTE agvno = 0;
		BYTE m1tag = 0;
		BYTE m2tag = 0;
		BYTE m6tag = 0;
		BYTE moveOrOpt = 0;
		UINT16 curDist = 0;
		UINT16 curSec = 0;
		UINT16 curPoint = 0;
		UINT16 agcStatus = 0;
		BYTE agcError = 0;
		BYTE reserve = 0;
		UINT16 curSpeed = 0;
		UINT16 curTask = 0;

		Msg_E1& operator=(const Msg_E1& e1) {
			agvno = e1.agvno;
			m1tag = e1.m1tag;
			m2tag = e1.m2tag;
			m6tag = e1.m6tag;
			curDist = e1.curDist;
			curSec = e1.curSec;
			curPoint = e1.curPoint;
			agcStatus = e1.agcStatus;
			agcError = e1.agcError;
			reserve = e1.reserve;
			curSpeed = e1.curSpeed;
			moveOrOpt = e1.moveOrOpt;
			curTask = e1.curTask;
			return *this;
		}
	};

	size_t a = sizeof(Msg_E1);

	// 登录
	/*CLoginDlg dlgLogin;
	if (IDOK == dlgLogin.DoModal()) {
		CString name = dlgLogin.m_account;
		CString sql = _T("select * from register where username = '") + name + _T("'");
		m_AdoConn.OnInitADOConn();
		m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);
		if (m_pRs->adoEOF) {
			AfxMessageBox(_T("账号错误！"));
			return(FALSE);
		}

		CString passwd = (_bstr_t)m_pRs->GetCollect("password");
		if (passwd != dlgLogin.m_passwd) {
			AfxMessageBox(_T("密码错误！"));
			return(FALSE);
		}
	}*/

	CWinApp::InitInstance();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CagvScheduleServerDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CagvScheduleServerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CagvScheduleServerApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CagvScheduleServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CagvScheduleServerApp 消息处理程序




