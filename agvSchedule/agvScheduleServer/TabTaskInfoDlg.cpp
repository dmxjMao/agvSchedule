// TabTaskInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TabTaskInfoDlg.h"
#include "afxdialogex.h"


// CTabTaskInfoDlg 对话框

IMPLEMENT_DYNAMIC(CTabTaskInfoDlg, CDialogEx)

CTabTaskInfoDlg::CTabTaskInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TASKINFO, pParent)
{

}

CTabTaskInfoDlg::~CTabTaskInfoDlg()
{
}

void CTabTaskInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CTabTaskInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabTaskInfoDlg 消息处理程序


BOOL CTabTaskInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rs;
	GetParent()->GetClientRect(&rs);
	m_ctl.MoveWindow(&rs);

	CString field[] = { _T("索引"),  _T("车辆"), _T("优先级"), _T("起始点"),  _T("目标点") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		// iCol为列的位置，从零开始，lpszColumnHeading为显示的列名，
		// nFormat为显示对齐方式， nWidth为显示宽度，nSubItem为分配给该列的列索引。
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 70);
	}

	//m_ctl.ShowScrollBar(SB_HORZ);

	// 读取数据库
	//m_AdoConn.OnInitADOConn();
	//CString sql = _T("select * from tasklist");
	//m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//int i = 0;
	//while (!m_pRs->adoEOF) {
	//	m_ctl.InsertItem(i, (_bstr_t)m_pRs->GetCollect("taskid"));
	//	m_ctl.SetItemText(i, 1, (_bstr_t)m_pRs->GetCollect("agvno"));
	//	m_ctl.SetItemText(i, 2, (_bstr_t)m_pRs->GetCollect("priority"));
	//	m_ctl.SetItemText(i, 3, (_bstr_t)m_pRs->GetCollect("startPt"));
	//	m_ctl.SetItemText(i, 4, (_bstr_t)m_pRs->GetCollect("endPt"));

	//	m_pRs->MoveNext();
	//	++i;
	//}

	//m_AdoConn.ExitConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
