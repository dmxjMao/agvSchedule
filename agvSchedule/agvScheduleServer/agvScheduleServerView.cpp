
// agvScheduleServerView.cpp : CagvScheduleServerView 类的实现
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CagvScheduleServerView

IMPLEMENT_DYNCREATE(CagvScheduleServerView, CView)

BEGIN_MESSAGE_MAP(CagvScheduleServerView, CView)
END_MESSAGE_MAP()

// CagvScheduleServerView 构造/析构

CagvScheduleServerView::CagvScheduleServerView()
{
	// TODO: 在此处添加构造代码

}

CagvScheduleServerView::~CagvScheduleServerView()
{
}

BOOL CagvScheduleServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CagvScheduleServerView 绘制

void CagvScheduleServerView::OnDraw(CDC* /*pDC*/)
{
	CagvScheduleServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//// 获取位图尺寸
	//CBitmap bmpobj;
	//bmpobj.Attach(hBitmap);

	//BITMAP bm;
	//bmpobj.GetBitmap(&bm);

	//CView* pView = GetActiveView();

	//// 改变mainframe大小
	//int cyMenu = GetSystemMetrics(SM_CYMENU);		// 菜单&状态
	//int cyCaption = GetSystemMetrics(SM_CYCAPTION); // 标题

	////MoveWindow(0, 0, bm.bmWidth + cyMenu, bm.bmHeight + 2 * cyMenu + cyCaption);
	////CenterWindow();

	////创建内存dc
	//CDC* pdc = pView->GetDC();
	//CDC hdcMem;
	//hdcMem.CreateCompatibleDC(pdc);

	//// 选入位图
	//hdcMem.SelectObject(&bmpobj);

	//// 贴图
	//pdc->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &hdcMem, 0, 0, SRCCOPY);
}


// CagvScheduleServerView 诊断

#ifdef _DEBUG
void CagvScheduleServerView::AssertValid() const
{
	CView::AssertValid();
}

void CagvScheduleServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CagvScheduleServerDoc* CagvScheduleServerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CagvScheduleServerDoc)));
	return (CagvScheduleServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CagvScheduleServerView 消息处理程序
