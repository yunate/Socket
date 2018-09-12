#pragma once
#include "Dog_Thread_Base.hpp"
#include "Dog_S_Client.h"

#include <mutex>
#include <list>

class Dog_ThreadManager;

// ����s_client���̣߳������ܸ�����Dog_ThreadManager����ʵ��ȷ��
class Dog_S_ClientThread : public Dog_Thread_Base
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

public:
	virtual void InitDes();

private:
	virtual void _Run();

private:
	int									m_nThreadId;			// ��û��ʲô�������壬��Dog_ThreadManager���䣬����ʶ��
	std::list<Dog_S_Client*>			m_pClients;				// ���̴߳����Dog_S_Client
	std::mutex*							m_pMutex;

	friend Dog_ThreadManager;
};
