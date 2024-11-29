#pragma once
#include "basic.h"

enum TOKENENUM {
    TOKEN_NUMBER,
    TOKEN_MINUS,
    TOKEN_PLUS,
    TOKEN_BY,
    TOKEN_UNDEFINE,
    TOKEN_LEFTBRACKET,
    TOKEN_RIGHTBRACKET,
    TOKEN_LEFTPARENTHESE,
    TOKEN_RIGHTPARENTHESE,
    TOKEN_END,
    TOKEN_LINE,
    TOKEN_BUZZ,
    TOKEN_BACK,
    TOKEN_SLASH,
    TOKEN_TWOQUOTES,
    TOKEN_QUOTES,
    TOKEN_COMMAS,
    TOKEN_AMOUNT,

    TOKEN_INT,
    TOKEN_PSTR,

    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,

    TOKEN_FUN,
    TOKEN_WHILE,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_IMPORT,
    TOKEN_STATIC,
    TOKEN_FOR,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_RETURN,

    TOKEN_ID,
};

struct keywordToken {
    const char* keyword;
    int length;
    TOKENENUM token;
};

struct TOKENType
{
    TOKENENUM token;
    char* str;
    int size;
};


struct Token {
    TOKENType token;
    Token* next;
    Token* father;
};
