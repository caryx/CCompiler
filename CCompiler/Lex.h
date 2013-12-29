#ifndef _LEX
#define _LEX

#include <vector>
#include <string>
#include "Token.h"
using namespace std;



class TypeDef
{
public:
	int typeIndex;
	int y;
	string str;
	bool extendable;
	vector<string> extendVec;
};

struct Str_VariableType_Map
{
	string str;
	VariableType variableType;
};

class CLex
{
public:
	CLex(void);
	~CLex(void);

	void Dump();
	void GetToken(const string& str);
	CToken Str2Token(const string& str);
	char IsSpliter(const char& c)
	{
		for(int i=0;i<spliterVec.size();++i)
		{
			if (c == spliterVec[i])
			{
				return 1;
			}
		}

		return 0;
	}

	char IsNewLine(const char& c)
	{
		return c == 10 || c == 13;
	}

	char IsMark(const string c)
	{
		for(int i=0;i<markVec.size(); ++i)
		{
			if (markVec[i] == c)
			{
				return 1;
			}
		}

		return 0;
	}

	char IsBiOerator(const string c)
	{
		for(int i=0;i<biOpeartorVec.size(); ++i)
		{
			if (biOpeartorVec[i] == c)
			{
				return 1;
			}
		}

		return 0;
	}

private:
	void Init()
	{
		char spliters[] = {' ', '\t'};
		char* biOperators[] = {"+", "-", "*", "/", "=", "^", "%"};
		char* keywords[] = {"for", "while", "do", "return", };
		Str_VariableType_Map types[] = {
			{"char", VariableType::CHAR}, 
			{"int", VariableType::INT}, 
			{"long", VariableType::LONG},
			{"float", VariableType::FLOAT}, 
			{"double", VariableType::DOUBLE}, 
			{"unsigned", VariableType::UNSIGNED}
		};

		char* makrs[] = {",", "{", "}", "(", ")", "[", "]", ";"};
		for(int i=0;i<sizeof(spliters)/sizeof(spliters[0]);++i)
		{
			spliterVec.push_back(spliters[i]);
		}
		
		for(int i=0;i<sizeof(biOperators)/sizeof(biOperators[0]);++i)
		{
			biOpeartorVec.push_back(biOperators[i]);
		}

		for(int i=0;i<sizeof(types)/sizeof(types[0]);++i)
		{
			typeVec.push_back(types[i]);
		}

		for(int i=0;i<sizeof(keywords)/sizeof(keywords[0]);++i)
		{
			keywordVec.push_back(keywords[i]);
		}

		for(int i=0;i<sizeof(makrs)/sizeof(makrs[0]);++i)
		{
			markVec.push_back(makrs[i]);
		}
	}

	void Init_Type()
	{

	}

	char IsNumber(const string& str)
	{
		if(str.size() == 0)
		{
			return 0;
		}

		int dotCount = 0;
		for(int i=1;i<str.size();++i)
		{
			if (str[i] == '.')
			{
				++dotCount;
				if (dotCount == 2)
				{
					return 0;
				}
			}
			else if (!isdigit(str[i]))
			{
				return 0;
			}
		}

		return 1;
	}

	char IsVariable(const string& str)
	{
		if(str.size() == 0)
		{
			return 0;
		}

		if (str.size() == 1)
		{
			return isalpha(str[0]);
		}

		if (str[0] == '_' || isdigit(str[0]))
		{
			for(int i=1;i<str.size();++i)
			{
				if (!(isdigit(str[i]) || isalpha(str[i]) || str[i] == '_'))
				{
					return 0;
				}
			}
		}

		return 1;
	}

	bool PushToken(string &tokenStr)
	{
		CToken token = Str2Token(tokenStr);
		if (!token.IsEmpty())
		{
			if (tokenVec.size() == 0 || tokenVec[tokenVec.size()-1].AppendToken(token))
			{
				tokenVec.push_back(token);
				token.Reset();
				tokenStr.clear();
			}

			return 0;
		}

		return 1;
	}

private:
	vector<CToken> tokenVec;

	vector<char> spliterVec;
	vector<string> biOpeartorVec;
	vector<string> uniOperatorVec;
	vector<string> keywordVec;
	vector<Str_VariableType_Map> typeVec;
	vector<string> markVec;
};

#endif

