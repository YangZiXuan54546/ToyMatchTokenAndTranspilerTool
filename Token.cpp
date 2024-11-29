#include "basic.h"
#include "parser.h"
#include "Token.h"

Token* GetToken(Parser* parser)
{
    //char* str = (char*)buf.c_str();
    Token* temp = new Token,*a = NULL;
    temp->next = NULL;
    if (parser->FirstToken != NULL)
    {
        a = parser->FirstToken->next;
        while (a != NULL&&a->next != NULL)
        {
             a = a->next;
        }
        if (a != NULL)
        {
            a->next = temp;
            temp->father = a;
        }
        else
        {
            parser->FirstToken->next = temp;
            temp->father = parser->FirstToken;
        }
    }
    else
    {
        temp->father = NULL;
        parser->FirstToken = temp;
    }
    temp->token = MatchToken(parser);
    return temp;
}

void skipblank(Parser* parser)
{
    if (parser->curchar == ' ' || parser->curchar == '\t')
    {
        GetNextChar(parser);
    }
}

TOKENType MatchToken(Parser* parser)
{
    TOKENType result;
    int i = 1;
    bool StopFor = false;
    char* str = nullptr;
    skipblank(parser);
    if (parser->curchar == ' ')
        GetNextChar(parser);
    if (isAtoZ(parser->curchar))
    {
        result = MatchTokenString(parser);
        return result;
    }
    switch (parser->curchar)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        result.token = TOKEN_NUMBER;
        for (; !StopFor;)
            switch (GetNextChar(parser))
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                i++;
                break;
            default:
                StopFor = true;
                break;
            }
        result.str = parser->NextCharStr - 1 - i;
        result.size = i;
        return result;
    case '+':
        result.token = TOKEN_PLUS;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '-':
        result.token = TOKEN_MINUS;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '/':
        switch (GetNextChar(parser))
        {
        case '/':
            for (; GetNextChar(parser) != '\n';);
            GetNextChar(parser);
            result = MatchToken(parser);
            return result;
        default:
            result.token = TOKEN_UNDEFINE;
            result.str = parser->NextCharStr - 2;
            result.size = 2;
            break;
        }
        break;
    case ',':
        result.token = TOKEN_COMMAS;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '(':
        result.token = TOKEN_LEFTPARENTHESE;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case ')':
        result.token = TOKEN_RIGHTPARENTHESE;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '{':
        result.token = TOKEN_LEFTBRACKET;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '}':
        result.token = TOKEN_RIGHTBRACKET;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case ';':
        result.token = TOKEN_END;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '=':
        result.token = TOKEN_AMOUNT;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '\n':
            result.token = TOKEN_LINE;
            result.str = parser->NextCharStr - 1;
            result.size = 1;
            break;
    case '\"':
        result.token = TOKEN_TWOQUOTES;
        result.str = parser->NextCharStr - 1;
        for (; LookNextChar(parser) != '\0' && GetNextChar(parser) != '\"';);
        result.size = (int)(parser->NextCharStr - result.str);
        break;
    case '\'':
        result.token = TOKEN_QUOTES;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    case '*':
        TOKENType token2;
        token2.str = (char*)"*";
        str = parser->NextCharStr;
        GetNextChar(parser);
        result = MatchToken(parser);
           token2.size = 1;
        if (result.token == TOKEN_NUMBER)
        {
            token2.token = TOKEN_BY;
        }
        else
        {
            token2.token = TOKEN_PSTR;
        }
        parser->NextCharStr = str+1;
        parser->curchar = *(parser->NextCharStr - 1);
        return token2;
    case '\\':
        switch (GetNextChar(parser))
        {
        case 'n':
            result.token = TOKEN_END;
            result.str = parser->NextCharStr - 1;
            result.size = 1;
            break;
        case 'a':
            result.token = TOKEN_BUZZ;
            result.str = parser->NextCharStr - 2;
            result.size = 2;
            break;
        case 'b':
            result.token = TOKEN_BACK;
            result.str = parser->NextCharStr - 2;
            result.size = 2;
            break;
        case '\\':
            result.token = TOKEN_SLASH;
            result.str = parser->NextCharStr - 2;
            result.size = 2;
            break;
        default:
            break;
        }
    default:
        result.token = TOKEN_UNDEFINE;
        result.str = parser->NextCharStr - 1;
        result.size = 1;
        break;
    }
    GetNextChar(parser);
    return result;
}


TOKENType MatchTokenString(Parser* parser)
{
    TOKENType result;
    unsigned int length = 0;
    char* start = parser->NextCharStr - 1;
    while (isAtoZ(parser->curchar) || parser->curchar == '_')
    {
        GetNextChar(parser);
    }
    length = (int)(parser->NextCharStr - start - 1);
    result.str = start;
    result.token = idOrkeyword(&result,start,length);
    return result;
}

void ParserToken(Parser* parser)
{
    while (LookNextChar(parser) != '\0' && parser->curchar != '\0')
    {
        GetToken(parser);
    }
    GetToken(parser);
}

void DeleteToken(Token* t)
{
    Token* temp;
    for (; t != NULL;)
    {
        temp = t;
        t = t->next;
        delete temp;
    }
}

bool isAtoZ(char c)
{
    switch ((c - 'A') >= 0 && ('z' - c) >= 0)
    {
    case 1:
        return true;
    case 0:
        return false;
    }
    return false;
}
