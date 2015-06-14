#include "WinampCommunicator.h"
#include "WinampWindowMessages.h"
#include "Util.h"

WinampCommunicator::WinampCommunicator()
{
	hWinampWindowHandle = NULL;
}

WinampCommunicator::~WinampCommunicator()
{
	hWinampWindowHandle = NULL;
}

bool WinampCommunicator::IsInitialized()
{
	hWinampWindowHandle = FindWindow("Winamp v1.x",NULL);
	
	return hWinampWindowHandle != NULL;
}

PlayingStatus WinampCommunicator::GetPlayingStatus()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	LRESULT lResult = SendMessage(hWinampWindowHandle, WM_USER, 1, WM_USER_GET_PLAYING_STATUS);
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

void WinampCommunicator::PreviousTrack()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle,WM_COMMAND,WPARAM_PREVIOUS_TRACK,0);
}

void WinampCommunicator::Play()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle, WM_COMMAND, WPARAM_PLAY_TRACK, 0);
}

void WinampCommunicator::Pause()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle, WM_COMMAND, WPARAM_PAUSE_TRACK, 0);
}

void WinampCommunicator::Stop()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle, WM_COMMAND, WPARAM_STOP_TRACK, 0);
}

void WinampCommunicator::NextTrack()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle,WM_COMMAND,WPARAM_NEXT_TRACK,0);
}

/*gets the track length in seconds*/
long WinampCommunicator::GetTrackLength()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	return SendMessage(hWinampWindowHandle, WM_USER, 1, WM_USER_GET_POSITION_OR_LENGTH);
}

/* get the position of the current playback
   example:
   if current track that is playing/paused is at 1:27 (1 minute 27 seconds)
   the function will return 87000 (miliseconds) (87 = 1 * 60 + 27 seconds) 
*/
long WinampCommunicator::GetPositionOfPlayback()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	return SendMessage(hWinampWindowHandle, WM_USER, 0, WM_USER_GET_POSITION_OR_LENGTH);
}

bool WinampCommunicator::IsShuffleSet()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	return SendMessage(hWinampWindowHandle, WM_USER, 0, WM_USER_GET_SHUFFLE) ? true : false;
}

void WinampCommunicator::SetShuffle(bool b)
{
	if(!IsInitialized())
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle, WM_USER, (b ? 1 : 0), WM_USER_SET_SHUFFLE);
}

bool WinampCommunicator::IsRepeatSet()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	return SendMessage(hWinampWindowHandle, WM_USER, 0, WM_USER_GET_REPEAT) ? true : false;
}

void WinampCommunicator::SetRepeat(bool b)
{
	if(!IsInitialized())
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle, WM_USER, (b ? 1 : 0), WM_USER_SET_REPEAT);
}

string WinampCommunicator::GetCurrentTrackName()
{
	if(!IsInitialized())
		throw NotInitilizedException();

	char* trackName = new char[256];
	GetWindowText(hWinampWindowHandle,trackName,256);
	RemoveWinampFromTitle(trackName);
	return trackName;
}
