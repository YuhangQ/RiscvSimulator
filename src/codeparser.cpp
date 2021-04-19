#include "../include/codeparser.h"


CodeParser::CodeParser(Register *reg, Memory *mem) {
    this->reg = reg;
    this->mem = mem;
}

std::vector<std::string> CodeParser::parseArgs(std::string args) {
    
}


bool CodeParser::exec(std::string cmd) {

    const char* ccmd = cmd.c_str();

    char commandNameArr[100];
    char parameterArr[100];

    sscanf(ccmd, "%s%s", commandNameArr, parameterArr);

    std::string commandName(commandNameArr);
    std::string parameter(parameterArr);

    Logger::log(">> " + commandName + " - " + parameter);

    auto args = parseArgs(parameter);

    if(cmd == "addi") addi(args);

    return true;
}

bool CodeParser::addi(std::vector<std::string> args) {
    
}