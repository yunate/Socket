#include <stdio.h>  
#include "SocketHead.h"
#include "Dog_GolbalData.h"
#include "Dog_Thread/Dog_ThreadManager.h"

// ÄÚ´æÐ¹Â¶¼ì²âÆ÷
#ifndef NDEBUG
#pragma comment(lib, "..//vld//release//vld.lib")
#include "..//vld//head//vld.h"
#endif

int main(int argc, char* argv[])
{
	GETTHREADMANAGER().StartAllThread();

	while (GETGOLBALDATA().IsRun())
	{
		Sleep(5);
	}

	GETTHREADMANAGER().StopAllThread();
	return 0;
}