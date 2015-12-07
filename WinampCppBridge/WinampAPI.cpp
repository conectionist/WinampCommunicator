#include "WinampAPI.h"

// !!! DON'T FORGET TO ADD EXCEPTION HANDLING IN EACH FUNCTION NEXT TIME !!!
// if winamp is not running, any of the following functions will cause the application to crash

extern "C"
{
	DLLEXPORT void PreviousTrack()
	{
		WinampCommunicator comm;
		comm.PreviousTrack();
	}

	DLLEXPORT void Play()
	{
		WinampCommunicator comm;
		comm.Play();
	}

	DLLEXPORT void Pause()
	{
		WinampCommunicator comm;
		comm.Pause();
	}

	DLLEXPORT void Stop()
	{
		WinampCommunicator comm;
		comm.Stop();
	}

	DLLEXPORT void NextTrack()
	{
		WinampCommunicator comm;
		comm.NextTrack();
	}

	DLLEXPORT void RaiseVolume(UINT percent /*= 1*/)
	{
		WinampCommunicator comm;
		comm.RaiseVolume(percent);
	}

	DLLEXPORT void LowerVolume(UINT percent /*= 1*/)
	{
		WinampCommunicator comm;
		comm.LowerVolume(percent);
	}

	DLLEXPORT void SetVolume(UINT percent)
	{
		WinampCommunicator comm;
		comm.SetVolume(percent);
	}

	DLLEXPORT char* GetCurrentTrackName()
	{
		WinampCommunicator comm;
		string sTrackName = comm.GetCurrentTrackName();
		UINT size = sTrackName.length();

		/* you must use CoTaskMemAlloc to allocate the memory, not malloc, new, or anything else */		
		char* returnedString = (char*)CoTaskMemAlloc(size + 1);
		ZeroMemory(returnedString, size + 1);

		for (UINT i = 0; i < size; i++)
			returnedString[i] = sTrackName[i];

		return returnedString;
	}
}