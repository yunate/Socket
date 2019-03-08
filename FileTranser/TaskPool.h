#pragma once

#include <queue>
#include <mutex>

#include "Lock/Dog_Lock.h"


/////////////////////////////TaskPool/////////////////////////////////////////////
class TaskBase;
using TBPool = std::queue<TaskBase*>;

class TaskPool
{
	friend TaskPool & GETTASKPOOL();

private:
	static TaskPool & GetIns()
	{
		static TaskPool s_taskPool;
		return s_taskPool;
	}

	TaskPool();
	TaskPool(const TaskPool &);
	TaskPool & operator=(const TaskPool &);

public:
	inline void Push(TaskBase * pTask)
	{
		Dog_Lock lock(m_pMutex);
		m_pool.push(pTask);
	}

	inline TaskBase * Pop()
	{
		Dog_Lock lock(m_pMutex);

		if (0 == m_pool.size())
		{
			return 0;
		}

		TaskBase * pTmp = m_pool.front();
		m_pool.pop();
		return pTmp;
	}

public:
	~TaskPool();

private:
	TBPool				m_pool;
	std::mutex *        m_pMutex;
};

TaskPool & GETTASKPOOL()
{
	return TaskPool::GetIns();
}