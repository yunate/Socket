#pragma once
#include "IDog_Msg.h"

/************************Msg_String*************************************/
class Msg_String : public IDog_Msg
{
public:
	Msg_String();
	virtual ~Msg_String();

public:
	virtual bool				HandMsg();		// 处理

};
/************************Msg_String*************************************/

/************************Msg_Testdata*************************************/
class Msg_Testdata : public IDog_Msg
{
public:
	Msg_Testdata();
	virtual ~Msg_Testdata();

public:
	virtual bool				HandMsg();		// 处理

};
/************************Msg_Testdata*************************************/
