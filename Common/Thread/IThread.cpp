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
	_Start_After();
}

void IThread::Stop()
{
	_Stop();

	// ���߳�������˵
	m_thread->join();

	_Stop_After();
}

void IThread::Run()
{
	_Run();
//	delete this;
}
