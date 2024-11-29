#pragma once
#include "basic.h"
#include "Token.h"

struct Parser {
    Token* FirstToken;
    char curchar;
    char* NextCharStr;
    char* buf;
};

Parser* initParser(char* buf);
char LookNextChar(Parser* parser);
char GetNextChar(Parser* parser);
void tokenprint(Token* token);
Token* GetToken(Parser* parser);
TOKENType MatchToken(Parser* parser);
void DeleteToken(Token* t);
TOKENType MatchTokenString(Parser* parser);
void ExitParser(Parser* parser);
TOKENENUM idOrkeyword(TOKENType* token,const char* start, uint32_t length);
void ParserToken(Parser* parser);
void Move(Parser* parser, int n);
bool isAtoZ(char c);
void skipblank(Parser* parser);