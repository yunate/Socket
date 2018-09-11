#include "IThread.h"

IThread::IThread()
	: m_thread(0)
{
}

IThread::~IThread()
{
	if (m_thread)
	{
		delete m_thread;
		m_thread = 0;
	}
}

void IThread::Start()
{
	_Start();
	m_thread = new std::thread(&IThread::Run, this);
}

void IThread::Stop()
{
	_Stop();

	// 让线程跑完再说
	m_thread->join();
}

void IThread::Run()
{
	_Run();
//	delete this;
}
