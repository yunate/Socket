#pragma once
#include <string>

#include "PackageCmd/Cmd.hpp"

class IDog_Msg
{
public:
	IDog_Msg();
	virtual ~IDog_Msg();

public:
	void						Init(Cmd::MsgHead nHead, std::string sMsgData);

	inline int					GetMsgType()
	{
		return m_nHead.m_nMsgType;
	}

public:
	virtual bool				HandMsg() = 0;		// ����

protected:
	std::string					m_sMsgData;
	Cmd::MsgHead				m_nHead;

	// TODO:��ӷ���client����Ϣ�����������һ�ݿ�����������ָ��
};