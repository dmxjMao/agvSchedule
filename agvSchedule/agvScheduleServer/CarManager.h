#pragma once

/*
	车辆管理模块（车辆状态）
	小车上报的E1
	其它小车常量、配置、计算等信息

*/
#include <vector>
#include "MsgStruct.h"

class ICar;
class CCarManager
{
private:
	std::vector<ICar*>		m_vecCar;
	Msg_E1					m_msgE1;

// attribute
// operator

};