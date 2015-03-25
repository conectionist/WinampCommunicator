#pragma once

#include <Windows.h>

class WinampCommunicator
{
private:
	HWND hWinampWindowHandle;
	bool initialized;

public:
	WinampCommunicator(void);
	~WinampCommunicator(void);
	bool Init();
	void Close();

	void PreviousTrack();
	long GetTrackLength();
	long GetPositionOfPlayback();
	bool IsShuffleSet();
	char* GetCurrentTrackName(); 
};

