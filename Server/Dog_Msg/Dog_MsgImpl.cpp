#include <stdio.h>

#include "PackageCmd/Cmd.hpp"

#include "Dog_MsgImpl.h"
#include "Dog_GolbalData.h"
#include "Tools/TimerRecorder.h"


/************************Msg_String*************************************/
Msg_String::Msg_String()
{
}

Msg_String::~Msg_String()
{
}

bool Msg_String::HandMsg()
{
	if (0 == m_sMsgData.compare("close"))
	{
		GETGOLBALDATA().SetRun(false);
	}

	printf("---------------------Msg Comming--------------------\r\n%s\r\n----------------------------------------------------\r\n"
		, m_sMsgData.c_str());
	return true;
}

/************************Msg_Testdata*************************************/
Msg_Testdata::Msg_Testdata()
{
}

Msg_Testdata::~Msg_Testdata()
{
}

bool Msg_Testdata::HandMsg()
{
	Cmd::TestData* data = (Cmd::TestData*)(m_sMsgData.data());
	int i = 0;
	++i;
	return false;
}

/************************Msg_FileTrans*************************************/

Msg_FileTrans::Msg_FileTrans()
{
}

Msg_FileTrans::~Msg_FileTrans()
{
}

bool Msg_FileTrans::HandMsg()
{
	std::string buff = "";

	// 添加命令头
	Cmd::CmdType nType = GetMsgType();
	buff.append((char*)(&nType), sizeof(nType));

	// 添加data
	buff.append(m_sMsgData.data());
	MemoryShare * pMemShare = GETGOLBALDATA().GetMemShare();

	if (!pMemShare)
	{
		return false;
	}

	TimerRecorder timer;

	while (!pMemShare->IsReadToWrite())
	{
		Sleep(10);

		// 5秒还没有被取走，上一条内存内容作废
		if (timer.GetTimePass() >= 5000)
		{
			pMemShare->Clear();
			break;
		}
	}

	pMemShare->Write((void *) (buff.data()), buff.size());
	return true;
}
