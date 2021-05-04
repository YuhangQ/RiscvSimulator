#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <cstring>

class Logger {
public:
    static void log(const char *&s);
    static void log(const std::string &s);
    static void log(const long long &num);
private:
    static std::string getTimeHead();
};