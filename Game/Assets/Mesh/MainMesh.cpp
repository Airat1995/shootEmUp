#include "MainMesh.h"
#include "Render/Buffer/BaseBuffer.h"
#include <utility>
#include <glm/glm.hpp>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>

namespace std
{
    template <>
    struct hash<Game::Assets::Mesh::MainVertexData>
    {
        size_t operator()(Game::Assets::Mesh::MainVertexData const &vertex) const {
            return hash<glm::vec3>()(vertex.position);
        }
    };
} // namespace std

namespace Game::Assets::Mesh
{

    static MainDescriptorVertexDescriptor _descriptor = {};

    MainMesh::MainMesh(std::vector<MainVertexData> vertecies, IMaterial *material) : _vertecies(std::move(vertecies)) {
        _material = material;

        _model = glm::transpose(glm::mat4(
                1, 0, 0, 1,
                0, 1, 0, 1,
                0, 0, 1, 1,
                0, 0, 0, 1
        ));
        _modelBuffer = new BaseBuffer(BufferUsageFlag::UniformBuffer, BufferSharingMode::Exclusive, &_model,
                                    BufferStageFlag::Vertex, 0);
        _perObjectBuffers.push_back(_modelBuffer);
        _isStatic = true;
    }

    MainMesh::MainMesh(std::vector<MainVertexData> vertecies, std::vector<uint32_t> indicies, IMaterial *material)
            : _vertecies(std::move(vertecies)) {
        _material = material;
        _indicies = std::move(indicies);
        _model = glm::transpose(glm::mat4(
                1, 0, 0, 1,
                0, 1, 0, 1,
                0, 0, 1, 1,
                0, 0, 0, 1
        ));
        _modelBuffer = new BaseBuffer(BufferUsageFlag::UniformBuffer, BufferSharingMode::Exclusive, &_model,
                                    BufferStageFlag::Vertex, 0);
        _perObjectBuffers.push_back(_modelBuffer);
        _isStatic = true;
    }

    MainMesh *MainMesh::Parse(const std::filesystem::path &filePath, IMaterial *material) {
        tinyobj::ObjReader reader;
        tinyobj::ObjReaderConfig readerConfig;
        //mtl must be in the same directory as obj file
        readerConfig.mtl_search_path = filePath.parent_path();

        if (!reader.ParseFromFile(filePath, readerConfig)) {
            if (!reader.Error().empty()) {
                std::cerr << "TinyObjReader: " << reader.Error();
            }
            return nullptr;
        }

        tinyobj::attrib_t attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warnings;
        std::string errors;

        tinyobj::LoadObj(&attributes, &shapes, &materials, &warnings, &errors, filePath.string().c_str());
        vector<MainVertexData> vertecies;
        vector<uint32_t> indicies;

        std::unordered_map<MainVertexData, uint32_t> uniqueVertices{};

        for (const auto &shape: shapes) {
            for (const auto &index: shape.mesh.indices) {
                MainVertexData vertex{};

                vertex.position = {
                        attributes.vertices[3 * index.vertex_index + 0],
                        attributes.vertices[3 * index.vertex_index + 1],
                        attributes.vertices[3 * index.vertex_index + 2],
                        1.0f
                };

                vertex.normal = {
                        attributes.normals[3 * index.vertex_index + 0],
                        attributes.normals[3 * index.vertex_index + 1],
                        attributes.normals[3 * index.vertex_index + 2],
                };

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertecies.size());
                    vertecies.push_back(vertex);
                }

                indicies.push_back(uniqueVertices[vertex]);
            }
        }

        auto *parsedMesh = new MainMesh(vertecies, indicies, material);
        parsedMesh->_isStatic = true;

        return parsedMesh;
    }

    const void *MainMesh::VerticesData() {
        return _vertecies.data();
    }

    const void *MainMesh::IndicesData() {
        return _indicies.data();
    }

    int MainMesh::VertexCount() {
        return _vertecies.size();
    }

    int MainMesh::RequiredBufferSize() {
        return VertexSize() * VertexCount();
    }

    int MainMesh::VertexSize() {
        return sizeof(MainVertexData);
    }

    int MainMesh::IndexSize() {
        return sizeof(uint32_t);
    }

    int MainMesh::IndexCount() {
        return _indicies.size();
    }

    std::vector<VertexAttributeInfo> MainMesh::VertexInfo() {
        return _descriptor.GetVertexInfo();
    }

    std::vector<VertexBindingInfo> MainMesh::GetVertexBindingInfo() {
        return _descriptor.GetBindingInfo();
    }

    const std::unordered_map<const ShaderType, IShader>& MainMesh::Shaders() const {
        return _material->MaterialShaders();
    }

    void MainMesh::AddPerObjectBuffer(IBuffer *buffer) {
        _perObjectBuffers.push_back(buffer);
    }

    std::vector<IBuffer *> &MainMesh::PerObjectBuffers() {
        return _perObjectBuffers;
    }

    IMaterial *MainMesh::Material() {
        return _material;
    }

    std::vector<MainVertexData> &MainMesh::GetVertecies() {
        return _vertecies;
    }
}
