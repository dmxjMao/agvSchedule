// TabColorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TabColorDlg.h"
#include "afxdialogex.h"


// CTabColorDlg 对话框

IMPLEMENT_DYNAMIC(CTabColorDlg, CDialogEx)

CTabColorDlg::CTabColorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_COLOR, pParent)
{

}

CTabColorDlg::~CTabColorDlg()
{
}

void CTabColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabColorDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabColorDlg 消息处理程序
