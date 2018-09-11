#include "LogImpl.h"
#include "LogFormatImpl.h"

////////////////////////--ErrorLog--///////////////////////////////////////////
ErrorLog::ErrorLog(std::string sLog)
	: ILog(sLog)
{
}

ErrorLog::~ErrorLog()
{
}

void ErrorLog::Format()
{
	LogLevelFormat levelFormat;
	TimeStampFormat timeFormat;
	levelFormat.Format(*this);
	timeFormat.Format(*this);
	m_sLog += "\r\n";
}

////////////////////////--InfoLog--///////////////////////////////////////////
InfoLog::InfoLog(std::string sLog)
	: ILog(sLog)
{
}

InfoLog::~InfoLog()
{
}

void InfoLog::Format()
{
	LogLevelFormat levelFormat;
	TimeStampFormat timeFormat;
	levelFormat.Format(*this);
	timeFormat.Format(*this);
	m_sLog += "\r\n";
}
