//
// Created by Айрат Насыров on 07.10.2024.
//

#include "OctreeNode.h"

namespace Engine::Physics::World
{

    OctreeNode::OctreeNode(Engine::Physics::World::Octree *tree,
                                                   Engine::Physics::World::OctreeNode *parent,
                                                   Engine::Physics::World::BoundingBox boundingBox, uint32_t depth) :
        _tree(tree), _parent(parent), _box(boundingBox), _depth(depth), _extendedBox({boundingBox.GetMin() * 2.0f, boundingBox.GetMax() * 2.0f})
    {
    }

    OctreeNode::~OctreeNode()
    {

    }

    bool OctreeNode::IsLeaf() const noexcept
    {
        return _isLeaf;
    }

    glm::vec3 OctreeNode::Center() const noexcept
    {
        return _box.GetCenter();
    }

    const BoundingBox &OctreeNode::GetBox() const noexcept
    {
        return _box;
    }

    uint32_t OctreeNode::GetDepth() const noexcept
    {
        return _depth;
    }

    OctreeNode* OctreeNode::GetChildNodes(const uint32_t childIdx) const noexcept
    {
        return _children->at(childIdx);
    }

    const std::vector<OctreePoint *> &OctreeNode::GetPointList() const noexcept
    {
        return _points;
    }

    uint32_t OctreeNode::GetPointsCount() const noexcept
    {
        return _points.size();
    }

    void OctreeNode::RemoveFromSubtree() 
    {
        uint32_t pointsCount = GetPointsCount();
        if (_isLeaf)
            return;

        for (uint32_t childIndex = 0; childIndex < NODE_CHILD_COUNT; childIndex++)
        {
            _children->at(childIndex)->RemoveFromSubtree();
        }
    }

    void Engine::Physics::World::OctreeNode::Split()
    {
        if (!_isLeaf || _depth == _maxDepth)
            return;
        _children = _tree->RequestChildrenFromPool();
        const float childHalfWidth = _box.GetWidth() * .25f;
        for (uint32_t childIndex = 0; childIndex < NODE_CHILD_COUNT; childIndex++)
        {
            glm::vec3 newCenter = _box.GetCenter();
            newCenter[0] += (childIndex & 1) ? childHalfWidth : -childHalfWidth;
            newCenter[1] += (childIndex & 2) ? childHalfWidth : -childHalfWidth;
            newCenter[2] += (childIndex & 4) ? childHalfWidth : -childHalfWidth;

            OctreeNode* childNode = _children->at(childIndex);
            childNode->~OctreeNode();
            BoundingBox childNodeBox {newCenter, childHalfWidth};
            new(childNode) OctreeNode{_tree, this, childNodeBox,_depth + 1};
        }
        _isLeaf = false;
    }
    
    void OctreeNode::RemoveAllDescendants() 
    {
        if(_isLeaf) return;

        for(uint32_t childIndex = 0; childIndex < NODE_CHILD_COUNT; ++childIndex)
        {
            _children->at(childIndex)->RemoveAllDescendants();
        }
    
        _tree->ReturnChildrenToPool(_children);
        _isLeaf = true;
    }
    
    void OctreeNode::RemoveEmptyDescendants() 
    {
        if(_isLeaf) return;

        bool allLeaf = true;
        bool allEmpty = false;
        for (uint32_t childIndex = 0; childIndex < NODE_CHILD_COUNT; childIndex++)
        {
            OctreeNode* childNode = _children->at(childIndex);
            childNode->RemoveEmptyDescendants();
            allLeaf &= childNode->IsLeaf();
            allEmpty &= childNode->_children->size() == 0;
        }

        /* Remove all 8 children nodes iff they are all leaf nodes and all empty
        nodes */
        if(allEmpty && allLeaf) 
        {
            _tree->ReturnChildrenToPool(_children);
            _isLeaf = true;
        }
    }
    
    void OctreeNode::KeepPoint(OctreePoint &point)
    {
        point.SetNode(this);
        point.SetIsValid(true);
        _points.push_back(&point);
    }
    
    void OctreeNode::InsertPoint(OctreePoint &point)
    {
        if(_depth == _maxDepth)
        {
            KeepPoint(point);
            return;
        }
        Split();

        glm::vec3 pointPosition = point.GetPosition();
        glm::vec3 center = _box.GetCenter();
        uint32_t childIndex = 0;
        for (uint32_t dimension = 0; dimension < 3; dimension++)
        {
            if(center[dimension] < pointPosition[dimension])
            {
                childIndex |= (1ull << dimension);
            }
        }
        _children->at(childIndex)->InsertPoint(point);
    }

    bool OctreeNode::Contains(glm::vec3 position) const noexcept
    {
        return _box.Contains(position);
    }

    bool OctreeNode::LoosleyContains(glm::vec3 position) const noexcept
    {
        return _extendedBox.Contains(position);
    }
} // namespace Engine::Physics::World
