#pragma once

#include <cstdint>
#include <utility>

enum class VertexType : uint8_t {
    Int = 0,
    UInt,
    Float,
    Double,
    Vector1F,
    Vector1SF,
    Vector1I,
    Vector2F,
    Vector2SF,
    Vector2I,
    Vector3F,
    Vector3SF,
    Vector3I,
    Vector4F,
    Vector4SF,
    Vector4I,
};

static std::unordered_map<std::string,VertexType> const strToTypeTable = {
        {"int", VertexType::Int},
        {"uint", VertexType::UInt},
        {"float", VertexType::Float},
        {"double", VertexType::Double},

        {"dvec1", VertexType::Vector1F},
        {"vec1", VertexType::Vector1SF},
        {"ivec1", VertexType::Vector1I},

        {"dvec2", VertexType::Vector2F},
        {"vec2", VertexType::Vector2SF},
        {"ivec2", VertexType::Vector2I},

        {"dvec3", VertexType::Vector3F},
        {"vec3", VertexType::Vector3SF},
        {"ivec3", VertexType::Vector3I},

        {"dvec4", VertexType::Vector4F},
        {"vec4", VertexType::Vector4SF},
        {"ivec4", VertexType::Vector4I},
};

static std::unordered_map<VertexType, std::string> const vertexTypeToCPPType = {
        {VertexType::Int, "int"},
        {VertexType::UInt, "uint"},
        {VertexType::Float, "float"},
        {VertexType::Double, "double"},

        {VertexType::Vector1F, "glm::vec<1, double>"},
        {VertexType::Vector1SF, "glm::vec<1, float>"},
        {VertexType::Vector1I, "glm::vec<1, int>"},

        {VertexType::Vector2F, "glm::vec<2, double>"},
        {VertexType::Vector2SF, "glm::vec<2, float>"},
        {VertexType::Vector2I, "glm::vec<2, int>"},

        {VertexType::Vector3F, "glm::vec<3, double>"},
        {VertexType::Vector3SF, "glm::vec<3, float>"},
        {VertexType::Vector3I, "glm::vec<3, int>"},

        {VertexType::Vector4F, "glm::vec<4, double>"},
        {VertexType::Vector4SF, "glm::vec<4, float>"},
        {VertexType::Vector4I, "glm::vec<4, single>"},
};


static std::unordered_map<VertexType, std::string> const vertexTypeToAttributeEnum = {
        {VertexType::Int, "Int"},
        {VertexType::UInt, "Uint"},
        {VertexType::Float, "Float"},
        {VertexType::Double, "Double"},

        {VertexType::Vector1F, "Vector1F"},
        {VertexType::Vector1SF, "Vector1SF"},
        {VertexType::Vector1I, "Vector1I"},

        {VertexType::Vector2F, "Vector2F"},
        {VertexType::Vector2SF, "Vector2SF"},
        {VertexType::Vector2I, "Vector2I"},

        {VertexType::Vector3F, "Vector3F"},
        {VertexType::Vector3SF, "Vector3SF"},
        {VertexType::Vector3I, "Vector3I"},

        {VertexType::Vector4F, "Vector4F"},
        {VertexType::Vector4SF, "Vector4SF"},
        {VertexType::Vector4I, "Vector4I"},
};

static std::unordered_map<VertexType, int> const vertexTypeToSize = {
        {VertexType::Int, 4},
        {VertexType::UInt, 4},
        {VertexType::Float, 4},
        {VertexType::Double, 4},

        {VertexType::Vector1F, 4},
        {VertexType::Vector1SF, 4},
        {VertexType::Vector1I, 4},

        {VertexType::Vector2F, 8},
        {VertexType::Vector2SF, 8},
        {VertexType::Vector2I, 8},

        {VertexType::Vector3F, 12},
        {VertexType::Vector3SF, 12},
        {VertexType::Vector3I, 12},

        {VertexType::Vector4F, 16},
        {VertexType::Vector4SF, 16},
        {VertexType::Vector4I, 16},
};

struct VertexStruct {
    int location;
    std::string name;
    VertexType type;
    bool input;

    VertexStruct(const std::string& locationStr, std::string nameStr, const std::string& inOutStr, const std::string& vertexTypeStr) {
        location = std::stoi(locationStr);
        name = std::move(nameStr);
        type = strToTypeTable.at(vertexTypeStr);
        input = inOutStr == "in";
    }

    [[nodiscard]] std::string TypeToCPPType() const noexcept {
        return vertexTypeToCPPType.at(type);
    }

    [[nodiscard]] std::string TypeToVertexAttributeType() const noexcept {
        return "Format::" + vertexTypeToAttributeEnum.at(type);
    }

    int PropertySize() const noexcept
    {
        return vertexTypeToSize.at(type);
    }
};