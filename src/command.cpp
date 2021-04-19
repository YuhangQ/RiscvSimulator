#include "../include/command.h"

Command::Command(const std::string& name, const std::vector<std::string>& args) {
    this->name = name;
    this->args = args;
}

bool Command::exec() {
    Logger::log(">>> exec command$ " + this->name);
    std::string argOut = "args: [ ";
    for(auto it=args.begin(); it!=args.end(); it++) {
        argOut += *it + " ";
    }
    argOut += "]";
    Logger::log(argOut);

    if(name == "addi") addi();
}

bool Command::addi() {
    reg->set(args[0], reg->get(args[1]) + std::atol(args[2].c_str()));
}