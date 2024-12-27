#pragma once

#include "OctreeNode.h"
#include "glm/glm.hpp"
#include "vector"

namespace Engine::Physics::World
{
    class OctreeNode;
    class OctreePoint
    {
    public:
        OctreePoint(std::vector<glm::vec3>& points, uint32_t idx) : _points(points), _idx(idx), _node(nullptr)
        {
        }

        [[nodiscard]] uint32_t GetIdx() const noexcept;

        [[nodiscard]] glm::vec3 GetPosition() const noexcept;

        [[nodiscard]] OctreeNode*& GetNodePtr() noexcept;

        [[maybe_unused]] [[nodiscard]] bool GetIsValid() const noexcept;

        bool SetIsValid(bool isValid) noexcept;

        void SetNode(OctreeNode *node);

    private:
        std::vector<glm::vec3>& _points;
        uint32_t _idx;
        OctreeNode* _node;
        bool _isValid = true;
    };
}