#pragma once

/*
	����ļ��ﶼ��һЩ���ݵĽṹ��
*/

#include <string>

namespace Cmd
{
	// ��������
	enum CmdType
	{
		CMD_ERROR_HEAD			= 0,				// ����ͷ
		CMD_STRING,									// �ַ�����

		CMD_ERROR_END								// ����β
	};

	typedef struct MsgHead
	{
		MsgHead(CmdType nType)
			: m_nMsgType(nType)
		{

		}

		MsgHead()
		{

		}

		CmdType m_nMsgType;
	}MsgHead;
}

