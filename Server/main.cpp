#include <stdio.h>  
#include "SocketHead.h"
#include "Dog_GolbalData.h"
#include "Dog_Thread/Dog_ThreadManager.h"

// �ڴ�й¶�����
#ifndef NDEBUG
#pragma comment(lib, "..//vld//release//vld.lib")
#include "..//vld//head//vld.h"
#endif

int main(int argc, char* argv[])
{
	GetDoggy().SetTracer(new LocalFileTracer("server"));
	GETTHREADMANAGER().CreateDogServerThread(8888);
	GETTHREADMANAGER().CreateDogSClientHandOutThread();
	GETTHREADMANAGER().CreateDogSDisConnClientThread();
	GETTHREADMANAGER().CreateDogMsgHandOutThread();

	while (GETGOLBALDATA().IsRun())
	{
		Sleep(5);
	}

	GETTHREADMANAGER().StopAllThread();
	return 0;
}