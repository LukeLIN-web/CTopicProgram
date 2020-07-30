#include "myTime.h"

#include <stdio.h>

void getID(char* str)
{
	struct tm* local;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	sprintf(str, "%02d%02d%02d%02d%02d%02d\0", local->tm_year % 100, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
}