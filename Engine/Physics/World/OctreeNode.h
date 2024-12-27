#pragma once

#include "Octree.h"
#include "OctreePoint.h"

namespace Engine::Physics::World
{
    class OctreeNode
    {
        friend class Octree;
        const BoundingBox _box;
        const BoundingBox _extendedBox;
        const uint32_t _depth;
        Octree* _tree;
        OctreeNode* _parent;
        std::array<OctreeNode*, NODE_CHILD_COUNT>* _children;
        int _currentChildIndex = 0;
        uint32_t _maxDepth;
        bool _isLeaf = true;
        std::vector<OctreePoint*> _points;
        NodeId _id = nullNode;

    public:
        OctreeNode() = default;
        OctreeNode(Octree* tree, OctreeNode* parent, BoundingBox boundingBox, uint32_t depth);

        OctreeNode(const OctreeNode&) = delete;
        OctreeNode& operator=(const OctreeNode&) = delete;

        ~OctreeNode();

        [[nodiscard]] bool IsLeaf() const noexcept;
        [[nodiscard]] glm::vec3 Center() const noexcept;
        [[nodiscard]] const BoundingBox& GetBox() const noexcept;
        [[nodiscard]] uint32_t GetDepth() const noexcept;

        OctreeNode* GetChildNodes(const uint32_t childIdx) const noexcept;
        const std::vector<OctreePoint*>& GetPointList() const noexcept;
        uint32_t GetPointsCount() const noexcept;

        void RemoveFromSubtree();
        void Split();
        void RemoveAllDescendants();
        void RemoveEmptyDescendants();
        void KeepPoint(OctreePoint& point);
        void InsertPoint(OctreePoint& point);

        bool Contains(glm::vec3 position) const noexcept;
        bool LoosleyContains(glm::vec3 position) const noexcept;

        bool LoosleyContains(BoundingBox& box) const noexcept;
        bool LoosleyOverlay(BoundingBox& box) const noexcept;
    };
}