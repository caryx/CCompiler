#include "Item.h"
#include "Production.h"
//
//LRCItem::LRCItem(void)
//{
//	index = -1;
//	//type = Invalid;
//}
//
//LRCItem::~LRCItem(void)
//{
//}
//
//void LRCItem::FromCProduction(const CProduction& production, int ind)
//{
//	index = ind;	
//	name = production.name;
//
//	for(int i=0;i<=production.tokens.size();++i)
//	{
//		if (index == i)
//		{
//			tokens.push_back(".");
//		}
//
//		if (i < production.tokens.size())
//		{
//			tokens.push_back(production.tokens[i]);
//		}
//	}	
//}
//
//string LRCItem::toString()
//{
//	string result = name;
//	//for(int i=0;i<=tokens.size();++i)
//	//{
//	//	if (i == index)
//	//	{
//	//		result.push_back('.');
//	//	}
//	//	
//	//	if (i < tokens.size())
//	//	{
//	//		result += tokens[i];
//	//	}
//	//}
//
//	for(int i=0;i<tokens.size();++i)
//	{
//		result += tokens[i];
//	}
//
//	return result;
//}
