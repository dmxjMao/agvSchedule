#pragma once

/*
M6: 任务目标点
21 08 41 (21 41 开始结束 08 包体长度)
4D 36 (4D 36表示本消息是M6消息)
01 (消息标签1-255循环利用)
01 (AGC车号)
01 00 (任务编号上位机指定2字节)
06 00 (任务目标点2字节)
共8字节 + 3 = 11
*/
struct Msg_M6
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };		// 包头
	const BYTE type[2] = { 0x4D, 0x36 };			// 消息类型
	BYTE tag = 0;					// 消息标签
	BYTE agvno = 0;					// AGV车号
	UINT16 taskno = 0;				// 任务编号
	UINT16 target = 0;				// 任务目标点

	Msg_M6& operator=(const Msg_M6& m6) {
		tag = m6.tag;
		agvno = m6.agvno;
		taskno = m6.taskno;
		target = m6.target;
		return *this;
	}
};


/*
M2: 任务操作码
21 08 41
4D 32(M2)
01(消息标签1-255)
01(AGC车号)
01 00(任务编号与下位机缓存的M6编号一致)
90 01(任务操作码)
8 + 3 = 11
*/
struct Msg_M2
{
	const BYTE head[3] = { 0x21, 0x08, 0x41 };
	const BYTE type[2] = { 0x4D, 0x32 };
	BYTE tag = 0;
	BYTE agvno = 0;
	UINT16 taskno = 0;
	UINT16 taskopcode = 0;			// 任务操作码

	Msg_M2& operator=(const Msg_M2& m2) {
		tag = m2.tag;
		agvno = m2.agvno;
		taskno = m2.taskno;
		taskopcode = m2.taskopcode;
		return *this;
	}
};


/*
M1: 移动路径
21(包头开始标志)10(包体长度) 41(包头结束标志)
4D 31(M1)
01(消息标签1-255)
01(AGC车号)
01 00(任务编号与下位机缓存的M6编号一致)
01(段数目1-25)
00 02(可行走段号,2B一段)
00 03 00 04 00 05 00   原则上不会操作57字节(0x39)，即段数不会超过25
57 + 3 = 60
*/
struct Msg_M1
{
	const BYTE head[3] = { 0x21, 0x39, 0x41 };
	const BYTE type[2] = { 0x4D, 0x31 };
	BYTE tag = 0;
	BYTE agvno = 0;
	UINT16 taskno = 0;
	BYTE secnum = 0;			// 段的数目
	char secno[50] = { 0 };		// F的段号问题

	Msg_M1& operator=(const Msg_M1& m1) {
		tag = m1.tag;
		agvno = m1.agvno;
		taskno = m1.taskno;
		secnum = m1.secnum;
		memcpy_s(secno, 50, m1.secno, 50);
		return *this;
	}
};



/*
E1: agv上报 200ms
45 31
01 车号
01 M1消息标签
01 M2消息标签
01 M6消息标签
00 01 当前所走段距离(mm)
00 01 当前段号
00 01 当前点号
00 01 agc状态位
01 agc错误码
01 预留
00 01 当前速度mm/s
01 移动完成&操作完成
00 01 当前任务号
共21字节 + 包头 = 24字节
*/
struct Msg_E1
{
	const BYTE head[3] = { 0x21, 0x15, 0x41 };
	const BYTE type[2] = { 0x45, 0x31 };
	BYTE agvno = 0;
	BYTE m1tag = 0;
	BYTE m2tag = 0;
	BYTE m6tag = 0;
	UINT16 curDist = 0;
	UINT16 curSec = 0;
	UINT16 curPoint = 0;
	UINT16 agcStatus = 0;
	BYTE agcError = 0;
	BYTE reserve = 0;
	UINT16 curSpeed = 0;
	BYTE moveOrOpt = 0;
	UINT16 curTask = 0;

	Msg_E1& operator=(const Msg_E1& e1) {
		agvno = e1.agvno;
		m1tag = e1.m1tag;
		m2tag = e1.m2tag;
		m6tag = e1.m6tag;
		curDist = e1.curDist;
		curSec = e1.curSec;
		curPoint = e1.curPoint;
		agcStatus = e1.agcStatus;
		agcError = e1.agcError;
		reserve = e1.reserve;
		curSpeed = e1.curSpeed;
		moveOrOpt = e1.moveOrOpt;
		curTask = e1.curTask;
		return *this;
	}
};

//struct Msg_E1 {
//	union {
//		unsigned char b[24];
//		struct e1 {
//			unsigned char H45;
//			unsigned char H31;
//			unsigned char AGC_No;
//			unsigned char m1_msg_tag;
//			unsigned char m2_msg_tag;
//			unsigned char m6_msg_tag;
//			unsigned short currectn_dist_section;
//			unsigned short current_section;
//			unsigned short current_spot;
//			unsigned short acg_flag;
//			unsigned char errno;
//			unsigned char voltage;
//			unsigned short speed;
//			unsigned char move_op_done;
//			unsigned short task;
//		};
//	};
//};



struct Msg_M1M2M6
{
	Msg_M1 m1;
	Msg_M2 m2;
	Msg_M6 m6;
};