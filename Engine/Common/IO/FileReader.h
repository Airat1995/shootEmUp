#pragma once

#include <fstream>
#include <string>
#include <vector>

class FileReader {
public:
    static std::vector<char> Read(const std::string &fileLocation);
};
