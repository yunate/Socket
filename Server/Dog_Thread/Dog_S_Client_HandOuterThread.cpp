#include "Dog_S_Client_HandOuterThread.h"
#include "Dog_GolbalData.h"
#include "Dog_ThreadManager.h"

// 目前暂定最大Dog_S_Client处理数量为5个
#define	MAX_S_CLIENT_THREAD_COUNT 5

Dog_S_Client_HandOuterThread::Dog_S_Client_HandOuterThread()
	: m_bRun(true)
{
	Init();
}

Dog_S_Client_HandOuterThread::~Dog_S_Client_HandOuterThread()
{
	UnInit();
}

void Dog_S_Client_HandOuterThread::Init()
{
	for (int i = 0; i < MAX_S_CLIENT_THREAD_COUNT; ++i)
	{
		GETTHREADMANAGER().CreateDogSClientThread(i);
	}
}

void Dog_S_Client_HandOuterThread::UnInit()
{
	for (int i = 0; i < MAX_S_CLIENT_THREAD_COUNT; ++i)
	{
		GETTHREADMANAGER().StopDogSClientThread(i);
	}
}

void Dog_S_Client_HandOuterThread::_Stop()
{
	m_bRun = false;
}

void Dog_S_Client_HandOuterThread::_Run()
{
	while(m_bRun)
	{
		// 将控制权限交出，省的cpu占用率过高
		Sleep(5);
		std::list<Dog_S_Client*>& clients = GETGOLBALDATA().GetClients();

		if (clients.size() <= 0)
		{
			continue;
		}

		// 加上锁
		std::mutex* pMutex = GETGOLBALDATA().GetClientMutex();
		Dog_Lock lock(pMutex);
		std::list<Dog_S_Client*>::iterator cit = clients.begin();

		while (clients.end() != cit)
		{
			// 将其加到线程中数量最少的那个线程中去,
			Dog_ThreadManager::ThreadList&	threads = GETTHREADMANAGER().GetThreadsByKind(Dog_ThreadManager::THREAD_DOG_S_CLIENT);
			Dog_ThreadManager::ThreadList::iterator it = threads.begin();

			if (threads.end() == it)
			{
				// threads 一般不会为空
				Init();
				break;
			}

			Dog_S_ClientThread* temp = static_cast<Dog_S_ClientThread*>(*it);
			++it;

			while (threads.end() != it)
			{
				Dog_S_ClientThread* temp1 = static_cast<Dog_S_ClientThread*>(*it);
				if (temp1->GetClientSize() < temp->GetClientSize())
				{
					temp = temp1;
				}
				++it;
			}

			temp->InsertClient(*cit);
			cit = clients.erase(cit);
		}
	}
}
