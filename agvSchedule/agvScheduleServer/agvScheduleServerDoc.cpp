
// agvScheduleServerDoc.cpp : CagvScheduleServerDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "agvScheduleServer.h"
#endif

#include "agvScheduleServerDoc.h"
#include "agvScheduleServerView.h"
#include "MainFrm.h"

#include "NetSocketDef.h"
#include "ScheduleDlg.h"
#include "TaskList.h"
#include "CarListDlg.h"
#include "LogDlg.h"
#include "ErrorDlg.h"
#include "TaskAndCarInfoDlg.h"

#include "TrafficManager.h"
#include "CarManager.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CagvScheduleServerDoc

IMPLEMENT_DYNCREATE(CagvScheduleServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CagvScheduleServerDoc, CDocument)
//	ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
//ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
//ON_UPDATE_COMMAND_UI(ID_FILE_SETXY, &CagvScheduleServerDoc::OnUpdateFileSetxy)
ON_UPDATE_COMMAND_UI(ID_FILE_START, &CagvScheduleServerDoc::OnUpdateFileStart)
//ON_COMMAND(ID_FILE_SETXY, &CagvScheduleServerDoc::OnFileSetxy)
ON_UPDATE_COMMAND_UI(ID_EDIT_SETXY, &CagvScheduleServerDoc::OnUpdateEditSetxy)
ON_COMMAND(ID_EDIT_SETXY, &CagvScheduleServerDoc::OnEditSetxy)
ON_COMMAND(ID_EDIT_IMPORTXY, &CagvScheduleServerDoc::OnEditImportxy)
ON_UPDATE_COMMAND_UI(ID_EDIT_IMPORTXY, &CagvScheduleServerDoc::OnUpdateEditImportxy)
ON_COMMAND(ID_EDIT_RESETXY, &CagvScheduleServerDoc::OnEditResetxy)
ON_UPDATE_COMMAND_UI(ID_EDIT_RESETXY, &CagvScheduleServerDoc::OnUpdateEditResetxy)
ON_COMMAND(ID_EDIT_EXPORT, &CagvScheduleServerDoc::OnEditExport)
ON_UPDATE_COMMAND_UI(ID_EDIT_EXPORT, &CagvScheduleServerDoc::OnUpdateEditExport)
ON_COMMAND(ID_FILE_START, &CagvScheduleServerDoc::OnFileStart)
ON_COMMAND(ID_WINDOW_SCHEDULE, &CagvScheduleServerDoc::OnWindowSchedule)
ON_UPDATE_COMMAND_UI(ID_WINDOW_SCHEDULE, &CagvScheduleServerDoc::OnUpdateWindowSchedule)
ON_COMMAND(ID_WINDOW_TASKLIST, &CagvScheduleServerDoc::OnWindowTasklist)
ON_COMMAND(ID_WINDOW_CARLIST, &CagvScheduleServerDoc::OnWindowCarlist)
ON_COMMAND(ID_WINDOW_LOG, &CagvScheduleServerDoc::OnWindowLog)
ON_COMMAND(ID_WINDOW_ERROR, &CagvScheduleServerDoc::OnWindowError)
ON_COMMAND(ID_WINDOW_TASK_CAR, &CagvScheduleServerDoc::OnWindowTaskCar)
END_MESSAGE_MAP()


// CagvScheduleServerDoc 构造/析构

CagvScheduleServerDoc::CagvScheduleServerDoc()
{
	// TODO: 在此添加一次性构造代码
	m_bitmap = nullptr;
	m_pListenSocket = nullptr;
	m_pDlg = nullptr;
	m_pScheDlg = nullptr;
}

CagvScheduleServerDoc::~CagvScheduleServerDoc()
{
	if (m_pTrafficMgn) {
		delete m_pTrafficMgn; m_pTrafficMgn = nullptr;
	}
	if (m_pCarMgn) {
		delete m_pCarMgn; m_pCarMgn = nullptr;
	}
}

BOOL CagvScheduleServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CagvScheduleServerDoc 序列化

void CagvScheduleServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CagvScheduleServerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CagvScheduleServerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CagvScheduleServerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CagvScheduleServerDoc 诊断

#ifdef _DEBUG
void CagvScheduleServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CagvScheduleServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CagvScheduleServerDoc 命令


BOOL CagvScheduleServerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	// 加载位图
	HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), lpszPathName,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		
	// 赋值成员
	m_bitmap = hBitmap;

	if (!m_pDlg) {
		m_pDlg = new CTaskAndCarInfoDlg;
		m_pDlg->Create(IDD_DIALOG_TASK_CAR_INFO, AfxGetApp()->GetMainWnd());
		m_pDlg->ShowWindow(SW_SHOW);
		m_pDlg->CenterWindow();
	}
	else {
		m_pDlg->ShowWindow(SW_SHOW);
	}

	m_pTrafficMgn = new CTrafficManager;
	m_pCarMgn = new CCarManager;

	return TRUE;
}



void CagvScheduleServerDoc::OnUpdateFileStart(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (EDIT_IMPORT == m_uEditPushStatus 
		|| EDIT_SET == m_uEditPushStatus)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(0);

	if (m_bitmap)
		pCmdUI->Enable();
}



void CagvScheduleServerDoc::OnUpdateEditSetxy(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_bitmap)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(0);

	if (EDIT_IMPORT == m_uEditPushStatus)
		pCmdUI->Enable(0);
}


void CagvScheduleServerDoc::OnEditSetxy()
{
	// TODO: 在此添加命令处理程序代码
	m_uEditPushStatus = EDIT_SET;
}


void CagvScheduleServerDoc::OnEditImportxy()
{
	// TODO: 在此添加命令处理程序代码
	m_uEditPushStatus = EDIT_IMPORT; // 点击了导入坐标

	CFileDialog dlg(TRUE, _T(".txt"), 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("TXT Files(*.txt)|*.txt||"));
	if (IDOK == dlg.DoModal())
	{
		CString strPath = dlg.GetPathName();
		CStdioFile file(strPath,  CFile::modeRead);
		m_mapPoint.RemoveAll();

		// 点号 （坐标）->  2\t233,37
		CString strLine, strNo, strPtX, strPtY;
		while (file.ReadString(strLine))
		{
			int pos1 = strLine.Find(_T("\t"));
			strNo = strLine.Left(pos1);
			int pos2 = strLine.Find(_T(","));
			strPtX = strLine.Mid(pos1 + 1, pos2 - pos1);
			strPtY = strLine.Mid(pos2 + 1, strLine.GetLength() - pos2);

			m_mapPoint[_ttoi(strNo)] = CPoint(_ttoi(strPtX), _ttoi(strPtY));
		}

		//TCHAR szExePath[MAX_PATH];
		//GetModuleFileName(nullptr, szExePath, MAX_PATH);
		//CString str(szExePath);
		//int strPos = str.ReverseFind(_T('\\'));
		//str.Truncate(strPos);
		//str += _T("\\导入的点号&坐标.txt");

		//CStdioFile file1(str,
		//	CFile::modeWrite | CFile::modeCreate /*| CFile::typeText*/);
		//POSITION pos = m_mapPoint.GetStartPosition();
		//unsigned key;
		//CPoint pt;
		//CString str1;
		//while (pos)
		//{
		//	m_mapPoint.GetNextAssoc(pos, key, pt);
		//	str1.Format(_T("%d\t%d,%d\n"), key, pt.x, pt.y);
		//	file1.WriteString(str1);
		//}

	}
}


void CagvScheduleServerDoc::OnUpdateEditImportxy(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_bitmap)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(0);
	
}


void CagvScheduleServerDoc::OnEditResetxy()
{
	// TODO: 在此添加命令处理程序代码
	m_mapPoint.RemoveAll();
	POSITION pos = GetFirstViewPosition();
	CagvScheduleServerView* pView = (CagvScheduleServerView*)GetNextView(pos);
	pView->m_uCurNum = 0;
}


void CagvScheduleServerDoc::OnUpdateEditResetxy(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_mapPoint.IsEmpty())
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable();

	if (1 == m_uEditPushStatus)
		pCmdUI->Enable(0);
}


void CagvScheduleServerDoc::OnEditExport()
{
	// TODO: 在此添加命令处理程序代码
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(nullptr, szExePath, MAX_PATH);
	CString str(szExePath);
	int strPos = str.ReverseFind(_T('\\'));
	str.Truncate(strPos);
	str += _T("\\点号&坐标.txt");

	CStdioFile file(str,
		CFile::modeWrite | CFile::modeCreate /*| CFile::typeText*/);

	POSITION pos = m_mapPoint.GetStartPosition();
	unsigned key;
	CPoint pt;
	//file.WriteString(_T("点号\t坐标\n"));
	while (pos)
	{
		m_mapPoint.GetNextAssoc(pos, key, pt);
		str.Format(_T("%d\t%d,%d\n"), key, pt.x, pt.y);
		file.WriteString(str);
	}

	file.Close();
	m_mapPoint.RemoveAll();
	m_uEditPushStatus = EDIT_DEFAULT;
	return;
}


void CagvScheduleServerDoc::OnUpdateEditExport(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_mapPoint.IsEmpty())
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable();
}


void CagvScheduleServerDoc::OnFileStart()
{
	// TODO: 在此添加命令处理程序代码
	AfxSocketInit();

	// 赋值view DC
	POSITION pos = GetFirstViewPosition();
	CagvScheduleServerView* pView = (CagvScheduleServerView*)GetNextView(pos);

	m_pListenSocket = new CListenSocket(pView, m_pDlg);
	//创建套接字
	if (m_pListenSocket->Create(SVR_PORT))
	{
		//开始监听
		if (!m_pListenSocket->Listen(100))
		{
			delete m_pListenSocket;
			m_pListenSocket = NULL;
			AfxMessageBox(_T("监听套接字失败！"));
			return;
		}
	}else
	{
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		AfxMessageBox(_T("创建监听套接字失败！"));
		return;
	}

}


void CagvScheduleServerDoc::OnWindowSchedule()
{
	// TODO: 在此添加命令处理程序代码
	//CScheduleDlg dlg(this);
	//if (IDOK == dlg.DoModal())
	//{
	//	
	//}
	if (!m_pScheDlg) {
		m_pScheDlg = new CScheduleDlg(this);
		m_pScheDlg->Create(IDD_DIALOG_SCHEDULE, AfxGetApp()->GetMainWnd());
		m_pScheDlg->ShowWindow(SW_SHOW);
		m_pScheDlg->CenterWindow();
	}
	else {
		m_pScheDlg->ShowWindow(SW_SHOW);
	}
}


void CagvScheduleServerDoc::OnUpdateWindowSchedule(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!m_pListenSocket)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);
}


void CagvScheduleServerDoc::OnWindowTasklist()
{
	// TODO: 在此添加命令处理程序代码
	CTaskList tasklist;
	tasklist.DoModal();
}


void CagvScheduleServerDoc::OnWindowCarlist()
{
	// TODO: 在此添加命令处理程序代码
	CCarListDlg carlist;
	carlist.DoModal();
}


void CagvScheduleServerDoc::OnWindowLog()
{
	// TODO: 在此添加命令处理程序代码
	CLogDlg logdlg;
	logdlg.DoModal();
}


void CagvScheduleServerDoc::OnWindowError()
{
	// TODO: 在此添加命令处理程序代码
	CErrorDlg errdlg;
	errdlg.DoModal();
}


void CagvScheduleServerDoc::OnWindowTaskCar()
{
	// TODO: 在此添加命令处理程序代码
	//CTaskAndCarInfoDlg dlg;
	//dlg.DoModal();

	if (!m_pDlg) {
		m_pDlg = new CTaskAndCarInfoDlg;
		m_pDlg->Create(IDD_DIALOG_TASK_CAR_INFO, AfxGetApp()->GetMainWnd());
		m_pDlg->ShowWindow(SW_SHOW);
		m_pDlg->CenterWindow();
	}
	else {
		m_pDlg->ShowWindow(SW_SHOW);
	}
}

