
// common中的
#include "Lock/Dog_Lock.h"

#include "Dog_Msg_Thread.h"
#include "Dog_GolbalData.h"

Dog_Msg_Thread::Dog_Msg_Thread(int nId, size_t nMaxCount)
	: m_nId(nId), m_nMaxMsgCount(nMaxCount)
{
	m_pMutex = new std::mutex();
}

Dog_Msg_Thread::~Dog_Msg_Thread()
{
	if (m_pMutex)
	{
		delete m_pMutex;
		m_pMutex = 0;
	}
}

bool Dog_Msg_Thread::InsertMsg(IDog_Msg* sMsg)
{
	if (m_pMsgs.size() >= m_nMaxMsgCount || 0 == sMsg)
	{
		return false;
	}

	Dog_Lock lock(m_pMutex);
	m_pMsgs.push_back(sMsg);
	return true;
}

void Dog_Msg_Thread::InitDes()
{
	char sInfo[MAX_PATH] = { 0 };
	sprintf_s(sInfo, sizeof(sInfo), "Dog_Msg_Thread %d :", m_nId);
	m_sThreadDes = sInfo;
}

void Dog_Msg_Thread::_Run()
{
	while (m_bRun)
	{
		Sleep(5);

		if (m_pMsgs.size() <= 0)
		{
			continue;
		}

		std::list<IDog_Msg*>::iterator it = m_pMsgs.begin();

		while (m_pMsgs.end() != it)
		{
			(*it)->HandMsg();

			// 这儿就不管处理成功还是失败，直接丢掉msg
			Dog_Lock lock(m_pMutex);
			delete (*it);
			it = m_pMsgs.erase(it);
		}
	}

	// 对msg清理，不要直接清理，交给Dog_Msg_HandOutThread
	Dog_Lock lock(m_pMutex);
	if (m_pMsgs.size() > 0)
	{
		std::list<IDog_Msg*>::iterator it = m_pMsgs.begin();

		while (it != m_pMsgs.end())
		{
			GETGOLBALDATA().InsertMsg(*it);
			++it;
		}

		m_pMsgs.clear();
	}
}
