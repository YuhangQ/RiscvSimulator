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
    static Register *reg;
    static Memory *mem;
    static long long *pc;
    static std::map<std::string, int>* jTarget;
private:
    std::string name;
    std::vector<std::string> args;
    std::pair<std::string, int> offsetParser(std::string s);
    bool addi();
    bool sd();
    bool sw();
    bool li();
    bool j();
    bool lw();
    bool sextw();
    bool addiw();
    bool bge();
    bool ble();
    bool mulw();
    bool addw();
    bool mv();
    bool ld();
    bool call();
    bool jr();
};