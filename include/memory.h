#pragma once

#include <cstring>
#include <vector>
#include <string>

class Memory {
public:
    Memory();
    long long get(int index);
    long long set(int index, long long value);
    void clear();
    void clearUsed();
    std::vector<int> getUsed();
private:
    long long mem[4096];
    std::vector<int> used;
};