#include "FileReader.h"

std::vector<char> FileReader::Read(const std::string &fileLocation)
{
    std::ifstream infile(fileLocation, std::ios::binary | std::ifstream::ate);
    uint32_t size = 0;
    std::vector<char> fileData;

    if (infile.is_open())
    {
        size = infile.tellg();
        fileData.resize(size);
        infile.seekg(0, std::ios::beg);
        infile.read(fileData.data(), size);
        infile.close();
    }

    return fileData;
}
