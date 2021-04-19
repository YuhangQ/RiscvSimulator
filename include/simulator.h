#include <vector>
#include <string>

#include "memory.h"
#include "register.h"
#include "codeparser.h"
#include "command.h"
#include "utils.h"
#include "logger.h"

class Simulator {
public:
    Simulator(std::vector<std::string> &input);
    ~Simulator();
    int currentLine();
    int nextStep();
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
    CodeParser *parser;
    long long *pc;
    std::vector<int> memoryUsed;
    std::vector<std::string> registerUsed;
    std::vector<Command> commands;
    std::map<std::string, int> jTarget;

    void parseCommand(std::vector<std::string> &input);
};