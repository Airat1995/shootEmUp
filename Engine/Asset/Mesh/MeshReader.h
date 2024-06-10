

//TODO: !!!!FINISH IT ONCE I WILL REALLY NEED IT!!!!
#pragma once

#include <charconv>
#include <fstream>
#include <unordered_map>

#include "MeshAttributeReaderType.h"

class MeshReader {
public:

//     static void ReadFromFile(const std::string& filePath, std::unordered_map<MeshAttributeReaderType*, std::vector<void*>>& readData)
//     {
//         if (std::ifstream meshFile(filePath); meshFile.is_open())
//         {
//             MeshAttributeReaderType* currentAttribute = nullptr;
//             std::string line;
//             while (std::getline(meshFile, line))
//             {
//                 //if attribute is null or current line with another attribute
//                 if(currentAttribute == nullptr || line.rfind(currentAttribute->GetAttributeName()) != 0)
//                 {
//                     currentAttribute = FindAttribute(line, readData);
//                 }
//                 switch (currentAttribute->GetAttributeFormat())
//                 {
//
//                 case Format::Int:
//                     int intVal{};
//                     std::from_chars(line.data(), line.data()+line.size(), intVal);
//                     readData.at(currentAttribute).push_back(new void*(reinterpret_cast<void *>(intVal)));
//                     break;
//                 case Format::UInt:
//                     uint uintVal{};
//                     std::from_chars(line.data(), line.data()+line.size(), uintVal);
//                     readData.at(currentAttribute).push_back(new void*(reinterpret_cast<void *>(uintVal)));
//                     break;
//                 case Format::Float:
//                     float floatVal = std::stof(line);
//                     void *p = new void*(reinterpret_cast<void *>(static_cast<uintptr_t>(*reinterpret_cast<uint32_t *>(&floatVal))));
//                     readData.at(currentAttribute).push_back(p);
//                     break;
//                 }
//             }
//             meshFile.close();
//         }
//     }
//
// private:
//     static MeshAttributeReaderType* FindAttribute(const std::string& line, std::unordered_map<MeshAttributeReaderType*, std::vector<void*>>& _readData)
//     {
//         for (const auto& [attribute, data] : _readData)
//         {
//             if(line.rfind(attribute->GetAttributeName()) == 0)
//             {
//                 return attribute;
//             }
//         }
//
//         return nullptr;
//     }
};
