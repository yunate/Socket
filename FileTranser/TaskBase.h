#pragma once

#include "Task/ITask.h"


/////////////////////////////TaskType/////////////////////////////////////////////
enum TaskType
{
	TT_BEGIN = 0,
	TT_TRANSFILE,
	TT_END
};

/////////////////////////////TaskBase/////////////////////////////////////////////
class TaskBase : public ITask
{
public:
	TaskBase(TaskType nType);
	~TaskBase();

	virtual bool DoTask();

public:
	inline TaskType GetType()
	{
		return m_nType;
	}

private:
	TaskType		m_nType;
};
