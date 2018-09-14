#include "LogDoggy.h"
#include "LogTracerImpl.h"
#include "LogImpl.h"

LogDoggy::LogDoggy()
	:  m_pTracer(0)
{
}

LogDoggy::~LogDoggy()
{
	if (m_pTracer)
	{
		delete m_pTracer;
		m_pTracer = 0;
	}
}

void LogDoggy::Bark(Unique_ILog upLog)
{
	if (m_pTracer)
	{
		m_pTracer->Trace(std::move(upLog));
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
	Unique_ILog upLog(new ErrorLog(sLog));
	upLog->Format();
	Bark(std::move(upLog));
}

void LogDoggy::Bark_Info_Log(std::string sLog)
{
	Unique_ILog upLog(new InfoLog(sLog));
	upLog->Format();
	Bark(std::move(upLog));
}
