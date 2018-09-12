#include "Lock/Dog_Lock.h"

#include "Dog_S_ClientThread.h"
#include "Dog_GolbalData.h"

Dog_S_ClientThread::Dog_S_ClientThread(int nId)
	: m_nThreadId(nId)
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

void Dog_S_ClientThread::InitDes()
{
	char sInfo[MAX_PATH] = { 0 };
	sprintf_s(sInfo, sizeof(sInfo), "Dog_S_ClientThread %d :", m_nThreadId);
	m_sThreadDes = sInfo;
}

void Dog_S_ClientThread::_Run()
{
	while (m_bRun)
	{
		// 将控制权限交出，省的cpu占用率过高
		Sleep(5);

		Dog_Lock lock(m_pMutex);
		if (m_pClients.size() > 0)
		{
			std::list<Dog_S_Client*>::iterator it = m_pClients.begin();

			while (it != m_pClients.end())
			{
				// 将控制权限交出，省的cpu占用率过高
				Sleep(5);

				if (!(*it)->IsConnect())
				{
					// 移除断开连接的Dog_S_Client， 只做从m_hClients中移除处理，其他操作（内存释放等后续处理）交给其他线程处理
					GETGOLBALDATA().InsertDisConnClient(*it);
					it = m_pClients.erase(it);
					continue;
				}

				(*it)->ReceviceData();
				++it;
			}
		}
	}

	// 线程停止后将Dog_S_Client返回给GETGOLBALDATA
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
