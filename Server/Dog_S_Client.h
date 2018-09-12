#pragma once

#include "SocketHead.h"
#include <sstream>

/*
	�������˹�����client����S_��ͷ��ʾ����
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
	SOCKET						m_hClient;			// socket���
	sockaddr_in					m_Address;			// ��ַ
	std::stringstream			m_sStrBuff;			// ���������ݻ���
	bool						m_bConnect;			// ����������
	int							m_nErrorCount;		// ����ʧ�ܴ������ﵽһ���̶���Ϊʧ��
};
