#include "Lock/Dog_Lock.h"

#include "Dog_S_DisConnClientsThread.h"
#include "Dog_GolbalData.h"

Dog_S_DisConnClientsThread::Dog_S_DisConnClientsThread()
	: m_bRun(true)
{
}

Dog_S_DisConnClientsThread::~Dog_S_DisConnClientsThread()
{
}

void Dog_S_DisConnClientsThread::_Stop()
{
	m_bRun = false;
}

void Dog_S_DisConnClientsThread::_Run()
{
	while (m_bRun)
	{
		// ������Ȩ�޽�����ʡ��cpuռ���ʹ���
		Sleep(5);
		std::list<Dog_S_Client*>& clients = GETGOLBALDATA().GetDisConnClients();

		if (clients.size() <= 0)
		{
			continue;
		}

		std::mutex* pMutex = GETGOLBALDATA().GetDisConnClientMutex();
		Dog_Lock lock(pMutex);
		std::list<Dog_S_Client*>::iterator it = clients.begin();

		while (clients.end() != it)
		{
			// TODO:�����client�Ͽ����Ӻ�Ĵ��������������ڴ��ͷŵ�
			delete (*it);
			it = clients.erase(it);
		}
	}
}
