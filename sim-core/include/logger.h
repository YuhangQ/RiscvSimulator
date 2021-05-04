#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>

class Logger {
public:
    static void log(const char *&s);
    static void log(const std::string &s);
    static void log(const long long &num);
    static std::vector<std::string> logs;
private:
    static std::string getTimeHead();
};