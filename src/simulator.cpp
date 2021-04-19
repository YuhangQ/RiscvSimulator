#include "../include/simulator.h"

Simulator::Simulator(std::vector<std::string> &input) {
    this->mem = new Memory();
    this->reg = new Register();
    this->parser = new CodeParser(this->reg, this->mem);
    this->pc = &this->reg->get("pc");

    Command::mem = this->mem;
    Command::reg = this->reg;

    this->parseCommand(input);
}

void Simulator::parseCommand(std::vector<std::string> &input) {
    for(auto it=input.begin(); it!=input.end(); it++) {
        const char* ccmd = it->c_str();
        char commandNameArr[100];
        char parameterArr[100];

        sscanf(ccmd, "%s%s", commandNameArr, parameterArr);

        std::string commandName(commandNameArr);
        std::string parameter(parameterArr);

        //Logger::log(parameter);

        std::vector<std::string> args = Utils::splitString(parameter, ",");

        size_t index;
        if((index = commandName.find(":")) != commandName.npos) {
            this->jTarget[commandName.substr(index)] = this->commands.size() + 1;
            commandName = commandName.substr(index+1, commandName.size());
        }

        Logger::log(commandName);

        Command cmd(commandName, args);
        this->commands.push_back(cmd);
    }
}

Simulator::~Simulator() {
    delete this->mem;
    delete this->reg;
    delete this->parser;
}

int Simulator::nextStep() {
    this->commands[*this->pc].exec();
}

bool Simulator::end() {
    // todo
}

void Simulator::execToEnd() {
    do {
        this->nextStep();
    } while(!this->end());
}