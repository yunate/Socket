#include "Dog_ThreadManager.h"
#include "Dog_ServerThread.h"
#include "Dog_S_ClientThread.h"
#include "Dog_S_Client_HandOuterThread.h"
#include "Dog_S_DisConnClientsThread.h"
#include "Dog_Thread/Dog_Msg_Thread.h"
#include "Dog_Thread/Dog_Msg_HandOutThread.h"

Dog_ThreadManager::Dog_ThreadManager()
{
}

Dog_ThreadManager::~Dog_ThreadManager()
{
}

bool Dog_ThreadManager::InsertThread(Thread_Kind nKind, IThread * pThread)
{
	if (!pThread)
	{
		return false;
	}

	switch (nKind)
	{
		case Dog_ThreadManager::THREAD_ERROR:
		{
			return false;
			break;
		}
		// 唯一线程处理
		case Dog_ThreadManager::THREAD_DOG_SERVER:
		case Dog_ThreadManager::THREAD_DOG_CLIENT_HANDOUT:
		case Dog_ThreadManager::THREAD_DOG_DisConn_CLIENT:
		case Dog_ThreadManager::THREAD_DOG_MSG_HANDOUT:
		{
			if (0 == m_ThreadPull[nKind].size())
			{
				m_ThreadPull[nKind].push_back(pThread);
			}
			else
			{
				delete pThread;
				return false;
			}
			break;
		}
		// Dog_S_Client/Dog_Msg 线程处理
		case Dog_ThreadManager::THREAD_DOG_S_CLIENT:
		case Dog_ThreadManager::THREAD_DOG_MSG:
		{
			m_ThreadPull[nKind].push_back(pThread);
			break;
		}

		
		default:
		{
			return false;
			break;
		}
	}

	return true;
}

Dog_ThreadManager::ThreadList & Dog_ThreadManager::GetThreadsByKind(Dog_ThreadManager::Thread_Kind nKind)
{
	if (m_ThreadPull.find(nKind) != m_ThreadPull.end())
	{
		return m_ThreadPull[nKind];
	}

	return m_ThreadPull[Dog_ThreadManager::THREAD_ERROR];
}

void Dog_ThreadManager::CreateDogServerThread(int nPort)
{
	Dog_ServerThread* pThread = new Dog_ServerThread(nPort);

	if (InsertThread(THREAD_DOG_SERVER, pThread))
	{
		pThread->Start();
	}
}

void Dog_ThreadManager::StopDogServerThread()
{
	if (0 != m_ThreadPull[THREAD_DOG_SERVER].size())
	{
		IThread* pThread = m_ThreadPull[THREAD_DOG_SERVER].back();
		m_ThreadPull[THREAD_DOG_SERVER].pop_back();
		pThread->Stop();
		delete pThread;
	}
}

void Dog_ThreadManager::CreateDogSDisConnClientThread()
{
	IThread* pThread = new Dog_S_DisConnClientsThread();
	if (InsertThread(THREAD_DOG_DisConn_CLIENT, pThread))
	{
		pThread->Start();
	}
}

void Dog_ThreadManager::StopDogSClDisConnCientThread()
{
	if (0 != m_ThreadPull[THREAD_DOG_DisConn_CLIENT].size())
	{
		IThread* pThread = m_ThreadPull[THREAD_DOG_DisConn_CLIENT].back();
		m_ThreadPull[THREAD_DOG_DisConn_CLIENT].pop_back();
		pThread->Stop();
		delete pThread;
	}
}

void Dog_ThreadManager::CreateDogSClientHandOutThread()
{
	Dog_S_Client_HandOuterThread* pThread = new Dog_S_Client_HandOuterThread();
	if (InsertThread(THREAD_DOG_CLIENT_HANDOUT, pThread))
	{
		pThread->Start();
	}
}

void Dog_ThreadManager::StopDogSClientHandOutThread()
{
	if (0 != m_ThreadPull[THREAD_DOG_CLIENT_HANDOUT].size())
	{
		IThread* pThread = m_ThreadPull[THREAD_DOG_CLIENT_HANDOUT].back();
		m_ThreadPull[THREAD_DOG_CLIENT_HANDOUT].pop_back();
		pThread->Stop();
		delete pThread;
	}
}

void Dog_ThreadManager::CreateDogMsgHandOutThread()
{
	IThread* pThread = new Dog_Msg_HandOutThread();
	if (InsertThread(THREAD_DOG_MSG_HANDOUT, pThread))
	{
		pThread->Start();
	}
}

void Dog_ThreadManager::StopDogMsgHandOutThread()
{
	if (0 != m_ThreadPull[THREAD_DOG_MSG_HANDOUT].size())
	{
		IThread* pThread = m_ThreadPull[THREAD_DOG_MSG_HANDOUT].back();
		m_ThreadPull[THREAD_DOG_MSG_HANDOUT].pop_back();
		pThread->Stop();
		delete pThread;
	}
}

void Dog_ThreadManager::CreateDogSClientThread(int nId)
{
	IThread* pThread = new Dog_S_ClientThread(nId);
	if (InsertThread(THREAD_DOG_S_CLIENT, pThread))
	{
		pThread->Start();
	}
}

void Dog_ThreadManager::StopDogSClientThread(int nId)
{
	ThreadList& threads = m_ThreadPull[THREAD_DOG_S_CLIENT];
	ThreadList::iterator it = threads.begin();

	while (threads.end() != it)
	{
		Dog_S_ClientThread* pDogSCThread = dynamic_cast<Dog_S_ClientThread*>(*it);

		if (nId == pDogSCThread->GetId())
		{
			threads.erase(it);
			pDogSCThread->Stop();
			delete pDogSCThread;
			break;
		}

		++it;
	}
}

void Dog_ThreadManager::CreateDogMsgThread(int nId)
{
	// TODO: 20 这个常量以后根据处理线程的类型决定
	IThread* pThread = new Dog_Msg_Thread(nId, 20);
	if (InsertThread(THREAD_DOG_MSG, pThread))
	{
		pThread->Start();
	}
}

void Dog_ThreadManager::StopDogMsgThread(int nId)
{
	ThreadList& threads = m_ThreadPull[THREAD_DOG_MSG];
	ThreadList::iterator it = threads.begin();

	while (threads.end() != it)
	{
		Dog_Msg_Thread* pDogMsgThread = dynamic_cast<Dog_Msg_Thread*>(*it);

		if (nId == pDogMsgThread->GetId())
		{
			threads.erase(it);
			pDogMsgThread->Stop();
			delete pDogMsgThread;
			break;
		}

		++it;
	}
}

void Dog_ThreadManager::StopAllDogMsgThread()
{
	ThreadList& threads = m_ThreadPull[THREAD_DOG_MSG];
	ThreadList::iterator it = threads.begin();

	while (threads.end() != it)
	{
		Dog_Msg_Thread* pDogMsgThread = dynamic_cast<Dog_Msg_Thread*>(*it);
		pDogMsgThread->Stop();
		delete pDogMsgThread;
		it = threads.erase(it);
	}
}

void Dog_ThreadManager::StopAllThread()
{
	StopDogMsgHandOutThread();
	StopDogSClientHandOutThread();
	ThreadPull::iterator it = m_ThreadPull.begin();

	while (m_ThreadPull.end() != it)
	{
		ThreadList& threadList = it->second;

		ThreadList::iterator itor = threadList.begin();

		while (threadList.end() != itor)
		{
			IThread* pThread = (*itor);
			pThread->Stop();
			delete pThread;
			itor = threadList.erase(itor);
		}

		++it;
	}
}
