#pragma once


class CAgvSocket : public CSocket
{

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};