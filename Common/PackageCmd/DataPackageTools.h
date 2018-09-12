#pragma once
#include <sstream>
#include <string>
#include <list>


/*****************************--���ݰ�����������--********************************
	1��ʹ��1E\1F ��Ϊ��ʼ\������ǣ���������г�������Ļ���/1E\/1F��ʾ
*/

class DataPackageTools
{
private:
	enum 
	{
		ESCAPE_CHAR = 0x1D,		// ת���ַ�
		BEGIN_FLAG	= 0x1E,		// ��ʼ
		END_FLAG	= 0x1F,		// ����
	};

public:
	DataPackageTools() {};
	~DataPackageTools() {};

public:
	// �������������Ͳ������ˣ��Ͼ���������ݵ��ٶ���һ��Ҳûʲô���˵�
	std::string Package(const char* cBuffs, size_t nSize);

	// �����ע������ı�cBuffs
	// TODO:���⣬�����������������Ժ���
	std::list<std::string> UnPackage(char* cBuffs, size_t nSize, size_t& nOutSize);
	std::list<std::string> UnPackage(std::string& sBuff);

};