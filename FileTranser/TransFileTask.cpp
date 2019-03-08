#include "stdafx.h"
#include "TransFileTask.h"

TransFileTask::TransFileTask(TaskType nType, const Cmd::FileTrans & transInfo)
	: TaskBase(nType)
	, m_sIp(transInfo.m_sAddress)
	, m_nPort(transInfo.m_nPort)
	, m_nId(transInfo.m_nFileId)
{
}

TransFileTask::~TransFileTask()
{
}

bool TransFileTask::DoTask()
{
	// TODO:实现文件传输
	return false;
}
