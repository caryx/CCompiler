
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
	vector<CProduction> BuildLRItems();

	void FromCProduction(const CProduction& production, int index);	
	string nextElement();
	string prevElement();
	string toString();

    bool isLastItem();
    bool isFirstItem();
    CProduction nextItem();
    string prevToken();
    string nextToken();

    bool hasSameCore(const CProduction& prod);
    bool operator==(const CProduction& prod);
    bool operator!=(const CProduction& prod);

    string getTokenAfterNext();

	string store();
	void load(string& str);

public:
    int index;
    string name;
    vector<string> tokens;
    vector<string> comingTokens;
};


#endif

