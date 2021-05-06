#include "../../include/command.h"

// OP
bool Command::add() { return false; } // TODO
bool Command::sub() { return false; } // TODO
bool Command::slt() { return false; } // TODO
bool Command::sltu() { return false; } // TODO
bool Command::xor_() { return false; } // TODO
bool Command::or_() { return false; } // TODO
bool Command::and_() { return false; } // TODO
bool Command::sll() { return false; } // TODO
bool Command::srl() { return false; } // TODO
bool Command::sra() { return false; } // TODO

// OP-32
bool Command::addw() {
    reg->set(args[0], reg->get(args[1]) + reg->get(args[2]));
    return true;
}
bool Command::subw() { return false; } // TODO
bool Command::sllw() { return false; } // TODO
bool Command::srlw() { return false; } // TODO
bool Command::sraw() { return false; } // TODO
