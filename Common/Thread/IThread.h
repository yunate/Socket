#pragma once

#include <thread>

class IThread
{
public:
	IThread();
	virtual ~IThread();

public:
	void Start();
	void Stop();

	virtual void Notify() {}

private:
	void Run();

private:
	virtual void _Start() {};
	virtual void _Start_After() {};
	virtual void _Stop() {};
	virtual void _Stop_After() {};
	virtual void _Run() = 0;

private:
	std::thread*			m_thread;
};
