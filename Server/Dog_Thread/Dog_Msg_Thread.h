#pragma once
#include <string>
#include <list>
#include <mutex>

#include "Dog_Thread_Base.hpp"
#include "Dog_Msg/IDog_Msg.h"

// Dog_S_Client 分发线程
class Dog_Msg_Thread : public Dog_Thread_Base
{
public:
	Dog_Msg_Thread(int nId, size_t nMaxCount);
	virtual ~Dog_Msg_Thread();

public:
	bool InsertMsg(IDog_Msg* sMsg);

	inline bool IsFull()
	{
		return m_pMsgs.size() >= m_nMaxMsgCount;
	}

	inline int GetMsgSize()
	{
		return m_pMsgs.size();
	}

	inline int GetId()
	{
		return m_nId;
	}

public:
	virtual void InitDes();

private:
	virtual void _Run();

private:
	size_t							m_nMaxMsgCount;		// 此线程最多处理消息等待条数
	int								m_nId;				// 线程id
	std::list<IDog_Msg*>		    m_pMsgs;			// 消息表
	std::mutex*						m_pMutex;			// 线程锁
}; 
