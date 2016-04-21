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
	DDX_Control(pDX, IDC_COMBO_CARID, m_comboCarid);
	DDX_Control(pDX, IDC_STATIC_CARID, m_stsCarid);
	DDX_Control(pDX, IDC_STATIC_STATUS0, m_stsStatus0);
	DDX_Control(pDX, IDC_STATIC_STATUS1, m_stsStatus1);
	DDX_Control(pDX, IDC_STATIC_STATUS10, m_stsStatus10);
	DDX_Control(pDX, IDC_STATIC_STATUS11, m_stsStatus11);
	DDX_Control(pDX, IDC_STATIC_STATUS12, m_stsStatus12);
	DDX_Control(pDX, IDC_STATIC_STATUS13, m_stsStatus13);
	DDX_Control(pDX, IDC_STATIC_STATUS14, m_stsStatus14);
	DDX_Control(pDX, IDC_STATIC_STATUS15, m_stsStatus15);
	DDX_Control(pDX, IDC_STATIC_STATUS2, m_stsStatus2);
	DDX_Control(pDX, IDC_STATIC_STATUS3, m_stsStatus3);
	DDX_Control(pDX, IDC_STATIC_STATUS4, m_stsStatus4);
	DDX_Control(pDX, IDC_STATIC_STATUS5, m_stsStatus5);
	DDX_Control(pDX, IDC_STATIC_STATUS6, m_stsStatus6);
	DDX_Control(pDX, IDC_STATIC_STATUS7, m_stsStatus7);
	DDX_Control(pDX, IDC_STATIC_STATUS8, m_stsStatus8);
	DDX_Control(pDX, IDC_STATIC_STATUS9, m_stsStatus9);
}


BEGIN_MESSAGE_MAP(CTabControlDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabControlDlg 消息处理程序


BOOL CTabControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str[] = {_T("001"), _T("002") ,_T("003") ,_T("004") ,
		_T("005") ,_T("006") };
	for (int i = 0; i < 6; ++i) {
		m_comboCarid.InsertString(i, str[i]);
	}
	m_comboCarid.SetCurSel(0);
	m_stsCarid.SetWindowTextW(_T("1号车"));

	m_arrStatus[0] = &m_stsStatus0;
	m_arrStatus[1] = &m_stsStatus1;
	m_arrStatus[2] = &m_stsStatus2;
	m_arrStatus[3] = &m_stsStatus3;
	m_arrStatus[4] = &m_stsStatus4;
	m_arrStatus[5] = &m_stsStatus5;
	m_arrStatus[6] = &m_stsStatus6;
	m_arrStatus[7] = &m_stsStatus7;
	m_arrStatus[8] = &m_stsStatus8;
	m_arrStatus[9] = &m_stsStatus9;
	m_arrStatus[10] = &m_stsStatus10;
	m_arrStatus[11] = &m_stsStatus11;
	m_arrStatus[12] = &m_stsStatus12;
	m_arrStatus[13] = &m_stsStatus13;
	m_arrStatus[14] = &m_stsStatus14;
	m_arrStatus[15] = &m_stsStatus15;


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
