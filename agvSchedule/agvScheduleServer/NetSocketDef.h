#pragma once

#include "MsgStruct.h"

class CagvScheduleServerView;
// 服务器监听套接字
class CListenSocket : public CSocket
{
public:
	CListenSocket(CagvScheduleServerView* pView);
	virtual ~CListenSocket() {}

	virtual void OnAccept(int nErrorCode);

	CObList				m_clientList;		// 连接的agv
	CCriticalSection	m_csClientList;

	CagvScheduleServerView* m_pView;
};



// 管理与客户端的通信
class CClientSocket : public CSocket
{
public:
	Msg_E1			m_e1;				// 最近的一条E1消息
	CListenSocket*	m_pListenSocket;	// 回值监听套接字
	CagvScheduleServerView* m_pView;

public:
	CClientSocket(CagvScheduleServerView* pView, CListenSocket* pListenSocket);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

private:
	void getAgvXY(const Msg_E1& e1, CPoint& pt);
};