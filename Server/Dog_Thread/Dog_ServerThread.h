#pragma once
#include "Thread/IThread.h"

class Dog_ThreadManager;

class Dog_ServerThread : public IThread
{
private:
	Dog_ServerThread();

public:
	~Dog_ServerThread();

private:
	virtual void _Run();
	virtual void _Stop();

	friend Dog_ThreadManager;
};
