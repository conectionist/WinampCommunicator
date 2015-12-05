#pragma once

#include "ServiceBase.h"

class WinampRequestListener;

class WinampService : public CServiceBase
{
public:

    WinampService(PWSTR pszServiceName, 
        BOOL fCanStop = TRUE, 
        BOOL fCanShutdown = TRUE, 
        BOOL fCanPauseContinue = FALSE);
    virtual ~WinampService(void);

protected:

    virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);
    virtual void OnStop();

	WinampRequestListener* m_pWinampRequestListener;

private:

    BOOL m_fStopping;
    HANDLE m_hStoppedEvent;
};