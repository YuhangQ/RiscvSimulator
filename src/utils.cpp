#include "../include/utils.h"

std::vector<std::string> Utils::splitString(std::string target, std::string d) {
    std::vector<std::string> result;

    size_t index = target.find(d);
    while((index = target.find(d)) != target.npos) {
        if(target == d) break;
        if(index == 0) target = target.substr(1, target.size());
        std::string ele = target.substr(0, index);
        target = target.substr(index, target.size());
        if(ele != "") result.push_back(ele);
        //Logger::log(target + " " + d + " " + std::to_string(index));
    }
    if(target != "") result.push_back(target);

    return result;
}