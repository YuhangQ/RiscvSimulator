#include "../../include/command.h"

// pseudo
bool Command::nop() { return true; }
bool Command::li() {
    reg->set(args[0], std::atoll(args[1].c_str()));
    return true;
}
bool Command::mv() {
    reg->set(args[0], reg->get(args[1]));
    return true;
}
bool Command::not_() { return false; } // TODO
bool Command::neg() { return false; } // TODO
bool Command::negw() { return false; } // TODO
bool Command::sextw() {
    reg->set(args[0], (int)reg->get(args[1]));
    return true;
}
bool Command::seqz() { return false; } // TODO
bool Command::snez() { return false; } // TODO
bool Command::sltz() { return false; } // TODO
bool Command::sgtz() { return false; } // TODO
