#include <unordered_set>
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
		CProduction& lastLri = productionVec[i];
		for(int k=0;k<lastLri.lrItems.size();++k)
		{
			CProduction& lri = productionVec[i].lrItems[k];
			map<string, vector<CProduction>>::iterator nextIter = productionNameMap.find(lri.nextElement());
			if (nextIter != productionNameMap.end())
			{
				productionVec[i].lrItems[k].lr_after = nextIter->second;
			}

			map<string, vector<CProduction>>::iterator prevIter = productionNameMap.find(lri.prevElement());
			if (prevIter != productionNameMap.end())
			{
				productionVec[i].lrItems[k].lr_before = prevIter->second;
			}
		}
	}
}

void CYacc::InitProduction()
{
	static char * syntax[] = {
		"S->CElement", 
		"CElement->DefineVariable", 
		"CElement->DefineMethod", 
		"CElement->Statement", 
		"DefineVariable->TYPEDEF VARIABLE ;", 
		"DefineMethod->TYPEDEF VARIABLE ( ARG_LIST ) { METHOD_BODY }",
		"ARG_LIST->EMPTY",
		"ARG_LIST->DefineVariable ARG_LIST2",
		"ARG_LIST2->EMPTY",
		"ARG_LIST2->, DefineVariable ARG_LIST2",
		
	};

	for(int i=0;i<sizeof(syntax)/sizeof(syntax[0]);++i)
	{
		CProduction production;
		production.FromString(syntax[i]);
		production.BuildLRItems();

		productionVec.push_back(production);
		productionNameMap[production.name].push_back(production);
	}

	std::unordered_set<string> nonTernimalSet;
	vector<string> nonTernimal;
	for(int i=0;i<productionVec.size();++i)
	{
		nonTernimal.push_back(productionVec[i].name);
		nonTernimalSet.insert(productionVec[i].name);
	}
	

	for(int i=0;i<productionVec.size();++i)
	{
		for(int k=0;k<productionVec[i].tokens.size();++k)
		{
			std::unordered_set<string>::iterator iter = nonTernimalSet.find(productionVec[i].tokens[k]);
			if (iter!= nonTernimalSet.end())
			{
				firstSet.push_back(*iter);
			}
		}
	}


}

void CYacc::Init()
{
	InitProduction();
	InitItems();
}