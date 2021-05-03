#pragma once

#include <string>
#include <map>
#include <cstring>
#include <vector>

#include "logger.h"

class Register {
public:
    Register();
    long long& get(int index);
    long long& get(std::string s);
    void set(int index, long long value);
    void set(std::string s, long long value);
    void clear();
    void clearUsed();
    std::vector<std::string> getUsed();
private:
    long long pc;
    long long reg[32];
    std::map<std::string, long long> mp;
    std::vector<std::string> used;
};