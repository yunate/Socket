#pragma once
#include "Thread/IThread.h"

class Dog_S_DisConnClientsThread : public IThread
{
public:
	Dog_S_DisConnClientsThread();
	~Dog_S_DisConnClientsThread();

private:
	bool m_bRun;

private:
	virtual void _Stop();
	virtual void _Run();
};