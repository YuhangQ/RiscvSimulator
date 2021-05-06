#include "../../include/command.h"

// OP-IMM
bool Command::addi() {
    reg->set(args[0], reg->get(args[1]) + std::atoll(args[2].c_str()));
    return true;
}
bool Command::slti() { return false; } // TODO
bool Command::sltiu() { return false; } // TODO
bool Command::xori() { return false; } // TODO
bool Command::ori() { return false; } // TODO
bool Command::andi() { return false; } // TODO
bool Command::slli() { return false; } // TODO
bool Command::srli() { return false; } // TODO
bool Command::srai() { return false; } // TODO

// OP-IMM-32
bool Command::addiw() {
    reg->set(args[0], (int)reg->get(args[1]) + std::atoll(args[2].c_str()));
    return true;
}
bool Command::slliw() { return false; } // TODO
bool Command::srliw() { return false; } // TODO
bool Command::sraiw() { return false; } // TODO
