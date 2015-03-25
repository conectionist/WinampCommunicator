#include "WinampCommunicator.h"
#include "Exceptions.h"
#include "WinampWindowMessages.h"
#include "Util.h"
//#include <stdio.h>

WinampCommunicator::WinampCommunicator(void) : initialized(false)
{
	hWinampWindowHandle = NULL;
}

WinampCommunicator::~WinampCommunicator(void)
{
	/*if(hWinampWindowHandle != NULL)
	{
		CloseHandle(hWinampWindowHandle);
		hWinampWindowHandle = NULL;
	}*/
}



bool WinampCommunicator::Init()
{
	hWinampWindowHandle = FindWindow("Winamp v1.x",NULL);
	
	// if handle is null, then initialized will be false
	initialized = !(hWinampWindowHandle == NULL);

	return initialized;
}

void WinampCommunicator::Close()
{
	hWinampWindowHandle = NULL;
	initialized = false;
}

void WinampCommunicator::PreviousTrack()
{
	if(!initialized)
		throw NotInitilizedException();

	SendMessage(hWinampWindowHandle,WM_COMMAND,WPARAM_PREVIOUS_TRACK,0);
}

long WinampCommunicator::GetTrackLength()
{
	if(!initialized)
		throw NotInitilizedException();

	return SendMessage(hWinampWindowHandle,WM_USER,1,105);
}

/* get the position of the current playback
   example:
   if current track that is playing/paused is at 1:27 (1 minute 27 seconds)
   the function will return 87000 (miliseconds) (87 = 1 * 60 + 27 seconds) 
*/
long WinampCommunicator::GetPositionOfPlayback()
{
	if(!initialized)
		throw NotInitilizedException();

	return SendMessage(hWinampWindowHandle,WM_USER,0,105);
}

bool WinampCommunicator::IsShuffleSet()
{
	LRESULT lResult = 0;
	lResult = SendMessage(hWinampWindowHandle,WM_USER,0,250);

	return lResult ? true : false;
}

char* WinampCommunicator::GetCurrentTrackName()
{
	char* trackName = new char[256];
	GetWindowText(hWinampWindowHandle,trackName,256);
	RemoveWinampFromTitle(trackName);
	return trackName;
}