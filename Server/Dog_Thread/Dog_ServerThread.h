#pragma once
#include "Dog_Server.h"
#include "Dog_Thread_Base.hpp"

class Dog_ThreadManager;

class Dog_ServerThread : public Dog_Thread_Base
{
private:
	Dog_ServerThread(int nPort);

public:
	~Dog_ServerThread();

private:
	Dog_Server*			m_pServer;

public:
	virtual void InitDes();

private:
	virtual void _Run();

	friend Dog_ThreadManager;
};
