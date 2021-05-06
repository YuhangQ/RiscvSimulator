#pragma once

#include <string>
#include <vector>
#include <map>

#include "logger.h"
#include "register.h"
#include "memory.h"
#include "utils.h"


class Command {
public:
    Command(const std::string& name, const std::vector<std::string>& args);
    bool exec();
    #include "commands/branch.h"
    #include "commands/mem.h"
    #include "commands/misc.h"
    #include "commands/mul.h"
    #include "commands/op.h"
    #include "commands/opimm.h"
    #include "commands/pseudo.h"
    static Register *reg;
    static Memory *mem;
    static long long *pc;
    static std::map<std::string, int>* jTarget;
private:
    std::string name;
    std::vector<std::string> args;
    std::pair<std::string, int> offsetParser(std::string s);
};
