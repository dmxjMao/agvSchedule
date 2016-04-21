#pragma once
#include "afxwin.h"

#include "MsgStruct.h"
#include "ADOConn.h"

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


private:
	BOOL Dijkstra(UINT16 src, UINT16 des); // Dijkstra求最短路径

public:
	//CScheduleDlg(CWnd* pParent = NULL);   // 标准构造函数
	CScheduleDlg(CagvScheduleServerDoc* pDoc, CWnd* pParent = NULL);

	virtual ~CScheduleDlg();

	_RecordsetPtr m_pRs;
	ADOConn m_AdoConn;

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

private:
	void SetBufm6(BYTE* buf, const Msg_M6& m6);
	void SetBufm2(BYTE* buf, const Msg_M2& m2);
	void SetBufm1(char* buf, const Msg_M1& m1);
	void SetBuf(BYTE* buf, const Msg_M6&, const Msg_M1&, const Msg_M2&);
public:
	afx_msg void OnClickedIdm2();
	afx_msg void OnClickedIdm1();
};
