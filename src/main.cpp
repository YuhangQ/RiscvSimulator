#include "../include/main.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("未指定输入文件.\n");
        return 0;
    }

    Logger::log("input file: " + std::string(argv[1]));

    freopen(argv[1], "r", stdin);

    FileHandler file(argv[1]);
    std::vector<std::string> codes = file.readLines();


    CodeParser parser;

    Logger::log("read file content");
    std::string line;
    while(getline(std::cin, line)) {
        codes.push_back(line);
        Logger::log(line);
        parser.exec(line);
    }
    fclose(stdin);
    Logger::log("read file finished!");

    return 0;
}