// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{

}

ADOConn::~ADOConn()
{

}

void ADOConn::OnInitADOConn()//连接数据库
{
	
	try
	{
		m_pCon.CreateInstance("ADODB.Connection");
		m_pCon->ConnectionTimeout=3;//连接尝试时间
		//连接Access数据库
		m_pCon->Open("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=agvSchedule.accdb",
			"","", adModeUnknown);
		//m_pCon->Open("Driver=(Microsoft Access Driver (*.mdb,*.accdb));"
		//	"Data Source=H:\agvSchedule.accdb;",
		//		"","", adModeUnknown);
	}
	catch(_com_error e)//捕捉异常
	{
		AfxMessageBox(e.Description());
	}
}

void ADOConn::ExitConn()//断开连接
{
	if(m_pRs!=NULL)
		m_pRs->Close();
	m_pCon->Close();
	
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)//执行SQL查询语句
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();
		m_pRs.CreateInstance("ADODB.Recordset");//创建记录集
		m_pRs->Open(bstrSQL,m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)//捕捉异常
	{
		AfxMessageBox(e.Description());
	}
	return m_pRs;//返回结果集
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)//执行SQL操作语句
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();//连接数据库
		m_pCon->Execute(bstrSQL,NULL,adCmdText);//执行SQL
		return true;
	}
	catch(_com_error e)//捕捉异常
	{
		AfxMessageBox(e.Description());
		return false;
	}
}
