
#include "Log.h"

int CLog::filterLevel = 0;

CLog::CLog(void)
{
	filterLevel = 3;
}

CLog::~CLog(void)
{
}

void CLog::Log(int level, string str)
{
	if (filterLevel <= level)
	{
		printf("%s\n", str.c_str());
	}
}
