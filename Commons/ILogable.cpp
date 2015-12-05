#include "ILogable.h"
#include "Shlwapi.h"
#include <fstream>

using std::fstream;

#pragma comment(lib, "Shlwapi.lib")

ILogable::ILogable(string sLogPath)
{
	m_sLogPath = sLogPath;
}

ILogable::~ILogable()
{
}

void ILogable::Log(string message)
{
	fstream f;

	f.open(m_sLogPath, std::ios_base::app);

	if (f.is_open())
	{
		f << message << std::endl;
		f.close();
	}
}
