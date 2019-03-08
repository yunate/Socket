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
	// 将连接的客户端加入到池中
	void InsertClient(SOCKET hClient, sockaddr_in address);
	void InsertClient(Dog_S_Client* pClient);

	// 将已经断开连接的客户端加入到池中，给相应线程处理
	void InsertDisConnClient(Dog_S_Client* pClient);

	// 将消息加入消息池中，让相应线程处理
	void InsertMsg(IDog_Msg* pMsg);

	// 这个函数调用后别忘了加锁
	inline std::list<Dog_S_Client*>& GetClients()
	{
		return m_hClients;
	}

	inline std::mutex* GetClientMutex()
	{
		return m_pClientMutex;
	}

	// 这个函数调用后别忘了加锁
	inline std::list<Dog_S_Client*>& GetDisConnClients()
	{
		return m_hDisConnClients;
	}

	inline std::mutex* GetDisConnClientMutex()
	{
		return m_pDisConnClientMutex;
	}

	// 这个函数调用后别忘了加锁
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
	std::list<Dog_S_Client*>			m_hClients;					// 连接的客户端，由Dog_S_ClientThread管理
	std::mutex*							m_pClientMutex;				// 互斥锁

	std::list<Dog_S_Client*>			m_hDisConnClients;			// 已经断开连接的客户端
	std::mutex*							m_pDisConnClientMutex;		// 互斥锁

	std::list<IDog_Msg*>				m_pMsgs;					// 客户端发来的消息
	std::mutex*							m_pMsgMutex;				// 互斥锁

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
