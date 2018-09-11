#pragma once
#include "Lock/Dog_Lock.h"

#include "SocketHead.h"
#include "Dog_Server.h"
#include "Dog_S_Client.h"

#include <list>

class Dog_GolbalData
{
private:
	Dog_GolbalData();
	Dog_GolbalData(const Dog_GolbalData&);

public:
	~Dog_GolbalData();

public:
	inline Dog_Server& GetServer()
	{
		return Dog_Server::GetIns();
	}

	// �����ӵĿͻ��˼��뵽����
	void InsertClient(SOCKET hClient);
	void InsertClient(Dog_S_Client* pClient);

	// ���Ѿ��Ͽ����ӵĿͻ��˼��뵽���У�����Ӧ�̴߳���
	void InsertDisConnClient(Dog_S_Client* pClient);

	// ����������ú�����˼���
	inline std::list<Dog_S_Client*>& GetClients()
	{
		return m_hClients;
	}

	inline std::mutex* GetClientMutex()
	{
		return m_pClientMutex;
	}

	// ����������ú�����˼���
	inline std::list<Dog_S_Client*>& GetDisConnClients()
	{
		return m_hDisConnClients;
	}

	inline std::mutex* GetDisConnClientMutex()
	{
		return m_pDisConnClientMutex;
	}

private:
	std::list<Dog_S_Client*>			m_hClients;					// ���ӵĿͻ��ˣ���Dog_S_ClientThread����
	std::mutex*							m_pClientMutex;				// ������

	std::list<Dog_S_Client*>			m_hDisConnClients;			// �Ѿ��Ͽ����ӵĿͻ���
	std::mutex*							m_pDisConnClientMutex;		// ������

private:
	static Dog_GolbalData& GetIns()
	{
		static Dog_GolbalData sIns;
		return sIns;
	}

	friend Dog_GolbalData& GETGOLBALDATA();
};

inline Dog_GolbalData& GETGOLBALDATA()
{
	return Dog_GolbalData::GetIns();
}
