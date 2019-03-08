// FileTranser.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <Windows.h>

#include "Tools/TimerRecorder.h"

#include "MainFrame.h"

#define FPS 100

int main()
{
	int nMillonSecPreFrame = 1000 / FPS;
	MainFrame mainFrame;

	while (true)
	{
		TimerRecorder timer;

		{
			mainFrame.OnFrame();
		}

		int nSleep = nMillonSecPreFrame - timer.GetTimePass();

		if (nSleep > 0)
		{
			Sleep(nSleep);
		}
		else
		{
			// ������
		}
	}
    return 0;
}

