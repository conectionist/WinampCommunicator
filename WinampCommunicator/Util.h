#ifndef UTIL_H
#define UTIL_H
#include <string.h>

bool EndsWith(char* str, char* substr)
{
	char* temp = strstr(str,substr);

	return (temp != NULL && strlen(temp) == strlen(str + (temp - str)));
}

void RemoveWinampFromTitle(char* title)
{
	if(title == NULL)
		return;

	if(EndsWith(title," - Winamp"))
		title[strlen(title) - strlen(" - Winamp")] = '\0';
}

#endif