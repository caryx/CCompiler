#ifndef _Token
#define _Token

#include <string>
#include "Basic_type.h"
using namespace std;

class CToken
{
public:
	CToken(void);
	~CToken(void);
	void Reset();
	char IsEmpty();
	//char FromStr(const string& str);
	char AppendToken(CToken token);
	string tokenStr;
	int lineIndex;
	int colIndex;

	TokenType type;
	VariableType variableType;	// only valid if it's a variable

    string toString();
    string info();

     static CToken getEndToken();
    //{
    //    CToken token;
    //    token.type = TokenType::EndDollar;
    //    return token;
    //}
};

#endif
