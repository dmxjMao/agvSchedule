#pragma once
#include "afxwin.h"

// CTabControlDlg 对话框

class CTabControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabControlDlg)

public:
	CTabControlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabControlDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboCarid;
	CStatic m_stsCarid;
	CStatic m_stsStatus0;
	CStatic m_stsStatus1;
	CStatic m_stsStatus10;
	CStatic m_stsStatus11;
	CStatic m_stsStatus12;
	CStatic m_stsStatus13;
	CStatic m_stsStatus14;
	CStatic m_stsStatus15;
	CStatic m_stsStatus2;
	CStatic m_stsStatus3;
	CStatic m_stsStatus4;
	CStatic m_stsStatus5;
	CStatic m_stsStatus6;
	CStatic m_stsStatus7;
	CStatic m_stsStatus8;
	CStatic m_stsStatus9;

	CStatic* m_arrStatus[16];
};
