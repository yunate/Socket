#include "Dog_GolbalData.h"

Dog_GolbalData::Dog_GolbalData()
{
	m_pClientMutex = new std::mutex();
	m_pDisConnClientMutex = new std::mutex();
	m_pMsgMutex = new std::mutex();

	m_bRun = true;
}

Dog_GolbalData::~Dog_GolbalData()
{
	delete m_pClientMutex;
	m_pClientMutex = NULL;

	for (std::list<Dog_S_Client*>::iterator it = m_hClients.begin();
		it != m_hClients.end(); ++it)
	{
		delete (*it);
	}
	m_hClients.clear();

	delete m_pDisConnClientMutex;
	m_pDisConnClientMutex = NULL;

	for (std::list<Dog_S_Client*>::iterator it = m_hDisConnClients.begin();
		it != m_hDisConnClients.end(); ++it)
	{
		delete (*it);
	}
	m_hDisConnClients.clear();

	delete m_pMsgMutex;
	m_pMsgMutex = NULL;

	for (std::list<IDog_Msg*>::iterator it = m_pMsgs.begin();
		it != m_pMsgs.end(); ++it)
	{
		delete (*it);
	}
	m_pMsgs.clear();
}

void Dog_GolbalData::InsertClient(SOCKET hClient, sockaddr_in address)
{
	GetDoggy().Bark_Info_Log("there is a client linked, ip is:" + std::string(inet_ntoa(address.sin_addr)));
	Dog_Lock lock(m_pClientMutex);
	Dog_S_Client* pClient = new Dog_S_Client(hClient, address);

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

void Dog_GolbalData::InsertMsg(IDog_Msg * pMsg)
{
	// 不要判断pMsg是否为空，这个由调用者判断
	Dog_Lock lock(m_pMsgMutex);
	m_pMsgs.push_back(pMsg);
}

