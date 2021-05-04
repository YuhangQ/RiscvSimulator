#pragma once

#include <vector>
#include <string>

#include "memory.h"
#include "register.h"
#include "command.h"
#include "utils.h"
#include "logger.h"

class Simulator {
public:
    Simulator(std::vector<std::string> &input);
    ~Simulator();
    int currentLine();
    void nextStep();
    bool end();
    void execToEnd();
    void addBreakPoint(int line);
    std::vector<int> memoryUsedByLastCommand();
    std::vector<std::string> registerUsedByLastCommand();
    Memory* getMemory();
    Register* getRegister();
private:
    Memory *mem;
    Register *reg;
    long long pc;

    bool toEnd;
    
    std::vector<Command> commands;
    std::map<std::string, int> jTarget;

    std::map<int, int> rawLine;

    void parseCommand(std::vector<std::string> &input);
};
void useMemory(int addr);