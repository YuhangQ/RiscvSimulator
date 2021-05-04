#include "../include/memory.h"

Memory::Memory() {
    memset(mem, 0, sizeof(mem));
}

long long Memory::get(int index) {
    all.insert(index);
    return mem[index];
}
void Memory::set(int index, long long value) {
    mem[index] = value;
    all.insert(index);
    used.push_back(index);
}

void Memory::clearUsed() {
    used.clear();
}
std::vector<int> Memory::getUsed() {
    return used;
}
std::vector<int> Memory::getAll() {
    std::vector<int> v;
    for(auto it = all.begin(); it !=all.end(); it++) {
        v.push_back(*it);
    }
    return v;
}