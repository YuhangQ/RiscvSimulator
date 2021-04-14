#include <vector>
#include <string>
#include "../include/logger.h"

class CodeParser {
public:
    bool exec(std::string cmd);
private:
    bool addw();
    bool sw();
    bool lw();
};