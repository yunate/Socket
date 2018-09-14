#pragma once
#include <string>
#include <list>
#include <mutex>

#include "Dog_Thread_Base.hpp"
#include "Dog_Msg/IDog_Msg.h"

// Dog_S_Client �ַ��߳�
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
	size_t							m_nMaxMsgCount;		// ���߳���ദ����Ϣ�ȴ�����
	int								m_nId;				// �߳�id
	std::list<IDog_Msg*>		    m_pMsgs;			// ��Ϣ��
	std::mutex*						m_pMutex;			// �߳���
}; 
