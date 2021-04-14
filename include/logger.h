#include <iostream>
#include <ctime>
#include <string>
#include <cstring>

class Logger {
public:
    static void log(const char *&s);
    static void log(const std::string &s);
private:
    static std::string getTimeHead();
};