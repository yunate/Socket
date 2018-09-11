#pragma once
#include "SocketHead.h"

class Dog_GolbalData;

class Dog_Server
{
private:
	Dog_Server();
	Dog_Server(const Dog_Server&);

public:
	~Dog_Server();

private:
	bool _Init();

public:
	bool Start();
	bool Stop();

	void SetPort(int nPort);
	void SetIp(unsigned long ulIp = INADDR_ANY);

private:
	int					m_nPort;
	unsigned long		m_ulIp;
	bool				m_bInit;
	SOCKET				m_hSocket;

private:
	static Dog_Server& GetIns()
	{
		static Dog_Server sIns;
		return sIns;
	}

	friend Dog_GolbalData;
};

