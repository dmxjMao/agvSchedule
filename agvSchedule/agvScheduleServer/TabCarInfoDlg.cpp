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
}


BEGIN_MESSAGE_MAP(CTabCarInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabCarInfoDlg 消息处理程序
