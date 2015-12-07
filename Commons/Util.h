#ifndef UTIL_H
#define UTIL_H

#include <string>

#include <tlhelp32.h>

#include "Exceptions.h"

inline bool EndsWith(std::string const & value, std::string const & ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void RemoveWinampFromTitle(string& title)
{
	if(title.size() == 0)
		return;

	if(EndsWith(title," - Winamp"))
		title.erase(title.size() - strlen(" - Winamp"));
}

void EnableDebugPriv()
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkp;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = luid;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);

	CloseHandle(hToken);
}


HANDLE GetHandleToProcess(string sProcessName)
{
	EnableDebugPriv();

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (entry.szExeFile == sProcessName)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

				CloseHandle(snapshot);
				return hProcess;
			}
		}
	}

	CloseHandle(snapshot);
	return NULL;
}

void ImpersonateCurrentUser(void (*executorFunction)(void))
{
	// Handle to token
	HANDLE hToken;

	HANDLE hExplorer = GetHandleToProcess("explorer.exe");
	if (hExplorer == NULL)
	{
		throw Win32Exception("GetHandleToProcess", GetLastError(), "Could not get handle to explorer.");
	}

	// Open a handle to the access token for the calling process that is the currently login access token
	if (!OpenProcessToken(hExplorer, TOKEN_ALL_ACCESS, &hToken))
	{
		CloseHandle(hExplorer);
		throw Win32Exception("OpenProcessToken", GetLastError(), "Getting the handle to access token failed.");
	}

	CloseHandle(hExplorer);

	// Lets the calling process impersonate the security context of a logged-on user.
	if (!ImpersonateLoggedOnUser(hToken))
	{
		throw Win32Exception("ImpersonateLoggedOnUser", GetLastError());
	}

	(*executorFunction)();

	// Terminates the impersonation of a client.
	RevertToSelf();

	// Close the handle
	CloseHandle(hToken);
}

#endif
