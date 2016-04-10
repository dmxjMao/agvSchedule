#pragma once

// 服务器监听套接字
class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket() {}

	virtual void OnAccept(int nErrorCode);

	CObList				m_clientList;		// 连接的agv
	CCriticalSection	m_csClientList;
};



// 管理与客户端的通信
class CClientSocket : public CAsyncSocket
{
public:
	UINT16				m_curPointNo = 0;	// 小车当前所在点号
	BYTE				m_agvno = 0;		// 小车车号

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};