#pragma once


class CAgvSocket : public CSocket
{
public:
	UINT16				m_target = 0;		// 小车目标点号
	UINT16				m_curPointNo = 0;	// 小车当前点号

	bool				m_bRecv = false;	// 接收到指令

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};