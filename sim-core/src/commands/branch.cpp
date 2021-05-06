#include "../../include/command.h"

// JAL
bool Command::jal() { return false; } // TODO

// JALR
bool Command::jalr() { return false; } // TODO

// BRANCH
bool Command::beq() {
    try{
    
    if(reg->get(args[0]) == reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]] - 1));
    }

    }catch(...){return false;}
    return true; } // TODO
bool Command::bne() {
    try{
        if(reg->get(args[0]) != reg->get(args[1])) {
            *(this->pc) = (*jTarget)[args[2]] - 1;
            Logger::log("pc = " + std::to_string((*jTarget)[args[2]] - 1));
        }
    } catch(...) { return false; }
    return true;
}
bool Command::blt() { return false; } // TODO
bool Command::bge() {
    if(reg->get(args[0]) >= reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]]));
    }
    return true;
}
bool Command::bltu() { return false; } // TODO
bool Command::bgeu() { return false; } // TODO

// pseudo
bool Command::j() {
    *(this->pc) = (*jTarget)[args[0]] - 1;
    /*
    for(auto it = jTarget->begin(); it != jTarget->end(); it++) {
        Logger::log(it->first + ":" + std::to_string(it->second));
    }
    */
    Logger::log("pc = " + std::to_string((*jTarget)[args[0]]));
    return true;
}
bool Command::jr() {
    *(this->pc) = reg->get(args[0]);
    Logger::log("pc = " + std::to_string(reg->get(args[0])));

    return true;
}
bool Command::ret() { return false; } // TODO
bool Command::call() {
    reg->set("ra", *pc);
    *(this->pc) = (*jTarget)[args[0]] - 1;
    Logger::log("pc = " + std::to_string((*jTarget)[args[0]] - 1));

    return true;
}
bool Command::tail() { return false; } // TODO

// pseudo branch
bool Command::beqz() { return false; } // TODO
bool Command::bnez() { return false; } // TODO
bool Command::blez() { return false; } // TODO
bool Command::bgez() { return false; } // TODO
bool Command::bltz() { return false; } // TODO
bool Command::bgtz() { return false; } // TODO
bool Command::bgt() { return false; } // TODO
bool Command::ble() {
    if(reg->get(args[0]) <= reg->get(args[1])) {
        *(this->pc) = (*jTarget)[args[2]] - 1;
        Logger::log("pc = " + std::to_string((*jTarget)[args[2]]));
    }
    return true;
}
bool Command::bgtu() { return false; } // TODO
bool Command::bleu() { return false; } // TODO
