#pragma once
#include <map>

#include "PackageCmd/Cmd.hpp"

#include "IDog_Msg.h"

typedef IDog_Msg* (*MsgCreater)();

class MsgFactory
{
private:
	MsgFactory()
	{
		Init();
	}

	MsgFactory(const MsgFactory&);

public:
	~MsgFactory()
	{

	}

public:
	IDog_Msg* CreateMsg(Cmd::CmdType nType);

private:
	void Init();

private:
	std::map<Cmd::CmdType, MsgCreater>	m_MsgCreaters;

private:
	static MsgFactory& GetIns()
	{
		static MsgFactory sIns;
		return sIns;
	}

	friend MsgFactory& GETMSTFACTORY();
};


inline MsgFactory & GETMSTFACTORY()
{
	return MsgFactory::GetIns();
}
