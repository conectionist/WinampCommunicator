#include <stdio.h>
#include "DateTime.h"
#include "WinampCommunicator.h"

//#include "Util.h"

int main()
{
	WinampCommunicator winampCom;
	
	if(!winampCom.Init())
	{
		printf("Winamp window not found. Please start (re)winamp\n");
	}
	else
	{
		printf("Winamp window handle successfully found. Let's give some commands :D\n");
		
		int i = 0;
		DateTime totalLen, curPos;

		while(true)
		{
			system("cls");
			totalLen.SetDate(winampCom.GetTrackLength());
			curPos.SetDate(winampCom.GetPositionOfPlayback()/1000);
			
			printf("Currently playing: %s\n", winampCom.GetCurrentTrackName().c_str());
			printf("Track at: %s/%s\n", curPos.ToString().c_str(), totalLen.ToString().c_str());

			Sleep(1000);

			if(i++ % 10 == 0)
				winampCom.NextTrack();
		}
	}
	

	return 0;
}