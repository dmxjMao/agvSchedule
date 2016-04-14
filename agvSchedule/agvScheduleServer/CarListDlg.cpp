// CarListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "CarListDlg.h"
#include "afxdialogex.h"


// CCarListDlg 对话框

IMPLEMENT_DYNAMIC(CCarListDlg, CDialogEx)

CCarListDlg::CCarListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CARLIST, pParent)
{

}

CCarListDlg::~CCarListDlg()
{
}

void CCarListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctl);
}


BEGIN_MESSAGE_MAP(CCarListDlg, CDialogEx)
END_MESSAGE_MAP()


// CCarListDlg 消息处理程序


BOOL CCarListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString field[] = { _T("小车号"),_T("任务号"), _T("当前点"), _T("当前段"),
		_T("目标点"),_T("操作码"),_T("状态"), _T("错误码") };

	int fieldnum = sizeof(field) / sizeof(field[0]);
	for (int i = 0; i < fieldnum; ++i) {
		// iCol为列的位置，从零开始，lpszColumnHeading为显示的列名，
		// nFormat为显示对齐方式， nWidth为显示宽度，nSubItem为分配给该列的列索引。
		m_ctl.InsertColumn(i, field[i], LVCFMT_LEFT, 60);
	}

	m_ctl.ShowScrollBar(SB_HORZ);

	// 读取数据库
	m_AdoConn.OnInitADOConn();
	CString sql = _T("select * from carlist");
	m_pRs = m_AdoConn.GetRecordSet((_bstr_t)sql);

	//CTime time = CTime::GetCurrentTime();
	int i = 0;
	while (!m_pRs->adoEOF) {
		m_ctl.InsertItem(i, (_bstr_t)m_pRs->GetCollect("carno"));
		m_ctl.SetItemText(i, 1, (_bstr_t)m_pRs->GetCollect("taskno"));
		m_ctl.SetItemText(i, 2, (_bstr_t)m_pRs->GetCollect("curPoint"));
		m_ctl.SetItemText(i, 3, (_bstr_t)m_pRs->GetCollect("curSide"));
		m_ctl.SetItemText(i, 4, (_bstr_t)m_pRs->GetCollect("targetPoint"));
		m_ctl.SetItemText(i, 5, (_bstr_t)m_pRs->GetCollect("optCode"));
		m_ctl.SetItemText(i, 6, (_bstr_t)m_pRs->GetCollect("agcStatus"));
		m_ctl.SetItemText(i, 7, (_bstr_t)m_pRs->GetCollect("agcErrCode"));

		m_pRs->MoveNext();
		++i;
	}
	m_AdoConn.ExitConn();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
