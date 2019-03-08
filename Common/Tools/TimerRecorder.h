#pragma once
#include <time.h>

class TimerRecorder
{
public:
	TimerRecorder()
	{
		m_n64StartTime = clock();
	}

	~TimerRecorder() {}

	__int64 GetTimePass()
	{
		return clock() - m_n64StartTime;
	}

private:
	__int64		m_n64StartTime;
};