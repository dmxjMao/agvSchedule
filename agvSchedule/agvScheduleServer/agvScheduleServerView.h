
// agvScheduleServerView.h : CagvScheduleServerView 类的接口
//

#pragma once


class CagvScheduleServerView : public CView
{
// 数据
public:
	unsigned		m_uCurNum = 0;					// 当前点号

protected: // 仅从序列化创建
	CagvScheduleServerView();
	DECLARE_DYNCREATE(CagvScheduleServerView)

// 特性
public:
	CagvScheduleServerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CagvScheduleServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // agvScheduleServerView.cpp 中的调试版本
inline CagvScheduleServerDoc* CagvScheduleServerView::GetDocument() const
   { return reinterpret_cast<CagvScheduleServerDoc*>(m_pDocument); }
#endif

