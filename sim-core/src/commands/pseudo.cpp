#include "../../include/command.h"

// pseudo
bool Command::nop() {
    return true;
    }
bool Command::li() {
    reg->set(args[0], std::atoll(args[1].c_str()));
    return true;
}
bool Command::mv() {
    args.resize(3);
    args[2] = "0";
    name = "addi";
    return addi();
}
bool Command::not_() {
    args.resize(3);
    args[2] = "-1";
    name = "xori";
    return xori();
}
bool Command::neg() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    name = "sub";
    return sub();
}
bool Command::negw() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    name = "subw";
    return subw();
}
bool Command::sextw() {
    args.resize(3);
    args[2] = "0";
    name = "addiw";
    return addiw();
}
bool Command::seqz() {
    args.resize(3);
    args[2] = "1";
    name = "sltiu";
    return sltiu();
}
bool Command::snez() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    name = "sltu";
    return sltu();
}
bool Command::sltz() {
    args.resize(3);
    args[2] = "zero";
    name = "slt";
    return slt();
}
bool Command::sgtz() {
    args.resize(3);
    args[2] = args[1];
    args[1] = "zero";
    name = "slt";
    return slt();
}
