#pragma once

#include <string>
#include <vector>

#include "logger.h"

class Utils {
public:
    static std::vector<std::string> splitString(std::string target, std::string d);
};