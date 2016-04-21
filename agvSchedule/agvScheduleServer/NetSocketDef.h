#pragma once

/*
	通信模块
	发M1 M2 M6
	收E1

*/

#include "MsgStruct.h"

class CagvScheduleServerView;
class CTaskAndCarInfoDlg;
class ICarState;

// 服务器监听套接字
class CListenSocket : public CSocket
{
public:
	CListenSocket(CagvScheduleServerView* pView, CTaskAndCarInfoDlg* pDlg);
	virtual ~CListenSocket() {}

	virtual void OnAccept(int nErrorCode);

	CObList				m_clientList;		// 连接的agv
	CCriticalSection	m_csClientList;

	CagvScheduleServerView* m_pView;
	CTaskAndCarInfoDlg*		m_pDlg;

};



// 管理与客户端的通信
class CClientSocket : public CSocket
{
public:
	Msg_E1			m_e1;				// 最近的一条E1消息
	Msg_E1			m_prevE1;			// 上一条E1消息
	CPoint			m_pt;				// 最近一条E1消息对应的小车坐标
	UINT16			m_targetPt = 0;		// 目标点
	CListenSocket*	m_pListenSocket;	// 回指监听套接字
	CagvScheduleServerView* m_pView;
	CTaskAndCarInfoDlg*		m_pDlg;
	

public:
	CClientSocket(CagvScheduleServerView* pView, 
		CListenSocket* pListenSocket, CTaskAndCarInfoDlg* pDlg);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

private:
	void getAgvXY(CClientSocket* pClient, CPoint& pt);
	void setDlgInfo();
	void ShowAGV();
	void TrafficMgn();
	ICarState* GetCarState(UINT16 state);
	void SetMsgE1(char* buf);
};