// TabCarInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TabCarInfoDlg.h"
#include "afxdialogex.h"


// CTabCarInfoDlg 对话框

IMPLEMENT_DYNAMIC(CTabCarInfoDlg, CDialogEx)

CTabCarInfoDlg::CTabCarInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CARINFO, pParent)
{

}

CTabCarInfoDlg::~CTabCarInfoDlg()
{
}

void CTabCarInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CTabCarInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabCarInfoDlg 消息处理程序


BOOL CTabCarInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rs;
	GetParent()->GetClientRect(&rs);
	m_ctl.MoveWindow(&rs);

	CString field[] = { _T("小车号"),  _T("主状态"), _T("当前点"), _T("目标点"),  _T("当前段") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 70);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
