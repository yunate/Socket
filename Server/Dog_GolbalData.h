#pragma once
#include <list>

#include "Lock/Dog_Lock.h"

#include "SocketHead.h"
#include "Dog_Server.h"
#include "Dog_S_Client.h"
#include "Dog_Msg/IDog_Msg.h"
#include "MemoryShare/MemoryShare.h"


class Dog_GolbalData
{
private:
	Dog_GolbalData();
	Dog_GolbalData(const Dog_GolbalData&);

public:
	~Dog_GolbalData();

public:
	// �����ӵĿͻ��˼��뵽����
	void InsertClient(SOCKET hClient, sockaddr_in address);
	void InsertClient(Dog_S_Client* pClient);

	// ���Ѿ��Ͽ����ӵĿͻ��˼��뵽���У�����Ӧ�̴߳���
	void InsertDisConnClient(Dog_S_Client* pClient);

	// ����Ϣ������Ϣ���У�����Ӧ�̴߳���
	void InsertMsg(IDog_Msg* pMsg);

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

	// ����������ú�����˼���
	inline std::list<IDog_Msg*>& GetMsgs()
	{
		return m_pMsgs;
	}

	inline std::mutex* GetMsgsMutex()
	{
		return m_pMsgMutex;
	}

	inline bool IsRun()
	{
		return m_bRun;
	}

	inline void SetRun(bool bRun)
	{
		m_bRun = bRun;
	}

	inline MemoryShare * GetMemShare()
	{
		return m_pMemShare;
	}

private:
	std::list<Dog_S_Client*>			m_hClients;					// ���ӵĿͻ��ˣ���Dog_S_ClientThread����
	std::mutex*							m_pClientMutex;				// ������

	std::list<Dog_S_Client*>			m_hDisConnClients;			// �Ѿ��Ͽ����ӵĿͻ���
	std::mutex*							m_pDisConnClientMutex;		// ������

	std::list<IDog_Msg*>				m_pMsgs;					// �ͻ��˷�������Ϣ
	std::mutex*							m_pMsgMutex;				// ������

	bool								m_bRun;

	// 
	MemoryShare *						m_pMemShare;
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
