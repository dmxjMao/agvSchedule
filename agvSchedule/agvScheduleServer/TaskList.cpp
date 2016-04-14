// TaskList.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "TaskList.h"
#include "afxdialogex.h"


// CTaskList 对话框

IMPLEMENT_DYNAMIC(CTaskList, CDialogEx)

CTaskList::CTaskList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TASKLIST, pParent)
{

}

CTaskList::~CTaskList()
{
}

void CTaskList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CTaskList, CDialogEx)
END_MESSAGE_MAP()


// CTaskList 消息处理程序


BOOL CTaskList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CString field[] = { _T("索引"), _T("任务号"), _T("启动时间"), _T("车辆"),
		_T("优先级"), _T("起始点"),  _T("目标点"),  _T("消息标签"),  _T("任务操作码"),
		_T("下发段数"), _T("可行走段") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		// iCol为列的位置，从零开始，lpszColumnHeading为显示的列名，
		// nFormat为显示对齐方式， nWidth为显示宽度，nSubItem为分配给该列的列索引。
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 70);
	}

	m_ctl.ShowScrollBar(SB_HORZ);

	// 读取数据库
	m_AdoConn.OnInitADOConn();
	CString sql = _T("select * from tasklist");
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//CTime time = CTime::GetCurrentTime();
	int i = 0;
	while (!m_pRs->adoEOF) {
		m_ctl.InsertItem(i, (_bstr_t)m_pRs->GetCollect("taskid"));
		m_ctl.SetItemText(i, 1, (_bstr_t)m_pRs->GetCollect("taskno"));
		m_ctl.SetItemText(i, 2, (_bstr_t)m_pRs->GetCollect("starttime"));
		m_ctl.SetItemText(i, 3, (_bstr_t)m_pRs->GetCollect("agvno"));
		m_ctl.SetItemText(i, 4, (_bstr_t)m_pRs->GetCollect("priority"));
		m_ctl.SetItemText(i, 5, (_bstr_t)m_pRs->GetCollect("startPt"));
		m_ctl.SetItemText(i, 6, (_bstr_t)m_pRs->GetCollect("endPt"));
		m_ctl.SetItemText(i, 7, (_bstr_t)m_pRs->GetCollect("msgtag"));
		m_ctl.SetItemText(i, 8, (_bstr_t)m_pRs->GetCollect("taskOptCode"));
		m_ctl.SetItemText(i, 9, (_bstr_t)m_pRs->GetCollect("sidenum"));
		m_ctl.SetItemText(i, 10, (_bstr_t)m_pRs->GetCollect("sideno"));

		m_pRs->MoveNext();
		++i;
	}

	m_AdoConn.ExitConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
