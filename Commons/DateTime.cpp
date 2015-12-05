#include "DateTime.h"


DateTime::DateTime(void)
{
}

DateTime::DateTime(unsigned int _hours, unsigned int _minutes, unsigned int _seconds)
{
	hours = _hours;
	minutes = _minutes;
	seconds = _seconds;
}

DateTime::~DateTime(void)
{
}

void DateTime::SetDate(const DateTime& dt)
{
	unsigned int minutesCarry = 0;
	unsigned int hoursCarry = 0;

	seconds = dt.seconds % 60;

	minutesCarry = dt.seconds / 60;
	minutes = dt.minutes + minutesCarry;

	hoursCarry = minutes / 60;

	minutes %= 60;

	hours = dt.hours + hoursCarry;
}

void DateTime::SetDate(long miliseconds)
{
	SetDate(DateTime(0,0,miliseconds));
}

string DateTime::ToString()
{
	string secs = std::to_string(seconds);
	secs = (secs.length() == 1 ? "0" : "") + secs;

	string mins = std::to_string(minutes);
	mins = (mins.length() == 1 ? "0" : "") + mins;

	string hrs = std::to_string(hours);
	hrs = (hrs.length() == 1 ? "0" : "") + hrs;

	return hrs + ":" + mins + ":" + secs;
}