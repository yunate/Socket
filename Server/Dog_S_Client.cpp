#include "Dog_S_Client.h"
#include "CommonHead.h"

#include "Log/LogDoggy.h"

Dog_S_Client::Dog_S_Client(SOCKET hClient)
	: m_hClient(hClient), m_bConnect(false), m_nErrorCount(0)
{
}

Dog_S_Client::~Dog_S_Client()
{
}

bool Dog_S_Client::Init()
{
	//����SocketΪ������ģʽ
	int iMode = 1;
	if (SOCKET_ERROR == ioctlsocket(m_hClient, FIONBIO, (u_long FAR*)&iMode))
	{
		closesocket(m_hClient);
		GetDoggy().Bark_Error_Log("S_Client set non-block failed, has deleted this client");
		return false;
	}

	m_bConnect = true;
	return true;
}

void Dog_S_Client::ReceviceData()
{
	if (!m_bConnect)
	{
		return;
	}

	char buff[MAX_PACK_SIZE];
	memset(buff, 0, sizeof(buff));
	int nResult = recv(m_hClient, buff, sizeof(buff), 0);

	if (SOCKET_ERROR == nResult)
	{
		int err = WSAGetLastError();
		if (err == WSAEWOULDBLOCK)
		{
			// ��������æ����������
			return;
		}
		else if (err == WSAETIMEDOUT || err == WSAENETDOWN)
		{
			// ʧ����
			m_nErrorCount++;

			// ʧ�ܴ�������һ����������Ϊ�Ͽ�����
			if (m_nErrorCount > MAX_ERROR_COUNT)
			{
				OnDisConnect();
			}

			return;
		}
		else if (err == WSAECONNRESET)
		{
			OnDisConnect();
			return;
		}
	}
	else if (0 == nResult)
	{
		// ���ӶϿ���,�������Ϣ�׳�
		OnDisConnect();
		return;
	}
	else if (nResult > 0)
	{
		m_nErrorCount = 0;
		m_sStrBuff << buff;
	}

	// �����ݰ�,�������������������ݶ��׳�ȥ
	// TODO:
}

void Dog_S_Client::OnDisConnect()
{
	// �������ﴦ��
	m_bConnect = false;
}
