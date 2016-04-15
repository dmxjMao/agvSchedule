#pragma once
#include "afxcmn.h"


// CTabCarInfoDlg 对话框

class CTabCarInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCarInfoDlg)

public:
	CTabCarInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabCarInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CARINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctl;
	virtual BOOL OnInitDialog();
};
