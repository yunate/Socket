#pragma once
#include "Thread/IThread.h"

// Dog_S_Client �ַ��߳�
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