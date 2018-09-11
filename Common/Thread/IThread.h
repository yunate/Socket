#pragma once

#include <thread>

class IThread
{
public:
	IThread();
	~IThread();

public:
	void Start();
	void Stop();

	virtual void Notify() {}

private:
	void Run();

private:
	virtual void _Start() {};
	virtual void _Stop() {};
	virtual void _Run() = 0;

private:
	std::thread*			m_thread;
};
