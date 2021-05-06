#include "../include/command.h"

Command::Command(const std::string& name, const std::vector<std::string>& args) {
    this->name = name;
    this->args = args;
}

Register* Command::reg = NULL;
Memory* Command::mem = NULL;
long long* Command::pc = NULL;
std::map<std::string, int> *Command::jTarget = NULL;

bool Command::exec() {
    Logger::log(">>> exec command$ " + this->name);
    std::string argOut = "args: [ ";
    for(auto it=args.begin(); it!=args.end(); it++) {
        argOut += *it + " ";
    }
    argOut += "]";
    Logger::log(argOut);

    if(name == "jal") return jal();
    if(name == "jalr") return jalr();
    if(name == "beq") return beq();
    if(name == "bne") return bne();
    if(name == "blt") return blt();
    if(name == "bge") return bge();
    if(name == "bltu") return bltu();
    if(name == "bgeu") return bgeu();
    if(name == "j") return j();
    if(name == "jr") return jr();
    if(name == "ret") return ret();
    if(name == "call") return call();
    if(name == "tail") return tail();
    if(name == "beqz") return beqz();
    if(name == "bnez") return bnez();
    if(name == "blez") return blez();
    if(name == "bgez") return bgez();
    if(name == "bltz") return bltz();
    if(name == "bgtz") return bgtz();
    if(name == "bgt") return bgt();
    if(name == "ble") return ble();
    if(name == "bgtu") return bgtu();
    if(name == "bleu") return bleu();
    if(name == "lb") return lb();
    if(name == "lh") return lh();
    if(name == "lw") return lw();
    if(name == "ld") return ld();
    if(name == "lbu") return lbu();
    if(name == "lhu") return lhu();
    if(name == "lwu") return lwu();
    if(name == "sb") return sb();
    if(name == "sh") return sh();
    if(name == "sw") return sw();
    if(name == "sd") return sd();
    if(name == "lui") return lui();
    if(name == "auipc") return auipc();
    if(name == "fence") return fence();
    if(name == "ecall") return ecall();
    if(name == "ebreak") return ebreak();
    if(name == "mul") return mul();
    if(name == "mulh") return mulh();
    if(name == "mulhsu") return mulhsu();
    if(name == "mulhu") return mulhu();
    if(name == "div") return div();
    if(name == "divu") return divu();
    if(name == "rem") return rem();
    if(name == "remu") return remu();
    if(name == "mulw") return mulw();
    if(name == "divw") return divw();
    if(name == "divuw") return divuw();
    if(name == "remw") return remw();
    if(name == "remuw") return remuw();
    if(name == "add") return add();
    if(name == "sub") return sub();
    if(name == "slt") return slt();
    if(name == "sltu") return sltu();
    if(name == "xor") return xor_();
    if(name == "or") return or_();
    if(name == "and") return and_();
    if(name == "sll") return sll();
    if(name == "srl") return srl();
    if(name == "sra") return sra();
    if(name == "addw") return addw();
    if(name == "subw") return subw();
    if(name == "sllw") return sllw();
    if(name == "srlw") return srlw();
    if(name == "sraw") return sraw();
    if(name == "addi") return addi();
    if(name == "slti") return slti();
    if(name == "sltiu") return sltiu();
    if(name == "xori") return xori();
    if(name == "ori") return ori();
    if(name == "andi") return andi();
    if(name == "slli") return slli();
    if(name == "srli") return srli();
    if(name == "srai") return srai();
    if(name == "addiw") return addiw();
    if(name == "slliw") return slliw();
    if(name == "srliw") return srliw();
    if(name == "sraiw") return sraiw();
    if(name == "nop") return nop();
    if(name == "li") return li();
    if(name == "mv") return mv();
    if(name == "not") return not_();
    if(name == "neg") return neg();
    if(name == "negw") return negw();
    if(name == "sext.w") return sextw();
    if(name == "seqz") return seqz();
    if(name == "snez") return snez();
    if(name == "sltz") return sltz();
    if(name == "sgtz") return sgtz();

    Logger::log("stop..... no handler of " + name);
    exit(1);

    return false;
}

std::pair<std::string, int> Command::offsetParser(std::string s) {
    std::vector<std::string> res = Utils::splitString(s, "(");
    int offset = std::atoi(res[0].c_str());
    std::string t = res[1].substr(0, res[1].size()-1);
    return make_pair(t, offset);
}
