#pragma once

#include "ADOConn.h"
#include "afxcmn.h"
// CTabTaskInfoDlg 对话框

class CTabTaskInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabTaskInfoDlg)

public:
	CTabTaskInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabTaskInfoDlg();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TASKINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctl;
};
