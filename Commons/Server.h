#pragma once

#include "Runnable.h"
#include "Exceptions.h"
#include "ILogable.h"

#define DllExport   __declspec( dllexport )

class DllExport Server : public Runnable, public ILogable
{
public:
	Server(int port, string sShutdownEventName, string sLogPath, int nMaxConnections = 1);
	~Server();

protected:
	void Run();
	void HandleIncomingConnections();
	bool WaitForNewClient();
	void ReceiveMessage();
	virtual void HandleReceivedMessage(string message) = 0;
	
protected:
	int m_nPort;
};

