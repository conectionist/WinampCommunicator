#include "WinampRequestListener.h"
#include "WinampCommunicator.h"

WinampRequestListener::WinampRequestListener() : Server(4567, "Winamp_Server_Shutdown_Event", "D:\\winamp_service_logs.txt")
{
	Log("========== Winamp service has started ==========");

	m_pWinampCommunicator = new WinampCommunicator;
}

WinampRequestListener::~WinampRequestListener()
{
	Log("========== Winamp service has stopped ==========");

	delete m_pWinampCommunicator;
}

void WinampRequestListener::HandleReceivedMessage(string msg)
{
	// remove the trailing new line
	msg.erase(msg.end() - 1);

	WinampCommand cmd = TranslateReceivedMessageIntoCommand(msg);

	try
	{
		switch (cmd)
		{
		case WinampCmd_Previous:
			m_pWinampCommunicator->PreviousTrack();
			break;
		case WinampCmd_Play:
			m_pWinampCommunicator->Play();
			break;
		case WinampCmd_Pause:
			m_pWinampCommunicator->Pause();
			break;
		case WinampCmd_Stop:
			m_pWinampCommunicator->Stop();
			break;
		case WinampCmd_Next:
			m_pWinampCommunicator->NextTrack();
			break;
		case WinampCmd_Invalid:
		default:
			Log("Unknown command: >>>" + msg + "<<<");
			break;
		}
	}
	catch (const NotRunningException& ex)
	{
		Log(ex.GetErrorMessage());
	}
}

WinampCommand WinampRequestListener::TranslateReceivedMessageIntoCommand(string msg)
{
	if (msg == "z")
		return WinampCmd_Previous;
	else if (msg == "x")
		return WinampCmd_Play;
	else if (msg == "c")
		return WinampCmd_Pause;
	else if (msg == "v")
		return WinampCmd_Stop;
	else if (msg == "b")
		return WinampCmd_Next;
	else
		return WinampCmd_Invalid;
}
