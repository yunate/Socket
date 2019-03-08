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
		CMD_FILETRANS,								// �ļ�����
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

	typedef struct FileTrans
	{
		char			m_sAddress[16];
		unsigned short	m_nPort;
		int				m_nFileId;

		FileTrans()
		{
			m_nFileId = -1;
			memset(&m_sAddress, 0, sizeof(m_sAddress)); 
			m_nPort = 0;
		}

	}FileTrans;

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

