#include "Dog_S_Client_HandOuterThread.h"
#include "Dog_GolbalData.h"
#include "Dog_ThreadManager.h"

// Ŀǰ�ݶ����Dog_S_Client��������Ϊ5��
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
		// ������Ȩ�޽�����ʡ��cpuռ���ʹ���
		Sleep(5);
		std::list<Dog_S_Client*>& clients = GETGOLBALDATA().GetClients();

		if (clients.size() <= 0)
		{
			continue;
		}

		// ������
		std::mutex* pMutex = GETGOLBALDATA().GetClientMutex();
		Dog_Lock lock(pMutex);
		std::list<Dog_S_Client*>::iterator cit = clients.begin();

		while (clients.end() != cit)
		{
			// ����ӵ��߳����������ٵ��Ǹ��߳���ȥ,
			Dog_ThreadManager::ThreadList&	threads = GETTHREADMANAGER().GetThreadsByKind(Dog_ThreadManager::THREAD_DOG_S_CLIENT);
			Dog_ThreadManager::ThreadList::iterator it = threads.begin();

			if (threads.end() == it)
			{
				// threads һ�㲻��Ϊ��
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
