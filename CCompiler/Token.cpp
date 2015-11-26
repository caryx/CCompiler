
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
	curIndex = 0;
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
