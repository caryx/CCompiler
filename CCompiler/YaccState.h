#pragma once
#include "Production.h"
class YaccState
{
public:
    YaccState(void);
    ~YaccState(void);
    bool hasItem(const CProduction& production);
    void addItem(const CProduction& production);

    bool operator==(const YaccState& state);
    bool operator!=(const YaccState& state);

    vector<CProduction> productionVec;
};

