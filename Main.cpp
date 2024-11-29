#include "basic.h"
#include "Token.h"
#include "parser.h"
#include "Transpiler.h"

using std::cout;
using std::endl;

int main(int argc, char** agrv)
{
    std::string buf = "";
    std::string filename;
    std::ifstream readfile;
    std::string tempbuf;
    bool DR = true;
    if (argc < 3)
    {
        cout << "ReadFileName: " << endl;
        getline(std::cin, buf);
        readfile.open(buf, std::ios::ios_base::in);
        buf = "";
        cout << "WriteFileName: " << endl;
        std::cin >> filename;
    }
    else
    {
        filename = agrv[2];
        readfile.open(agrv[1], std::ios::ios_base::in);
        if (argc == 4 && !strcmp(agrv[3], "--DR"))
        {
            DR = false;
        }
    }
    while (std::getline(readfile, tempbuf))
    {
        tempbuf += '\n';
        buf += tempbuf;
    }
    char* cbuf = (char*)buf.c_str();
    Parser* parser = initParser(cbuf);
    ParserToken(parser);
    //tokenprint(parser->FirstToken);
    TRANSPIILER transpiiler(parser,filename,DR);
    OutPut(&transpiiler);
    WriteCodeFile(&transpiiler);
    RunFile(&transpiiler);
    ExitParser(parser);
    return 0;
}
