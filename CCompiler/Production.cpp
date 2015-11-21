#include "Production.h"


CProduction::CProduction(void)
{
	index = 0;
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
			if (i == str.size() - 1)
			{
                tokens.push_back(str.substr(start, i-start + 1));
                start = i + 1;
			}
            else if(str[i] == ' ')
            {
                tokens.push_back(str.substr(start, i-start));
                start = i + 1;
            }
		}
	}
}

/// next expecting token .
string CProduction::nextElement()
{
	string result;
	if (index >= 0 && index < tokens.size())
	{
		result = tokens[index];
	}

	return result;
}

/// previous element.
string CProduction::prevElement()
{
    if (index == 0)
    {
        return "";
    }

	string result = tokens[index-1];
	return result;
}

vector<CProduction> CProduction::BuildLRItems()
{
    vector<CProduction> lrItems;
	//for(int i=0;i<=tokens.size();++i)
	//{
	//	CProduction lrCItem;
	//	lrCItem.FromCProduction(*this, i);
	//	lrItems.push_back(lrCItem);
	//	printf("%s\n", lrCItem.toString().c_str());
	//}

    return lrItems;
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

/// only consider the production. ignore index and availableComingToken
bool CProduction::hasSameCore(const CProduction& prod)
{
    bool result1 = (this->name == prod.name);
    if (result1)
    {
        bool result2 = this->tokens.size() == prod.tokens.size();
        if (result2)
        {
            for(int i=0;i<this->tokens.size();++i)
            {
                if (this->tokens[i] != prod.tokens[i])
                {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

bool CProduction::operator==(const CProduction& prod)
{
    bool result1 = (this->index == prod.index) && (this->name == prod.name);
    if (result1)
    {
        bool result2 = this->tokens.size() == prod.tokens.size();
        if (result2)
        {
            for(int i=0;i<this->tokens.size();++i)
            {
                if (this->tokens[i] != prod.tokens[i])
                {
                    return false;
                }
            }

            for(int i=0;i<this->comingTokens.size();++i)
            {
                if (this->comingTokens[i] != prod.comingTokens[i])
                {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

bool CProduction::operator!=(const CProduction& prod)
{
    return !(*this == prod);
}

bool CProduction::isLastItem()
{
    return (this->tokens.size() == index);
}


bool CProduction::isFirstItem()
{
    return index == 0;
}

CProduction CProduction::nextItem()
{
    CProduction prod = *this;
    if (!prod.isLastItem())
    {
        prod.index++;
    }

    return prod;
}

string CProduction::prevToken()
{
    if (index <= 0 || index >= tokens.size())
    {
        return "";
    }

    return tokens[index-1];
}

string CProduction::nextToken()
{
    if (index < 0 || index >= tokens.size())
    {
        return "";
    }

    return tokens[index];
}

string  CProduction::getTokenAfterNext()
{
    if (index < 0 || index + 1 >= tokens.size())
    {
        return "";
    }

    return tokens[index+1];
}

string CProduction::toString()
{
    string result = name;
    result += "->";
    for(int i=0;i<tokens.size();++i)
    {
        if (i == index)
        {
            result += " .";
        }

        result += " ";
        result += tokens[i];
    }

    if (tokens.size() == index)
    {
        result += " .";
    }

    if (comingTokens.size())
    {
        result += "\t~~~~\t";
        for(int i=0;i<comingTokens.size();++i)
        {
            if (i)
            {
                result += "/";
            }
            result += comingTokens[i];
        }
    }
    
    return result;
}