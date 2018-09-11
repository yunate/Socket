#pragma once
#include "Thread/IThread.h"

// Dog_S_Client 分发线程
class Dog_S_Client_HandOuterThread : public IThread
{
public:
	Dog_S_Client_HandOuterThread();
	~Dog_S_Client_HandOuterThread();

	void Init();
	void UnInit();

private:
	bool m_bRun;

private:
	virtual void _Stop();
	virtual void _Run();
};