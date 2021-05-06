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
    if(name == "nop") return true;
    if(name == "beq") return beq();
    if(name == "bne") return bne();
    return false;
}

bool Command::bne() {
    try{
    
    if(reg->get(args[0]) != reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]] - 1));
    }

    }catch(...){return false;}
    return true;
}

bool Command::beq() {
    try{
    
    if(reg->get(args[0]) == reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]] - 1));
    }

    }catch(...){return false;}
    return true;
}

bool Command::jr() {
    try{

    *(this->pc) = reg->get(args[0]);
    Logger::log("pc = " + std::to_string(reg->get(args[0])));

    }catch(...){return false;}
    return true;
}

bool Command::call() {
    try{
    reg->set("ra", *pc);
    *(this->pc) = (*jTarget)[args[0]] - 1;
    Logger::log("pc = " + std::to_string((*jTarget)[args[0]] - 1));

    }catch(...){return false;}
    return true;
}

bool Command::ld() {
    try{
    auto addr = offsetParser(args[1]);
    reg->set(args[0], mem->get(reg->get(addr.first) + addr.second));
    }catch(...){return false;}
    return true;
}


bool Command::mv() {
    try{
    reg->set(args[0], reg->get(args[1]));
    }catch(...){return false;}
    return true;
}


bool Command::addw() {
    try{
    reg->set(args[0], reg->get(args[1]) + reg->get(args[2]));
    }catch(...){return false;}
    return true;
}

bool Command::mulw() {
    try{
    reg->set(args[0], reg->get(args[1]) * reg->get(args[2]));
    }catch(...){return false;}
    return true;
}

bool Command::bge() {
    try{
    if(reg->get(args[0]) >= reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]]));
    }
    }catch(...){return false;}
    return true;
}
bool Command::ble() {
    try{
    if(reg->get(args[0]) <= reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]]));
    }
    }catch(...){return false;}
    return true;
}

bool Command::sextw() {
    try{
    reg->set(args[0], (int)reg->get(args[1]));
    }catch(...){return false;}
    return true;
}
bool Command::addiw() {
    try{
    reg->set(args[0], (int)reg->get(args[1]) + std::atoll(args[2].c_str()));
    }catch(...){return false;}
    return true;
}

bool Command::lw() {
    try{
    auto addr = offsetParser(args[1]);
    reg->set(args[0], (int)mem->get(reg->get(addr.first) + addr.second));
    }catch(...){return false;}
    return true;
}

bool Command::j() {
    try{
    *(this->pc) = (*jTarget)[args[0]] - 1;
    /*
    for(auto it = jTarget->begin(); it != jTarget->end(); it++) {
        Logger::log(it->first + ":" + std::to_string(it->second));
    }
    */
    Logger::log("pc = " + std::to_string((*jTarget)[args[0]]));
    }catch(...){return false;}
    return true;
}

bool Command::li() {
    try{
    reg->set(args[0], std::atoll(args[1].c_str()));
    }catch(...){return false;}
    return true;
}

bool Command::addi() {
    try{
    reg->set(args[0], reg->get(args[1]) + std::atoll(args[2].c_str()));
    }catch(...){return false;}
    return true;
}

bool Command::sd() {
    try{
    auto addr = offsetParser(args[1]);
    mem->set(reg->get(addr.first)+addr.second, reg->get(args[0]));
    }catch(...){return false;}
    return true;
}

bool Command::sw() {
    try{
    auto addr = offsetParser(args[1]);
    mem->set(reg->get(addr.first)+addr.second, reg->get(args[0]));
    }catch(...){return false;}
    return true;
}



std::pair<std::string, int> Command::offsetParser(std::string s) {
    std::vector<std::string> res = Utils::splitString(s, "(");
    int offset = std::atoi(res[0].c_str());
    std::string t = res[1].substr(0, res[1].size()-1);
    return make_pair(t, offset);
}