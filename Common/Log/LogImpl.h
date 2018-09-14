#pragma once
#include "ILog.hpp"

class ErrorLog : public ILog
{
public:
	ErrorLog(std::string sLog);
	virtual ~ErrorLog();

public:
	virtual LogLevel GetLogLevel()
	{
		return LogLevel::LOG_ERROR;
	}

	virtual void Format();
};

class InfoLog : public ILog
{
public:
	InfoLog(std::string sLog);
	~InfoLog();

public:
	virtual LogLevel GetLogLevel()
	{
		return LogLevel::LOG_INFO;
	}

	virtual void Format();
};

