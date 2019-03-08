#pragma once

#include "MemoryShare/MemoryShare.h"

class MainFrame
{
public:
	MainFrame();
	~MainFrame();

	bool OnFrame();

private:
	bool CheckShareMem();
	void AnalyzeBuff(void * buff, int nBuffSize);

private:
	MemoryShare *	m_pMemShare;
};
