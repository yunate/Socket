#pragma once

/*
	这个文件里都是一些数据的结构体
*/

#include <string>

namespace Cmd
{
	// 数据类型
	enum CmdType
	{
		CMD_ERROR_HEAD			= 0,				// 错误头
		CMD_STRING,									// 字符数据

		CMD_ERROR_END								// 错误尾
	};


	typedef struct Cmd_Head
	{
		Cmd_Head(CmdType nCmdType)
			: m_nCmdType(nCmdType)
		{
		}

		// 这是那种类型的数据
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

