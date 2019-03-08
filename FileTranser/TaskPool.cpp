#include "stdafx.h"
#include "TaskPool.h"

/////////////////////////////TaskPool/////////////////////////////////////////////
TaskPool::TaskPool()
{
	m_pMutex = new std::mutex();
}

TaskPool::~TaskPool()
{
	if (m_pMutex)
	{
		delete m_pMutex;
	}
}
