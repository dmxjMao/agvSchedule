#include "stdafx.h"
#include "NetSocketDef.h"
#include "MsgStruct.h"


void CAgvSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_bRecv = true;

	Msg_M1M2M6 m1m2m6;
	int recvBytes = Receive(&m1m2m6, sizeof(m1m2m6));
	
	m_target = m1m2m6.m6.target;

	CSocket::OnReceive(nErrorCode);
}


void CAgvSocket::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnSend(nErrorCode);
}
