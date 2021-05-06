#include "../../include/command.h"

// LUI
bool Command::lui() { return false; } // TODO

// AUIPC
bool Command::auipc() { return false; } // TODO

// MEM-MISC
bool Command::fence() { return true; }

// SYSTEM
bool Command::ecall() { return true; }
bool Command::ebreak() { return true; }
