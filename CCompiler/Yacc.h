#ifndef _YACC
#define _YACC

#include <vector>
#include <map>
#include "item.h"
#include "Production.h"
using namespace std;

class CYacc
{
public:
	CYacc(void);
	~CYacc(void);

private:
	void Init();
	void InitProduction();
	void InitItems();
	//vector<CProduction> lrItems;
	vector<CProduction> productionVec;
	map<string, CProduction> productionNameMap;
};

#endif
