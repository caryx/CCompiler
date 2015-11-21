
#ifndef _Basic_Type
#define _Basic_Type

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
	TypeDef, 
	Const,
	Variable,
	Keyword,
	Operator,
	Mark,
	Number,
	Semicolon, 
};

//
//char* TypeStrName[] = 
//{
//	"Invalid",
//	"TypeDef", 
//	"Const",
//	"Variable",
//	"Keyword",
//	"Operator",
//	"Mark",
//	"Number",
//};

#endif
