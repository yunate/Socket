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
		// 将控制权限交出，省的cpu占用率过高
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
			// TODO:这儿作client断开连接后的处理，比如后续命令，内存释放等
			delete (*it);
			it = clients.erase(it);
		}
	}
}
