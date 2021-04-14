#include "../../include/modules/register.h"

Register::Register() {
    mp["zero"] = 0;
    mp["ra"] = 1;
    mp["sp"] = 2);
    mp["gp"] = 3);
    mp["tp"] = 4);

    for(int i=0; i<=2; i++) {
        mp.push("t" + std::to_string(i), 5 + i);
    }

    mp.push("s0", 8);
    mp.push("fp", 8);

    mp.push("s1", 9);

    for(int i=0; i<=7; i++) {
        mp.push("a" + std::to_string(i), 10 + i);
    }

    for(int i=2; i<=11; i++) {
        mp.push("s" + std::to_string(i), 16 + i);
    }

    for(int i=3; i<=6; i++) {
        mp.push("t" + std::to_string(i), 25 + i);
    }
}