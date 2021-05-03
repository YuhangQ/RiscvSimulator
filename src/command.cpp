#include "../include/command.h"

Command::Command(const std::string& name, const std::vector<std::string>& args) {
    this->name = name;
    this->args = args;
}

Register* Command::reg = NULL;
Memory* Command::mem = NULL;

bool Command::exec() {
    Logger::log(">>> exec command$ " + this->name);
    std::string argOut = "args: [ ";
    for(auto it=args.begin(); it!=args.end(); it++) {
        argOut += *it + " ";
    }
    argOut += "]";
    Logger::log(argOut);

    if(name == "addi") addi();
    if(name == "sd") sd();
    if(name == "sw") sw();
}

bool Command::addi() {
    reg->set(args[0], reg->get(args[1]) + std::atoll(args[2].c_str()));
}

bool Command::sd() {
    auto addr = offsetParser(args[1]);
    mem->set(reg->get(addr.first)+addr.second, reg->get(args[0]));
}

bool Command::sw() {
    auto addr = offsetParser(args[1]);
    mem->set(reg->get(addr.first)+addr.second, reg->get(args[0]));
    Logger::log(args[0]);
}

std::pair<std::string, int> Command::offsetParser(std::string s) {
    std::vector<std::string> res = Utils::splitString(s, "(");
    int offset = std::atoi(res[0].c_str());
    std::string t = res[1].substr(0, res[1].size()-1);

    return make_pair(t, offset);
}