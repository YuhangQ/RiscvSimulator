#pragma once

#include <string>
#include <vector>
#include "logger.h"
#include "register.h"
#include "memory.h"

class Command {
public:
    Command(const std::string& name, const std::vector<std::string>& args);
    bool exec();
    static Register *reg;
    static Memory *mem;
private:
    std::string name;
    std::vector<std::string> args;

    bool addi();
};