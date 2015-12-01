#include "WinampCommunicator.h"
#include "WinampWindowMessages.h"
#include "Util.h"

WinampCommunicator::WinampCommunicator()
{
	m_hWinampWindowHandle = NULL;
}

WinampCommunicator::~WinampCommunicator()
{
	m_hWinampWindowHandle = NULL;
}

PlayingStatus WinampCommunicator::GetPlayingStatus()
{
	ValidateWindowHandle();

	LRESULT lResult = SendMessage(m_hWinampWindowHandle, WM_USER, 1, WM_USER_GET_PLAYING_STATUS);
	switch(lResult)
	{
	case 1:
		return PLAYING;
		break;
	case 3:
		return PAUSED;
		break;
	default:
		return STOPPED;
	}
}

string WinampCommunicator::GetPlayingStatusAsString()
{
	PlayingStatus playingStatus = GetPlayingStatus();

	switch(playingStatus)
	{
	case PLAYING:
		return "playing";
	case PAUSED:
		return "paused";
	case STOPPED:
		return "stopped";
	default:
		return "N/A";
	}
}

void WinampCommunicator::PreviousTrack()
{
	ValidateWindowHandle();

	SendMessage(m_hWinampWindowHandle,WM_COMMAND,WPARAM_PREVIOUS_TRACK,0);
}

void WinampCommunicator::Play()
{
	ValidateWindowHandle();

	SendMessage(m_hWinampWindowHandle, WM_COMMAND, WPARAM_PLAY_TRACK, 0);
}

void WinampCommunicator::Pause()
{
	ValidateWindowHandle();

	SendMessage(m_hWinampWindowHandle, WM_COMMAND, WPARAM_PAUSE_TRACK, 0);
}

void WinampCommunicator::Stop()
{
	ValidateWindowHandle();

	SendMessage(m_hWinampWindowHandle, WM_COMMAND, WPARAM_STOP_TRACK, 0);
}

void WinampCommunicator::NextTrack()
{
	ValidateWindowHandle();

	SendMessage(m_hWinampWindowHandle,WM_COMMAND,WPARAM_NEXT_TRACK,0);
}

/*gets the track length in seconds*/
long WinampCommunicator::GetTrackLength()
{
	ValidateWindowHandle();

	return SendMessage(m_hWinampWindowHandle, WM_USER, 1, WM_USER_GET_POSITION_OR_LENGTH);
}

/* get the position of the current playback
   example:
   if current track that is playing/paused is at 1:27 (1 minute 27 seconds)
   the function will return 87000 (miliseconds) (87 = 1 * 60 + 27 seconds) 
*/
long WinampCommunicator::GetPositionOfPlayback()
{
	ValidateWindowHandle();

	return SendMessage(m_hWinampWindowHandle, WM_USER, 0, WM_USER_GET_POSITION_OR_LENGTH);
}

bool WinampCommunicator::IsShuffleSet()
{
	ValidateWindowHandle();

	return SendMessage(m_hWinampWindowHandle, WM_USER, 0, WM_USER_GET_SHUFFLE) ? true : false;
}

void WinampCommunicator::SetShuffle(bool b)
{
	ValidateWindowHandle();

	SendMessage(m_hWinampWindowHandle, WM_USER, (b ? 1 : 0), WM_USER_SET_SHUFFLE);
}

bool WinampCommunicator::IsRepeatSet()
{
	ValidateWindowHandle();

	return SendMessage(m_hWinampWindowHandle, WM_USER, 0, WM_USER_GET_REPEAT) ? true : false;
}

void WinampCommunicator::SetRepeat(bool b)
{
	ValidateWindowHandle();

	SendMessage(m_hWinampWindowHandle, WM_USER, (b ? 1 : 0), WM_USER_SET_REPEAT);
}

/* 
 * Sets the volume percentage
 * must be between 0 and 100
 * UINT ensures value is positive (at least 0)
 * if received value is higher than 100, it is set to 100
 */
void WinampCommunicator::SetVolume(UINT percent)
{
	ValidateWindowHandle();

	if (percent > 100)
		percent = 100;

	SendMessage(m_hWinampWindowHandle, WM_USER, percent *  255 / 100 , WM_USER_SET_VOLUME);
}

string WinampCommunicator::GetCurrentTrackName()
{
	ValidateWindowHandle();

	char trackName[256];
	GetWindowTextA(m_hWinampWindowHandle,trackName,256);

	string sTrackName = trackName;

	RemoveWinampFromTitle(sTrackName);

	return sTrackName;
}

void WinampCommunicator::ValidateWindowHandle()
{
	if(m_hWinampWindowHandle == NULL || !IsWindow(m_hWinampWindowHandle))
	{
		m_hWinampWindowHandle = FindWindowA("Winamp v1.x",NULL);
	}

	if(m_hWinampWindowHandle == NULL)
		throw NotRunningException();
}
