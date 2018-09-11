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

	// 将连接的客户端加入到池中
	void InsertClient(SOCKET hClient);
	void InsertClient(Dog_S_Client* pClient);

	// 将已经断开连接的客户端加入到池中，给相应线程处理
	void InsertDisConnClient(Dog_S_Client* pClient);

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

private:
	std::list<Dog_S_Client*>			m_hClients;					// 连接的客户端，由Dog_S_ClientThread管理
	std::mutex*							m_pClientMutex;				// 互斥锁

	std::list<Dog_S_Client*>			m_hDisConnClients;			// 已经断开连接的客户端
	std::mutex*							m_pDisConnClientMutex;		// 互斥锁

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
