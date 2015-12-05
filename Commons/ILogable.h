#pragma once

#define DllExport   __declspec( dllexport )

#pragma warning (disable : 4251)

#include "Exceptions.h"
#include <string>

using std::string;

class DllExport ILogable
{
public:
	ILogable(string sLogPath);
	~ILogable();

	void Log(string message);

protected:
	string m_sLogPath;
};
