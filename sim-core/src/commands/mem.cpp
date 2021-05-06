#include "../../include/command.h"

// LOAD
bool Command::lb() {
    int addr = offsetParser(args[1]);
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    data = (data>>(addr%8*8))&0xffll;
    if(data & (1<<7)) data |= 0xffffffffffffff00ll;
    reg->set(args[0], static_cast<long long>(data));
    return true;
}
bool Command::lh() {
    int addr = offsetParser(args[1]);
    if (addr % 2) {
        Logger::log("Misaligned memory access");
        return false;
    }
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    data = (data>>(addr%8*8))&0xffffll;
    if(data & (1<<15)) data |= 0xffffffffffff0000ll;
    reg->set(args[0], static_cast<long long>(data));
    return true;
}
bool Command::lw() {
    int addr = offsetParser(args[1]);
    if (addr % 4) {
        Logger::log("Misaligned memory access");
        return false;
    }
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    data = (data>>(addr%8*8))&0xffffffffll;
    if(data & (1<<31)) data |= 0xffffffff00000000ll;
    reg->set(args[0], static_cast<long long>(data));
    return true;
}
bool Command::ld() {
    int addr = offsetParser(args[1]);
    if (addr % 8) {
        Logger::log("Misaligned memory access");
        return false;
    }
    reg->set(args[0], mem->get(addr));
    return true;
}
bool Command::lbu() {
    int addr = offsetParser(args[1]);
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    data = (data>>(addr%8*8))&0xffll;
    reg->set(args[0], static_cast<long long>(data));
    return true;
}
bool Command::lhu() {
    int addr = offsetParser(args[1]);
    if (addr % 2) {
        Logger::log("Misaligned memory access");
        return false;
    }
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    data = (data>>(addr%8*8))&0xffffll;
    reg->set(args[0], static_cast<long long>(data));
    return true;
}
bool Command::lwu() {
    int addr = offsetParser(args[1]);
    if (addr % 4) {
        Logger::log("Misaligned memory access");
        return false;
    }
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    data = (data>>(addr%8*8))&0xffffffffll;
    reg->set(args[0], static_cast<long long>(data));
    return true;
}

// STORE
bool Command::sb() {
    int addr = offsetParser(args[1]);
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    unsigned long long wdata = static_cast<unsigned long long>(reg->get(args[0]));
    data = data&((-1ll)^(0xffllu<<(addr%8*8)));
    data |= (wdata&0xffllu)<<(addr%8*8);
    mem->set(addr/8*8, static_cast<long long>(data));
    return true;
} // TODO
bool Command::sh() {
    int addr = offsetParser(args[1]);
    if (addr % 2) {
        Logger::log("Misaligned memory access");
        return false;
    }
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    unsigned long long wdata = static_cast<unsigned long long>(reg->get(args[0]));
    data = data&((-1ll)^(0xffffllu<<(addr%8*8)));
    data |= (wdata&0xffffllu)<<(addr%8*8);
    mem->set(addr/8*8, static_cast<long long>(data));
    return true;
}
bool Command::sw() {
    int addr = offsetParser(args[1]);
    if (addr % 4) {
        Logger::log("Misaligned memory access");
        return false;
    }
    unsigned long long data = static_cast<unsigned long long>(mem->get(addr/8*8));
    unsigned long long wdata = static_cast<unsigned long long>(reg->get(args[0]));
    data = data&((-1ll)^(0xffffffffllu<<(addr%8*8)));
    data |= (wdata&0xffffffffllu)<<(addr%8*8);
    mem->set(addr/8*8, static_cast<long long>(data));
    return true;
}
bool Command::sd() {
    int addr = offsetParser(args[1]);
    mem->set(addr, reg->get(args[0]));
    return true;
}
