#include <stdio.h>

#include "PackageCmd/Cmd.hpp"

#include "Dog_MsgImpl.h"
#include "Dog_GolbalData.h"


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
/************************Msg_String*************************************/

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
/************************Msg_Testdata*************************************/
