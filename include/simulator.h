#include <vector>
#include <string>

#include "memory.h"
#include "register.h"
#include "codeparser.h"

class Simulator {
public:
    Simulator(std::vector<std::string> &commands);
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
    std::vector<int> memoryUsed;
    std::vector<std::string> registerUsed;
    std::vector<std::string> commands;
};