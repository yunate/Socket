#pragma once

#include "SocketHead.h"
#include <list>

/*
	�������˹����client����S_��ͷ��ʾ����
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

	// TODO:����ʹ����ֵ���ʽ�Ż�
	std::list<std::string>		AnayzeBuff();

private:
	void OnDisConnect();

private:
	SOCKET						m_hClient;			// socket���
	sockaddr_in					m_Address;			// ��ַ
	std::string					m_sStrBuff;			// ���������ݻ���,�ⲻ��һ���ַ���,�ⲻ��һ���ַ���,�ⲻ��һ���ַ���,��Ҫ������˵���飬�������Ϊvoid*
	bool						m_bConnect;			// ����������
	int							m_nErrorCount;		// ����ʧ�ܴ������ﵽһ���̶���Ϊʧ��
};

