#include "IDog_Msg.h"

IDog_Msg::IDog_Msg()
{
}

IDog_Msg::~IDog_Msg()
{
}

void IDog_Msg::Init(Cmd::MsgHead nHead, std::string sMsgData)
{
	m_nHead = nHead;
	m_sMsgData = sMsgData;
}
