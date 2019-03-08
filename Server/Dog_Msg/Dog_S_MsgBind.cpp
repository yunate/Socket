#pragma once

#define BIND_MSG(nMsgType, classname)	\
m_MsgCreaters[nMsgType] = []() -> IDog_Msg* {return new (classname)();}

#include "PackageCmd/Cmd.hpp"

#include "Dog_MsgFactory.h"
#include "Dog_MsgImpl.h"

void MsgFactory::Init()
{
	BIND_MSG(Cmd::CmdType::CMD_STRING, Msg_String);
	BIND_MSG(Cmd::CmdType::CMD_TEST, Msg_Testdata);
	BIND_MSG(Cmd::CmdType::CMD_FILETRANS, Msg_FileTrans);
}
