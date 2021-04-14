#include <string>
#include <map>

class Register {
public:
    Register();
    int get(int index);
    int get(std::string s);
private:
    int pc;
    int reg[32];
    std::map<std::string, int> mp;
};