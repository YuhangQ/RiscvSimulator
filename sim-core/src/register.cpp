#include "../include/register.h"


long long Register::get(int index) {
    return reg[index];
}
long long Register::get(std::string s) {
    return get(mp[s]);
}

void Register::set(int index, long long value) {
    if(!index) return;
    reg[index] = value;
}
void Register::set(std::string s, long long value) {
    if(s == "zero") return;
    set(mp[s], value);
    used.push_back(s);
}

void Register::clearUsed() {
    this->used.clear();
}
std::vector<std::string> Register::getUsed() {
    return this->used;
}

Register::Register() {

    memset(reg, 0, sizeof(reg));

    reg[2] = 1024; // stack pointer
    reg[8] = 1024; // frame pointer

    mp["zero"] = 0;
    mp["ra"] = 1;
    mp["sp"] = 2;
    mp["gp"] = 3;
    mp["tp"] = 4;

    for(int i=0; i<=2; i++) {
        mp["t" + std::to_string(i)] = 5 + i;
    }

    mp["s0"] = 8;
    mp["fp"] = 8;

    mp["s1"] = 9;

    for(int i=0; i<=7; i++) {
        mp["a" + std::to_string(i)] = 10 + i;
    }

    for(int i=2; i<=11; i++) {
        mp["s" + std::to_string(i)] = 16 + i;
    }

    for(int i=3; i<=6; i++) {
        mp["t" + std::to_string(i)] = 25 + i;
    }

}