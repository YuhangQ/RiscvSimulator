#include "../../include/command.h"

// OP
bool Command::add() {
    reg->set(args[0], reg->get(args[1]) + reg->get(args[2]));
    return true;
}
bool Command::sub() {
    reg->set(args[0], reg->get(args[1]) - reg->get(args[2]));
    return true;
}
bool Command::slt() {
    if (reg->get(args[1]) < reg->get(args[2])) reg->set(args[0], 1);
    return true;
}
bool Command::sltu() {
    if (static_cast<unsigned long long>(reg->get(args[1]))
        < static_cast<unsigned long long>(reg->get(args[2]))
        ) reg->set(args[0], 1);
    return true;
}
bool Command::xor_() {
    reg->set(args[0], reg->get(args[1]) ^ reg->get(args[2]));
    return true;
}
bool Command::or_() {
    reg->set(args[0], reg->get(args[1]) | reg->get(args[2]));
    return true;
}
bool Command::and_() {
    reg->set(args[0], reg->get(args[1]) & reg->get(args[2]));
    return true;
}
bool Command::sll() {
    reg->set(args[0], reg->get(args[1]) << reg->get(args[2])&0b111111);
    return true;
}
bool Command::srl() {
    reg->set(args[0], static_cast<unsigned long long>(reg->get(args[1])) 
        >> reg->get(args[2])&0b111111);
    return true;
}
bool Command::sra() {
    reg->set(args[0], reg->get(args[1]) >> reg->get(args[2])&0b111111);
    return true;
}

// OP-32
bool Command::addw() {
    reg->set(args[0], ((int)(reg->get(args[1])&0xffffffffll)
        + (int)(reg->get(args[2])&0xffffffffll)));
    return true;
}
bool Command::subw() {
    reg->set(args[0], ((int)(reg->get(args[1])&0xffffffffll)
        - (int)(reg->get(args[2])&0xffffffffll)));
    return true;
}
bool Command::sllw() {
    reg->set(args[0], (int)(reg->get(args[1])&0xffffffffll)
        << reg->get(args[2])&0b11111);
    return true;
}
bool Command::srlw() {
    reg->set(args[0],
        (unsigned int)(static_cast<unsigned long long>(reg->get(args[1]))&0xffffffffll)
        >> reg->get(args[2])&0b111111);
    return true;
}
bool Command::sraw() {
    reg->set(args[0], (int)(reg->get(args[1])&0xffffffffll)
        >> reg->get(args[2])&0b111111);
    return true;
}
