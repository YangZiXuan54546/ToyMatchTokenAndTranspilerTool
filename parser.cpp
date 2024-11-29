#include "basic.h"
#include "parser.h"

using std::cout;
using std::endl;

keywordToken  keywordsToken[] = {
   {"int",	  3,	TOKEN_INT},
   {"fun",	  3,	TOKEN_FUN},
   {"if",	  2,	TOKEN_IF},
   {"else",	  4,  	TOKEN_ELSE},
   {"true",	  4,  	TOKEN_TRUE},
   {"false",	  5,  	TOKEN_FALSE},
   {"while",	  5,  	TOKEN_WHILE},
   {"for",	  3,  	TOKEN_FOR},
   {"break",	  5,  	TOKEN_BREAK},
   {"continue",   8,    TOKEN_CONTINUE},
   {"return",	  6,  	TOKEN_RETURN},
   {"null",	  4,  	TOKEN_NULL},
   {"static",	  6,  	TOKEN_STATIC},
   {"import",	  6,  	TOKEN_IMPORT},
};

#ifdef _WIN32
#include <Windows.h>
void error(const WCHAR* buf)
{
    HWND JB = GetForegroundWindow();
    MessageBox(JB, buf, L"Error!", MB_OK | MB_ICONERROR);
    exit(0);
}

#else
void error(const char* buf)
{
    perror(buf);
}
#endif

Parser* initParser(char* buf)
{
    Parser* parser = new Parser;
    parser->buf = buf;
    parser->curchar = buf[0];
    parser->NextCharStr = &buf[1];
    parser->FirstToken = NULL;
    GetToken(parser);
    return parser;
}

char LookNextChar(Parser* parser)
{
    return *parser->NextCharStr;
}

char GetNextChar(Parser* parser)
{
	parser->curchar = *parser->NextCharStr++;
    return parser->curchar;
}

void Move(Parser* parser, int n)
{
    parser->NextCharStr += n;
    parser->curchar = *(parser->NextCharStr - 1);
}

TOKENENUM idOrkeyword(TOKENType* token,const char* start, uint32_t length) {
    uint32_t idx = 0;
    while (keywordsToken[idx].keyword != NULL) {
        if (keywordsToken[idx].length == length &&
            memcmp(keywordsToken[idx].keyword, start, length) == 0) {
            token->str = (char*)keywordsToken[idx].keyword;
            token->size = keywordsToken[idx].length;
            return keywordsToken[idx].token;
        }
        idx++;
    }
    token->str =(char*) start;
    token->size = length;
    return TOKEN_ID;
}

void tokenprint(Token* token)
{
    if (!token)
        return;
    do {
        cout << "父节点地址: " << token->father << endl;
        cout << "子节点地址: " << token->next << endl;
        cout << "字符串: ";
        for(int i = 0;i<token->token.size;i++)
        {
            cout << token->token.str[i];
        }
        cout << endl;
        cout << "长度:" << token->token.size << endl;
        cout << "Token: ";
        switch (token->token.token)
        {
        case TOKEN_MINUS:
            cout << "TOKEN_MINUS" << endl;
            break;
        case TOKEN_NUMBER:
            cout << "TOKEN_NUMBER" << endl;
            break;
        case TOKEN_PLUS:
            cout << "TOKEN_PLUS" << endl;
            break; 
        case TOKEN_UNDEFINE:
            cout << "TOKEN_UNDEFINE" << endl;
            break;
        case TOKEN_BREAK:
            cout << "TOKEN_BREAK" << endl;
            break;
        case TOKEN_CONTINUE:
            cout << "TOKEN_CONTINUE" << endl;
            break;
        case TOKEN_ELSE:
            cout << "TOKEN_IF_ELSE" << endl;
                break;
        case TOKEN_IF:
            cout << "TOKEN_IF" << endl;
            break;
        case TOKEN_LEFTBRACKET:
            cout << "TOKEN_LEFTBRACKET" << endl;
            break;
        case TOKEN_RIGHTBRACKET:
            cout << "TOKEN_RIGHTBRACKET" << endl;
            break;
        case TOKEN_LEFTPARENTHESE:
            cout << "TOKEN_LEFTPARENTHESE" << endl;
            break;
        case TOKEN_RIGHTPARENTHESE:
            cout << "TOKEN_RIGHTPARENTHESE" << endl;
            break;
        case TOKEN_INT:
            cout << "TOKEN_INT" << endl;
            break;
        case TOKEN_FUN:
            cout << "TOKEN_FUN" << endl;
            break;
        case TOKEN_LINE:
            cout << "TOKEN_LINE" << endl;
            break;
        case TOKEN_END:
            cout << "TOKEN_END" << endl;
            break;
        case TOKEN_ID:
            cout << "TOKEN_ID";
            break;
            

        default:
            cout << (int)token->token.token;
#ifdef WIN32
            error(L"An error occurred while parsing the token");
#else
            error("An error occurred while parsing the token");
#endif
            break;
        }
        token = token->next;
        cout << endl;
    } while (token != NULL);
}

void ExitParser(Parser* parser)
{
    DeleteToken(parser->FirstToken);
    delete parser;
}
