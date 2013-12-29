// CCompiler.cpp : Defines the entry point for the console application.
//
#include <cstdio>
#include "Compiler.h"

void TestSyntax()
{
	unsigned					int i = 7;	    \
	int a = 5+(++i);
	char x;
	x = 3 >>  1
		      ;

	//unsigned long char x;
	unsigned int long long y = 3;
	printf("%d\n", sizeof(y));
}

int main()
{
	//TestSyntax();

	string input;
	char *testfile = "../main.c";
	FILE* file = fopen(testfile, "rb");

	if (file)
	{
		char buf[1025];
		while(1)
		{
			memset(buf, 0, sizeof(buf));
			int size = fread(buf, 1, 1024, file);
			string str(buf);
			input += str;
			if (size != 1024)
			{
				break;
			}
		}

		fclose(file);
		file = NULL;
	}

	if (input.size())
	{
		CCompiler compiler;
		compiler.Compile(input);
	}
	else
	{
		printf("failed to open source file.");
	}

	return 0;
}

