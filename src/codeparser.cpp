#include "../include/codeparser.h"

bool CodeParser::exec(std::string cmd) {

    size_t index = cmd.find(' ');

    // not a valid command
    if(index == cmd.npos) return false;

    std::string commandName = cmd.substr(0, index);
    std::string parameter = cmd.substr(index, cmd.size());

    Logger::log(commandName + " $$$$$$$$$$$$$$$$$$$$$ " + parameter);

    return true;
}