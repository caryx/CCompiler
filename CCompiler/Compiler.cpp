#include "Compiler.h"


CCompiler::CCompiler(void)
{
}


CCompiler::~CCompiler(void)
{
}

void CCompiler::Compile(const string& str)
{
	lex.GetToken(str);
	//lex.Dump();
    yacc.processToken(lex);
}