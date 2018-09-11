#pragma once
#include <list>
#include <map>

#include "Thread/IThread.h"

#include "Dog_S_ClientThread.h"



class Dog_ThreadManager
{
public:
	enum Thread_Kind
	{
		THREAD_ERROR = -1,
		THREAD_DOG_SERVER,
		THREAD_DOG_CLIENT_HANDOUT,
		THREAD_DOG_DisConn_CLIENT,
		THREAD_DOG_S_CLIENT
	};

	typedef std::list<IThread*> ThreadList;
	typedef std::map<Dog_ThreadManager::Thread_Kind, ThreadList > ThreadPull;

private:
	Dog_ThreadManager();
	Dog_ThreadManager(const Dog_ThreadManager&);

public:
	~Dog_ThreadManager();

public:
	bool				InsertThread(Thread_Kind nKind, IThread* pThread);
	ThreadList&			GetThreadsByKind(Thread_Kind nKind);
	

	// 创建/停止dog_server线程
	void				CreateDogServerThread();
	void				StopDogServerThread();

	// 创建/停止 Dog_S_Client_HandOuterThread 线程
	void				CreateDogSDisConnClientThread();
	void				StopDogSClDisConnCientThread();

	// 创建/停止 Dog_S_Client_HandOuterThread 线程
	void				CreateDogSClientHandOutThread();
	void				StopDogSClientHandOutThread();

	// 创建/停止 Dog_S_ClientThread 线程
	void				CreateDogSClientThread(int nId);
	void				StopDogSClientThread(int nId);

private:
	ThreadPull				m_ThreadPull;

private:
	static Dog_ThreadManager& GetIns()
	{
		static Dog_ThreadManager sIns;
		return sIns;
	}

	friend Dog_ThreadManager& GETTHREADMANAGER();
};

inline Dog_ThreadManager& GETTHREADMANAGER()
{
	return Dog_ThreadManager::GetIns();
}