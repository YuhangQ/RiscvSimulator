#include "../../include/command.h"

// OP-IMM
bool Command::addi() {
    reg->set(args[0], reg->get(args[1]) + std::atoll(args[2].c_str()));
    return true;
}
bool Command::slti() {
    if(reg->get(args[1]) < std::atoll(args[2].c_str())) reg->set(args[0], 1);
    return true;
}
bool Command::sltiu() {
    if (static_cast<unsigned long long>(reg->get(args[1]))
        < static_cast<unsigned long long>(std::atoll(args[2].c_str()))
        ) reg->set(args[0], 1);
    return true;
}
bool Command::xori() {
    reg->set(args[0], reg->get(args[1]) ^ std::atoll(args[2].c_str()));
    return true;
}
bool Command::ori() {
    reg->set(args[0], reg->get(args[1]) | std::atoll(args[2].c_str()));
    return true;
}
bool Command::andi() {
    reg->set(args[0], reg->get(args[1]) & std::atoll(args[2].c_str()));
    return true;
}
bool Command::slli() {
    reg->set(args[0], reg->get(args[1]) << std::atoll(args[2].c_str())&0b111111);
    return true;
}
bool Command::srli() {
    reg->set(args[0], static_cast<unsigned long long>(reg->get(args[1])) 
        >> std::atoll(args[2].c_str())&0b111111);
    return true;
}
bool Command::srai() {
    reg->set(args[0], reg->get(args[1]) >> std::atoll(args[2].c_str())&0b111111);
    return true;
}

// OP-IMM-32
bool Command::addiw() {
    reg->set(args[0], (int)(reg->get(args[1])&0xffffffffll)
        + (int)std::atoll(args[2].c_str()));
    return true;
}
bool Command::slliw() {
    reg->set(args[0], (int)(reg->get(args[1])&0xffffffffll)
        << std::atoll(args[2].c_str())&0b11111);
    return true;
}
bool Command::srliw() {
    reg->set(args[0],
        (unsigned int)(static_cast<unsigned long long>(reg->get(args[1]))&0xffffffffll)
        >> std::atoll(args[2].c_str())&0b111111);
    return true;
}
bool Command::sraiw() {
    reg->set(args[0], (int)(reg->get(args[1])&0xffffffffll)
        >> std::atoll(args[2].c_str())&0b111111);
    return true;
}
