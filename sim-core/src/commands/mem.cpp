#include "../../include/command.h"

// LOAD
bool Command::lb() { return false; } // TODO
bool Command::lh() { return false; } // TODO
bool Command::lw() {
    auto addr = offsetParser(args[1]);
    reg->set(args[0], (int)mem->get(reg->get(addr.first) + addr.second));
    return true;
}
bool Command::ld() {
    auto addr = offsetParser(args[1]);
    reg->set(args[0], mem->get(reg->get(addr.first) + addr.second));
    return true;
}
bool Command::lbu() { return false; } // TODO
bool Command::lhu() { return false; } // TODO
bool Command::lwu() { return false; } // TODO

// STORE
bool Command::sb() { return false; } // TODO
bool Command::sh() { return false; } // TODO
bool Command::sw() {
    auto addr = offsetParser(args[1]);
    mem->set(reg->get(addr.first)+addr.second, reg->get(args[0]));
    return true;
}
bool Command::sd() {
    auto addr = offsetParser(args[1]);
    mem->set(reg->get(addr.first)+addr.second, reg->get(args[0]));
    return true;
}
