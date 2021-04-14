#include "../../include/utils/filehandler.h"

FileHandler::FileHandler(std::string filename) {
    this->filename = filename;
}

std::vector<std::string> FileHandler::readLines() {
    FILE *fp = fopen(this->filename.)
}