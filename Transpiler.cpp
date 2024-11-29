#include "Transpiler.h"

TRANSPIILER::TRANSPIILER(Parser* parser_,std::string filename,bool i) 
{
	FileName = filename + ".c";
	WriteFile = fopen(FileName.c_str(), "w");
	parser = parser_;
	DR = i;
}

void OutPut(TRANSPIILER* transpiiler)
{
	Token* token;
	std::string* str;
	token = transpiiler->parser->FirstToken;
	str = EatTokenRetStr(token);
	transpiiler->buf = *str;
	delete str;
}

void WriteCodeFile(TRANSPIILER* tranpiiler)
{
	const char* buf = tranpiiler->buf.c_str();
	//tranpiiler->WriteFile.write(buf, sizeof(char) * (tranpiiler->buf.size()+1));
	fputs(buf, tranpiiler->WriteFile);
}

void RunFile(TRANSPIILER* tranpiiler)
{
	std::string str;
	int i = 0;
	str = "gcc ";
	str += tranpiiler->FileName + ' ';
	str += "-o ";
	for (i = 0; tranpiiler->FileName[i] != '.';i++);
	for (int j = 0; j < i; j++)
	{
		str += tranpiiler->FileName[j];
	}
	str += ".exe";
	fclose(tranpiiler->WriteFile);
	system(str.c_str());
}

std::string* EatTokenRetStr(Token* token)
{
	std::string* str = new std::string;
	while (token->next != NULL)
	{
		switch ((token->token.token))
		{
		case TOKEN_LEFTBRACKET:
			*str += "{";
			break;
		case TOKEN_RIGHTBRACKET:
			*str += "}";
			break;
		case TOKEN_LEFTPARENTHESE:
			*str += "(";
			break;
		case TOKEN_RIGHTPARENTHESE:
			*str += ")";
			break;
		case TOKEN_IF:
			*str += "if";
			break;
		case TOKEN_WHILE:
			*str += "while";
			break;
		case TOKEN_FOR:
			*str += "for";
			break;
		case TOKEN_FUN:
			*str += "fun ";
			break;
		case TOKEN_RETURN:
			*str += "return ";
			break;
		case TOKEN_END:
			*str += ";";
			break;
		case TOKEN_LINE:
			*str += '\n';
			break;
		case TOKEN_INT:
			*str += "int ";
			break;
		case TOKEN_NUMBER:
			for (int i = 0; i < token->token.size; i++)
			{
				*str += token->token.str[i];
			}
			*str += ' ';
			break;
		case TOKEN_ID:
			for (int i = 0; i < token->token.size; i++)
			{
				*str += token->token.str[i];
			}
			*str += ' ';
			break;
		case TOKEN_IMPORT:
			*str += "#include <";
			token = token->next;
			for (int i = 0; i < token->token.size; i++)
			{
				*str += token->token.str[i];
			}
			*str += ".h";
			*str += ">";
			break;
		case TOKEN_TWOQUOTES:
			for (int i = 0; i < token->token.size; i++)
			{
				*str += token->token.str[i];
			}
			break;
		case TOKEN_QUOTES:
			*str += "\'";
			break;
		case TOKEN_COMMAS:
			*str += ',';
			break;
		case TOKEN_BY:
		case TOKEN_PSTR:
			*str += '*';
			break;
		case TOKEN_AMOUNT:
			*str += '=';
		default:
			break;
		}
		token = token->next;
	}
	return str;
}

TRANSPIILER::~TRANSPIILER()
{
	if(DR)
		remove(FileName.c_str());
}
