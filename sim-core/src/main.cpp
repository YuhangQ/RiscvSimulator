#include "../include/main.h"

#include <napi.h>
 
using namespace Napi;

Simulator* sim = NULL;
 
void setCodes(const CallbackInfo& info) {
    std::vector<std::string> codes;
    if(sim != NULL) delete sim;

    codes = Utils::splitString(info[0].As<String>(), "\n");
    sim = new Simulator(codes);

    for(int i=0; i<codes.size(); i++) {
        Logger::log(codes[i]);
    }
}

Number curLine(const CallbackInfo& info) {
    return Number::New(info.Env(), sim->currentLine());
}

void nextStep(const CallbackInfo& info) {
    sim->nextStep();
}

void end(const CallbackInfo& info) {
    sim->execToEnd();
}

String getLogs(const CallbackInfo& info) {
    std::string s;
    for(int i=0; i<Logger::logs.size(); i++) {
        s += Logger::logs[i] + "\n";
    }
    Logger::logs.clear();
    return String::New(info.Env(), s);
}

BigUint64Array getRegister(const CallbackInfo& info) {
    auto array = BigUint64Array::New(info.Env(), 32);
    for(int i=0; i<32; i++) array[i] = sim->getRegister()->get(i);
    return array;
}

Int32Array getUsedMemory(const CallbackInfo& info) {
    auto array = Int32Array::New(info.Env(), sim->getMemory()->getAll().size());
    for(int i=0; i<sim->getMemory()->getAll().size(); i++) {
        array[i] = sim->getMemory()->getAll()[i];
    }
    return array;
}

Number getMemory(const CallbackInfo& info) {
    return Number::New(info.Env(), sim->getMemory()->get(info[0].As<Number>().Int32Value()));
}

Napi::Object  Init(Env env, Object exports) {
    exports.Set("setCodes", Function::New(env, setCodes));
    exports.Set("nextStep", Function::New(env, nextStep));
    exports.Set("end", Function::New(env, end));
    exports.Set("curLine", Function::New(env, curLine));
    exports.Set("getRegister", Function::New(env, getRegister));
    exports.Set("getLogs", Function::New(env, getLogs));

    exports.Set("getUsedMemory", Function::New(env, getUsedMemory));
    exports.Set("getMemory", Function::New(env, getMemory));
    return exports;
}
NODE_API_MODULE(addon, Init)

/*

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

*/