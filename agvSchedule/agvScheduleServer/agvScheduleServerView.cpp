
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
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
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

void CagvScheduleServerView::OnDraw(CDC* pDC)
{
	CagvScheduleServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	static RECT rcClient;
	GetClientRect(&rcClient);

	HBITMAP& hBitmap = pDoc->GetBitmap();
	if (hBitmap)
	{
		// 获取位图尺寸
		CBitmap bmpobj;
		bmpobj.Attach(hBitmap);

		BITMAP bm;
		bmpobj.GetBitmap(&bm);

		//创建内存dc
		CDC hdcMem/*, memdc2*/;
		hdcMem.CreateCompatibleDC(pDC);

		// 选入位图
		hdcMem.SelectObject(&bmpobj);
		
		// 贴图
		pDC->StretchBlt(0, 0, rcClient.right, rcClient.bottom, 
			&hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		bmpobj.Detach();
	}
	
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


void CagvScheduleServerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	auto pDoc = GetDocument();
	if (EDIT_SET == pDoc->GetEditPushStatus())
	{
		++m_uCurNum;
		// 保存点的坐标
		pDoc->m_mapPoint[m_uCurNum] = point;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CagvScheduleServerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	auto pDoc = GetDocument();
	if (EDIT_SET == pDoc->GetEditPushStatus())
	{
		if (pDoc->m_mapPoint.IsEmpty()) {
			m_uCurNum = 0;
			return;
		}

		pDoc->m_mapPoint.RemoveKey(unsigned(pDoc->m_mapPoint.GetCount()));
		--m_uCurNum;
	}

	CView::OnRButtonDown(nFlags, point);
}


void CagvScheduleServerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	auto pDoc = GetDocument();
	if (EDIT_SET == pDoc->GetEditPushStatus())
	{
		CDC* pDC = GetDC();
		CDC memdc1, memdc2;
		memdc1.CreateCompatibleDC(pDC);
		memdc2.CreateCompatibleDC(pDC);

		// 获取区域大小
		RECT rc;
		GetClientRect(&rc);

		CBitmap bitmapSrc, bitmap2;
		bitmapSrc.Attach(pDoc->GetBitmap());
		bitmap2.CreateCompatibleBitmap(pDC, rc.right, rc.bottom);

		memdc1.SelectObject(&bitmap2);	// 画布大小是客户区大小
		memdc2.SelectObject(&bitmapSrc);

		BITMAP bm;
		bitmapSrc.GetBitmap(&bm);

		// 在memedc1上画图，相当于在客户区上画
		memdc1.StretchBlt(0, 0, rc.right, rc.bottom,
			&memdc2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

		// 显示数字
		POSITION pos = pDoc->m_mapPoint.GetStartPosition();
		unsigned key;
		CPoint pt;
		CString strMsg;
		//memdc1.SetBkMode(TRANSPARENT);
		while (pos)
		{
			pDoc->m_mapPoint.GetNextAssoc(pos, key, pt);
			strMsg.Format(_T("%d"), key);
			memdc1.TextOutW(pt.x, pt.y, strMsg);
		}

		pDC->StretchBlt(0, 0, rc.right, rc.bottom,
			&memdc1, 0, 0, rc.right, rc.bottom, SRCCOPY);

		bitmapSrc.Detach();
	}

	CView::OnMouseMove(nFlags, point);
}
