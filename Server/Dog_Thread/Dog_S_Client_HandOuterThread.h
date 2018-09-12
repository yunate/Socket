#pragma once
#include "Dog_Thread_Base.hpp"

// Dog_S_Client 分发线程
class Dog_S_Client_HandOuterThread : public Dog_Thread_Base
{
public:
	Dog_S_Client_HandOuterThread();
	~Dog_S_Client_HandOuterThread();

	void Init();
	void UnInit();


public:
	virtual void InitDes();

private:
	virtual void _Run();
	virtual bool _Dog_Stop();
};