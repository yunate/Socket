#include "Dog_ServerThread.h"

#include "Dog_GolbalData.h"

Dog_ServerThread::Dog_ServerThread(int nPort)
{
	m_pServer = new Dog_Server(nPort);
	m_bRun = m_pServer->Init();
}

Dog_ServerThread::~Dog_ServerThread()
{
	if (m_pServer)
	{
		delete m_pServer;
	}
}

void Dog_ServerThread::InitDes()
{
	m_sThreadDes = "Dog_ServerThread : ";
}

void Dog_ServerThread::_Run()
{
	// 开启监听循环
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);

	while (m_bRun)
	{
		memset(&sClient, sizeof(sClient), 0);
		memset(&remoteAddr, sizeof(remoteAddr), 0);
		sClient = m_pServer->Accept(&remoteAddr, &nAddrlen);

		if (0 == sClient)
		{
			Sleep(5);
			continue;
		}

		// 将这个请求加入全局的client池中
		GETGOLBALDATA().InsertClient(sClient, remoteAddr);
	}

	m_pServer->UnInit();
}
