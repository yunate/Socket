#include "Dog_S_Client.h"
#include "CommonHead.h"
#include "PackageCmd/DataPackageTools.h"
#include "PackageCmd/Cmd.hpp"

#include "Log/LogDoggy.h"
#include "Dog_Msg/Dog_MsgFactory.h"
#include "Dog_GolbalData.h"

Dog_S_Client::Dog_S_Client(SOCKET hClient, sockaddr_in address)
	: m_hClient(hClient), m_Address(address), m_bConnect(false), m_nErrorCount(0), m_sStrBuff("")
{
}

Dog_S_Client::~Dog_S_Client()
{
}

bool Dog_S_Client::Init()
{
	//设置Socket为非阻塞模式
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
			// 缓冲区繁忙，不做处理
			return;
		}
		else if (err == WSAETIMEDOUT || err == WSAENETDOWN)
		{
			// 失败了
			m_nErrorCount++;

			// 失败次数大于一定次数，视为断开连接
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
		// 连接断开了,将这个消息抛出
		OnDisConnect();
		return;
	}
	else if (nResult > 0)
	{
		m_nErrorCount = 0;
		m_sStrBuff.append(buff, nResult);

		// 解数据包,并将解析到的所有数据段抛出去
		// TODO:
		std::list<std::string> sMsgs = AnayzeBuff();

		std::list<std::string>::iterator it = sMsgs.begin();

		while (sMsgs.end() != it)
		{
			//MsgHead
			Cmd::MsgHead msgHead;
			memcpy(&msgHead, (*it).data(), sizeof(Cmd::MsgHead));
			std::string sMsgData;
			sMsgData.append((*it).data() + sizeof(Cmd::MsgHead), (*it).size() - sizeof(Cmd::MsgHead));
			IDog_Msg* pMsg = GETMSTFACTORY().CreateMsg(msgHead.m_nMsgType);

			if (!pMsg)
			{
				char sInfo[MAX_PATH] = { 0 };
				sprintf_s(sInfo, sizeof(sInfo), "the msg : %d has not bind, please bind it in file Dog_S_MsgBind.cpp", msgHead.m_nMsgType);
				GetDoggy().Bark_Error_Log(std::string(sInfo));
				continue;
			}

			pMsg->Init(msgHead, sMsgData);
			GETGOLBALDATA().InsertMsg(pMsg);

			++it;
		}
	}
}

std::string Dog_S_Client::GetIp()
{
	return std::string(inet_ntoa(m_Address.sin_addr));
}

std::list<std::string> Dog_S_Client::AnayzeBuff()
{
	DataPackageTools tools;
	size_t nOut = 0;
	return tools.UnPackage(m_sStrBuff);
}

void Dog_S_Client::OnDisConnect()
{
	// 不在这里处理
	m_bConnect = false;
	char sInfo[MAX_PATH] = { 0 };
	sprintf_s(sInfo, sizeof(sInfo), "the client : %s is DisConnected", GetIp().c_str());
	GetDoggy().Bark_Info_Log(std::string(sInfo));
}
