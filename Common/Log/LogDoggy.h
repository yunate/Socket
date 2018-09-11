#pragma once
#include "Ilog.hpp"

class LogDoggy
{
private:
	LogDoggy();
	LogDoggy(const LogDoggy &);

public:
	~LogDoggy();

	void Bark(ILog& log);
	void SetTracer(ILogTracer* pTracer);
	void Init();

public:
	void Bark_Error_Log(std::string sLog);
	void Bark_Info_Log(std::string sLog);

private:
	ILogTracer* m_pTracer;

	static LogDoggy& GetIns()
	{
		static LogDoggy sIns;
		return sIns;
	}

	friend LogDoggy& GetDoggy();
};

inline LogDoggy& GetDoggy()
{
	return LogDoggy::GetIns();
}