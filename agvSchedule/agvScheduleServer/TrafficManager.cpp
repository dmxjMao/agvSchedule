#include "stdafx.h"
#include "TrafficManager.h"
#include "CarDef.h"

void CTrafficManager::SetCurCar(BYTE carno)
{
	m_curCarno = carno;
}

void CTrafficManager::SetCurCarState()
{
	m_curState = m_mapCarState[m_curCarno]->SetCurCarState();
}


BOOL CTrafficManager::SetOnline()
{
	m_mapCarState[m_curCarno]->SetOnline();
	return(TRUE);
}


BOOL CTrafficManager::SetOffline()
{
	return(TRUE);
}


BOOL CTrafficManager::StartUp()
{
	return(TRUE);
}


BOOL CTrafficManager::Stop()
{
	return(TRUE);
}


BOOL CTrafficManager::SetAllOnline()
{
	return(TRUE);
}

