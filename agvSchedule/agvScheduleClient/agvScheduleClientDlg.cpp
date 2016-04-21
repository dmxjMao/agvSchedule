
// agvScheduleClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <vector>
#include "agvScheduleClient.h"
#include "agvScheduleClientDlg.h"
#include "afxdialogex.h"

#include "NetSocketDef.h"
#include "MsgStruct.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 给小车一条指定的路线:小车1 （1-2-3）
static std::vector<Msg_E1>  g_vecE1;
// 小车2：（2-3-4-26-24）
static std::vector<Msg_E1>	g_vecE1No2;

void setVecE1()
{
	/*
	E1: agv上报 200ms
	45 31
	01 车号
	01 M1消息标签
	01 M2消息标签
	01 M6消息标签
	00 01 当前所走段距离(mm)
	00 01 当前段号
	00 01 当前点号
	00 01 agc状态位
	01 agc错误码
	01 预留
	00 01 当前速度mm/s
	01 移动完成&操作完成
	00 01 当前任务号
	共21字节
	*/
	extern BYTE g_AGVNo;
	Msg_E1 e1;
	if (1 == g_AGVNo)
	{
		e1.m1tag = e1.m2tag = e1.m6tag = 1;
		e1.agvno = g_AGVNo;

		e1.curPoint = 1;
		e1.curDist = 1; // mm

		for (int i = 0; i < 5; ++i)
		{
			// 在1-2段走1s 5次 5mm 1-2点41个像素，每次走1/5 8像素
			g_vecE1.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 2;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// 在2-3段走1s 5次 5mm 1-2点41个像素，每次走1/5 8像素
			g_vecE1.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 3;
		e1.curDist = 0;
		g_vecE1.push_back(e1);
	}

	if (2 == g_AGVNo) {
		e1.agvno = g_AGVNo;
		e1.m1tag = e1.m2tag = e1.m6tag = 2;
		e1.curPoint = 2;
		e1.curDist = 1; // mm

		for (int i = 0; i < 5; ++i)
		{
			// 在1-2段走1s 5次 5mm 1-2点41个像素，每次走1/5 8像素
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 3;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// 在2-3段走1s 5次 5mm 1-2点41个像素，每次走1/5 8像素
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 4;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// 在2-3段走1s 5次 5mm 1-2点41个像素，每次走1/5 8像素
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 26;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// 在2-3段走1s 5次 5mm 1-2点41个像素，每次走1/5 8像素
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 24;
		e1.curDist = 1;
		for (int i = 0; i < 5; ++i)
		{
			// 在2-3段走1s 5次 5mm 1-2点41个像素，每次走1/5 8像素
			g_vecE1No2.push_back(e1);
			++e1.curDist;
		}

		e1.curPoint = 24;
		e1.curDist = 0;
		g_vecE1No2.push_back(e1);
	}

}


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
public:
	virtual BOOL OnInitDialog();
	CButton m_ctl;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ctl);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CagvScheduleClientDlg 对话框



CagvScheduleClientDlg::CagvScheduleClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AGVSCHEDULECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CagvScheduleClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CagvScheduleClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CagvScheduleClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CagvScheduleClientDlg::OnClickedButtonQuit)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CagvScheduleClientDlg 消息处理程序

BOOL CagvScheduleClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	setVecE1();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CagvScheduleClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CagvScheduleClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CagvScheduleClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CagvScheduleClientDlg::OnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pAgvSocket = new CAgvSocket;
	// 创建套接字，绑定，注册网络事件
	if (!m_pAgvSocket->Create()) 
	{
		delete m_pAgvSocket;
		m_pAgvSocket = nullptr;
		AfxMessageBox(_T("创建套接字失败！"));
		return;
	}

	// 构造server地址
	TCHAR* ip = _T("127.0.0.1");
	UINT port = SVR_PORT;
	if (!m_pAgvSocket->Connect(ip, port))
	{
		AfxMessageBox(_T("连接服务器失败！"));
		delete m_pAgvSocket;
		m_pAgvSocket = nullptr;
		return;
	}

	// 初始给server发送一条E1消息，上报小车车号等信息
	extern BYTE g_AGVNo;
	Msg_E1 e1;
	e1.agvno = g_AGVNo;
	e1.curPoint = e1.agvno;
	e1.agcStatus = 1032; // 插入系统

	int sendBytes = m_pAgvSocket->Send(&e1, sizeof(e1));
	//m_pAgvSocket->AsyncSelect();

	SetTimer(1, 200, nullptr);
}


void CagvScheduleClientDlg::OnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pAgvSocket)
	{
		m_pAgvSocket->Close();
		delete m_pAgvSocket;
		m_pAgvSocket = nullptr;
	}

	EndDialog(0);
}


void CagvScheduleClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	extern BYTE g_AGVNo;
	static size_t i = 0;
	if (1 == nIDEvent)
	{
		if (m_pAgvSocket->m_bRecv) {
			if (g_AGVNo == 1) {
				int sendBytes = m_pAgvSocket->Send(&g_vecE1[i++], sizeof(Msg_E1));
				if (i == 11)
					KillTimer(1);
			}
				
			if (g_AGVNo == 2) {
				m_pAgvSocket->Send(&g_vecE1No2[i++], sizeof(Msg_E1));
				if (i == 25)
					KillTimer(1);
			}
			//m_pAgvSocket->AsyncSelect();
		}	
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
