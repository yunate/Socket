#include <stdio.h>  
#include "SocketHead.h"
#include "Dog_GolbalData.h"
#include "Dog_Thread/Dog_ThreadManager.h"

#include <crtdbg.h>
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

	_CrtDumpMemoryLeaks();
	return 0;
}