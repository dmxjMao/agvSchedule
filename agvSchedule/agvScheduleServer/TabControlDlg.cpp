// TabControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TabControlDlg.h"
#include "afxdialogex.h"


// CTabControlDlg 对话框

IMPLEMENT_DYNAMIC(CTabControlDlg, CDialogEx)

CTabControlDlg::CTabControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CONTROL, pParent)
{

}

CTabControlDlg::~CTabControlDlg()
{
}

void CTabControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabControlDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabControlDlg 消息处理程序
