#ifndef _LEX
#define _LEX

#include <vector>
#include <string>
#include "Token.h"
using namespace std;

class TYPE
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
	CToken Str2Token(const string& str, int lineCount, int columnCount);
	char IsSpliter(const char& c);
	char IsNewLine(const char& c);
	char IsMark(const string c);
	char IsBiOerator(const string c);

    const vector<CToken>& getTokenVec() const;
private:
	void Init();
	void Init_Type();
	char IsNumber(const string& str);
	char IsVariable(const string& str);
	bool PushToken(string &tokenStr, int lineCount, int columnCount);

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

