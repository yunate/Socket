#pragma once

#include "ILog.hpp"

class TimeStampFormat : public ILogFormat
{
public:
	virtual void Format(ILog& log);
};

class LogLevelFormat : public ILogFormat
{
public:
	virtual void Format(ILog& log);
};