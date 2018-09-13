#include "Dog_MsgFactory.h"

IDog_Msg* MsgFactory::CreateMsg(Cmd::CmdType nType)
{
	if (m_MsgCreaters.end() != m_MsgCreaters.find(nType))
	{
		return (*m_MsgCreaters[nType])();
	}

	return 0;
}

