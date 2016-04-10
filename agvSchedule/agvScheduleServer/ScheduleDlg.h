#pragma once
#include "afxwin.h"

#include "MsgStruct.h"

// CScheduleDlg 对话框

class Graph;
class CagvScheduleServerDoc;
class CScheduleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScheduleDlg)

private:
	Msg_M1				m_m1;
	Msg_M2				m_m2;
	Msg_M6				m_m6;

	Graph *				m_baseGraph;
	CagvScheduleServerDoc* m_pDoc;

	// 因为socket信息都保存在doc中，所以回指mainfreme


private:
	BOOL Dijkstra(UINT16 src, UINT16 des); // Dijkstra求最短路径

public:
	//CScheduleDlg(CWnd* pParent = NULL);   // 标准构造函数
	CScheduleDlg(CagvScheduleServerDoc* pDoc, CWnd* pParent = NULL);

	virtual ~CScheduleDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCHEDULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboAGCNo;
	CComboBox m_comboOpt;
	CComboBox m_comboTargetNo;
	afx_msg void OnBnClickedOk();
};
