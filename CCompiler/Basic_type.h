
#ifndef _Basic_Type
#define _Basic_Type
//#include <iostream>
//#include <vector>
#include <string>
//using namespace std;
const char SPLITER1 = '\1';
const char SPLITER2 = '\2';
const char SPLITER3 = '\3';

enum VariableType
{
    VOID,
	CHAR,
	INT,
	LONG,
	FLOAT,
	DOUBLE,
	UNSIGNED,
	LONG_INT,
	LONG_LONG,
	LONG_LONG_INT,

	UNSIGNED_CHAR,
	UNSIGNED_INT,
	UNSIGNED_LONG,
	UNSIGNED_LONG_INT,
	UNSIGNED_LONG_LONG,
	UNSIGNED_LONG_LONG_INT,
};

//enum KeywordType
//{
//	FOR,
//	IF,
//	ELSE,
//	WHILE,
//	DO,
//	RETURN,
//};

enum TokenType
{
	Invalid =0, 
	TYPE, 
	Const,
	ID,
	Keyword,
	Operator,
	Mark,
	Number,
	Semicolon,
    EndDollar,
};

//
//char* TypeStrName[] = 
//{
//	"Invalid",
//	"TYPE", 
//	"Const",
//	"ID",
//	"Keyword",
//	"Operator",
//	"Mark",
//	"Number",
//};


#endif
