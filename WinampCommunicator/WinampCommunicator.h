#pragma once

#include <Windows.h>
#include <string>

using std::string;

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
	void NextTrack();
	long GetTrackLength();
	long GetPositionOfPlayback();
	bool IsShuffleSet();
	string GetCurrentTrackName(); 
};

