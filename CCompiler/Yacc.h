#ifndef _YACC
#define _YACC

#include "GotoAction.h"
#include "YaccState.h"
#include <unordered_set>
#include <vector>
#include <map>
#include "item.h"
#include "Lex.h"
#include "Production.h"
using namespace std;

class CYacc
{
public:
	CYacc(void);
	~CYacc(void);
    void processToken(CLex lex);

    vector<CProduction> CYacc::GetAfterItems(CProduction& lastLri);
    vector<CProduction> CYacc::GetBeforeItems(CProduction& lastLri);
    void CYacc::getFullState(YaccState& state);

    vector<string> getFirstSet(const string token);
    vector<string> getFirstSet(vector<string> token);

private:
    vector<string> getFirstSet(vector<string> token, int startIndex);

private:
    void Init();
    void InitProduction();                  ///init after LR item for all production
    void InitItem(CProduction& lastLri);    ///init after item and before item for a production
    void InitItems();                       ///init after item and before item for all production
    void InitGotoTable();
	//vector<CProduction> lrItems;
	vector<CProduction> productionVec;
	map<string, vector<CProduction>> productionNameMap;
	vector<string> firstSet;
    unordered_set<string> nonTernimalSet;
    unordered_set<string> ternimalSet;

    GotoAction gotoAction;


};

#endif
