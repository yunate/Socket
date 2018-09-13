#pragma once
#include <sstream>
#include <string>
#include <list>

#include "Cmd.hpp"


/*****************************--数据包打包解包工具--********************************
	1、使用1E\1F 作为开始\结束标记，如果数据中出现这个的话用/1E\/1F表示
*/

class DataPackageTools
{
private:
	enum 
	{
		ESCAPE_CHAR = 0x1D,		// 转义字符
		BEGIN_FLAG	= 0x1E,		// 开始
		END_FLAG	= 0x1F,		// 结束
	};

public:
	DataPackageTools() {};
	~DataPackageTools() {};

public:
	// 这个的性能问题就不考虑了，毕竟这个发数据的速度慢一点也没什么大不了的
	std::string Package(Cmd::CmdType nType, const unsigned char* cBuffs, size_t nSize);

	// 解包，注意他会改变cBuffs
	// TODO:另外，关于性能问题留作以后考虑
	std::list<std::string> UnPackage(unsigned char* cBuffs, size_t nSize, size_t& nOutSize);
	std::list<std::string> UnPackage(std::string& sBuff);

};