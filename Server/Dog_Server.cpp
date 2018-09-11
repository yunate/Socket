#include "Dog_Server.h"

#include "Dog_GolbalData.h"
#include "Dog_S_Client.h"

#define WSAVERSIONMAJOR 2
#define WSAVERSIONMINOR 2

Dog_Server::Dog_Server()
	:m_nPort(-1), m_ulIp(-1), m_bInit(false), m_hSocket(INVALID_SOCKET)
{
}

Dog_Server::~Dog_Server()
{
	Stop();
}

bool Dog_Server::_Init()
{
	GetDoggy().Bark_Info_Log("Dog_Server init...");
	m_bInit = false;

	try
	{
		if (-1 == m_nPort || -1 == m_ulIp)
		{
			GetDoggy().Bark_Error_Log("m_nPort or m_ulIp not init, please call SetPort or SetIp before _Init");
			return m_bInit;
		}

		//��ʼ��WSA  
		WORD sockVersion = MAKEWORD(WSAVERSIONMAJOR, WSAVERSIONMINOR);
		WSADATA wsaData;

		if (0 != WSAStartup(sockVersion, &wsaData))
		{
			GetDoggy().Bark_Error_Log("WSAStartup error !");
			return m_bInit;
		}

		//�����׽���  
		m_hSocket = socket(AF_INET			// Э����
			, SOCK_STREAM					// ���䣨�������Ӵ��䣩
			, IPPROTO_TCP					// Э��
		);

		if (INVALID_SOCKET == m_hSocket)
		{
			throw std::exception("socket error !");
		}

		//��IP�Ͷ˿�  
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(m_nPort);
		sin.sin_addr.S_un.S_addr = m_ulIp;

		if (bind(m_hSocket, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			throw std::exception("bind error !");
		}

		//��ʼ����  
		if (listen(m_hSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			throw std::exception("listen error !");
		}
	}
	catch (const std::exception& e)
	{
		WSACleanup();
		GetDoggy().Bark_Error_Log(e.what());
		m_bInit = false;
		return m_bInit;
	}

	GetDoggy().Bark_Info_Log("Dog_Server init success");

	m_bInit = true;
	return m_bInit;
}

bool Dog_Server::Start()
{
	if (!_Init())
	{
		return false;
	}

	// ��������ѭ��
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	while (m_bInit)
	{
		sClient = accept(m_hSocket, (SOCKADDR *)&remoteAddr, &nAddrlen);

		if (sClient == INVALID_SOCKET)
		{
			Sleep(5);
			continue;
		}

		// ������������ȫ�ֵ�client����
		GETGOLBALDATA().InsertClient(sClient);
	}

	return true;
}

bool Dog_Server::Stop()
{
	if (m_bInit)
	{
		m_bInit = false;
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
		WSACleanup();
	}

	return true;
}

void Dog_Server::SetPort(int nPort)
{
	m_nPort = nPort;
}

void Dog_Server::SetIp(unsigned long ulIp/* = INADDR_ANY*/)
{
	m_ulIp = ulIp;
}
