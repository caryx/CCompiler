#include "Production.h"


CProduction::CProduction(void)
{
	index = -1;
}


CProduction::~CProduction(void)
{
}

void CProduction::FromString(const string& str)
{
	int start=0;
	for(int i=0;i<str.size();++i)
	{
		if (name.size() == 0 && i > 0 && str[i] == '>' && str[i-1] == '-')
		{
			name = str.substr(0, i-1);
			start = i+1;
			if (start >= str.size())
			{
				throw "Invalid production string";
			}
		}

		if (name.size())
		{
			if (i == str.size() - 1 || str[i] == ' ')
			{
				tokens.push_back(str.substr(start, i-start + 1));
				start = i + 1;
			}
		}
	}
}

/// next element.
string CProduction::nextElement()
{
	string result;
	if (index >= 0 && index < tokens.size())
	{
		result = tokens[(index+1)%tokens.size()];
	}

	return result;
}

/// previous element.
string CProduction::prevElement()
{
	string result = tokens[(index+tokens.size()-1)%tokens.size()];
	return result;
}

void CProduction::BuildLRItems()
{
	for(int i=0;i<=tokens.size();++i)
	{
		//LRCItem lrCItem;
		//lrCItem.index = i;
		//lrCItem.tokens = tokens;
		//lrCItem.name = name;

		//lrItems.push_back(lrCItem);
		//
		//printf("%s\n", lrCItem.toString().c_str());

		CProduction lrCItem;
		lrCItem.FromCProduction(*this, i);
		lrItems.push_back(lrCItem);
		printf("%s\n", lrCItem.toString().c_str());
	}
}

void CProduction::FromCProduction(const CProduction& production, int ind)
{
	index = ind;	
	name = production.name;

	for(int i=0;i<=production.tokens.size();++i)
	{
		if (index == i)
		{
			tokens.push_back(".");
		}

		if (i < production.tokens.size())
		{
			tokens.push_back(production.tokens[i]);
		}
	}	
}

string CProduction::toString()
{
	string result = name + "->";
	//for(int i=0;i<=tokens.size();++i)
	//{
	//	if (i == index)
	//	{
	//		result.push_back('.');
	//	}
	//	
	//	if (i < tokens.size())
	//	{
	//		result += tokens[i];
	//	}
	//}

	for(int i=0;i<tokens.size();++i)
	{
		result += tokens[i];
	}

	return result;
}
