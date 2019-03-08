
#include "MemoryShare.h"

#define  BUF_SIZE 100
#define  FLAG 1

MemoryShare::MemoryShare(const std::string & sShareName)
{
	m_hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,     // �����ļ����
		NULL,                     // Ĭ�ϰ�ȫ����
		PAGE_READWRITE,           // �ɶ���д
		0,                        // ��λ�ļ���С
		BUF_SIZE + 1,             // ��λ�ļ���С,�����һ�������ж��Ƿ�׼����ȥ����д
		sShareName.c_str()        // �����ڴ����ƣ���ΪNULL
	);

	// ӳ�仺������ͼ , �õ�ָ�����ڴ��ָ��
	m_lpBase = MapViewOfFile(
		m_hMapFile,               // �����ڴ�ľ��
		FILE_MAP_ALL_ACCESS,      // �ɶ�д���
		0,                        // ��λƫ����
		0,                        // ��λƫ����
		BUF_SIZE + 1              // Ҫӳ����ֽ���
	);

}

MemoryShare::~MemoryShare()
{
	UnmapViewOfFile(m_lpBase);
	m_lpBase = NULL;

	// �ر��ڴ�ӳ���ļ�������
	CloseHandle(m_hMapFile);
	m_hMapFile = INVALID_HANDLE_VALUE;
}

bool MemoryShare::Write(void * pBuf, int nSize)
{
	if (0 == m_lpBase || nSize > BUF_SIZE)
	{
		return false;
	}

	memcpy(m_lpBase, pBuf, nSize);
	char cTmp = FLAG;
	memcpy(m_lpBase, &cTmp, 1);

	return true;
}

bool MemoryShare::Read(void * pBuf)
{
	if (0 == m_lpBase)
	{
		return false;
	}

	memcpy(pBuf, m_lpBase, BUF_SIZE);
	return true;
}

bool MemoryShare::Clear()
{
	if (0 == m_lpBase)
	{
		return false;
	}

	memset(m_lpBase, 0, BUF_SIZE + 1);
	return true;
}

bool MemoryShare::IsReadToWrite()
{
	if (0 == m_lpBase)
	{
		return false;
	}

	char * cTmp = (((char *)m_lpBase) + BUF_SIZE);

	if (0 == (*cTmp))
	{
		return true;
	}

	return false;
}

bool MemoryShare::IsReadToRead()
{
	if (0 == m_lpBase)
	{
		return false;
	}

	char * cTmp = (((char *)m_lpBase) + BUF_SIZE);

	if (FLAG == (*cTmp))
	{
		return true;
	}

	return false;
}

int MemoryShare::GetBuffSize()
{
	return BUF_SIZE;
}
