#pragma once


// CTabColorDlg 对话框

class CTabColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabColorDlg)

public:
	CTabColorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabColorDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
