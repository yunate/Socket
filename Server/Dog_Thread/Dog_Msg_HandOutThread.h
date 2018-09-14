#pragma once
#include "Dog_Thread_Base.hpp"
#include "Dog_Thread/Dog_ThreadManager.h"

// msg �ַ��߳�
class Dog_Msg_HandOutThread : public Dog_Thread_Base
{
public:
	Dog_Msg_HandOutThread();
	~Dog_Msg_HandOutThread();

	// ���Ե�Ӳ����Դ�Ƿ��㹻�ڴ���һ���߳���
	bool				IsCptHardSrcEnough();
	void				Init();
	void				UnInit();

private:
	size_t				GetAvaiableId(Dog_ThreadManager::ThreadList&);

public:
	virtual void		InitDes();

private:
	virtual void		_Run();
	virtual bool		_Dog_Stop_After();
};