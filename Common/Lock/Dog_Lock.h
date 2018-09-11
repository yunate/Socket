#pragma once
#include <mutex>

class Dog_Lock
{
public:
	Dog_Lock(std::mutex* mutex);
	~Dog_Lock();

private:
	std::mutex*		m_mutex;
};