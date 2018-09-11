#include "LogTracerImpl.h"
#include <fstream>
#include <sstream>

#ifndef NDEBUG
#include <assert.h>
#endif

#define MAX_LOG_FILE_SIZE 10

LocalFileTracer::LocalFileTracer(std::string sFix/* = "log"*/)
	: m_sFileName(""), m_sFix(sFix)
{
	char exeFullPath[MAX_PATH];
	GetModuleFileNameA(NULL, exeFullPath, MAX_PATH);
	std::string strPath = exeFullPath;
	int pos = strPath.find_last_of('\\', strPath.length());
	m_sDirPath = strPath.substr(0, pos) + "\\log\\";
	CreateDirectoryA(m_sDirPath.c_str(), NULL);
	m_sDirPath = m_sDirPath + sFix + "\\";
	CreateDirectoryA(m_sDirPath.c_str(), NULL);
}

bool LocalFileTracer::Trace(ILog & log)
{
	std::string sPath = GetAvailableFile();
	FILE* pFile;
	if (fopen_s(&pFile, sPath.c_str(), "a"))
	{
		return false;
	}

	fprintf_s(pFile, log.GetLog().c_str());
	fclose(pFile);

	
#ifndef NDEBUG
	if (ILog::LOG_ERROR == log.GetLogLevel())
	{
		assert(1);
	}
#endif

	return true;
}

std::string LocalFileTracer::GetAvailableFile()
{
	CreateDirectoryA(m_sDirPath.c_str(), NULL);
	std::string sFullPath;
	std::string sLogIniFullPath = m_sDirPath + m_sFix + "-log.ini";

	while (1)
	{
		// 先找到日志配置文件ini
		DWORD ftyp = GetFileAttributesA(sLogIniFullPath.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
		{
			m_sFileName = "";
		}
		else
		{
			// 打开文件
			std::fstream fileStream(sLogIniFullPath);
			fileStream >> m_sFileName;
			fileStream.close();
			DeleteFileA(sLogIniFullPath.c_str());
		}

		if (0 == m_sFileName.length())
		{
			m_sFileName = "log-0.txt";
		}

		// 看看文件大小
		sFullPath = m_sDirPath + m_sFileName;
		struct _stat info;

		if (0 != _stat(sFullPath.c_str(), &info))
		{
			// 文件不存在就返回
			break;
		}

		int size = info.st_size >> 20;

		if (size >= MAX_LOG_FILE_SIZE)
		{
			// 文件过大，就在创建一个
			int nIndex = m_sFileName.find('-');
			std::string sPre = m_sFileName.substr(0, nIndex + 1);
			std::string sTail = m_sFileName.substr(nIndex + 1);
			std::stringstream sTmpStream;
			sTmpStream << sTail;
			int nTmp = 0;
			sTmpStream >> nTmp;
			sTmpStream.str("");
			sTmpStream << sPre << (++nTmp) << ".txt";
			m_sFileName = sTmpStream.str();
			sFullPath = m_sDirPath + m_sFileName;
			break;
		}

		break;
	}

	// 将配置写回去
	FILE* fp = 0;
	if (0 == fopen_s(&fp, sLogIniFullPath.c_str(), "a"))
	{
		fwrite(m_sFileName.c_str(), m_sFileName.length(), 1, fp);
		fclose(fp);
	}

	return sFullPath;
}
