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
	Dijkstra(pClient->m_e1.curPoint, targetno);
	auto& vecRoute = m_pDoc->m_vecRoute;
	m_m1.secnum = (BYTE)vecRoute.size() - 1; // 段数
	// 可行走段
	auto& mapSideNo = m_pDoc->m_sideNo; //<段，段号>
	auto it = vecRoute.begin();
	int prevSide = *it;
	std::advance(it, 1);
	int i = 0; // 控制段索引
	for (auto it2 = it; it2 != vecRoute.end(); ++it2)
	{
		unsigned sideNo = mapSideNo[make_pair(prevSide, *it2)];
		prevSide = *it2;
		m_m1.secno[i++] = sideNo;
	}

	Msg_M1M2M6 m1m2m6;
	m1m2m6.m1 = m_m1;
	m1m2m6.m2 = m_m2;
	m1m2m6.m6 = m_m6;

	// 给小车发送M1,M2,M6消息
	pClient->Send(&m1m2m6, sizeof(m1m2m6));

	CDialogEx::OnOK();
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