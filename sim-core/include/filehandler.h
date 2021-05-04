#pragma once

#include <vector>
#include <string>
#include <cstdio>

class FileHandler {
public:
    FileHandler(std::string filename);
    FileHandler(const char *filename);
    std::vector<std::string> readLines();
private:
    std::string filename;
};