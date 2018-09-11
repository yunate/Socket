#include "Dog_Lock.h"

Dog_Lock::Dog_Lock(std::mutex* mutex)
	: m_mutex(mutex)
{
	if (m_mutex)
	{
		m_mutex->lock();
	}
}

Dog_Lock::~Dog_Lock()
{
	if (m_mutex)
	{
		m_mutex->unlock();
	}
}
