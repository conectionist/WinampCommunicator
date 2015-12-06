#define DLLEXPORT __declspec(dllexport)

#include "WinampCommunicator.h"

extern "C"
{
	DLLEXPORT void PreviousTrack();
	DLLEXPORT void Play();
	DLLEXPORT void Pause();
	DLLEXPORT void Stop();
	DLLEXPORT void NextTrack();

	DLLEXPORT void RaiseVolume(UINT percent = 1);
	DLLEXPORT void LowerVolume(UINT percent = 1);
	DLLEXPORT void SetVolume(UINT percent);

	DLLEXPORT char* GetCurrentTrackName();
}