#ifndef _LOG_
#define _LOG_
#include <string>
using namespace std;
class CLog
{
public:
	CLog(void);
	~CLog(void);
	static int filterLevel;
	static void Log(int level, string str);
};


#endif

