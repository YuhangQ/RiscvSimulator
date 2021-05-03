#include "../include/main.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("未指定输入文件.\n");
        return 0;
    }

    Logger::log("input file: " + std::string(argv[1]));

    FileHandler file(argv[1]);
    std::vector<std::string> codes = file.readLines();

    Logger::log("read file finished!");

    Logger::log("start simulator...");
    Simulator sim(codes);

    Logger::log("-----------------------------------");

    sim.execToEnd();

    while(true) {
        getchar();
        sim.nextStep();
        if(sim.end()) break;
    }

    return 0;
}