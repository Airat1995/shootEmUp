#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace Engine::Common::IO
{
    class FileReader {
    public:
        static std::vector<char> Read(const std::string &fileLocation);
    };
}