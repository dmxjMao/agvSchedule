#pragma once
#include "afxcmn.h"


// CTaskAndCarInfoDlg 对话框
class CTabColorDlg;
class CTabControlDlg;
class CTabTaskInfoDlg;
class CTabCarInfoDlg;
class CTaskAndCarInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskAndCarInfoDlg)

public:
	CTaskAndCarInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskAndCarInfoDlg();

	CTabColorDlg*				m_color;
	CTabControlDlg*				m_control;
	CTabTaskInfoDlg*			m_task;
	CTabCarInfoDlg*				m_car;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TASK_CAR_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
