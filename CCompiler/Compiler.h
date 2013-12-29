#ifndef _Compiler
#define _Compiler

#include <string>
#include "Lex.h"
#include "Yacc.h"

class CCompiler
{
public:
	CCompiler(void);
	~CCompiler(void);

	void Compile(const string& str);

private:
	CLex lex;
	CYacc yacc;
};

#endif 
