#pragma once
#include "Octree.h"

namespace Engine::Physics::World
{
    struct OctreeNodeBlock {
        OctreeNode _nodes[NODE_CHILD_COUNT];
    };
}