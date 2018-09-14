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
		CMD_TEST,									// ����
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

