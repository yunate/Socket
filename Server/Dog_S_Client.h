#pragma once

#include "SocketHead.h"
#include <list>

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
	std::string					GetIp();

	// TODO:考虑使用右值表达式优化
	std::list<std::string>		AnayzeBuff();

private:
	void OnDisConnect();

private:
	SOCKET						m_hClient;			// socket句柄
	sockaddr_in					m_Address;			// 地址
	std::string					m_sStrBuff;			// 读到的数据缓存,这不是一个字符串,这不是一个字符串,这不是一个字符串,重要的事情说三遍，可以理解为void*
	bool						m_bConnect;			// 连接正常吗
	int							m_nErrorCount;		// 接受失败次数，达到一定程度视为失败
};

