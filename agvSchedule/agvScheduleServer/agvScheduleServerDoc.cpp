
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

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CagvScheduleServerDoc

IMPLEMENT_DYNCREATE(CagvScheduleServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CagvScheduleServerDoc, CDocument)
//	ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
//ON_COMMAND(ID_FILE_OPEN, &CagvScheduleServerDoc::OnFileOpen)
END_MESSAGE_MAP()


// CagvScheduleServerDoc 构造/析构

CagvScheduleServerDoc::CagvScheduleServerDoc()
{
	// TODO: 在此添加一次性构造代码
	m_bitmap = nullptr;

}

CagvScheduleServerDoc::~CagvScheduleServerDoc()
{
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

//void CagvScheduleServerDoc::OnFileOpen()
//{
//	// TODO: 在此添加命令处理程序代码
//	// 打开对话框
//	CFileDialog fileDlg(TRUE, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		_T("place files(*.bmp)|*.bmp"));
//	
//	CString strPath;
//	if (IDOK == fileDlg.DoModal())
//		strPath = fileDlg.GetPathName();
//	else
//		return;
//	
//	// 加载位图
//	HBITMAP hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strPath,
//		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
//	
//	// 赋值成员
//	m_bitmap = hBitmap;
//}


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

	return TRUE;
}
