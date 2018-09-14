#include "Dog_Msg_HandOutThread.h"
#include "Dog_GolbalData.h"
#include "Dog_Thread/Dog_Msg_Thread.h"

#define MAX_MSGHANDTHREAD_COUNT 20
#define MSG_INIT_COUNT 5

Dog_Msg_HandOutThread::Dog_Msg_HandOutThread()
{
}

Dog_Msg_HandOutThread::~Dog_Msg_HandOutThread()
{
}

bool Dog_Msg_HandOutThread::IsCptHardSrcEnough()
{
	// TODO: 这儿以后去判断
	return true;
}

void Dog_Msg_HandOutThread::Init()
{
	for (int i = 0; i < MSG_INIT_COUNT; ++i)
	{
		GETTHREADMANAGER().CreateDogMsgThread(i);
	}
}

void Dog_Msg_HandOutThread::UnInit()
{
	GETTHREADMANAGER().StopAllDogMsgThread();
}

size_t Dog_Msg_HandOutThread::GetAvaiableId(Dog_ThreadManager::ThreadList& pThreads)
{
	Dog_ThreadManager::ThreadList::iterator it = pThreads.begin();
	Dog_Msg_Thread* temp = 0;
	size_t nCount = 0;
	char* cTmps = new char[pThreads.size()];
	memset(cTmps, 0, pThreads.size());

	while (pThreads.end() != it)
	{
		temp = static_cast<Dog_Msg_Thread*>(*it);
		nCount = temp->GetId();

		if (nCount < pThreads.size())
		{
			cTmps[nCount] = true;
		}

		++it;
	}

	nCount = pThreads.size();

	for (size_t i = 0; i < pThreads.size(); ++i)
	{
		if (!cTmps[i])
		{
			nCount = i;
			break;
		}
	}

	delete []cTmps;

	return nCount;
}

void Dog_Msg_HandOutThread::InitDes()
{
	m_sThreadDes = "Dog_Msg_HandOutThread : ";
}

void Dog_Msg_HandOutThread::_Run()
{
	while (m_bRun)
	{
		Sleep(5);

		std::list<IDog_Msg*>& pMsgs = GETGOLBALDATA().GetMsgs();
		if (pMsgs.size() <= 0)
		{
			continue;
		}

		std::mutex*						pMutex = GETGOLBALDATA().GetMsgsMutex();
		std::list<IDog_Msg*>::iterator	it = pMsgs.begin();

		while (pMsgs.end() != it)
		{
			// 分发
			Dog_ThreadManager::ThreadList&	threads = GETTHREADMANAGER().GetThreadsByKind(Dog_ThreadManager::THREAD_DOG_MSG);
			Dog_ThreadManager::ThreadList::iterator tit = threads.begin();

			if (threads.end() == tit)
			{
				// 空的，就先创建一个线程
				Init();
				break;
			}

			Dog_Msg_Thread* temp = static_cast<Dog_Msg_Thread*>(*tit);
			++tit;

			while (threads.end() != tit)
			{
				Dog_Msg_Thread* temp1 = static_cast<Dog_Msg_Thread*>(*tit);
				if (temp1->GetMsgSize() < temp->GetMsgSize() && !temp1->IsFull())
				{
					temp = temp1;
				}
				++tit;
			}

			if (temp->IsFull())
			{
				if (threads.size() < MAX_MSGHANDTHREAD_COUNT && IsCptHardSrcEnough())
				{
					// 尝试创建一个线程
					GETTHREADMANAGER().CreateDogMsgThread(GetAvaiableId(threads));
				}
				
				break;
			}

			char sInfo[MAX_PATH] = { 0 };
			sprintf_s(sInfo, sizeof(sInfo), "the msg : %d is hand out to %d msgthread", (*it)->GetMsgType(), temp->GetId());
			GetDoggy().Bark_Info_Log(std::string(sInfo));

			temp->InsertMsg(*it);
			Dog_Lock lock(pMutex);
			it = pMsgs.erase(it);
		}
	}
	UnInit();
}
