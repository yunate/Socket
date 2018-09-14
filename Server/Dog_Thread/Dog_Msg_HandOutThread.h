#pragma once
#include "Dog_Thread_Base.hpp"
#include "Dog_Thread/Dog_ThreadManager.h"

// msg 分发线程
class Dog_Msg_HandOutThread : public Dog_Thread_Base
{
public:
	Dog_Msg_HandOutThread();
	~Dog_Msg_HandOutThread();

	// 电脑的硬件资源是否足够在创建一条线程了
	bool				IsCptHardSrcEnough();
	void				Init();
	void				UnInit();

private:
	size_t				GetAvaiableId(Dog_ThreadManager::ThreadList&);

public:
	virtual void		InitDes();

private:
	virtual void		_Run();
	virtual bool		_Dog_Stop_After();
};