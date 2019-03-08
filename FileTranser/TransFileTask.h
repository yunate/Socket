#pragma once
#include <string>

#include "PackageCmd/Cmd.hpp"

#include "TaskBase.h"

class TransFileTask : public TaskBase
{
public:
	TransFileTask(TaskType nType, const Cmd::FileTrans & transInfo);
	~TransFileTask();

	virtual bool DoTask();

private:
	std::string				m_sIp;
	unsigned short			m_nPort;
	int						m_nId;
};
