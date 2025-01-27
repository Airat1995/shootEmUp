#include "BoundingBox.h"
Engine::Physics::Common::BoundingBox::BoundingBox(glm::vec3 position, float halfSize)
{
    _halfSize = halfSize;
    _pos = position;
}

Engine::Physics::Common::BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
{
    _halfSize = max.x - min.x;
    _pos = {(max.x-min.x)/2, (max.y-min.y)/2, (max.z-min.z)/2};
}

bool Engine::Physics::Common::BoundingBox::IsOverlap(Engine::Physics::Common::BoundingBox &box) const noexcept
{
    glm::vec3 lhsMax = _pos + _halfSize;
    glm::vec3 lhsMin = _pos - _halfSize;

    glm::vec3 rhsMax = box._pos + box._halfSize;
    glm::vec3 rhsMin = box._pos - box._halfSize;

    bool collision = true;
    if( lhsMax.x < rhsMin.x || lhsMin.x > rhsMax.x ) {
        collision = false;
    }
    if( lhsMax.y < rhsMin.y || lhsMin.y > rhsMax.y ) {
        collision = false;
    }

    if( lhsMax.z < rhsMin.z || lhsMin.z > rhsMax.z ) {
        collision = false;
    }

    return collision;
}