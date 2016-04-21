#pragma once

/*
	交通管理模块（车辆运作）
	小车上/下线
	全部上/下线
	启动，停止
	状态模式

*/


#include <map>

class ICarState;
enum CAR_STATE;
class CTrafficManager
{
private:

public:
	void SetCurCar(BYTE carno);
	void SetCurCarState();
	
// all user operator
	BOOL SetOnline();	// 小车上线
	BOOL SetOffline();  // 小车下线
	BOOL StartUp();		// 小车启动
	BOOL Stop();		// 小车停止
	BOOL SetAllOnline();// 全部上线
	
	std::map<BYTE, ICarState*>		m_mapCarState;  // 不同小车的当前状态
	BYTE		m_curCarno;	// 当前小车
	CAR_STATE   m_curState; // 当前小车状态

};