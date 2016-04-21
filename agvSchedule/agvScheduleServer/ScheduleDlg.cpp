// ScheduleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "agvScheduleServer.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"

#include "Graph.h"
#include "agvScheduleServerDoc.h"
#include "NetSocketDef.h"

// 消息标签 1-255循环使用
static BYTE MSG_TAG = 0;
static UINT16 MSG_TASK = 0;

// CScheduleDlg 对话框

IMPLEMENT_DYNAMIC(CScheduleDlg, CDialogEx)

//CScheduleDlg::CScheduleDlg(CWnd* pParent /*=NULL*/)
//	: CDialogEx(IDD_DIALOG_SCHEDULE, pParent)
//{
//	m_baseGraph = new Graph();
//}

CScheduleDlg::CScheduleDlg(CagvScheduleServerDoc* pDoc, CWnd* pParent)
	: m_pDoc(pDoc), CDialogEx(IDD_DIALOG_SCHEDULE, pParent)
{
	m_baseGraph = new Graph();
}

CScheduleDlg::~CScheduleDlg()
{
}

void CScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AGCNO, m_comboAGCNo);
	DDX_Control(pDX, IDC_COMBO_OPT, m_comboOpt);
	DDX_Control(pDX, IDC_COMBO_TARGETNO, m_comboTargetNo);
}


BEGIN_MESSAGE_MAP(CScheduleDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScheduleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDM2, &CScheduleDlg::OnClickedIdm2)
	ON_BN_CLICKED(IDM1, &CScheduleDlg::OnClickedIdm1)
END_MESSAGE_MAP()


// CScheduleDlg 消息处理程序


BOOL CScheduleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	for (int i = 1; i < 11; ++i)
	{
		str.Format(_T("%d"), i);
		m_comboAGCNo.AddString(str);
	}
	m_comboAGCNo.SetCurSel(0);

	for (int i = 1; i < 201; ++i)
	{
		str.Format(_T("%d"), i);
		m_comboTargetNo.AddString(str);
	}
	m_comboTargetNo.SetCurSel(0);

	CString strOpt[] = { _T("急停"), _T("移动"), _T("装载"), _T("卸载")  };
	for (int i = 0; i < 4; ++i)
	{
		m_comboOpt.AddString(strOpt[i]);
		m_comboOpt.SetItemData(i, i);
	}
	m_comboOpt.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CScheduleDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strAGCNo, strTargetNo, strOpt;
	m_comboAGCNo.GetWindowTextW(strAGCNo);
	m_comboTargetNo.GetWindowTextW(strTargetNo);
	m_comboOpt.GetWindowTextW(strOpt);

	if (strAGCNo.IsEmpty() || strTargetNo.IsEmpty()
		|| strOpt.IsEmpty())
	{
		AfxMessageBox(_T("请输入车号，目标点号和操作！"));
		return;
	}

	// 类型转换
	BYTE agvno = _ttoi(strAGCNo);
	UINT16 targetno = _ttoi(strTargetNo);
	UINT16 opt = (UINT16)m_comboOpt.GetItemData(m_comboOpt.GetCurSel());

	if (++MSG_TAG > 255)
		MSG_TAG = 0;

	// 任务编号
	UINT16 taskno = ++MSG_TASK;

	// 还要接收E1消息，其中的M6与这条tag不一样要重发
	m_m6.tag = MSG_TAG;
	m_m6.agvno = agvno;
	m_m6.taskno = taskno;
	m_m6.target = targetno;
	
	m_m2.tag = MSG_TAG;
	m_m2.agvno = agvno;
	m_m2.taskno = taskno;
	m_m2.taskopcode = opt;

	m_m1.tag = MSG_TAG;
	m_m1.agvno = agvno;
	m_m1.taskno = taskno;
	// 段数，可行走段号 通过Dijkstra算法计算
	// 获取小车当前点号
	CObList& clientList = m_pDoc->m_pListenSocket->m_clientList;
	POSITION pos = clientList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	while (pos)
	{
		pClient = (CClientSocket*)clientList.GetNext(pos);
		if (pClient->m_e1.agvno == agvno)
			break;
	}
	
	// 计算最短路径
	if (!pClient) {
		AfxMessageBox(_T("还没用任何小车连接！"));
		return;
	}

	pClient->m_targetPt = targetno;

	Dijkstra(pClient->m_e1.curPoint, targetno);
	auto& vecRoute = m_pDoc->m_vecRoute;
	m_m1.secnum = (BYTE)vecRoute.size() - 1; // 段数
	// 可行走段
	auto& mapSideNo = m_pDoc->m_sideNo; //<段，段号>
	auto it = vecRoute.begin();
	int prevSide = *it;
	std::advance(it, 1);
	int i = 0; // 控制段索引
	CString strSideNo, strTemp; // 输出
	for (auto it2 = it; it2 != vecRoute.end(); ++it2)
	{
		unsigned sideNo = mapSideNo[make_pair(prevSide, *it2)];
		prevSide = *it2;
		memcpy_s(m_m1.secno + i, 50, (char*)&sideNo, 2);
		i += 2;
		strTemp.Format(_T("%d-"), sideNo);
		strSideNo += strTemp;
	}
	if (strSideNo.IsEmpty())
		strSideNo = _T("''");

	Msg_M1M2M6 m1m2m6;
	m1m2m6.m1 = m_m1;
	m1m2m6.m2 = m_m2;
	m1m2m6.m6 = m_m6;

	// 写入数据库
	//m_AdoConn.OnInitADOConn();
	//CTime tm = CTime::GetCurrentTime();
	//CString strTm;
	//strTm.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
	//	tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
	//CString str; //
	//str.Format(_T("%d,\'%s\',%d,%d,%d,%d,%d,%d,%d,\'%s\'"),
	//	taskno, strTm, agvno, 1, pClient->m_e1.curPoint, \
	//	targetno, MSG_TAG, opt, m_m1.secnum, strSideNo);
	//CString sql = _T("insert into tasklist (")  \
	//	_T("taskno,starttime,agvno,priority,startPt,endPt,msgtag,taskOptCode,sidenum,sideno) ")  \
	//	_T("values(") + str + _T(")");
	//m_AdoConn.ExecuteSQL((_bstr_t)sql);
	//m_AdoConn.ExitConn();

	// 给小车发送M1,M2,M6消息
	BYTE buf[11] = { 0 };
	SetBufm6(buf, m_m6);
	int sendBytes = pClient->Send(buf, 11);
	//BYTE buf[82] = { 0 }; // 11(m6) + 11(m2) + 60(m1)
	//SetBuf(buf, m_m6, m_m1, m_m2);
	//int sendBytes = pClient->Send(buf, 82);

	//while(1) {
	//	if (pClient->m_e1.m6tag == m_m6.tag) {
	//		BYTE buf[11] = { 0 };
	//		SetBufm2(buf, m_m2);
	//		sendBytes = pClient->Send(buf, 11);
	//	}	
	//}

	CDialogEx::OnOK();
}

void CScheduleDlg::OnClickedIdm2()
{
	// TODO: 在此添加控件通知处理程序代码
	CObList& clientList = m_pDoc->m_pListenSocket->m_clientList;
	POSITION pos = clientList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	while (pos)
	{
		pClient = (CClientSocket*)clientList.GetNext(pos);
	}

	if (pClient->m_e1.m6tag == m_m6.tag) {
		BYTE buf[11] = { 0 };
		SetBufm2(buf, m_m2);
		int sendBytes = pClient->Send(buf, 11);
	}	

	CDialogEx::OnOK();
}


void CScheduleDlg::OnClickedIdm1()
{
	// TODO: 在此添加控件通知处理程序代码
	CObList& clientList = m_pDoc->m_pListenSocket->m_clientList;
	POSITION pos = clientList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	while (pos)
	{
		pClient = (CClientSocket*)clientList.GetNext(pos);
	}

	if (pClient->m_e1.m2tag == m_m2.tag) {
		char buf[60] = { 0 };
		SetBufm1(buf, m_m1);
		int sendBytes = pClient->Send(buf, 60);
		int n = sendBytes;
	}

	CDialogEx::OnOK();
}


void CScheduleDlg::SetBufm6(BYTE* buf, const Msg_M6& m6)
{
	int i = 0;
	buf[i++] = m6.head[0];
	buf[i++] = m6.head[1];
	buf[i++] = m6.head[2];
	buf[i++] = m6.type[0];
	buf[i++] = m6.type[1];
	buf[i++] = m6.tag;
	buf[i++] = m6.agvno;
	memcpy_s(buf + i, 11, (BYTE*)&m6.taskno, 2);
	i += 2;
	memcpy_s(buf + i, 11, (BYTE*)&m6.target, 2);
}

void CScheduleDlg::SetBufm2(BYTE* buf, const Msg_M2& m2)
{
	int i = 0;
	buf[i++] = m2.head[0];
	buf[i++] = m2.head[1];
	buf[i++] = m2.head[2];
	buf[i++] = m2.type[0];
	buf[i++] = m2.type[1];
	buf[i++] = m2.tag;
	buf[i++] = m2.agvno;
	memcpy_s(buf + i, 11, (BYTE*)&m2.taskno, 2);
	i += 2;
	memcpy_s(buf + i, 11, (BYTE*)&m2.taskopcode, 2);
}

void CScheduleDlg::SetBufm1(char* buf, const Msg_M1& m1)
{
	int i = 0;
	buf[i++] = m1.head[0];
	buf[i++] = m1.head[1];
	buf[i++] = m1.head[2];
	buf[i++] = m1.type[0];
	buf[i++] = m1.type[1];
	buf[i++] = m1.tag;
	buf[i++] = m1.agvno;

	memcpy_s(buf + i, 60, (BYTE*)&m1.taskno, 2);
	i += 2;
	buf[i++] = m1.secnum;
	char* pSecno = (char*)&m1.secno;
	while (i < 58) {
		memcpy_s(buf + i, 82, pSecno, 2);
		pSecno += 2;
		i += 2;
	}
}

void CScheduleDlg::SetBuf(BYTE* buf, const Msg_M6& m6, const Msg_M1& m1, const Msg_M2& m2)
{
	int im6(11), im2(22);
	int i = 0;
	buf[i++] = m6.head[0];
	buf[i++] = m6.head[1];
	buf[i++] = m6.head[2];
	buf[i++] = m6.type[0];
	buf[i++] = m6.type[1];
	buf[i++] = m6.tag;
	buf[i++] = m6.agvno;
	memcpy_s(buf + i, 82, (BYTE*)&m6.taskno, 2);
	i += 2;
	memcpy_s(buf + i, 82, (BYTE*)&m6.target, 2);

	i = 0;
	buf[i++ + im6] = m2.head[0];
	buf[i++ + im6] = m2.head[1];
	buf[i++ + im6] = m2.head[2];
	buf[i++ + im6] = m2.type[0];
	buf[i++ + im6] = m2.type[1];
	buf[i++ + im6] = m2.tag;
	buf[i++ + im6] = m2.agvno;
	memcpy_s(buf + i + im6, 82, (BYTE*)&m2.taskno, 2);
	i += 2;
	memcpy_s(buf + i + im6, 82, (BYTE*)&m2.taskopcode, 2);

	i = 0;
	buf[i++ + im2] = m1.head[0];
	buf[i++ + im2] = m1.head[1];
	buf[i++ + im2] = m1.head[2];
	buf[i++ + im2] = m1.type[0];
	buf[i++ + im2] = m1.type[1];
	buf[i++ + im2] = m1.tag;
	buf[i++ + im2] = m1.agvno;
	memcpy_s(buf + i + im2, 82, (BYTE*)&m1.taskno, 2);
	i += 2;
	buf[i++ + im2] = m1.secnum;
	BYTE* pSecno = (BYTE*)&m1.secno;
	while (i < 58) {
		memcpy_s(buf + i + im2, 82, pSecno, 2);
		pSecno += 2;
		i += 2;
	}
	//for (int j = 0; j < 50; j += 2) {
	//	memcpy_s(buf + i + im2, 82, (BYTE*)&(m1.secno + j), 2);
	//	i += 2;
	//}
}


BOOL CScheduleDlg::Dijkstra(UINT16 src, UINT16 des)
{
	Vertex te;
	list<Vertex> newList;

	// 生成段号
	static bool bGen = true;
	if (bGen) {
		m_baseGraph->generateSideNo();
		bGen = false;
	}

	te.vertexNo = src;
	m_baseGraph->UnweightedGraph(&te);

	memset(&te, 0, sizeof(Vertex));
	te.vertexNo = des;
	m_baseGraph->printPath(&te);
	//TRACE("Target(%d)\n", TARGET_VERTEX);
	m_baseGraph->GetRoute().push_back(des);
	m_baseGraph->ResetVertex(); // 重置关系，解决只能2-3，不能3-2的问题

	// 传递到doc中去
	m_pDoc->m_vecRoute = std::move(m_baseGraph->GetRoute());
	m_pDoc->m_sideNo = std::move(m_baseGraph->GetSideNoMap());

	return TRUE;
}



