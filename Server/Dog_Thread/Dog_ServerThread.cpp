#include "Dog_ServerThread.h"

#include "Dog_GolbalData.h"

Dog_ServerThread::Dog_ServerThread()
{
}

Dog_ServerThread::~Dog_ServerThread()
{
}

void Dog_ServerThread::_Run()
{
	GETGOLBALDATA().GetServer().Start();
}

void Dog_ServerThread::_Stop()
{
	GETGOLBALDATA().GetServer().Stop();
}
