#pragma once
#include "afxcmn.h"
#include "ADOConn.h"


// CTaskList 对话框

class CTaskList : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskList)

public:
	CTaskList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskList();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TASKLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctl;
};
