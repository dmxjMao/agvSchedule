
// agvScheduleServerDoc.h : CagvScheduleServerDoc 类的接口
//


#pragma once


/* 菜单更新：
初始0；
1为点击了导入坐标
2为点击了设置坐标
*/
enum EDIT_PUSH_STATUS{
	EDIT_DEFAULT = 0,
	EDIT_IMPORT,
	EDIT_SET
};


class CListenSocket;
class CagvScheduleServerDoc : public CDocument
{
// 成员
private:
	HBITMAP				m_bitmap;
	EDIT_PUSH_STATUS	m_uEditPushStatus = EDIT_DEFAULT;
	
public:
	CMap<unsigned, unsigned, CPoint, CPoint> m_mapPoint;	// (点号，坐标)的映射
	CListenSocket*		m_pListenSocket;

// 操作
public:
	inline HBITMAP& GetBitmap() { return m_bitmap; }
	inline UINT8 GetEditPushStatus() const { return m_uEditPushStatus;  }

private:
	

protected: // 仅从序列化创建
	CagvScheduleServerDoc();
	DECLARE_DYNCREATE(CagvScheduleServerDoc)

// 特性
public:


// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CagvScheduleServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnUpdateFileStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditSetxy(CCmdUI *pCmdUI);
	afx_msg void OnEditSetxy();
	afx_msg void OnEditImportxy();
	afx_msg void OnUpdateEditImportxy(CCmdUI *pCmdUI);
	afx_msg void OnEditResetxy();
	afx_msg void OnUpdateEditResetxy(CCmdUI *pCmdUI);
	afx_msg void OnEditExport();
	afx_msg void OnUpdateEditExport(CCmdUI *pCmdUI);
	afx_msg void OnFileStart();
	afx_msg void OnWindowSchedule();
};
