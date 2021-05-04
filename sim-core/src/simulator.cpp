#include "../include/simulator.h"

Simulator::Simulator(std::vector<std::string> &input) {
    this->mem = new Memory();
    this->reg = new Register();
    this->pc = 0;

    Command::mem = this->mem;
    Command::reg = this->reg;
    Command::pc = &this->pc;
    Command::jTarget = &this->jTarget;

    this->parseCommand(input);

    pc = jTarget["main"];
}

Memory* Simulator::getMemory() {
    return this->mem;
}
Register* Simulator::getRegister() {
    return this->reg;
}

int Simulator::currentLine() {
    return rawLine[pc];
}

void Simulator::parseCommand(std::vector<std::string> &input) {
    for(int i=0; i<input.size(); i++) {
        const char* ccmd = input[i].c_str();
        char commandNameArr[100];
        char parameterArr[100];

        sscanf(ccmd, "%s%s", commandNameArr, parameterArr);

        std::string commandName(commandNameArr);
        std::string parameter(parameterArr);

        //Logger::log(parameter);

        std::vector<std::string> args = Utils::splitString(parameter, ",");

        size_t index;
        if((index = commandName.find(":")) != commandName.npos) {
            this->jTarget[commandName.substr(0, commandName.size()-1)] = this->commands.size();
            Logger::log("add tag: " + commandName + "-> " +  std::to_string(this->commands.size()));
            continue;
        } else if(commandName[0] == '.') {
            continue;
        }

        Logger::log(std::to_string(this->commands.size())+": " + commandName);

        Command cmd(commandName, args);
        this->commands.push_back(cmd);

        rawLine[commands.size()-1] = i + 1;
    }
}

Simulator::~Simulator() {
    delete this->mem;
    delete this->reg;
}

void Simulator::nextStep() {

    if(end()) return;

    reg->clearUsed();
    mem->clearUsed();

    this->commands[pc].exec();
    pc++;


    for(int i=0; i<reg->getUsed().size(); i++) {
        Logger::log("reg["+reg->getUsed()[i]+"] = " + std::to_string(reg->get(reg->getUsed()[i])));
    }
    
    for(int i=0; i<mem->getUsed().size(); i++) {
        Logger::log("mem["+std::to_string(mem->getUsed()[i])+"] = " + std::to_string(mem->get(mem->getUsed()[i])));
    }
}

bool Simulator::end() {
    // todo
    return pc >= this->commands.size() - 1;
}

void Simulator::execToEnd() {
    do {
        this->nextStep();
    } while(!this->end());
}