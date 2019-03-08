#pragma once

class ITask
{
public:
	ITask() {}
	virtual ~ITask() {}

	virtual bool DoTask() = 0;
};