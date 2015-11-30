#include "GotoAction.h"


GotoAction::GotoAction(void)
{
}


GotoAction::~GotoAction(void)
{
}

void GotoAction::clear()
{
    stateVec.clear();
}

int GotoAction::getStateCount()
{
    return stateVec.size();
}

int GotoAction::addState(YaccState state)
{
    stateVec.push_back(state);
    return stateVec.size() - 1;
}

int GotoAction::addItemToState(int index, const CProduction& prod)
{
    if (index >= 0 && index < stateVec.size())
    {
        stateVec[index].addItem(prod);
        return index;
    }

    return -1;
}

bool GotoAction::hasItem(int index, const CProduction& prod)
{
    if (index >= 0 && index < getStateCount())
    {
        return (stateVec[index].hasItem(prod));
    }     

    return false;
}

int GotoAction::getStateIndex(YaccState state)
{
    for(int i=0;i<stateVec.size();++i)
    {
        if(stateVec[i] == state)
        {
            return i;
        }
    }     

    return -1;
}

void GotoAction::setGotoState(int stateIndex, string token, int newStateIndex)
{
    if (gotoTable.size() == 0)
    {
        gotoTable.resize(32);
    }

    if (gotoTable.size() <= stateIndex)
    {
        gotoTable.resize(gotoTable.size()*2);
    }

    gotoTable[stateIndex][token] = newStateIndex;
}

int GotoAction::getGotoState(int stateIndex, string token)
{
    if (gotoTable.size() <= stateIndex)
    {
        return -1;
    }

    if(gotoTable[stateIndex].find(token) != gotoTable[stateIndex].end())
    {
        return gotoTable[stateIndex][token];
    }

    return GotoAction::INVALID_ACTION;
}

void GotoAction::dump()
{
    for(int i=0;i<stateVec.size();++i)
    {
        //CLog::Log(3, )
        printf("State %d--------------------------------------------------\n",i);
        for(int k=0;k<stateVec[i].productionVec.size();++k)
        {
            printf("%s\n", stateVec[i].productionVec[k].toString().c_str());
        }
        printf("\n\n");
    }

    printf("Goto table--------------------------------------------------\n");
    for(int i=0;i<gotoTable.size();++i)
    {
        bool itemPrinted = false;
        for(map<string,int>::iterator iter = gotoTable[i].begin();iter!= gotoTable[i].end();++iter)
        {
            printf("State [%02d] get %s goto [%02d]\n", i, iter->first.c_str(), iter->second);
            itemPrinted = true;
        }

        if (itemPrinted)
        {
            printf("\n");
        }
    }
}
int str2int(string str);
string int2str(int result);
bool storeStr(string& str, const char * filePath);
bool loadStr(string& str, const char * filePath);
vector<string > split(string& s, char delim);

void GotoAction::store()
{
	// vector<map<string, int>> gotoTable; // this table should be stored.
	string result;
	for (int i = 0; i < gotoTable.size(); ++i)
	{
		for (map<string, int>::iterator iter = gotoTable[i].begin(); iter != gotoTable[i].end(); ++iter)
		{
			result += iter->first;
			result += SPLITER1;
			result += int2str(iter->second);
			result += SPLITER1;
		}

		result += SPLITER2;
	}

	storeStr(result, filePath);
}

bool GotoAction::load()
{
	string str;
	bool result = loadStr(str, filePath); 
	if (result == false)
	{
		return false;
	}

	vector<string> tableItemVec = split(str, SPLITER2);
	gotoTable.resize(tableItemVec.size());
	for (int i = 0; i < tableItemVec.size(); ++i)
	{
		vector<string> mapItemVec = split(tableItemVec[i], SPLITER1);
		for (int k = 0; k < mapItemVec.size()/2; ++k)
		{
			string str = mapItemVec[k*2];
			string str1 = mapItemVec[k*2+1];
			int action = str2int(str1);
			gotoTable[i][str] = action;
		}
	}

	return true;
}

void GotoAction::Reset()
{
	gotoTable.clear();
}