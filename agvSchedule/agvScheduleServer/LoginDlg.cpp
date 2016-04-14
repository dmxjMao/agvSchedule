// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_account(_T(""))
	, m_passwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USECOUNT, m_account);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_passwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	CDialogEx::OnOK();
}
