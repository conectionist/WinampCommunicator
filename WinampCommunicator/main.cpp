#include "DateTime.h"
#include "WinampCommunicator.h"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
	WinampCommunicator winampCom;
	DateTime totalLen, curPos;
	long trackLen = -1;
	PlayingStatus playingStatus;

	while(true)
	{
		system("cls");

		try
		{
			trackLen = winampCom.GetTrackLength();
			totalLen.SetDate(trackLen > 0 ? trackLen : 0);
			curPos.SetDate(winampCom.GetPositionOfPlayback()/1000);
			playingStatus = winampCom.GetPlayingStatus();

			switch(playingStatus)
			{
			case PLAYING:
				cout << "Winamp is playing...\n";
				break;
			case PAUSED:
				cout << "Winamp is paused...\n";
				break;
			case STOPPED:
				cout << "Winamp is stopped...\n";
				break;
			}
			
			cout << "Current track: " << winampCom.GetCurrentTrackName() << endl;
			cout << "Track at: " << curPos.ToString() << "/" << totalLen.ToString() << endl;
			cout << "Shuffle is " << (winampCom.IsShuffleSet() ? "" : "not ") << "set\n";
			cout << "Repeat is "  << (winampCom.IsRepeatSet() ? "" : "not ") << "set\n";
		}
		catch(const NotRunningException& nrEx)
		{
			cout << nrEx.GetErrorMessage() << endl;
		}

		Sleep(1000);
	}

	return 0;
}
