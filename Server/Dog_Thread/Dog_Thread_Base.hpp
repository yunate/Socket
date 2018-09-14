#pragma once

#include <string>

#include "Thread/IThread.h"
#include "Log/LogDoggy.h"

class Dog_Thread_Base : public IThread
{
public:
	Dog_Thread_Base() 
		: m_bRun(false)
	{
	}

	virtual ~Dog_Thread_Base()
	{

	}

	virtual void Notify()
	{
		GetDoggy().Bark_Info_Log(m_sThreadDes + "notify");
	}

private:
	inline virtual void _Start() final
	{
		InitDes();

		if (_Dog_Start())
		{
			GetDoggy().Bark_Info_Log(m_sThreadDes + "start");
		}

		m_bRun = true;
	}

	// 为了在这之前做一些事情（比如日志）将Ithread 中的虚函数转换为_Dog_Stop
	inline virtual void _Stop() final 
	{
		_Dog_Stop();
		m_bRun = false;
	}

	inline virtual void _Stop_After() final
	{
		GetDoggy().Bark_Info_Log(m_sThreadDes + "stop");
		_Dog_Stop_After();
	}

	virtual bool _Dog_Start()
	{
		return true;
	}

	virtual bool _Dog_Stop()
	{
		return true;
	}

	virtual bool _Dog_Stop_After()
	{
		return true;
	}

	virtual void InitDes() = 0;

protected:
	bool					m_bRun;
	std::string				m_sThreadDes;
};
