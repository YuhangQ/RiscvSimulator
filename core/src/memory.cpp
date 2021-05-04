#include "../include/memory.h"

Memory::Memory() {
    memset(mem, 0, sizeof(mem));
}

long long Memory::get(int index) {
    return mem[index];
}
long long Memory::set(int index, long long value) {
    mem[index] = value;
    used.push_back(index);
}

void Memory::clearUsed() {
    used.clear();
}
std::vector<int> Memory::getUsed() {
    return used;
}