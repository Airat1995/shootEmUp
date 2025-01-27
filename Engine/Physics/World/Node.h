#pragma once

#include <array>
#include <vector>
#include "Physics/Colliders/Collider.h"
#include "Physics/Common/BoundingBox.h"

namespace Engine::Physics::World
{
    enum class NodeState
    {
        Empty,
        Node,
        Leaf,
    };

    using namespace Engine::Physics;

    class Node
    {
    public:

        Node(Node* parent, Engine::Physics::Common::BoundingBox box);
        Node(Node* parent, glm::vec3 position, float size);

        ~Node();

        inline void SetNestedIndex(int index) noexcept
        {
            _nestedIndex = index;
        }

        void UpdateNode() noexcept;

        void InsertCollider(Collider::Collider* collider);

        inline bool IsOverlap(Common::BoundingBox& colliderBox) noexcept;

    private:

        static const int OCTREE_CHILD_COUNT = 8;

        int _nestedIndex = 0;
        NodeState _state = NodeState::Empty;
        float _size;
        Common::BoundingBox _box;
        std::vector<Collider::Collider*> _collidersInNode;
        Node* _parentNode;
        std::array<Node*, OCTREE_CHILD_COUNT> _childNodes;
    };
}