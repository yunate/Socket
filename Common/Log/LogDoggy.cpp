#include "LogDoggy.h"
#include "LogTracerImpl.h"
#include "LogImpl.h"

LogDoggy::LogDoggy()
	:  m_pTracer(0)
{
}

LogDoggy::~LogDoggy()
{
	if (!m_pTracer)
	{
		delete m_pTracer;
		m_pTracer = 0;
	}
}

void LogDoggy::Bark(ILog & log)
{
	if (m_pTracer)
	{
		m_pTracer->Trace(log);
	}
}

void LogDoggy::SetTracer(ILogTracer * pTracer)
{
	if (m_pTracer)
	{
		delete m_pTracer;
	}

	m_pTracer = pTracer;
}

void LogDoggy::Init()
{
	m_pTracer = new LocalFileTracer();
}

void LogDoggy::Bark_Error_Log(std::string sLog)
{
	ILog& log = ErrorLog(sLog);
	log.Format();
	Bark(log);
}

void LogDoggy::Bark_Info_Log(std::string sLog)
{
	ILog& log = InfoLog(sLog);
	log.Format();
	Bark(log);
}
