#pragma once

#define DllExport   __declspec( dllexport )

#pragma warning (disable : 4251)

#include <string>
#include <thread>

using std::thread;
using std::string;

#define ALIVE (!IsShutdownSet())

class DllExport Runnable
{
public:
	Runnable(string sStopEventName);
	~Runnable();

	void Start();
	void Stop();

protected:
	virtual void Run() = 0;

protected:
	void SetShutdown();
	bool IsShutdownSet();

protected:
	thread m_thread;

	HANDLE m_hShutdownEvt;
};

