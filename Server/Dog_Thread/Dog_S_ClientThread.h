#pragma once
#include "Thread/IThread.h"
#include "Dog_S_Client.h"

#include <mutex>
#include <list>

class Dog_ThreadManager;

// 处理s_client的线程，他的总个数由Dog_ThreadManager根据实际确定
class Dog_S_ClientThread : public IThread
{
public:
	Dog_S_ClientThread(int nId);
	~Dog_S_ClientThread();

public:
	inline int GetId()
	{
		return m_nThreadId;
	}

	inline int GetClientSize()
	{
		return m_pClients.size();
	}

	void InsertClient(Dog_S_Client* pClient);

private:
	virtual void _Run();
	virtual void _Stop();

private:
	int									m_nThreadId;			// 并没有什么物理意义，由Dog_ThreadManager分配，作标识用
	std::list<Dog_S_Client*>			m_pClients;				// 本线程处理的Dog_S_Client
	bool								m_bRun;					// 循环标记
	std::mutex*							m_pMutex;


	friend Dog_ThreadManager;
};
