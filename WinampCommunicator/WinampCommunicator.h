#pragma once

#include <Windows.h>
#include <string>

#include "Exceptions.h"

using std::string;

enum PlayingStatus
{
	PLAYING,
	PAUSED,
	STOPPED
};

class WinampCommunicator
{
private:
	HWND hWinampWindowHandle;

public:
	WinampCommunicator();
	~WinampCommunicator();
	void Close();

	void PreviousTrack();
	void Play();
	void Pause();
	void Stop();
	void NextTrack();
	long GetTrackLength();
	long GetPositionOfPlayback();

	PlayingStatus GetPlayingStatus();

	bool IsShuffleSet();
	void SetShuffle(bool b);
	bool IsRepeatSet();
	void SetRepeat(bool b);

	string GetCurrentTrackName();

private:
	bool IsInitialized();
};

