#pragma once

class Memory {
public:
    Memory();
    long long get(int index);
    long long set(int index, long long value);
    void clear();
private:
    long long mem[1024];
};