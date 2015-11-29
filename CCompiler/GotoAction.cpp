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