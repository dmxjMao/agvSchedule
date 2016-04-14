#pragma once
#include "afxcmn.h"
#include "ADOConn.h"

// CCarListDlg 对话框

class CCarListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarListDlg)

public:
	CCarListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCarListDlg();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CARLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctl;
};
