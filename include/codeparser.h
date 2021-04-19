#include <vector>
#include <string>
#pragma once

#include "logger.h"
#include "memory.h"
#include "register.h"

class CodeParser {
public:
    CodeParser(Register *reg, Memory *mem);
    bool exec(std::string cmd);
private:
    Memory *mem;
    Register *reg;

    std::vector<std::string> parseArgs(std::string args);
    bool addi(std::vector<std::string> args);
    bool sw(std::vector<std::string> args);
    bool lw(std::vector<std::string> args);
    //....
};