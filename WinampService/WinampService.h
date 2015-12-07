#pragma once

#include "ServiceBase.h"

class WinampRequestListener;

class WinampService : public CServiceBase
{
public:

    WinampService(PSTR pszServiceName, 
        BOOL fCanStop = TRUE, 
        BOOL fCanShutdown = TRUE, 
        BOOL fCanPauseContinue = FALSE);
    virtual ~WinampService(void);

protected:

    virtual void OnStart(DWORD dwArgc, PSTR *pszArgv);
    virtual void OnStop();

	WinampRequestListener* m_pWinampRequestListener;
};