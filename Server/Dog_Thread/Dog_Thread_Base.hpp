#pragma once

#include <string>

#include "Thread/IThread.h"
#include "Log/LogDoggy.h"

class Dog_Thread_Base : public IThread
{
public:
	Dog_Thread_Base() 
		: m_bRun(true)
	{
	}

	~Dog_Thread_Base()
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
	}

	inline virtual void _Stop() final 
	{
		if (_Dog_Stop())
		{
			GetDoggy().Bark_Info_Log(m_sThreadDes + "stop");
			m_bRun = false;
		}
	}

	virtual bool _Dog_Start()
	{
		return true;
	}

	virtual bool _Dog_Stop()
	{
		return true;
	}

	virtual void InitDes() = 0;

protected:
	bool					m_bRun;
	std::string				m_sThreadDes;
};
