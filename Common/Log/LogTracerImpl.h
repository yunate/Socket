#pragma once
#include <list>
#include <mutex>
#include "ILog.hpp"
#include "Thread/IThread.h"

/*************************本地日志*******************************************/
class LocalFileTracer : public ILogTracer
{
public:
	LocalFileTracer(std::string sFix = "log");
	virtual ~LocalFileTracer() {};

public:
	virtual bool Trace(Unique_ILog upLog);

private:
	std::string GetAvailableFile();

private:
	std::string m_sFix;
	std::string m_sDirPath;
	std::string m_sFileName;
};
/*************************本地日志*******************************************/


/*************************异步日志*******************************************/
class AsyncLogTracerImpl : public ILogTracer, public IThread
{
public:
	AsyncLogTracerImpl(ILogTracer* pNormalTracter);
	~AsyncLogTracerImpl();

public:
	virtual bool Trace(Unique_ILog upLog);

private:
	virtual void _Run();

	inline virtual void _Stop() 
	{
		m_bRun = false;
	};

private:
	ILogTracer*						m_pNormalTracter;		// 即将在线程里处理的tracter
	std::list<Unique_ILog>			m_upLogList;			// 日志池	
	std::mutex*						m_pMutex;
	bool							m_bRun;
};
/*************************异步日志*******************************************/
