#include "Yacc.h"
#include "Production.h"

CYacc::CYacc(void)
{
	Init();
}


CYacc::~CYacc(void)
{
}

void CYacc::InitItems()
{
	for(int i=0;i<productionVec.size();++i)
	{
		vector<CProduction> lriVec;
		CProduction lri;
		while(1)
		{
			
		}
	}
}

void CYacc::InitProduction()
{
	static char * syntax[] = {
		"S->CElement", 
		"CElement->DefineVariable", 
		"CElement->DefinitionMethod", 
		"DefineVariable->TYPEDEF VARIABLE ;", 
	};

	for(int i=0;i<sizeof(syntax)/sizeof(syntax[0]);++i)
	{
		CProduction production;
		production.FromString(syntax[i]);
		production.BuildLRItems();

		productionVec.push_back(production);
		productionNameMap[production.name] = production;
	}
}

void CYacc::Init()
{
	InitProduction();
	InitItems();
}