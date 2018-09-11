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
	

	// ����/ֹͣdog_server�߳�
	void				CreateDogServerThread();
	void				StopDogServerThread();

	// ����/ֹͣ Dog_S_Client_HandOuterThread �߳�
	void				CreateDogSDisConnClientThread();
	void				StopDogSClDisConnCientThread();

	// ����/ֹͣ Dog_S_Client_HandOuterThread �߳�
	void				CreateDogSClientHandOutThread();
	void				StopDogSClientHandOutThread();

	// ����/ֹͣ Dog_S_ClientThread �߳�
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