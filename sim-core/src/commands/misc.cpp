#include "../../include/command.h"

// LUI
bool Command::lui() {
    long long data = std::stoi(args[1].c_str()+2, nullptr, 16)<<12;
    if(data & (1<<31)) data |= 0xffffffff00000000ll;
    reg->set(args[0], data);
    return true;
}

// AUIPC
bool Command::auipc() {
    long long data = std::stoi(args[1].c_str()+2, nullptr, 16)<<12;
    if(data & (1<<31)) data |= 0xffffffff00000000ll;
    reg->set(args[0], (*pc)+data);
}

// MEM-MISC
bool Command::fence() { return true; }

// SYSTEM
bool Command::ecall() { return true; }
bool Command::ebreak() { return true; }
