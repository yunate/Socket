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


	typedef struct Cmd_Head
	{
		Cmd_Head(CmdType nCmdType)
			: m_nCmdType(nCmdType)
		{
		}

		// �����������͵�����
		CmdType m_nCmdType;
	}Cmd_Head;

	typedef struct Cmd_String
	{
		Cmd_String()
			: m_head(CMD_STRING)
		{

		}

		Cmd_Head m_head;
		std::string m_sData;
	}Cmd_String;
}

