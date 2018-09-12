#include "Dog_Server.h"

#include "Dog_GolbalData.h"
#include "Dog_S_Client.h"

#define WSAVERSIONMAJOR 2
#define WSAVERSIONMINOR 2

Dog_Server::Dog_Server(int nPort)
	:m_nPort(nPort), m_hSocket(INVALID_SOCKET)
{
}

Dog_Server::~Dog_Server()
{
}

bool Dog_Server::Init()
{
	GetDoggy().Bark_Info_Log("Dog_Server init...");

	try
	{
		if (-1 == m_nPort)
		{
			GetDoggy().Bark_Error_Log("m_nPort is invalid");
			return false;
		}

		//��ʼ��WSA  
		WORD sockVersion = MAKEWORD(WSAVERSIONMAJOR, WSAVERSIONMINOR);
		WSADATA wsaData;

		if (0 != WSAStartup(sockVersion, &wsaData))
		{
			GetDoggy().Bark_Error_Log("WSAStartup error !");
			return false;
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
		sin.sin_addr.S_un.S_addr = INADDR_ANY;

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
		return false;
	}

	GetDoggy().Bark_Info_Log("Dog_Server init success");

	return true;
}

void Dog_Server::UnInit()
{
	if (INVALID_SOCKET != m_hSocket)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
		WSACleanup();
	}
}

SOCKET Dog_Server::Accept(sockaddr_in* addr, int * addrlen)
{
	SOCKET sClient = accept(m_hSocket, (SOCKADDR *)addr, addrlen);

	if (sClient == INVALID_SOCKET)
	{
		return 0;
	}
	return sClient;
}
