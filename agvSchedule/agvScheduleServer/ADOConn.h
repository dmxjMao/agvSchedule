// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


class ADOConn  
{
public:
	BOOL ExecuteSQL(_bstr_t bstrSQL);//执行SQL语句
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);//
	void ExitConn();//断开连接
	void OnInitADOConn();//连接数据库
	ADOConn();
	virtual ~ADOConn();
	_ConnectionPtr m_pCon;//_ConnectionPtr对象
	_RecordsetPtr m_pRs;//_RecordsetPtr对象

};

