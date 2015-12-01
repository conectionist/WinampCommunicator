#pragma once

#include <Windows.h>
#include <string>

#include "Exceptions.h"

using std::string;

enum PlayingStatus
{
	INVALID,
	PLAYING,
	PAUSED,
	STOPPED
};

class WinampCommunicator
{
public:
	WinampCommunicator();
	~WinampCommunicator();
	
	void PreviousTrack();
	void Play();
	void Pause();
	void Stop();
	void NextTrack();
	long GetTrackLength();
	long GetPositionOfPlayback();

	PlayingStatus GetPlayingStatus();
	string GetPlayingStatusAsString();

	bool IsShuffleSet();
	void SetShuffle(bool b);
	bool IsRepeatSet();
	void SetRepeat(bool b);

	void RaiseVolume(UINT percent = 1);
	void LowerVolume(UINT percent = 1);
	void SetVolume(UINT percent);

	string GetCurrentTrackName();

protected:
	void ValidateWindowHandle();

protected:
	HWND m_hWinampWindowHandle;
};

