#pragma once

#include <cstring>
#include <vector>
#include <string>
#include <set>

class Memory {
public:
    Memory();
    long long get(int index);
    void set(int index, long long value);
    void clear();
    void clearUsed();
    std::vector<int> getUsed();
    std::vector<int> getAll();
private:
    long long mem[4096];
    std::vector<int> used;
    std::set<int> all;
};