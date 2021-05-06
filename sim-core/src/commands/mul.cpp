#include "../../include/command.h"

// OP
bool Command::mul() { return false; } // TODO
bool Command::mulh() { return false; } // TODO
bool Command::mulhsu() { return false; } // TODO
bool Command::mulhu() { return false; } // TODO
bool Command::div() { return false; } // TODO
bool Command::divu() { return false; } // TODO
bool Command::rem() { return false; } // TODO
bool Command::remu() { return false; } // TODO

//OP-32
bool Command::mulw() {
    reg->set(args[0], reg->get(args[1]) * reg->get(args[2]));
    return true;
}
bool Command::divw() { return false; } // TODO
bool Command::divuw() { return false; } // TODO
bool Command::remw() { return false; } // TODO
bool Command::remuw() { return false; } // TODO
