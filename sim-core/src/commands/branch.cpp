#include "../../include/command.h"

void Command::jumpTo(int addr) {
    *pc = addr - 1;
    Logger::log("pc = " + std::to_string(addr - 1));
}
void Command::jumpTo(std::string& label) {
    jumpTo((*jTarget)[label]);
}

// JAL
bool Command::jal() {
    if(args.size() == 1) {
        args.resize(2);
        args[1] = args[0];
        args[0] = "ra";
    }
    reg->set(args[0], (*pc)+1);
    jumpTo(args[1]);
    return true;
}

// JALR
bool Command::jalr() {
    if(args.size() == 1) {
        args.resize(3);
        args[1] = args[0];
        args[0] = "ra";
        args[2] = "0";
    }
    reg->set(args[0], (*pc)+1);
    jumpTo(reg->get(args[1]) + std::atoi(args[2].c_str()));
    return true;
}

// BRANCH
bool Command::beq() {
    if (reg->get(args[0]) == reg->get(args[1])) jumpTo(args[2]);
    return true;
}
bool Command::bne() {
    if (reg->get(args[0]) != reg->get(args[1])) jumpTo(args[2]);
    return true;
}
bool Command::blt() {
    if (reg->get(args[0]) < reg->get(args[1])) jumpTo(args[2]);
    return true;
}
bool Command::bge() {
    if (reg->get(args[0]) >= reg->get(args[1])) jumpTo(args[2]);
    return true;
}
bool Command::bltu() {
    if (static_cast<unsigned long long>(reg->get(args[0]))
        < static_cast<unsigned long long>(reg->get(args[1]))
    ) jumpTo(args[2]);
    return true;
}
bool Command::bgeu() {
    if (static_cast<unsigned long long>(reg->get(args[0]))
        >= static_cast<unsigned long long>(reg->get(args[1]))
    ) jumpTo(args[2]);
    return true;
}

// pseudo
bool Command::j() {
    args.resize(2);
    args[1] = args[0];
    args[0] = "zero";
    return jal();
}
bool Command::jr() {
    args.resize(3);
    args[1] = args[0];
    args[0] = "zero";
    args[2] = "0";
    return jalr();
}
bool Command::ret() {
    args.resize(3);
    args[0] = "zero";
    args[1] = "ra";
    args[2] = "0";
    return jalr();
}
bool Command::call() {
   return jal();
}
bool Command::tail() {
    return j();
}

// pseudo branch
bool Command::beqz() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    return beq();
}
bool Command::bnez() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    return bne();
}
bool Command::blez() {
    args.resize(3);
    args[2] = args[1];
    args[1] = args[0];
    args[0] = "zero";
    return bge();
}
bool Command::bgez() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    return bge();
}
bool Command::bltz() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    return blt();
}
bool Command::bgtz() {
    args.resize(3);
    args[2] = args[1];
    args[1] = args[0];
    args[0] = "zero";
    return blt();
}
bool Command::bgt() {
    std::swap(args[0], args[1]);
    return blt();
}
bool Command::ble() {
    std::swap(args[0], args[1]);
    return bge();
}
bool Command::bgtu() {
    std::swap(args[0], args[1]);
    return bltu();
}
bool Command::bleu() {
    std::swap(args[0], args[1]);
    return bgeu();
}
