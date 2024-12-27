#include "OctreePoint.h"
#include "OctreeNode.h"

namespace Engine::Physics::World
{
    void OctreePoint::SetNode(OctreeNode *node)
    {
        _node = node;
    }

    bool OctreePoint::SetIsValid(bool isValid) noexcept
    {
        _isValid = isValid;
        return _isValid;
    }

    bool OctreePoint::GetIsValid() const noexcept
    {
        return _isValid;
    }

    OctreeNode *&OctreePoint::GetNodePtr() noexcept
    {
        return _node;
    }

    glm::vec3 OctreePoint::GetPosition() const noexcept
    {
        return _points[_idx];
    }
    uint32_t OctreePoint::GetIdx() const noexcept
    {
        return _idx;
    }
}