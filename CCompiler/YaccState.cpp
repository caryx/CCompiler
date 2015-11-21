#include "YaccState.h"


YaccState::YaccState(void)
{
}


YaccState::~YaccState(void)
{
}

void YaccState::addItem(const CProduction& production)
{
    productionVec.push_back(production);
}


bool YaccState::hasItem(const CProduction& production)
{
    for(int i=0;i<productionVec.size();++i)
    {
        if (productionVec[i] == production)
        {
            return true;
        }
    }

    return false;
}

bool YaccState::operator==(const YaccState& state)
{
    if(this->productionVec.size() != state.productionVec.size())
    {
        return false;
    }

    for(int i=0;i<state.productionVec.size();++i)
    {
        if (productionVec[i] != state.productionVec[i])
        {
            return false;
        }
    }

    return true;
}

bool YaccState::operator!=(const YaccState& state)
{
    return !(*this == state);
}