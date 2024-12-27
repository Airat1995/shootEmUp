#include "Octree.h"

namespace Engine::Physics::World
{
    Octree::Octree(glm::vec3 minPos, glm::vec3 maxPos) : _childNodes(), _colliders(), _box({0,0,0}, 1.0f)
    {
        _area = {minPos, maxPos};
    }

    Octree::Octree(glm::vec3 minPos, glm::vec3 maxPos, std::vector<Collider::Collider *> colliders)
        : _childNodes(), _colliders(std::move(colliders)), _box({0,0,0}, 1.0f)
    {
        _area = {minPos, maxPos};
    }

    Octree::~Octree()
    {
//        /* Firstly clear data recursively */
//        clear();
//
//        /* Deallocate memory pool */
//        CORRADE_ASSERT(_numAllocatedNodes ==
//                           (_freeNodeBlocks.size() + _activeNodeBlocks.size())*8 + 1,
//                       "Internal data corrupted, maybe all nodes were not returned from the tree", );
//
//        for(OctreeNodeBlock* nodeBlock: _freeNodeBlocks)
//            delete nodeBlock;
//        for(OctreeNodeBlock* nodeBlock: _activeNodeBlocks)
//            delete nodeBlock;
    }

    void Octree::Update(double deltaTime)
    {

    }

    void Octree::Build()
    {
        if(_colliders.size() <= 1)
            return;

        glm::vec3 size = _area.GetMax() - _area.GetMin();
        if(size == MathConst::ZERO)
        {

        }
    }

    void Octree::Clear()
    {
        
    }

    std::array<OctreeNode*, NODE_CHILD_COUNT>* Octree::RequestChildrenFromPool()
    {
    }
} // namespace Engine::Physics::World
