#pragma once
#pragma once

#include "basic.h"
#include "Token.h"
#include "parser.h"

struct TRANSPIILER {
	Parser* parser;
	std::string buf;
	FILE* WriteFile;
	std::string FileName;
	bool DR;
	TRANSPIILER(Parser* parser,std::string filename,bool i);
	~TRANSPIILER();
};

void OutPut(TRANSPIILER* transpiiler);
std::string* EatTokenRetStr(Token* token);
void WriteCodeFile(TRANSPIILER* tranpiiler);
void RunFile(TRANSPIILER* tranpiiler);