#pragma once

#include "Server.h"

class WinampCommunicator;

enum WinampCommand
{
	WinampCmd_Invalid,
	WinampCmd_Previous,
	WinampCmd_Play,
	WinampCmd_Pause,
	WinampCmd_Stop,
	WinampCmd_Next
};

class WinampRequestListener : public Server
{
public:
	WinampRequestListener();
	~WinampRequestListener();

	void HandleReceivedMessage(string message);

	WinampCommand TranslateReceivedMessageIntoCommand(string message);

protected:
	WinampCommunicator* m_pWinampCommunicator;
};

