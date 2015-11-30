// CCompiler.cpp : Defines the entry point for the console application.
//
#include <cstdio>
#include "Compiler.h"


vector <string> split(string& s, string& delim)
{
	vector< std::string > ret;
	int last = 0;
	int index = s.find_first_of(delim, last);
	string tmpStr;
	while (index != std::string::npos)
	{
		tmpStr = s.substr(last, index - last);
		if (tmpStr.size() == 0)
		{
			continue;
		}
		ret.push_back(tmpStr);
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index == -1 && s.size() > last)
	{
		ret.push_back(s.substr(last, s.size() - last));
	}

	return ret;
}

// split string
vector<string > split(string& s, char delim)
{
	std::string spliter;
	spliter += delim;
	return split(s, spliter);
}


int str2int(std::string str)
{
	int result = 0;
	int index = 0;
	while (index < str.size())
	{
		if (str[index] > '9' || str[index] < 0)
		{
			printf("Invalid str: [%s] to conver to int.", str.c_str());
			return 0;
		}
	
		result *= 10;
		result += (str[index] - '0');
		++index;
	}
	
	return result;
}



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

int add(int x, int y)
{
    printf("-------------------------------------------------------\n");
    return x+y;
}
int x = add(1,2);

int main()
{
	//TestSyntax();
	{
		CProduction prod;
		prod.index = 2;
		prod.name = "S";
		prod.tokens.push_back("F");
		prod.tokens.push_back("T");
		prod.comingTokens.push_back("-");
		prod.comingTokens.push_back("+");

		string result = prod.store();

		CProduction prod2;
		prod2.load(result);
	}

	string input;
	char *testfile = "../main.c";
	FILE* file = fopen(testfile, "rb");
    int fileOpened = 0;
	if (file)
	{
		char buf[1025];
		while(1)
		{
            fileOpened = 1;
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
        if (fileOpened)
        {
            printf("Empty source file.\n");
        }
        else
        {
		    printf("failed to open source file.\n");
        }
	}

	return 0;
}

