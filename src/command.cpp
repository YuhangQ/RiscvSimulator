#include "../include/command.h"

Command::Command(const std::string& name, const std::vector<std::string>& args) {
    this->name = name;
    this->args = args;
}

Register* Command::reg = NULL;
Memory* Command::mem = NULL;
long long* Command::pc = NULL;
std::map<std::string, int> *Command::jTarget = NULL;

bool Command::exec() {
    Logger::log(">>> exec command$ " + this->name);
    std::string argOut = "args: [ ";
    for(auto it=args.begin(); it!=args.end(); it++) {
        argOut += *it + " ";
    }
    argOut += "]";
    Logger::log(argOut);

    if(name == "addi") return addi();
    if(name == "sd") return sd();
    if(name == "sw") return sw();
    if(name == "li") return li();
    if(name == "j") return j();
    if(name == "lw") return lw();
    if(name == "sext.w") return sextw();
    if(name == "addiw") return addiw();
    if(name == "bge") return bge();
    if(name == "ble") return ble();
    if(name == "mulw") return mulw();
    if(name == "addw") return addw();
    if(name == "mv") return mv();
    if(name == "ld") return ld();
    if(name == "call") return call();
    if(name == "jr") return jr();

    Logger::log("stop..... no handler of " + name);
    exit(0);
    

    return false;
}

bool Command::jr() {
    *(this->pc) = reg->get(args[0]);
    Logger::log("pc = " + std::to_string(reg->get(args[0])));
}

bool Command::call() {
    reg->set("ra", *pc);
    *(this->pc) = (*jTarget)[args[0]] - 1;
    Logger::log("pc = " + std::to_string((*jTarget)[args[0]] - 1));
}

bool Command::ld() {
    auto addr = offsetParser(args[1]);
    reg->set(args[0], mem->get(reg->get(addr.first) + addr.second));
}


bool Command::mv() {
    reg->set(args[0], reg->get(args[1]));
}


bool Command::addw() {
    reg->set(args[0], reg->get(args[1]) + reg->get(args[2]));
}

bool Command::mulw() {
    reg->set(args[0], reg->get(args[1]) * reg->get(args[2]));
}

bool Command::bge() {
    if(reg->get(args[0]) >= reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]]));
    }
}
bool Command::ble() {
    if(reg->get(args[0]) <= reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]]));
    }
}

bool Command::sextw() {
    reg->set(args[0], (int)reg->get(args[1]));
}
bool Command::addiw() {
    reg->set(args[0], (int)reg->get(args[1]) + std::atoll(args[2].c_str()));
}

bool Command::lw() {
    auto addr = offsetParser(args[1]);
    reg->set(args[0], (int)mem->get(reg->get(addr.first) + addr.second));
}

bool Command::j() {
    *(this->pc) = (*jTarget)[args[0]] - 1;
    /*
    for(auto it = jTarget->begin(); it != jTarget->end(); it++) {
        Logger::log(it->first + ":" + std::to_string(it->second));
    }
    */
    Logger::log("pc = " + std::to_string((*jTarget)[args[0]]));
}

bool Command::li() {
    reg->set(args[0], std::atoll(args[1].c_str()));
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
}



std::pair<std::string, int> Command::offsetParser(std::string s) {
    std::vector<std::string> res = Utils::splitString(s, "(");
    int offset = std::atoi(res[0].c_str());
    std::string t = res[1].substr(0, res[1].size()-1);
    return make_pair(t, offset);
}