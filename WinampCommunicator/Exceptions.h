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
	std::string m_message;
};

class NotRunningException : public BaseException
{
public:
	NotRunningException() : BaseException("Winamp is not running")
	{}
};