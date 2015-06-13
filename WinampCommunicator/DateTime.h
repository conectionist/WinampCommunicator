#pragma once

#include <string>

using std::string;

class DateTime
{
public:
	DateTime(void);
	DateTime(unsigned int _hours, unsigned int _minutes, unsigned int _seconds);
	~DateTime(void);

	void SetDate(const DateTime& dt);
	void SetDate(long miliseconds);
	string ToString();

private:
	unsigned int seconds;
	unsigned int minutes;
	unsigned int hours;
};

