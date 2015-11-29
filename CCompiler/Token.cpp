
#include "Token.h"


CToken::CToken(void)
{
	Reset();
}

CToken::~CToken(void)
{
}

void CToken::Reset()
{
	type = Invalid;
	tokenStr.clear();
	lineIndex = 0;
	colIndex = 0;
}

string CToken::info()
{
    const int bufLen = 255;
    char buf[bufLen] = {0};
    sprintf_s(buf, bufLen, " - line: %d, column: %d", lineIndex+1, colIndex);
    return tokenStr + buf;
}

/// Non-zero means failed.
char CToken::AppendToken(CToken token)
{
	switch(type)
	{
	case TokenType::TYPE:
		{
			if (token.type != TYPE)
			{
				return 1;
			}
			
			switch (variableType)
			{
			case VariableType::UNSIGNED:
				{
					switch(token.variableType)
					{
					case VariableType::CHAR:
						tokenStr.append(" ");
						tokenStr.append(token.tokenStr);
						variableType = VariableType::UNSIGNED_CHAR;
						return 0;

					case VariableType::INT:
						break;
					}
				}
				break;
			}
		}
		break;

	case TokenType::Operator:
		break;
	}

	return 1; // failed to taken the token
}

char CToken::IsEmpty()
{
	return (type == Invalid) && (tokenStr.size() == 0);
}

string CToken::toString()
{
    switch (type)
    {
    case TokenType::EndDollar:
        return "$";
    case TokenType::ID:
        return "id";
    case TokenType::Number:
        return "num";
    case Mark:
    default:
        return tokenStr;
    }
}

CToken CToken::getEndToken()
{
    CToken token;
    token.type = TokenType::EndDollar;
    return token;
}