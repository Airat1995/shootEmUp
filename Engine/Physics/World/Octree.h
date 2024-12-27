#pragma once

#include <vector>
#include "Colliders/Collider.h"
#include "Common/Math/MathConst.h"
#include "OctreeNode.h"
#include "World/BoundingBox.h"
#include "glm/vec3.hpp"

class OctreeNode;
namespace Engine::Physics::World
{
    using namespace Common::Math;

    using NodeId = std::uint32_t;
    static constexpr NodeId nullNode = NodeId(-1);

    static const int NODE_CHILD_COUNT = 8;

    class Octree
    {
        friend class OctreeNode;

        static constexpr float inf = std::numeric_limits<float>::infinity();
        static constexpr int emptyLifespan = 8;
        static bool _ready;
        static bool _built;

        static std::vector<Collider::Collider*> _readyToInsert;

        Octree(glm::vec3 minPos, glm::vec3 maxPos, std::vector<Collider::Collider*> colliders);

    public:

        Octree() = default;
        Octree(glm::vec3 minPos, glm::vec3 maxPos);

        ~Octree();

        void Update(double deltaTime);

        void Build();
        void Clear();
        void ClearPoints();

    protected:
        void Rebuild();
        void FillPoints();
        void IncrementalUpdate();
        void CheckValidity();
        void RemoveInvalidPointsFromNodes();
        void ReinsertInvalidPointsIntoToNodes();
        std::array<OctreeNode*, NODE_CHILD_COUNT>* RequestChildrenFromPool();
        void ReturnChildrenToPool(std::array<OctreeNode*, NODE_CHILD_COUNT>*& pNodesBlock);

    private:
        glm::vec3 _center;
        glm::vec3 _min;
        glm::vec3 _max;
        uint32_t _maxDepth;
        OctreeNode _rootNode;
        std::vector<std::array<OctreeNode*, NODE_CHILD_COUNT>*> _freeBlocks;
        std::uint32_t _allocatedNodesCount;
        std::vector<OctreePoint> _octreePoints;

        bool _alwaysRebuild = false;
        bool _completeRebuild = false;
    };
}