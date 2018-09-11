#include "Lock/Dog_Lock.h"

#include "Dog_S_ClientThread.h"
#include "Dog_GolbalData.h"

Dog_S_ClientThread::Dog_S_ClientThread(int nId)
	: m_bRun(true), m_nThreadId(nId)
{
	m_pMutex = new std::mutex();
}

Dog_S_ClientThread::~Dog_S_ClientThread()
{
}

void Dog_S_ClientThread::InsertClient(Dog_S_Client * pClient)
{
	Dog_Lock lock(m_pMutex);
	m_pClients.push_back(pClient);
}

void Dog_S_ClientThread::_Run()
{
	while (m_bRun)
	{
		// ������Ȩ�޽�����ʡ��cpuռ���ʹ���
		Sleep(5);

		Dog_Lock lock(m_pMutex);
		if (m_pClients.size() > 0)
		{
			std::list<Dog_S_Client*>::iterator it = m_pClients.begin();

			while (it != m_pClients.end())
			{
				// ������Ȩ�޽�����ʡ��cpuռ���ʹ���
				Sleep(5);

				if (!(*it)->IsConnect())
				{
					// �Ƴ��Ͽ����ӵ�Dog_S_Client�� ֻ����m_hClients���Ƴ����������������ڴ��ͷŵȺ����������������̴߳���
					GETGOLBALDATA().InsertDisConnClient(*it);
					it = m_pClients.erase(it);
					continue;
				}

				(*it)->ReceviceData();
				++it;
			}
		}
	}

	// �߳�ֹͣ��Dog_S_Client���ظ�GETGOLBALDATA
	Dog_Lock lock(m_pMutex);
	if (m_pClients.size() > 0)
	{
		std::list<Dog_S_Client*>::iterator it = m_pClients.begin();

		while (it != m_pClients.end())
		{
			GETGOLBALDATA().InsertClient(*it);
			++it;
		}

		m_pClients.clear();
	}
}

void Dog_S_ClientThread::_Stop()
{
	m_bRun = false;
}
