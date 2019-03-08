#include "stdafx.h"

#include "PackageCmd/Cmd.hpp"

#include "MainFrame.h"
#include "TaskPool.h"
#include "TransFileTask.h"

MainFrame::MainFrame()
{
	m_pMemShare = new MemoryShare("{3AAB25AC-B3D0-4C5D-9EDD-D94114C05495}");
}

MainFrame::~MainFrame()
{
	if (m_pMemShare)
	{
		delete m_pMemShare;
		m_pMemShare = 0;
	}
}

bool MainFrame::OnFrame()
{
	CheckShareMem();
	return true;
}

bool MainFrame::CheckShareMem()
{
	if (!m_pMemShare)
	{
		return false;
	}

	if (!m_pMemShare->IsReadToRead())
	{
		return false;
	}

	int nSize = m_pMemShare->GetBuffSize() + 1;
	char * buff = new char[nSize];
	buff[nSize] = 0;
	m_pMemShare->Read(buff);
	AnalyzeBuff(buff, nSize - 1);
	delete buff;
}

void MainFrame::AnalyzeBuff(void * buff, int nBuffSize)
{
	Cmd::MsgHead msgHead;
	memcpy(&msgHead, buff, sizeof(Cmd::MsgHead));
	std::string sMsgData;
	sMsgData.append((char*)buff + sizeof(Cmd::MsgHead), nBuffSize - sizeof(Cmd::MsgHead));

	switch (msgHead.m_nMsgType)
	{
	case Cmd::CMD_FILETRANS:
	{
		Cmd::FileTrans* data = (Cmd::FileTrans*)(sMsgData.data());
		TransFileTask * pTask = new TransFileTask(TT_TRANSFILE, *data);
		GETTASKPOOL().Push(pTask);
		break;
	}
	default:
		// 其他的直接处理了
		break;
	}
	
}
