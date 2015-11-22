#include "Lex.h"


CLex::CLex(void)
{
	Init();
}


CLex::~CLex(void)
{
}

CToken CLex::Str2Token(const string& str)
{
	//printf("%s\n", str.c_str());
	CToken token;
	char keepSearching = 1;

	// typedef
	for(int i=0; keepSearching && i<typeVec.size();++i)
	{
		if (str == typeVec[i].str)
		{
			token.type = TokenType::TypeDef;
			token.variableType = typeVec[i].variableType;
			token.tokenStr = str;
			keepSearching = 0;
		}
	}

	// keywords
	for(int i=0; keepSearching && i<keywordVec.size();++i)
	{
		if (str == keywordVec[i])
		{
			token.type = TokenType::Keyword;
			token.tokenStr = str;
			keepSearching = 0;
		}
	}
	
	// mark
	for(int i=0; keepSearching && i<markVec.size();++i)
	{
		if (str == markVec[i])
		{
			token.type = TokenType::Mark;
			token.tokenStr = str;
			keepSearching = 0;
		}
	}

	// operator
	for(int i=0; keepSearching && i<biOpeartorVec.size();++i)
	{
		if (str == biOpeartorVec[i])
		{
			token.type = TokenType::Operator;
			token.tokenStr = str;
			keepSearching = 0;
		}
	}

	// variable
	if (keepSearching && IsVariable(str))
	{
		token.type = TokenType::Variable;
		token.tokenStr = str;
		keepSearching = 0;
	}

	// digit
	if (keepSearching && IsNumber(str))
	{
		token.type = TokenType::Number;
		token.tokenStr = str;
		keepSearching = 0;
	}

	// string


	return token;
}


void CLex::Dump()
{
	char* TypeStrName[] = 
	{
		"Invalid",
		"TypeDef", 
		"Const",
		"Variable",
		"Keyword",
		"Operator",
		"Mark",
		"Number",
	};

	for(int i=0;i<tokenVec.size();++i)
	{
		if (tokenVec[i].type == TokenType::TypeDef)
		{
			printf("%s \t type:%s \t VariableType:%d \n", tokenVec[i].tokenStr.c_str(), TypeStrName[tokenVec[i].type], tokenVec[i].variableType);
			//printf("%s \t type:%d \t VariableType:%d \n", tokenVec[i].tokenStr.c_str(), tokenVec[i].type, tokenVec[i].variableType);
		}
		else
		{
			printf("%s \t type:%s \n", tokenVec[i].tokenStr.c_str(), TypeStrName[tokenVec[i].type]);
			//printf("%s \t type:%d \n", tokenVec[i].tokenStr.c_str(), tokenVec[i].type);
		}
	}
}

void CLex::GetToken(const string& str)
{
	int lineCount=0, curCount=0, index = 0;
	char moreProcess = 0;
	char lastChar = 0;
	CToken token;
	string tokenStr;

	while(index < str.size())
	{
		char takeCurrentChar = 0;
		char c = str[index++];
		string cur_str;
		cur_str.push_back(c);
		if (IsSpliter(c) || IsNewLine(c))
		{
			if (tokenStr.empty())
			{
				continue;
			}
			else
			{
				if (IsSpliter(c) || lastChar != '\\')
				{
					// new token
					if (PushToken(tokenStr))
					{
						printf("Error:%s\n", tokenStr.c_str());
						break;
					}
				}
			}
		}
		else if (IsMark(cur_str))
		{
			// new token
			if (tokenStr.size())
			{
				if (PushToken(tokenStr))
				{
					printf("Error:%s\n", tokenStr.c_str());
					break;
				}
			}

			/// take the new 
			tokenStr.push_back(c);
			// new token
			if (PushToken(tokenStr))
			{
				printf("Error:%s\n", tokenStr.c_str());
				break;
			}
		}
		else if (IsBiOerator(cur_str))
		{
			// new token
			if (tokenStr.size())
			{
				if (PushToken(tokenStr))
				{
					printf("Error:%s\n", tokenStr.c_str());
					break;
				}
			}

			/// take the new 
			tokenStr.push_back(c);
			// new token
			if (PushToken(tokenStr))
			{
				printf("Error:%s\n", tokenStr.c_str());
				break;
			}
		}
		else
		{
			if (IsNewLine(c))
			{
				continue;
			}

			tokenStr.push_back(c);
		}
	}

}

char CLex::IsSpliter(const char& c)
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

char CLex::IsNewLine(const char& c)
{
    return c == 10 || c == 13;
}

char CLex::IsMark(const string c)
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

char CLex::IsBiOerator(const string c)
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


void CLex::Init()
{
    char spliters[] = {' ', '\t'};
    char* biOperators[] = {"+", "-", "*", "/", "=", "^", "%"};
    char* keywords[] = {"for", "while", "do", "return", "goto"};
    Str_VariableType_Map types[] = {
        {"void", VariableType::VOID}, 
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

void CLex::Init_Type()
{

}

char CLex::IsNumber(const string& str)
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

char CLex::IsVariable(const string& str)
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

bool CLex::PushToken(string &tokenStr)
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