#include <stdio.h>
#include "WinampCommunicator.h"
//#include "Util.h"

int main()
{
	//printf("Hello World\n");
	WinampCommunicator winampCom;
	
	if(!winampCom.Init())
	{
		printf("Wimamp window not found. Please start (re)winamp\n");
	}
	else
	{
		printf("Winamp window handle successfully found. Let's give some commands :D\n");
		//winampCom.PreviousTrack();
		//printf("%d\n",winampCom.GetTrackLength());
		char* currentTrackTitle = winampCom.GetCurrentTrackName();
		printf("Currently playing: %s\n",currentTrackTitle);
		delete [] currentTrackTitle;
		/*if(EndsWith("dark horse - katy perry - Winamp"," - Winamp"))
			printf("Ends with\n");
		else
			printf("Doesn't end with\n");*/
		winampCom.Close();
	}
	

	return 0;
}