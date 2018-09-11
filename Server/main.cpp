#include <stdio.h>  
#include "SocketHead.h"
#include "Dog_GolbalData.h"
#include "Dog_Thread/Dog_ThreadManager.h"

int main(int argc, char* argv[])
{
	GetDoggy().SetTracer(new LocalFileTracer("server"));
	GETGOLBALDATA().GetServer().SetIp(INADDR_ANY);
	GETGOLBALDATA().GetServer().SetPort(8888);

	GETTHREADMANAGER().CreateDogServerThread();
	GETTHREADMANAGER().CreateDogSClientHandOutThread();
	GETTHREADMANAGER().CreateDogSDisConnClientThread();

	while (1)
	{
		Sleep(5);
	}

	return 0;
}