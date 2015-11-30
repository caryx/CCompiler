// CCompiler.cpp : Defines the entry point for the console application.
//
#include <cstdio>
#include <io.h>
#include "Compiler.h"
//#include <Windows.h>


vector <string> split(string& s, string& delim)
{
	vector< std::string > ret;
	int last = 0;
	int index = s.find_first_of(delim, last);
	string tmpStr;
	while (index != std::string::npos)
	{
		tmpStr = s.substr(last, index - last);
		if (tmpStr.size() != 0)
		{
			ret.push_back(tmpStr);
		}

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

string int2str(int result)
{
	char buf[20] = { 0 };
	sprintf(buf, "%d", result);
	string str(buf);
	return str;
}

int str2int(std::string str)
{
	int result = 0;
	int index = 0;
	int flag = 1;
	if (str[0] == '-')
	{
		index++;
		flag = -1;
	}
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
	
	return result*flag;
}

bool storeStr(string& str, const char * filePath)
{
	int fileExist = access(filePath, 0);
	if (fileExist == 0)
	{
		/// file does EXIST
		remove(filePath);
	}

	FILE* file = fopen(filePath, "w+");
	if (file == NULL)
	{
		return false;
	}

	fwrite(str.c_str(), str.size(), 1, file);
	fclose(file);

	return true;
}

bool loadStr(string& str, const char* filePath)
{
	int fileExist = access(filePath, 0);
	if (fileExist != 0)
	{
		/// file does not exist
		return false;
	}
	FILE* file = fopen(filePath, "r+");
	if (file == NULL)
	{
		return false;
	}

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buf = new char[length + 1];
	memset(buf, 0, length + 1);
	fread(buf, length + 1, 1, file);
	fclose(file);
	str = buf;
	delete[] buf;
	return true;
}

char* getExePath()
{
	/**/
	int size = 32;
	int dwRet = 32;
	char *Buffer = (char*)malloc(sizeof(char)*dwRet);
	//memset(Buffer, 0, dwRet*sizeof(char));
	//// get windoes path
	//// got path
	//dwRet = GetModuleFileNameA(NULL, Buffer, dwRet);
	//if (dwRet == 0)
	//	return NULL;
	//while (size == dwRet)
	//{
	//	size *= 2;
	//	Buffer = (char*)realloc(Buffer, sizeof(char)*size);
	//	memset(Buffer, 0, size*sizeof(char));
	//	dwRet = GetModuleFileNameA(NULL, Buffer, size);
	//}
	return Buffer;
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

