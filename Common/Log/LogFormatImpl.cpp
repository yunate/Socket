
#include "LogFormatImpl.h"
#include <time.h>

void TimeStampFormat::Format(ILog & log)
{
	std::string sLog = log.GetLog();
	time_t t = time(0);
	char tmp[MAX_PATH];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %H:%M:%S\t", localtime(&t));
	std::string sNowTime(tmp);
	log.SetLog(sNowTime + sLog);
}

void LogLevelFormat::Format(ILog & log)
{
	std::string sLog = log.GetLog();
	ILog::LogLevel level = log.GetLogLevel();
	switch (level)
	{
	case ILog::LOG_INFO:
		log.SetLog("info:\t" + sLog);
		break;
	case ILog::LOG_WARNING:
		log.SetLog("warnning:\t" + sLog);
		break;
	case ILog::LOG_ERROR:
		log.SetLog("error:\t" + sLog);
		break;
	default:
		break;
	}
}
