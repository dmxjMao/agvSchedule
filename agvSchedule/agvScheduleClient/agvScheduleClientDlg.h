
// agvScheduleClientDlg.h : 头文件
//

#pragma once


// CagvScheduleClientDlg 对话框
class CAgvSocket;
class CagvScheduleClientDlg : public CDialogEx
{
// 构造
public:
	CagvScheduleClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AGVSCHEDULECLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CAgvSocket*				m_pAgvSocket = NULL;

public:
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonQuit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
