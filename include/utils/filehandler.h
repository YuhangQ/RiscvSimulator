#include <vector>
#include <string>
#include <cstdio>

class FileHandler {
public:
    FileHandler(std::string filename);
    std::vector<std::string> readLines();
private:
    std::string filename;
}