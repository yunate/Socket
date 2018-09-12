#pragma once
#include "SocketHead.h"

class Dog_Server
{
public:
	Dog_Server(int nPort);
	~Dog_Server();

public:
	bool			Init();
	void			UnInit();
	SOCKET			Accept(sockaddr_in *addr, int *addrlen);;

private:
	int					m_nPort;
	SOCKET				m_hSocket;
};

