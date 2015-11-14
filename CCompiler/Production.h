
#ifndef _PRODUCTION_
#define _PRODUCTION_

#include <string>
#include <vector>
#include "Token.h"
#include "Item.h"
using namespace std;

class CProduction
{
public:
	CProduction(void);
	~CProduction(void);
	void FromString(const string& str);
	void BuildLRItems();

	void FromCProduction(const CProduction& production, int index);	
	string nextElement();
	string prevElement();
	string toString();

	int index;
	string name;
	vector<string> tokens;
	vector<CProduction> lrItems;
	vector<CProduction> lr_after;
	vector<CProduction> lr_before;
};


#endif

