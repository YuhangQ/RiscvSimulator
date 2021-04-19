#include "../include/simulator.h"

Simulator::Simulator(std::vector<std::string> &commands) {
    this->commands = commands;
    this->mem = new Memory();
    this->reg = new Register();
    this->parser = new CodeParser(this->reg, this->mem);
   
}

Simulator::~Simulator() {
    delete this->mem;
    delete this->reg;
    delete this->parser;
}

int Simulator::nextStep() {

}

bool Simulator::end() {

}

void Simulator::execToEnd() {
    do {
        this->nextStep();
    } while(!this->end());
}