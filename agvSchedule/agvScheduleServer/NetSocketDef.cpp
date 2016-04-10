#include "stdafx.h"
#include "NetSocketDef.h"
#include "MsgStruct.h"


CListenSocket::CListenSocket()
{

}


void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClientSocket = new	CClientSocket;
	if (! Accept(*pClientSocket))
	{
		delete pClientSocket;
		pClientSocket = nullptr;
	}

	// 将连接的agv小车加入list
	m_csClientList.Lock();
	m_clientList.AddTail(pClientSocket);
	m_csClientList.Unlock();

	CSocket::OnAccept(nErrorCode);
}





void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	Msg_E1 e1;
	Receive(&e1, sizeof(e1));

	m_agvno = e1.agvno;
	m_curPointNo = e1.curPoint;

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	/*
		点击调度窗口的ok，发送M1,M2,M6消息
		请看CScheduleDlg::OnBnClickedOk()
	*/
	// 

	CAsyncSocket::OnSend(nErrorCode);
}
