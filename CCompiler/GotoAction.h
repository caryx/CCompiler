#pragma once

#include <map>
#include <vector>
#include "Production.h"
#include "YaccState.h"
class GotoAction
{
public:
    GotoAction(void);
    ~GotoAction(void);    

    bool hasItem(int index, const CProduction& prod);
    int addItemToState(int index, const CProduction& prod);
    int addState(YaccState state); // return the index of new added state
    int getStateCount();
    int getStateIndex(YaccState state);
    void clear();

    vector<YaccState> stateVec;

    void setGotoState(int stateIndex, string token, int newStateIndex);
    int getGotoState(int stateIndex, string token);

    void dump();

	void store();
	bool load();
	void Reset();
    static const int INVALID_ACTION = 1<<31;
private:
    //map<CProduction,int> prodStateMap;  // a map from a product to the state containing it.
    vector<map<string, int>> gotoTable;

	const char* filePath = "./!actionTable.txt";
};

