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
		CMD_TEST,									// 测试
		CMD_ERROR_END								// 错误尾
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

	typedef struct TestData
	{
		int nX;
		int nY;
		char cX;
		char cY[10];
		int nZ[10];

		TestData()
		{
			nX = 0;
			nY = 0;
			cX = 0;
			memset(cY, 0, sizeof(cY));
			memset(nZ, 0, sizeof(nZ));
		}

	}TestData;
}

