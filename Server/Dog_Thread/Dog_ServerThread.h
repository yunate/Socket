#pragma once
#include "Dog_Server.h"
#include "Dog_Thread_Base.hpp"

class Dog_ThreadManager;

class Dog_ServerThread : public Dog_Thread_Base
{
private:
	Dog_ServerThread(int nPort);

public:
	virtual ~Dog_ServerThread();

private:
	Dog_Server*			m_pServer;

public:
	virtual void InitDes();

private:
	virtual void _Run();
	virtual bool _Dog_Stop();

	friend Dog_ThreadManager;
};
