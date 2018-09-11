#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>

class ILog
{
public:
	enum LogLevel
	{
		LOG_INFO = 0,
		LOG_WARNING,
		LOG_ERROR,
	};

public:
	ILog(std::string sLog) 
		: m_sLog(sLog)
	{ 
	};

	virtual ~ILog() {};

public:
	virtual LogLevel GetLogLevel() = 0;
	virtual void Format() = 0;

public:
	std::string GetLog()
	{
		return m_sLog;
	}

	void SetLog(std::string sLog)
	{
		m_sLog = sLog;
	}

protected:
	std::string m_sLog;

};

class ILogFormat
{
public:
	virtual void Format(ILog& log) = 0;
};

class ILogTracer
{
public:
	virtual bool Trace(ILog& log) = 0;
};