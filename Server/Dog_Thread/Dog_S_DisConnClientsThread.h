#pragma once
#include "Dog_Thread_Base.hpp"

class Dog_S_DisConnClientsThread : public Dog_Thread_Base
{
public:
	Dog_S_DisConnClientsThread();
	virtual ~Dog_S_DisConnClientsThread();


public:
	virtual void InitDes();

private:
	virtual void _Run();
};