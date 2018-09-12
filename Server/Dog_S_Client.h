#pragma once

#include "SocketHead.h"
#include <sstream>

/*
	服务器端管理的client，以S_打头已示区别
*/
class Dog_S_Client
{
public:
	Dog_S_Client(SOCKET hClient, sockaddr_in address);
	~Dog_S_Client();

public:
	bool Init();
	void ReceviceData();

	inline bool IsConnect()
	{
		return m_bConnect;
	}

public:
	std::string GetIp();

private:
	void OnDisConnect();

private:
	SOCKET						m_hClient;			// socket句柄
	sockaddr_in					m_Address;			// 地址
	std::stringstream			m_sStrBuff;			// 读到的数据缓存
	bool						m_bConnect;			// 连接正常吗
	int							m_nErrorCount;		// 接受失败次数，达到一定程度视为失败
};

