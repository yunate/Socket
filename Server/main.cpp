#include <stdio.h>  
#include "SocketHead.h"
#include "Dog_GolbalData.h"
#include "Dog_Thread/Dog_ThreadManager.h"

// #pragma comment(lib, "vld.lib")
// #include "E:\projects\vld\head\vld.h"

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