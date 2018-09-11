#pragma once
#include "ILog.hpp"

class LocalFileTracer : public ILogTracer
{
public:
	LocalFileTracer(std::string sFix = "log");
	~LocalFileTracer() {};

public:
	virtual bool Trace(ILog& log);

private:
	std::string GetAvailableFile();

private:
	std::string m_sFix;
	std::string m_sDirPath;
	std::string m_sFileName;
};