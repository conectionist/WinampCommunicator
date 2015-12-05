#ifndef UTIL_H
#define UTIL_H

#include <string>

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

#endif
