#include "Runnable.h"
#include "Windows.h"

Runnable::Runnable(string sStopEventName)
{
	m_hShutdownEvt = CreateEventA(NULL, TRUE, FALSE, sStopEventName.c_str());

	if (m_hShutdownEvt == NULL)
	{
		throw GetLastError();
	}
}

Runnable::~Runnable()
{
	if (m_hShutdownEvt)
	{
		CloseHandle(m_hShutdownEvt);
		m_hShutdownEvt = NULL;
	}
}

void Runnable::Start()
{
	m_thread = thread(&Runnable::Run, this);
}

void Runnable::Stop()
{
	SetShutdown();

	if (m_thread.joinable())
		m_thread.join();
}

void Runnable::SetShutdown()
{
	SetEvent(m_hShutdownEvt);
}

bool Runnable::IsShutdownSet()
{
	return WaitForSingleObject(m_hShutdownEvt, 0) != WAIT_TIMEOUT;
}
