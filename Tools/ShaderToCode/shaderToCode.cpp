#include <fstream>
#include <iostream>
#include <libcodedirectory.h>
#include <regex>
#include "ShaderType.h"
#include "vertexStruct.h"

const std::string vertexRegexStr = R"(layout \(location = (\d)\) (in) (.*) (.*);)";

const std::string headerTemplate = "#pragma once\n"
                                   "\n"
                                   "#include \"Asset/Mesh/Mesh.h\"\n"
                                   "\n";

const std::string shaderHeaderTemplate = "#pragma once\n"
                                         "\n"
                                         "#include \"Asset/Material/IShader.h\"\n"
                                         "\n";

const std::string materialHeaderTemplate = "#pragma once\n"
                                           "\n"
                                           "#include \"Asset/Material/IMaterial.h\"\n";

const std::string inlineMethodOffset = "\t";
const std::string propertyOffset = "\t\t";
const std::string inlinePropPlatform = "\t\t\t";

const std::unordered_map<std::string, ShaderType> shaderTypes = {{".vert", ShaderType::Vertex},
                                                                 {".frag", ShaderType::Fragment}};

const std::unordered_map<ShaderType, std::string> shaderTypeToFile = {{ShaderType::Vertex,   "Vertex"},
                                                                      {ShaderType::Fragment, "Fragment"}};

std::string getShaderClassName(std::string &className, ShaderType shaderType) {
    const std::string shaderClassName = className + shaderTypeToFile.at(shaderType);
    return shaderClassName;
}

const bool generateShaderClass(std::string &className, ShaderType shaderType, const std::filesystem::path &filePath) {

    std::fstream shaderClassGenFile;
    auto absolutePath = std::filesystem::canonical(filePath);
    std::string shadeFileName = getShaderClassName(className, shaderType) + "Shader.h";
    shaderClassGenFile.open(shadeFileName, std::fstream::out);
    if (shaderClassGenFile.fail()) {
        return false;
    }

    std::ifstream shaderFile(filePath, std::ifstream::ate | std::ifstream::binary);
    const auto begin = shaderFile.tellg();
    shaderFile.seekg(0, std::ios::end);
    const auto end = shaderFile.tellg();
    shaderFile.close();
    const auto fileSize = end - begin;

    const std::string shaderClassName = className + shaderTypeToFile.at(shaderType);
    shaderClassGenFile << shaderHeaderTemplate;
    shaderClassGenFile << "class " << shaderClassName << "Shader : public IShader {\n";
    shaderClassGenFile << propertyOffset << "friend class " << className << "Material;\n";
    shaderClassGenFile << "protected:\n";
    shaderClassGenFile << inlineMethodOffset << shaderClassName << "Shader() : IShader() {\n";
    shaderClassGenFile << propertyOffset << "_name = "
                       << "\"" << className << "\";\n";
    shaderClassGenFile << propertyOffset << "_size = " << fileSize << ";\n";
    shaderClassGenFile << propertyOffset << "std::ifstream shaderFile (\"" << absolutePath.c_str()
                       << "\", std::ios::in|std::ios::binary|std::ios::ate);\n"
                       << propertyOffset << "if (shaderFile.is_open())\n"
                       << propertyOffset << "{\n"
                       << inlinePropPlatform << "const auto size = shaderFile.tellg();\n"
                       << inlinePropPlatform << "_size = shaderFile.tellg();\n"
                       << inlinePropPlatform << "_shaderData = new char [size];\n"
                       << inlinePropPlatform << "shaderFile.seekg (0, std::ios::beg);\n"
                       << inlinePropPlatform << "shaderFile.read (_shaderData, size);\n"
                       << inlinePropPlatform << "shaderFile.close();\n"
                       << propertyOffset << "}\n"
                       << propertyOffset
                       << "else throw std::runtime_error(\"Unable to load shader file \" + _name); \n";
    shaderClassGenFile << inlineMethodOffset << "}\n";
    shaderClassGenFile << "};";


    shaderClassGenFile.close();

    return true;
}

std::vector<VertexStruct> readAllVertex(const std::string &fileLocation) {
    std::regex vertexRegex(vertexRegexStr, std::regex_constants::ECMAScript | std::regex_constants::optimize);
    std::ifstream shaderFile(fileLocation);
    std::string shader((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

    const std::vector<std::smatch> matches{std::sregex_iterator{shader.cbegin(), shader.cend(), vertexRegex},
                                           std::sregex_iterator{}};

    std::vector<VertexStruct> shaderVertecies;
    for (const auto &match: matches) {
        const auto location = match.str(1);
        const auto name = match.str(4);
        const auto inputType = match.str(2);
        const auto vertexType = match.str(3);
        VertexStruct vertexInfo{location, name, inputType, vertexType};
        shaderVertecies.emplace_back(vertexInfo);
    }

    return shaderVertecies;
}

bool generateDataClass(const std::string &className, const std::vector<VertexStruct> &verteciesInfo) {
    std::fstream classFile;
    std::string dataFileName = className + std::string("Data.h");
    classFile.open(dataFileName, std::fstream::out);
    if (classFile.fail()) {
        return false;
    }

    classFile << headerTemplate;
    classFile << "class " << className << "VertexData : BaseVertexData {\n";
    classFile << "public: \n";
    for (const auto &vertexStruct: verteciesInfo) {
        classFile << "\t" << vertexStruct.TypeToCPPType() << " " << vertexStruct.name << ";\n";
    }
    classFile << "};";
    classFile.close();

    return true;
}

bool generateVertexInfoClass(const std::string &fileName, const std::vector<VertexStruct> &verteciesInfo) {
    std::fstream classFile;
    const auto className = fileName + std::string("Descriptor");
    std::string infoFileName = className + std::string(".h");
    classFile.open(infoFileName, std::fstream::out);
    if (classFile.fail()) {
        return false;
    }

    int totalOffset = 0;
    classFile << headerTemplate;
    classFile << "class " << className << "VertexDescriptor : public BaseVertexDescriptor {\n";
    classFile << "public: \n";
    classFile << "\t" << className << "VertexDescriptor"
              << "() {\n";
    classFile << propertyOffset << "_vertexInfo = vector<VertexAttributeInfo>();\n";
    for (const auto &vertexInfo: verteciesInfo) {
        classFile << propertyOffset << "VertexAttributeInfo " << vertexInfo.name << "{};\n";
        classFile << propertyOffset << vertexInfo.name << ".Location = " << vertexInfo.location << ";\n";
        classFile << propertyOffset << vertexInfo.name << ".Offset = " << totalOffset << ";\n";
        classFile << propertyOffset << vertexInfo.name << ".Format = " << vertexInfo.TypeToVertexAttributeType()
                  << ";\n";
        classFile << propertyOffset << "_vertexInfo.push_back(" << vertexInfo.name << ");\n\n";
        totalOffset += vertexInfo.PropertySize();
    }

    classFile << "\n";
    classFile << propertyOffset << "_bindingInfo = vector<VertexBindingInfo>();\n";
    classFile << propertyOffset << "VertexBindingInfo bindingInfo{};\n";
    classFile << propertyOffset << "bindingInfo.BindId = 0;\n";
    classFile << propertyOffset << "bindingInfo.Size = " << totalOffset << ";\n";
    classFile << propertyOffset << "bindingInfo.Instanced = false;\n";
    classFile << propertyOffset << "_bindingInfo.push_back(bindingInfo);\n";

    classFile << "\t}\n";
    classFile << "};";

    return true;
}


void checkShaderWithValidator(const std::string &shaderPath) {
    std::string validationCall = "glslangValidator " + shaderPath;
    system(validationCall.c_str());
}

bool generateMaterialClass(const std::string &className, const std::unordered_map<ShaderType, std::string> &shaders) {
    std::fstream materialFile;
    std::string infoFileName = className + std::string("Material.h");
    materialFile.open(infoFileName, std::fstream::out);
    if (materialFile.fail()) {
        return false;
    }
    materialFile << materialHeaderTemplate;
    for (auto [shaderType, className]: shaders) {
        materialFile << "#include \"" << className << "Shader.h\"\n";
    }
    materialFile << "\n";

    materialFile << "class " << className << "Material : public IMaterial {\n";
    materialFile << "public:\n";
    materialFile << inlineMethodOffset << className << "Material() {\n";
    for (auto [shaderType, className]: shaders) {
        materialFile << propertyOffset << "_shaders.emplace(ShaderType::" << shaderTypeToFile.at(shaderType) << ", "
                     << className << "Shader());\n";
    }
    materialFile << inlineMethodOffset << "}\n";
    materialFile << "};";
    return true;

}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Arguments not enough!" << std::endl;
        return -1;
    }

    std::unordered_map<ShaderType, std::string> materialShaders = {};

    auto className = std::string(argv[1]);
    for (int argumentIndex = 2; argumentIndex < argc; argumentIndex++) {
        const auto shaderFile = std::string(argv[argumentIndex]);
        const auto shaderFilePath = std::filesystem::path(shaderFile);
        const auto shaderType = shaderTypes.at(shaderFilePath.extension().c_str());

        checkShaderWithValidator(shaderFile);

        switch (shaderType) {
            case ShaderType::Vertex: {
                const std::vector<VertexStruct> allVertecies = readAllVertex(shaderFile);
                const bool ableToCreateDataClass = generateDataClass(className, allVertecies);
                if (!ableToCreateDataClass)
                    std::cerr << "Unable to create data class file " << shaderFile << std::endl;

                const bool ableToCreateVertexInfoClass = generateVertexInfoClass(className, allVertecies);
                if (!ableToCreateVertexInfoClass)
                    throw std::runtime_error("Unable to generate vertex shader code!");

                break;
            }
        }

        const std::string shaderClassName = getShaderClassName(className, shaderType);
        materialShaders.emplace(shaderType, shaderClassName);

        auto compiledShaderFilePath = shaderFilePath.filename().c_str() + std::string(".spv");
        std::string compilationCall = "glslc " + shaderFile + " -o " + compiledShaderFilePath;
        system(compilationCall.c_str());

        const bool ableToCreateShaderClass = generateShaderClass(className, shaderType, compiledShaderFilePath);
        if (!ableToCreateShaderClass)
            throw std::runtime_error("Unable to generate shader class!");
    }

    const bool ableToGenerateMaterialClass = generateMaterialClass(className, materialShaders);
    if (!ableToGenerateMaterialClass)
        throw std::runtime_error("Unable to generate material class!");
}
