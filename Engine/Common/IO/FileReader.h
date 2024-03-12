#pragma once

#include <fstream>
#include <string>

class FileReader
{
public:
    static std::vector<char> Read(const std::string &fileLocation);
};
