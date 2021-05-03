#include "../include/logger.h"

void Logger::log(const std::string &s) {
    std::cout << getTimeHead() << " " << s << std::endl;
}

void Logger::log(const char *&s) {
    log(std::string(s));
}

void Logger::log(const long long &num) {
    log(std::to_string(num));
}

std::string Logger::getTimeHead() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string head = "[";
    head += std::to_string(1900 + ltm->tm_year);
    head += "-" + std::to_string(1 + ltm->tm_mon);
    head += "-" + std::to_string(ltm->tm_mday);
    head += " " + std::to_string(ltm->tm_hour);
    head += ":" + std::to_string(ltm->tm_min);
    head += ":" + std::to_string(ltm->tm_sec) + "]";
    return head;
}