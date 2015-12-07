#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

class BaseException
{
public:
	BaseException(string _message)
	{
		m_message = _message;
	}

	string GetErrorMessage() const
	{
		return m_message;
	}

protected:
	string m_message;
};

class NotRunningException : public BaseException
{
public:
	NotRunningException() : BaseException("Winamp is not running")
	{}
};

class InexistantPathException : public BaseException
{
public:
	InexistantPathException(string path) : BaseException("Path does not exist: " + path)
	{}
};

class Win32Exception : public BaseException
{
	static string buildMessage(string operation, int errCode, string
		sAdditionalInfo)
	{
		string message;
		message += "Operation \"" + operation + "\" failed with error code ";
		message += std::to_string(errCode);

		if (!sAdditionalInfo.empty())
			message += "\nAdditional info: " + sAdditionalInfo;
		return message;
	}

public:
	Win32Exception(string operation, int errCode, string sAdditionalInfo = "") :
		BaseException(buildMessage(operation, errCode, sAdditionalInfo))
	{
	}
};

#endif
