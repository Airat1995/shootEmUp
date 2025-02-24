//
// Created by Айрат Насыров on 27.12.2024.
//

#include "Node.h"
#include "Octree.h"

Engine::Physics::World::Node::Node(Engine::Physics::World::Node* parent, glm::vec3 position, float size) :
    _box({position, size}), _size(size), _parentNode(parent)
{
}

Engine::Physics::World::Node::Node(Engine::Physics::World::Node* parent, Engine::Physics::Common::BoundingBox box) :
    _box(box), _size(box.GetSize()), _parentNode(parent)
{
}

Engine::Physics::World::Node::~Node()
{
    _box.SetPosition(glm::vec3(0,0,0));
    _size = 0;
    _parentNode = nullptr;
    _collidersInNode.clear();
    if(_state == NodeState::Node)
    {
        for (int childIndex = 0; childIndex < OCTREE_CHILD_COUNT; ++childIndex) {
            delete _childNodes[childIndex];
        }
    }
}
void Engine::Physics::World::Node::UpdateNode() noexcept
{
    if(_state == NodeState::Empty)
    {
        return;
    }
    for (int childIndex = 0; childIndex < OCTREE_CHILD_COUNT; ++childIndex) {
        _childNodes.at(childIndex)->UpdateNode();
    }
}
void Engine::Physics::World::Node::InsertCollider(Engine::Physics::Collider::Collider *collider)
{
    Engine::Physics::Common::BoundingBox& colliderBox = collider->GetBoundingBox();

    switch (_state) {
    case NodeState::Empty:
        _collidersInNode.push_back(collider);
        _state = NodeState::Leaf;
        break;
    case NodeState::Node:
        for (int octreeIndex = 0; octreeIndex < OCTREE_CHILD_COUNT; octreeIndex++) {
            if(_childNodes[octreeIndex]->IsOverlap(colliderBox))
            {
                _childNodes[octreeIndex]->InsertCollider(collider);
                break;
            }
        }
        break;
    case NodeState::Leaf:
            glm::vec3 nodeCenter = _box.GetPosition();
            float nodeSize = _box.GetSize();
            _collidersInNode.push_back(collider);
            if(_collidersInNode.size() > Octree::MAX_COLLIDERS_PER_NODE && _size > Octree::MIN_NODE_SIZE)
            {
                int nodeIndex = 0;
                for (int xAxis = -1; xAxis <= 1; xAxis+=2)
                {
                    for (int yAxis = -1; yAxis <= 1; yAxis+=2)
                    {
                        for (int zAxis = -1; zAxis <= 1; zAxis+=2)
                        {
                            glm::vec3 childNodeCenter {nodeCenter.x + (float)(xAxis)*(nodeSize / 2), nodeCenter.y + (float)(yAxis)*(nodeSize / 2), nodeCenter.z + (float)(zAxis)*(nodeSize / 2)};
                            Engine::Physics::Common::BoundingBox nodeBox {childNodeCenter, nodeSize/2};
                            Node* childNode = new Node(this, nodeBox);
                            int childNodeNestIndex = _nestedIndex + 1;
                            childNode->SetNestedIndex(childNodeNestIndex);
                            _childNodes[nodeIndex] = childNode;
                            nodeIndex++;
                        }
                    }
                }

                bool didntFoundAnyChild = true;
                for (int colliderIndex = _collidersInNode.size() - 1; colliderIndex >= 0 ; colliderIndex--)
                {
                    for (int octreeIndex = 0; octreeIndex < OCTREE_CHILD_COUNT; octreeIndex++)
                    {
                        Engine::Physics::Common::BoundingBox &childBox = _collidersInNode[colliderIndex]->GetBoundingBox();
                        if (_childNodes[octreeIndex]->IsOverlap(childBox)) {
                            _childNodes[octreeIndex]->InsertCollider(_collidersInNode[colliderIndex]);
                            didntFoundAnyChild = false;
                        }
                    }
                    if(didntFoundAnyChild)
                    {

                    }
                }

                _collidersInNode.clear();
                _state = NodeState::Node;
            }
        break;
    }
}
bool Engine::Physics::World::Node::IsOverlap(Engine::Physics::Common::BoundingBox &colliderBox) noexcept
{
    return _box.IsOverlap(colliderBox);
}
void Engine::Physics::World::Node::RemoveCollider(Engine::Physics::Collider::Collider *collider)
{
    switch (_state)
    {
    case NodeState::Empty:
        break;
    case NodeState::Node:
        {
            bool allEmpty = true;
            for (int childIndex = 0; childIndex < OCTREE_CHILD_COUNT; ++childIndex) {
                _childNodes[childIndex]->RemoveCollider(collider);
                allEmpty &= _childNodes[childIndex]->_state == NodeState::Empty;
            }
            if (allEmpty) {
                _state = NodeState::Empty;
                for (int childIndex = 0; childIndex < OCTREE_CHILD_COUNT; ++childIndex) {
                    delete _childNodes[childIndex];
                }
            }
        }
        break;
    case NodeState::Leaf:
        for (int colliderIndex = 0; colliderIndex < _collidersInNode.size(); ++colliderIndex) {
            if(_collidersInNode[colliderIndex] == collider)
            {
                _collidersInNode.erase(std::remove(_collidersInNode.begin(), _collidersInNode.end(), _collidersInNode[colliderIndex]), _collidersInNode.end());
                break;
            }
        }

        if(_collidersInNode.empty())
        {
            _state = NodeState::Empty;
        }
        break;
    }
}
void Engine::Physics::World::Node::FillCollidedObjects(CollisionInfoContainer& collisionInfo) {
    switch (_state) {

    case NodeState::Empty:
        return;
    case NodeState::Node:
        for (int nodeIndex = 0; nodeIndex < OCTREE_CHILD_COUNT; ++nodeIndex) {
            _childNodes[nodeIndex]->FillCollidedObjects(collisionInfo);
        }
        break;
    case NodeState::Leaf:
        if(_collidersInNode.size() <= 1)
        {
            return;
        }

        for (int colliderIndex = 0; colliderIndex < _collidersInNode.size(); ++colliderIndex)
        {
            for (int secondColliderIndex = colliderIndex + 1; secondColliderIndex < _collidersInNode.size(); ++secondColliderIndex)
            {
                if(_collidersInNode[colliderIndex]->IsColliding(_collidersInNode[secondColliderIndex]))
                {
                    collisionInfo.TryInsert(_collidersInNode[colliderIndex],_collidersInNode[secondColliderIndex]);
                }
            }
        }
        break;
    }
}
