#include "Dog_GolbalData.h"

Dog_GolbalData::Dog_GolbalData()
{
	m_pClientMutex = new std::mutex();
	m_pDisConnClientMutex = new std::mutex();
}

Dog_GolbalData::~Dog_GolbalData()
{
	delete m_pClientMutex;
	m_pClientMutex = NULL;

	delete m_pDisConnClientMutex;
	m_pDisConnClientMutex = NULL;
}

void Dog_GolbalData::InsertClient(SOCKET hClient)
{
	Dog_Lock lock(m_pClientMutex);
	Dog_S_Client* pClient = new Dog_S_Client(hClient);

	if (pClient->Init())
	{
		m_hClients.push_back(pClient);
	}
	else
	{
		delete pClient;
	}
}

void Dog_GolbalData::InsertClient(Dog_S_Client * pClient)
{
	Dog_Lock lock(m_pClientMutex);
	m_hClients.push_back(pClient);
}

void Dog_GolbalData::InsertDisConnClient(Dog_S_Client* pClient)
{
	// 不要判断pClient是否为空
	Dog_Lock lock(m_pDisConnClientMutex);
	m_hDisConnClients.push_back(pClient);
}

