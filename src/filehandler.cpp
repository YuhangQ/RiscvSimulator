#include "../include/filehandler.h"

FileHandler::FileHandler(std::string filename) {
    this->filename = filename;
}
FileHandler::FileHandler(const char *filename) {
    this->filename = std::string(filename);
}

std::vector<std::string> FileHandler::readLines() {
    std::vector<std::string> result;
    FILE *fp = fopen(this->filename.c_str(), "r");
    std::string s;
    int c;
    while(true) {
        c = fgetc(fp);
        if(feof(fp)) break;
        if(c == '\n') {
            result.push_back(s);
            s.clear();
            continue;
        }
        if(c != '\r') s.push_back(c);
    }
    fclose(fp);
    return result;
}