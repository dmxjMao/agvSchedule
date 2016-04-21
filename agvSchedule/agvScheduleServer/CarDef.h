#pragma once

/*
	状态枚举
*/
enum CAR_STATE
{
	UNKNOWN = 0,	// 未知 AGV调度系统未能读到该小车的信息，小车未插入到系统中
	FREE,			// 空闲 车辆未被分配任务
	ASSIGNMENTED,	// 已分配 车辆已被分配任务
	LINKED,			// 已连接 一般是小车已经到达装货站台或已载货状态
	CANCELED		// 取消 小车处于急停或手动状态

	//LOADING = 0x1,  // 载货
	//OBSTACLE = 0x4,	// 检测到障碍物
	//CARERROR = 0x8,	// 报错
	//LOWPOWER = 0x10,	// 低电量
	//PLUGIN = 0x400,		// 插入系统
	//ONLINE = 0x800,		// 上线
	//SCRAM = 0x1000,		// 急停
};

/*
	小车状态基类
*/

class ICarState
{
protected:
	//BYTE		m_agvno; // 车号
	//CAR_STATE	m_state;

public:
	virtual CAR_STATE SetCurCarState() { return UNKNOWN;  }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop(){ return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};


// 继承自ICar的状态小车
// 未知
class CCarUnknown : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return UNKNOWN;  }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};



// 空闲
class CCarFree : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return FREE; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};

// 已分配
class CCarAssignmented : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return ASSIGNMENTED; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};

// 已连接
class CCarLinked : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return LINKED; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};

// 取消
class CCarCanceled : public ICarState
{
public:
	virtual CAR_STATE SetCurCarState() { return CANCELED; }
	virtual BOOL SetOnline() { return TRUE;  }
	virtual BOOL SetOffline() { return TRUE;  }
	virtual BOOL StartUp() { return TRUE;  }
	virtual BOOL Stop() { return TRUE;  }
	virtual BOOL SetAllOnline() { return TRUE;  }
};




